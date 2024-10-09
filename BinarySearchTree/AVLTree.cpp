#include <iostream>

using namespace std;

template <typename T> struct Node {
    T data;
    Node* left;
    Node* right;
    int height;

    Node (T data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }

    Node ()
    {   
        this->data = T{};
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
    }
};


template <typename T> class AVLTree
{
    private:
        int size;
        Node<T>* root;

        int height(Node<T> *node)
        {
            if(node == nullptr)
                return 0;
            return node->height;
        }

        int get_balance(Node<T> *node)
        {
            if(node == nullptr)
                return 0;
            
            return height(node->left) - height(node->right);
        }

        Node<T> *right_rotate(Node<T> *A)
        {
            Node<T> *B = A->left;
            Node<T> *Br = B->right;

            A->left = Br;
            B->right = A;

            A->height = 1 + max(height(A->left), height(A->right));            
            B->height = 1 + max(height(B->left), height(B->right));       

            return B;     
        }

        Node<T> *left_rotate(Node<T> *A)
        {
            Node<T> *B = A->right;
            Node<T> *Bl = B->left;

            A->right = Bl;
            B->left = A;

            A->height = 1 + max(height(A->left), height(A->right));            
            B->height = 1 + max(height(B->left), height(B->right));       

            return B;
        }

        Node<T> *find_left_successor(Node<T> *node)
        {
            Node<T> *temp = node;

            while(temp && temp->right)
                temp = temp->right;
            
            return temp;
        }

        Node<T> *find_right_successor(Node<T> *node)
        {
            Node<T> *temp = node;
            
            while(temp && temp->left)
                temp = temp->left;
            
            return temp;
        }

        Node<T>* insert(Node<T>* node, T data)
        {
            // Base Case
            if(node == nullptr) return new Node<T>(data);

            if(data > node->data)
                node->right = insert(node->right, data);
            else if(data < node->data)
                node->left = insert(node->left, data);
            else
                return node;
            
            // updates heights after insertion;
            // new inserted node will get 0, its parents will be incremented.
            node->height = 1 + max(height(node->left), height(node->right));

            int balance = get_balance(node);

            if(balance > 1 && data < node->left->data)
                return right_rotate(node);
            
            if(balance < -1 && data > node->right->data)
                return left_rotate(node);

            if(balance > 1 && data > node->left->data){
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }

            if(balance < -1 && data < node->right->data){
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }

            return node;

        }
        
        Node<T>* remove(Node<T>* node, T data)
        {
            if(node == nullptr) return node;

            if(data > node->data)
                node->right = remove(node->right, data);
            
            if(data < node->data)
                node->left = remove(node->left, data);
            else {
                // 4 cases!;
                Node<T>* temp = nullptr;

                if(node->right == nullptr)
                {
                    temp = node->left;
                    delete node;
                    return temp;
                }
                if(node->left == nullptr)
                {
                    temp = node->right;
                    delete node;
                    return temp;
                }

                if(node->right && node->left)
                {
                    Node<T> *successor = nullptr;
                    successor = find_right_successor(node->right);

                    // Uncomment these two commented lines below to use left successor as preference
                    // successor = find_left_successor(node->left);
                    
                    node->data = successor->data;
                    
                    // node->left = remove(node->left, successor->data);

                    // Comment this line if you want to use left successor
                    node->right = remove(node->right, successor->data);
                } 
            }
            
             node->height = height(node->left) + 
                   height(node->right) + 1;

            int balance = get_balance(node);

            if (balance > 1 && 
                get_balance(node->left) >= 0)
                return right_rotate(node);

            if (balance > 1 && 
                get_balance(root->left) < 0) {
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }

            if (balance < -1 && 
                get_balance(node->right) <= 0)
                return left_rotate(node);


            if (balance < -1 && 
                get_balance(node->right) > 0) {
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }


            return node;
        }

        void in_order_traversal(Node<T>* node)
        {
            if(node == nullptr) return;
            in_order_traversal(node->left);
            cout << node->data << " ";
            in_order_traversal(node->right);
        }

        void pre_order_traversal(Node<T>* node)
        {
            if(node == nullptr) return;
            cout << node->data << " ";
            pre_order_traversal(node->left);
            pre_order_traversal(node->right);
        }

        Node<T>* find(Node<T>* node, T data)
        {
            if(node == nullptr) return nullptr;

            if(data > node->data)
                return find(node->right, data);
            
            if(data < node->data)
                return find(node->left, data);

            // This means node->data == data
            return node;
        }

        int get_height(Node<T> *node)
        {
            if(node == nullptr) return 0;

            int left = get_height(node->left) + 1;
            int right = get_height(node->right) + 1;

            return left > right ? left : right;
        }
        
    public:
        AVLTree ()
        {
            this->size = 0;
            this->root = new Node<T>();
        }

        AVLTree (T data)
        {
            this->size = 1;
            this->root = new Node<T>(data);
        }
        
        int get_height()
        {
            return get_height(root);
        }

        bool contains(T data)
        {
            return find(root, data) != nullptr;
        }

        bool insert(T data)
        {
            if(data == T{})
                return false;

            // Calls recursive private insert() method.
            if(!contains(data)){
                root = insert(root, data);
                size++;
                return true;
            }

            // This is executed when we want to enter already existing data.
            return false;
        }

        T remove(T data)
        {
            if(data == T{}) return T{};

            if(size == 0) {
                cout << "The tree is empty!" << endl;
                return T{};
            }    

            if(!contains(data)){
                cout << "There is no such data" << endl;
                return T{};
            }

            remove(root, data);
            return data;
        }

        void in_order_traversal()
        {
            if(size > 0)
                in_order_traversal(root);
            else
                cout << "The tree is empty!" << endl;
            return;
        }

        void pre_order_traversal()
        {
            if(size > 0)
                pre_order_traversal(root);
            else
                cout << "The tree is empty!" << endl;
            return;
        }
};


int main(int argc, char * argv[])
{
    AVLTree<int> tree(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);

    //tree.remove(10);
    cout << "Height: " << tree.get_height() << endl;
    tree.pre_order_traversal();
    return 0;
}