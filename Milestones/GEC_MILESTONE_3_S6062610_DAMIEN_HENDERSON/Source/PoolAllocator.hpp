#pragma once

#include <HAPI_lib.h>
#include <cassert>

#include <fstream>
#include <string>
#include <cstdlib>

#include "Types.hpp"


constexpr u32 max_block_size = 1000000000;


struct Block
{
	Block(size_t block_size = 4096, Block* next = nullptr, const std::string& name = "") : block_size_(block_size), name_(name)
	{
		data_ = new u8[block_size]();
		memset(data_, 255, block_size);
		next_ = next;
	}
	~Block()
	{
		delete[] data_;
	}

	
	u8* data_;

	

	// blocks arranged in singly linked list
	// note that this means the memory is inherently non contiguous;
	Block* next_{ nullptr };

	size_t block_size_;

	bool free_{ false };

	std::string name_;
};
// This is an attempt at making a pool memory allocator to reduce the number of calls to new and also to allow better memory management debugging
// This Pool Allocator should also ensure that no leaks occur as the memory in each block is always deleted when the program exits(provided that the desturctors are called correctly)
class PoolAllocator
{
public:
	PoolAllocator()
	{
		
	}

	
	~PoolAllocator();
	
	
	template <typename T>
	T* Allocate(size_t count = 1, const std::string& name = "")
	{
		if (count == 0)
		{
			return nullptr;
		}
		
		
		return (T*)Allocate(sizeof(T) * count, name);
		
	}
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
		
		// This doesn't work currently
		// I'm not entirely sure how to make it work
		// it seems like the pointers are different for some reason
		// i've even tried passing the pointer by reference to see if the copy was making it not work
		// it isn't too bad anyway at least the memory is freed automatically on exit
		Block* current = root_;
		while (current)
		{
			// std::cerr << std::hex << (void*)current->data_ << std::dec << "\n";
			// std::cerr << std::hex << (void*)current << std::dec << "\n";
			// std::cerr << std::hex << (void*)*ptr << std::dec << "\n\n\n";

			// finally works all i needed to do was pass the pointer by pointer
			if ((void*)(*ptr) == (void*)(current->data_))
			{
				std::cout << "freed\n";
				current->free_ = true;
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
	
	

private:

	// returns a pointer to a block of memory
	// Q: should this track whether the block is freed or not?
	u8* Allocate(size_t size, const std::string& name = "");
	


	Block* root_{ nullptr };

	
	
};

