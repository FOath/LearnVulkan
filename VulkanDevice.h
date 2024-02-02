#pragma once

#include <algorithm>
#include <cassert>
#include <exception>

#include <vulkan/vulkan.h>

#include "VulkanBuffer.h"
#include "VulkanTools.h"


namespace vks
{
	struct VulkanDevice
	{
		/// <summary>
		/// Physical device representation
		/// </summary>
		VkPhysicalDevice physicalDevice;

		/// <summary>
		/// Logical device representation (application's view of the device)
		/// </summary>
		VkDevice logicalDevice;

		/// <summary>
		/// Properties of the physical device including limits that the application can check against
		/// </summary>
		VkPhysicalDeviceProperties properties;

		/// <summary>
		/// Features of the physical device that an application can use to check if a feature is supported
		/// </summary>
		VkPhysicalDeviceFeatures features;

		/// <summary>
		/// Features that have been enabled for use on the physical device
		/// </summary>
		VkPhysicalDeviceFeatures enabledFeatures;

		/// <summary>
		/// Memory types and heaps of the physical device
		/// </summary>
		VkPhysicalDeviceMemoryProperties memoryProperties;

		/// <summary>
		/// Queue family properties of the physical device
		/// </summary>
		std::vector<VkQueueFamilyProperties> queueFamilyProperties;

		/// <summary>
		/// List of extensions supported by the device
		/// </summary>
		std::vector<std::string> supportedExtensions;

		/// <summary>
		/// Default command pool for the graphics queue family index
		/// </summary>
		VkCommandPool commandPool = VK_NULL_HANDLE;

		/// <summary>
		/// Contains queue family indices
		/// </summary>
		struct
		{
			uint32_t graphics;
			uint32_t compute;
			uint32_t transfer;
		} queueFamilyIndices;

		operator VkDevice() const
		{
			return logicalDevice;
		}

		explicit VulkanDevice(VkPhysicalDevice physicalDevice);
		~VulkanDevice();
		uint32_t getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32* memTypeFound = nullptr) const;
		uint32_t getQueueFamilyIndex(VkQueueFlags queueFlags) const;
		VkResult createLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures, std::vector<const char*> enabledExtensions, void* pNextChain, bool useSwapChain = true, VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
		VkResult createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer* buffer, VkDeviceMemory* memory, void* data = nullptr);
		VkResult createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, vks::Buffer* buffer, VkDeviceSize size, void* data = nullptr);
		void copyBuffer(vks::Buffer* src, vks::Buffer* dst, VkQueue queue, VkBufferCopy* copyRegion = nullptr);
		VkCommandPool createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, VkCommandPool pool, bool begin = false);
		VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, bool begin = false);
		void flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, VkCommandPool pool, bool free = true);
		void flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, bool free = true);
		bool extensionSupported(std::string extension);
		VkFormat getSupportedDepthFormat(bool checkSamplingSupport);
	};
}