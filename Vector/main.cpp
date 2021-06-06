#include "Vector.h"

#include <string>
#include <iostream>
#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("testing ctors and = operators") {
	{
		std::vector<std::string>v{ "a", "b", "c", "d" };
		Vector<std::string>V{ "a", "b", "c", "d" };
		REQUIRE(v.size() == V.size());
		auto vit = v.begin();
		for (auto it = V.begin(); it != V.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		std::vector<std::string>v{ "a", "b", "c", "d" };
		const Vector<std::string>V{ "a", "b", "c", "d" };
		REQUIRE(v.size() == V.size());
		auto vit = v.begin();
		for (auto it = V.begin(); it != V.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		std::vector<std::string>v{ "a", "b", "c", "d" };
		Vector<std::string>V = { "a", "b", "c", "d" };
		REQUIRE(v.size() == V.size());
		auto vit = v.begin();
		for (auto it = V.begin(); it != V.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		Vector<std::string>V(5, "a");
		REQUIRE(5 == V.size());
		for (auto it = V.begin(); it != V.end(); it++) {
			CHECK(*it == "a");
		}
	}
	{
		std::vector<std::string>v{ "a", "b", "c", "d" };
		Vector<std::string>V(v.begin(), v.end());
		REQUIRE(v.size() == V.size());
		auto vit = v.begin();
		for (auto it = V.begin(); it != V.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		Vector<std::string>V{ "a", "b", "c", "d" };
		Vector<std::string>V2(V);
		REQUIRE(V.size() == V2.size());
		auto vit = V2.begin();
		for (auto it = V.begin(); it != V.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		Vector<std::string>V{ "a", "b", "c", "d" };
		Vector<std::string>V2 = V;
		REQUIRE(V.size() == V2.size());
		auto vit = V2.begin();
		for (auto it = V.begin(); it != V.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		std::vector<std::string>v{ "a", "b", "c", "d" };
		Vector<std::string>V(v.begin(), v.end());
		Vector<std::string>V2(std::move(V));
		REQUIRE(V.size() == 0);
		REQUIRE(V.empty());
		REQUIRE(V2.size() == v.size());
		auto vit = v.begin();
		for (auto it = V2.begin(); it != V2.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
	{
		std::vector<std::string>v{ "a", "b", "c", "d" };
		Vector<std::string>V(v.begin(), v.end());
		Vector<std::string>V2 = std::move(V);
		REQUIRE(V.size() == 0);
		REQUIRE(V.empty());
		REQUIRE(V2.size() == v.size());
		auto vit = v.begin();
		for (auto it = V2.begin(); it != V2.end(); it++, vit++) {
			CHECK(*it == *vit);
		}
	}
}

TEST_CASE("testing assign") {
	{
		Vector<int>v;
		REQUIRE(v.size() == 0);
		v.assign(5, 10);
		REQUIRE(v.size() == 5);
		for (auto i : v) {
			CHECK(i == 10);
		}
		v.assign(3, 5);
		REQUIRE(v.size() == 3);
		for (auto i : v) {
			CHECK(i == 5);
		}
		v.assign(20, 30);
		REQUIRE(v.size() == 20);
		for (auto i : v) {
			CHECK(i == 30);
		}
	}
	{
		Vector<std::string> v{"a", "b"};
		v.assign(5, "aba");
		REQUIRE(v.size() == 5);
		for (auto i : v) {
			CHECK(i == "aba");
		}
	}
}

TEST_CASE("testing element access and iterators") {
	{
		Vector<int> v{ 1,2,3,4,5 };
		CHECK(v.front() == 1);
		CHECK(v.back() == 5);
		for (int i = 0; i < 5; i++) {
			CHECK(v[i] == i + 1);
			CHECK(v.at(i) == i + 1);
		}
		CHECK(*v.begin() == v[0]);
		CHECK(*std::prev(v.end()) == v.back());
		CHECK(*(v.begin()+3) == v.at(3));
		CHECK(*v.rbegin() == v.back());
		CHECK(*std::prev(v.rend()) == v.front());
		CHECK(*(v.rbegin() + 3) == v.at(1));
	}
	{
		const Vector<int> v{ 1,2,3,4,5 };
		CHECK(v.front() == 1);
		CHECK(v.back() == 5);
		for (int i = 0; i < 5; i++) {
			CHECK(v[i] == i + 1);
			CHECK(v.at(i) == i + 1);
		}
		CHECK(*v.begin() == v[0]);
		CHECK(*std::prev(v.end()) == v.back());
		CHECK(*(v.begin() + 3) == v.at(3));
		CHECK(*v.rbegin() == v.back());
		CHECK(*std::prev(v.rend()) == v.front());
		CHECK(*(v.rbegin() + 3) == v.at(1));
	}
}

TEST_CASE("testing capacity") {
	Vector<double>v;
	CHECK(v.empty());
	v.push_back(5.5);
	CHECK(!v.empty());
	v.reserve(300);
	CHECK(v.capacity() == 300);
	CHECK(v.size() == 1);
	CHECK(v.front() == 5.5);
	v.pop_back();
	CHECK(v.capacity() == 300);
	CHECK(v.size() == 0);
	v.insert(v.end(), { 1.3, 2.6, 7.6, 5.5 });
	CHECK(v.capacity() == 300);
	CHECK(v.size() == 4);
	v.shrink_to_fit();
	CHECK(v.capacity() == 4);
	CHECK(v.size() == 4);
	v.push_back(10);
	CHECK(v.size() == 5);
}

TEST_CASE("testing modifiers") {
	{
		Vector<std::string>v{"a", "b", "c"};
		v.clear();
		CHECK(v.empty());
		v.push_back("h");
		CHECK(v.size() == 1);
	}
	{
		Vector<std::string>v;
		v.insert(v.end(), "a");
		CHECK(v.size() == 1);
		CHECK(v[0] == "a");
		v.insert(v.begin(), "b");
		CHECK(v.size() == 2);
		CHECK(v == Vector<std::string>{"b", "a"});
		v.insert(v.end(), "c");
		CHECK(v.size() == 3);
		CHECK(v == Vector<std::string>{"b", "a", "c"});
		v.insert(v.end()-2, "d");
		CHECK(v.size() == 4);
		CHECK(v == Vector<std::string>{"b", "d", "a", "c"});
		std::string move_str = "asdfg";
		v.insert(v.end() - 2, std::move(move_str));
		CHECK(v.size() == 5);
		CHECK(v == Vector<std::string>{"b", "d", "asdfg", "a", "c"});
		CHECK(move_str == "");
		v.insert(v.begin(), 3, "ff");
		CHECK(v.size() == 8);
		CHECK(v == Vector<std::string>{"ff", "ff", "ff", "b", "d", "asdfg", "a", "c"});
		v.insert(v.end(), 2, "aa");
		CHECK(v.size() == 10);
		CHECK(v == Vector<std::string>{"ff", "ff", "ff", "b", "d", "asdfg", "a", "c", "aa", "aa"});
		v.insert(v.begin() + 2, 1, "bb");
		CHECK(v.size() == 11);
		CHECK(v == Vector<std::string>{"ff", "ff", "bb", "ff", "b", "d", "asdfg", "a", "c", "aa", "aa"});
		v.erase(v.begin());
		CHECK(v.size() == 10);
		CHECK(v == Vector<std::string>{"ff", "bb", "ff", "b", "d", "asdfg", "a", "c", "aa", "aa"});
		v.erase(v.begin() + 4);
		CHECK(v.size() == 9);
		CHECK(v == Vector<std::string>{"ff", "bb", "ff", "b", "asdfg", "a", "c", "aa", "aa"});
		v.erase(std::prev(v.end()));
		CHECK(v.size() == 8);
		CHECK(v == Vector<std::string>{"ff", "bb", "ff", "b", "asdfg", "a", "c", "aa"});
	}
	{
		Vector<int>V{};
		std::vector<int>v{ 1,2,3,4 };
		V.insert(V.end(), v.begin(), v.end());
		CHECK(V == Vector<int>{1, 2, 3, 4});
		CHECK(v == std::vector<int>{1, 2, 3, 4});
		V.insert(V.end()-2, v.begin(), v.end());
		CHECK(V == Vector<int>{1, 2, 1, 2, 3, 4, 3, 4});
		V.insert(V.begin(), v.begin(), v.end());
		CHECK(V == Vector<int>{1, 2, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4});
		V.insert(V.end(), v.begin(), v.end());
		CHECK(V == Vector<int>{1, 2, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4 });
		V.insert(V.begin(), { 5,6,7,8 });
		CHECK(V == Vector<int>{5, 6, 7, 8, 1, 2, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4 });
		V.insert(V.begin()+6, { 9 });
		CHECK(V == Vector<int>{5, 6, 7, 8, 1, 2, 9, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4 });
		V.insert(V.begin() + 3, { 10, 11 });
		CHECK(V == Vector<int>{5, 6, 7, 10, 11, 8,  1, 2, 9, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4 });
		V.insert(V.end(), { 12, 13, 14 });
		CHECK(V == Vector<int>{5, 6, 7, 10, 11, 8,  1, 2, 9, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 12, 13, 14});
		V.erase(V.begin(), V.begin() + 3);
		CHECK(V.size() == 23);
		CHECK(V == Vector<int>{10, 11, 8, 1, 2, 9, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 12, 13, 14});
		V.erase(V.begin(), V.begin());
		CHECK(V.size() == 23);
		CHECK(V == Vector<int>{10, 11, 8, 1, 2, 9, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 12, 13, 14});
		V.erase(V.end(), V.end());
		CHECK(V.size() == 23);
		CHECK(V == Vector<int>{10, 11, 8, 1, 2, 9, 3, 4, 1, 2, 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 12, 13, 14});
		V.erase(V.begin()+5, V.begin()+15);
		CHECK(V.size() == 13);
		CHECK(V == Vector<int>{10, 11, 8, 1, 2, 4, 1, 2, 3, 4, 12, 13, 14});
		V.erase(V.begin() + 5, V.end());
		CHECK(V.size() == 5);
		CHECK(V == Vector<int>{10, 11, 8, 1, 2});
		V.erase(V.begin(), V.end());
		CHECK(V.size() == 0);
		CHECK(V == Vector<int>{});
	}
	{
		Vector<int>v{ 1,2,3 };
		v.push_back(4);
		CHECK(v == Vector<int>{1, 2, 3, 4});
		v.push_back(5);
		CHECK(v == Vector<int>{1, 2, 3, 4, 5});
		v.pop_back();
		v.pop_back();
		v.pop_back();
		CHECK(v == Vector<int>{1, 2});
		v.pop_back();
		v.pop_back();
		CHECK(v == Vector<int>{});
		v.pop_back();
		CHECK(v == Vector<int>{});
	}
	{
		Vector<std::string>v{ "a", "b" };
		std::string s = "c";
		v.push_back(std::move(s));
		CHECK(v == Vector<std::string>{"a", "b", "c"});
		CHECK(s == "");
	}
	{
		Vector<std::string>v;
		v.resize(5);
		CHECK(v.size() == 5);
		for (auto s : v) {
			CHECK(s == "");
		}
		v.resize(3);
		CHECK(v.size() == 3);
		for (auto s : v) {
			CHECK(s == "");
		}
		v.resize(8, "a");
		CHECK(v.size() == 8);
		for (size_t i = 0; i < 8; i++) {
			if (i < 3) {
				CHECK(v[i] == "");
			}
			else {
				CHECK(v[i] == "a");
			}
		}
		v.resize(4, "a");
		CHECK(v.size() == 4);
		for (size_t i = 0; i < 4; i++) {
			if (i < 3) {
				CHECK(v[i] == "");
			}
			else {
				CHECK(v[i] == "a");
			}
		}
	}
	{
		Vector<int>v1{ 1,2,3,4,5 };
		Vector<int>v2{ 6,7,8,9,10, 11 };
		v1.swap(v2);
		CHECK(v1 == Vector<int>{ 6, 7, 8, 9, 10, 11 });
		CHECK(v2 == Vector<int>{ 1, 2, 3, 4, 5 });
	}
}

int main() {
	doctest::Context context;
	int res = context.run();
	return 0;
}