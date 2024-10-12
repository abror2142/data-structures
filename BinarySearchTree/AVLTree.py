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
    
    def _insert(self, node: Node, data) -> Node:
        if node is None:
            return Node(data)
        
        if data > node.data:
            node.right = self._insert(node.right, data)
        if data < node.data:
            node.left = self._insert(node.left, data)
        
        node.height = 1 + max(self.height(node.left), self.height(node.right))

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

    def _preOrderTraversal(self, node: Node) -> None:
        if node is None:
            return
        self._preOrderTraversal(node.left)
        print(node.data)
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
print("Height:", tree.getHeightOf(3))

tree.preOrderTraversal()