#include <iostream>
#include <limits>

using namespace std;


/*
    Max Heap Operations:
        -- getMin()
        -- extractMin()
        -- increaseKey(index, new_val)
        -- insert(data)
        -- delete(index)
*/


template <typename T> class MaxHeap
{
    private: 
        int heap_size;
        int max_heap_size;
        T* heap;

        int get_parent(int index) {return (index - 1) / 2; }

        int get_left(int index) {return 2 * index + 1; }

        int get_right(int index) {return 2 * index + 2; }

        void heapify(int index)
        {
            int largest = index;
            int left = get_left(index);
            int right = get_right(index);

            if(left < this->heap_size && this->heap[left] > this->heap[largest])
                largest = left;
            
            if(right < this->heap_size && this->heap[right] > this->heap[largest])
                largest = right;

            if(largest != index)
            {
                swap(largest, index);
                heapify(largest);
            }            
        }

        void swap(int i, int j)
        {
            T temp = this->heap[i];
            this->heap[i] = this->heap[j];
            this->heap[j] = temp;
        }

    public:
        int get_size() {return this->heap_size; }

        MaxHeap(int max_size)
        {
            this->max_heap_size = max_size;
            this->heap_size = 0;
            this->heap = new T[this->max_heap_size];
        }

        void insert(T data)
        {
            int index = this->heap_size;
            this->heap[index] = data;
            this->heap_size = this->heap_size + 1;

            int parent = this->get_parent(index);
            while(index > 0 && data > this->heap[parent])
            {
                // swap(i, j)
                swap(index, parent);
                index = parent;
                parent = this->get_parent(index);
            }
        }

        void delete_at(int index)
        {
            this->increase_key(index, numeric_limits<int>::max());
            this->extract_max();
        }

        void increase_key(int index, T new_val)
        {
            if(index >= this->heap_size || index < 0){
                cout << "Error: Invalid index!" << endl;
                return;
            }
            this->heap[index] = new_val;

            int parent = this->get_parent(index);
            while(index > 0 && new_val > this->heap[parent])
            {
                // swap(i, j)
                swap(index, parent);
                index = parent;
                parent = this->get_parent(index);
            }
        }

        T extract_max()
        {
            if(heap_size == 0){
                cout << "Error: Heap is empty!";
                return T{};
            }
            else if(heap_size == 1)
            {
                this->heap_size = this->heap_size - 1;
                return this->heap[0];
            }
            
            T root = this->heap[0];
            this->swap(0, this->heap_size-1);
            this->heap[this->heap_size - 1] = T{};
            this->heap_size = this->heap_size - 1;
            this->heapify(0);

            return root;
        }

        void print()
        {
            if(this->heap_size == 0)
                cout << "Heap is empty!";
            else
            {
                cout << "Heap: ";
                for(int i=0; i<this->heap_size; i++)
                    cout << this->heap[i] << " ";
                cout << endl;
            }
        }
};

int main(int argc, char * argvp[])
{
    MaxHeap<int> heap(100);
    heap.insert(20);
    heap.insert(12);
    heap.insert(30);
    heap.insert(2);
    heap.insert(3);
    heap.insert(23);
    cout << "Size: " << heap.get_size() << endl;
    heap.insert(15);
    heap.increase_key(3, 10);
    heap.delete_at(1);
    heap.print();
    return 0;
}