#include <iostream>

using namespace std;


struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int num)
    {
        this->data = num;
        this->next = nullptr;
        this->prev = nullptr;
    }
};


class LinkedList {
    private:
        int size;
        Node* head;
        Node* tail;
    
    public:

        LinkedList()
        {
            this->size = 0;
            this->head = nullptr;
            this->tail = nullptr;
        }

        LinkedList(int num)
        {
            Node* new_node = new Node(num);
            this->size = 1;
            this->head = new_node;
            this->tail = new_node;
        }

        bool is_empty()
        {
            return this->size == 0;
        }

        int get_size()
        {
            return this->size;
        }

        void add_head(int num)
        {
            Node* new_node = new Node(num);

            // Testing for uninitialized case
            if(this->head == nullptr and this->tail == nullptr)
            {
                this->head = new_node;
                this->tail = new_node;
            } else 
            {
                new_node->next = this->head;
                this->head->prev = new_node;
                this->head = new_node;
            }
            // Incrementing size by 1
            this->size = this->size + 1;
        }

        void add_tail(int num)
        {
            Node* new_node = new Node(num);

            // Testing for uninitialized case
            if(this->head == nullptr and this->tail == nullptr)
            {
                this->head = new_node;
                this->tail = new_node;
            } else 
            {
                this->tail->next = new_node;
                new_node->prev = this->tail;
                this->tail = new_node;
            }
            // Incrementing size by 1
            this->size = this->size + 1;
        }

        void add_at(int index, int num)
        {
            // Indexing starts from 0!
            if(index == 0)
                this->add_head(num);
            else if (index == this->size)
                this->add_tail(num);
            else if (index > 0 && index < this->size)
            {
                Node* new_node = new Node(num);

                Node* current = this->head;
                Node* previous = nullptr; 

                for(int i=0; i<index; i++)
                {
                    previous = current;
                    current = current->next;
                }

                if(previous != nullptr) //there is no nullptr case as it will be add_head
                {
                    previous->next = new_node;
                    new_node->prev = previous;
                    new_node->next = current;
                    current->prev = new_node;
                    this->size = this->size + 1;
                } 
            }
        }

        void remove_head()
        {
            if(this->head == nullptr && this->tail == nullptr){
                cout << "Uninitialized list structure!";
            } else
            {
                Node* temp = this->head;  //to delete after losing pointer
                if(this->head->next == nullptr)  // this means head is the only node
                {
                    this->head = nullptr;
                    this->tail = nullptr;
                } else
                {
                    Node* after_head = this->head->next;
                    after_head->prev = nullptr;
                    this->head = after_head;
                }
                delete temp;
                this->size = this->size - 1;
            }
        }

        void remove_tail()
        {
            if(this->head == nullptr && this->tail == nullptr)
            {
                cout << "Uninitialized list structure!\n";
            } else
            {
                Node* temp = this->tail;

                if(this->tail->prev == nullptr) // list consists of only one node
                {
                    this->tail = nullptr;
                    this->head = nullptr;
                } else
                {
                    Node* before_tail = this->tail->prev;
                    before_tail->next = nullptr;
                    this->tail = before_tail;
                }

                delete temp;
                this->size = this->size - 1;
            }
        }

        void remove_at(int index)
        {
            if(index == 0)
                this->remove_head();
            else if(index == this->size-1)
                this->remove_tail();
            else if(index > 0 && index < this->size-1)
            {
                Node* current = this->head;
                Node* previous = nullptr;

                for(int i=0; i<index; i++)
                {
                    previous = current;
                    current = current->next;
                }

                Node* next = current->next;
                previous->next = next;
                next->prev = previous;

                delete current;
                this->size = this->size - 1;
            }
        }

        void print_forwards()
        {
            Node* current = this->head;
            while(current != nullptr)
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << "\n";
        }

        void print_backwards()
        {
            Node* current = this->tail;
            while(current != nullptr)
            {
                cout << current->data << " ";
                current = current->prev;
            }
            cout << "\n";
        }
};


int main(int argc, char * argv[])
{
    LinkedList list(4);
    list.add_head(1);
    list.add_tail(12);
    list.remove_head();
    list.remove_tail();
    list.add_at(0, 1);
    list.add_at(1, 2);
    list.add_at(3, 7);
    list.remove_at(1);
    list.remove_at(2);
    list.remove_at(1);
    cout << "Forwrds:\t";
    list.print_forwards();
    cout << "Backwards:\t";
    list.print_backwards();
    cout << "Is Empty?: " << list.is_empty();
}