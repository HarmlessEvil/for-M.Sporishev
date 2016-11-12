#pragma once

#define POOL_SIZE 255
#define CHUNK_SIZE 10000

namespace my {

	template<typename T>
	class Allocator {
	public:
		typedef size_t	  size_type;
		typedef ptrdiff_t difference_type;
		typedef T*		  pointer;
		typedef const T*  const_pointer;
		typedef T&		  reference;
		typedef const T&  const_reference;
		typedef T		  value_type;

		Allocator();

		pointer allocate(size_type countObjects, const void* hint = 0);
		void deallocate(pointer p, size_type countObjects);

		template <class U, class... Args>
			void construct(U *p, Args&& ...args);

		template <class U>
			void destroy(U *p);

	private:
		struct Chunk {
			struct MemControlBlock {
				MemControlBlock() : available(true), size(0) {};

				bool available : 1;
				size_t size :    31;
				unsigned char*   data;
			};

			void Init(size_t block_size, unsigned int blocks);
			void* Allocate(size_t blockSize);

			bool isHaving(void* ptr);

			MemControlBlock* controls;
			unsigned char*   pData;
			unsigned int     firstAvailableBlock;
			unsigned int     blocksAvailable;
		};

		Chunk pool[POOL_SIZE];
		unsigned char lastAllocChunk;
		unsigned char lastDeallocChunk;
	};

	//Also, for testing
	template<typename T>
	inline Allocator<T> :: Allocator() : lastAllocChunk(0), lastDeallocChunk(0)
	{
		for (int i = 0; i < POOL_SIZE; pool[i++].Init(sizeof(T), CHUNK_SIZE));

		T* a = static_cast<T*>(pool[0].Allocate(150));
	}

	template<typename T>
	inline T* Allocator<T> :: allocate(size_type countObjects, const void* hint)
	{
		if (pool[lastAllocChunk].blocksAvailable < countObjects) {

			int i;
			for (i = 0; i < POOL_SIZE; i++) {
				if (pool[i].blocksAvailable >= countObjects) {
					lastAllocChunk = i;
					break;
				}
			}

			if ((i == POOL_SIZE) || (pool[i].blocksAvailable < countObjects)) {
				throw "Out of memory.";
			}

			return static_cast<T*>(pool[i].Allocate(countObjects));
		}
		else {
			return static_cast<T*>(pool[lastAllocChunk].Allocate(countObjects));
		}
	}

	template<typename T>
	inline void Allocator<T> :: deallocate(pointer p, size_type countObjects)
	{
		if (!pool[lastDeallocChunk].isHaving(p)) {

			int i, j;
			for (i = 0; i < POOL_SIZE && !pool[i].isHaving(p); i++);
			lastDeallocChunk = i;
			for (j = 0; j < CHUNK_SIZE && (void*)pool[i].controls[j].data != (void*)p;) {
				j += pool[i].controls[j].available ? 1 : pool[i].controls[j].size;
			}

			pool[i].controls[j].available = true;
			if (pool[i].firstAvailableBlock - countObjects == j) {
				pool[i].firstAvailableBlock -= (unsigned char)countObjects;
				while (pool[i].controls[pool[i].firstAvailableBlock].available && pool[i].firstAvailableBlock > 0) {
					pool[i].firstAvailableBlock--;
				}
				pool[i].firstAvailableBlock = pool[i].controls[pool[i].firstAvailableBlock].available ? 0 : (unsigned char)pool[i].controls[pool[i].firstAvailableBlock].size;
				pool[i].blocksAvailable = CHUNK_SIZE - pool[i].firstAvailableBlock;
			}
		}
		else {
			int j;
			for (j = 0; j < CHUNK_SIZE && (void*)pool[lastAllocChunk].controls[j].data != (void*)p;) {
				j += pool[lastDeallocChunk].controls[j].available ? 1 : pool[lastAllocChunk].controls[j].size;
			}

			pool[lastDeallocChunk].controls[j].available = true;
			if (pool[lastDeallocChunk].firstAvailableBlock - countObjects == j) {
				pool[lastDeallocChunk].firstAvailableBlock -= (unsigned char)countObjects;
				while (pool[lastDeallocChunk].controls[pool[lastDeallocChunk].firstAvailableBlock].available && pool[lastDeallocChunk].firstAvailableBlock > 0) {
					pool[lastDeallocChunk].firstAvailableBlock--;
				}
				pool[lastDeallocChunk].firstAvailableBlock = pool[lastDeallocChunk].controls[pool[lastDeallocChunk].firstAvailableBlock].available ? 0 : (unsigned char)pool[lastDeallocChunk].controls[pool[lastDeallocChunk].firstAvailableBlock].size;
				pool[lastDeallocChunk].blocksAvailable = CHUNK_SIZE - pool[lastDeallocChunk].firstAvailableBlock;
			}
		}
	}

	template <typename T>
	template<class U, class ...Args>
	inline void Allocator<T> :: construct(U* p, Args&& ...args)
	{
		if (!pool[lastAllocChunk].isHaving(p)) {
		
			int i, j;
			for (i = 0; i < POOL_SIZE && !pool[i].isHaving(p); i++);
			for (j = 0; j < CHUNK_SIZE && (void*)pool[i].controls[j].data != (void*)p;) {
				j += pool[i].controls[j].available ? 1 : pool[i].controls[j].size;
			}

			for (unsigned int k = 0; k < pool[i].controls[j].size; k++) {
				new(p + k) U(std :: forward<Args>(args)...);
			}
		}
		else {
			int j;
			for (j = 0; j < CHUNK_SIZE && (void*)pool[lastAllocChunk].controls[j].data != (void*)p;) {
				j += pool[lastAllocChunk].controls[j].available ? 1 : pool[lastAllocChunk].controls[j].size;
			}

			for (unsigned int k = 0; k < pool[lastAllocChunk].controls[j].size; k++) {
				new(p + k) U(std :: forward<Args>(args)...);
			}
		}
	}

	template<typename T>
	template<class U>
	inline void Allocator<T> :: destroy(U* p)
	{
		if (!pool[lastAllocChunk].isHaving(p)) {

			int i, j;
			for (i = 0; i < POOL_SIZE && !pool[i].isHaving(p); i++);
			for (j = 0; j < CHUNK_SIZE && (void*)pool[i].controls[j].data != (void*)p;) {
				j += pool[i].controls[j].available ? 1 : pool[i].controls[j].size;
			}

			for (unsigned int k = 0; k < pool[i].controls[j].size; k++) {
				(p + k)->~U();
			}
		}
		else {
			int j;
			for (j = 0; j < CHUNK_SIZE && (void*)pool[lastAllocChunk].controls[j].data != (void*)p;) {
				j += pool[lastAllocChunk].controls[j].available ? 1 : pool[lastAllocChunk].controls[j].size;
			}

			for (unsigned int k = 0; k < pool[lastAllocChunk].controls[j].size; k++) {
				(p + k)->~U();
			}
		}
	}

	template<typename T>
	inline void Allocator<T> :: Chunk :: Init(size_t block_size, unsigned int blocks)
	{
		pData = new unsigned char[block_size * blocks];
		controls = new MemControlBlock[blocks];
		firstAvailableBlock = 0;
		blocksAvailable = blocks;
	}

	template<typename T>
	inline void* Allocator<T> :: Chunk :: Allocate(size_t blockSize)
	{
		if (blocksAvailable < blockSize) {
			return NULL;
		}

		unsigned char* pResult = pData + (firstAvailableBlock * sizeof(T));
		controls[firstAvailableBlock].available = false;
		controls[firstAvailableBlock].size = blockSize;
		controls[firstAvailableBlock].data = pResult;
		firstAvailableBlock += (unsigned char)blockSize;
		blocksAvailable -= (unsigned char)blockSize;
		return pResult;
	}

	template<typename T>
	inline bool Allocator<T> :: Chunk :: isHaving(void* ptr)
	{
		return ((ptr >= pData) && (ptr < pData + CHUNK_SIZE * sizeof(T)));
	}
}