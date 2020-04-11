#pragma once
#include <string>
#ifndef List_h
using namespace std;



template<typename T>
class NodeOfList
{
private:

	NodeOfList* next, * prev;
public:
	T data;
	NodeOfList() : next(NULL), prev(NULL) {};
	NodeOfList(T data) {
		this->data = data;
		next = NULL;
		prev = NULL;
	}
	~NodeOfList() {
		next = NULL;
		prev = NULL;
	}
	void set_data(T data) {
		this->data = data;
	}
	T get_data() {
		return data;
	}
	NodeOfList* get_next() {

		return next;
	}
	NodeOfList* get_prev() {
		return prev;
	}
	void set_next(NodeOfList* pointer) {
		next = pointer;
	}
	void set_prev(NodeOfList* pointer) {
		prev = pointer;
	}
};

template<typename T>
class List
{
private:


public:



	NodeOfList<T>* head, * tail;
	NodeOfList<T>* get_pointer(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			NodeOfList<T>* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}
			return temp;
		}
	}




	List() 
	{
		head = NULL;
		tail = NULL;
	}
	List(const List<T>& list) {
		clear();
		NodeOfList<T>* temp = list.head;
		while (temp) {
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}
	~List()
	{
		if (head == NULL)
		{
			head = NULL;
		}
		else
		{
			while (head)
			{
				tail = head->get_next();
				delete head;
				head = tail;
			}
		}
	}
	void push_back(T data)
	{
		NodeOfList<T>* temp = new NodeOfList<T>;
		temp->set_data(data);
		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(T data)
	{
		NodeOfList<T>* temp = new NodeOfList<T>;
		temp->set_data(data);
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}
	void push_front(List& ls2)
	{
		NodeOfList<T>* temp = ls2.tail;
		size_t n = ls2.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}
	void pop_back()
	{
		if (head != tail)
		{
			NodeOfList<T>* temp = tail;
			tail = tail->get_prev();
			tail->set_next(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			NodeOfList<T>* temp = tail;
			tail = head = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	void pop_front()
	{
		if (head != tail)
		{
			NodeOfList<T>* temp = head;
			head = head->get_next();
			head->set_prev(NULL);
			delete temp;
		}
		else if (!isEmpty())
		{
			NodeOfList<T>* temp = head;
			head = tail = NULL;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}
	void insert(size_t index, T data)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		if (temp == head)
			push_front(data);
		else
		{
			NodeOfList<T>* newElem = new NodeOfList;
			newElem->set_data(data);
			temp->get_prev()->set_next(newElem);
			newElem->set_prev(temp->get_prev());
			newElem->set_next(temp);
			temp->set_prev(newElem);
		}
	}
	T at(size_t index)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		return temp->get_data();
	}
	void remove(size_t index)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	void remove(T data) {
		NodeOfList<T>* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Invalid argument");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}
	size_t get_size()
	{
		NodeOfList<T>* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->get_next();
		}
		return length;
	}
	void print_to_console()
	{
		NodeOfList<T>* temp = head;
		while (temp)
		{
			cout << temp->get_data() << ' ';
			temp = temp->get_next();
		}
		cout << endl;
	}
	void clear()
	{
		if (this->isEmpty())
			return;
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}
	void set(size_t index, T data)
	{
		NodeOfList<T>* temp;
		temp = get_pointer(index);
		temp->set_data(data);
	}

	bool isEmpty()
	{
		if (head==NULL)
			return true;
		else
			return false;
	}

};



#define List_h
#endif //data_h