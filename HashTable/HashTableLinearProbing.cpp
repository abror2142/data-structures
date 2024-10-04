#include <iostream>
#include <numeric>

using namespace std;

bool is_prime(int n) 
{ 
    // Corner cases 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
   
    // This is checked so that we can skip  
    // middle five numbers in below loop 
    if (n%2 == 0 || n%3 == 0) return false; 
   
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return false; 
   
    return true; 
} 

int next_prime(int N)
{
 
    // Base case
    if (N <= 1)
        return 2;
 
    int prime = N;
    bool found = false;
 
    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;
 
        if (is_prime(prime))
            found = true;
    }
 
    return prime;
}


template <typename K, typename V> struct HashNode
{
    K key;
    V value;

    HashNode(K key, V value)
    {
        this->key = key;
        this->value = value;
    }

    HashNode()
    {
        this->key = K{};
        this->value = V{};
    }

    size_t hash_value()
    {
        return hash<K>()(key) ^ hash<V>()(value);  
    }
};


template <typename K, typename V> class HashTable
{
    private:
        int LOAD_CONSTANT = 3;
        double MAX_LOAD_FACTOR = 0.665;

        int size;
        int capacity;
        HashNode<K, V>* table;

        int linear_probing(int index)
        {
            // index + b  is very easy; doesn't require capacity checks;
            // k * index is failing everytime with 0; so I avoided using it;
            // k * index + b will do the job, only if capacity is the prime number.

            // I tried making k and index coprime and using k * index, result is loop when index=0;

            // Globally available; k defines acceleration and ramdomness while choosing next slot;
            // increasing by only b might not provide ramdomness, noticable in large tables;

            int k = LOAD_CONSTANT; 
            int b = 1; // makes sure every node is visited; handles index=0 case;

            return (k * index + b) % capacity;
        }

        void adjust_capacity()
        {   
            int prime_num = next_prime(capacity);

            // Somehow LOAD_CONSTANT can be equal to LOAD_CONSTANT; avoid that to have coprimes;
            if(LOAD_CONSTANT == prime_num)
                prime_num = next_prime(prime_num);
            
            capacity = prime_num;
        }

        void resize_table(int old_capacity)
        {
            HashNode<K, V>* old_table = table;
            table = new HashNode<K, V>[capacity];
            size = 0;

            for(int i=0; i<old_capacity; i++)
                if(old_table[i].key != K{})
                    insert(old_table[i].key, old_table[i].value);
        }

        void rehash()
        {
            cout << "Rehashing..." << endl;
            int old_capacity = capacity; 
            
            capacity *= 2;
            adjust_capacity();
            
            resize_table(old_capacity);
        }

        int hash_function(K key)
        {
            cout << "Hashing... " << key << endl;
            int a = hash<K>()(key) % capacity;
            cout << "Hashed value: " << a << endl;
            return a;
        }

    public:
        HashTable()
        {
            this->capacity = 5;
            this->table = new HashNode<K, V>[capacity];
            this->size = 0;
        }

        HashTable(int capacity)
        {
            this->capacity = capacity;
            this->table = new HashNode<K, V>[capacity];
            this->size = 0;
        }

        bool contains(K key) {return search(key) != V{}; }
        
        bool empty() {return size == 0; }

        int size() {return size; }

        void insert(K key, V value)
        {
            if(size/double(capacity) >= MAX_LOAD_FACTOR)
                rehash();

            HashNode<K, V>* node = new HashNode<K, V>(key, value);
            int index = this->hash_function(key);

            while(table[index].key != K{}){
                index = linear_probing(index);
            }

            table[index] = *node;
            size++;
        }

        V search(K key)
        {
            int index = hash_function(key);

            while(table[index].key != K{} && table[index].key != key)
                index = linear_probing(index);
            
            if(table[index].key == K{})
                return V{};
            else 
                return table[index].value; 
        }

        void remove(K key)
        {
            // TOMBSTONE method to delete node and keep consistency among nodes!
            
        }

        void print()
        {
            for(int i=0; i<capacity; i++)
            {
                cout << "Key: " << table[i].key << "\tValue: " << table[i].value << endl;
            }
        }
};


int main(int argc, char * argv[])
{
    HashTable<string, int> table;
    table.insert("Nodir", 70);
    table.insert("Qodir", 75);
    table.insert("Botir", 40);
    table.insert("Baxrom", 12);
    table.insert("Bahodir", 22);
    table.insert("Bahodiadasdr", 22);
    table.insert("Bahodiadasr", 22);
    table.insert("Bahodisdsdr", 22);
    table.insert("Bahodidsr", 22);
    table.print();

    cout << table.contains("Qodir") << endl;
    cout << table.contains("Nodirali") << endl;

    HashNode<string, int> node("Abduvali", 43);
    return 0;
}