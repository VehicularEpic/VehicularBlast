#include "veb/engine/Map.hpp"
#include "veb/pbf/map_pbf.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define ONE_MB_MEMORY sizeof(uint8_t) * 1024 * 1024

namespace veb {

Map::Map(const std::string &filePath, const MeshBank &bank) {
    FILE *file = fopen(filePath.c_str(), "rb");
    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    void *buffer = malloc(sizeof(uint8_t) * size);
    fread(buffer, sizeof(uint8_t), size, file);
    fclose(file);

    void *workspace = malloc(ONE_MB_MEMORY);

    struct map_t *map = map_new(workspace, ONE_MB_MEMORY);
    map_decode(map, static_cast<uint8_t *>(buffer), size);
    free(buffer);

    name = std::string(map->name_p);

    uint8_t uAmbient[3];
    memcpy(uAmbient, map->ambient_color.buf_p, sizeof(uAmbient));
    ambient.r = uAmbient[0] / 255.f;
    ambient.g = uAmbient[1] / 255.f;
    ambient.b = uAmbient[2] / 255.f;

    uint8_t uSky[3];
    memcpy(uSky, map->sky_color.buf_p, sizeof(uSky));
    sky.r = uSky[0] / 255.f;
    sky.g = uSky[1] / 255.f;
    sky.b = uSky[2] / 255.f;

    uint8_t uGround[3];
    memcpy(uGround, map->ground_color.buf_p, sizeof(uGround));
    ground.r = uGround[0] / 255.f;
    ground.g = uGround[1] / 255.f;
    ground.b = uGround[2] / 255.f;

    std::vector<std::string> objects;
    for (int i = 0; i < map->objects.length; i++)
        objects.push_back(std::string(map->objects.items_pp[i]));

    auto CreateEntity = [&](const map_entity_t &e) {
        veb::Entity entity;
        const Mesh &mesh = bank.GetMesh(objects.at(e.i));

        entity.Add(ComponentMesh{mesh});
        entity.Add(ComponentPosition{e.position.items_p[0], e.position.items_p[1], e.position.items_p[2]});
        entity.Add(ComponentRotation{e.rotation.items_p[0], e.rotation.items_p[1], e.rotation.items_p[2]});

        return entity;
    };

    for (int i = 0; i < map->set.length; i++)
        entities.push_back(CreateEntity(map->set.items_p[i]));

    for (int i = 0; i < map->fix.length; i++)
        entities.push_back(CreateEntity(map->fix.items_p[i]));

    for (int i = 0; i < map->chk.length; i++)
        entities.push_back(CreateEntity(map->chk.items_p[i]));

    free(workspace);
}

} // namespace veb
