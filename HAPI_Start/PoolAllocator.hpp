#pragma once

#ifndef POOLALLOCATOR_HPP
#define POOLALLOCATOR_HPP
#include <HAPI_lib.h>
#include <cassert>

#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>

#include "Types.hpp"
#include "Utils.hpp"

constexpr size_t one_gigabyte{ 1073741824 };

constexpr u32 max_block_size = one_gigabyte;


/// TODO: partition a single shared pool of memory into smaller blocks to ensure that new is not called at runtime
struct Block
{
	Block(size_t block_size, const std::string& name, u8* data ,Block* prev = nullptr, Block* next = nullptr) : data_(data), block_size_(block_size), name_(name), prev_(prev), next_(next)
	{
		
		// memset(data_, 255, block_size);
		// block_size_ = 4096;
		
	}
	~Block()
	{
		
	}

	
	u8* data_;

	

	// blocks arranged in singly linked list
	// note that this means the memory is inherently non contiguous;
	Block* next_{ nullptr };

	Block* prev_{ nullptr };

	size_t block_size_;

	

	std::string name_;
};
// This is an attempt at making a pool memory allocator to reduce the number of calls to new and also to allow better memory management debugging
// This Pool Allocator should also ensure that no leaks occur as the memory in each block is always deleted when the program exits(provided that the desturctors are called correctly)
// TODO: intercept calls to new 
// TODO: classes with variadic args?
// could write some kind of get allocator which holds a static templated allocator?
// does make this very annoying
class PoolAllocator
{
public:
	PoolAllocator(size_t size) : pool_size_(size)
	{
		DEBUG_ONLY(std::cout << "Created pool of size: " << size;);
		pool_ = new u8[size];// new u8[size]();

	}

	
	~PoolAllocator();
	
	PoolAllocator(const PoolAllocator& other) = delete;
	
	/*
	template <typename T, typename... Args>
	T* Allocate(size_t count = 1, const std::string& name = "", Args&&... args)
	{
		if (count == 0)
		{
			return nullptr;
		}
		if (sizeof(T) * count >= max_block_size)
		{
			assert("Allocating over 1GB at a time is not recommended for performance reasons" && false);
			return nullptr;
		}
		void* tmp = last_->data_ + last_->block_size_;
		size_t space = pool_size_ - GetAllocatedSize();

		assert(sizeof(T) % alignof(T) == 0);
		void* aligned = std::align(alignof(T), sizeof(T) * count, tmp, space);
		T* ptr = (T*)aligned;
		assert(ptr != nullptr);
		ptr[0] = T(std::forward<Args>(args)...);
		return ptr;

	}
	*/
	template <typename T>
	T* Allocate(size_t count = 1, const std::string& name = "")
	{
		if (count == 0)
		{
			return nullptr;
		}
		T* ptr = (T*)Allocate(sizeof(T) *  count, name);
		
		
		return ptr;

	}
	// returns a pointer to a block of memory
	// TODO: search for gaps of sufficient size in the pool and allocate in those gaps
	u8* Allocate(size_t size, const std::string& name = "");
	template<typename T>
	void Deallocate(T** ptr)
	{
		if (ptr == nullptr)
		{
			// no need to deallocate a nullptr
			return;
		}
		if (root_ == nullptr)
		{
			// no blocks allocated
			return;
		}
		
		// Block* block = (Block*)ptr;
		// block->free_ = true;
		
		
		Block* current = root_;
		while (current)
		{
			// std::cerr << std::hex << (void*)current->data_ << std::dec << "\n";
			// std::cerr << std::hex << (void*)current << std::dec << "\n";
			// std::cerr << std::hex << (void*)*ptr << std::dec << "\n\n\n";

			// finally works all i needed to do was pass the pointer by pointer
			if ((void*)(*ptr) == (void*)(current->data_))
			{
				DEBUG_ONLY(std::cout << "freed " << current->name_ << "\n";);
				// current->free_ = true;
				if (current == root_)
				{
					root_ = current->next_;
				}
				if (current->prev_ != nullptr)
				{
					current->prev_->next_ = current->next_;
				}
				if (current->next_ != nullptr)
				{
					current->next_->prev_ = current->prev_;
				}
				delete current;
				return;
			}
			current = current->next_;
		}
		
		// the pointer isn't from the pool allocator 
	}
	
	/// MemDump to file using a preconstructed file stream so file opening can be done in advance
	/// This function does not close the file stream
	void MemDump(std::fstream& file);
	
	/// Write all of the memory from  the allocator to a file
	/// Creates and destroys a filestream within this function
	/// For code which should be Fast it is recommended you use the version which uses a preopened filestream 
	void MemDump(const std::string& filename);
	
	void LeakCheck(const std::string& filename);
	
	size_t GetPoolSize() const { return pool_size_; }
	size_t GetAllocatedSize() const;

private:

	
	


	Block* root_{ nullptr };
	Block* last_{ nullptr };

	size_t pool_size_;
	
	u8* pool_{ nullptr };
	
};

extern PoolAllocator g_allocator;

#endif