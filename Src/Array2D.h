#pragma once


template <class T> struct Array2DIterator
{
	/// Construct.
	Array2DIterator() :
		mPtr(nullptr)
	{
	}

	/// Construct with an object pointer.
	explicit Array2DIterator(T* ptr) :
		mPtr(ptr)
	{
	}

	/// Point to the object.
	T* operator ->() const { return mPtr; }

	/// Dereference the object.
	T& operator *() const { return *mPtr; }

	/// Preincrement the pointer.
	Array2DIterator<T>& operator ++()
	{
		++mPtr;
		return *this;
	}

	/// Predecrement the pointer.
	Array2DIterator<T>& operator --()
	{
		--mPtr;
		return *this;
	}

	/// Add an offset to the pointer.
	Array2DIterator<T>& operator +=(int value)
	{
		mPtr += value;
		return *this;
	}

	/// Subtract an offset from the pointer.
	Array2DIterator<T>& operator -=(int value)
	{
		mPtr -= value;
		return *this;
	}

	/// Add an offset to the pointer.
	Array2DIterator<T> operator +(int value) const { return Array2DIterator<T>(mPtr + value); }

	/// Subtract an offset from the pointer.
	Array2DIterator<T> operator -(int value) const { return Array2DIterator<T>(mPtr - value); }

	/// Calculate offset to another iterator.
	int operator -(const Array2DIterator& rhs) const { return (int)(mPtr - rhs.mPtr); }

	/// Test for equality with another iterator.
	bool operator ==(const Array2DIterator& rhs) const { return mPtr == rhs.mPtr; }

	/// Test for inequality with another iterator.
	bool operator !=(const Array2DIterator& rhs) const { return mPtr != rhs.mPtr; }

	/// Test for less than with another iterator.
	bool operator <(const Array2DIterator& rhs) const { return mPtr < rhs.mPtr; }

	/// Test for greater than with another iterator.
	bool operator >(const Array2DIterator& rhs) const { return mPtr > rhs.mPtr; }

	/// Test for less than or equal with another iterator.
	bool operator <=(const Array2DIterator& rhs) const { return mPtr <= rhs.mPtr; }

	/// Test for greater than or equal with another iterator.
	bool operator >=(const Array2DIterator& rhs) const { return mPtr >= rhs.mPtr; }

	/// Pointer.
	T* mPtr;
};

/// Random access const iterator.
template <class T> struct Array2DConstIterator
{
	/// Construct.
	Array2DConstIterator() :
		mPtr(nullptr)
	{
	}

	/// Construct with an object pointer.
	explicit Array2DConstIterator(T* ptr) :
		mPtr(ptr)
	{
	}

	/// Construct from a non-const iterator.
	Array2DConstIterator(const Array2DIterator<T>& rhs) :
		mPtr(rhs.mPtr)
	{
	}

	/// Assign from a non-const iterator.
	Array2DConstIterator<T>& operator =(const Array2DIterator<T>& rhs)
	{
		mPtr = rhs.mPtr;
		return *this;
	}

	/// Point to the object.
	const T* operator ->() const { return mPtr; }

	/// Dereference the object.
	const T& operator *() const { return *mPtr; }

	/// Preincrement the pointer.
	Array2DConstIterator<T>& operator ++()
	{
		++mPtr;
		return *this;
	}

	/// Predecrement the pointer.
	Array2DConstIterator<T>& operator --()
	{
		--mPtr;
		return *this;
	}

	/// Add an offset to the pointer.
	Array2DConstIterator<T>& operator +=(int value)
	{
		mPtr += value;
		return *this;
	}

	/// Subtract an offset from the pointer.
	Array2DConstIterator<T>& operator -=(int value)
	{
		mPtr -= value;
		return *this;
	}

	/// Add an offset to the pointer.
	Array2DConstIterator<T> operator +(int value) const { return Array2DConstIterator<T>(mPtr + value); }

	/// Subtract an offset from the pointer.
	Array2DConstIterator<T> operator -(int value) const { return Array2DConstIterator<T>(mPtr - value); }

	/// Calculate offset to another iterator.
	int operator -(const Array2DConstIterator& rhs) const { return (int)(mPtr - rhs.mPtr); }

	/// Test for equality with another iterator.
	bool operator ==(const Array2DConstIterator& rhs) const { return mPtr == rhs.mPtr; }

	/// Test for inequality with another iterator.
	bool operator !=(const Array2DConstIterator& rhs) const { return mPtr != rhs.mPtr; }

	/// Test for less than with another iterator.
	bool operator <(const Array2DConstIterator& rhs) const { return mPtr < rhs.mPtr; }

	/// Test for greater than with another iterator.
	bool operator >(const Array2DConstIterator& rhs) const { return mPtr > rhs.mPtr; }

	/// Test for less than or equal with another iterator.
	bool operator <=(const Array2DConstIterator& rhs) const { return mPtr <= rhs.mPtr; }

	/// Test for greater than or equal with another iterator.
	bool operator >=(const Array2DConstIterator& rhs) const { return mPtr >= rhs.mPtr; }

	/// Pointer.
	T* mPtr;
};


template <class T>
class Array2D
{
public:
	typedef Array2DIterator<T> Iterator;
	typedef Array2DConstIterator<T> ConstIterator;

	Array2D() {}

	Array2D(unsigned fWidth, unsigned fHeight)
	{
		allocate(fWidth, fHeight);
	}

	Array2D(const Array2D& fSrc) : mWidth(fSrc.mWidth), mHeight(fSrc.mHeight)
	{
		allocate(mWidth, mHeight);
		if (fSrc.mData != nullptr)
		{
			const unsigned _dataLength = mWidth * mHeight * sizeof(T);
			memcpy(mData, fSrc.mData, _dataLength);
		}
	}

	void operator=(const Array2D& fSrc)
	{
		mWidth = fSrc.mWidth;
		mHeight = fSrc.mHeight;
		allocate(mWidth, mHeight);
		
		if (fSrc.mData != nullptr)
		{
			const unsigned _dataLength = mWidth * mHeight * sizeof(T);
			memcpy(mData, fSrc.mData, _dataLength);
		}
	}

	~Array2D()
	{
		delete[] mData;
	}


	void allocate(unsigned fWidth, unsigned fHeight)
	{
		mWidth = fWidth;
		mHeight = fHeight;
		delete[] mData;
		if (mWidth != 0 && mHeight != 0)
		{
			mData = new T[mWidth * mHeight];
		}
		else
		{
			mData = nullptr;
		}
	}
	

	inline T* operator[](unsigned i)
	{
		return (mData + (mHeight * i));
	}

	inline T const*const operator[](unsigned i) const
	{
		return (mData + (mHeight * i));
	}

	inline unsigned getWidth() const
	{
		return mWidth;
	}

	inline unsigned getHeight() const
	{
		return mHeight;
	}


	Iterator begin() { return Iterator(mData); }

	ConstIterator begin() const { return ConstIterator(mData); }

	Iterator end() { return Iterator(mData + mWidth * mHeight); }

	ConstIterator end() const { return ConstIterator(mData + mWidth * mHeight); }


	inline operator bool() const
	{
		return mData != nullptr;
	}

	T* getData() { return mData; }
	const T* getData() const { return mData; }


private:

	unsigned mWidth = 0;
	unsigned mHeight = 0;
	T* mData = nullptr;
};