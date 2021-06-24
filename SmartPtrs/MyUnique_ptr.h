#pragma once
#include "CObject.h"

class MyUnique_ptr {
public:
	//Constructors, assignment operators, destructor
	MyUnique_ptr() noexcept;
	explicit MyUnique_ptr(CObject* p) noexcept;
	MyUnique_ptr(MyUnique_ptr&& u) noexcept;
	MyUnique_ptr(const MyUnique_ptr& u) = delete;

	MyUnique_ptr& operator=(MyUnique_ptr&& r) noexcept;
	MyUnique_ptr& operator=(MyUnique_ptr& r) = delete;

	~MyUnique_ptr();

	//Modifiers
	CObject* release() noexcept;
	void reset(CObject* p = nullptr) noexcept;
	void swap(MyUnique_ptr& other) noexcept;

	//Observers
	CObject* get() const noexcept;
	explicit operator bool() const noexcept;

	//Operators
	CObject& operator*() const;
	CObject* operator->() const noexcept;
private:
	CObject* m_Data;
};

template<class T, class ...Args>
MyUnique_ptr make_unique(Args && ...args)
{
	auto p = new T(args...);
	return MyUnique_ptr(p);
}

bool operator == (const MyUnique_ptr& p1, const MyUnique_ptr& p2);