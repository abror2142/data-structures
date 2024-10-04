#include <iostream>

using namespace std;


class FenwickTree
{
    private:
        int size;
        int* array;
        int* tree;

        int lsb(int index)
        {
            return index & -index;
        }

         void construct_tree()
        {
            for(int i=1; i<size; i++)
            {

                int parent = i + lsb(i);
                if(parent <= size)
                    cout <<  " Index " << i << " " << tree[i] << "\tParent: " << parent << " " << tree[parent] << endl;
                    tree[parent] += tree[i];
            }
        }

    public:
        FenwickTree(int size, int arr[])
        {
            this->size = size;
            this->array = new int[size];
            this->tree = new int[size+1];

            for(int i=0; i<size; i++){
                array[i] = arr[i];
                tree[i+1] = arr[i];
            }

            construct_tree();
        }

        int prefix_sum(int index)
        {
            // adds up to index!
            index = index + 1;
            int sum = 0;
            while(index != 0)
            {
                sum += tree[index];
                index -= lsb(index);
            }
            return sum;
        }

        int range_sum(int i, int j)
        {
            // j > i
            return prefix_sum(j) - prefix_sum(i-1);
        }

        void print()
        {
            cout << "Array: ";
            for(int i=0; i<size; i++)
            {
                cout << array[i] << " ";
            }

            cout << endl;

            cout << "Tree: ";
            for(int i=0; i<size; i++)
            {
                cout << tree[i] << " ";
            }

            cout << endl;
        }

       

};


int main(int argc, char * argv[])
{
    int arr[] = {1, 4, 9, -2, 7, 8, 12, 0, 3, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    FenwickTree tree(size, arr);
    tree.print();
    cout << tree.prefix_sum(4) << endl;
    cout << tree.range_sum(1,3) << endl;
    return 0;
}