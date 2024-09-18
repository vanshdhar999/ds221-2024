#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(){
    
    map<vector<string>, vector<int>> m;
    m.insert({{"tech", "gadget"}, {1}});
    m[{"gadget", "tech"}].push_back(2);
    

    //print the map
    for(auto it = m.begin(); it != m.end(); it++){
        cout << "Key: ";
        for(auto i = it->first.begin(); i != it->first.end(); i++){
            cout << *i << " ";
        }
        cout << "Value: ";
        for(auto i = it->second.begin(); i != it->second.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }

   
}