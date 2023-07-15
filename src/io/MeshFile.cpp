#include "veb/io/MeshFile.hpp"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include <cgltf.h>
#include <draco/mesh/mesh.h>
#include <draco/core/decoder_buffer.h>
#include <draco/compression/decode.h>

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

namespace veb {

MeshFile::MeshFile(const std::string &filePath) {
    cgltf_data *model = NULL;
    cgltf_options options = {cgltf_file_type_glb};
    cgltf_result result = cgltf_parse_file(&options, filePath.c_str(), &model);

    if (result != cgltf_result_success) {
        cgltf_free(model);
        return;
    }

    result = cgltf_load_buffers(&options, model, NULL);
    if (result != cgltf_result_success) {
        cgltf_free(model);
        return;
    }

    draco::Decoder decoder;
    for (uint32_t i = 0; i < model->meshes_count; i++) {
        const cgltf_mesh &mesh = model->meshes[i];

        for (uint32_t j = 0; j < mesh.primitives_count; j++) {
            const cgltf_primitive &primitive = mesh.primitives[j];
            if (!primitive.has_draco_mesh_compression)
                continue; // TODO: uncompressed data

            float color[4] = {.5f, .5f, .5f, 1.f};
            if (primitive.material->has_pbr_metallic_roughness) {
                float *material = primitive.material->pbr_metallic_roughness.base_color_factor;
                memcpy(&color[0], material, sizeof(color));
            }

            draco::DecoderBuffer buffer;
            cgltf_buffer_view *view = primitive.draco_mesh_compression.buffer_view;
            buffer.Init(static_cast<char *>(view->buffer->data) + view->offset, view->size);

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

    cgltf_free(model);
}

} // namespace veb
