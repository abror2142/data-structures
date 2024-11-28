#include <iostream>

using namespace std;


template <typename T> class MinHeap
{
    private:
        int heap_size;
        int max_heap_size;
        T* heap;

        int get_parent(int index) {return (index - 1) / 2; }

        int get_left(int index) {return 2 * index + 1; }

        int get_right(int index) {return 2 * index + 2; }

        void swap(int i, int j)
        {
            T temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        void heapify(int index) // = bubble_down
        {
            int smallest = index;
            int left = get_left(index);
            int right = get_right(index);

            if(left < heap_size && heap[left] < heap[smallest])
                smallest = left;
            
            if(right < heap_size && heap[right] < heap[smallest])
                smallest = right;
            
            if(smallest != index)
            {
                swap(index, smallest);
                heapify(smallest);
            }
        }   

        void bubble_up(int index)
        {
            if(index > 0)  // ensures there is a valid parent index (goes until root)
            {
                int parent = get_parent(index);
                if(heap[index] < heap[parent]){  
                    swap(index, parent);  // easily swap with private swap method
                    bubble_up(parent);  // recursively bubble up
                }
            }
        }

    public:
        MinHeap(int max_size)
        {
            this->max_heap_size = max_size;
            this->heap = new T[max_size];
            this->heap_size = 0;
        }

        int get_size() {return heap_size; }
        
        void insert(T data)
        {
            int index = heap_size;
            heap[index] = data;
            heap_size++;

            bubble_up(index);
        }

        void decrease_key(int index, T data)
        {
            if(index < 0 || index >= heap_size)
                cout << "Error: Invalid Index!";
            else
            {
                heap[index] = data;
                
                // when decreased we must bubble_up
                bubble_up(index);
            }
        }

        void extract_min()
        {
            if(heap_size == 0)
                cout << "Error: Heap is empty!" << endl;
            else if(heap_size == 1)
            {
                heap[0] = T{};
                heap_size--;
            }else {
                swap(0, heap_size-1);
                heap[heap_size-1] = T{};
                heap_size--;
                
                heapify(0);
            }
        }

        T get_min()
        {
            if(heap_size == 0){
                cout << "Heap is empty!" << endl;
                return T{};
            }
            return heap[0];
        }

        void print()
        {
            if(heap_size == 0)
                cout << "Heap is empty!";
            else
            {
                cout << "Heap: ";
                for(int i=0; i<heap_size; i++)
                    cout << heap[i] << " ";
                cout << endl;
            }
        }
        
};


int main(int argc, char * argv[])
{
    MinHeap<int> heap(100);
    heap.insert(10);
    heap.insert(1);
    heap.insert(19);
    heap.insert(0);
    heap.extract_min();
    heap.insert(7);
    heap.insert(8);
    heap.insert(9);
    heap.decrease_key(5, 7);
    cout << "Heap Size: " << heap.get_size() << endl;
    heap.print();
    cout << "Heap Min: " << heap.get_min() << endl;
    return 0;
}