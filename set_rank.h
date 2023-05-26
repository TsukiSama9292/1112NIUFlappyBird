#include<bits/stdc++.h>
using namespace std;
class setrank
{
    private:
    string binary_to_string(string s);
    long long binary_to_longlong(string s);
    string string_to_binary(string s);
    string longlong_to_binary(long long n);
    public:
    setrank();
    vector<pair<string,long long>> v;
    pair<int,long long> renewrank(pair<string,long long> p);
    
}; 