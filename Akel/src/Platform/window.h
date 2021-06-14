// This file is a part of Akel
// CREATED : 28/03/2021
// UPDATED : 13/06/2021

#ifndef __AK_WINDOW__
#define __AK_WINDOW__

#include <Akpch.h>
#include <Core/core.h>
#include <Renderer/renderer.h>
#include <Maths/maths.h>
#include <Platform/input.h>
#include <Utils/utils.h>

enum windowSetting
{
    title,
    dimensions,
    position,
    fullscreen,
    border,
    brightness,
    opacity,
    resizable,
    visible,
    maximumSize,
    minimumSize,
    icon
};

namespace Ak
{
    class Window : public Instance
    {
        public:
            Window();

            void create(std::string title, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

            void initWindowRenderer(const char* vert, const char* frag);

            // Setters            
            void setSetting(windowSetting setting, Ak_text value);
            void setSetting(windowSetting setting, bool value);
            void setSetting(windowSetting setting, float value);
            void setSetting(windowSetting setting, uint16_t x, uint16_t y);

            // Getters
            std::string getTitle();
            uint32_t getFlags();
            Maths::Vec2<uint16_t> getPosition();
            Maths::Vec2<uint16_t> getSize();

            void update();

            void destroy();

            virtual ~Window();
        
        private:
            SDL_Window* _window;

            std::string _title;
            Maths::Vec2<uint16_t> _position;
            Maths::Vec2<uint16_t> _size;

            uint32_t _flags;

            SDL_Surface* _icon;
    };
}

#endif // __AK_WINDOW__
