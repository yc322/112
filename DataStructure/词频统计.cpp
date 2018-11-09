#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void display_map(map<string,int> &wmap);

int main()
{
    using namespace std;
    string filename;
    cout << "Enter the file name : ";
    cin >> filename;
    cin.get();
    ifstream fin(filename.c_str());
    string  temp;
    map<string,int> wmap;
    while(fin>>temp)
        wmap[temp]++;
    display_map(wmap);

    fin.close();
    cin.get();
    return 0;
}

void display_map(map<string,int> &wmap)
{
    map<string,int>::const_iterator map_it;
    for(map_it=wmap.begin();map_it != wmap.end();map_it ++)
    {
        cout << "(\"" << map_it->first << "\"," << map_it->second << ")" << endl;
    }
}
