#include "MyShared_ptr.h"

MyShared_ptr::MyShared_ptr() noexcept :
	m_Data(nullptr),
	m_Control(nullptr) {}

MyShared_ptr::MyShared_ptr(CObject* ptr) :
	m_Data(ptr),
	m_Control(nullptr) {
	if (m_Data) m_Control = new Control{ 1 };
}

MyShared_ptr::MyShared_ptr(const MyShared_ptr& r) noexcept :
	m_Data(r.m_Data),
	m_Control(r.m_Control) {
	if (m_Control) ++m_Control->counter;
}

MyShared_ptr::MyShared_ptr(MyShared_ptr&& r) noexcept :
	m_Data(r.m_Data),
	m_Control(r.m_Control) {
	r.m_Data = nullptr;
	r.m_Control = nullptr;
}

MyShared_ptr& MyShared_ptr::operator=(const MyShared_ptr& r) noexcept {
	destruct();
	m_Data = r.m_Data;
	m_Control = r.m_Control;
	if (m_Control) ++m_Control->counter;
	return *this;
}

MyShared_ptr& MyShared_ptr::operator=(MyShared_ptr&& r) noexcept {
	destruct();
	m_Data = r.m_Data;
	m_Control = r.m_Control;
	if (m_Control) ++m_Control->counter;
	r.m_Data = nullptr;
	r.m_Control = nullptr;
	return *this;
}

MyShared_ptr::~MyShared_ptr() {
	destruct();
}

void MyShared_ptr::reset(CObject* ptr) {
	if (m_Data == ptr) return;
	destruct();
	m_Data = ptr;
	if (m_Data) m_Control = new Control{ 1 };
}

void MyShared_ptr::swap(MyShared_ptr& r) noexcept {
	std::swap(m_Data, r.m_Data);
	std::swap(m_Control, r.m_Control);
}

void MyShared_ptr::destruct() {
	if (m_Control && m_Control->counter > 1) {
		--m_Control->counter;
	}
	else if (m_Control) {
		delete m_Control;
	}
	if (m_Data) delete m_Data;
}
