/* �ֻ��� ������ */
// play ��Ȳ - 0(����) ~ 42(����)
// �⺻ �̵� map - ���� ĭ�� ��´�
// �Ķ�ĭ���� �����Ѵٸ� ���ο� map���� ����
// Ư�� map�� ���� ĭ�� ����Ų��
// ���� �⺻orƯ�� map�� �ִ°��� �����ϴ� KIND

// ��� ����� ���� �� ���� dfs
// �� 4���� ���� ��ġ

#include <iostream>
#include <vector>
using namespace std;

struct NODE {
	int ind; // map ����
	int num; // map �� ��ġ
};

// [5][22]
vector<int> MAP[5]; // ������ �� - 0:�⺻, 1~3:�Ķ�ȭ��ǥ ���� ����, 4: 25���� ����
int used[5][22]; // ���� ���� �����ϴ°� �ƴѰ��� ǥ��
NODE player[4]; // 4���� ���� ����ġ

int dice[10]; // �ֻ��� ���� (1~5)

int ans; // �ִ� ���� (��)

void init() {
	// �⺻ �� �ʱ�ȭ - ���� �ٱ� ����
	for (int i = 0; i <= 21; i++) {
		MAP[0].push_back(i * 2); // �� ĭ�� ����
	}

	MAP[1].push_back(10); MAP[1].push_back(13); MAP[1].push_back(16); MAP[1].push_back(19); MAP[1].push_back(25);
	MAP[2].push_back(20); MAP[2].push_back(22); MAP[2].push_back(24); MAP[2].push_back(25);
	MAP[3].push_back(30); MAP[3].push_back(28); MAP[3].push_back(27); MAP[3].push_back(26); MAP[3].push_back(25);
	MAP[4].push_back(25); MAP[4].push_back(30); MAP[4].push_back(35); MAP[4].push_back(40); MAP[4].push_back(42);

	// �� �ʱ�ȭ
	for (int i = 0; i < 4; i++) {
		player[i] = { 0, 0 };
	}
}

void play(int turn, int sum) {
	// �������� - 10���� ���� �� ���Ҵٸ� ���� ���� �� ����
	if (turn == 9) {
		if (sum > ans) ans = ans;

		return;
	}

	// 4���� �� �� �̵��� �����ϴٸ� �̵���Ų �� ���� �÷��̷� �Ѿ��
	for (int i = 0; i < 4; i++) {
		NODE now = player[i];

		if (MAP[now.ind][now.num] == 42) continue; // �̹� ������ ���� �̵� �Ұ�
		
		int dInd = 0, dNum = 0;
		if (now.num + dice[turn] > MAP[now.ind].size()) {
			if (now.ind == 0) {
				dInd = 0; dNum = 21;
			}
			else {

			}
		}
		else {
			 
		}
	}
}

int main() {
	init(); // ��������, �� �ʱ�ȭ
	
	// input
	for (int i = 0; i < 10; i++) cin >> dice[i];

	play(i, 0);

	cout << ans;

	return 0;
}