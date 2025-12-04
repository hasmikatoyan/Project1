#include <iostream>
#include <stack>
#include <algorithm>

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

std::string infix_to_prefix(const std::string& infix) {
    std::string rev = infix;
    std::reverse(rev.begin(), rev.end());

   
    for (char& c : rev) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    std::stack<char> st;
    std::string postfix;

    for (char c : rev) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }
        else { 
            while (!st.empty() && priority(st.top()) >= priority(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    
    std::reverse(postfix.begin(), postfix.end());
    return postfix;
}

int main() {
    std::cout << infix_to_prefix("(5+6)*(7-2)") << "\n";
}
