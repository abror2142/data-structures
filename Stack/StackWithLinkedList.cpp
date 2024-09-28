#include <iostream>

using namespace std;

template <typename T> struct Node {
    T data; 
    Node* next;

    Node(T new_data)
    {
        this->data = new_data;
        this->next = nullptr;
    }
};


template <typename T> class Stack {
    private:
        int size;
        Node<T>* head;
    
    public:
        Stack()
        {
            this->size = 0;
            this->head = nullptr;
        }

        Stack(int data)
        {
            Node<T>* new_node = new Node<T>(data);
            this->head = new_node;
            this->size = 1;
        }

        int get_size() {return this->size; }

        bool empty() {return this->size == 0; }
    
        int top() {return this->head->data; }

        void push(T data)
        {
            Node<T>* new_node = new Node<T>(data);
           
            if(this->head == nullptr)
            {
                this->head = new_node;
            } else 
            {
                new_node->next = this->head;
                this->head = new_node;
            }

            this->size = this->size + 1;
        }

        void pop()
        {
            if(this->head == nullptr)
                cout << "Error: List has no elements!" << endl;
            else{
                Node<T>* temp = this->head; // keep pointer to delete later
                this->head = this->head->next;

                delete temp;
                this->size = this->size - 1;
            }
        }

        void print()
        {   
            if(this->empty())
                cout << "Stack is empty!" << endl;
            else
            {
                cout << "Stack: " << endl;
                Node<T>* current = this->head;

                while(current != nullptr)
                {
                    cout << current->data << " " << endl;
                    current = current->next;
                }     
            }
        }
};

int main(int argc, char * argv[]) 
{
    Stack<char> stack('A');
    stack.push('H');
    stack.push('C');
    stack.pop();
    stack.print();
    cout << "\nStack Size: " << stack.get_size() << endl;
    return 0;
}