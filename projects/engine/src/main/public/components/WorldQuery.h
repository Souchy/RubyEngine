#pragma once

#include <components/3d/Components3d.h>
#include <flecs.h>
#include <resources/Material.h>
#include <util/MeshVao.h>

class WorldQuery {
public:
    flecs::query<Transform3d, MeshVao, Material> renderables;
};
