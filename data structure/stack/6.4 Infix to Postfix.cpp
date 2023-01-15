#include <iostream>
#include <stack>
using namespace std;

void InfixToPostfix(char *);
bool digit(int);
bool isoperator(int);
bool compare(int, int);
bool openbrackets(int);
bool closebrackets(int);

int main(int argc, char *argv[]) {
	char s[100];
	fgets(s, sizeof(s), stdin);
	
	InfixToPostfix(s);
	cout << "Infix to Postfix " << ": ";
	cout << s << endl;
	
	return 0;
}

void InfixToPostfix(char *exp){
	static int i = 0, j = 0;
	stack<char> s;
	
	for(; exp[i] != '\n'; i++){
		if( exp[i] == ' ' || exp[i] == ',' )
			continue;
		else if( digit(exp[i]) ){
			while( digit(exp[i]) )
				exp[j++] = exp[i++];
			if( exp[i] == '.' ){
				exp[j++] = exp[i++];
				while( digit(exp[i]) )
					exp[j++] = exp[i++];
			}
			exp[j++] = ' ';
			i--;
		}else if( exp[i] == '-' ){
			if( digit(exp[i+1]) ){
				exp[j++] = exp[i++];
				while( digit(exp[i]) )
					exp[j++] = exp[i++];
				exp[j++] = ' ';
				i--;
			}else{
				if( s.empty() )
					s.push('-');
				else{
					while( !s.empty() ){
						exp[j++] = s.top();
						exp[j++] = ' ';
						s.pop();
					}
					s.push('-');
				}
			}
		}else if( isoperator(exp[i]) ){
			if( s.empty() || compare(s.top(), exp[i]))
				s.push(exp[i]);
			else if( !compare(s.top(), exp[i]) ){
				while( !s.empty() ){
					exp[j++] = s.top();
					exp[j++] = ' ';
					s.pop();
				}
				s.push(exp[i]);
			}
		}else if( openbrackets(exp[i]) ){
			i++;
			InfixToPostfix(exp);
		}else if( closebrackets(exp[i]) ){
			while( !s.empty() ){
				exp[j++] = s.top();
				exp[j++] = ' ';
				s.pop();
			}
			return;
		}
	}
	while( !s.empty() ){
		exp[j++] = s.top();
		exp[j++] = ' ';
		s.pop();
	}
	exp[j] = '\0';
}

bool digit(int c){
	return (c >= '0' && c <= '9' ) ? true : false;
}

bool isoperator(int c){
	return (c == '*' || c == '+' || c == '/' || c == '%') ? true : false;
}

bool compare(int a, int b){
	bool res = false;
	if( b == '*' || b == '/' || b == '%' && !(a == '*' || a == '/' || a == '%') )
		res = true;
	return res;
}

bool openbrackets(int c){
	return (c == '(' || c == '{' || c == '[') ? true : false;
}

bool closebrackets(int c){
	return (c == ')' || c == '}' || c == ']') ? true : false;
}