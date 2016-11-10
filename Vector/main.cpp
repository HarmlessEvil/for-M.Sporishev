#define CATCH_CONFIG_MAIN
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "include\catch.h"

#include "vector.hpp"

TEST_CASE("block1") {
	class testClass1 {
	public:
		testClass1() : IsCreatedByDefaultConstructor(true) {};
		~testClass1() { my :: calledDestructorForN++; };

		bool IsCreatedByDefaultConstructor;
	};

	my :: vector<int> buff;
	my :: vector<int> buff1(10);

	SECTION("Default constructor") {
		REQUIRE(buff.size() == 0);
		REQUIRE(buff.capacity() == 0);
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