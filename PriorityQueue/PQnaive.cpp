#include <iostream>

using namespace std;

// In computer science, a priority queue is an abstract data type similar to a 
// regular queue or stack abstract data type. Each element in a priority queue 
// has an associated priority. In a priority queue, elements with high priority 
// are served before elements with low priority.  --- wiki

//This means we could implement it using MaxHeap

/*
    PQ operations:
        -- add(element)
        -- poll() => extract_max in MaxHeap
        -- empty()
        -- bubble_up() = swim() 
        -- bubble_down() = sink()
*/

template <typename T> class PQueue 
{
    private:
        int size;
        int max_size;
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

        void bubble_up(int index)
        {
            if(index > 0)  // ensures there is a parent.
            {
               int parent = get_parent(index);
                if(heap[index] > heap[parent])
                {
                    swap(index, parent);
                    bubble_up(parent);
                }
            }
        }

        void bubble_down(int index)
        {
            int largest = index;
            int left = get_left(index);  // left children
            int right = get_right(index); // right children

            if(left < size && heap[left] > heap[largest])
                largest = left;
            
            if(right < size && heap[right] > heap[largest])
                largest = right;
            
            if(largest != index)
            {
                swap(largest, index);
                bubble_down(largest);
            }
        }

    public:
        PQueue(int max_queue_size)
        {   
            this->max_size = max_queue_size;
            this->size = 0;
            this->heap = new T[max_queue_size];
        }

        T peek() {return heap[0]; }

        bool empty() {return size == 0; }

        void add(T element)
        {  
            if(size == max_size)
                cout << "Overflow: Queue is full!";
            else{
                int index = size;
                heap[index] = element;
                size++;

                bubble_up(index);
            }
        }

        void poll()
        {
            if(size == 0)
                cout << "Error: Queue is Empty!" << endl;
            else if(size == 1){
                heap[0] = T{};
                size--;
            } else
            {
                swap(0, size-1);
                heap[size-1] = T{};
                size--;

                bubble_down(0);
            }
        }

        void print()
        {
            if(size == 0)
                cout << "Queue is Empty!" << endl;
            else
            {
                cout << "Queue: ";
                for(int i=0; i<size; i++)
                    cout << heap[i] << " -> ";
                cout << endl;
            }
        }
};


int main(int argc, char * argv[])
{
    PQueue<int> queue(100);
    queue.add(89);
    queue.add(70);
    queue.add(90);
    queue.add(19);
    queue.add(100);
    queue.add(10);
    queue.poll();
    queue.poll();
    queue.poll();
    queue.poll();
    queue.print();
    return 0;
}