#pragma once

#include "_base.h"

#define VECTORSTARTLEN (1<<4)	// Initial vector capacity.

/* A lightweight vector class specialized for
	the assembler. It does very little bounds
	checking at the benefit of increased speed.*/
template <class T>
class vector
{
protected:
	T* data;

public:
	int count, capacity;

	vector();
	vector(const int size);
	vector(const T* data, const int size);
	~vector();

	T& operator[](int index);

	T& get(const int index);
	void set(const T& val, const int index);
	void set(const T* val, const int size, const int index);
    inline T* getdata() 
    {
        return data;
    }

	void push(const T& val);
	void push(const T* val, const int size);
	T& pop();
	T& peek();

    void clear();

	void realloc(const int size);
};

template <class T>
vector<T>::vector()
{
	this->capacity = VECTORSTARTLEN;
	this->data = (T*)malloc(VECTORSTARTLEN * sizeof(T));
	this->count = 0;
    memset(this->data, NULL, this->capacity * sizeof(T));
}

template <class T>
vector<T>::vector(const int size)
{
	this->capacity = mallocresize(size);
	this->data = (T*)malloc(this->capacity * sizeof(T));
	this->count = 0;
    memset(this->data, NULL, this->capacity * sizeof(T));
}

template <class T>
vector<T>::vector(const T* data, const int size)
{
	this->capacity = mallocresize(size);
	this->data = (T*)malloc(this->capacity * sizeof(T));
	memcpy(this->data, data, size * sizeof(T));
	this->count = size;
}
	
template <class T>
vector<T>::~vector()
{
	free(this->data);
}

template <class T>
T& vector<T>::operator[](int index)
{
	return this->data[index];
}

template <class T>
T& vector<T>::get(const int index)
{
	if (index >= this->capacity)
		realloc(index + 1);
	if (index >= this->count)
		this->count = index + 1;
	return this->data[index];
}

template <class T>
void vector<T>::set(const T& val, const int index)
{
	if (index >= this->capacity)
		realloc(index + 1);
	if (index >= this->count)
		this->count = index + 1;
	this->data[index] = val;
}

template <class T>
void vector<T>::set(const T* val, const int size, const int index)
{
	const int last = index + size;
	if (last > this->capacity)
		realloc(last);
	if (last > this->count)
		this->count = last;
	memcpy(this->data + index, val, size * sizeof(T));
}

template <class T>
void vector<T>::push(const T& val)
{
	set(val, this->count);
}
	
template <class T>
void vector<T>::push(const T* val, const int size)
{
	set(val, size, this->count);
}
	
template <class T>
T& vector<T>::pop()
{
	return this->data[--this->count];
}
	
template <class T>
T& vector<T>::peek()
{
	return this->data[this->count - 1];
}

template <class T>
void vector<T>::clear()
{
    this->count = 0;
}
	
template <class T>
void vector<T>::realloc(const int size)
{
	if (size > this->capacity)
	{
		this->capacity = mallocresize(size);
		this->data = (T*)::realloc(this->data, this->capacity * sizeof(T));
        memset(this->data + this->count, NULL, (this->capacity - this->count) * sizeof(T));
	}
}