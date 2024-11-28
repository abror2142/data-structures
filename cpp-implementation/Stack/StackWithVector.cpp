#include <iostream>
#include <vector>

using namespace std;


template <typename T> class Stack {
    private:
        vector<T>* arr;
    
    public:
        Stack()
        {
            this->arr = new vector<T>;
        }

        int get_size() {return this->arr->size(); }

        bool empty() {return this->arr->empty(); }

        int top() {return this->arr->at(this->arr->size() - 1); }

        void push(T data)
        {
            this->arr->push_back(data);
        }

        void pop()
        {
            this->arr->pop_back();
        }

        void print_stack()
        {
            if(this->empty())
                cout << "Stack is Empty!" << endl;
            else
            {
               
                for(auto it = this->arr->rbegin(); it != this->arr->rend(); it++)
                {
                    cout << *it << endl;
                }
            }
        }
};


int main(int argc, char * argv[])
{
    Stack<char> stack;
    stack.push('A');
    stack.push('B');
    stack.push('E');
    stack.push('X');
    stack.pop();
    stack.print_stack();
    cout << "Stack Size: " << stack.get_size() << endl;
}