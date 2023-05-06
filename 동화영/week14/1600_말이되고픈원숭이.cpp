/* ���� �ǰ��� ������ */
#include <iostream>
#include <queue>
using namespace std;
#define MAX_W 200
#define HOR_NUM 8
#define DIR_NUM 4

struct Node {
	int r;
	int c;
	int hcnt;
};

int hrdir[HOR_NUM] = { -2, -1, 1, 2, 2, 1, -1, -2 }; // ���� ������
int hcdir[HOR_NUM] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // �����Ͽ�
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

int visited[MAX_W][MAX_W][31] = { 0, }; // �湮 ���� - visited[r][c][a] = ���� �������� a�� ����Ͽ� (r,c)�� �����ϴµ� �ɸ� �̵� Ƚ��
int MAP[MAX_W][MAX_W]; // ��ֹ� ���� ǥ��
int H, W; // ���� ������ (H * W)
int K; // ���� ������ ���� Ƚ��

int Move() {
	// BFS �غ�
	queue<Node> q;

	visited[0][0][0] = 1;
	q.push({ 0, 0, 0 });

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		int cnt = now.hcnt;

		// ���������� �߰��ߴٸ� ��ȯ (���������� visited ���� 1�̾��⿡ -1 ó���Ͽ� ��ȯ)
		if (now.r == H - 1 && now.c == W - 1) return visited[H - 1][W - 1][cnt] - 1;

		if (cnt < K) { // ���� ���� �������� �����ϴٸ� ���� ���������� �̵�
			for (int i = 0; i < HOR_NUM; i++) {
				int nr = now.r + hrdir[i];
				int nc = now.c + hcdir[i];

				if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue; // ���� ���� ����
				if (MAP[nr][nc] == 1) continue; // ��ֹ� ĭ�� �̵� �Ұ�
				// ����ĭ���� ���� ������ 1�� ����Ͽ� (nr, nc)�� ������ ���̱⿡
				// (nr, nc)�� ������ �� ���� ������ ���Ƚ���� cnt + 1 �̴�
				if (visited[nr][nc][cnt + 1] > 0 && visited[nr][nc][cnt + 1] <= visited[now.r][now.c][cnt] + 1) continue;

				// ���� ĭ Ž�� ����
				q.push({ nr, nc, cnt + 1 });
				visited[nr][nc][cnt + 1] = visited[now.r][now.c][cnt] + 1;
			}
		}

		// �������� �������� �׻� ����
		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.r + rdir[i];
			int nc = now.c + cdir[i];

			if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue; // ���� ���� ����
			if (MAP[nr][nc] == 1) continue; // ��ֹ� ĭ�� �̵� �Ұ�
			// �������� �������̱⿡ ���� ������ ��� Ƚ���ʹ� ����
			if (visited[nr][nc][cnt] > 0 && visited[nr][nc][cnt] <= visited[now.r][now.c][cnt] + 1) continue;

			// ���� ĭ Ž�� ����
			q.push({ nr, nc, cnt });
			visited[nr][nc][cnt] = visited[now.r][now.c][cnt] + 1;
		}
	}


	return -1;
}

int main() {
	// input
	cin >> K >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve & output
	cout << Move() << "\n";

	return 0;
}