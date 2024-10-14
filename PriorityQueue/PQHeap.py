class PQueue:
    def __init__(self, max_size=1000) -> None:
        self.size = 0
        self.max_size = max_size
        self.heap = []
    
    def _swap(self, i, j):
        temp = self.heap[i]
        self.heap[i] = self.heap[j]
        self.heap[j] = temp 

    def _getParent(self, index) -> int:
        return (index-1)//2

    def _getRightChild(self, index) -> int:
        return 2 * index + 1
    
    def _getLeftChild(self, index) -> int:
        return 2 * index + 2
    
    def _bubbleUp(self, index):
        if index > 0:
            parent = self._getParent(index)

            if self.heap[index] > self.heap[parent]:
                self._swap(index, parent)
                self._bubbleUp(parent)
            return

    def _bubbleDown(self, index):
        left = self._getLeftChild(index)
        right = self._getRightChild(index)

        largest = index
        if left < self.size and self.heap[left] > self.heap[largest]:
            largest = left
        if right < self.size and self.heap[right] > self.heap[largest]:
            largest = right

        if largest != index:
            self._swap(index, largest)
            self._bubbleDown(largest)

    def empty(self) -> None:
        return self.size == 0
    
    def getSize(self) -> int:
        return self.size

    def add(self, data): 
        if self.size == self.max_size:
            raise OverflowError("Queue is Full!")
        index = self.size
        self.heap.append(data);
        self.size = self.size + 1

        self._bubbleUp(index)

    def poll(self):
        if self.size == 0:
            raise IndexError("Queue is Empty!")
        index = self.size - 1
        self._swap(0, index)
        self.heap.pop()
        self.size = self.size - 1

        self._bubbleDown(0)

    def print(self):
        for num in self.heap:
            print(num)
        

pq = PQueue(100)

pq.add(12)
pq.add(22)
pq.add(2)
pq.add(29)
pq.poll()

pq.print()