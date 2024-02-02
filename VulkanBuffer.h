#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanTools.h"

namespace vks
{
	/// <summary>
	/// Encapsulates access to a Vulkan buffer backed up by device memory
	/// To be filled by an external source like the VulkanDevice
	/// </summary>
	struct Buffer
	{
		VkDevice device;
		VkBuffer buffer = VK_NULL_HANDLE;
		VkDeviceMemory memory = VK_NULL_HANDLE;
		VkDescriptorBufferInfo descriptor;
		VkDeviceSize size = 0;
		VkDeviceSize alignment = 0;
		void* mapped = nullptr;
		/// <summary>
		/// Usage flags to be filled by external source at buffer creation (to query at asome later point)
		/// </summary>
		VkBufferUsageFlags usageFlags;
		/// <summary>
		/// Memory property flags to be filled by external source at buffer creation (to query at some later point)
		/// </summary>
		VkMemoryPropertyFlags memoryPropertyFlags;
		VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void unmap();
		VkResult bind(VkDeviceSize offset = 0);
		void setupDescriptor(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void copyTo(void* data, VkDeviceSize size);
		VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
		void destroy();
	};
}