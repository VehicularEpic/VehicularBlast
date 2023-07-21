#include "veb/io/MeshFile.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <draco/mesh/mesh.h>
#include <draco/core/decoder_buffer.h>
#include <draco/compression/decode.h>

#include <GLTFSDK/GLTF.h>
#include <GLTFSDK/GLBResourceReader.h>
#include <GLTFSDK/Deserialize.h>
#include <GLTFSDK/RapidJsonUtils.h>

/**
 * Decoding compressed data with draco (thanks to Blender :D)
 * 
 * Reference:
 * https://github.com/blender/blender/tree/main/extern/draco
*/

class MeshAttributes {
private:
    std::map<draco::GeometryAttribute::Type, const draco::PointAttribute *> attributes;

public:
    MeshAttributes(const std::unique_ptr<draco::Mesh> &mesh) {
        for (uint32_t i = 0; i < mesh->num_attributes(); i++) {
            const draco::PointAttribute *attribute = mesh->GetAttributeByUniqueId(i);
            attributes.emplace(std::make_pair(attribute->attribute_type(), attribute));
        }
    }

    ~MeshAttributes() = default;

    std::vector<float> GetValue(draco::GeometryAttribute::Type type, const draco::PointIndex &index) {
        auto attribute = attributes.at(type);
        std::vector<float> data(attribute->num_components());

        attribute->GetMappedValue(index, &data[0]);
        return data;
    }
};

class MeshStreamReader : public Microsoft::glTF::IStreamReader {
public:
    std::shared_ptr<std::istream> GetInputStream(const std::string &filename) const override {
        auto istream = std::make_shared<std::ifstream>(filename, std::ios_base::binary);
        return istream;
    }
};

namespace veb {

MeshFile::MeshFile(const std::string &filePath) {
    auto streamReader = std::make_unique<MeshStreamReader>();
    auto istream = streamReader->GetInputStream(filePath);

    Microsoft::glTF::GLBResourceReader reader(std::move(streamReader), std::move(istream));
    auto gltf = Microsoft::glTF::Deserialize(reader.GetJson());

    if (!gltf.IsExtensionRequired("KHR_draco_mesh_compression"))
        return;

    if (gltf.meshes.Size() < 1)
        return;

    draco::Decoder decoder;
    auto mesh = gltf.meshes[0];

    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
        auto primitive = mesh.primitives[i];
        float color[4] = {.5f, .5f, .5f, 1.f};

        if (gltf.materials.Has(primitive.materialId)) {
            auto material = gltf.materials.Get(primitive.materialId);
            auto baseColor = material.metallicRoughness.baseColorFactor;

            color[0] = baseColor.r;
            color[1] = baseColor.g;
            color[2] = baseColor.b;
            color[3] = baseColor.a;
        }

        auto bufferView = gltf.bufferViews[i];
        auto binary = reader.ReadBinaryData<char>(gltf, bufferView);

        draco::DecoderBuffer buffer;
        buffer.Init(&binary[0], binary.size());

        auto status = decoder.DecodeMeshFromBuffer(&buffer);
        if (!status.ok())
            continue;

        std::unique_ptr<draco::Mesh> decoded = std::move(status).value();
        MeshAttributes attributes(decoded);

        for (uint32_t k = 0; k < decoded->num_faces(); k++) {
            auto face = decoded->face(draco::FaceIndex(k));
            points += face.size();

            for (const draco::PointIndex &index : face) {
                auto position = attributes.GetValue(draco::GeometryAttribute::Type::POSITION, index);
                data.insert(data.end(), position.begin(), position.end());

                auto normal = attributes.GetValue(draco::GeometryAttribute::Type::NORMAL, index);
                data.insert(data.end(), normal.begin(), normal.end());

                data.insert(data.end(), std::begin(color), std::end(color));
            }
        }
    }
}

} // namespace veb
