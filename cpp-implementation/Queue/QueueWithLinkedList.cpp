#include <iostream>

using namespace std;


template <typename T> struct Node
{
    T data;
    Node<T>* next;

    Node()
    {
        this->data = NULL;
        this->next = nullptr;
    }

    Node(T new_data)
    {
        this->data = new_data;
        this->next = nullptr;
    }
};


template <typename T> class Queue
{
    private:
        int size;
        Node<T>* head;
        Node<T>* tail;

    public:
        Queue()
        {
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;
        }

        Queue(T data)
        {
            Node<T>* new_node = new Node<T>(data);
            this->head = new_node;
            this->tail = new_node;
            this->size = 1;
        }

        int get_size() {return this->size; }

        bool empty() {return this->get_size() == 0; }

        void enqueue(T data)
        {
            // Add to tail as the last node;
            Node<T>* new_node = new Node<T>(data);

            if(this->head == nullptr)
            {
                this->head = new_node;
                this->tail = new_node;
            } else 
            {
                this->tail->next = new_node;
                this->tail = new_node;
            }

            this->size = this->size + 1;
        }

        void dequeue()
        {
            if(this->empty())
                cout << "Queue is empty!";
            else
            {
                Node<T>* temp = this->head;

                this->head = this->head->next;
                
                delete temp;
                this->size = this->size - 1;
            }
        }

        void print()
        {
            if(this->empty())
                cout << "Queue is empty!" << endl;
            else 
            {
                Node<T>* current = this->head;

                cout << "Queue: ";
                while(current != nullptr)
                {
                    cout << current->data << " -> ";
                    current = current->next;
                }
            }
        }
};


int main(int argc, char * argv[])
{
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(30);
    queue.enqueue(1);
    queue.dequeue();
    queue.enqueue(4);
    queue.dequeue();
    queue.print();
    return 0;
}