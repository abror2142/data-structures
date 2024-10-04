#include <iostream>
#include <string>

using namespace std;


int find_rep_substring(string s, int len){
    string suffixes[len];
    for(int i=0; i<len; i++)
        suffixes[i] = s.substr(i);
    
    sort(suffixes, suffixes+len);

    int lcp[len];

    for(int i=0; i<len; i++)
        lcp[i] = 0;

    for(int i=0; i<len-1; i++)
    {   
        int j = 0;
        while(suffixes[i][j] == suffixes[i+1][j])
            j++;
        lcp[i+1] = j;
    }

    // print and sum the array elements;
    cout << "LCP Array: " << endl;
    int sum = 0;
    for(int i=0; i<len; i++){
        sum += lcp[i];
        cout << "| " << lcp[i] << " | " << suffixes[i] << endl;
    }
    cout << endl;
    return sum;
}

int unique_supstring(string s)
{
    int n = s.length();
    int number_of_substrings = n * (n+1)/2;
    int repeted_substrings = find_rep_substring(s, n);
    return number_of_substrings - repeted_substrings;
}


int main (int argc, char * argv[])
{
    cout << unique_supstring("AZAZA") << endl;
    return 0;
}