#pragma once
#include<iostream>
#include<stdio.h>
template<typename queueELement>
class Queue {
private:
	class QueueNode {
	public:
		queueELement data;
		QueueNode* next;
		QueueNode(queueELement data) :next(NULL), data(data) {}
		QueueNode() : next(NULL) {}

	};
	QueueNode* front;
	QueueNode* back;
public:
	//internal function to dispaly data of queue
	void display() const;
	//returns the element in the front of the queue
	queueELement getFront() const;
	//checks if the queue is empty or not
	bool isEmpty() const;
	//adding an element to the queue
	void enqueue(queueELement data);
	//removing the element from the queue
	void dequeue();
	// constructor
	Queue();
	Queue(const Queue<queueELement>& q) {

		front = back = NULL;
		if (!q.isEmpty()) {

			front = back = new QueueNode(q.getFront());
			QueueNode* qPtr = q.front->next;
			while (qPtr != NULL) {
				back->next = new QueueNode(qPtr->data);
				back = back->next;
				qPtr = qPtr->next;
			}

		}

	}
	//destructor
	~Queue();
	//get size of queue;
	int getSize() const;
	//get last element
	queueELement getBack() const;

};


template<typename queueElement>
void Queue<queueElement>::display() const {

	for (QueueNode* ptr = front; ptr != NULL; ptr = ptr->next)
		std::cout << ptr->data << " ";
	std::cout << std::endl;
}

template<typename queueElement>
bool Queue<queueElement>::isEmpty() const {

	if (front == NULL)
		return true;
	else
		return false;
}

template<typename queueElement>
queueElement Queue<queueElement>::getFront() const {
	if (!isEmpty())
		return front->data;
	else {
		std::cerr << "queue is empty" << std::endl;
		queueElement* temp = new(queueElement);
		queueElement garbage = *temp;     // "Garbage" value
		delete temp;
		return garbage;
	}
}

template<typename queueElement>
void Queue<queueElement>::enqueue(queueElement data) {
	QueueNode* node = new QueueNode(data);
	if (isEmpty()) {
		front = back = node;
	}
	else {
		back->next = node;
		back = back->next;
	}
	return;
}

template<typename queueElement>
void Queue<queueElement>::dequeue() {
	if (isEmpty()) {

		std::cerr << "queue is empty" << std::endl;
		return;
	}
	QueueNode* ptr = front;
	front = front->next;
	delete(ptr);
	if (front == NULL) // is now empty 
		back = NULL;
	return;
}

template<typename queueElement>
Queue<queueElement>::Queue() {

	front = NULL;
	back = NULL;
}

template<typename queueElement>
Queue<queueElement>::~Queue() {
	QueueNode* ptr = front;
	QueueNode* current = nullptr;
	while (ptr != NULL) {
		
			current = ptr->next;
			delete ptr;
			ptr = current;
		
	}
}

template<typename queueElement>
int Queue<queueElement>::getSize() const {

	QueueNode* ptr = front;
	int count = 0;
	while (ptr != NULL) {
		ptr = ptr->next;
		count++;
	}

	return count;
}

template<typename queueElement >
queueElement Queue<queueElement>::getBack() const {

	if (!isEmpty())
		return back->data;
	else {
		std::cerr << "queue is empty" << std::endl;
		queueElement* temp = new(queueElement);
		queueElement garbage = *temp;     // "Garbage" value
		delete temp;
		return garbage;
	}
}

