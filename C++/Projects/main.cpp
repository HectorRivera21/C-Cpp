#include<iostream>
using namespace std;

class Solution {
private:
  int sumDigits(int num) {
    int sum = 0;
    while(num) {
      sum += num%10;
      num /= 10;
    }
    return sum;
  }
  int solution(int num)
  {
    int sum = 0;
    sum+=num%10;
    sum+=num/=10;
    return num < 10 ? sum : solution(sum);
  }
public:
  int getLucky(string s, int k) {
    int sum = 0;
    for(char &ch : s) {
      int val = ch-'a'+1;
      sum += val < 10 ? val : (val%10 + val/10);
    }
    k-=1;
    while(k-- && sum >= 10){
      // sum = solution(sum);
      sum = sumDigits(sum);
      cout<<sum;
    }
    return sum;
  }
};

int main()
{
  Solution a;

  a.getLucky("vbyytoijnbgtyrjlsc", 2);

  return 0;
}