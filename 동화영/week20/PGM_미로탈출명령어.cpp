// PGM - �̷� Ż�� ��ɾ�
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

char dir[5] = "dlru";
int dr[4] = { 1, 0, 0, -1 }; // dlru ��
int dc[4] = { 0, -1, 1, 0 };
bool flag = false; // ���� ���� ���� ã�Ҵ°��� ����
string answer; // ��ȯ�� ��
int n, m, x, y, r, c, k; // n*m ����, ������(x,y), ������(r,c), �ִ� k ����

// ���� (curr, curc)�� ��ġ�ϸ� cnt�� �̵��� �����̴�
void dfs(int curr, int curc, int cnt) {
	// �� ã�Ҵٸ� ���̻� Ž�� X
	// �̹� ���� ������ Ž���Ͽ��⿡ ���� �� �� ã�Ҵٸ� �װ� ������ ���� �����̴�
	//if (flag) return;

	// (�� �̵� ������ Ƚ��) - (���� ��ġ���� ���� �������� ���� �Ÿ�)
	int remain = (k - cnt) - (abs(curr - r) + abs(curc - c));
	if (remain < 0) return; // �̵� ������ Ƚ���� �ȳ��Ҵٸ� �Ұ�
	if (remain % 2 != 0) return; // Ȧ�� �� �̻� ���Ҵٸ� �̵� �Ұ� - �Դٰ��� �Ϸ��� ¦���� �̵� �ʿ�

	// ������������ k�� �ɷ��� �Դٸ� flag ���� �� ����
	if (curr == r && curc == c && cnt == k) {
		flag = true;
		return;
	}

	// 4���� Ž��
	for (int i = 0; i < 4; i++) {
		int nr = curr + dr[i];
		int nc = curc + dc[i];

		if (nr <= 0 || nc <= 0 || nr > n || nc > m) continue; // ���� ���� �̵� �Ұ�

		answer += dir[i]; // Ž�� �� answer ���� �߰�
		dfs(nr, nc, cnt + 1); // ���� �������� Ž��
		if (flag) return; // ���� ã�Ҵٸ� �ٷ� ���� - �������� ������ ������ ��θ� pop_back �Ͽ��� �ȵ�
		answer.pop_back(); // Ž�� �� answer ���� ����
	}
}

string solution(int _n, int _m, int _x, int _y, int _r, int _c, int _k) {
	// input
	// �Է°��� ���������� ����
	n = _n, m = _m, x = _x, y = _y, r = _r, c = _c, k = _k;

	// solve
	dfs(x, y, 0);

	// return
	if (answer == "") return "impossible"; // ���� ��ã�Ҵٸ� impossible ��ȯ
	return answer;
}

//int main() {
//	cout << solution(3, 4, 2, 3, 3, 1, 5) << "\n";
//
//	return 0;
//}