/* �� */
#include <iostream>
#include <queue>
using namespace std;
#define MAX_N 101
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // �����Ͽ�
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

queue<pair<int, char>> corner; // ���� ���� ��ȯ ����
int APPLE[MAX_N][MAX_N]; // ��� ��ġ ����
int MAP[MAX_N][MAX_N]; // ���� ��ġ ���� �����
int N; // ���� ������

pair<int, int> head, tail; // ���� �Ӹ��� ����
int dir; // ���� ����

// �� �̵�
int move() {
	// ���� �������� ���� �� �� �Ӹ��� ���� ��ġ
	int nr = head.first + rdir[dir];
	int nc = head.second + cdir[dir];

	// �� Ȥ�� ���� ���� �ε����� ���� ����
	if ((nr < 1 || nc < 1 || nr > N || nc > N) || MAP[nr][nc] > 0) {
		return 0;
	}

	// ���� �Ӹ� �̵�
	MAP[nr][nc] = MAP[head.first][head.second] + 1; // �����Ҽ��� ���� ���� -> �� ������ �̵���� �ľ��� ����
	head = { nr, nc };

	// �̵��� ���⿡ ����� �ִٸ�
	if (APPLE[nr][nc] == 1) {
		APPLE[nr][nc] = 0; // ��� �԰� ������ �̵� X
	}
	// ����� ���ٸ�
	else {
		// ���� ���� 4���� Ž���Ͽ� ���� �ٷ� ��ĭ�� �߰� �� ���� ������ �̵�
		for (int i = 0; i < DIR_NUM; i++) {
			int nxtR = tail.first + rdir[i];
			int nxtC = tail.second + cdir[i];

			if (MAP[nxtR][nxtC] == MAP[tail.first][tail.second] + 1) {
				MAP[tail.first][tail.second] = 0;
				tail = { nxtR, nxtC };
				break;
			}
		}
	}

	return 1; // ���� �̵� �� 1 ��ȯ
}

int main() {
	// input
	int K, L, X, a, b;
	char C;
	int timer = 0; // �ҿ� �ð�

	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> a >> b;
		APPLE[a][b] = 1; // ��� ����
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		corner.push({ X,C }); // ���� ���� ��ȯ ����
	}

	// init - �ʱ� ����
	dir = 3;
	MAP[1][1] = 1;
	head = { 1, 1 };
	tail = { 1, 1 };

	// solve
	while (1) {
		++timer; // �ð� �߰�

		// 1. �� �̵�
		// 0 ��ȯ�� ���� ����
		if(move() == 0) break;

		// 2. ���� ������� �ٲ� Ÿ�̹��̶�� �ٲ��ֱ�
		if (!corner.empty() && corner.front().first == timer) {
			pair<int, char> turn = corner.front();
			corner.pop();

			if (turn.second == 'L') dir = (dir + 1) % DIR_NUM; // �������� 90�� ȸ�� 
			else if (turn.second == 'D') dir = (dir - 1 + DIR_NUM) % DIR_NUM; // ���������� 90�� ȸ��
		}
	}

	// output
	cout << timer;

	return 0;
}