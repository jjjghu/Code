#include <iostream>
#include <unordered_map>
using namespace std;
int main(void)
{
    int n;
    string s;
    while(cin >> n, n != 0)
    {
        unordered_map<string, int> umap;
        umap["top"] = 1;
        umap["north"] = 2;
        umap["west"] = 3;
        umap["east"] = 4;
        umap["south"] = 5;
        umap["bottom"] = 6;
        for(int i = 0; i < n; ++i)
        {
            cin >> s;
            if(s == "east")
            {
                int temp = umap["east"];
                umap["east"] = umap["top"];
                umap["top"] = umap["west"];
                umap["west"] = umap["bottom"];
                umap["bottom"] = temp;           
            }
            else if(s == "south")
            {
                int temp = umap["south"];
                umap["south"] = umap["top"];
                umap["top"] = umap["north"];
                umap["north"] = umap["bottom"];
                umap["bottom"] = temp;
            }
            else if(s == "west")
            {
                int temp = umap["west"];
                umap["west"] = umap["top"];
                umap["top"] = umap["east"];
                umap["east"] = umap["bottom"];
                umap["bottom"] = temp;
            }
            else if(s == "north")
            {
                int temp = umap["north"];
                umap["north"] = umap["top"];
                umap["top"] = umap["south"];
                umap["south"] = umap["bottom"];
                umap["bottom"] = temp;
            }
        }
        cout << umap["top"] << endl;
    }
}