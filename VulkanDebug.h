#pragma once
#include <vulkan/vulkan.h>

#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#endif
#ifdef __ANDROID__
#include "VulkanAndroid.h"
#endif
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace vks
{
	namespace debug
	{
		// Default debug callback
		VKAPI_ATTR VkBool32 VKAPI_CALL messageCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t srcObject,
			size_t location,
			int32_t msgCode,
			const char* pLayerPrefix,
			const char* pMsg,
			void* pUserData
		);

		// Load debug function pointers and set debug callback
		void setupDebugging(VkInstance instance);

		// Clear debug callback
		void freeDebugCallback(VkInstance instacne);
	}

	// Wrapper for the VK_EXT_debug_utils extension
	// These can be used to name Vulkan objects for debugging tools like RenderDoc
	namespace debugutils
	{
		void setup(VkInstance instance);
		void cmdBeginLabel(VkCommandBuffer cmdBuffer, std::string caption, glm::vec4 color);
		void cmdEndLabel(VkCommandBuffer cmdBuffer);
	}
}