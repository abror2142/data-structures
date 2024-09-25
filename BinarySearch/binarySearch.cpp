#include <iostream>
#include <vector>

using namespace std;


int binarySearchRecursive(int arr[], int x, int i, int j)
{
    if(i <= j){
        int mid = i + (j-i)/2;
        
        if(arr[mid] == x)
            return mid;
        
        if(x > arr[mid])
            return binarySearchRecursive(arr, x, mid + 1, j);
        
        if(x < arr[mid]) 
            return binarySearchRecursive(arr, x, i, mid - 1);
    }
    return -1;
}


int binarySearchLoop(int arr[], int x, int i, int j)
{
    while (i <= j){
        int mid = i + (j-i)/2;
        cout << "i: " << i << "\tj: " << j << "\tmid: " << mid << "\n";

        if(arr[mid] == x)
            return mid;

        else if(arr[mid] > x)
            j = mid - 1;
        
        else if (arr[mid] < x)
            i = mid + 1;
    }
    return -1;
}


int main()
{
    int a[] = {20, 30, 40, 50, 50};
    int l = sizeof(a)/sizeof(a[0]);
    int res = binarySearchLoop(a, 30, 0, l); 
    cout << res;
    return 0;
}