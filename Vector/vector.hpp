#pragma once

#include <iterator>
#include "Allocator.hpp"

namespace my {
	//TODO: Использоавть свой аллокатор
	int calledDestructorForN = 0;

	template <typename T>
	class vector {
	public:
		vector() : _capacity(0), _size(0), array(NULL) {};
		vector(vector<T>& src);
		vector(int i);
		~vector();

		class Iterator : public std :: iterator<std :: input_iterator_tag, T>{
		public:
			friend class vector;

			Iterator operator++();
			Iterator operator--();
			Iterator operator++(int);
			Iterator operator--(int);
			T& operator*();

			bool operator!=(const Iterator& rhs);
			bool isValid();
		private:
			T* data;
		};

		T& operator[](int i);
		const T& operator[](int i) const;
		bool operator==(vector<T>& rhs);
		bool operator!=(vector<T>& rhs);
		vector<T> operator=(vector<T>& rhs);

		Iterator begin();
		Iterator end();
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
		T* array1;
		unsigned _capacity;
		unsigned _size;
	};

	template<typename T>
	inline vector<T> :: vector(vector<T>& src) : _capacity(src.capacity()), _size(src.size())
	{
		array = new T[_capacity];

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

	template<typename T>
	inline vector<T> :: vector(int i)
	{
		_capacity = _size = i;
		array = new T[i];
	}

	template<typename T>
	inline vector<T> :: ~vector() 
	{
		delete[] array;
	}

	template<typename T>
	inline typename vector<T> :: Iterator vector<T> :: begin()
	{
		Iterator iterator;
		iterator.data = array;

		return iterator;
	}

	template<typename T>
	inline typename vector<T> :: Iterator vector<T> :: end()
	{
		Iterator iterator;
		iterator.data = array + _size;

		return iterator;
	}

	template<typename T>
	inline typename T& vector<T> :: front()
	{
		return *(begin());
	}

	template<typename T>
	inline typename T& vector<T> :: back()
	{
		return *(--end());
	}

	template<typename T>
	inline void vector<T> :: clear()
	{
		_size = _capacity = 0;
		delete array;
	}

	template<typename T>
	inline T& vector<T> :: operator[](int i)
	{
		return array[i];
	}

	template<typename T>
	inline const T& vector<T> :: operator[](int i) const
	{
		return array[i];
	}

	template<typename T>
	inline bool vector<T> :: operator==(vector<T>& rhs)
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

	template<typename T>
	inline bool vector<T> :: operator!=(vector<T>& rhs)
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline vector<T> vector<T> :: operator=(vector<T>& rhs)
	{
		if (rhs.size() >= _capacity) {
			T* buff = new T[_capacity = rhs.size() * 2];

			int i = 0;
			for (auto it = rhs.begin(); it != rhs.end(); it++, i++) {
				buff[i] = *it;
			}

			delete array;
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

	template<typename T>
	inline void vector<T> :: insert(typename vector<T> :: Iterator& iterator, const T& value)
	{
		T* buff;
		if (_capacity <= ++_size) {
			_capacity = _capacity == 0 ? 1 : _capacity * 2;
		}
		buff = new T[_capacity];

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

		delete array;
		array = buff;

		iterator.data = &(array[j]); //sickening crutch -- тошнотворный костыль
	}

	template<typename T>
	inline void vector<T> :: push_back(T value)
	{
		insert(end(), value);
	}

	template<typename T>
	inline void vector<T> :: reserve(const unsigned i)
	{
		if (i < _size) {
			return;
		}

		T* buff = new T[i];

#ifdef _SCL_SECURE_NO_WARNINGS
		if (array) {
			std :: copy(array, &(array[_size - 1]), buff);

			delete array;
		}
		
		array = buff;
#else
		delete array;

		for (unsigned i = 0; i < _size; i++) {
			buff[i] = array[i];
		}
#endif
		_capacity = i;
	}

	template<typename T>
	inline bool vector<T> :: empty()
	{
		return _size <= 0;
	}

	template<typename T>
	inline unsigned vector<T> :: capacity()
	{
		return _capacity;
	}

	template<typename T>
	inline unsigned vector<T> :: size()
	{
		return _size;
	}

	template<typename T>
	inline typename vector<T> :: Iterator vector<T> :: Iterator :: operator++()
	{
		data++;
		return *this;
	}

	template<typename T>
	inline typename vector<T> :: Iterator vector<T> :: Iterator :: operator--()
	{
		data--;
		return *this;
	}

	template<typename T>
	inline typename vector<T> :: Iterator vector<T> :: Iterator :: operator++(int)
	{
		Iterator old(*this);
		++(*this);
		return old;
	}

	template<typename T>
	inline typename vector<T> :: Iterator vector<T> :: Iterator :: operator--(int)
	{
		Iterator old(*this);
		--(*this);
		return old;
	}

	template<typename T>
	inline T& vector<T> :: Iterator :: operator*()
	{
		return *data;
	}

	template<typename T>
	inline bool vector<T> :: Iterator :: operator!=(const Iterator& rhs)
	{
		return data != rhs.data;
	}

	template<typename T>
	inline bool vector<T> :: Iterator :: isValid()
	{
		return data != 0;
	}
}