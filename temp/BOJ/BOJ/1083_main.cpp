	#include<iostream>
	using namespace std;

	#define maxNum 51

	int n, s;
	int list[maxNum];

	void sorting() {
		for (int i = 1; i < n && s; i++) {
			for (int k = 1; k < n && s; k++) {
				if (list[k] < list[k + 1]) {
					//swap
					int temp = list[k];
					list[k] = list[k + 1];
					list[k + 1] = temp;
					s--;
				}
			}
		}
	}

	int main() {
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> list[i];
		cin >> s;

		sorting();

		for (int i = 1; i <= n; i++)
			cout << list[i] << ' ';

		return 0;
	}