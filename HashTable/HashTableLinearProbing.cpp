#include <iostream>
#include <string>


using namespace std;


struct HashNode
{
    string key;
    int value;

    HashNode()
    {
        this->key = "";
        this->value = 0;
    }

    HashNode(string key, int value)
    {
        this->key = key;
        this->value = value;
    }    
};


class HashTable
{  
    private:
        int size;
        int BUCKET;
        double growth_rate;
        double max_load_factor;
        HashNode* table;

        int hash_function(string key)
        {
            int total = 0;

            for(char ch : key)
                total += int(ch);

            total += key.length();

            return total % BUCKET;
        }

        int linear_probe(int index)
        {
            return (2 * index + 1) % BUCKET;
        }

        double get_load_factor() {return size / double(BUCKET); }

        bool rehashing_required() {return get_load_factor() >= max_load_factor; }

        void rehash()
        {
            cout << "Rehashing...." << endl;
            int old_bucket_size = BUCKET;
            BUCKET = BUCKET * growth_rate;
            HashNode* old_table = table;
            table = new HashNode[BUCKET];
            this->size = 0;

            for(int i=0; i<old_bucket_size; i++)
            {   
                HashNode node = old_table[i];
                insert(node.key, node.value);
            }

            delete old_table;
        }

    public:
        HashTable()
        {
            this->BUCKET = 7;
            this->size = 0;
            this->growth_rate = 2.0;
            this->max_load_factor = 0.667;
            this->table = new HashNode[BUCKET];
        }
  
        void insert(string key, int value)
        {
            HashNode* new_node = new HashNode(key, value);
            int index = hash_function(key);

            while(table[index].key != "")
            {
                index = linear_probe(index);
                cout << "Linear Probing worked!" << index << endl;
            }

            table[index] = *new_node;
            size++;

            if(rehashing_required())
                rehash();
        }

        void print()
        {
            for(int i=0; i<BUCKET; i++)
            {
                cout << table[i].key << ": " << table[i].value << endl;
            }
        }
};



int main (int argc, char * argv[])
{
    HashTable table;
    table.insert("Alisher", 32);
    table.insert("Farhod", 22);
    table.insert("Nodir", 30);
    table.insert("Shoqosim", 42);
    table.insert("Murod", 12);
    table.insert("Ortiq", 52);
    table.print();

    return 0;
}