#include <iostream>

using namespace std;


struct Node {
    int data;
    Node* next;

    Node(int d) {
        this->data = d;
        this->next = nullptr;
    }
};

class SinglyLinkedList {
    private:
        int size;
        Node* head;
        Node* tail;
    
    public:
        SinglyLinkedList()
        {
            this->size = 0;
            this->head = nullptr;
            this->tail = nullptr;
        }

        SinglyLinkedList(int data)
        {
            Node* new_node = new Node(data);
            this->head = new_node;
            this->tail = new_node;
            this->size = 1;
        }

        int get_size() {return this->size; }

        bool is_empty() {return this->size == 0; }

        Node* get_head() {return this->head; }

        Node* get_tail() {return this->tail; }

        void add_head(int data)
        {
            Node* new_node = new Node(data);

            if(this->head == nullptr)
            {
                this->head = new_node;
                this->tail = new_node;
            } else
            {
                new_node->next = this->head;
                this->head = new_node;
            }

            this->size = this->size + 1;
        }

        void add_tail(int data)
        {
            Node* new_node = new Node(data);
            if(this->tail == nullptr)
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

        void add_at(int index, int data)
        {
            // Indexing starts with 0!
            if(index == 0)
                this->add_head(data);
            else if(index == this->size)
                this->add_tail(data);
            else if(index > 0 && index < this->size)
            {
                Node* new_node = new Node(data);
                Node* current = this->head;
                
                for(int i=0; i<index-1; i++)
                {
                    current = current->next;
                }

                new_node->next = current->next;
                current->next = new_node;

                this->size = this->size + 1;
            }
        }

        void remove_head()
        {
            if(this->head == nullptr)
                cout << "List is uninitialized!";
            else 
            {
                Node* temp = this->head;
                
                if(this->head->next != nullptr)
                {
                    this->head = temp->next;
                } else 
                {
                    this->head = nullptr;
                    this->tail = nullptr;
                }

                delete temp;
                this->size = this->size - 1;
            }
        }

        void remove_tail()
        {
            if(this->tail == nullptr)
                cout << "Uninitialized list!" << endl;
            else {
                Node* current = this->head;
                Node* previous = nullptr;

                while(current != this->tail){
                    previous = current;
                    current = current->next;
                }

                if(previous == nullptr){
                    this->head = nullptr;
                    this->tail = nullptr;
                } else {
                    previous->next = nullptr;
                    this->tail = previous;
                }

                delete current;
                this->size = this->size - 1;
            }
        }
        
        void remove_at(int index)
        {
            if(index == 0)
                this->remove_head();
            else if(index == this->size - 1)
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

                previous->next = current->next;
                
                delete current;
                this->size = this->size - 1;
            }
        }

        void print_list()
        {
            if(this->head == nullptr){
                cout << "List is empty!" << endl;
            } else {
                cout << "List: ";
                Node* current = this->head;
                while(current != nullptr)
                {
                    cout << current->data << " ";
                    current = current->next;
                }
                cout << "\n";
            }
        }
};


int main(int argc, char * argv[])
{
    SinglyLinkedList list(12);
    list.add_head(23);
    list.add_head(1);
    list.add_tail(11);
    list.remove_head();
    list.remove_tail();
    list.add_at(1, 2);
    list.remove_at(1);
    list.print_list();
    return 0;
}