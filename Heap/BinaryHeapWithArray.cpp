#include <iostream>

using namespace std;


template <typename T> class BinaryHeap
{
    private:
        int max_heap_size;
        int heap_size;
        T* heap;
    
        int get_parent(int index) {return (index - 1)/2; }

        int get_right_child(int index) {return index * 2 + 1; }
        int get_left_child(int index) {return index * 2 + 2; }

        void swap(int i, int j)
        {
            T data = this->heap[i];
            this->heap[i] = this->heap[j];
            this->heap[j] = data;
        }

        void bubble_up(int index)
        {
            int parent_index = this->get_parent(index);

            if(parent_index >= 0 && this->heap[index] < this->heap[parent_index])
            {
                // swap(i, j)
                this->swap(parent_index, index);
                bubble_up(parent_index);
            }
        }

        void bubble_down(int index)
        {
            int left_child = this->get_left_child(index);
            int right_child = this->get_right_child(index);
            
            int swap_index = left_child;

            if(right_child && this->heap[right_child] < this->heap[left_child]){
                swap_index = right_child;
            }

            if(swap_index && swap_index < this->heap_size)
            {
                this->swap(index, swap_index);
                bubble_down(swap_index);
            }
        }

    public:
        BinaryHeap()
        {
            this->max_heap_size = 100;
            this->heap_size = 0;
            this->heap = new T[this->max_heap_size];
        }

        BinaryHeap(T data)
        {
            this->max_heap_size = 100;
            this->heap = new T[this->max_heap_size];
            this->heap[0] = data;
            this->heap_size = 1;
        }

        void add(T data)
        {
            int index = this->heap_size; // index for new data;
            this->heap[index] = data;
            this->heap_size = this->heap_size + 1;
            
            // bubble up;
            this->bubble_up(index);
        }

        void poll()
        {
            if(this->heap_size == 0){
                cout << "Error: Heap is Empty!";
                return;
            }else if(this->heap_size == 1){
                this->heap[0] = NULL;
                this->heap_size = this->heap_size - 1;
            }
            else
            {
                this->swap(0, this->heap_size-1);
                this->heap[this->heap_size-1] = NULL;
                this->heap_size = this->heap_size - 1;

                this->bubble_down(0);
            }
        }

        void remove(T data)
        {
            for(int i=0; i<this->heap_size; i++)
            {
                if(this->heap[i] == data){
                    this->swap(i, this->heap_size-1);
                    this->heap[this->heap_size-1] = NULL;
                    this->heap_size = this->heap_size - 1;

                    bubble_up(i);
                    bubble_down(i);
                }
            }
        }

        void print()
        {
            if(this->heap_size == 0)
                cout << "Heap is empty!" << endl;
            else 
            {
                cout << "Heap: " << endl;
                for(int i=0; i<this->heap_size; i++)
                {
                    cout << this->heap[i] << " ";
                }
                cout << endl;
            }
        }
};


int main(int argc, char * argv[])
{
    BinaryHeap<int> heap(10);
    heap.add(8);
    heap.add(2);
    heap.add(0);
    heap.add(7);
    heap.add(18);
    heap.add(5);
    heap.add(9);
    heap.remove(2);
    heap.print();
    return 0;
}