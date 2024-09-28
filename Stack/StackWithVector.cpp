#include <iostream>
#include <vector>

using namespace std;


class Stack {
    private:
        vector<int>* arr;
    
    public:
        Stack()
        {
            this->arr = new vector<int>;
        }

        int get_size() {return this->arr->size(); }

        bool empty() {return this->arr->empty(); }

        int top() {return this->arr->at(this->arr->size() - 1); }

        void push(int data)
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
    Stack stack;
    stack.push(10);
    stack.push(2);
    stack.push(12);
    stack.push(4);
    stack.pop();
    stack.print_stack();
    cout << "Stack Size: " << stack.get_size() << endl;
}