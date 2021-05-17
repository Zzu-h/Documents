#include<iostream>
#include<vector>
using namespace std;

#define bigNum 4000001
bool primeNumber[bigNum];
vector<int> primeList;

void setPrime() {
	for (int i = 2; i < bigNum; i++) {
		primeNumber[i] = true;
	}

	for (int i = 2; i < bigNum; i++) {
		if (!primeNumber[i]) continue;

		for (int j = 2 * i; j < bigNum; j += i) {
			primeNumber[j] = false;
		}
	}

	for (int i = 2; i <= bigNum; i++) {
		if (primeNumber[i]) {
			primeList.push_back(i);
		}
	}
}

int n;
int count_ = 0;

int main() {
	setPrime();
	cin >> n;

	for (int i = 2; i <= n; i++) {
		if (primeNumber[i]) {

		}
	}
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int k = i; k < primeList.size() && sum < n; k++) {
			sum += primeList[k];
		}
		if (sum == n)
			count_++;
	}
	cout << count_;

	return 0;
}