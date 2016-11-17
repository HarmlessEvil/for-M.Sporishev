#define CATCH_CONFIG_MAIN
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>
#include <vector>
#include "include\catch.h"

#include "vector.hpp"
#include "Allocator.hpp"
#include "include\tlsf.h"

#ifndef BENCHMARK
TEST_CASE("block1") {
	class testClass1 {
	public:
		testClass1() : IsCreatedByDefaultConstructor(true) {};
		~testClass1() { my :: calledDestructorForN++; };

		bool IsCreatedByDefaultConstructor;
	};

	class testClass2 {
	public:
		testClass2(int) {};
	};

	my :: vector<int> buff;
	my :: vector<int> buff1(10);

	SECTION("Default constructor") {
		REQUIRE(buff.size() == 0);
		REQUIRE(buff.capacity() == 0);
	}

	SECTION(".at()") {
		REQUIRE_THROWS(int b = buff.at(10));
		buff1[0] = 15;

		REQUIRE(buff1.at(0) == 15);
	}

	SECTION("Default constructor isn't necessary anymore!") {
		my :: vector<testClass2> a(5, 2);
	}

	SECTION(".reserve()") {
		buff.reserve(100);

		REQUIRE(buff.capacity() == 100);

		my :: vector<int> newBuff(15);

		newBuff[4] = 17;
		newBuff.reserve(5);

		REQUIRE(newBuff.capacity() == 15);
		REQUIRE(newBuff[4] == 17);

		newBuff.reserve(50);

		REQUIRE(newBuff[4] == 17);
	}

	SECTION("Default constructor of template class when initializing") {
		my :: vector<testClass1> checkOnClass1(10);

		REQUIRE(checkOnClass1.size() == 10);
		REQUIRE(checkOnClass1.capacity() == 10);

		bool trueForAll(true);

		for (int i = 0; trueForAll && i < 10; i++) {
			trueForAll = checkOnClass1[i].IsCreatedByDefaultConstructor;
		}

		REQUIRE(trueForAll);
	}

	SECTION("Dectructor when vector is destroyed") {
		REQUIRE(my :: calledDestructorForN == 10);
	}

	SECTION("[] overload") {
		my :: vector<testClass1> checkOnClass1(1);
		REQUIRE(checkOnClass1[0].IsCreatedByDefaultConstructor); 

		buff1[5] = 7;
		REQUIRE(buff1[5] == 7);
	}

	SECTION("== & != overload") {
		my::vector<char> str1(3);
		my::vector<char> str2(3);

		str1[0] = str2[0] = 'a';
		str1[1] = str2[1] = 'b';
		str1[2] = str2[2] = 'c';

		REQUIRE(str1 == str2);

		my::vector<char> str3(str2);

		REQUIRE(str3 == str2);

		str3[2] = 'd';

		REQUIRE(str3 != str2);

		str1.insert(str1.begin(), 'P');

		REQUIRE(str1 != str2);
	}

	SECTION("= overload") {
		my :: vector<char> str(5);
		my :: vector<char> bigStr(100);
		my :: vector<char> emptyStr;
		int i = 0;
		for (auto it = str.begin(); it != str.end(); it++) {
			*it = 'A' + (i % 3);
		}

		bigStr = str;
		REQUIRE(bigStr == str);

		emptyStr = str;
		REQUIRE(emptyStr == str);
	}

	SECTION("Copying constructor") {
		my :: vector<int> buff2(buff1);

		REQUIRE(buff1.size() == buff2.size());
		REQUIRE(buff1.capacity() == buff2.capacity());

		bool trueForAll(true);

		for (unsigned i = 0; i < buff1.size() && trueForAll; i++) {
			trueForAll = buff1[i] == buff2[i];
		}

		REQUIRE(trueForAll);
	}

	SECTION("Iterators") {
		my :: vector<char> str(10);

		for (int i = 0; i < 10; i++) {
			str[i] = 'a' + i;
		}

		str.end() != str.begin();
		(str.begin())++;
		char c = *(++(str.begin()));
		*(str.begin()) = 'd';
		c = *(str.begin());

		str.insert(++str.begin(), 'f');

		std :: copy(str.begin(), str.end(), std :: ostream_iterator<char>(std :: cout, " "));
	}

	SECTION(".empty()") {
		REQUIRE(buff.empty());
		REQUIRE(!buff1.empty());
	}

	SECTION(".front() & .back()") {
		my :: vector<bool> values(1);
		values[0] = true;

		REQUIRE(values.front());

		values[0] = false;

		REQUIRE(!values.back());
	}

	SECTION(".clear()") {
		buff.clear();

		REQUIRE(buff.size() == 0);
		REQUIRE(buff.capacity() == 0);
		REQUIRE(buff.empty());
	}

	SECTION(".push_back()") {
		my :: vector<int> vec;

		vec.push_back(12);
		vec.push_back(24);
		vec.push_back(50);

		my :: vector<int> clone(3);

		clone[0] = 12;
		clone[1] = 24;
		clone[2] = 50;

		REQUIRE(vec == clone);
	}
}

template <typename T>
class allocatorStub {
public:
	allocatorStub() { created = true; };
	
	void destroy(void* p) {};
	void deallocate(void* p, int n) {};

	bool created;
	T data;
};

TEST_CASE("Allocator supprot") {

	class testClass1 {
	public:
		testClass1() : IsCreatedByDefaultConstructor(true) {};
		~testClass1() { my::calledDestructorForN++; };

		bool IsCreatedByDefaultConstructor;
	};

	SECTION("Appears in default constructor of vector") {
		my::vector<int, allocatorStub<int>> def;

		REQUIRE(def.getAllocator()->created);
	}

	SECTION("Supports copying constructor") {
		my :: vector<int> orig(3);
		for (int i = 0; i < 3; i++) {
			orig[i] = i;
		}
		my :: vector<int> copied(orig);

		REQUIRE(orig == copied);
	}

	SECTION("Initializes if amount of elements has been set") {
		my :: vector<testClass1> checkerInitialize(5);

		bool trueForAll(true);

		for (int i = 0; trueForAll && i < 10; i++) {
			trueForAll = checkerInitialize[i].IsCreatedByDefaultConstructor;
		}

		REQUIRE(trueForAll);
	}

	SECTION("Iterators can travese through") {
		my :: vector<int> bridge(15);

		int i = 1;
		for (auto it = bridge.begin(); it != bridge.end(); it++, i++) {
			(*it) = i * 2;
		}
		REQUIRE(bridge[10] == 22);
		REQUIRE(bridge[14] == 30);

		i = 1;
		for (auto it = bridge.end(); it != bridge.begin(); it--, i++) {
			(*it) = i * 2;
		}
		REQUIRE(bridge[10] == 12);
		REQUIRE(bridge[0] == 2);
	}

	SECTION("Vectors equality doesn't depend on it's allocation") {
		my :: vector<int> lhs(50);
		my :: vector<int> rhs(50);

		int i = 0;
		for (auto it = lhs.begin(); it != lhs.end(); it++, i++) {
			(*it) = i;
			rhs[i] = i;
		}

		REQUIRE(lhs == rhs);

		lhs[12] = -1;
		REQUIRE(lhs != rhs);
	}

	SECTION("vector1 = vector2 =/> common adress") {
		my :: vector<char> name(5);
		name[0] = 'S';
		name[1] = 'a';
		name[2] = 's';
		name[3] = 'h';
		name[4] = 'a';

		my :: vector<char> copy = name;

		REQUIRE(name == copy);
		
		name.clear();
		REQUIRE(copy[1] == copy[4]);
	}

	SECTION("vector recognises his borders") {
		my :: vector<int> loong(1);
		loong[0] = 5;

		REQUIRE(loong.back() == loong.front());

		loong.push_back(7);
		REQUIRE(loong.back() != loong.front());
	}

	SECTION("Can not give memory more than CHUNK_SIZE") {
		REQUIRE_THROWS(my::vector<int> tooLong(500));
	}
}
#else

TEST_CASE("Benchmark") {
	time_t begin = time(NULL);
	for (int i = 0; i < 300; i++) {
	my :: Allocator<int> all = my :: Allocator<int>();
	std :: vector<int*> allPool;
	
		for (int i = 0; i < 300; i++) {
			allPool.push_back(all.allocate(300));
		}
		for (int i = 0; i < 200; i++) {
			int* p = allPool.back();
			allPool.pop_back();
			all.deallocate(p, 300);
		}
	}
	time_t end = time(NULL);
	std :: cout << std :: endl << "My allocator. Elapsed time: " << end - begin << std :: endl;

	#define PUL_SIZE 1000 * 1000
	
	// Pool size is in bytes.
	char pool[PUL_SIZE];

	int *ptr[300];
	int i, free_mem;

	begin = time(NULL);
	for (int j = 0; j < 300; j++) {
		free_mem = init_memory_pool(PUL_SIZE, pool);
		//printf("Total free memory= %d\n", free_mem);
		for (i = 0; i < 300; i++)
			if (!(ptr[i] = (int *)malloc_ex(300, pool))) {
				printf("Error\n");
				exit(-1);
			}
		for (i = 0; i < 200; i++)
			free_ex(ptr[i], pool);

		destroy_memory_pool(pool);
	}
	end = time(NULL);
	std :: cout << std :: endl << "TLSF allocator. Elapsed time: " << end - begin << std :: endl;
	printf("Test OK\n");
	system("pause");
}
#endif
