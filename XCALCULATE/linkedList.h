#ifndef _LISTA
#define _LISTA
#include <Windows.h>
#include <stdio.h>
#include "nodes.h"
using namespace std;

template <typename T> class LinkedList {
	Node<T> *first;
	Node<T> *last;
public:
	LinkedList();
	~LinkedList();
	Node<T> *getFirst() { return this->first; }
	Node<T> *getLast() { return this->last; }
	void EraseList();
	void AddNode(T);
	void DeleteNode(Node<T>*);
	Node<T> *SearchNode(int);
	void PrintOnWindow(HWND, int);
	int CountList();
};
//// PRIVATE METHODS ////
//// PUBLIC METHODS ////
template <typename T> LinkedList<T>::LinkedList() {
	first = NULL;
	last = NULL;
}
template <typename T> LinkedList<T>::~LinkedList() {
	while (first != NULL) {
		Node<T>* deleter = first;
		first = first->next;
		delete deleter;
	}
}
template <typename T> void LinkedList<T>::EraseList() {
	while (first != NULL) {
		Node<T>* deleter = first;
		first = first->next;
		delete deleter;
	}
}
template <typename T> void LinkedList<T>::AddNode(T data) {
	Node<T> *newest = new Node<T>(data);
	newest->prev = newest->next = NULL;
	if (first == NULL) {
		first = newest;
		last = newest;
	}
	else {
		last->next = newest;
		newest->prev = last;
		last = newest;
	}
}
template <typename T> void LinkedList<T>::DeleteNode(Node<T>* deleter) {
	if (deleter->next == NULL & deleter->prev == NULL) {
		delete deleter;
		first = last = NULL;
	}
	else if (deleter->prev == NULL) {
		deleter->next->prev = NULL;
		first = deleter->next;
		delete deleter;
	}
	else if (deleter->next == NULL) {
		deleter->prev->next = NULL;
		last = deleter->prev;
		delete deleter;
	}
	else {
		deleter->next->prev = deleter->prev;
		deleter->prev->next = deleter->next;
		delete deleter;
	}
}
template <typename T> Node<T>* LinkedList<T>::SearchNode(int ref) {
	Node<T> *aux = first;
	while (aux != NULL) {
		if (aux->data == ref) {
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}
template <typename T> void LinkedList<T>::PrintOnWindow(HWND hWindow, int windowType) {
	switch (windowType) {
	case 0: {
		SendMessage(hWindow, LB_RESETCONTENT, 0, 0);
		Node<T> *aux = first;
		while (aux != NULL) {
			SendMessage(hWindow, LB_ADDSTRING, 0, (LPARAM)aux->callPrint());
			aux = aux->next;
		}
		break;
	}
	case 1: {
		SendMessage(hWindow, CB_RESETCONTENT, 0, 0);
		Node<T> *aux = first;
		while (aux != NULL) {
			SendMessage(hWindow, CB_ADDSTRING, 0, (LPARAM)aux->callPrint());
			aux = aux->next;
		}
		break;
	}
	default:
		char buff[60];
		snprintf(buff, 40, "Intentó ingrasar tipo de ventana %d invalida.", windowType);
		MessageBox(NULL, buff, "ERROR", MB_ICONERROR);
		break;
	}
}
template <typename T> int LinkedList<T>::CountList() {
	int c = 0;
	Node<T> *aux = first;
	while (aux != NULL) {
		c++;
		aux = aux->next;
	}
	return c;
}
#endif
