"""
    AVL Tree is Balanced Binary Tree.
    In AVL tree max height of the tree is always log(n)
    which makes the searching O(log n) even in worst case.
"""

class Node:
    def __init__(self, data) -> None:
        self.data = data
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self, data=None) -> None:
        if data is not None:
            self.root = Node(data)
            self.size = 1
        else:
            self.root = None
            self.size == 0

    def _getRightSuccessor(self, node: Node) -> Node:
        successor = node.right
        while successor.left:
            successor = successor.left
        return successor

    def _getLeftSuccessor(self, node: Node) -> Node:
        successor = node.left
        while successor.right:
            successor = successor.right
        return successor

    def _getBalanceFactor(self, node: Node) -> int:
        if node is None:
            return 0
        return self.height(node.left) - self.height(node.right)
    
    def _rightRotate(self, A: Node) -> Node:
        B: Node = A.left
        Br: Node = B.right

        B.right = A
        A.left = Br

        A.height = 1 + max(self.height(A.right), self.height(A.left))
        B.height = 1 + max(self.height(B.right), self.height(B.left))        

        return B
    
    def _leftRotate(self, A: Node) -> Node:
        B: Node = A.right
        Br: Node = B.left

        B.left = A
        A.right = Br

        A.height = 1 + max(self.height(A.right), self.height(A.left))
        B.height = 1 + max(self.height(B.right), self.height(B.left))        

        return B
    
    def _updateHeight(self, node: Node) -> None:
        node.height = 1 + max(self.height(node.left), self.height(node.right))
        return
    
    def _balanceNode(self, node: Node, data) -> Node:

        balance = self._getBalanceFactor(node)

        if balance > 1 and data < node.left.data:
            return self._rightRotate(node)
        
        if balance > 1 and data > node.left.data:
            node.left = self._leftRotate(node.left)
            return self._rightRotate(node)
        
        if balance < -1 and data < node.right.data:
            node.right = self._rightRotate(node.right)
            return self._leftRotate(node)
        
        if balance < -1 and data > node.right.data:
            return self._leftRotate(node)

        return node


    def _insert(self, node: Node, data) -> Node:
        if node is None:
            return Node(data)
        
        if data > node.data:
            node.right = self._insert(node.right, data)
        if data < node.data:
            node.left = self._insert(node.left, data)
        
        # Update height of the node.
        self._updateHeight(node)

        # Balance the node if it is unbalanced!
        return self._balanceNode(node, data)

    def _remove(self, node: Node, data) -> Node:
        if node is None:
            return None
        
        if data > node.data:
            node.right = self._remove(node.right, data)
        elif data < node.data:
            node.left = self._remove(node.left, data)
        else:
            # Here node is found!
            # Should not return here. as there is work to perform below!
            if node.left is None:
                temp = node.right
                node = temp
            elif node.right is None:
                temp = node.left
                node = temp
            else:
                # This node has two children
                successor = self._getRightSuccessor(node)
                node.data = successor.data
                node.right = self._remove(node.right, successor.data)

                # If you want to use left node instead, uncomment these lines
                # successor = self._getLeftSuccessor(data)
                # node.data = successor.data
                # self._remove(node.right, successor.data)

        # If the node is None there is no work to do.
        if node is None:
            return node
        
        # Else Perform the work to keep tree balanced
        # Work to be done to keep balance of the height among tree nodes;

        # Update the height of the node
        self._updateHeight(node)

        # Balance the node
        return self._balanceNode(node, data)


    def _preOrderTraversal(self, node: Node) -> None:
        if node is None:
            return
        print(node.data)
        self._preOrderTraversal(node.left)
        self._preOrderTraversal(node.right)
    
    def _find(self, node: Node, data) -> Node:
        if node is None:
            return None
        if node.data == data:
            return node
        if data > node.data:
            return self._find(node.right, data)
        if data < node.data:
            return self._find(node.left, data)

    def getHeightOf(self, data):
        node = self._find(self.root, data)
        if node is None:
            raise KeyError("Invalid Key!")
        return self.height(node)

    def height(self, node: Node) -> int:
        if node is None:
            return 0
        return node.height
    
    def contains(self, data):
        return self._find(self.root, data) is not None

    def preOrderTraversal(self) -> None:
        if self.root is None:
            raise KeyError("Tree is empty!")
        else:
            self._preOrderTraversal(self.root)

    def getRoot(self):
        if self.root is not None:
            raise KeyError("The tree is empty.")
        else:
            return self.root.data
    
    def insert(self, data):
        if data is None:
            raise ValueError("Invalid Value!")
        else:
            self.root = self._insert(self.root, data)

    def remove(self, data):
        if not self.contains(data):
            raise KeyError("There is no key!")
        self._remove(self.root, data)


tree = AVLTree(12)

tree.insert(23)
tree.insert(3)
tree.insert(2)
tree.insert(10)
tree.insert(1)
tree.insert(12)
tree.insert(19)
tree.insert(17)
tree.insert(7)
tree.insert(5)
tree.insert(6)
tree.insert(11)
tree.remove(1)
tree.remove(7)
tree.remove(12)
tree.remove(6)
print("Height:", tree.getHeightOf(3))

tree.preOrderTraversal()