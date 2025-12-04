#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string prefix_to_infix(const std::string& prefix) {
    std::stack<std::string> st;

  
    for (int i = prefix.size() - 1; i >= 0; --i) {
        char c = prefix[i];

        
        if (c == ' ') continue;

        if (!isOperator(c)) {
            
            st.push(std::string(1, c));
        }
        else {
            
            auto a = st.top(); st.pop();
            auto b = st.top(); st.pop();
            std::string expr = "(" + a + " " + c + " " + b + ")";
            st.push(expr);
        }
    }

    return st.top();
}

int main() {
    std::string prefix = "*+56-72";
    std::cout << prefix_to_infix(prefix) << "\n";
}
