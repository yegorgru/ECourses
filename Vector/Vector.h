#pragma once
#include <memory>
#include <iterator>
#include <stdexcept>

template <typename T>
class Vector {
public:
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reference = T&;
	using const_reference = const T&;

	//constructors / destructor
	Vector();
	explicit Vector(size_t count, const T& value = T());
	template<class InputIt>
	Vector(InputIt first, InputIt last);
	Vector(const Vector& other);
	Vector(Vector&& other) noexcept;
	Vector(std::initializer_list<T> init);

	~Vector();

	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other) noexcept;
	Vector& operator=(std::initializer_list<T> ilist);

	void assign(size_t count, const T& value);

	//element access
	reference at(size_t pos);
	const_reference at(size_t pos) const;
	reference operator[](size_t pos);
	const_reference operator[](size_t pos) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	T* data() noexcept;
	const T* data() const noexcept;

	//iterators
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	iterator end() noexcept;
	const_iterator end() const noexcept;
	reverse_iterator rbegin() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator rend() const noexcept;

	//capacity
	bool empty() const noexcept;
	size_t size() const noexcept;
	void reserve(size_t new_cap);
	size_t capacity() const noexcept;
	void shrink_to_fit();

	//modifiers
	void clear();
	iterator insert(iterator pos, const T& value);
	iterator insert(iterator pos, T&& value);
	iterator insert(iterator pos, size_t count, const T& value);
	template <class InputIt>
	iterator insert(iterator pos, InputIt first, InputIt last);
	iterator insert(iterator pos, std::initializer_list<T> ilist);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
	void push_back(const T& value);
	void push_back(T&& value);
	void pop_back();
	void resize(size_t count);
	void resize(size_t count, const T& value);
	void swap(Vector<T>& other) noexcept;
private:
	void reallocate_data(size_t new_cap);

	T* m_Data;
	size_t m_Size;
	size_t m_Capacity;
};

template<typename T>
Vector<T>::Vector()
{
	m_Data = new T[8];
	m_Capacity = 8;
	m_Size = 0;
}

template<typename T>
Vector<T>::Vector(size_t count, const T& value)
{
	m_Data = new T[count + 8];
	for (size_t i = 0; i < count; ++i) {
		m_Data[i] = value;
	}
	m_Capacity = count+8;
	m_Size = count;
}


template<typename T>
template<class InputIt>
Vector<T>::Vector(InputIt first, InputIt last)
{
	size_t distance = std::distance(first, last);
	m_Data = new T[distance + 8];
	size_t i = 0;
	for (auto it = first; it < last; ++it) {
		m_Data[i++] = *it;
	}
	m_Capacity = distance + 8;
	m_Size = distance;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	m_Data = new T[other.m_Size + 8];
	size_t i = 0;
	for (const auto& obj : other) {
		m_Data[i++] = obj;
	}
	m_Capacity = other.m_Size + 8;
	m_Size = other.m_Size;
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
	this->m_Data = other.m_Data;
	this->m_Size = other.m_Size;
	this->m_Capacity = other.m_Capacity;
	other.m_Data = new T[8];
	other.m_Size = 0;
	other.m_Capacity = 8;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init)
{
	m_Size = init.size();
	m_Capacity = m_Size + 8;
	m_Data = new T[m_Size + 8];
	size_t i = 0;
	for (const auto& obj : init) {
		m_Data[i++] = obj;
	}
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] m_Data;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	size_t i = 0;
	reserve(other.m_Size);
	for (const auto& obj : other) {
		m_Data[i++] = obj;
	}
	m_Size = other.m_Size;
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
	this->m_Data = other.m_Data;
	this->m_Size = other.m_Size;
	this->m_Capacity = other.m_Capacity;
	other.m_Data = new T[8];
	other.m_Size = 0;
	other.m_Capacity = 8;
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> ilist)
{
	m_Size = ilist.size();
	m_Capacity = m_Size;
	m_Data = new T[m_Size];
	size_t i = 0;
	for (const T& obj : ilist) {
		m_Data[i++] = obj;
	}
	return *this;
}

template<typename T>
void Vector<T>::assign(size_t count, const T& value)
{
	delete[] m_Data;
	m_Data = new T[count+8];
	m_Capacity = count + 8;
	for (size_t i = 0; i < count; ++i) {
		m_Data[i] = value;
	}
	m_Size = count;
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_t pos)
{
	if (pos < m_Size) {
		return m_Data[pos];
	}
	throw std::out_of_range("");
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_t pos) const
{
	if (pos < m_Size) {
		return m_Data[pos];
	}
	throw std::out_of_range("");
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_t pos)
{
	return m_Data[pos];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_t pos) const
{
	return m_Data[pos];
}

template<typename T>
typename Vector<T>::reference Vector<T>::front()
{
	return *m_Data;
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const
{
	return *m_Data;
}

template<typename T>
typename Vector<T>::reference Vector<T>::back()
{
	return m_Data[m_Size - 1];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const
{
	return m_Data[m_Size - 1];
}

template<typename T>
T* Vector<T>::data() noexcept
{
	return m_Data;
}

template<typename T>
const T* Vector<T>::data() const noexcept
{
	return m_Data;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept
{
	return m_Data;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept
{
	return m_Data;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept
{
	return m_Data + m_Size;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept
{
	return m_Data + m_Size;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
{
	return std::make_reverse_iterator(m_Data + m_Size);
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const noexcept
{
	return std::make_reverse_iterator(m_Data + m_Size);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
{
	return std::make_reverse_iterator(m_Data);
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const noexcept
{
	return std::make_reverse_iterator(m_Data);
}

template<typename T>
bool Vector<T>::empty() const noexcept
{
	return m_Size == 0;
}

template<typename T>
size_t Vector<T>::size() const noexcept
{
	return m_Size;
}

template<typename T>
void Vector<T>::reserve(size_t new_cap)
{
	if (new_cap > m_Capacity) {
		reallocate_data(new_cap);
		m_Capacity = new_cap;
	}
}

template<typename T>
size_t Vector<T>::capacity() const noexcept
{
	return m_Capacity;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	if (m_Capacity > m_Size) {
		reallocate_data(m_Size);
		m_Capacity = m_Size;
	}
}

template<typename T>
void Vector<T>::clear()
{
	delete[] m_Data;
	m_Data = new T[m_Capacity];
	m_Size = 0;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T& value)
{
	size_t save_distance = pos - m_Data;
	if (m_Size == m_Capacity) {
		reserve(m_Capacity * 2+1);
	}
	for (iterator it = end(); it > m_Data + save_distance; --it) {
		*it = *std::prev(it);
	}
	*(m_Data + save_distance) = value;
	++m_Size;
	return m_Data + save_distance;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, T&& value)
{
	size_t save_distance = pos - m_Data;
	if (m_Size == m_Capacity) {
		reserve(m_Capacity * 2 + 1);
	}
	for (iterator it = end(); it > m_Data + save_distance; --it) {
		*it = *std::prev(it);
	}
	*(m_Data + save_distance) = std::move(value);
	++m_Size;
	return m_Data + save_distance;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, size_t count, const T& value)
{
	size_t save_distance = pos - m_Data;
	if (m_Capacity < m_Size + count) {
		reserve(std::max(m_Capacity * 2, m_Size+count));
	}
	iterator it = end() + count - 1;
	for (iterator copy_it = end()-1; copy_it >= m_Data + save_distance; --it, --copy_it) {
		*it = *copy_it;
	}
	while (it >= m_Data + save_distance) {
		*it-- = value;
	}
	m_Size+=count;
	return m_Data + save_distance;
}

template<typename T>
template<class InputIt>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, InputIt first, InputIt last)
{
	size_t save_distance = pos - m_Data;
	size_t distance = std::distance(first, last);
	if (m_Capacity < m_Size + distance) {
		reserve(std::max(m_Capacity * 2, m_Size + distance));
	}
	iterator it = end() + distance - 1;
	for (iterator copy_it = end() - 1; copy_it >= m_Data + save_distance; --it, --copy_it) {
		*it = *copy_it;
	}
	InputIt cur = last;
	while (it >= m_Data + save_distance) {
		*it-- = *(--cur);
	}
	m_Size += distance;
	return m_Data + save_distance;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, std::initializer_list<T> ilist)
{
	return insert(pos, ilist.begin(), ilist.end());
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos)
{
	for (auto it = pos; it < std::prev(end()); ++it) {
		*it = *std::next(it);
	}
	m_Size = m_Size > 0 ? m_Size-1 : 0;
	return pos;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
{
	iterator copy_it = last;
	for (auto it = first; copy_it < end(); ++it) {
		*it = *copy_it++;
	}
	m_Size = m_Size > (last - first) ? m_Size - (last - first) : 0;
	return first;
}

template<typename T>
void Vector<T>::push_back(const T& value)
{
	insert(end(), value);
}

template<typename T>
void Vector<T>::push_back(T&& value)
{
	if (m_Size == m_Capacity) {
		reserve(m_Capacity * 2 + 1);
	}
	*(m_Data + m_Size) = std::move(value);
	++m_Size;
}

template<typename T>
void Vector<T>::pop_back()
{
	m_Size = m_Size > 0 ? m_Size - 1 : 0;
}

template<typename T>
void Vector<T>::resize(size_t count)
{
	if (count > m_Size) {
		reserve(count);
		for (iterator it = end(); it < begin() + count; ++it) {
			*it = T();
		}
	}
	m_Size = count;
}

template<typename T>
void Vector<T>::resize(size_t count, const T& value)
{
	if (count > m_Size) {
		reserve(count);
		for (iterator it = end(); it < begin() + count; ++it) {
			*it = value;
		}
	}
	m_Size = count;
}

template<typename T>
void Vector<T>::swap(Vector<T>& other) noexcept
{
	std::swap(m_Data, other.m_Data);
	std::swap(m_Capacity, other.m_Capacity);
	std::swap(m_Size, other.m_Size);
}

template<typename T>
void Vector<T>::reallocate_data(size_t new_cap)
{
	T* new_data = new T[new_cap];
	std::move(m_Data, m_Data + m_Size, new_data);
	delete[] m_Data;
	m_Data = new_data;
}

template< class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	for (auto it1 = lhs.begin(), it2 = rhs.begin(); it1 < lhs.end(); ++it1, ++it2) {
		if (*it1 != *it2) return false;
	}
	return true;
}

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
	return !(lhs == rhs);
}

template <class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
	for (auto it1 = lhs.begin(), it2 = rhs.begin(); it1 < lhs.end() && it2 < rhs.end(); ++it1, ++it2) {
		if (*it1 == *it2) continue;
		return *it1 < *it2;
	}
	return lhs.size() < rhs.size();
}

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs){
	return lhs < rhs || lhs == rhs;
}

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
	return rhs < lhs;
}

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
	return lhs > rhs || lhs == rhs;
}