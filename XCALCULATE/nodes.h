#ifndef _NODO
#define _NODO
template <typename T> class LinkedList;

template <typename T> class Node {
	friend class LinkedList<T>;
	T data;
	Node *next;
	Node *prev;
public:
	Node() {};
	Node(T);
	T getData() { return this->data; }
	void setData(T data) { this->data = data; }
	char *callPrint();
};
template <typename T> Node<T>::Node(T data) {
	this->data = data;
	this->next = NULL;
	this->prev = NULL;
}
template <typename T>char* Node<T>::callPrint() {
	return data.print();
}
#endif
