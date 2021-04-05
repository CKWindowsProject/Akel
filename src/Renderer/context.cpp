// This file is a part of AtlasEngine
// CREATED : 05/04/2021
// UPDATED : 05/04/2021

#include <Renderer/renderer.h>

namespace AE
{
    Context::Context() {}

    void Context::init(SDL_Window* window, ContextType type)
    {
        _type = type;
        _window = window;
        if(_type == OpenGL)
        {
            _glcontext = SDL_GL_CreateContext(_window);
            if(!_glcontext)
                messageBox(FATAL_ERROR, "Can't init GL context", SDL_GetError());
            
            GLuint GLEWerr = glewInit();
            if(GLEW_OK != GLEWerr)
                messageBox(FATAL_ERROR, "Can't init GLEW", std::string(reinterpret_cast<AE_text>(glewGetErrorString(GLEWerr))));
        }
    }
    void Context::SwapBuffers()
    {
        if(_type == OpenGL)
            SDL_GL_SwapWindow(_window);
    }
    void Context::enableVerticalSync(bool enabled)
    {
        if(_type == OpenGL)
            SDL_GL_SetSwapInterval(enabled);
    }
    bool Context::isCreated()
    {
        if(!_glcontext)
            return false;
        return true;
    }
    void Context::destroy()
    {
        if(_type == OpenGL)
            SDL_GL_DeleteContext(_glcontext);
    }

    Context::~Context()
    {
        destroy();
    }
}
