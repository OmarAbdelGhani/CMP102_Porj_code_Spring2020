#pragma once
#include<iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	
public:


	LinkedList()
	{
		Head = nullptr;
	}

	
	~LinkedList()
	{
		DeleteAll();
	}

	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}

	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}


	Node<T>* getHead() {
		return Head;
	}
	void setHead(Node<T>* node) {
		Head = node;
	}



	void InsertEnd(const T& data) {
		Node<T>* R = new Node<T>(data);
		if (Head == nullptr) {
			Head = R;
			return;
		}
		Node<T>* trav = Head;
		while (trav->getNext()) {
			trav = trav->getNext();
		}
		trav->setNext(R);

	}

	
	bool Find(T Key) {
		Node<T>* ptr = Head;
		while (ptr) {
			if (ptr->getItem() == Key) {
				return true;
			}
			ptr = ptr->getNext();
		}
		return false;

	};

	
	int CountOccurance(const T& value) {
		int count = 0;
		Node<T>* ptr = Head;
		while (ptr) {
			if (ptr->getItem() == value)
			{
				count++;
			}
			ptr = ptr->getNext();
		}
		return count;
	};


	void DeleteFirst() {
		if (Head == nullptr)
			return;
		Node<T>* ptrTMP = Head;
		Head = Head->getNext();
		delete ptrTMP;

	};



	void DeleteLast() {
		Node<T>* ptr = Head;
		Node<T>* beforePtr = Head;
		if (Head == nullptr)
			return;
		while (ptr->getNext()) {
			ptr = ptr->getNext();
		}
		while (beforePtr->getNext() != ptr) {
			beforePtr = beforePtr->getNext();
		}
		if (ptr == nullptr)
			return;
		beforePtr->setNext(nullptr);
		delete ptr;
		ptr = nullptr;
	}

	bool DeleteNode(const T& value) {
		if (this->Find(value) == false) {
			return false;
		}
		Node<T>* ptr = Head;
		Node<T>* beforePtr = Head;
		while (ptr->getItem() != value) { //ptr = el pointer ele 3ayz al8eeh
			ptr = ptr->getNext();
		}

		if (ptr == Head) {
			this->DeleteFirst();
			return true;
		}
		if (ptr->getNext() == nullptr) {
			this->DeleteLast();
			return true;
		}
		while (beforePtr->getNext() != ptr) { // ymkn asheel el negative?
			beforePtr = beforePtr->getNext(); // beforePtr = el pointer ele ablo
		}
		beforePtr->setNext(ptr->getNext());
		delete ptr;
		ptr = nullptr;
		return true;
	}


	
	bool DeleteNodes(const T& value) {
		if (this->Find(value) == false) {
			return false;
		}
		int count_ = 0;
		count_ = this->CountOccurance(value);
		for (int i = 0; i < count_; i++) {
			if (this->Find(value) == false) {
				return false;
			}
			this->DeleteNode(value);
		}
		return true;
	}



};


