/* ���ο� ���� 2 */
#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 14 /// MAX_N�� 13���� �����߾��..... OutOfBounds �߻�.......
#define DIR_NUM 4

struct Horse {
	int y; // ��ġ
	int x;
	int dir; // �̵����� - �����Ͽ�
};

int ydir[DIR_NUM] = { -1, 0, 1, 0 }; // �����Ͽ�
int xdir[DIR_NUM] = { 0, -1, 0, 1 };

vector<Horse> horses; // ���� ����

// �� �Ʒ��� ���� vector�� �� �տ� ��ġ�Ѵٰ� ����
vector<int> INFO[MAX_N][MAX_N]; // ������ ��ġ(ind�� ǥ��, 1~K)
int MAP[MAX_N][MAX_N]; // ü������ ����(0:��, 1:��, 2:��)
int N, K;

// ind�� �� �̵��ϱ�
int moveInd(int ind) {
	Horse now = horses[ind];

	// �� �������� ind�� ���� �̵��Ѵٸ� �� ��ġ (ny, nx)
	int ny = now.y + ydir[now.dir];
	int nx = now.x + xdir[now.dir];

	if (MAP[ny][nx] == 0) { // ��� ĭ
		// ind�� ���� ���� ��ġ�� ĭ�� ������ ���鼭
		// ind�� ���� �� ��°�� �ִ����� ã��
		int sz = INFO[now.y][now.x].size();
		for (int i = 0; i < sz; i++) {
			if (INFO[now.y][now.x][i] == ind) {
				// i ~ ������ ������� (ny, nx)�� �̾� ���δ�
				for (int j = i; j < sz; j++) {
					int num = INFO[now.y][now.x][j];
					INFO[ny][nx].push_back(num);

					horses[num].y = ny;
					horses[num].x = nx;
				}
				// ������ ��ġ������ pop���ֱ�
				for (int j = i; j < sz; j++) {
					INFO[now.y][now.x].pop_back();
				}
				break; // �̵����״ٸ� �Ϸ�
			}
		}
		
		if (INFO[ny][nx].size() >= 4) return 4; // �̵��� ĭ(ny, nx)�� ���� 4�� �̻��̶�� 4 ��ȯ
	}
	else if (MAP[ny][nx] == 1) { // ������ ĭ
		int sz = INFO[now.y][now.x].size();
		for (int i = 0; i < sz; i++) {
			if (INFO[now.y][now.x][i] == ind) {
				// i ~ �������� ���� �ݴ��
				// ��, �� ~ i�������� ���� (ny, nx)�� �̾� ���δ�
				for (int j = sz - 1; j >= i; j--) {
					int num = INFO[now.y][now.x][j];
					INFO[ny][nx].push_back(num);

					horses[num].y = ny;
					horses[num].x = nx;

					// ������ ��ġ������ pop���ֱ�
					// ���⼭�� �� �ڿ������� (ny, nx)�� ���̱� ������
					// for�� �ȿ� pop ���൵ ������
					INFO[now.y][now.x].pop_back();
				}
				break; // �̵����״ٸ� �Ϸ�
			}
		}

		if (INFO[ny][nx].size() >= 4) return 4; // �̵��� ĭ(ny, nx)�� ���� 4�� �̻��̶�� 4 ��ȯ
	}
	else { // �Ķ��� ĭ
		horses[ind].dir = (horses[ind].dir + 2) % DIR_NUM; // ���� �ݴ�� ��ȯ

		// ���� ��ȯ ���� ��ġ
		now = horses[ind];
		ny = now.y + ydir[now.dir];
		nx = now.x + xdir[now.dir];

		// ���� ��ȯ �Ŀ� �� ��ġ�� �Ķ��� ĭ�̶�� �״�� �̵� ��
		// �Ķ��� ĭ�� �ƴ϶�� ind�� ���� moveInd() ȣ�� -> ��|���� ĭ �� �ϳ��̹Ƿ�
		if (MAP[ny][nx] != 2) {
			if (moveInd(ind) == 4) return 4; // �̵��� ĭ(ny, nx)�� ���� 4�� �̻��̶�� 4 ��ȯ
		}
	}

	return 0; // ��� ĭ�� ��ġ�� ���� ������ 4�� �̸��̶�� 0 ��ȯ - ��, ���� ���� ���� ����
}

// ��� ���� 1������ ������� �̵��ϱ�
int moveAll() {
	int sz = horses.size();
	for (int i = 1; i < sz; i++) {
		if (moveInd(i) >= 4) return 1; // 4�� ��ȯ�޾Ҵٸ� ���� ����
	}

	return 0; // �� ĭ�� 4�� �̻��� ���� �������� �ʴ´ٸ� 0 ��ȯ (���� ���� ���� X)
}

int main() {
	// input
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	// ü������ ����� ��쿡�� �Ķ����� �����ϰ� �����ϹǷ�
	// ü������ 2�� �ѷ��ش�
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1) MAP[i][j] = 2;
		}
	}

	horses.push_back({ 0,0,0 }); // �� ������ 0�� �ε��� ä��� - �ε��� �����ֱ�
	// ���� ���� ����
	int iy, ix, id;
	for (int i = 1; i <= K; i++) {
		cin >> iy >> ix >> id;
		
		id = id == 1 ? 3 : id == 2 ? 1 : id == 3 ? 0 : 2; // �����Ͽ� ������ dir �����Ͽ� ����
		horses.push_back({ iy, ix, id });
		INFO[iy][ix].push_back(i); // INFO ü���ǿ� �� ��ȣ push
	}

	int turn = 1;
	while (turn <= 1000) { // �ִ� 1000���� ��
		if(moveAll() == 1) break; // �� ĭ�� 4�� �̻��� ���� �ִ� ��� Ž�� ����

		turn++;
	}

	if (turn > 1000) turn = -1; // 1000�� Ž���Ͽ������� ������ ������ �ʾҴٸ� -1 ���
	cout << turn;

	return 0;
}

/*
4 4
2 2 2 2
0 0 0 0
2 2 2 2
0 0 0 0
1 1 3
1 2 3
1 3 3
1 4 3
*/