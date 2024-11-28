# Priority Queue is a queue but it gives an opportunity to give certain objects 
# some priority so they can be adjusted to positions according to thier priority. 
# There are many implementations of PQ (array, linked list, heap ...)

# This class defines Priority Queue data structure.
# This PQ is built on top of the heap.
# MaxHeap is used to have wider control over heap.


class PQueue:
    def __init__(self, max_size=1000) -> None:
        self.size = 0
        self.max_size = max_size
        self.heap = []
    
    def _swap(self, i, j):
        # swap function is used to change the values
        # inside the heap
        temp = self.heap[i]  # used to temporarily store value
        self.heap[i] = self.heap[j]
        self.heap[j] = temp 

    def _getParent(self, index) -> int:
        return (index-1)//2  # returns parent of the index.

    def _getRightChild(self, index) -> int:
        return 2 * index + 1  # returns right child of the index.
    
    def _getLeftChild(self, index) -> int:
        return 2 * index + 2  # returns the left child of the index.
    
    def _bubbleUp(self, index):
        # if the index is negative, then we shouldn't continue recursion
        if index > 0:
            parent = self._getParent(index) # get parent of the index

            # If the parent is greater than the index than, 
            # we should make a change to satisfy heap property
            if self.heap[index] > self.heap[parent]:
                # swap two elements to comply with the rule
                self._swap(index, parent)  

                # recursively move up, and check if 
                # the parent index also needs to be changed.
                self._bubbleUp(parent) 
        return

    def _bubbleDown(self, index):
        # Bubble down function ensures the heap property
        # applies to both of it's children
        left = self._getLeftChild(index)  # find index of left children
        right = self._getRightChild(index)  # find index of right children

        # We need to find at least one of its children's value is more than 
        # the value of itself which requires fix. The trick is find the index of
        # the largest among three (index, left and right), if it is not index than
        # we need to perform swap to satisfy heap property.
        largest = index  # start with the index itself
        # if the left child's value is greater
        if left < self.size and self.heap[left] > self.heap[largest]:
            largest = left
        # if the right child's value is greater
        if right < self.size and self.heap[right] > self.heap[largest]:
            largest = right

        # if the there is some index with greater value among children
        if largest != index:
            self._swap(index, largest)
            self._bubbleDown(largest)

    def empty(self) -> bool:
        # Returns boolean value; checks if the queue is empty.
        return self.size == 0
    
    def getSize(self) -> int:
        # Returns the size of the Queue
        return self.size

    def peek(self):
        # This function returns the first element inside the Queue.
        if self.size == 0:
            raise KeyError("Queue is Empty")
        return self.heap[self.size-1]

    def add(self, data):
        # add() function  adds element to the back of the queue
        # it compares the size of the queue and max_size. 
        if self.size == self.max_size:
            raise OverflowError("Queue is Full!")

        # the element should be added to the back of the queue.
        index = self.size
        self.heap.append(data)
        self.size = self.size + 1
        
        # after the insertion we should adjust the position of the element
        # and make changes if needed. We only need to go upwards to check.        
        self._bubbleUp(index)

    def poll(self):
        # Polling is to remove first element in the Queue
        if self.size == 0:
            raise IndexError("Queue is Empty!")
        # the element we need to remove is the first element (index = 0)
        # However before removing we need to swap it with the last element
        # and then we can delete the last element.
        index = self.size - 1
        self._swap(0, index)
        # remove last element (after swaping first element replaces the last)
        self.heap.pop()
        self.size = self.size - 1

        # We need to bubble down after we have removed the 
        # Max element(with the highest priority). By bubling down we
        # adjust the child nodes of the new top element.
        self._bubbleDown(0)

    def print(self):
        # a utility function to print the queue
        for num in self.heap:
            print(num)
    

pq = PQueue(100)

pq.add(12)
pq.add(22)
pq.add(2)
pq.add(29)
pq.poll()

pq.print()