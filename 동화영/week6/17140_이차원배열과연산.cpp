/* ������ �迭�� ���� */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MAX_N 101

struct numSet {
	int num; // ����
	int cnt; // ���� Ƚ��

	// ����Ƚ�� -> ���� ������ ��������
	bool operator < (numSet nxt) const {
		if (cnt < nxt.cnt) return false;
		if (cnt > nxt.cnt) return true;
		if (num < nxt.num) return false;
		if (num > nxt.num) return true;
		return false;
	}
};

priority_queue<numSet> pq;
int MAP[MAX_N][MAX_N]; // �迭

int rLen, cLen;

// R���� : �࿡ ���� ����
void sortRow() {
	// * �࿡ ���� ���� -> ���� ������ ���Ѵ�
	int colCnt = 0;
	for (int i = 1; i <= rLen; i++) { // �� �ึ�� ���� ����
		// ������ ����Ƚ���� ī������ DAT
		int DAT[MAX_N] = { 0, };
		for (int j = 1; j < MAX_N; j++) {
			if (MAP[i][j] != 0) DAT[MAP[i][j]]++;
		}

		// ������ �� ���̶� �� ���ڿ� ����
		// (����, ����Ƚ��)�� pq�� push�Ѵ� -> ����
		for (int j = 1; j < MAX_N; j++) {
			if (DAT[j] != 0) pq.push({ j, DAT[j] });
		}

		// i��° ���� 0���� �ʱ�ȭ -> ���̰� ���� ����� ���� ����(��)�� ���߱� ����
		for (int j = 1; j < MAX_N; j++) {
			MAP[i][j] = 0;
		}

		// pq�� ���鼭 ���� ����� ���
		int ind = 1;
		while (!pq.empty()) {
			// �迭�� ���Ľ� �ִ� 100���� ����
			if (ind > 100) {
				while (!pq.empty()) pq.pop();
				break;
			}

			numSet now = pq.top();
			pq.pop();

			// ������ (����, Ƚ��) ������
			MAP[i][ind] = now.num;
			MAP[i][ind + 1] = now.cnt;

			ind += 2;
		}
		
		// i��° �� ���� ����� ����
		if (ind - 1 > colCnt) colCnt = ind - 1;
	}

	// ��� �� ���� �� ����(��)�� ����
	cLen = colCnt;
}

// ������ R����� �����ϳ� �ε����� ����
// C���� : ���� ���� ����
void sortCol() {
	int rowCnt = 0;
	for (int i = 1; i <= cLen; i++) {
		int DAT[MAX_N] = { 0, };
		for (int j = 1; j < MAX_N; j++) {
			if (MAP[j][i] != 0) DAT[MAP[j][i]]++;
		}

		for (int j = 1; j < MAX_N; j++) {
			if (DAT[j] != 0) pq.push({ j, DAT[j] });
		}

		// i��° ���� 0���� �ʱ�ȭ
		for (int j = 1; j < MAX_N; j++) {
			MAP[j][i] = 0;
		}

		int ind = 1;
		while (!pq.empty()) {
			if (ind > 100) {
				while (!pq.empty()) pq.pop();
				break;
			}

			numSet now = pq.top();
			pq.pop();

			MAP[ind][i] = now.num;
			MAP[ind + 1][i] = now.cnt;

			ind += 2;
		}

		if (ind - 1 > rowCnt) rowCnt = ind - 1;
	}

	rLen = rowCnt;
}

int main() {
	// input
	int r, c, k;
	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> MAP[i][j];
		}
	}

	// �ʱ� �迭�� ������ = 3*3
	rLen = 3, cLen = 3;

	int ans = 0; // ���� �ð�
	while (MAP[r][c] != k) {
		// ���� �ð��� 100�ʰ� �����ٸ� -1 ���
		if (ans == 100) {
			ans = -1;
			break;
		}

		// (���� ���� >= ���� ����) - �࿡ ���� ����
		if (rLen >= cLen) {
			sortRow();
		}
		// (���� ���� < ���� ����) - ���� ���� ����
		else {
			sortCol();
		}

		ans++; // ����ð� ����
	}

	// output
	cout << ans;

	return 0;
}