#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

int main() {

    ifstream input("input.txt");
    ofstream output("output.tmp");

    stack<char> st;
    char c;
    int line_number = 1;
    bool error_found = false;

    while (input.get(c)) {
        if (c == '\n') {
            line_number++;
        }
        else if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) {
                cout << "Error on line " << line_number << ": unexpected closing bracket " << c << endl;
                error_found = true;
                break;
            }

            char opening_bracket = st.top();
            if ((opening_bracket == '(' && c == ')') ||
                (opening_bracket == '[' && c == ']') ||
                (opening_bracket == '{' && c == '}')) {
                st.pop();
            }
            else {
                cout << "Error on line " << line_number << ": expected " << (opening_bracket == '(' ? ')' : (opening_bracket == '[' ? ']' : '}')) << " but found " << c << endl;
                error_found = true;
                break;
            }
        }
    }

    if (!error_found && !st.empty()) {
        char opening_bracket = st.top();
        cout << "Error: " << (opening_bracket == '(' ? ')' : (opening_bracket == '[' ? ']' : '}')) << " expected but end of file found" << endl;
        error_found = true;
    }

    if (!error_found) {
        cout << "No errors found" << endl;
    }

    input.close();
    output.close();

    return 0;
}