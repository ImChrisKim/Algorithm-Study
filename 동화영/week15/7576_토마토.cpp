/* �丶�� */
#include <iostream>
#include <queue>
using namespace std;
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // �����Ͽ�
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

// bfs Ž���� ���� queue�� visited
queue<pair<int, int>> q;
int visited[1000][1000];

int MAP[1000][1000]; // �丶�� ���� - -1:��ĭ 0:������ �丶�� 1:���� �丶��
int N, M; // N * M
int unripe; // ���� ���� �丶���� ��
int days; // �ҿ� �ð�

int main() {
	// input
	cin >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 0) unripe++; // ���� ���� �丶���� �� ����
			else if (MAP[i][j] == 1) { // ���� �丶��� Ž�� �غ��ϱ�
				q.push({ i, j });
				visited[i][j] = 1;
			}
		}
	}

	// ���� Ž�� ���� �� ���� ���� �丶�䰡 �ϳ��� �ִٸ� while�� ����
	// ���ٸ� �ٷ� 0 ����Ϸ� �Ʒ��� ����
	if (unripe != 0) {
		while (!q.empty() && unripe > 0) {
			int sz = q.size(); // ���� ���� ���� �丶���� ��
			days++;
			
			// ���ں��� �丶�� Ž���ϱ� -> �ҿ� �ϼ��� ���ϱ� ����
			for (int i = 0; i < sz; i++) {
				pair<int, int> now = q.front();
				q.pop();

				for (int j = 0; j < DIR_NUM; j++) {
					int nr = now.first + rdir[j];
					int nc = now.second + cdir[j];

					if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue; // ���� ���� ����
					if (visited[nr][nc] == 1) continue; // ��湮�� ĭ�� ����
					if (MAP[nr][nc] == -1) continue; // �丶�䰡 ���� ĭ�� ����

					// ���� Ž���� ĭ���� �߰�
					q.push({ nr, nc });
					visited[nr][nc] = 1;
					unripe--; // (nr, nc)ĭ�� ���� �;����Ƿ� unripe ���ҽ�Ű��
				}
			}
		}
	}

	// Ž�� ���Ŀ��� ���� ���� �丶�䰡 �Ѱ��� �ִٸ� ���� ���� �� ���� �丶���̴�
	// -1�� ��� (���� �丶����� �������� ���ÿ� ��ü Ž���� �ϹǷ�)
	if (unripe != 0) days = -1;

	// output
	cout << days << "\n";

	return 0;
}