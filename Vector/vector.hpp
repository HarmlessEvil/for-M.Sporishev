#pragma once

#include <iterator>
#include "Allocator.hpp"

namespace my {
	int calledDestructorForN = 0;

	template <typename T, typename alloc = Allocator<T>>
	class vector {
	public:
		vector() : _capacity(0), _size(0), array(NULL), allocator(new alloc) {};
		vector(vector<T>& src);
		template <class... Args>
			vector(int i, Args&& ...args);
		~vector();

		class Iterator : public std :: iterator<std :: random_access_iterator_tag, T>{
		public:
			friend class vector;

			Iterator operator++();
			Iterator operator--();
			Iterator operator++(int);
			Iterator operator--(int);
			T& operator*();
			bool operator<(Iterator&);

			bool operator!=(const Iterator& rhs);
			bool isValid();
		private:
			T* data;
		};
		
		T& operator[](int i);
		const T& operator[](int i) const;
		bool operator==(vector<T>& rhs);
		bool operator!=(vector<T>& rhs);
		vector<T, alloc> operator=(vector<T>& rhs);

		alloc* getAllocator();
		Iterator begin();
		Iterator end();
		T& at(unsigned i);
		T& front();
		T& back();
		void clear();
		void insert(typename vector<T> :: Iterator& iterator, const T& value);
		void push_back(T value);
		void reserve(const unsigned i);
		bool empty();
		unsigned capacity();
		unsigned size();
	private:
		T* array;
		alloc* allocator;
		unsigned _capacity;
		unsigned _size;
	};

	template<typename T, typename alloc>
	inline vector<T, alloc> :: vector(vector<T>& src) : _capacity(src.capacity()), _size(src.size()), allocator(new alloc)
	{
		array = allocator->allocate(_capacity);

#ifdef _SCL_SECURE_NO_WARNINGS
		if (_capacity > 0) {
			std :: copy(&(src[0]), &(src[_size]), array);
		}
#else
		for (unsigned i = 0; i < _size; i++) {
			array[i] = src[i];
		}
#endif
	}

	template<typename T, typename alloc>
	template<class... Args>
	inline vector<T, alloc> :: vector(int i, Args&& ...args) : _capacity(i), _size(i), allocator(new alloc)
	{
		array = allocator->allocate(i);
		allocator->construct(array, std::forward<Args>(args)...);
	}

	template<typename T, typename alloc>
	inline vector<T, alloc> :: ~vector()
	{
		allocator->destroy(array);
		allocator->deallocate(array, _capacity);
	}

	template<typename T, typename alloc>
	inline alloc* vector<T, alloc> :: getAllocator()
	{
		return allocator;
	}

	template<typename T, typename alloc>
	inline typename vector<T, alloc> :: Iterator vector<T, alloc> :: begin()
	{
		Iterator iterator;
		iterator.data = array;

		return iterator;
	}

	template<typename T, typename alloc>
	inline typename vector<T, alloc> :: Iterator vector<T, alloc> :: end()
	{
		Iterator iterator;
		iterator.data = array + _size;

		return iterator;
	}

	template<typename T, typename alloc>
	inline T& vector<T, alloc> ::at(unsigned i)
	{
		if (i >= _size) {
			throw("Wrong index");
		}
		return array[i];
	}

	template<typename T, typename alloc>
	inline typename T& vector<T, alloc> :: front()
	{
		return *(begin());
	}

	template<typename T, typename alloc>
	inline typename T& vector<T, alloc> :: back()
	{
		return *(--end());
	}

	template<typename T, typename alloc>
	inline void vector<T, alloc> :: clear()
	{
		_size = _capacity = 0;
		delete array;
	}

	template<typename T, typename alloc>
	inline T& vector<T, alloc> :: operator[](int i)
	{
		return array[i];
	}

	template<typename T, typename alloc>
	inline const T& vector<T, alloc> :: operator[](int i) const
	{
		return array[i];
	}

	template<typename T, typename alloc>
	inline bool vector<T, alloc> :: operator==(vector<T>& rhs)
	{

		if (_size != rhs.size()) {
			return false;
		}

		bool areEqual(true);

		for (unsigned i = 0; i < _size && areEqual; i++) {
			areEqual = array[i] == rhs[i];
		}

		return areEqual;
	}

	template<typename T, typename alloc>
	inline bool vector<T, alloc> :: operator!=(vector<T>& rhs)
	{
		return !(*this == rhs);
	}

	template<typename T, typename alloc>
	inline vector<T, alloc> vector<T, alloc> :: operator=(vector<T>& rhs)
	{
		unsigned deCapacity = _capacity;
		if (rhs.size() >= _capacity) {
			T* buff = allocator->allocate(_capacity = rhs.size() * 2);

			int i = 0;
			for (auto it = rhs.begin(); it != rhs.end(); it++, i++) {
				buff[i] = *it;
			}

			allocator->deallocate(array, deCapacity);
			array = buff;
		}
		else {
			int i = 0;
			for (auto it = rhs.begin(); it != rhs.end(); it++, i++) {
				array[i] = *it;
			}
		}

		_size = rhs.size();
		return *this;
	}

	template<typename T, typename alloc>
	inline void vector<T, alloc> :: insert(typename vector<T> :: Iterator& iterator, const T& value)
	{
		T* buff;
		unsigned deCapacity = _capacity;
		if (_capacity <= ++_size) {
			_capacity = _capacity == 0 ? 1 : _capacity * 2;
		}
		buff = allocator->allocate(_capacity);

		int i = 0;

		for (auto it = begin(); it != iterator; it++, i++) {
			buff[i] = *it;
		}
		int j = i++;
		buff[j] = value;
		if (iterator.isValid()) {
			for (auto it = iterator; it != end(); it++, i++) {
				buff[i] = *it;
			}
		}

		allocator->deallocate(array, deCapacity);
		array = buff;

		iterator.data = &(array[j]); //sickening crutch -- тошнотворный костыль
	}

	template<typename T, typename alloc>
	inline void vector<T, alloc> :: push_back(T value)
	{
		insert(end(), value);
	}

	template<typename T, typename alloc>
	inline void vector<T, alloc> :: reserve(const unsigned i)
	{
		if (i < _size) {
			return;
		}

		T* buff = allocator->allocate(i);

#ifdef _SCL_SECURE_NO_WARNINGS
		if (array) {
			std :: copy(array, &(array[_size - 1]), buff);

			allocator->destroy(array);
			allocator->deallocate(array, _capacity);
		}
		
		array = buff;
#else
		allocator->destroy(array);
		allocator->deallocate(array, _capacity);

		for (unsigned i = 0; i < _size; i++) {
			buff[i] = array[i];
		}
#endif
		_capacity = i;
	}

	template<typename T, typename alloc>
	inline bool vector<T, alloc> :: empty()
	{
		return _size <= 0;
	}

	template<typename T, typename alloc>
	inline unsigned vector<T, alloc> :: capacity()
	{
		return _capacity;
	}

	template<typename T, typename alloc>
	inline unsigned vector<T, alloc> :: size()
	{
		return _size;
	}

	template<typename T, typename alloc>
	inline typename vector<T, alloc> :: Iterator vector<T, alloc> :: Iterator :: operator++()
	{
		data++;
		return *this;
	}

	template<typename T, typename alloc>
	inline typename vector<T, alloc> :: Iterator vector<T, alloc> :: Iterator :: operator--()
	{
		data--;
		return *this;
	}

	template<typename T, typename alloc>
	inline typename vector<T, alloc> :: Iterator vector<T, alloc> :: Iterator :: operator++(int)
	{
		Iterator old(*this);
		++(*this);
		return old;
	}

	template<typename T, typename alloc>
	inline typename vector<T, alloc> :: Iterator vector<T, alloc> :: Iterator :: operator--(int)
	{
		Iterator old(*this);
		--(*this);
		return old;
	}

	template<typename T, typename alloc>
	inline T& vector<T, alloc> :: Iterator :: operator*()
	{
		return *data;
	}

	template<typename T, typename alloc>
	inline bool vector<T, alloc> :: Iterator :: operator<(Iterator& x)
	{
		return data < x.data;
	}

	template<typename T, typename alloc>
	inline bool vector<T, alloc> :: Iterator :: operator!=(const Iterator& rhs)
	{
		return data != rhs.data;
	}

	template<typename T, typename alloc>
	inline bool vector<T, alloc> :: Iterator :: isValid()
	{
		return data != 0;
	}
}
