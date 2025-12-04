#include <iostream>
#include <stack>
#include <string>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string postfix_to_infix(const std::string& postfix) {
    std::stack<std::string> st;

    for (char c : postfix) {

        if (c == ' ') continue;

        
        if (!isOperator(c)) {
            st.push(std::string(1, c));
        }
        else {
           
            auto b = st.top(); st.pop();
            auto a = st.top(); st.pop();

            std::string expr = "(" + a + " " + c + " " + b + ")";
            st.push(expr);
        }
    }

    return st.top();
}

int main() {
    std::string postfix = "123+4*+";
    std::cout << postfix_to_infix(postfix) << "\n";
}
