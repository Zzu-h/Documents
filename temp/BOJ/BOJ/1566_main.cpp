#include<iostream>
using namespace std;
// �� ��� ���� ���� ���ϰ� ��� ���� ���� ���� ���� ���� flip����
#define flip(a) (-1*a)

int matrix[20][20];
int cpy_matrix[20][20];
int n, m;

void copyTotemp() {
	for (int y = 1; y <= n; y++)
		for (int x = 1; x <= m; x++)
			cpy_matrix[y][x] = matrix[y][x];
}
void copyToOrigin() {
	for (int y = 0; y <= n; y++)
		for (int x = 0; x <= m; x++)
			matrix[y][x] = cpy_matrix[y][x];
}
void setup() {
	for (int y = 0; y < 20; y++) {
		matrix[y][0] = 0;
		matrix[y][19] = 0;
	}
	for (int x = 0; x < 20; x++) {
		matrix[0][x] = 0;
		matrix[19][x] = 0;
	}
}

int rowSum() {
	int sum = 0, count = 0;
	// �� �հ��
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++)
			sum += matrix[y][x];
		matrix[y][19] = sum;
		count = (sum < 0) ? count + 1 : count;
		sum = 0;
	}

	return count;
}
int colSum() {
	int sum = 0,count = 0;
	// �� �հ��
	for (int x = 1; x <= m; x++) {
		for (int y = 1; y <= n; y++)
			sum += matrix[y][x];
		matrix[19][x] = sum;
		count = (sum < 0) ? count + 1 : count;
		sum = 0;
	}
	return count;
}

void rowFlip(int idx) {
	for (int x = 1; x <= m; x++) {
		matrix[idx][x] *= -1;
	}
}
void colFlip(int idx) {
	for (int y = 1; y <= n; y++) {
		matrix[y][idx] *= -1;
	}
}

bool AllCheck() {
	for (int y = 1; y <= n; y++) {
		if (matrix[y][19] <= 0) {
			return true;
		}
	}
	for (int x = 1; x <= m; x++) {
		if (matrix[19][x] <= 0) {
			return true;
		}
	}
	return false;
}

int main() {
	setup();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;

	for (int y = 1; y <= n; y++)
		for (int x = 1; x <= m; x++)
			cin >> matrix[y][x];

	bool flag = true;
	int count = 0;

	int r = rowSum(), c = colSum();
	while (AllCheck() && flag) {
		
		if (r > c) {
			//�� üũ
			for (int y = 1; y <= n; y++) {
				if (matrix[y][19] < 0) {
					//flip
					rowFlip(y);
					matrix[y][0]++; //�ش� �� flip 1ȸ
					count++;
				}
			}
			//colSum(); //�࿡�� ���ŵǾ��� �� �ֱ⿡ ���� �� ����
		}
		else {
			//�� üũ
			for (int x = 1; x <= m; x++) {
				if (matrix[19][x] < 0) {
					//flip
					colFlip(x);
					matrix[0][x]++; //�ش� �� flip 1ȸ
					count++;
				}
			}
			//rowSum(); //������ ���ŵǾ��� �� �ֱ⿡ ���� �� ����
		}

		r = rowSum(), c = colSum();
		if (r == 0 && c == 0)
			flag = false;
	}

	if(AllCheck())
		cout << -1;
	else
		cout << count;
	return 0;
}