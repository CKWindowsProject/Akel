// This file is a part of Akel
// CREATED : 24/09/2021
// UPDATED : 26/09/2021

#include <Renderer/Memory/chunk.h>
#include <Core/core.h>

namespace Ak
{
    bool Buffer::operator == (Buffer const& buffer)
    {
        if(memory == buffer.memory && offset == buffer.offset && size == buffer.size && ptr == buffer.ptr)
            return true;
        return false;
    }

    Chunk::Chunk(VkDeviceSize size, int memoryTypeIndex) : LowestInheritance()
    {
        _size = size;
        _memoryTypeIndex = memoryTypeIndex;

        VkMemoryAllocateInfo allocateInfo{};
        allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocateInfo.allocationSize = size;
        allocateInfo.memoryTypeIndex = memoryTypeIndex;

        Buffer buffer;
        buffer.offset = 0;
        buffer.size = size;
        if(vkAllocateMemory(device, &allocateInfo, nullptr, &_memory) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : Chunck : failed to allocate buffer memory");

        buffer.memory = _memory;

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        if((memProperties.memoryTypes[memoryTypeIndex].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            vkMapMemory(device, _memory, 0, VK_WHOLE_SIZE, 0, &_ptr);
        buffer.ptr = _ptr;

        _freeBuffers.emplace_back(buffer);
    }

#pragma GCC diagnostic push
// to avoid "warning: always_inline function might not be inlinable [-Wattributes]"
#pragma GCC diagnostic ignored "-Wattributes"
    forceinline bool Chunk::contains(const Buffer& buffer)
    {
        for(auto it = _usedBuffers.begin(); it != _usedBuffers.end(); it++)
        {
            if(*it == buffer)
                return true;
        }
        return false;
    }

    forceinline bool Chunk::canHold(VkDeviceSize size)
    {
        return size <= _size - _memUsed;
    }
#pragma GCC diagnostic pop

    bool Chunk::alloc(VkDeviceSize size, Buffer& buffer, VkDeviceSize alignment)
    {
        if(size > _size)
            Core::log::report(FATAL_ERROR, "Vulkan : Chunck : unable to allocate buffer, not enought free space");

        for(Buffer& bufferAllocated : _freeBuffers)
        {
            uint32_t newSize = bufferAllocated.size;

            if(bufferAllocated.offset % alignment != 0)
                newSize -= alignment - bufferAllocated.offset % alignment;

            if(newSize >= size)
            {
                bufferAllocated.size = newSize;
                if(bufferAllocated.offset % alignment != 0)
                    bufferAllocated.offset += alignment - bufferAllocated.offset % alignment;

                if(_ptr != nullptr)
                    bufferAllocated.ptr = (char*)_ptr + bufferAllocated.offset;

                if(bufferAllocated.size == size)
                {
                    buffer = bufferAllocated;
                    return true;
                }

                Buffer nextBuffer;
                nextBuffer.offset = bufferAllocated.offset + size;
                nextBuffer.memory = _memory;
                nextBuffer.size = bufferAllocated.size - size;
                _freeBuffers.emplace_back(nextBuffer);

                bufferAllocated.size = size;

                buffer = bufferAllocated;
                return true;
            }
        }
        return false;
    }

    void Chunk::free(const Buffer& buffer)
    {
        auto bufferIt(std::find(_usedBuffers.begin(), _usedBuffers.end(), buffer));
        if(bufferIt == _usedBuffers.end())
            Core::log::report(FATAL_ERROR, "Vulkan : Allocator_GPU : Chunck : free(const Buffer&) : unable to find the buffer in the stack, it cannot be freed");
        _freeBuffers.emplace_back(*bufferIt);
        _usedBuffers.erase(bufferIt);
    }
}
