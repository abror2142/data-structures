#include <iostream>
#include <vector>

using namespace std;


struct Person
{   
    string name;
    int age;
    string phone;

    Person(string name, int age, string phone)
    {
        this->name = name;
        this->age = age;
        this->phone = phone;
    }
};


struct Node
{
    Person* person;
    Node* next;

    Node(Person* person)
    {   
        this->person = person;
        this->next = nullptr;
    }
};


class LinkedList
{
    private:
        Node* root;
        int size;

    public:
        LinkedList()
        {
            this->root = nullptr;
            this->size = 0;
        }

        LinkedList(Person* person)
        {
            this->root = new Node(person);
            this->size = 1;
        }

        void add_to_tail(Person* person)
        {
            Node* new_node = new Node(person);

            if(this->root == nullptr)
            {
                root = new_node;
                size++;
                return;
            }

            Node* current = this->root;

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
                Node* current = root;
                cout << "List: ";
                while(current)
                {
                    Person* person = current->person;
                    cout << person->name << " " << person->age << " " << person->phone << " -> ";
                    current = current->next;
                }
                cout << endl;
            }
        }
};


class HashTableSeperateChaining
{
    private:
        int BUCKET; // hash table size;
        LinkedList* table;

        int hashFunction(Person* person)
        {
            string name = person->name;
            int age = person->age;
            string phone = person->phone;
            
            int total = 0;
            for(char ch : name)
                total += int(ch);

            for(char ch : phone)
                total += int(ch);
            
            total += age;
            
            return total % BUCKET;
        }
        

    public:
        HashTableSeperateChaining(int bucket)
        {
            this->BUCKET = bucket;
            this->table = new LinkedList[bucket];
        }

        void insert(Person* person)
        {
            int key = hashFunction(person);
            table[key].add_to_tail(person);
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

    HashTableSeperateChaining table(3);

    for(auto person : people)
        table.insert(person);

    table.print();

    return 0;    
}