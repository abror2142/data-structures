#include <iostream>

using namespace std;


class DynamicArray {
    private:
        int size;
        int capacity;
        int growth_rate;
        int* array = NULL;
    
        void grow_array() 
        {
            int new_capacity = this->capacity * this->growth_rate;
            cout << "Growing..." << this->capacity << " --> " << new_capacity << "\n";

            int* new_array = new int[new_capacity];
            for(int i=0; i<this->size; i++)
                new_array[i] = this->array[i];

            int* arr = this->array;
            this->array = new_array;
            delete[] arr;
            this->capacity = new_capacity;
        }

        void shrink_array() 
        {
            int new_capacity = this->capacity/this->growth_rate;
            cout << "Shrinking..." << this->capacity << " --> " << new_capacity << "\n";
            int* new_array = new int[new_capacity];

            for(int i=0; i<this->size; i++)
                new_array[i] = this->array[i];

            int* arr = this->array;
            this->array = new_array;
            delete[] arr;
            this->capacity = new_capacity;
        }

        bool is_shrink_needed()
        {
            // find ratio of capacity/size
            double ratio = double(this->capacity)/this->size;
            return ratio >= this->growth_rate;
        }

    public:
        DynamicArray()
        {
            capacity = 1;
            size = 0;
            growth_rate=2; 
            array = new int[capacity];
        }

        DynamicArray(int init_capacity)
        {

            this->capacity = init_capacity;
            size = 0;
            array = new int[capacity];
        }

        DynamicArray(int init_capacity, int num)
        {
            // Initialize with a number;
            this->capacity = init_capacity;
            this->array = new int[init_capacity];
            for(int i=0; i<init_capacity; i++)
                this->array[i] = num;
            this->size = init_capacity;
        }

        int getSize() {return this->size; }

        int getCapacity() {return this->capacity; }

        void push_back(int element) 
        {
            if(this->size == this->capacity)
                grow_array();

            this->array[this->size] = element;
            
            this->size += 1;
        }

        void pop_back() 
        {
            if(this->size == 0)
                cout << "The array is empty!";
            
            this->array[this->size-1] = NULL;

            this->size = this->size - 1;

            // is shrinking needed? => function
            if(this->is_shrink_needed())
                this->shrink_array();
        }

        int search(int element) {return 0; }

        void insert_at(int index, int element) 
        {
            // checking for index error
            try {
                if(index <= this->size && index >= 0){
                    // checking if growing the capacity is needed
                    if(this->size == this->capacity)
                        this->grow_array();
                    
                    for(int i=this->size-1; i>=index; i--)
                        this->array[i+1] = this->array[i];
                    
                    this->array[index] = element;
                    this->size = this->size + 1;
                }else{
                    throw 505;
                }
            }catch(int error_code){
                cout << "\nError while inserting an element\n";
                cout << "Error code: " << error_code;
            }
        }  

        void delete_at(int index) 
        {
            // checking for index error
            try {
                if(index < this->size && index >=0){
                    int* new_array = new int[this->capacity];
                    for(int i=0, j=0; i<this->size;)
                        if(i==index)
                            i++;
                        else{
                            new_array[j] = this->array[i];
                            i++;
                            j++;
                        }
                    int* arr = this->array;
                    this->array = new_array;
                    delete[] arr;
                    this->size = this->size-1;
                } else {
                    throw 505;
                }
            } catch(int error_code) {
                 cout << "\nError while deleting an element\n";
                cout << "Error code: " << error_code;
            }
        }

        void print_array() 
        {
            for(int i=0; i<this->size; i++)
                cout << this->array[i] << " ";
        }

        bool is_empty() {return this->size == 0; }

};

int main(int args, char * argv[]) {
    DynamicArray a(10, 2);
    a.print_array();
    a.insert_at(11, 4);
    a.delete_at(12);
    cout << "\nSize: " << a.getSize();
    return 0;
}