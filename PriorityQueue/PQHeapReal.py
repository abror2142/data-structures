from typing import List

"""
    I also want to have somekind of controller class/funciton
    to use the power of the queue!
"""


class Client:
    def __init__(self, id: int, fullName: str, priority: int) -> None:
        self.id: int = id
        self.fullName: str = fullName
        self.priority: int = priority

class PriorityQueue:
    def __init__(self, max_size: int=1000) -> None:
        self.size: int = 0
        self.max_size: int = max_size
        self.queue: List[Client] = list()

    def _swap(self, i: int, j: int) -> None:
        temp = self.queue[i]
        self.queue[i] = self.queue[j]
        self.queue[j] = temp

    def _getParent(self, index: int) -> int:
        return (index - 1)//2

    def _getRightChild(self, index: int) -> int:
        return 2 * index + 1
    
    def _getLeftChild(self, index: int) -> int:
        return 2 * index + 2

    def _bubbleUp(self, index: int) -> None:
        if index > 0:
            parent = self._getParent(index)

            if self.queue[index].priority < self.queue[parent].priority:
                self._swap(index, parent)
                self._bubbleUp(parent)
        return

    def _bubbleDown(self, index: int) -> None:
        left = self._getLeftChild(index)
        right = self._getRightChild(index)

        smallest = index

        if (left < self.size 
            and self.queue[left].priority < self.queue[smallest].priority):
            smallest = left
        if (right < self.size 
            and self.queue[right].priority < self.queue[smallest].priority):
            smallest = right
        
        if smallest != index:
            self._swap(index, smallest)
            self._bubbleDown(smallest)
    
    def _findByName(self, name: str) -> None:
        for i in range(0, len(self.queue)):
            if self.queue[i].fullName == name:
                return i
        return -1
    
    def _findByID(self, id: int) -> None:
        for i in range(0, len(self.queue)):
            if self.queue[i].id == id:
                return i
        return -1
    
    def _findByNameAndID(self, id: int, name: str) -> None:
        for i in range(0, len(self.queue)):
            if self.queue[i].id == id and self.queue[i].fullName == name:
                return i
        return -1

    def _increasePriority(self, index: int, new_priority: int) -> None:
        self.queue[index].priority = new_priority
        self._bubbleDown(index)

    def _decreasePriority(self, index: int, new_priority: int) -> None:
        self.queue[index].priority = new_priority
        self._bubbleUp(index)

    def add(self, client: Client) -> bool:
        if self.size == self.max_size:
            raise OverflowError("Queue is full!")
        index = self.size
        self.queue.append(client)
        self.size = self.size + 1

        self._bubbleUp(index)
        return True

    def poll(self) -> None:
        if self.size == 0:
            raise IndexError("Queue is empty!")
        index = self.size - 1
        self._swap(0, index)
        self.queue.pop()
        self.size = self.size - 1

        self._bubbleDown(0)

    def changePriority(self, new_priority: int, id:int=None, name: str = None) -> None:
        if id is None and name is None:
            raise ValueError("Please define at least one valid argument!")
        elif id is None:
            index = self._findByName(name)
        elif name is None:
            index = self._findByID(id)
        else:
            index = self._findByNameAndID(id, name)

        if index > 0 and index < self.size:        
            if(new_priority > self.queue[index].priority):
                self._increasePriority(index, new_priority)   
            elif(new_priority < self.queue[index].priority):
                self._decreasePriority(index, new_priority)
        
        return

    def print(self) -> None:
        for client in self.queue:
            print(client.priority, client.fullName)


pq = PriorityQueue()
client1 = Client(1289, "Nodir Botirov", 2)
client2 = Client(12349, "Abdulla Nasimov", 1)
client3 = Client(9485, "Feruz Yunusov", 14)
client4 = Client(945, "Feruza Yunusova", 0)
pq.add(client1)
pq.add(client2)
pq.add(client3)
pq.add(client4)
pq.changePriority(5, name="Feruza Yunusova")
pq.changePriority(7, id=12349)
pq.print()