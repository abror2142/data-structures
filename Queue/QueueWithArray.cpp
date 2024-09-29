#include <iostream>

using namespace std;


template <typename T> class Queue
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
            
            T* temp = this->array;
            this->array = new_array;
            this->capacity = new_capacity;
            delete[] temp;
        }

    public:
        Queue()
        {
            this->size = 0;
            this->capacity = 1;
            this->growth_rate = 2;
            this->array = new T[this->capacity];
        }

        Queue(T data)
        {
            this->capacity = 1;
            this->growth_rate = 2;
            this->array = new T[this->capacity];
            this->array[0] = data;
            this->size = 1;
        }

        bool empty() {return this->size == 0; }

        int get_size() {return this->size; }

        void enqueue(T data)
        {
            if(this->size == this->capacity)
                this->grow();

            this->array[this->size] = data;
            this->size = this->size + 1;
        }

        void dequeue()
        {
            // Have to move elements except first; -> costly O(n)
            if(this->size <= 0)
                cout << "Error: Queue is empty!";
            else
            {
                for(int i=0; i<this->size; i++)
                {
                    this->array[i] = this->array[i+1];
                }

                this->size = this->size - 1;

                // shrink if the capacity/size is mode than growth rate;
                if(this->capacity/double(this->size) >= this->growth_rate)
                    this->shrink();
            }
        }

        void print()
        {
            if(this->size == 0)
                cout << "Queue is Empty!";
            else 
            {
                cout << "Queue: ";
                for(int i=0; i<this->size; i++)
                {
                    cout << this->array[i] << " -> ";
                }
                cout << endl;

                cout << "Size: " << this->size << endl;
                cout << "Capacity: " << this->capacity << endl;
                cout << "Growth rate: " << this->growth_rate << endl;
            }
        }
};


int main(int argc, char * argv[])
{
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(1);
    queue.enqueue(11);
    queue.dequeue();
    queue.dequeue();
    queue.enqueue(3);
    queue.enqueue(9);
    queue.enqueue(5);
    queue.enqueue(7);
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.print();
    return 0;
}