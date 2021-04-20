#pragma once
#include "stdio.h"
#include <iostream>

template <class T>
class Node {
public:
	T data;
	Node* next;

	Node(T temp, Node* nexttemp) {
		data = temp;
		next = nexttemp;
	}
};


template <class T>
class List {
protected:
	Node<T>* head;
	int count;
public:
	class iterator
	{
	private:
		Node<T>* current;
	public:
		iterator(Node<T>* temp) : current(temp) {}
		iterator(const iterator& iter) : current(iter.current) {}

		iterator operator ++()
		{
			current = current->next;
			return *this;
		}

		Node<T>& operator*() { return *current; }

		Node<T>*& getit() { return current; }

		Node<T>* operator ->() { return current; }

		bool operator==(iterator iter)
		{
			return (current == iter.current);
		}

		bool operator!=(iterator iter)
		{
			return !(*this == iter);
		}
	};

	iterator begin() const {
		iterator iter(head);
		return iter;
	}
	iterator end() const {
		iterator iter(head);
		return iter;
	}


	List(Node<T>* p)
	{
		head = p;
		head->next = head;
		count = 0;
	}
	
	List(const List<T>& list) {
		Node<T>* p = new Node<T>(list.gethead()->data, NULL);
		head = p;
		head->next = head;
		count = 0;
		iterator it1 = begin();
		iterator it2 = list.begin()->next;
		while (it2 != list.end())
		{
			insert(it2->data, it1.getit());
			++it1;
			++it2;
		}
	}

	~List()
	{
		clear();
	}

	Node<T>* gethead() const
	{
		return head;
	}


	void insert(T elem, Node<T>* node)
	{
		Node<T>* p = new Node<T>(elem, node->next);
		node->next = p;
		count++;
	};

	List& operator=(const List& list)
	{
		if (*this == list) return (*this);
		else {
			this->clear();
			iterator it1 = begin();
			iterator it2 = list.begin()->next;
			while (it2 != list.end())
			{
				insert(it2->data, it1.getit());
				++it1;
				++it2;
			}
		}
		return (*this);
	}

	bool operator==(const List& lst) const
	{
		iterator it1 = begin();
		iterator it2 = lst.begin();
		bool temp = true;
		if (count != lst.getcount())
			return false;
		else {
			do
			{
				if (it1->data != it2->data)
				{
					temp = false;
					break;
				}
				else
				{
					++it1;
					++it2;
				}
			} while (it1 != end());
		}
		return temp;
	}

	void clear() {
		while (head->next != head)	
			pop_front();
		count = 0;
	};

	void push_front(T elem)
	{
		Node<T>* p = new Node<T>(elem, head->next);
		head->next = p;
		count++;
	}

	void pop_front()
	{
		if (count == 0) 
			throw "Empty list";
		Node<T>* p = head->next;
		head->next = p->next;
		delete p;
		count--;
	}

	bool empty() {
		return (head->next == head);
	};

	int getcount() const{ return count; };

	Node<T>* get_head() { return head; }
};

class Polinom;

class Monom {
public:
	int power;
	double coef;
	Monom(int temp1 = -1, double temp2 = 0);
	Monom(const Monom& A) {
		power = A.power;
		coef = A.coef;
	}
	int xPower() const { return (power / 100); }
	int yPower() const { return ((power / 10) % 10); }
	int zPower() const { return (power % 10); }

	Monom operator+(const Monom& A) {
		Monom C;
		if (power == A.power) {
			C.power = power;
			C.coef = coef + A.coef;
			return C;
		}
		else throw "Unequal powers";
	}

	Monom operator*(const Monom& A) {
		Monom C;
		int A2 = xPower() + A.xPower();
		int B2 = yPower() + A.yPower();
		int C2 = zPower() + A.zPower();
		if (A2 < 10 && B2 < 10 && C2 < 10)
		{
			C.power = A2 * 100 + B2 * 10 + C2;
			C.coef = coef * A.coef;
			return C;
		}
		else throw "Too big power after multiplication";
	}


	bool operator==(const Monom& A) {
		return (coef == A.coef && power == A.power);
	}

	bool operator!=(const Monom& A) {
		return !(*this == A);

	}

	friend std::ostream& operator<<(std::ostream& os, const Monom& monom)
	{
		os << monom.coef << "*x^" << monom.xPower() <<
			"*y^" << monom.yPower() <<
			"*z^" << monom.zPower();
		return os;
	}

	Polinom Monom::operator* (const Polinom& polinom);
};



class Polinom :public List<Monom> {
public:
	Polinom(Node<Monom>* p);
	Polinom(const Polinom& polinom);

	~Polinom()
	{
		clear();
	}

	Polinom operator+ (const Polinom& A) {
		Monom monom_;
		Node<Monom>* p = new Node<Monom>(monom_, NULL);
		p->next = p;
		Polinom res(p);
		Polinom::iterator it1 = begin()->next;
		Polinom::iterator it2 = A.begin()->next;
		Polinom::iterator it3 = res.begin();
		while ((it1 != end()) && (it2 != A.end()))
		{
			if ((it1->data.power) < (it2->data.power))
			{
				res.insert(it1->data, it3.getit());
				++it1;
				++it3;
			}
			else if ((it2->data.power) < (it1->data.power))
			{
				res.insert(it2->data, it3.getit());
				++it2;
				++it3;
			}
			else if ((it2->data.power) == (it1->data.power))
			{
				res.insert((it1->data + it2->data), it3.getit());
				++it1;
				++it2;
				++it3;
			}
		}
		if (it1 == end())
		{
			while (it2 != A.end())
			{
				res.insert(it2->data, it3.getit());
				++it2;
				++it3;
			}
		}
		else
		{
			while (it1 != end())
			{
				res.insert(it1->data, it3.getit());
				++it1;
				++it3;
			}
		}
		return res;
	};


	Polinom operator* (const Polinom& A) {
		Monom monom;
		Node<Monom>* p = new Node<Monom>(monom, NULL);
		p->next = p;
		Polinom res(p);
		Polinom pol2(res);
		Polinom::iterator it1 = begin()->next;
		while (it1 != end())
		{
			pol2 = (it1->data) * A;
			res = res + pol2;
			++it1;
		}
		return res;
	};

	Polinom operator* (Monom& A) {
		return (A * (*this));
	};
	

	bool empty() {
		return (head->next == head);
	};

	friend std::ostream& operator<<(std::ostream& os, const Polinom& polinom)
	{
		Polinom::iterator it = polinom.begin()->next;
		while (it != polinom.end())
		{
			os <<  it->data << " + " ;
			++it;
		}
		os << "0";

		return os;
	};

	int GetCount() { return count; };

};

Monom::Monom(int temp1_, double temp2_) {
	power = temp1_;
	coef = temp2_;
	if (!(xPower() < 10 && yPower() < 10 && zPower() < 10))
		throw "Unexeptable power";
};

Polinom Monom::operator* (const Polinom& polinom) {
	Monom m;
	Node<Monom>* p = new Node<Monom>(m, nullptr);
	p->next = p;
	Polinom res(p);
	Polinom::iterator it1 = polinom.begin()->next;
	Polinom::iterator it2 = res.begin();
	while (it1 != polinom.end())
	{
		res.insert((*this) * (it1->data), it2.getit());
		++it1;
		++it2;
		if (!(xPower() < 10 && yPower() < 10 && zPower() < 10))
			throw "Unexeptable power";
	}
	return res;
};


Polinom::Polinom(Node<Monom>* p) :List<Monom>(p) {};
Polinom::Polinom(const Polinom& polinom) :List<Monom>(polinom) {};