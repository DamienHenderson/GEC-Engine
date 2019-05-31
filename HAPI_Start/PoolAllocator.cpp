#include "PoolAllocator.hpp"

PoolAllocator g_allocator(one_gigabyte);

PoolAllocator::~PoolAllocator()
{
	Block* current = root_;
	while (current != nullptr)
	{
		current = current->next_;
		delete root_;
		root_ = current;
	}
	delete[] pool_;
	// free(pool_);
}

void PoolAllocator::MemDump(std::fstream & file)
{
	Block* current = root_;
	while (current != nullptr)
	{
		if (current->name_ != "")
		{
			file.write(current->name_.c_str(), current->name_.length());
		}
		else
		{
			const char* mem_block_str = "Memory Block";
			file.write(mem_block_str, strlen(mem_block_str));
		}

		file.write((char*)current->data_, current->block_size_);
		current = current->next_;
	}
}

void PoolAllocator::MemDump(const std::string & filename)
{
	std::fstream file{ filename,std::ios::out | std::ios::binary };
	if (!file.good())
	{
		assert("Could not open filestream to dump memory!" && false);
		return;
	}
	Block* current = root_;
	while (current != nullptr)
	{
		if (current->name_ != "")
		{
			file.write(current->name_.c_str(), current->name_.length());
		}
		else
		{
			const char* mem_block_str = "Memory Block";
			file.write(mem_block_str, strlen(mem_block_str));
		}

		file.write((char*)current->data_, current->block_size_);
		current = current->next_;
	}
	file.close();
}

void PoolAllocator::LeakCheck(const std::string & filename)
{
	std::fstream file{ filename, std::ios::out };
	if (!file.good())
	{
		assert("Could not open file for leak check" && false);
	}
	Block* current = root_;
	while (current != nullptr)
	{

		file << std::hex << "Memory leak detected!!! block at: " << (void*)current->data_ << " of size " << std::dec << current->block_size_;
		if (current->name_ != "")
		{
			file << " with name: " << current->name_;
		}
		file << " was not freed\n";


		current = current->next_;

	}
	file.close();
}
size_t PoolAllocator::GetAllocatedSize() const
{
	size_t allocated_size{ 0 };
	Block* current = root_;
	while (current)
	{
		allocated_size += current->block_size_;

		current = current->next_;
	}
	return allocated_size;
}
u8* PoolAllocator::Allocate(size_t size, const std::string& name)
{
	
	if (size >= max_block_size)
	{
		assert("Allocating over 1GB at a time is not recommended for performance reasons" && false);
		return nullptr;
	}
	
	if (root_ == nullptr)
	{
		if (size > pool_size_)
		{
			assert("OUT OF POOL MEMORY" && false);
			return nullptr;
		}
		Block* block = new Block(size, name, pool_);
		root_ = block;
		last_ = root_;
		return root_->data_;
	}
	else
	{
		size_t allocated_size{ 0 };
		Block* current = root_;
		while (current->next_ != nullptr)
		{
			allocated_size += current->block_size_;
			
			current = current->next_;
		}
		if ((allocated_size + size) > pool_size_)
		{
			assert("OUT OF POOL MEMORY" && false);
			return nullptr;
		}
		Block* block = new Block(size, name, current->data_ + current->block_size_, current);

		current->next_ = block;
		last_ = block;


		return block->data_;
	}
	return nullptr;


}
