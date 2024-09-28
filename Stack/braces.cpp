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
    bool is_valid = true;

    // works but not good for long string
    // for(char a : s)
    //     if(!stack.empty() && stack.top() == b[a])
    //         stack.pop();
    //     else
    //         stack.push(a);    

    // is_valid = stack.empty();

    // better solution: detects early mismatch, so stops in first mismatch encounter 
    for(char a : s)
    {
       if(b[a]){
        if(stack.empty())
        {
            is_valid = false;
            break;
        }else {
            if(stack.top() == b[a])
            {
                stack.pop();
            }else
            {
                is_valid = false;
                break;
            }
        }
       } else 
       {
        stack.push(a);
       }
    }
    // valid string would complete pop and push cycle without leaving a char in stack
    if(!stack.empty())
        is_valid = false;

    cout << "\nStack: " << endl;
    while(!stack.empty()){
        cout << stack.top() << endl;
        stack.pop();
    }
    return is_valid;
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