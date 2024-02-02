
#include "VulkanBuffer.h"

namespace vks
{
	/// <summary>
	/// Map a memory range of this buffer. If successful, mapped points to the specified buffer range.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="offset"></param>
	/// <returns>VKResult of the buffer mappint call</returns>
	VkResult Buffer::map(VkDeviceSize size, VkDeviceSize offset)
	{
		return vkMapMemory(device, memory, offset, size, 0, &mapped);
	}

	/// <summary>
	/// Unmap a mapped memory range
	/// </summary>
	void Buffer::unmap()
	{
		if (mapped)
		{
			vkUnmapMemory(device, memory);
			mapped = nullptr;
		}
	}

	/// <summary>
	/// Attach the allocated memory block to the buffer
	/// </summary>
	/// <param name="offset"></param>
	/// <returns></returns>
	VkResult Buffer::bind(VkDeviceSize offset)
	{
		return vkBindBufferMemory(device, buffer, memory, offset);
	}

	/// <summary>
	/// Setup the default descriptor for this buffer
	/// </summary>
	/// <param name="size"></param>
	/// <param name="offset"></param>
	void Buffer::setupDescriptor(VkDeviceSize size, VkDeviceSize offset)
	{
		descriptor.offset = offset;
		descriptor.buffer = buffer;
		descriptor.range = size;
	}

	/// <summary>
	/// Copies the specified data to the mapped buffer
	/// </summary>
	/// <param name="data"></param>
	/// <param name="size"></param>
	void Buffer::copyTo(void* data, VkDeviceSize size)
	{
		assert(mapped);
		memcpy(mapped, data, size);
	}

	/// <summary>
	/// Flush a memory range of the buffer to make it visible to the device
	/// </summary>
	/// <param name="size"></param>
	/// <param name="offset"></param>
	/// <returns></returns>
	VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset)
	{
		VkMappedMemoryRange mappedRange{};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkFlushMappedMemoryRanges(device, 1, &mappedRange);
	}

	/// <summary>
	/// Invalidate a memory range of the buffer to make it visible to the host
	/// </summary>
	/// <param name="size"></param>
	/// <param name="offset"></param>
	/// <returns></returns>
	VkResult Buffer::invalidate(VkDeviceSize size, VkDeviceSize offset)
	{
		VkMappedMemoryRange mappedRange{};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkInvalidateMappedMemoryRanges(device, 1, &mappedRange);
	}

	/// <summary>
	/// Release all Vulkan resources held by this buffer
	/// </summary>
	void Buffer::destroy()
	{
		if (buffer)
		{
			vkDestroyBuffer(device, buffer, nullptr);
		}
		if (memory)
		{
			vkFreeMemory(device, memory, nullptr);
		}
	}
}