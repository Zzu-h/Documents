#include<iostream>
using namespace std;
#define maxNum 1000000000000000000
#define pi 3.141592
long long unsigned int dp[1001][1001];
//[a][b] a는 n b는 π의 수
int n;

long long unsigned int pibo(int nidx, int pidx) {
	
	if (dp[nidx][pidx])
		return dp[nidx][pidx];

	double cal = (nidx - (pidx * pi));
	
	if (0 <= cal && cal <= pi)
		return dp[nidx][pidx] = 1;

	dp[nidx][pidx] = (pibo(nidx - 1, pidx) + pibo(nidx, pidx + 1)) % maxNum;

	return (dp[nidx][pidx] % maxNum);
}

int main() {
	cin >> n;
	dp[1][0] = dp[2][0] = dp[3][0] = 1;
	cout << pibo(n, 0)<<endl;

	return 0;
}