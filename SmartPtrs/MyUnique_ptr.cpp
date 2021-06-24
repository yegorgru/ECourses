#include "MyUnique_ptr.h"

#include <algorithm>

MyUnique_ptr::MyUnique_ptr() noexcept :
	m_Data(nullptr) {}

MyUnique_ptr::MyUnique_ptr(CObject* p) noexcept :
	m_Data(p) {}

MyUnique_ptr::MyUnique_ptr(MyUnique_ptr&& u) noexcept {
	this->m_Data = u.m_Data;
	u.m_Data = nullptr;
}

MyUnique_ptr& MyUnique_ptr::operator=(MyUnique_ptr&& r) noexcept
{
	this->m_Data = r.m_Data;
	r.m_Data = nullptr;
}

MyUnique_ptr::~MyUnique_ptr() {
	if (m_Data) delete m_Data;
	m_Data = nullptr;
}

CObject* MyUnique_ptr::release() noexcept {
	auto p = m_Data;
	m_Data = nullptr;
	return p;
}

void MyUnique_ptr::reset(CObject* p) noexcept {
	if (m_Data) delete m_Data;
	m_Data = p;
}

void MyUnique_ptr::swap(MyUnique_ptr& other) noexcept {
	std::swap(m_Data, other.m_Data);
}

CObject* MyUnique_ptr::get() const noexcept {
	return m_Data;
}
