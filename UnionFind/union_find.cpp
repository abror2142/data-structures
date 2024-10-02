#include <iostream>
#include <map>

using namespace std;


template <typename T> struct Node
{
    int rank;
    T data;
    Node* parent;

    Node(T d)
    {
        this->rank = 0;
        this->data = d;
        this->parent = nullptr;
    }
};


template <typename T> class DisjointSet
{
    private:
        map<T, Node<T>*>* mp;

    public:
        DisjointSet()
        {
            this->mp = new map<T, Node<T>*>;
        }

        void make_set(T data)
        {
            Node<T>* node = new Node<T>(data);
            node->parent = node;
            this->mp->insert({data, node});  
        }

        void make_set(int len, T arr[])
        {
            if(len <= 0)
                cout << "Error: The arr is empty!";
            else 
            {
                Node<T>* root;
                for(int i=0; i<len; i++)
                {
                    Node<T>* node = new Node<T>(arr[i]);
                    if(i == 0){
                        root = node;
                        node->rank = 1;
                    }
                    node->parent = root;
                    this->mp->insert({arr[i], node});
                }
            }

        }

        void union_sets(T data1, T data2)
        {
            Node<T>* node1 = mp->at(data1);
            Node<T>* node2 = mp->at(data2);

            Node<T>* rp1 = find_set(node1);
            Node<T>* rp2 = find_set(node2);

            if(T(rp1->data) == T(rp2->data))
                return;
            
            if(int(rp1->rank) >= int(rp2->rank))
            {
                rp1->rank = 
                    rp1->rank == rp2->rank 
                    ? rp1->rank + 1
                    : rp1->rank;
                rp2->parent = rp1;
            }
            else    
                rp1->parent = rp2;

        }

        Node<T>* find_set(Node<T>* node)
        {
            Node<T>* parent = node->parent;
            
            if(parent->data == node->data)
                return parent;
            
            node->parent = find_set(node->parent);

            return node->parent;
        }

        T find_representative(T data)
        {
            Node<T>* node = mp->at(data);
            Node<T>* representative = find_set(node);
            cout << "Rank of " << representative->data << " is: " << representative->rank << endl;
            return representative->data;
        }
};


int main(int argv, char * argc[])
{
    DisjointSet<int> ds;
    ds.make_set(1);
    ds.make_set(2);
    ds.make_set(3);
    int arr[] = {5, 3, 9};
    ds.make_set(3, arr);
    ds.union_sets(1, 2);
    ds.union_sets(1, 3);
    ds.union_sets(9, 1);

    int rp = ds.find_representative(9);
    cout << "9 -> " << rp << endl;
    return 0;
}