#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class myStack {
	char data;
	myStack* lptr;
	myStack * top, *previous;
public: 
	myStack(): data(0),lptr(NULL),top(NULL),previous(NULL){}
	void push(char);
	char pop();
	char retTop();
};
void myStack::push(char value) {
	top = new myStack;
	top->lptr = NULL;
	top->data = value;
	top->lptr = previous;
	previous = top;
}
char myStack::pop() {
	if (top == NULL) {
		return '#';
	}
	else {
		myStack* temp = top;
		char a = top->data;
		top = top->lptr;
		previous = top;
		delete(temp);
		return a;
	}
}
char myStack::retTop() {
	if (top != NULL)
		return top->data;
	else
		return '#';
}

class reversePolish {
	char table[3][2];
public:
	reversePolish() {
		table[0][0] = '^';
		table[1][0] = '/';
		table[1][1] = '*';
		table[2][0] = '+';
		table[2][1] = '-';
	}
	bool isPrior(char, char);
};
bool reversePolish::isPrior(char op, char st) {
	int oper = 999, stackOp = 999;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if (table[i][j] == op) {
				oper = i;
			}
			if (table[i][j] == st) {
				stackOp = i;
			}
		}
		if (oper != 999 && stackOp != 999) {
			break;
		}
	}
	if (oper < stackOp) {
		return true;
	}
	return false;
}

void evaluation(string postfix) {
	myStack stack;
	int answer = 0;
	for (int i = 0; i < postfix.length(); i++) {
		if (postfix[i] >= '0' && postfix[i] <= '9') {
			stack.push(postfix[i]);
		}
		else if (postfix[i] == '^' || postfix[i] == '/' || postfix[i] == '*' || postfix[i] == '+' || postfix[i] == '-') {
			int second = static_cast<int>(stack.pop()) - 48;
			int first = static_cast<int>(stack.pop()) - 48;
			
			switch (postfix[i]) {
			case '^':
				answer = first ^ second;
				stack.push(answer + 48);
				break;
			case '/':
				answer = first / second;
				stack.push(answer + 48);
				break;
			case '*':
				answer = first * second;
				stack.push(answer + 48);
				break;
			case '+':
				answer = first + second;
				stack.push(answer + 48);
				break;
			case '-':
				answer = first - second;
				stack.push(answer + 48);
				break;
			}
		}
	}
	cout << answer << endl;
}

int main() {
	char a = '9';
	myStack stack;
	reversePolish polish;

	string infix="", postfix="";
	cout << "ENTER YOUR DATA" << endl;
	getline(cin , infix);
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == '^' || infix[i] == '/' || infix[i] == '*' || infix[i] == '+' || infix[i] == '-') {
			while (stack.retTop() != '#' && stack.retTop() != '(' && !polish.isPrior(infix[i], stack.retTop())) {
				postfix += stack.pop();
			}
			stack.push(infix[i]);
		}
		else if ((infix[i] >= 'a' && infix[i] < 'z') || (infix[i] >= '0' && infix[i] <= '9')) {
			postfix += infix[i];
		}
		else if (infix[i] == '(') {
			stack.push(infix[i]);
		}
		else if (infix[i] == ')') {
			while (stack.retTop() != '#' && stack.retTop() != '(') {
				postfix += stack.pop();
			}
			stack.pop();
		}
	}
	while (stack.retTop() != '#') {
		postfix += stack.pop();
	}
	cout << postfix << endl;
	evaluation(postfix);
	

	system("pause");
	return 0;
}