#include <iostream>
#include <map>
#include <vector>

using namespace std;


class DisjointSet
{
    private:
        int* rank;
        int* parent;
        int n;
     
    public:
        DisjointSet(int n)
        {
            this->rank = new int[n];
            this->parent = new int[n];
            this->n = n;
            makeset();
        }

        int get_rank(int element) {return rank[element]; }

        int get_parent(int element) {return parent[element]; }

        void makeset()
        {
            for(int i=0; i<n; i++)
                parent[i] = i;
        }

        int find_set(int element)
        {
            int parent_element = parent[element];

            if(parent_element != element)
            {
                // this performs path compression;
                parent[element] =  find_set(parent_element);
            }

            return parent[element];
        }

        void union_sets(int element1, int element2)
        {
            int rp1 = find_set(element1);
            int rp2 = find_set(element2);

            int rp1_rank = rank[rp1];
            int rp2_rank = rank[rp2];

            if(rp1_rank >= rp2_rank)
            {
                rank[rp1] = rp1_rank == rp2_rank ? rp1_rank + 1 : rp1_rank;
                rank[rp2] = 0;
                parent[rp2] = rp1;
            } else 
            {
                parent[rp1] = rp2;
            }
        }

        void print_sets()
        {
            map<int, vector<int>> mp;
            for(int i=0; i<n; i++)
            {
                int p = find_set(i);
                if(p == i && mp.count(i) == 0)
                {
                   mp[i] = {i};
                }
                else
                {
                    // find parent
                    int root = find_set(i);
                    if(mp.count(root) == 0)
                    {
                        mp[root] = {root};
                        mp[root].push_back(i);
                    }
                    else if(root != i)
                        mp[root].push_back(i);
                    
                }      
            }
            
            for(auto it=mp.begin(); it!=mp.end(); it++)
            {
                vector<int>arr = it->second;
                
                cout << "Root: " << it->first << " {";
                for(int i=0; i<arr.size(); i++)
                {
                    cout << arr[i];
                    if(arr[i] == it->first)
                        cout << "*";
                    if(i != arr.size()-1)
                        cout << ", ";
                }
                cout << "}" << endl;
            }
        }

};


int main(int argc, char * argv[])
{
    DisjointSet ds(10);
    ds.union_sets(1, 2);
    ds.union_sets(3, 4);
    ds.union_sets(5, 6);
    ds.union_sets(8, 9);

    ds.union_sets(7, 9);

    ds.union_sets(2, 4);

    ds.union_sets(9, 5);
    ds.union_sets(1, 9);
    ds.print_sets();    
    return 0;
}