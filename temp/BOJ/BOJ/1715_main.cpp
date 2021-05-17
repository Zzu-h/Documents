#include<iostream>
#include<functional>
#include<queue>
using namespace std;
#define maxNum 100001
int list[maxNum];
int n;
priority_queue<int, vector<int>, greater<int>> list_;

int main() {
	cin >> n;

	for (int i = 0; i < n; i++){
		int t;
		cin >> t;
		list_.push(t);
	}

	int sum = 0, totalsum = 0;

	while (list_.size() != 1) {
		sum += list_.top();
		list_.pop();

		sum += list_.top();
		list_.pop();

		list_.push(sum);
		totalsum += sum;
		sum = 0;
	}
	
	cout << totalsum;

	return 0;
}