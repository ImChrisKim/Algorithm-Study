/* ���� */
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 300
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 1, 0, 0 };
int cdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // ����
int visited[MAX_N][MAX_N]; // �湮���� ����

int N, M; // ���� ������ (N*M)

void bfs(int r, int c) {
	int TMP[MAX_N][MAX_N] = { 0, }; // �̹� �Ͽ� �پ�� ������ ���̸� ����

	// bfsŽ���� ���� queue �غ�
	queue<pair<int, int>> q;
	q.push({ r, c });

	visited[r][c] = 1; // �湮 ǥ��

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		int cnt = 0; // nowĭ ���� 4������ Ž���Ͽ� ���̰� 0�� ĭ�� ��
		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.first + rdir[i];
			int nc = now.second + cdir[i];

			// ���̰� 0�� ĭ�� cnt�� ���� ��������
			// 0�� ĭ�� bfs Ž���� ����� �ƴϴ�
			if (MAP[nr][nc] == 0) {
				cnt++;
				continue;
			}

			if (visited[nr][nc] == 1) continue; // ��湮�� ĭ�� ����
			visited[nr][nc] = 1; // �湮 ó��
			q.push({ nr, nc });
		}

		TMP[now.first][now.second] = cnt; // �ֺ��� 0�� ĭ�� ������ ����
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// �پ�� ������ ���̸�ŭ ����ֱ�
			MAP[i][j] -= TMP[i][j];
			if (MAP[i][j] < 0) MAP[i][j] = 0; // ������ �Ǿ��ٸ� 0���� �����ֱ�
		}
	}
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve
	int ans = 0; // Ž�� ����Ǵµ� �ɸ� �ð�
	while (1) {
		memset(visited, 0, sizeof(visited)); // �� �ϸ��� visited �ʱ�ȭ
		int cnt = 0; // ���� �׷� ����
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] > 0 && visited[i][j] == 0) { // ������ ���������鼭 �̹湮�� ĭ���� Ž��
					bfs(i, j); // (i, j)���� Ž�� ����
					cnt++; //���� �׷� ����
				}
			}
		}

		// �׷��� 2�� �̻��̸� Ž�� ����
		// �׷��� 1���̸� Ž�� ���
		// �׷��� 0���̸� 1������ �׷��� ���ÿ� ����� ���̹Ƿ� Ž�� ����
		if (cnt >= 2) break;
		else if (cnt == 0) {
			ans = 0;
			break;
		}

		ans++; // �ð� ����
	}

	// output
	cout << ans;

	return 0;
}