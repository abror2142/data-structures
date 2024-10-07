#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
    This is the implementation of Suffix Array using naive approach.
    Time complexity of this algorithm is O(n*k*Logn).  
    The sorting step itself takes O(n*k*Logn) time as every comparison 
    is a comparison of two strings and the comparison takes O(K) time where
    K is max length of string in given array. 
*/

struct Suffix {
    string suff;
    int index;

    Suffix(string suff, int index)
    {
        this->suff = suff;
        this->index = index;
    }

    Suffix()
    {
        this->suff = "";
        this->index = -1;
    }
};

int suffixcmp(struct Suffix a, struct Suffix b)
{
    return strcmp(a.suff.c_str(), b.suff.c_str()) < 0 ? 1 : 0;
};

void buildAuffixArray(string s)
{
    int len = s.length();
    Suffix suffix_array[len];

    for(int i=0; i<len; i++)
        suffix_array[i] = Suffix(s.substr(i), i);
    
    sort(suffix_array, suffix_array+len, suffixcmp);

    for(int i=0; i<len; i++)
        cout << suffix_array[i].suff << " " << suffix_array[i].index << endl;
};


int main(int argc, char * argv[])
{
    string s = "banana";
    buildAuffixArray(s);
    return 0;
}