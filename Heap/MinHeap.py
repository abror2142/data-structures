"""
    Min Heap is a data structure which root node is always 
    the lowest element in the given set.
"""

class MinHeap:
    def __init__(self, max_size: int=1000) -> None:
        self.heap = list()
        self.size = 0
        self.max_size = max_size

    def _getParent(self, index: int) -> int:
        return (index - 1) // 2
    
    def _getLeftChild(self, index: int) -> int:
        return 2 * index + 1
    
    def _getRightChild(self, index: int) -> int:
        return 2 * index + 2
    
    def _swap(self, i: int, j: int) -> None:
        temp = self.heap[i]
        self.heap[i] = self.heap[j]
        self.heap[j] = temp
        return

    def _swim(self, index: int) -> None:
        parent = self._getParent(index)
        
        if parent >= 0:
            if self.heap[index] < self.heap[parent]:
                self._swap(index, parent)
                self._swim(parent)
        return
    
    def _heapify(self, index: int) -> None:
        left = self._getLeftChild(index)
        right = self._getRightChild(index)

        smallest = index

        if left < self.size and self.heap[left] < self.heap[smallest]:
            smallest = left
        if right < self.size and self.heap[right] < self.heap[smallest]:
            smallest = right

        if smallest != index:
            self._swap(index, smallest)
            self._heapify(smallest)

    def _find(self, key):
        for i in range(0, self.size):
            if self.heap[i] == key:
                return i
        return -1

    def empty(self) -> bool:
        return self.size == 0
    
    def getSize(self) -> int:
        return self.size
    
    def insert(self, key: int) -> bool:
        if self.size == self.max_size:
            print("Heap is full!")
            return False
        
        index = self.size
        self.heap.append(key)
        self.size += 1

        self._swim(index)
        return True
    
    def peek(self) -> int:
        if self.empty():
            raise KeyError("Heap is empty!")
        return self.heap[0]

    def contians(self, key: int) -> bool:
        return self._find(key) >= 0

    def delete(self, key: int) -> int:
        if self.empty():
            print("Heap is empty!")
            return -1 
        
        i = self._find(key)
        if i >= 0:
            j = self.size - 1
            self._swap(i, j)
            temp = self.heap.pop()
            self.size -= 1
            self._heapify(i)
            return temp
        
    def print(self) -> None:
        for item in self.heap:
            print(item)


heap = MinHeap(100)
heap.insert(10)
heap.insert(12)
heap.insert(8)
heap.insert(14)
heap.insert(3)
heap.delete(10)
heap.print()
