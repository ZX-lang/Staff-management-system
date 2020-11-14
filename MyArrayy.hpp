#pragma once
#include<iostream>
using namespace std;
template<typename T>
class MyArray {
public:
	MyArray(int capacity)
	{
		this->capacity = capacity;
		this->size = 0;
		this->pAddress = new T[capacity];
	}
	MyArray(const MyArray &arr)
	{
		this->capacity = arr.capacity;
		this->size = arr.size;
		this->pAddress=new T[arr.capacity];
		for (int i = 0; i < arr.size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}
	MyArray& operator=(const MyArray& arr)
	{
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->capacity = 0;
			this->size = 0;
		}
		this->capacity = arr.capacity;
		this->size = size;
		this->pAddress= new T[capacity];
		for (int i = 0; i < this->size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}
	void push_back(const T &val)
	{
		if(this->capacity == this->size)
		{
			return;
		}
		this->pAddress[this->size] = val;
		this->size++;
	}
	void pop_back()
	{
		if (this->size == 0)
		{
			return;
		}
		this->size--;
	}
	T& operator[](int index)
	{
		return this->pAddress[index];
	}
	int getCapacity()
	{
		return this->capacity;
	}
	int getSize()
	{
		return this->size;
	}
	~MyArray()
	{
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->capacity = NULL;

		}
	}
private:
	T *pAddress;
	int capacity;
	int size;

};