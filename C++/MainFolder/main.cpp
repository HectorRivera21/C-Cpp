#include "Standard.h"

void solve(){
    int x = 0 ;
    cin>> x;
    
    bool neg;

    if(x<0)
    {
        neg = true;
        x= -x;
    }
    int32_t rev=0, prev_rev=0;

    while(x!=0){
        int32_t tmp = x %10;
        rev = (rev*10)+tmp;
        if((rev - tmp)/10 != prev_rev)
        {
            cout<< 0;
        }
        prev_rev = rev;
        x = x /10;
    }
    (neg == true)?-rev:rev;
    cout<<rev;
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