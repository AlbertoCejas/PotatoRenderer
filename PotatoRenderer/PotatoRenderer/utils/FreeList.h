#ifndef _FREE_LIST_H_
#define _FREE_LIST_H_

#include <cstdlib>
#include <atomic>

template<typename T>
class FreeList
{
  public:

	FreeList(size_t _maxNumOfElements);
	~FreeList();

	T* get();
	void free(T& elementToFree);

  private:

	void* memoryOrigin;
	std::atomic<FreeList<T>*> next;
};

template<typename T>
FreeList<T>::FreeList(size_t _maxNumOfElements)
{
	union
	{
		void* as_void;
		char* as_char;
		FreeList<T>* as_self;
	};

	memoryOrigin = malloc(sizeof(T) * _maxNumOfElements);
	as_self = (FreeList<T>*) memoryOrigin;

	next.store(as_self, std::memory_order_release);

	size_t elementSize = sizeof(T) * 8;
	as_char += elementSize;

	FreeList<T>* runner = next.load(std::memory_order::memory_order_acquire); // as_self is pointing to #2, next is pointing to #1 -> runner #1

	for (size_t i = 1u; i < _maxNumOfElements; i++)
	{
		runner->next.store(as_self, std::memory_order::memory_order_release);
		runner = as_self;
		as_char += elementSize;
	}

	runner->next.store(nullptr, std::memory_order::memory_order_release);
}

template<typename T>
FreeList<T>::~FreeList()
{
	std::free(memoryOrigin);
}

template<typename T>
T* FreeList<T>::get() // Lock-free
{
	FreeList<T>* nextRaw = nullptr;

	do
	{
		nextRaw = next.load(std::memory_order_acquire);

		if (nextRaw == nullptr)
		{
			return nullptr;
		}
	}
	while (!next.compare_exchange_strong(nextRaw, nextRaw->next, std::memory_order_acq_rel));

	return (T*)nextRaw;
}

template<typename T>
void FreeList<T>::free(T& elementToFree) // lock free
{
	FreeList<T>* newHeadRaw = (FreeList<T>*) &elementToFree;
	FreeList<T>* oldHeadRaw = nullptr;

	do
	{
		oldHeadRaw = next.load(std::memory_order_acquire);
		newHeadRaw->next.store(oldHeadRaw);
	}
	while (next.compare_exchange_strong(oldHeadRaw, newHeadRaw, std::memory_order_acq_rel));
}

#endif