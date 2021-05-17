#include<iostream>
#include<algorithm>
using namespace std;

int n;
int findDropIdx(string &str) {
	//���������� ���� ���� ���� �� ���� �ε����� ��ȯ
	for (size_t i = str.size() - 2; i > 0; i--)
		if (str[i] < str[i + 1])
			return i;
	return 0;
}
void swapStr(string &str, int idx) {
	//�ڱ⺸�� ū �� �� ���� ���� ���� swap
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
		1. ���� ū ������ �ε����� ã�´�.
		2. �ش� �ε��� �ٷ� �հ� ��ȯ�Ѵ�.
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