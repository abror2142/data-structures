#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;


bool is_valid_braces(string s)
{
    map<char, char> b;
    b['}'] = '{';
    b[')'] = '(';
    b[']'] = '[';

    stack<char> stack;
    for(char a : s)
        if(!stack.empty() && stack.top() == b[a])
            stack.pop();
        else
            stack.push(a);    
    bool is_empty = stack.empty();
    cout << "\nStack: " << endl;
    while(!stack.empty()){
        cout << stack.top() << endl;
        stack.pop();
    }
    return is_empty;
}

int main(int argc, char * argv[])
{
    string s = "";
    cin >> s;
    if(is_valid_braces(s))
        cout << "valid";
    else
        cout << "invalid"; 
    return 0;
}