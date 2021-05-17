#include<iostream>
#include<algorithm>
using namespace std;
#define maxN 180000
#define getNum 65

int n, i;
string str = "", mainstr = "";
string arr[maxN];

bool check() {
	for (size_t i = 0; i < mainstr.size(); i++) {
		unsigned int checkNum = mainstr[i] - getNum, index1 = 0, index2 = 0;
		
		for (size_t k = 0; k < str.size();k++) {
			if (mainstr[i] == str[k]) {
				if (!index1)
					index1 = k;
				else
					index2 = k;
			}
		}
		if (checkNum >= index2-index1)
			return false;
	}
	return true;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	while (n--) {
		cin >> i;
		char temp = i + getNum;
		str.push_back(temp);
		str.push_back(temp);
		mainstr.push_back(temp);
	}

	int c = 0;
	do {
		/*if (check()) {
			arr[c] = str;
			c++;
		}*/
		cout << (str) << '\n';
	} while (next_permutation(str.begin(), str.end()));
	
	if (c) {
		sort(arr, arr + c);
		
		for (int i = 0; i < str.size(); i++)
			cout << (int)(arr[0][i] - getNum) << ' ';
	}
	else
		cout << -1;

	return 0;
}