
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <new>

/*using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;
using std::bad_alloc;*/

using namespace std;

#ifndef STACK_H
#define STACK_H

template <class T>
class stack{

private:
	T *stackArray;
	int capacity;
	int top;
	int sizeArray;

public:
	stack(int capacity = 10); //Constructor 
	~stack() { delete[] stackArray; }

	void push(T value);
	void pop();
	bool isEmpty() const;

	T& getTop() const;

	int cap() { return capacity; }
	int size(){ return sizeArray; }

};

/************************Stack Implementation********************/

//Constructor 
template<class T>
stack<T>::stack(int capacity)
{
	this->capacity = capacity;
	stackArray = new T[capacity];
	top = 0;
	sizeArray = 0;
}

//Adds value to a stack 
template<class T>
void stack<T>::push(T value)
{
	if (sizeArray == cap())
	{
		T *ptr = new T[cap() * 2];

		for (int i = 0; i < size(); i++)
		{
			ptr[i] = stackArray[i];
		}

		delete[] stackArray;
		stackArray = ptr;
		capacity *= 2;
	}

	stackArray[top] = value;
	top++;
	sizeArray++;

}

//Pop Function; Returns and Removes top element
template <class T>
void stack<T>::pop()
{
	if (!isEmpty())
	{
		top--;

		T * ptr = new T[capacity];

		for (int i = 0; i < size() - 1; i++)
		{
			ptr[i] = stackArray[i];
		}

		delete[] stackArray;
		stackArray = ptr;

		sizeArray--;
	}

}

//Returning top element of stack
template<class T>
T& stack<T>::getTop() const
{
	return stackArray[top - 1];
}

//Checks if the stack is empty
template <class T>
bool stack<T>::isEmpty() const
{
	if (top == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif