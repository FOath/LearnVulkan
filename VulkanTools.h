#pragma once
#include <vulkan/vulkan.h>
#include "VulkanInitializers.hpp"

#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#if defined(_WIN32)
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#elif defined(__ANDROID__)
#include "VulkanAndroid.h"
#include <android/asset_manager.h>
#endif

#define VK_FLAGS_NONE 0

#define DEFAULT_FENCE_TIMEOUT 100000000000

#define VK_CHECK_RESULT(f)																												\
{																																		\
	VkResult res = (f);																													\
	if (res != VK_SUCCESS)																												\
	{																																	\
		std::cout << "Fatal : VkResult is \"" << vks::tools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << "\n";	\
		assert(res == VK_SUCCESS);																										\
	}																																	\
}																																		\

const std::string getAssetPath();
const std::string getShaderBasePath();

namespace vks
{
	namespace tools
	{
		/// <summary>
		/// Disable message boxes on fatal errors
		/// </summary>
		extern bool errorModeSilent;

		/// <summary>
		/// Returns an error code as a string
		/// </summary>
		/// <param name="errorCode"></param>
		/// <returns></returns>
		std::string errorString(VkResult errorCode);

		/// <summary>
		/// Returns the deivce type as a string
		/// </summary>
		std::string physicalDeviceTypeString(VkPhysicalDeviceType type);

		/// <summary>
		/// Selected a suitable supported depth format starting with 32 bit down to 16 bit
		/// Returns false if none of the depth formats in the list is supported by the device
		/// </summary>
		/// <param name="physicalDevice"></param>
		/// <param name="depthFormat"></param>
		/// <returns></returns>
		VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat);

		/// <summary>
		/// Same as getSupportedDepthFormat but will only select formats that also have stencil
		/// </summary>
		/// <param name="physicalDevice"></param>
		/// <param name="depthStencilFormat"></param>
		/// <returns></returns>
		VkBool32 getSupportedDepthStencilFormat(VkPhysicalDevice physicalDevice, VkFormat* depthStencilFormat);

		/// <summary>
		/// Returns tru a given format support LINEAR filtering
		/// </summary>
		/// <param name="physicalDevice"></param>
		/// <param name="format"></param>
		/// <param name="tiling"></param>
		/// <returns></returns>
		VkBool32 formatIsFilterable(VkPhysicalDevice physicalDevice, VkFormat format, VkImageTiling tiling);

		/// <summary>
		/// Returns true if a given format has a stencil part
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		VkBool32 formatHasStencil(VkFormat format);

		/// <summary>
		/// Put an image memory barrier for setting an image layout on the sub resource into the given command buffer
		/// </summary>
		/// <param name="commandBuffer"></param>
		/// <param name="image"></param>
		/// <param name="oldImageLayout"></param>
		/// <param name="newImageLayou"></param>
		/// <param name="subresourceRange"></param>
		/// <param name="srcStageMask"></param>
		/// <param name="dstStageMask"></param>
		void setImageLayout(
			VkCommandBuffer commandBuffer,
			VkImage image,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayou,
			VkImageSubresourceRange subresourceRange,
			VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
		);

		/// <summary>
		/// Uses a fixed sub resource layout with first mip level and layer
		/// </summary>
		/// <param name="commandBuffer"></param>
		/// <param name="image"></param>
		/// <param name="aspectMask"></param>
		/// <param name="oldImageLayout"></param>
		/// <param name="newImageLayout"></param>
		/// <param name="srcStageMask"></param>
		/// <param name="dstStageMask"></param>
		void setImageLayout(
			VkCommandBuffer commandBuffer,
			VkImage image,
			VkImageAspectFlags aspectMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
		);

		/// <summary>
		/// Insert an image memory barrier into the command buffer
		/// </summary>
		/// <param name="cmdBuffer"></param>
		/// <param name="image"></param>
		/// <param name="srcAccessMask"></param>
		/// <param name="dstAccessMask"></param>
		/// <param name="oldImageLayout"></param>
		/// <param name="newImageLayout"></param>
		/// <param name="srcStageMask"></param>
		/// <param name="dstStageMask"></param>
		/// <param name="subresourceRange"></param>
		void insertImageMemoryBarrier(
			VkCommandBuffer cmdBuffer,
			VkImage image,
			VkAccessFlags srcAccessMask,
			VkAccessFlags dstAccessMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask,
			VkImageSubresourceRange subresourceRange
		);

		/// <summary>
		/// Display error message and exit on fatal error
		/// </summary>
		/// <param name="message"></param>
		/// <param name="exitCode"></param>
		void exitFatal(const std::string& message, int32_t exitCode);

		void exitFatal(const std::string& message, VkResult resultCode);

		// Load a SPIR-V shader (binary)
#if defined(__ANDROID__)
		VkShaderModule loadShader(AAssetManager* assetManager, const char* fileName, VkDevice device);
#else
		VkShaderModule loadShader(const char* fileName, VkDevice device);
#endif

		bool fileExists(const std::string& filename);

		uint32_t alignedSize(uint32_t value, uint32_t alignment);
	}
}