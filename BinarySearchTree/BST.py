# Binary Search Tree implementation

class Node:
    def __init__(self, data=None) -> None:
        self.data = data
        self.right = None
        self.left = None


class BST:
    def __init__(self, data=None):
        if data:
            self.root = Node(data)
            self.size = 1
        else:
            self.root = Node()
            self.size = 0
    
    def _insert(self, node: Node, data):
        if node is None:
            return Node(data)
        
        if(data > node.data):
            node.right = self._insert(node.right, data=data)

        if(data < node.data):
            node.left = self._insert(node.left, data=data)

        return node 
    
    def _remove(self, node: Node, data):
        if node is None:
            return
        
        if data > node.data:
            node.right = self._remove(node.right, data)
        elif data < node.data:
            node.left = self._remove(node.left, data)
        else:
            # Here the node is found!
            if node.left is None:
                temp = node.right or None
                del node
                return temp
            elif node.right is None:
                temp = node.left
                del node
                return temp
            else:
                # We need to find successor!
                succ: Node = node.right

                while succ.left is not None:
                    succ = succ.left
                
                node.data = succ.data
                self._remove(node.right, succ.data)
                return node
                
        # This return is essential as it makes the node structure stable
        return node

    def _contains(self, node: Node, data):
        if node == None:
            return False

        if node.data == data:
            return True
        
        if data > node.data:
            return self._contains(node.right, data)
        if data < node.data:
            return self._contains(node.left, data)
        
    def _preOrderTraversal(self, node: Node):
        if(node  == None):
            return
        print(node.data)
        self._preOrderTraversal(node.left)
        self._preOrderTraversal(node.right)

    def contains(self, data):
        if data is None:
            return ValueError("Invalid Data!")

        return self._contains(self.root, data)

    def getRoot(self):
        return self.root.data

    def insert(self, data):
        if data is None:
            return ValueError("Data must be valid!")
        else:
            self.root = self._insert(self.root, data=data)
            self.size = self.size + 1
            return 
        
    def remove(self, data):
        if data == None:
            return ValueError("Invalid Data.")
        elif self.size == 0:
            return IndexError("Tree is empty!")
        else:
            if self.contains(data) == True:
                self._remove(self.root, data)
                self.size = self.size - 1
                return 
            else:
                return KeyError("Key doesn't exist!")

    def preOrderTraversal(self):
        if self.root is None:
            print("Tree is empty!")
            return;
        self._preOrderTraversal(self.root)


tree = BST(12)
tree.insert(11)
tree.insert(1)
tree.insert(11)
tree.insert(20)
tree.remove(100)
tree.preOrderTraversal()
    