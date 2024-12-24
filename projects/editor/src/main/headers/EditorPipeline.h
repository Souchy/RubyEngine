#pragma once

#include "DefaultPipeline.h"

class EditorPipeline : public DefaultPipeline {
public:

    virtual void systemRenderColor(flecs::world &world, flecs::entity_t phase) override {
        // ---------- Create FBO texture

		// Fbo fbo;
		// world.set<Fbo>(fbo);
        // auto ws = world.get<WindowSize>();
		auto w = world.get<Window>();

        // glGenFramebuffers(1, &w->fbo->id);
        // glBindFramebuffer(GL_FRAMEBUFFER, w->fbo->id);

        // glGenTextures(1, &w->fbo->texture);
        // glBindTexture(GL_TEXTURE_2D, w->fbo->texture);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w->fbo->width, w->fbo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, w->fbo->texture, 0);

        // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        //     // Handle framebuffer not complete
        // }
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
        // ---------- Render System

        world.system<Window, Shader>("RenderPass_Color")
            .kind(phase) //
            .term_at(0)
            .singleton()
            .each([this](flecs::iter &it, size_t i, const Window &w, const Shader &shader) {
                // glBindFramebuffer(GL_FRAMEBUFFER, w.fbo->id);

                // // // 2. then render scene as normal with shadow mapping (using depth map)
                // glViewport(w.fbo->x, w.fbo->y, w.fbo->width, w.fbo->height);
                // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // glEnable(GL_CULL_FACE);
                // glCullFace(GL_BACK);

                // // Render objects
                // glUseProgram(shader.programId());
                // // glBindTextureUnit(0, *depthMap); // Bind shadow map to texture unit 0
                // // renderNode(root);
                // // Idk if I should use the System or the Query. System is multithreaded.
                // this->renderMeshSystem.run();

                // glBindFramebuffer(GL_FRAMEBUFFER, 0);
            });
    }
};
