#pragma once

template<typename ArrayClass>
class ArrayIterator
{
public:
	using ValueType = typename ArrayClass::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	ArrayIterator(PointerType ptr)
		: m_Ptr(ptr) {}

	ArrayIterator& operator++()
	{
		m_Ptr++;
		return *this;
	}

	ArrayIterator& operator++(int)
	{
		ArrayIterator other = *this;
		(*this)++;
		return other;
	}

	ArrayIterator& operator--()
	{
		m_Ptr--;
		return *this;
	}

	ArrayIterator& operator--(int)
	{
		ArrayIterator other = *this;
		(*this)--;
		return *this;
	}

	ReferenceType operator[](size_t index)
	{
		return *(m_Ptr + index);
	}

	const ReferenceType operator[](size_t index) const
	{
		return *(m_Ptr + index);
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	ReferenceType operator->()
	{
		return m_Ptr;
	}

	bool operator==(ArrayIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(ArrayIterator& other) const
	{
		return !(*this == other);
	}

private:
	PointerType m_Ptr = nullptr;
};

template<typename T, size_t N>
class Array
{
public:
	using ValueType = T;
	using Iterator = typename ArrayIterator<Array<T, N>>;

public:
	T& at(size_t index)
	{
		if (index >= N)
		{
			throw std::out_of_range("out of range\n");
		}

		return m_Data[index];
	}

	const T& at(const size_t index) const
	{
		if (index >= N)
		{
			throw std::out_of_range;
		}

		return m_Data[index];
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	const T& operator[](const size_t index) const
	{
		return m_Data[index];
	}

	T& front()
	{
		return m_Data[0];
	}

	const T& front() const
	{
		return m_Data[0];
	}

	T& back()
	{
		return m_Data[N - 1];
	}

	const T& back() const
	{
		return m_Data[N - 1];
	}

	T* data()
	{
		return m_Data;
	}

	const T* data() const
	{
		return m_Data;
	}

	bool empty() const
	{
		return N == 0 ? true : false;
	}

	const size_t size() const
	{
		return N;
	}

	void fill(const T& value)
	{
		for (size_t i = 0; i < N; i++)
		{
			m_Data[i] = value;
		}
	}

	void print() const
	{
		for (size_t i = 0; i < N; i++)
		{
			std::cout << m_Data[i] << ' ';
		}
	}

	std::ostream& print(std::ostream& stream) const
	{
		for (size_t i = 0; i < N; i++)
		{
			stream << m_Data[i] << ' ';
		}
		return stream;
	}

public:
	Array() : m_Data() {}

	Array(T val) { fill(val); }

	Array(std::initializer_list<T> init_list)
	{
		size_t i = 0;
		for (auto& it : init_list)
		{
			m_Data[i] = it;
			i++;
		}
	}

public:
	friend bool operator==(const Array& lhs, const Array& rhs)
	{
		if (lhs->size() != rhs->size())
		{
			return false;
		}

		for (size_t i = 0; i < lhs->size(); i++)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}

		return true;
	}

	friend bool operator!=(const Array& lhs, const Array& rhs)
	{
		if (lhs->size() != rhs->size())
		{
			return true;
		}

		for (size_t i = 0; i < lhs->size(); i++)
		{
			if (lhs[i] != rhs[i])
			{
				return true;
			}
		}

		return false;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Array& other)
	{
		for (size_t i = 0; i < N; i++)
		{
			stream << other.data[i] << ' ';
		}
	}

private:
	T m_Data[N];
};
