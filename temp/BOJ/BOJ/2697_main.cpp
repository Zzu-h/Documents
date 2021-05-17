#include<iostream>
#include<algorithm>
using namespace std;

int n;
int findDropIdx(string &str) {
	//끝에서부터 최초 다음 수가 더 작은 인덱스를 반환
	for (size_t i = str.size() - 2; i > 0; i--)
		if (str[i] < str[i + 1])
			return i;
	return 0;
}
void swapStr(string &str, int idx) {
	//자기보다 큰 수 중 가장 작은 수와 swap
	pair<char, int> min;
	min.first = '9';
	min.second = idx + 1;
	for (size_t i = idx + 1; i < str.size(); i++) {
		if (min.first > str[i]) {
			if (str[idx] < str[i]) {
				min.first = str[i];
				min.second = i;
			}
		}
	}

	//swap
	char temp = str[idx];
	str[idx] = min.first;
	str[min.second] = temp;
}

int main() {
	cin >> n;
	while (n--) {
		string str;
		cin >> str;
		/*
		1. 가장 큰 최초의 인덱스를 찾는다.
		2. 해당 인덱스 바로 앞과 교환한다.
		*/
		int idx = findDropIdx(str);
		if (idx == 0)
			cout << "BIGGEST\n";
		else {
			swapStr(str, idx);
			sort(str.begin() + idx + 1, str.end());
			cout << str << '\n';
		}
	}
	return 0;
}