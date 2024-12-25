#pragma once

#include <glad/glad.h>
#include <components/Components.h>

class GlUtil
{
public:
    static void genFbo(std::shared_ptr<Fbo> fbo)
    {
        glGenFramebuffers(1, &fbo->id);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo->id);

        glGenTextures(1, &fbo->texture);
        glBindTexture(GL_TEXTURE_2D, fbo->texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fbo->width, fbo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->texture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            // Handle framebuffer not complete
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};