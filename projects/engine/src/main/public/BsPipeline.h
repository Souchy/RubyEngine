#pragma once

#include "DefaultPipeline.h"

class BsPipeline : public Pipeline {
public:
    virtual void init(flecs::world &world) {
    }
    virtual void systemInputs(flecs::world &world, flecs::entity_t phase) {
    }
    virtual void systemUpdateLogic(flecs::world &world, flecs::entity_t phase) {
    }
    virtual void systemUpdatePhysic(flecs::world &world, flecs::entity_t phase) {
    }
    virtual void systemRenderDepth(flecs::world &world, flecs::entity_t phase) {
    }
    virtual void systemRenderColor(flecs::world &world, flecs::entity_t phase) {
    }
    virtual void systemRenderMesh(flecs::world &world) {
    }
    virtual void systemRenderUi(flecs::world &world, flecs::entity_t phase) {
    }
    virtual void systemRenderWindow(flecs::world &world, flecs::entity_t phase) {
    }
};
