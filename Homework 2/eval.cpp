#include <string>
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

int precedence(char x);

int evaluate(string infix, string& postfix, bool& result) {

	stack<char> myStack;
	stack<char> notStack;
	int openpara = 0;
	int closepara = 0;
	postfix = ""; // ensure that postfix is empty

	//CHECK FOR A VALID INFIX----------------------------------------------------------------------------------------------------------------
	if (infix == "") { // when infix is = to empty string
		return 1;
	}
	
	string infix2 = "";
	for (int i = 0; i < infix.length(); i++) { // loop to remove white space
		if (infix[i] != ' ')
			infix2 += infix[i]; 
	}
	infix = infix2;
	if (infix[0] == '&' || infix[0] == '|' || infix[0] == ')') // invalid first element
		return 1;
	int lastChar = infix.length() - 1;
	if (infix[lastChar] == '&' || infix[lastChar] == '|' || infix[lastChar] == '(' ||infix[lastChar] == '!') // cannot end with these elements
		return 1;
	for (int a = 0; a < infix.length() - 1; a++) {
		if (infix[a] != 'T' && infix[a] != 'F' && infix[a] != '|' && infix[a] != '&' && infix[a] != '(' && infix[a] != ')' && infix[a] != '!') //make sure that the characters are valid
			return 1;
		if (infix[a] == 'T' || infix[a] == 'F') {
			int tempval = 0;
			int op = 0;
			int change = 0;
			if (infix[a + 1] == 'T' || infix[a + 1] == 'F' || infix[a + 1] == '(')
				return 1;
			if (infix[a + 1] == '!') {
				for (int y = a; y < infix.length() - 1; y++) {
					if (infix[y] == 'T' || infix[y] == 'F') {
						tempval = y; // temp val is index of next letter
						change = 1;
					}
				}
				if (change == 1) {
					for (int s = a + 1; s < tempval; s++) {
						if (infix[s] == '&' || infix[s] == '|')
							op++;
					}
					if (op != 1)
						return 1;
				}
			}
			
		}
		if (infix[a] == '(') {
			openpara++;
			if (infix[a + 1] != 'T' && infix[a + 1] != 'F' && infix[a + 1] != '!' && infix[a + 1] != '(') // the only valid things to follow (
				return 1;
		}
		if (infix[a] == ')') {
			closepara++;
			if (infix[a - 1] != 'T' && infix[a - 1] != 'F' && infix[a - 1] != ')')
				return 1;
		}
		if (infix[a] == '!') {
			if (infix[a + 1] == '&' || infix[a + 1] == '|')
				return 1;
			if (infix[a + 1] != 'T' && infix[a + 1] != 'F' && infix[a + 1] != '(' && infix[a + 1] != '!')
				return 1;
		}
		if (infix[a] == '&' || infix[a] == '|') {
			if (infix[a + 1] == '|' || infix[a + 1] == '&' || infix[a+1] == ')')
				return 1;
		}

	}
	if (infix[lastChar] == ')')
		closepara++;
	if (openpara != closepara)
		return 1;
	
	if (infix == "()") { // empty parentheses
		return 1;
	}
	
	// infix to postfix-------------------------------------------------------------------------------
	int x = 0;
	for (int i = 0; i < infix.length(); i++) {

		if (infix[i] == 'T' || infix[i] == 'F') {
			//postfix += ' ';
			postfix += infix[i];
			if (x != 0) {
				while (x != 0) {
					postfix += '!';
					x--;
				}
			}
		}
		else if (infix[i] == '(')
			myStack.push(infix[i]);
		else if (infix[i] == '!') {
			x = 1;
		}
		else if (infix[i] == '!' || infix[i] == '&' || infix[i] == '|' && myStack.empty() == true)
			myStack.push(infix[i]);
		else if (infix[i] == '!' || infix[i] == '&' || infix[i] == '|' && myStack.empty() == false) {
			int j = 1;
			
			while (j == 1) {
				if (precedence(infix[i]) >= precedence(myStack.top())) {
					//postfix += ' ';
					postfix += myStack.top();
					myStack.pop();
				}
				else if (precedence(infix[i]) < precedence(myStack.top()) || myStack.top() == '(') {
					j = -1;
					myStack.push(infix[i]);
				}
			}
			
		}	
		else if (infix[i] == ')') {
			int k = 1;
			while (k == 1) {
				if (myStack.top() == '(')
					k = -1;
				else {
					//postfix += ' ';
					postfix += myStack.top();
					myStack.pop();
				}
			}
		}
		/*else {
			return 1;
		}*/

	}
	while (myStack.empty() == false) {
		if(myStack.top() == '&' || myStack.top() == '|' || myStack.top() == '!')
			postfix += myStack.top();
		myStack.pop();
	}
	// NOW WE EVALUATE POSTFIX EXPRESSION
	stack<bool> evaluateStack;
	bool holder1, holder2, holder3;
	for (int i = 0; i < postfix.length(); i++) {
		if (postfix[i] == 'T')
			evaluateStack.push(true);
		else if (postfix[i] == 'F')
			evaluateStack.push(false);
		else if (postfix[i] == '!') {
			bool k = !evaluateStack.top();
			evaluateStack.pop();
			evaluateStack.push(k);
		}
		else if (postfix[i] == '&') {
			holder1 = evaluateStack.top();
			evaluateStack.pop();
			holder2 = evaluateStack.top();
			evaluateStack.pop();
			holder3 = holder1 && holder2;
			evaluateStack.push(holder3);

		}
		else if (postfix[i] == '|') {
			holder1 = evaluateStack.top();
			evaluateStack.pop();
			holder2 = evaluateStack.top();
			evaluateStack.pop();
			holder3 = holder1 || holder2;
			evaluateStack.push(holder3);
		}
				
	}
	result = evaluateStack.top();
	return 0;
}

int precedence(char x) {
	if (x == '!')
		return 3;
	else if (x == '&')
		return 2;
	else if (x == '|')
		return 1;
	else
		return -1;
}
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

int main() {
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("T+F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}