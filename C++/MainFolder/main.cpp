#include "Standard.h"
#include <map>
#include <hash_map>

void solve(){
    string s; 
    cin >> s;
    unordered_map<char, int> hash;
    int start = 0, len = 0;

    for(int i = 0; i< s.length(); i++){
        char c = s[i];
        if(hash.find(c) != hash.end())
        {
            if(hash[c] >= start)
                start = hash[c]+1;
        }
        len = max(len, i-start+1);
        hash[c] = i;
    }
    cout<< len;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, i=1;
    cin >> t;
    while(--t){
        cout<< "Case# "<<i<<":";
        solve();
        ++i;
        cout<<'\n';
    }

}