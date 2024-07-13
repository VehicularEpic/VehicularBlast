#include "veb/engine/MapSelection.hpp"

#include "veb/component/Components.hpp"
#include "veb/component/ComponentMesh.hpp"
#include "veb/component/ComponentPosition.hpp"
#include "veb/component/ComponentRotation.hpp"

namespace veb {
namespace state {

MapSelection::MapSelection(Game &g) : game(g), map_it(g.GetMaps().begin()) {
    camera.SetPosition(0.f, 30.f, 100.f);
    camera.SetTarget(0.f, 0.f, 0.f);
    renderer.SetCamera(camera);

    UpdateMap();
}

void MapSelection::UpdateMap() {
    renderer.SetAmbientLight({0.f, 100.f, 40.f}, map_it->GetAmbientColor());
    renderer.SetSkyColor(map_it->GetSkyColor());
    renderer.SetGroundColor(map_it->GetGroundColor());

    world.Clear();

    for (const auto &object : map_it->GetObjects()) {
        Entity entity;
        Components<ComponentMesh>::Put(entity, {game.GetMeshBank().GetMesh(object.name)});
        Components<ComponentPosition>::Put(entity, {object.position.x, object.position.y, object.position.z});
        Components<ComponentRotation>::Put(entity, {object.rotation.x, object.rotation.y, object.rotation.z});

        world.AddEntity(entity);
    }
}

void MapSelection::Run(double delta) {
    auto &keyboard = game.GetKeyboard();

    if (keyboard.Poll(VK_RIGHT)) {
        ++map_it;

        if (map_it == game.GetMaps().end())
            map_it = game.GetMaps().begin();

        UpdateMap();
    }

    if (keyboard.Poll(VK_LEFT)) {
        if (map_it == game.GetMaps().begin())
            map_it = game.GetMaps().end();

        --map_it;

        UpdateMap();
    }

    camera.Rotate(0.f, delta, 0.f);

    renderer.SetCamera(camera);
    renderer.Render(world);
}

} // namespace state
} // namespace veb
