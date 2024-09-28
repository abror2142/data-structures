#include <iostream>
// Stack using vector seems a bit overkill since it has more methods than needed.
// So let's implement it using built in static array by adding growing functionality!

using namespace std;


template <typename T> class Stack
{
    private:
        int size;
        int capacity;
        double growth_rate;
        T* array;

        void grow()
        {
            int new_capacity = this->capacity * this->growth_rate;
            T* new_array = new T[new_capacity];
            
            for(int i=0; i<this->size; i++)
                new_array[i] = this->array[i];
            
            this->array = new_array;
            this->capacity = new_capacity;
        }

        void shrink()
        {
            int new_capacity = this->capacity/this->growth_rate;
            T* new_array = new T[new_capacity];
            
            for(int i=0; i<this->size; i++)
                new_array[i] = this->array[i];
            
            this->array = new_array;
            this->capacity = new_capacity;
        }

    public:
        Stack()
        {
            this->size = 0;
            this->capacity = 1;
            this->growth_rate = 2.0;
            this->array = new T[this->capacity];
        }

        T top() {this->array[this->size - 1]; }
        
        int get_size() {return this->size; }

        bool empty() {return this->size == 0; }

        void push(T data)
        {
            if(this->size == this->capacity)
                this->grow();
            
            this->array[this->size] = data;
            this->size = this->size + 1;
        }

        void pop()
        {
            if(this->empty())
                cout << "Error: Stack is empty!" ;
            else 
            {
                this->array[this->size-1] = NULL;
                this->size = this->size - 1;

                if(this->size/double(this->capacity) > this->growth_rate)
                    this->shrink();
            }
        }

        void print()
        {
            if(this->empty())
                cout << "Stack is empty!" << endl;
            else
            {
                cout << "Stack: " << endl;
                for(int i=this->size-1; i>=0; i--)
                {
                    cout << this->array[i] << endl;
                }
            }
        }
} ; 


int main(int argc, char * argvp[])
{
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(11);
    stack.pop();
    stack.pop();
    stack.pop();
    
    stack.print();
    return 0;  
}