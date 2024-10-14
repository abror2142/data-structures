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

    def findIndex(self, id: int=None, name: str=None):
        if id is None and name is None:
            raise ValueError("Please define at least one valid argument!")
        elif id is None:
            index = self._findByName(name)
        elif name == '':
            index = self._findByID(id)
            print("Hit!")
        else:
            index = self._findByNameAndID(id, name)
        return index

    def empty(self):
        return self.size == 0
    
    def getSize(self):
        return self.size
    
    def peek(self) -> Client:
        if self.size ==  0:
            print("Queue is empty!")
        return self.queue[0]

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

    def changePriority(self, new_priority: int, id:int=None, name: str=None) -> None:
        # Negative priorities can only be used inside the function
        if new_priority < 0:
            raise ValueError("Negative priorities are not allowed.")

        index = self.findIndex(id, name)
        print("------", index, "------", id, name, new_priority)
        if name is '':
            print("None Type Hit!")
        if index >= 0 and index < self.size:        
            if(new_priority > self.queue[index].priority):
                self._increasePriority(index, new_priority)   
            elif(new_priority < self.queue[index].priority):
                self._decreasePriority(index, new_priority)
        
        return

    def remove(self, id: int=None, name: str=None):
        index = self.findIndex(id, name)
        if index == -1:
            return
        else:
            self._decreasePriority(index, -1)
            self.poll()


    def print(self) -> None:
        for client in self.queue:
            print(client.id, client.fullName, client.priority)


pq = PriorityQueue()

while True:
    if(pq.empty()):
        print("Queue is empty now! Insert clients!")

    print("Choose a command: ")
    print("\t1 -> insert \t2 -> poll \t3 -> delete")
    print("\t4 -> change \t5 -> print \t6 -> peek")

    command = int(input("Command code (e.g. 1): "))

    if command == 1:
        id = int(input("Client ID: "))
        name = input("Client Full Name: ")
        priority = int(input("Priority: "))

        client = Client(id, name, priority)
        pq.add(client)
    elif command == 2:
        pq.poll()
    elif command == 3:
        print("At least one is required: Client ID or Full Name!")
        id = int(input("Client ID: "))
        name = input("Client Full Name: ")
        pq.remove(id, name)
        print("Sucessfully deleted!")
    elif command == 4:
        print("At least one is required: Client ID or Full Name!")
        id = int(input("Client ID: ") or -1)
        name = input("Client Full Name: ")
        priority = int(input("New priority: "))
        pq.changePriority(priority, id=id, name=name)
    elif command == 5:
        pq.print()
    elif command == 6:
        client: Client = pq.peek()
        print("Peek:", client.fullName, client.id)
    print()