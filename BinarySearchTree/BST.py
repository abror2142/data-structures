# Binary Search Tree implementation

class Node:
    def __init__(self, data=None):
        self.data = data
        self.right = None
        self.left = None


class BST:
    def __init__(self, data=None):
        if data:
            self.root = Node(data)
            self.size = 1
        else:
            self.root = None
            self.size = 0

    def _insert(self, node: Node, data):
        if node is None:
            return Node(data)
        
        if(data > node.data):
            node.right = self._insert(node.right, data=data)

        if(data < node.data):
            node.left = self._insert(node.left, data=data)

        return node 

    def _getRightSuccessor(seld, node: Node):
        successor = node
        while successor.left is not None:
            successor = successor.left
        return successor

    def _getLeftSuccessor(seld, node: Node):
        successor = node
        while successor.right is not None:
            successor = successor.right
        return successor
    
    def _remove(self, node: Node, data):
        if node is None:
            return
        
        if data > node.data:
            node.right = self._remove(node.right, data)
        elif data < node.data:
            node.left = self._remove(node.left, data)
        else:
            # Here the node to be removed is found!
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
                succ: Node = self._getRightSuccessor(node)
                node.data = succ.data
                self._remove(node.right, succ.data)

                # Uncomment these lines to use Left successor instead of right one.
                # succ: Node = self._getLeftSuccessor(node)
                # node.data = succ.data
                # self._remove(node.left, succ.data)
                
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
            raise ValueError("Invalid Data!")

        return self._contains(self.root, data)

    def getRoot(self):
        return self.root.data

    def insert(self, data):
        if data is None:
            raise ValueError("Data must be valid!")
        else:
            self.root = self._insert(self.root, data=data)
            self.size = self.size + 1
            return 
        
    def remove(self, data):
        if data == None:
            raise ValueError("Invalid data.")
        elif self.size == 0:
            raise IndexError("Tree is empty!")
        else:
            if self.contains(data) == True:
                self._remove(self.root, data)
                self.size = self.size - 1
                return
            else:
                raise KeyError("Key doesn't exist!")

    def preOrderTraversal(self):
        if self.root is None:
            print("Tree is empty!")
            return;
        self._preOrderTraversal(self.root)


tree = BST(12)

tree.insert(11)
tree.insert(1)
tree.insert(111)
tree.insert(20)
tree.remove(12)
tree.preOrderTraversal()

print(tree.contains(11))