#include <iostream>
#include <cstddef>
using namespace std;

template <class T>
struct Node{
	T data;
	Node<T>* next;
	Node(): data(0), next(nullptr) {}
	Node(const T& data, T* next = nullptr): data(data), next(next) {}
};

template <class T>
class list{
public:
	list(): head(nullptr) {}
	void push(const T&);
	void insert(const T&, int);
	void del(int);
	void reverse();
	void print();
	
private:
	Node<T>* head;
};

template <class T>
void list<T>::push(const T& data){
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->next = head;
	head = newNode;
}

template <class T>
void list<T>::insert(const T& data, int pos){
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	
	Node<T>* current = head;
	
	if( pos == 1 ){
		newNode->next = head;
		head = newNode;
		return;
	}
	
	for(int i = 1; i != pos; i++)
		if( current ) current = current->next;
	
	if( current ){
		newNode->next = current->next;
		current->next = newNode;
	}
}

template <class T>
void list<T>::del(int pos){
	Node<T> *prev = head, *temp = head;
	
	for(int i = 0; i != pos; i++){
		if( i == 0 && pos == 1 ){
			head = head->next;
			delete prev;
		}else{
			if( i == pos-1 && temp ){
				prev->next = temp->next;
				delete temp;
			}else{
				prev = temp;
				if( prev ) temp = temp->next;
			}
		}
	}
}

template <class T>
void list<T>::print(){
	Node<T>* current = head;
	while( current ){
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

template <class T>
void list<T>::reverse(){
	Node<T>* current = head;
	Node<T>* prev = current->next;
	Node<T>* temp = prev->next;
	
	while( prev ){
		prev->next = current;
		current = prev;
		prev = temp;
		if( temp ) temp = temp->next;
	}
	
	head->next = nullptr;
	head = current;
}

int main(int argc, char *argv[]) {
	list<int> l;
	l.push(4);
	l.push(5);
	l.push(1);
	l.push(6);
	l.push(8);
	l.print();
	
	l.insert(2, 1);
	l.print();
	
	l.del(8);
	l.print();
	
	l.reverse();
	l.print();
	
	return 0;
}