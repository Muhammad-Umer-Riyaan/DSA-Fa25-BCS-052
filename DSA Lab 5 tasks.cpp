#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <stdexcept>

using namespace std;

// Generic Dynamic Stack implementation
template <typename T>
class DynamicStack {
private:
    T* arr;
    int capacity;
    int topIndex;

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicStack(int initialCapacity = 10) {
        capacity = initialCapacity;
        arr = new T[capacity];
        topIndex = -1;
    }

    ~DynamicStack() {
        delete[] arr;
    }

    void push(T val) {
        if (topIndex == capacity - 1) {
            resize();
        }
        arr[++topIndex] = val;
    }

    void pop() {
        if (!isEmpty()) {
            topIndex--;
        }
    }

    T peek() const {
        if (!isEmpty()) {
            return arr[topIndex];
        }
        throw runtime_error("Stack is empty");
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }
};

// ---------------------------------------------------------
// Lab Task 1: Check Balanced Brackets with Priority/Nesting
// ---------------------------------------------------------
bool isBalanced(const string& expr) {
    DynamicStack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } 
        else if (c == ')' || c == ']' || c == '}') {
            if (s.isEmpty()) return false;
            char top = s.peek();
            s.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return s.isEmpty();
}

// ---------------------------------------------------------
// Lab Task 2: Infix to Postfix Conversion using Dynamic Stack
// ---------------------------------------------------------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infixToPostfix(const string& infix) {
    DynamicStack<char> s;
    string postfix = "";

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isspace(c)) continue;

        if (isalnum(c)) {
            string operand = "";
            while (i < infix.length() && isalnum(infix[i])) {
                operand += infix[i];
                i++;
            }
            i--;
            postfix += operand + " ";
        }
        else if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            char matchingOpen = '(';
            if (c == ']') matchingOpen = '[';
            if (c == '}') matchingOpen = '{';

            while (!s.isEmpty() && s.peek() != matchingOpen) {
                postfix += string(1, s.peek()) + " ";
                s.pop();
            }
            if (!s.isEmpty()) {
                s.pop();
            }
        }
        else if (isOperator(c)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(c)) {
                postfix += string(1, s.peek()) + " ";
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.isEmpty()) {
        postfix += string(1, s.peek()) + " ";
        s.pop();
    }

    return postfix;
}

// ---------------------------------------------------------
// Lab Task 3: Evaluate Postfix Expression using Dynamic Stack
// ---------------------------------------------------------
double evaluatePostfix(const string& postfix, const unordered_map<string, double>& varValues) {
    DynamicStack<double> s;
    string token = "";

    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isspace(c)) {
            if (!token.empty()) {
                if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
                    s.push(stod(token));
                } else if (isOperator(token[0]) && token.length() == 1) {
                    if (s.size() < 2) throw runtime_error("Invalid postfix expression");
                    double val2 = s.peek(); s.pop();
                    double val1 = s.peek(); s.pop();
                    switch (token[0]) {
                        case '+': s.push(val1 + val2); break;
                        case '-': s.push(val1 - val2); break;
                        case '*': s.push(val1 * val2); break;
                        case '/': s.push(val1 / val2); break;
                        case '^': s.push(pow(val1, val2)); break;
                    }
                } else {
                    if (varValues.find(token) != varValues.end()) {
                        s.push(varValues.at(token));
                    } else {
                        throw runtime_error("Undefined variable: " + token);
                    }
                }
                token = "";
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            s.push(stod(token));
        } else if (isOperator(token[0]) && token.length() == 1) {
            if (s.size() < 2) throw runtime_error("Invalid postfix expression");
            double val2 = s.peek(); s.pop();
            double val1 = s.peek(); s.pop();
            switch (token[0]) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
                case '^': s.push(pow(val1, val2)); break;
            }
        } else {
            if (varValues.find(token) != varValues.end()) {
                s.push(varValues.at(token));
            } else {
                throw runtime_error("Undefined variable: " + token);
            }
        }
    }

    if (s.size() != 1) {
        throw runtime_error("Invalid postfix expression");
    }

    return s.peek();
}

int main() {
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "         DSA LAB 5 TASKS MENU          \n";
        cout << "========================================\n";
        cout << "1. Lab Task 1: Check Balanced Brackets\n";
        cout << "2. Lab Task 2: Infix to Postfix Conversion\n";
        cout << "3. Lab Task 3: Evaluate Postfix Expression\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string expr;
            cout << "Enter expression with brackets (e.g., [{()}]): ";
            getline(cin, expr);
            if (isBalanced(expr)) {
                cout << "Result: The expression is Balanced.\n";
            } else {
                cout << "Result: The expression is NOT Balanced.\n";
            }
        } 
        else if (choice == 2) {
            string infix;
            cout << "Enter infix expression (e.g., a + b * (c - d)): ";
            getline(cin, infix);
            string postfix = infixToPostfix(infix);
            cout << "Postfix Expression: " << postfix << "\n";
        } 
        else if (choice == 3) {
            string postfix;
            cout << "Enter space-separated postfix expression (e.g., a b + c *): ";
            getline(cin, postfix);

            unordered_map<string, double> varValues;
            int n;
            cout << "Enter number of variables: ";
            cin >> n;
            cin.ignore();

            for (int i = 0; i < n; i++) {
                string var;
                double val;
                cout << "Enter variable name (e.g., a): ";
                cin >> var;
                cout << "Enter value for " << var << ": ";
                cin >> val;
                cin.ignore();
                varValues[var] = val;
            }

            try {
                double result = evaluatePostfix(postfix, varValues);
                cout << "Evaluated Numerical Result: " << result << "\n";
            } catch (exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        }
    } while (choice != 4);

    [cite: 2]cout << "Exiting program. Good luck with your lab!\n";
    return 0;
}
