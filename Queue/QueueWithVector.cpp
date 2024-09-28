#include <iostream>
#include <vector>

using namespace std;


template <typename T> class Queue {
    private:
        vector<T>* arr;
    
    public:
        Queue()
        {
            this->arr = nullptr;
        }

        Queue(T data)
        {
            this->arr = new vector<T>;
            this->arr->push_back(data);
        }

        int get_size() {return this->arr->size(); }

        bool empty() {return this->arr->empty(); }

        void enqueue(T data)
        {
            this->arr->push_back(data);
        }

        void dequeue()
        {
            this->arr->erase(this->arr->begin());
        }

        void print()
        {
            if(this->empty())
                cout << "Queue is empty!" << endl;
            else 
            {  
                cout << "Queue: ";
                for(T a : *this->arr)
                    cout << a << " -> ";
            }
        }
};


int main(int argc, char * argv[])
{
    Queue<char> queue('A');
    queue.enqueue('B');
    queue.dequeue();
    queue.enqueue('G');
    queue.print();
    return 0;
}