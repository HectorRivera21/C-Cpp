#include<conio.h>
#include<bits/stdc++.h>

int fib(int n) {
  if(n < 2) return n;
  std::vector<int> fib;
  int s = 0;
  for(int i = 0; i < n; i++){
    if(fib.size()!=0 && fib.size()!=1){
      s = fib[i-1]+fib[i-2];
      fib.push_back(s);
    }
    else
    {
      s+=1;
      fib.push_back(1);
    }
  }
  return fib.back();
}

int main()
{
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin>> n;
  
  std::cout<<fib(n)<<'\n';
  
  return 0;
}