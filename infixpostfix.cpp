#include <iostream>
#include <stack>
#include <string>

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infix_to_postfix(const std::string& infix) {
    std::stack<char> st;
    std::string output;

    for (char c : infix) {

        
        if (c == ' ') continue;

        
        if (isalnum(c)) {
            output += c;
        }
        
        else if (c == '(') {
            st.push(c);
        }
        
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                output += st.top();
                st.pop();
            }
            st.pop();
        }
        
        else if (isOperator(c)) {
            while (!st.empty() && priority(st.top()) >= priority(c)) {
                output += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    
    while (!st.empty()) {
        output += st.top();
        st.pop();
    }

    return output;
}

int main() {
    std::string inf = "1+(2+3)*4";
    std::cout << infix_to_postfix(inf) << "\n";
}
