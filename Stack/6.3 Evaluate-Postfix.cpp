// C++ program to evaluate postfix
// In this program,  we'll just focus on some basic scenarios regardless of error handling

#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isnumericdigit(int);
bool isoperator(int);
int PerformOperation(char, int, int);
int EvaluatePostfix(char*);

int main(int argc, char *argv[]) {
	char s[100];
	fgets(s, sizeof(s), stdin);
	
	cout << EvaluatePostfix(s) << endl;
	
	return 0;
}

bool isnumericdigit(int c){
	return (c >= '0' && c <= '9') ? true : false;
}

bool isoperator(int c){
	return (c == '+' || c == '-' || c == '*' || c == '/') ? true : false;
}

int PerformOperation(char calculate, int op1, int op2){
	if( calculate == '+' )
		return op1+op2;
	else if( calculate == '-' )
		return op2-op1;
	else if( calculate == '*' )
		return op1*op2;
	else if( calculate == '/' ){
		if( op1 == 0 ){
			cout << "zero divisor" << endl;
			return false;
		}
		return op2/op1;
	}
	cout << "Unknown command" << endl;
	return false;
}

int EvaluatePostfix(char *exp){
	stack<int> s;
	int i = 0;
	
	for(i = 0; exp[i] != '\n'; i++){
		if( exp[i] == ' ' || exp[i] == ',' )
			continue;
		else if( isoperator(exp[i]) ){
			int op1 = s.top();  s.pop();
			int op2 = s.top();  s.pop();
			s.push(PerformOperation(exp[i], op1, op2));
		}else if( isnumericdigit(exp[i]) ){
			int operand = 0;
			while( isnumericdigit(exp[i]) ){
				operand = operand * 10 + exp[i] - '0';
				i++;
			}
			s.push(operand);
			i--;
		}
	}
	return s.top();
}


// C program implementation using linked list to create stack

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <string.h>
//#include <ctype.h>
//#include <math.h>
//
//typedef struct Node{
//	double data;
//	struct Node* next;
//} Node;
//
//typedef struct{
//	int count;
//	Node* top;
//} Stack;
//
//Stack* CreateStack(void);
//void push(Stack*, double);
//double pop(Stack*);
//double PerformOperation(char, double, double);
//double EvaluatePostfix(char*);
//bool isoperator(int);
//
//
//
//int main(int argc, char *argv[]) {
//	char s[100];
//	fgets(s, sizeof(s), stdin);
//	
//	printf("result is %f\n", EvaluatePostfix(s));
//	return 0;
//}
//
//
//Stack* CreateStack(void){
//	Stack* s = (Stack*)malloc(sizeof(Stack));
//	s->count = 0;
//	s->top = NULL;
//	return s;
//}
//
//void push(Stack *s, double new_data){
//	Node* newNode = (Node*)malloc(sizeof(Node));
//	newNode->data = new_data;
//	newNode->next = s->top;
//	s->top = newNode;
//	s->count++;
//}
//
//double pop(Stack* s){
//	if( s->top == NULL ){
//		printf("Stack empty\n");
//		return -1;
//	}
//	Node* temp = s->top;
//	s->top = s->top->next;
//	s->count--;
//	return temp->data;
//}
//
//double PerformOperation(char operation, double op1, double op2){
//	if( operation == '+' )
//		return op1+op2;
//	else if( operation == '-' )
//		return op2-op1;
//	else if( operation == '*' )
//		return op1*op2;
//	else if( operation == '/' ){
//		if( op1 == 0 ){
//			printf("error : zero divisor\n");
//			return false;
//		}
//		return op2/op1;
//	}
//	else if( operation == '%' ){
//		if( op1 == 0 ){
//			printf("error : zero diviosr\n");
//			return false;
//		}
//		return fmod(op2, op1);
//	}
//	printf("error : unknown command\n");
//	return false;
//}
//
//bool isoperator(int c){
//	return (c == '+' || c == '*' || c == '/' || c == '%') ? true : false;
//}
//
//double EvaluatePostfix(char* exp){
//	Stack* s = CreateStack();
//	int i = 0;
//	double operand = 0;
//	double temp = 0;
//	int pow = 1;
//	
//	while( exp[i] ){
//		operand = 0;
//		temp = 0;
//		pow = 1;
//		if( isoperator(exp[i]) ){
//			double op1 = pop(s);
//			double op2 = pop(s);
//			int operator = exp[i];
//			if( PerformOperation(operator, op1, op2) == false ){
//				printf("error : unknown command\n");
//				return false;
//			}else
//				push(s, PerformOperation(operator, op1, op2));
//		}else if( exp[i] == '-' ){
//			if( isdigit(exp[++i]) ){
//				while( isdigit(exp[i]) ){
//					operand = operand * 10 + exp[i] - '0';
//					i++;
//				}
//				operand = -operand;
//				if( exp[i] != '.' )
//					push(s, operand);
//			}else{
//				double op1 = pop(s);
//				double op2 = pop(s);
//				push(s, PerformOperation('-', op1, op2));
//			}
//		}else if( isdigit(exp[i]) || exp[i] == '.' ){
//			while( isdigit(exp[i]) ){
//				operand = operand * 10 + exp[i] - '0';
//				i++;
//			}
//			if( exp[i] == '.' ){
//				i++;
//				while( isdigit(exp[i]) ){
//					pow = pow * 10;
//					temp = temp * 10 + exp[i] - '0';
//					i++;
//				}
//			}
//			i--;
//			(operand > 0) ? (operand = operand + temp/pow) : (operand = operand - temp/pow);
//			push(s, operand);
//		}
//		i++;
//	}
//	return pop(s);
//}


// Check for K&R C Programming, Chapter 4, 4-4#.c for array implementation.
// This approach is generally more rigorous and more neat.