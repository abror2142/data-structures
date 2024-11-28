#include <iostream>
#include <string>


using namespace std;

struct suffix {
    int index;
    int rank[2];
    // data is not stored in suffix;
};

int cmp(struct suffix a, struct suffix b)
{
    // first compare according to rank[0]
    // if they equal compare according to rank[1]
    return (a.rank[0] == b.rank[0] 
            ? (a.rank[1] > b.rank[1] ? 1 : 0) 
            : (a.rank[0] < b.rank[0] ? 1 : 0));
}

int *buildSuffixArray(char * s, int len)
{
    suffix suffix_array[len];

    for(int i=0; i<len; i++)
    {
        suffix_array[i].index = i;
        suffix_array[i].rank[0] = s[i] - 'a';
        // i+1 < lenn => because i increases step by step, until it reaches len
        // and the last suffix positions will have index close to len
        suffix_array[i].rank[1] = (i+1 < len ? (s[i+1] - 'a') : -1);
        /*  
                "banana" =>
            banana  0  1  0
            anana   1  0  13
            nana    2  13 0 
            ...
        */
    }

    // we sort the suffix_array by rank[0] and rank[1]; giving rank[0] priority
    sort(suffix_array, suffix_array+len, cmp);

    int ind[len];

    for(int k=4; k<2*len; k=k*2)
    {
        suffix_array[0].rank[0] = 0;
        suffix_array[0].rank[1] = 0;
        int rank = 0;

        for(int i=1; i<len; i++)
        {
            // first check if the previous suffix has incomparable(same) ranks 1 and 2
            if(
                suffix_array[i].rank[0] == suffix_array[i-1].rank[0]
                && suffix_array[i].rank[1] == suffix_array[i-1].rank[1]
            ) // this means keep rank;
            {
                suffix_array[i].rank[0] = rank;
            } else 
            {
                suffix_array[i].rank[0] = rank + 1;
                rank++;
            }
        }

        for(int i=0; i<len; i++)
        {
            suffix_array[i].rank[1] = s[i] - 'a';
        }

        sort(suffix_array, suffix_array + len, cmp);
    }

}

int main(int arrc, char * arrv[])
{

    return 0;
}