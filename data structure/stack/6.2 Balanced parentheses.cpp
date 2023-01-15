#include <iostream>
#include <stack>
using namespace std;

void balancedparentheses(char *s){
	int c;
	stack<int> S;
	
	while( (c = *s++) != '\0' ){
		if( c == '(' || c == '{' || c == '[' )
			S.push(c);
		if( c == ')' || c== '}' || c == ']' ){
			if( S.empty() ){
				cout << "Parentheses not balanced" << endl;
				return;
			}else{
				switch( c ){
					case ')' :  if( S.top() == '(' )
									S.pop();
								else{
									cout << "Parentheses not balanced" << endl;
									return;
								}                                                  break;
					case '}' :  if( S.top() == '{' )
									S.pop();
								else{
									cout << "Parentheses not balanced" << endl;
									return;
								}               								   break;
					case ']' :  if( S.top() == '[' )
									S.pop();
								else{
									cout << "Parentheses not balanced" << endl;
									return;
								}   											   break;
				}
			}
		}
	}
	cout << "Parentheses balanced" << endl;
}

int main(int argc, char *argv[]) {
	char s[100];
	cin >> s;
	
	balancedparentheses(s);
	
	return 0;
}