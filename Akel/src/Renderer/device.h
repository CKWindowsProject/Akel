// This file is a part of Akel
// CREATED : 05/06/2021
// UPDATED : 05/06/2021

#ifndef __AK_VK_DEVICE__
#define __AK_VK_DEVICE__

#include <Akpch.h>

#include <Renderer/imageView.h>

namespace Ak
{
	const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	
	class Device : public ImageView
	{
		public:
			Device();

            void pickPhysicalDevice();
            bool isDeviceSuitable(VkPhysicalDevice device);
            void createLogicalDevice();
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}

#endif // __AK_VK_DEVICE__

