#include <iostream>
#include <vector>

using namespace std;


class Person
{   
    private:
        string name;
        int age;
        string phone;

    public:
        Person(string name, int age, string phone)
        {
            this->name = name;
            this->age = age;
            this->phone = phone;
        }

        int hash_value()
        {
            int total = 0;
            for(char ch : name)
                total += int(ch);

            for(char ch : phone)
                total += int(ch);
            
            total += age;
            return total;
        }

        string stringified()
        {
            string s = to_string(age);
            s = name + " " + s;
            return s;
        }
};


template <typename T> struct Node
{
    T* person;
    Node* next;

    Node(T* person)
    {   
        this->person = person;
        this->next = nullptr;
    }
};


template <typename T> class LinkedList
{
    private:
        Node<T>* root;
        int size;

    public:
        LinkedList()
        {
            this->root = nullptr;
            this->size = 0;
        }

        LinkedList(T* person)
        {
            this->root = new Node<T>(person);
            this->size = 1;
        }

        void add_to_tail(T* person)
        {
            Node<T>* new_node = new Node<T>(person);

            if(this->root == nullptr)
            {
                root = new_node;
                size++;
                return;
            }

            Node<T>* current = this->root;

            while(current->next)
            {
                // I should implement comparision of data to avoid duplicate value insertion!!!
                current = current->next;
            }

            current->next = new_node;
            size++;
        }

        void print()
        {
            if(root == nullptr)
                cout << "This List is Empty!" << endl;
            else
            {
                Node<T>* current = root;
                cout << "List: ";
                while(current)
                {
                    T* person = current->person;
                    cout << person->stringified() << " -> ";
                    current = current->next;
                }
                cout << endl;
            }
        }
};


template <typename T> class HashTableSeperateChaining
{
    private:
        int BUCKET; // hash table size;
        LinkedList<T>* table;

        int hashFunction(T* person)
        {        
            return  person->hash_value() % BUCKET;
        }
        

    public:
        HashTableSeperateChaining(int bucket)
        {
            this->BUCKET = bucket;
            this->table = new LinkedList<T>[bucket];
        }

        void insert(T* person)
        {
            int key = hashFunction(person);
            table[key].add_to_tail(person);
        }

        bool contains(T*)
        {

        }

        void print()
        {
            for(int i=0; i<BUCKET; i++)
            {
                table[i].print();
            }
        }

};


int main(int argc, char * argv[])
{
    vector<Person*> people;
    people.push_back(new Person("William Fiset", 30, "+123456789"));
    people.push_back(new Person("Abrorbek Ismoilov", 24, "+987654321"));
    people.push_back(new Person("Tushar Roy", 32, "+6789054321"));
    people.push_back(new Person("Abdul Bari", 40, "+0987612345"));

    HashTableSeperateChaining<Person> table(3);

    for(auto person : people)
        table.insert(person);

    table.print();

    return 0;    
}