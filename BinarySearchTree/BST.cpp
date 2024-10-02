#include <iostream>

using namespace std;


template <typename T> struct Node {
    T data;
    Node* left;
    Node* right;

    Node(T d)
    {
        this->data = d;
        this->left = nullptr;
        this->right = nullptr;
    }
};


template <typename T> class BinarySearchTree
{
    private:
        Node<T>* root;
        int size;
    
    public:
        BinarySearchTree()
        {
            this->root = nullptr;
            this->size = 0;
        }

        BinarySearchTree(T data)
        {
            Node<T>* new_node = new Node<T>(data);
            this->root = new_node;
            this->size = 1;
        }

        Node<T>* get_root() {return this->root; }

        void add(T data)
        {
            Node<T>* new_node = new Node<T>(data);
            if(this->root == nullptr)
            {
                root = new_node;
                size++;
                return;
            }

            Node<T>* node = this->root;
            Node<T>* parent = nullptr;

            while(node != nullptr){
                if(data > node->data){
                    parent = node;
                    node = node->right;
                }else {
                    parent = node;
                    node = node->left;                
                }
            }

            if(data > parent->data)
                parent->right = new_node;
            else
                parent->left = new_node;
            
            size++;
            return;
        }

        Node<T>* remove(Node<T>* node, T data)
        {
            if(node == nullptr)
                return node;
           
            if(data > node->data)
                node->right = remove(node->right, data);  
            else if(data < node->data)
                node->left = remove(node->left, data);
            else
            {
                if(node->left == nullptr){
                    Node<T>* temp = node->right;
                    delete node;
                    return temp;
                }
                else if(node->right == nullptr){
                    Node<T>* temp = node->left;
                    delete node;
                    return temp;
                }
                if(node->left && node->right)
                {
                    // Let's find rightmost node;
                    Node<T>* rightmost = node->right;

                    while(rightmost && rightmost->left)
                        rightmost = rightmost->left;
                    
                    node->data = rightmost->data;
                    node->right = remove(node->right, rightmost->data);
                } 
            }
            return node;
        }

        Node<T>* contains(Node<T>* node, T data)
        {
            if(node)
            {
                if(node->data == data)
                    return node;
                
                if(data > node->data)
                    return find(node->right, data);
                else   
                    return find(node->left, data);
            }
            else
                return nullptr;
        }

        void in_order_traversal(Node<T>* node)
        {
            if(node == nullptr) return;
            in_order_traversal(node->left);
            cout << node->data << " ",
            in_order_traversal(node->right);
        }
};


int main (int argc, char * argv[])
{
    BinarySearchTree<int> tree(12);
    Node<int>* root = tree.get_root();

    tree.add(5);
    tree.add(15);
    tree.add(13);
    tree.add(1);

    tree.remove(root, 12);

    tree.in_order_traversal(root);
    return 0;
}