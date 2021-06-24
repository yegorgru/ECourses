#include "MyShared_ptr.h"

MyShared_ptr::MyShared_ptr() noexcept :
	m_Data(nullptr),
	m_Control(nullptr) {}

MyShared_ptr::MyShared_ptr(CObject* ptr) :
	m_Data(ptr),
	m_Control(new Control{0}) {}

MyShared_ptr::MyShared_ptr(const MyShared_ptr& r) noexcept :
	m_Data(r.m_Data),
	m_Control(r.m_Control) {
	if (m_Control) ++m_Control->counter;
}

MyShared_ptr::MyShared_ptr(MyShared_ptr&& r) noexcept :
	m_Data(r.m_Data),
	m_Control(r.m_Control)
{
	r.m_Data = nullptr;
	r.m_Control = nullptr;
}

MyShared_ptr& MyShared_ptr::operator=(const MyShared_ptr& r) noexcept
{
	m_Data = r.m_Data;
	m_Control = r.m_Control;
	if (m_Control) ++m_Control->counter;
	return *this;
}

MyShared_ptr& MyShared_ptr::operator=(MyShared_ptr&& r) noexcept
{
	m_Data = r.m_Data;
	m_Control = r.m_Control;
	r.m_Data = nullptr;
	r.m_Control = nullptr;
	return *this;
}
