#include<iostream>
#include<unordered_map>
using namespace std;
long long n, p, q, x, y;
unordered_map<long long, long long> dp;
long long An(long long i) {
	if (i <= 0)
		return 1;

	auto iter = dp.find(i);
	if (iter != dp.end())
		return iter->second;
	
	long long int a = An(i / p - x), b = An(i / q - y);
	dp[i] = a + b;

	return a + b;
}

int main() {
	cin >> n >> p >> q >> x >> y;
	cout << An(n);
	return 0;
}