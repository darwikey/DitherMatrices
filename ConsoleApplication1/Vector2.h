#pragma once

class IntVector2
{
public:
	/// Construct a zero vector.
	IntVector2() :
		x(0),
		y(0)
	{
	}

	/// Construct from coordinates.
	IntVector2(int x, int y) :
		x(x),
		y(y)
	{
	}

	/// Construct from an int array.
	IntVector2(const int* data) :
		x(data[0]),
		y(data[1])
	{
	}

	/// Copy-construct from another vector.
	IntVector2(const IntVector2& rhs) :
		x(rhs.x),
		y(rhs.y)
	{
	}

	/// Assign from another vector.
	IntVector2& operator =(const IntVector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	/// Test for equality with another vector.
	bool operator ==(const IntVector2& rhs) const { return x == rhs.x && y == rhs.y; }

	/// Test for inequality with another vector.
	bool operator !=(const IntVector2& rhs) const { return x != rhs.x || y != rhs.y; }

	/// Add a vector.
	IntVector2 operator +(const IntVector2& rhs) const { return IntVector2(x + rhs.x, y + rhs.y); }

	/// Return negation.
	IntVector2 operator -() const { return IntVector2(-x, -y); }

	/// Subtract a vector.
	IntVector2 operator -(const IntVector2& rhs) const { return IntVector2(x - rhs.x, y - rhs.y); }

	/// Multiply with a scalar.
	IntVector2 operator *(int rhs) const { return IntVector2(x * rhs, y * rhs); }

	/// Divide by a scalar.
	IntVector2 operator /(int rhs) const { return IntVector2(x / rhs, y / rhs); }

	/// Add-assign a vector.
	IntVector2& operator +=(const IntVector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/// Subtract-assign a vector.
	IntVector2& operator -=(const IntVector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	/// Multiply-assign a scalar.
	IntVector2& operator *=(int rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	/// Divide-assign a scalar.
	IntVector2& operator /=(int rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	/// Return integer data.
	const int* Data() const { return &x; }

	/// Return hash value for HashSet & HashMap.
	unsigned ToHash() const { return (unsigned)x * 31 + (unsigned)y; }

	/// Return length.
	int Length2() const { return (x * x + y * y); }

	/// X coordinate.
	int x;
	/// Y coordinate.
	int y;
};
