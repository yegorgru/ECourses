#include "MyUnique_ptr.h"

#include <algorithm>

MyUnique_ptr::MyUnique_ptr() noexcept :
	m_Data(nullptr) {}

MyUnique_ptr::MyUnique_ptr(CObject* p) noexcept :
	m_Data(p) {}

MyUnique_ptr::MyUnique_ptr(MyUnique_ptr&& u) noexcept {
	std::swap(this->m_Data, u.m_Data);
	u.m_Data = nullptr;
}
