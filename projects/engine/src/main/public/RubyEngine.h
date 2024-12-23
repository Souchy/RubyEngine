/*
 * This source file was generated by the Gradle 'init' task
 */
#pragma once

#ifndef RUBYENGINE_H
#define RUBYENGINE_H

#ifdef _WIN32
#define RUBYENGINE_EXPORT_FUNC __declspec(dllexport)
#else
#define RUBYENGINE_EXPORT_FUNC
#endif

#include <iostream>
#include <windows.h>
#include <string>
#include <flecs.h>
#include <glm/glm.hpp>

#include <Window.h>
#include <shaders/Shader.h>
#include "nodes/3d/Node3d.h"
#include "components/3d/Components3d.h"
#include <components/Components.h>
#include "resources/Material.h"
#include "resources/Mesh.h"
#include <util/MeshVao.h>
#include <util/shapes/Cube.h>
#include <util/shapes/Gizmo.h>
#include <io/Files.h>
#include <Ui.h>
#include <DefaultPipeline.h>

namespace RubyEngine {
class Greeter {
public:
    std::string RUBYENGINE_EXPORT_FUNC greeting();
};

} // namespace RubyEngine

class Ruby {
public:
    flecs::world world;
    // flecs::query<Transform3d, MeshVao, Material> renderables;
    // flecs::system renderMeshSystem;
    std::shared_ptr<Pipeline> pipeline = nullptr;

    void init();
    void start();
};

#endif
