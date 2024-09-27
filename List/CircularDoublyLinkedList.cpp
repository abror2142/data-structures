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


class CircularDoublyLinkedList {
    private:
        int size;
        Node* head;
        Node* tail;
    
    public:

        CircularDoublyLinkedList()
        {
            this->size = 0;
            this->head = nullptr;
            this->tail = nullptr;
        }

        CircularDoublyLinkedList(int num)
        {
            Node* new_node = new Node(num);
            this->size = 1;
            this->head = new_node;
            this->tail = new_node;

            this->head->prev = this->tail;
            this->tail->next = this->head;
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

                this->head->prev = this->tail;
                this->tail->next = this->head;
            } else 
            {
                new_node->next = this->head;
                this->head->prev = new_node;
                new_node->prev = this->tail;
                this->tail->next = new_node;
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

                this->head->prev = this->tail;
                this->tail->next = this->head;
            } else 
            {
                this->tail->next = new_node;
                new_node->next = this->head;
                this->head->prev = new_node;
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

                //edge cases will be handled by add_head and add_tail 
                previous->next = new_node;
                new_node->prev = previous;
                new_node->next = current;
                current->prev = new_node;
                this->size = this->size + 1;
            }
        }

        void remove_head()
        {
            if(this->head == nullptr && this->tail == nullptr){
                cout << "Uninitialized list structure!";
            } else
            {
                Node* temp = this->head;  // to delete after losing pointer to head
                if(this->head->next == nullptr)  // this means head is the only node
                {
                    this->head = nullptr;
                    this->tail = nullptr;
                } else
                {
                    Node* after_head = this->head->next;
                    after_head->prev = this->tail;
                    this->tail->next = after_head;
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
                    before_tail->next = this->head;
                    this->head->prev = before_tail;
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
            if(this->head->prev == this->head){ // means only one node
                cout << "List: " << this->head->data << endl;
            } else {

                Node* current = this->head;
                
                do {
                    cout << current->data << " ";
                    current = current->next;
                } while(current != this->head);

                cout << "\n";
            }
        }

        void print_backwards()
        {
            if(this->head->prev == this->head){ // means only one node
                cout << "List: " << this->head->data << endl;
            } else {
                Node* current = this->tail;
                do {
                    cout << current->data << " ";
                    current = current->prev;
                } while(current != this->tail);
                cout << "\n";
            }
        }
};


int main(int argc, char * argv[])
{
    CircularDoublyLinkedList list(4);
    list.add_head(1);
    list.add_tail(2);
    list.add_at(1, 12);
    list.remove_head();
    list.remove_tail();
    list.add_head(30);
    list.add_at(2, 66);
    list.remove_at(2);
    cout << "Forwrds:\t";
    list.print_forwards();
    cout << "Backwards:\t";
    list.print_backwards();
    cout << "Is Empty?: " << list.is_empty();
}