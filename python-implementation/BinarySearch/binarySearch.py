def binary_search_recursive(arr, x, i, j):
    if i <= j:
        mid = i + (j-i)//2

        if arr[mid] == x:
            return mid
        
        if arr[mid] < x:
            return binary_search_recursive(arr, x, mid + 1, j)
        
        if arr[mid] > x:
            return binary_search_recursive(arr, x, i, mid - 1)
        
    return -1


def binary_search_loop(arr, x, i, j):
    while i <= j:
        mid = i + (j-i)//2
        
        if arr[mid] == x:
            return mid
        
        if arr[mid] < x:
            i = mid + 1 
        
        if arr[mid] > x:
            j = mid - 1

    return -1


arr = [10, 20, 30, 40, 50]
print(binary_search_loop(arr, 40, 0, len(arr)))