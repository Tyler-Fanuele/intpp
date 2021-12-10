#ifndef INT

#define INT
	

#include <iostream>
#include <cassert>
#include <string>
#include <exception>

#define I32_SIZE sizeof(signed int) * 8
using namespace std;

/*
*
*	i32 implimentation and struct
*
*/

struct i32
{
public:
	//constructors
	i32(int iVal)
	{
		value = iVal;
	}

	i32(const i32& pO)
	{
		value = pO.value;
	}

	//equals operators
	i32& operator = (int right)
	{
		*this = i32(right);
		//update_bits();
		return *this;
	}

	int operator = (i32& right)
	{
		return right.value;
	}

	i32& operator = (const i32& right)
	{
		value = right.value;
		return *this;
	}

	//index operator

	int operator [] (int index)const
	{
		if (index >= I32_SIZE || index < 0)
		{
			throw out_of_range("Bit index out of range!");
		}
		return 0 != (value & (1 << index));;
	}

	//addition operators
	i32& operator++()
	{
		(*this).value = value + 1;
		return *this;
	}

	i32 operator++(int)
	{
		i32 temp = *this;
		++* this;
		return *this;
	}

	i32 operator+(const i32& right)
	{
		i32 temp = i32(value + right.value);
		return temp;
	}

	i32 operator+(const int& right)
	{
		i32 temp(value + right);
		return temp;
	}

	i32 operator+=(const i32& right)
	{
		value = value + right.value;
		return *this;
	}

	//subtraction operators
	i32& operator--()
	{
		(*this).value = value - 1;
		return *this;
	}

	i32 operator--(int)
	{
		i32 temp = *this;
		--* this;
		return *this;
	}

	i32 operator-(const i32& right)
	{
		i32 temp = i32(value - right.value);
		return temp;
	}

	i32 operator-(const int& right)
	{
		i32 temp(value - right);
		return *this;
	}

	i32 operator-=(const i32& right)
	{
		value = value - right.value;
		return *this;
	}

	//division overloads
	i32 operator/(const i32& right)
	{
		assert(right.value != 0);
		i32 temp = i32(value / right.value);
		return temp;
	}

	i32 operator/(const int& right)
	{
		if (right == 0)
		{
			throw invalid_argument("Tried to devide by zero");
		}
		i32 temp(value /= right);
		return temp;
	}

	i32 operator/=(const i32& right)
	{
		assert(right.value != 0);
		value = value / right.value;
		return *this;
	}

	//multplication overloads
	i32 operator*(const i32& right)
	{
		i32 temp = i32(value * right.value);
		return temp;
	}

	i32 operator*(const int& right)
	{
		i32 temp(value * right);
		return temp;
	}

	i32 operator*=(const i32& right)
	{
		value = value * right.value;
		return *this;
	}

	//overloading bools
	bool operator > (const i32& pO)
	{
		return value > pO.value;
	}

	bool operator < (const i32& pO)
	{
		return value < pO.value;
	}

	bool operator >= (const i32& pO)
	{
		return !(value < pO.value);
	}

	bool operator <= (const i32& pO)
	{
		return !(value > pO.value);
	}

	bool operator == (const i32& pO)
	{
		return value == pO.value;
	}

	bool operator != (const i32& pO)
	{
		return value != pO.value;
	}

	//bitwise overloads 
	i32 operator&(i32& right)
	{
		i32 temp(value & right.value);
		return temp;
	}
	i32 operator|(i32& right)
	{
		i32 temp(value | right.value);
		return temp;
	}
	i32 operator^(i32& right)
	{
		i32 temp(value ^ right.value);
		return temp;
	}
	i32 operator~()
	{
		value = ~value;
		return *this;
	}
	i32 operator<<(i32& right)
	{
		i32 temp(value << right.value);
		return temp;
	}
	i32 operator>>(i32& right)
	{
		i32 temp(value >> right.value);
		return temp;
	}


	//overloading casting to int
	operator int() const { return value; }


	friend istream& operator >>(istream& in, i32& pO);
	friend ostream& operator <<(ostream& out, i32& pO);

	//print to string functions
	string little_endian()
	{
		string ret;
		for (int i = 0; i < I32_SIZE; i++)
		{
			ret += std::to_string((*this)[i]);
		}
		return ret;
	}

	string big_endian()
	{
		string ret;
		for (int i = I32_SIZE - 1; i >= 0; i--)
		{
			ret += std::to_string((*this)[i]);
		}
		return ret;
	}

	friend int operator+(const int& left, const i32& right);
	friend int operator-(const int& left, const i32& right);

	int size() const
	{
		return I32_SIZE;
	}

	void flip_at(int index)
	{
		if (index >= I32_SIZE || index < 0)
		{
			throw out_of_range("Bit index out of range!");
		}
		value ^= 1UL << index;
	}

	bool check_at(int index)
	{
		if (index >= I32_SIZE || index < 0)
		{
			throw out_of_range("Bit index out of range!");
		}

		return 0 != (value & (1 << index));
		
	}

	void set_at(int index)
	{
		if (index >= I32_SIZE || index < 0)
		{
			throw out_of_range("Bit index out of range!");
		}
		value |= 1UL << index;
	}

	void clear_at(int index)
	{
		if (index >= I32_SIZE || index < 0)
		{
			throw out_of_range("Bit index out of range!");
		}
		value &= ~(1UL << index);

	}

private:
	signed int value;
};



inline int operator+(const int& left, const i32& right)
{
	int ret = left;
	ret += right.value;
	return ret;
}

inline int operator-(const int& left, const i32& right)
{
	int ret = left;
	ret -= right.value;
	return ret;
}

inline istream& operator >>(istream& in, i32& pO)
{
	int v;
	in >> v;
	pO = i32(v);
	return in;
}

inline ostream& operator <<(ostream& out, i32& pO)
{
	out << pO.value;

	return out;
}

#endif
