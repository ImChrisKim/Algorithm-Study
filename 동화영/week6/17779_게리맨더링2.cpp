/* �Ը��Ǵ���2 */
#include <iostream>
#include <cstring>
using namespace std;
#define MAX_N 20
#define TERR 6

int SECTION[MAX_N][MAX_N]; // �� ĭ�� ���ű� ����
int MAP[MAX_N][MAX_N]; // ������ �� �� ������ �α� ��
int N; // �������� ũ��

int ans; // (�ִ� - �ּ�) �α� �� ���� �� �ּ� (��)

// (r, c)ĭ�� �� �� ���ű������� ��ȯ
int findGroup(int r, int c, int x, int y, int d1, int d2) {
	if (SECTION[r][c] == 5) return 5;
	else if (r >= 0 && r < x + d1 && c >= 0 && c <= y) return 1;
	else if (r >= 0 && r <= x + d2 && c > y && c < N) return 2;
	else if (r >= x + d1 && r < N && c >= 0 && c < y - d1 + d2) return 3;
	else if (r > x + d2 && r < N && c >= y - d1 + d2 && c < N) return 4;
	else return 5;
}

// 5�� ���ű��� ǥ��
void setSection(int x, int y, int d1, int d2) {
	int rdir[] = { 1, 1, -1, -1 }; // �Ͽ�, ����, ����, ���
	int cdir[] = { 1, -1, -1, 1 };

	// �׵θ�
	for (int i = 0; i <= d1; i++) {
		SECTION[x + i][y - i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		SECTION[x + i][y + i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		SECTION[x + d1 + i][y - d1 + i] = 5;
	}
	for (int i = 0; i <= d1; i++) {
		SECTION[x + d2 + i][y + d2 - i] = 5;
	}

	// �׵θ� ����
	bool isOn = false;
	for (int i = x + 1; i < x + d1 + d2; i++) {
		isOn = false;
		for (int j = y - d1; j <= y + d2; j++) {
			if (SECTION[i][j] == 5 && !isOn) isOn = true;
			else if (SECTION[i][j] == 5 && isOn) break;
			else if (isOn) SECTION[i][j] = 5;
		}
	}
}

// �� ���������� �α� �� ����ϱ�
int sumPeople(int x, int y, int d1, int d2) {
	int people[TERR] = { 0, };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// (i,j)ĭ�� ���ű��� Ȯ���Ͽ� �α��� �߰�
			people[findGroup(i, j, x, y, d1, d2)] += MAP[i][j];
		}
	}

	// �α����� �ּ�/�ִ��� �� ���Ͽ� ��ȯ
	int minS = 21e8;
	int maxS = -21e8;
	for (int i = 1; i < TERR; i++) {
		if (people[i] < minS) minS = people[i];
		if (people[i] > maxS) maxS = people[i];
	}

	return maxS - minS;
}

// 2. (r,c) ������ �������� ��輱�� ���� ���ϱ� - (d1, d2) ���ϱ�
void findDist(int r, int c) {
	for (int i = 1; i <= c; i++) { // d1
		if (r + i >= N) break;
		for (int j = 1; j < N - c; j++) { //d2
			if (r + i + j >= N) break;

			// 5�� ���ű� ǥ���ϱ�
			memset(SECTION, 0, sizeof(SECTION));
			setSection(r, c, i, j);

			// 3. ��輱�� ���������� �� ���ű��� �α����� ����Ѵ�
			int diff = sumPeople(r, c, i, j);
			if (diff < ans) { // ���̰� �ּҶ�� ����
				ans = diff;
			}
		}
	}
}

int main() {
	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve
	ans = 21e8;

	// 1. �� ĭ���� ������ �����Ѵ� - (x,y) ���ϱ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			findDist(i, j);
		}
	}

	// output
	cout << ans;

	return 0;
}

/*
7
1 2 3 4 1 6 1
7 8 9 1 4 2 1
2 3 4 1 1 3 1
6 6 6 6 9 4 1
9 1 9 1 9 5 1
1 1 1 1 9 9 1
1 1 1 1 9 9 1
*/