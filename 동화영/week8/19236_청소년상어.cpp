/* û�ҳ� ��� */
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define SIZE_N 4
#define SIZE_F 17
#define DIR_NUM 8

struct FISH {
	int y; // ��ǥ
	int x;
	int dir; // ����
	int alive; // ����ִ°�
};

int ydir[DIR_NUM] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // ��, �»�, ��, ..., ���
int xdir[DIR_NUM] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int MAP[SIZE_N][SIZE_N]; // -1: ���, 0: ��ĭ, 1~16: �����
FISH INFO[SIZE_F]; // ���� �������� ���� (0: ���, 1~16: �����)

int ans; // �ִ밪 (��)
int sum; // û�ҳ� �� ��Ƹ��� �������� ��ȣ�� ��

// �ʿ����� ����� �̵�(��ȣ �������)
void moveFish() {
	for (int i = 1; i < SIZE_F; i++) {
		FISH now = INFO[i];
		if (now.alive == 1) { // ����ִ� ����⸸ �̵��Ѵ�
			// ������ �������� �̵� �Ұ��ϴٸ�
			// �ѹ��� ���鼭 �ٸ� �������� �̵� �����Ѱ��� �Ǵ�
			for (int j = 0; j < DIR_NUM; j++) {
				int nDir = (now.dir + j) % DIR_NUM;

				int ny = now.y + ydir[nDir];
				int nx = now.x + xdir[nDir];

				if (ny < 0 || nx < 0 || ny >= SIZE_N || nx >= SIZE_N) continue;// ���� ���� �̵� �Ұ�
				if (MAP[ny][nx] == -1) continue; // �� �ִ� ĭ�� �̵� �Ұ�

				if (MAP[ny][nx] == 0) { // ��ĭ - i�� ����⸸ �̵�
					MAP[now.y][now.x] = 0;
					MAP[ny][nx] = i;

					INFO[i] = { ny, nx, nDir, 1 }; // ��ġ�� ���� ����
					break;
				}
				else { // �ٸ� ����Ⱑ �ִ� ĭ - i�� ������ (ny, nx)�� ����Ⱑ �ڸ� ����
					int tmp = MAP[ny][nx];
					MAP[ny][nx] = MAP[now.y][now.x];
					MAP[now.y][now.x] = tmp;

					INFO[tmp].y = now.y;
					INFO[tmp].x = now.x;
					INFO[i] = { ny, nx, nDir, 1 }; // ��ġ�� ���� ����
					break;
				}
			}
		}
	}
}

// ����Ⱑ �̵��� �� �� �����δ�
void move() {
	// �������� �̵��ϱ� ���� ������ ������ ����� ������ �����Ѵ�
	int TMP[SIZE_N][SIZE_N] = { 0, };
	FISH TMP_FISH[SIZE_F] = { 0, };
	memcpy(TMP, MAP, sizeof(MAP));
	memcpy(TMP_FISH, INFO, sizeof(INFO));

	moveFish(); // ������ �̵�

	int isMoved = 0; // �̹� �Ͽ� �� �̵��� ĭ�� �ִ°�?
	FISH shark = INFO[0]; // ����� ����
	for (int i = 1; i <= SIZE_N; i++) { // ���� �������δ� �� ĭ�̵� �̵� ����
		int ny = shark.y + ydir[shark.dir] * i;
		int nx = shark.x + xdir[shark.dir] * i;

		if (ny < 0 || nx < 0 || ny >= SIZE_N || nx >= SIZE_N) break; // ���� ������ ����ٸ� ���̻� �̵� �Ұ�
		if (MAP[ny][nx] == 0) continue; // �� ĭ�� �̵� �Ұ�

		isMoved = 1; // �̹� �Ͽ� ��� �̵��ߴ�
		int target = MAP[ny][nx]; // �̹��� ��Ƹ��� ����� ��ȣ

		// �� target�� ����⸦ ��ƸԴ´�
		MAP[shark.y][shark.x] = 0;
		MAP[ny][nx] = -1;
		sum += target;
		INFO[target].alive = 0;
		INFO[0] = { ny, nx, INFO[target].dir, 1 };

		move(); // ���� ������ ����

		// ���� �� Ž���� ���ƴٸ� target�� ����� ��Ƹ��� ���� ���� - target�� ����� �츮��
		INFO[0] = shark;
		INFO[target].alive = 1;
		sum -= target;
		MAP[ny][nx] = target;
		MAP[shark.y][shark.x] = -1;
	}

	// �� ���� ������ �̵� ���� ������ ������ �ٽ� �����ϱ�
	memcpy(MAP, TMP, sizeof(TMP));
	memcpy(INFO, TMP_FISH, sizeof(TMP_FISH));

	// �� �̵��� �� �ִ� ĭ�� ���ٸ�
	if (isMoved == 0) {
		if (sum > ans) ans = sum; // �ִ밪 ���� �� ����
		return;
	}
}

int main() {
	// input
	int ia, ib;
	int tmp = 1;
	for (int i = 0; i < SIZE_N; i++) {
		for (int j = 0; j < SIZE_N; j++) {
			cin >> ia >> ib;
			MAP[i][j] = ia;
			INFO[ia] = { i, j, ib - 1, 1 }; // ����� ���� ����
		}
	}

	// 0. �� (0,0)�� ����⸦ �����鼭 �����Ѵ�
	sum += MAP[0][0];
	INFO[MAP[0][0]].alive = 0;
	INFO[0] = { 0, 0, INFO[MAP[0][0]].dir, 1 };
	MAP[0][0] = -1;

	move();

	// output
	cout << ans << "\n";

	return 0;
}