#include <iostream>
using namespace std;
class LinearList {
private:
	struct Node
	{
		int value;
		Node* next;
	};
	int count;
	Node* head;
public:
	LinearList() { count = 0; head = NULL; }
	~LinearList() {
		while (head != NULL) {
			Node* p = head;
			head = head->next;
			delete p;
		}
		count = 0;
	}
	bool insert(int x, int pos) {
		if (pos > count || pos < 0) {
			return false;
		}
		Node* q = new Node;
		q->value = x;
		q->next = NULL;
		if (pos == 0) {
			q->next = head;
			head = q;
		}
		else {
			Node* p = head;
			for (int i = 1; i < pos; i++) p = p->next;
			q->next = p->next;
			p->next = q;
		}
		count++;
		return true;
	}
	bool remove(int& x, int pos) {
		if (pos > count || pos <= 0)return false;
		Node* p = head;
		if (pos == 1) {
			head = head->next;
			x = p->value;
			delete p;
		}
		else {
			for (int i = 2; i < pos; i++)p = p->next;
			Node* temp = p->next;
			p->next = temp->next;
			x = temp->value;
			delete temp;
		}
		count--;
		return true;
	}
	int element(int pos)const {
		if (pos > 0 && pos <= count) {
			Node* p = head;
			for (int i = 1; i < pos; i++)p = p->next;
			return p->value;
		}
		return -1;
	}
	int search(int x)const {
		int pos = 0;
		Node* p = head;
		while (p != NULL) {
			pos++;
			if (p->value == x)return pos;
			p = p->next;
		}
		return 0;
	}
	int length()const {
		return count;
	}
};
class Stack :public LinearList {
public:
	bool push(int x) {
		return insert(x, 0);
	}
	bool pop(int& x) {
		return remove(x, 1);
	}
	LinearList::length;
};
int main() {
	Stack s;
	s.push(77);
	int x = 0;
	s.pop(x);
	cout << x;
}