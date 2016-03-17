/*
Caroline Pattillo (cbp53)
Assignment 0
*/


#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <new>

#include "Stack.h"

using namespace std;
/*
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;
using std::bad_alloc;*/

#ifndef LL_H
#define LL_H

//************************** Node Class ************************************************

template <class T>
class Node
{
public:
	T coef; //Stores the coefficient in polynomial 
	T degree;//Stores degree of polynomial 
	Node<T> *next;//Points to next linked list item
	Node<T> *prev;//Points to previous item in linked list

	//Default constructor 
	//Default parameter for next 
	//Sets info to a T data type and next to ptr
	Node(T, T, Node<T> * nextptr = NULL, Node<T> * prevptr = NULL);

};

//*********************** LL Class **************************************************************

template <class T>
class LL
{

private:

	Node<T> *sentinel;

	int count; //number of items in linked list 

	//Copies Linked Lists
	//Uses Insert_rear method to build new linked list
	void copyList(const LL<T> & listtoCopy);

	//Inserts Node into the list
	void InsertList(Node<T> * &Left, Node<T>* &Right, Node<T>* &Add);

	//Internal method to erase node
	void EraseList(Node<T> *&Left, Node<T>*&Right, Node<T>*&Erase);

	//Bubble Sort
	void BubbleSort(LL<T> myLL, int size);

public:

	//Default Construtor
	//Sets head, tail to NULL and count to 0
	LL();

	//Copy Constructor, calls copylist
	LL(const LL<T> &otherLL);

	//Destructor, destroys dynaimcally created memory (Nodes)
	//Calls the clear method
	~LL();

	//Adds a new Node to the end of the Linked List
	//Updates new list count
	void Insert_rear(T, T);

	//Adds a new Node to the front of the Linked List
	//Updates new list count
	void Insert_front(T, T);

	//Deletes the last Node in the Linked List
	//Removes one from count
	void erase_rear();

	//Deletes all the Nodes in the Linked List
	void clear();

	//Returns the number of elements in the Linked List 
	int size() const;

	//Returns the capacity of the Linked List 
	int cap() const;

	//Returns reference of Object in position ndx of linked list 
	T& at(int ndx);

	//Returns Degree at positon index
	T& atD(int ndx);

	//Overloads the [] operator, returns the T object reference in positon ndx of linked list
	T& operator[](int ndx);

	//Returns reference of Object in position ndx of linked list
	//cannot modify T object
	T& at(int ndx) const;

	//Overloads the [] operator
	//returns the T object reference in positon ndx of linked list
	//Cannot modify T object
	T& operator [] (int ndx) const;

	//Overloading Assignment operator 
	//Returns the LL object 
	const LL<T>& operator=(const LL<T> &);

	//Insert value in index
	void Insert(int index, T val, T val2);

	//Erase node in the linked list
	void erase(int index);

	//Erase Front
	void erase_front();

	//Returns value in front node
	T& front() const;

	//Returns value in rear node
	T& back() const;

	//prints LL
	void print();

	//Overloading the '+' operator
	LL<T> operator+(LL<T> &poly1);

	//get Sentinel pointer
	Node<T> * getSent() const;

	//Overloading the * operator
	LL<T> operator*(LL<T> &poly);

	//Overloading the - operator
	LL<T> operator-(LL<T> &poly);

};



//******************Implementation for Node Class***************************

//Default Constructor 
//Sets info to T object
//Sets next to ptr
template <class T>
Node<T>::Node(T co, T de, Node<T> * nextptr, Node<T> * prevptr)
{
	coef = co;
	degree = de;
	next = nextptr;
	prev = prevptr;
}

//*****************Implementation for LL class*******************

//Default Constructor
//Sets count to 0
//Sets head and tail to NULL
template <class T>
LL<T>::LL()
{
	sentinel = new Node<T>(0, 0, sentinel, sentinel);

	count = 0;

}//End Default

//CopyConstructor
//Calls copylist
template <class T>
LL<T>::LL(const LL<T> &otherLL)
{
	sentinel = new Node<T>(0, 0, sentinel, sentinel);

	count = 0;

	copyList(otherLL);
}//End Copy Constructor


//Copies the items in one linked list to another linked list
//Creates new linked list using push-back function 
template <class T>
void LL<T>::copyList(const LL<T> & listToCopy)
{
	count = 0;
	this->clear();
	//Creates otherCurrent to traverse the Linked List
	Node<T> *otherCurrent = listToCopy.sentinel->next;

	while (otherCurrent != listToCopy.sentinel)
	{
		Insert_rear(otherCurrent->coef, otherCurrent->degree);

		otherCurrent = otherCurrent->next;
	}

}//End CopyList

//Destructor 
//Calls function clear
template<class T>
LL<T>::~LL()
{
	//cout << "Entering destructor" << endl;
	clear();
	//cout << "Exiting destructor" << endl;
}//End Destructor


//Adds new Node to end of list
//Updates count
template<class T>
void LL<T>::Insert_rear(T coef, T degree)
{
	try{

		Node<T> *addMe = new Node<T>(coef, degree); //New Node to be added to the LL

		//If head points to NULL, list empty head points to addMe
		if (size() == 0)
		{
			Insert_front(coef, degree);
		}
		else if (size() == 1)
		{

			addMe->next = sentinel;
			addMe->prev = sentinel->next;
			sentinel->next->next = addMe;
			sentinel->prev = addMe;
			count++;
		}
		else if (size() >1)
		{
			//Node current used to traverse LL
			Node<T> *current = sentinel->next;


			//Finding last element in LL
			while (current->next != sentinel)
			{
				current = current->next;
			}

			addMe->next = sentinel;
			addMe->prev = current;
			current->next = addMe;
			sentinel->prev = addMe;
			count++;
		}

	}

	//Catching error if could not create memory
	catch (bad_alloc)
	{
		cout << "Could not dynamically create memory" << endl;
		exit(1);
	}


}//End Insert Rear


//Adds item to front of LL
template<class T>
void LL<T>::Insert_front(T coef, T degree)
{
	try{

		Node<T>*addMe = new Node<T>(coef, degree);

		if (size() == 0)
		{
			addMe->next = sentinel;
			addMe->prev = sentinel;
			sentinel->next = addMe;
			sentinel->prev = addMe;

		}
		else if (size() >= 1)
		{
			addMe->prev = sentinel;
			addMe->next = sentinel->next;
			sentinel->next = addMe;
			sentinel->next->prev = addMe;
			//InsertList(sentinel, sentinel->next, addMe);

		}

		count++;
	}

	//Catching error if could not create memory
	catch (bad_alloc)
	{
		cout << "Could not dynamically create memory" << endl;
		exit(1);
	}

}//End Insert_front


//Removes Last Element of LL
//Updates count
template <class T>
void LL<T>::erase_rear()
{
	//If there are elements in the LL
	if (size() != 0)
	{
		Node<T>*current = sentinel->next;//create Node to traverse LL

		//Finding last element of LL
		while (current->next != sentinel)
		{

			current = current->next;
		}

		current->prev->next = sentinel;
		sentinel->prev = current->prev;
		delete current;

		count--;//deincrement count 
	}

} //End erase_rear


//Returns size of LL
template<class T>
int LL<T>::size() const
{
	return count;
}//End Size

//Clears the LL and destorys dynamically created memory 
template <class T>
void LL<T>::clear()
{
	//cout << "Entered member function LL::clear()" << endl;

	//If the head is pointing to NULL
	if (sentinel->next = sentinel)
	{
		//cout << "\tList is already empty, nothing to do here.\n";
		//cout << "List is pointing to itself\n";
	}
	else
	{
		Node<T> *current = sentinel->next;//Creates a Node to traverse LL
		int deleteCount = 0; //counts items deleted from List

		//Traverses LL and deletes elements
		while (current != sentinel)
		{
			current = current->next;
			erase_front();
			deleteCount++;
			//count--;
		}

		//sentinel->next = sentinel;
		//sentinel->prev = sentinel;

		//	cout << "\t" << deleteCount << " nodes were deallocated and removed from the list.\n";
	}

	count = 0;
	//cout << "Exiting member function LL::clear()" << endl;
}//End Clear 

//Returns T element at position ndx of LL
template<class T>
T& LL<T>::at(int ndx)
{
	//Holds the error message
	string error = "";

	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{

			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->coef);
		}
	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//end at


//Returns T element at position ndx of LL
template<class T>
T& LL<T>::atD(int ndx)
{
	//Holds the error message
	string error = "";

	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{

			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->degree);
		}
	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//end at


//Overload [] operator
//Return element T in position ndx
template<class T>
T& LL<T>::operator[](int ndx)
{
	string error = ""; //error message
	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{
			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->coef);
		}

	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//End [] overload

//Return element T in position ndx
//cannot modify element T
template<class T>
T& LL<T>::at(int ndx) const
{
	//Holds the error message
	string error = "";

	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{

			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->coef);
		}
	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//end at

//Overload [] operator
//Return Element in positio ndx
//Cannot modify element T
template<class T>
T& LL<T>::operator[](int ndx) const
{

	string error = ""; //error message
	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{
			Node<T> *current = sentinel - .next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->coef);
		}

	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//End overload [] operator 

//Overload assignment operator 
template <class T>
const LL<T>& LL<T>::operator=(const LL<T> &rhsObj)
{
	//test to ensure that the left hand side argument and the right hand argument
	//are not the same object

	if (this != &rhsObj)
	{
		this->clear();

		sentinel->next = sentinel;
		sentinel->prev = sentinel;
		count = 0;

		//Calling copyList
		copyList(rhsObj);
	}

	return *this;
}// End Assignment overload assignment operator 


//Inserts a Node in a certain index
//Capacity and number elements incerases by 1
template <class T>
void LL<T>::Insert(int ndx, T coef, T degree)
{
	try{

		Node<T> * addMe = new Node<T>(coef, degree);

		if (ndx == 0)
		{
			Insert_front(coef, degree);
		}
		else
		{
			Node<T> *current = sentinel->next;
			int counter = 1;

			while((current != sentinel )&& (counter!=ndx))
			{
				current = current->next;
				counter++;
			}

			addMe->next = current;
			addMe->prev = current->prev;
			current->prev = addMe;
			current->prev->next = addMe;
			
			count++;
		}

	}

	//Catching error if could not create new memory 
	catch (bad_alloc)
	{
		cout << "Could not dynamically create memory" << endl;
		exit(1);
	}

}


//Erase Node a certain index
//Capacity and number of elements decreases by 1
template <class T>
void LL<T>::erase(int index)
{
	Node<T> *current = sentinel->next;

	if (size()!=0)
	{
		return;
	}
	else if (index == 0)
	{
		erase_front();
	}
	else
	{
		int counter = 1;

		while (current->next != sentinel && counter != index)
		{
			current = current->next;
			counter++;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
			count--;
	}
}

//Erasing front Node
//Capacity and number of elements decreases by 1
template <class T>
void LL<T>::erase_front()
{
	if (size() >= 1)
	{
		Node<T> *current = sentinel->next;

		sentinel->next = current->next;
		current->next->prev = sentinel;
	}

}

//Cap method: returns size of LL
template <class T>
int LL<T>::cap() const
{
	return count;
}

//Printing coef and degree of each element
template<class T>
void LL<T>::print()
{
	Node<T> *current = sentinel->next;

	while (current != sentinel)
	{
		cout << (current->coef) << "x" <<"^"<< (current->degree)<<" + ";
		current = current->next;
	}
}

//Internal Insert Method
template<class T>
void LL<T>::InsertList(Node<T>* &Left, Node<T> * &Right, Node<T>* &Add)
{
	Add->next = Right;
	Add->prev = Left;
	Left->next = Add;
	Right->prev = Add;

}

//Internal Erase Method
template <class T>
void LL<T>::EraseList(Node<T> *&Left, Node<T>*&Right, Node<T>*&Erase)
{
	Left->next = Erase->next;
	Right->prev = Left;
	delete Erase;
}


//overloading +
template <class T>
LL<T> LL<T>:: operator+(LL<T> &poly1)
{
	LL<int> list;
	BubbleSort(*this, size());
	poly1.BubbleSort(poly1, poly1.size());

	Node<T> *C1 = this->sentinel->prev;
	Node<T> *C2 = poly1.sentinel->prev;

	int cnumber = 0;
	int counter = 0;

	while ((C1 != sentinel) && (C2 != poly1.sentinel))
	{

		if (C1->degree == C2->degree)
		{
			cnumber = (C1->coef) + (C2->coef);
			list.Insert_front(cnumber, C1->degree);
			C1 = C1->prev;
			C2 = C2->prev;
		}
		else if (C1->degree < C2->degree)
		{
			list.Insert_front(C1->coef, C1->degree);
			C1 = C1->prev;
		}
		else if (C2->degree < C1->degree)
		{
			list.Insert_front(C2->coef, C2->degree);
			C2 = C2->prev;
		}

	}

	if ((C1 == sentinel) && (C2 != poly1.sentinel))
	{

		while (C2 != poly1.sentinel)
		{
			list.Insert_front(C2->coef, C2->degree);
			C2 = C2->prev;
		}

	}

	else if ((C1 != sentinel) && (C2 == poly1.sentinel))
	{
		while (C1 != sentinel)
		{
			Insert_front(C1->coef, C1->degree);
			C1 = C1->prev;
		}
	}

	return list;


}

//Overloading the * operator 
template <class T>
LL<T> LL<T>::operator*(LL<T> &poly)
{
	stack<LL<int>> myS;
	LL<int> myLL;
	int num = 0;
	int de = 0;

	Node<T> *C1 = this->sentinel->next;
	Node<T> *C2 = poly.sentinel->next;

	while (C1 != sentinel)
	{
		for (int i = 0; i < poly.size(); i++)
		{
			num = (C1->coef) * (C2->coef);
			de = (C1->degree) + (C2->degree);
			myLL.Insert_rear(num, de);
			C2 = C2->next;
		}

		myS.push(myLL);
		C1 = C1->next;
		C2 = poly.sentinel->next;
		myLL.clear();

	}


	while (myS.size() > 1)
	{
		LL<int>temp1(myS.getTop());
		myS.pop();
		LL<int>temp2(myS.getTop());
		myS.pop();
		myS.push(temp1 + temp2);
	}


	return (myS.getTop());
	//return *this;
}

//Overloading the - operator 
template <class T>
LL<T> LL<T>::operator-(LL<T> &poly1)
{
	LL<int> list;

	BubbleSort(*this, size());
	poly1.BubbleSort(poly1, poly1.size());

	Node<T> *C1 = this->sentinel->prev;
	Node<T> *C2 = poly1.sentinel->prev;

	cout << poly1.size() << endl;
	int cnumber = 0;
	int counter = 0;

	while ((C1 != sentinel) && (C2 != poly1.sentinel))
	{

		if (C1->degree == C2->degree)
		{
			cnumber = (C1->coef) - (C2->coef);
			list.Insert_front(cnumber, C1->degree);
			C1 = C1->prev;
			C2 = C2->prev;
		}
		else if (C1->degree < C2->degree)
		{
			list.Insert_front(C1->coef, C1->degree);
			C1 = C1->prev;
		}
		else if (C2->degree < C1->degree)
		{
			list.Insert_front(C2->coef, C2->degree);
			C2 = C2->prev;
		}

	}

	if ((C1 == sentinel) && (C2 != poly1.sentinel))
	{

		while (C2 != poly1.sentinel)
		{
			list.Insert_front(C2->coef, C2->degree);
			C2 = C2->prev;
		}

	}

	else if ((C1 != sentinel) && (C2 == poly1.sentinel))
	{
		while (C1 != sentinel)
		{
			Insert_front(C1->coef, C1->degree);
			C1 = C1->prev;
		}
	}

	return list;


}


//Bubble Sort
template <class T>
void LL<T>::BubbleSort(LL<T> myLL, int size)
{
	int temp; 
	int temp2;
	bool swap;
	Node<T> *current = myLL.sentinel->next;

	do{
		swap = false;
		for (int i = 0; i < size - 1; i++)
		{
			if ( (current->degree)<(current->next->degree) )
			{
				temp = current->degree;
				temp2 = current->coef;
				myLL.Insert(i, current->next->coef, current->next->degree);
				myLL.Insert(i + 1, temp, temp2);
				swap = true;
			}
		}
	} while (swap);
}
#endif