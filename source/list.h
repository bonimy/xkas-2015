#pragma once

#include "_base.h"

#define LISTSTARTLEN (1<<4)

template<class T>
class list
{
protected:
	T **data;

public:
	int count, capacity;

	list();
	list(const int size);
	~list();

	T *get(const int index);
	T *get();
	void listalloc(const int size);

	const T *operator[] (int index) { return this->data[index]; }
};

template<class T>
list<T>::list()
{
	this->data = (T**)malloc(LISTSTARTLEN * sizeof(T*));
	this->capacity = this->count = LISTSTARTLEN;
	while (this->count)
		this->data[--this->count] = new T();
}

template<class T>
list<T>::list(const int size)
{
	this->data = (T**)malloc(size * sizeof(T*));
	this->capacity = this->count = size;
	while (this->count)
		this->data[--this->count] = new T();
}

template<class T>
list<T>::~list()
{
	while (this->capacity)
		delete this->data[--this->capacity];
	free(this->data);
}
	
template<class T>
T *list<T>::get(const int index)
{
	if (index >= this->capacity)
		listalloc(index + 1);
	if (index >= this->count)
		this->count = index + 1;
	return this->data[index];
}

template<class T>
T *list<T>::get()
{
	return get(this->count);
}

template<class T>
void list<T>::listalloc(const int size)
{
	const int x = mallocresize(size);
	this->data = (T**)realloc(this->data, x * sizeof(T*));
	do this->data[this->capacity] = new T();
	while (++this->capacity < x);
}