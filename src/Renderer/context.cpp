// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 14/04/2021

#include <Renderer/renderer.h>
#include <Platform/platform.h>

namespace AE
{
    Context::Context() {}

    void Context::init(SDL_Window* window)
    {
        _window = window;
        _glcontext = SDL_GL_CreateContext(_window);
        if(!_glcontext)
            messageBox(FATAL_ERROR, "Can't init GL context", SDL_GetError());
        
        GLuint GLEWerr = glewInit();
        if(GLEW_OK != GLEWerr)
            messageBox(FATAL_ERROR, "Can't init GLEW", std::string(reinterpret_cast<AE_text>(glewGetErrorString(GLEWerr))));

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, int(std::stof(Core::SoftInfo::getGLinfo()))); // Init opengl with driver version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, int(std::stof(Core::SoftInfo::getGLinfo()) - int(std::stof(Core::SoftInfo::getGLinfo()))));
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        std::cout << bg_green << "GL context created successfully with version : " << Core::SoftInfo::getGLinfo() << bg_def << std::endl;
    }
    void Context::SwapBuffers()
    {
        SDL_GL_SwapWindow(_window);
        clearRendering();
    }
    void Context::setVerticalSync(bool enabled)
    {
        SDL_GL_SetSwapInterval(enabled);
    }
    void Context::clearRendering()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
    }
    bool Context::isCreated()
    {
        if(!_glcontext)
            return false;
        return true;
    }
    void Context::destroy()
    {
        if(_glcontext)
            SDL_GL_DeleteContext(_glcontext);
    }

    Context::~Context()
    {
        destroy();
    }
}