#pragma once
#include "CObject.h"

class MyUnique_ptr {
public:
	MyUnique_ptr() noexcept;
	explicit MyUnique_ptr(CObject* p) noexcept;
	MyUnique_ptr(MyUnique_ptr&& u) noexcept;

	~MyUnique_ptr();
private:
	CObject* m_Data;
};