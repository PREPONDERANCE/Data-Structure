//#include <iostream>
//#include <stack>
//using namespace std;
//
//void reverse(char s[], int n){
//	stack<char> S;
//	for(int i = 0; i < n; i++)
//		S.push(s[i]);
//	for(int j = 0; j < n; j++){
//		s[j] =  S.top();
//		S.pop();
//	}
//}
//
//int main(){
//	char s[100];
//	cin >> s;
//	reverse(s, strlen(s));
//	cout << s << endl;
//	
//	return 0;
//}
// Reverse a string

#include <iostream>
#include <stack>
using namespace std;

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void push(Node**, int);
void reverse(Node**);
void print(Node*);

int main(){
	Node* head = NULL;
	push(&head, 3);
	push(&head, 6);
	reverse(&head);
	
	print(head);
}

void push(Node** headref, int new_data){
	Node* newNode = new(Node);
	newNode->data = new_data;
	newNode->next = *headref;
	*headref = newNode;
}

void print(Node* head){
	if( head ){
		printf("%d ", head->data);
		print(head->next);
	}
}

void reverse(Node** headref){
	stack<Node*> s;
	Node* temp = *headref;
	
	while( temp ){
		s.push(temp);
		temp = temp->next;
	}
	
	*headref = s.top();
	do{
		temp = s.top();
		s.pop();
		temp->next = s.top();
	}while( !s.empty() );
	temp->next = NULL; 
}