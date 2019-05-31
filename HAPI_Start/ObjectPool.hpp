#pragma once

#include <HAPI_lib.h>

template <typename T>
struct FreeListNode
{
	FreeListNode(T* ptr, size_t count = 1, FreeListNode<T>* prev = nullptr, FreeListNode<T>* next = nullptr) : data_(ptr), count_(count), prev_(prev), next_(next)
	{

	}
	~FreeListNode()
	{

	}
	T* data_{ nullptr };
	size_t count_{ 1 };
	FreeListNode<T>* prev_{ nullptr };
	FreeListNode<T>* next_{ nullptr };
};

template <typename T>
class ObjectPool
{
public:
	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;
	typedef T* pointer_type;
	typedef const T* const_pointer_type;

	typedef  FreeListNode<T> node_type;

	ObjectPool(size_t count = 1) : count_(count)
	{
		if (count == 1)
		{
			pool_ = new T;
		}
		else
		{
			pool_ = new T[count];
		}
		
		
	}
	~ObjectPool()
	{
		node_type* current = root_;
		while (current != nullptr)
		{
			current = current->next_;
			delete root_;
			root_ = current;
		}
		if (count_ > 1)
		{
			delete[] pool_;
		}
		else
		{
			delete pool_;
		}
		
	}
	
	pointer_type GetObject(size_t count = 1)
	{
		if (count > count_)
		{
			assert("Out of pool objects" && false);
			return nullptr;
		}
		if (root_ == nullptr)
		{
			root_ = new FreeListNode<T>(pool_, count, nullptr, nullptr);
			
			return root_->data_;
		}
		node_type* current = root_;
		size_t allocated_count{ 0 };
		while (current->next_ != nullptr)
		{
			allocated_count += current->count_;
			current = current->next_;
		}
		if ((allocated_count + count) > count_)
		{
			assert("Out of pool objects" && false);
			return nullptr;
		}
		current->next_ = new node_type(current->data_ + current->count_, count, current, nullptr);
		
		return current->next_->data_;
	}
private:
	T* pool_{ nullptr };
	FreeListNode<T>* root_;
	
	size_t count_;
};

// The count variable is only taken into account the first time this function is called for each unique template argument
// Subsequent calls will ignore the count variable 
template <typename T>
ObjectPool<T>& GetPool(size_t count = 100)
{
	static ObjectPool<T> pool(count);
	return pool;
}
