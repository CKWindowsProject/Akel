// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 23/09/2021

#include <Renderer/surface.h>

namespace Ak
{
	Surface::Surface() : LowestInheritance() {}
    void Surface::createSurface()
    {
        if(SDL_Vulkan_CreateSurface(window, instance, &surface) != SDL_TRUE)
            std::cout << SDL_GetError() << std::endl;
    }

    VkSurfaceFormatKHR Surface::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for(const auto& availableFormat : availableFormats)
        {
            if(availableFormat.format == VK_FORMAT_R8G8B8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;
        }

        return availableFormats[0];
    }
}
