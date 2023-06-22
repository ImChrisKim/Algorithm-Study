/* ������ ���� ���̾�� */
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
#define MAX_N 64
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 1, 0, 0 };
int cdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // ����
int N; // ������ �ǻ����� N*N

int visited[MAX_N][MAX_N]; // ���� ��� �� ���� �� ���
int sum; // �������� �����ִ� ������ �� ��

// �κ� ���ڸ� �ð�������� 90�� ȸ��
void rotate(int lev) {
	int level = pow(2, lev); // �κ� ������ �ǻ�����
	int TMP[MAX_N][MAX_N] = { 0, }; // ȸ���� ����� ������ �迭

	// ��� ĭ�� ���� �κа��ڷ� �ɰ��ٸ� �� ĭ�� (indR, indC) �׷쿡 �ִ�
	// ���� (indR, indC) �׷� ������ ȸ���� �Ͼ�� => indR*level�� indC*level�� ���� ���� => TMP[indR * level][indC * level]
	// MAP (0, 0) (0, 1) (0,2) (0,3) -> TMP (0,3) (1,3) (2,3) (3,3)���� �̵� => ��->��, ��->�� �� ���� => TMP[j][i]
	// (indR, indC) �׷� ó���� ����� ������ �� ĭ�� ���� �ε����� %(������) �����Ͽ� �� ��°�������� ��� => TMP[j % level][i % level]
	// TMP�� ���� MAP�� ���� level �������� ����ó���ؾ��Ѵ� => TMP[][level -1 - i]
	// ���� ������׵��� ���Ѵٸ� �Ʒ��� �ε��� ����� ���´�
	for (int i = 0; i < N; i++) {
		int indR = i / level;
		for (int j = 0; j < N; j++) {
			int indC = j / level;
			TMP[indR * level + j % level][indC * level + level - 1 - i % level] = MAP[i][j];
		}
	}

	memcpy(MAP, TMP, sizeof(MAP)); // ȸ���� ����� MAP���� ����
}

// �ֺ��� ������ �ִ� ĭ�� 3ĭ �̸���
// �ش� ĭ�� ���� �پ��� -1
void shrink() {
	int tmp[MAX_N][MAX_N] = { 0, }; // ������ �پ�� ĭ ǥ���

	// ��� ĭ�� ���� Ž���Ѵ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == 0) continue; // ���� ĭ�� �̹� ������ 0�̶�� Ž�� X

			// 4���� Ž���ϸ� �ֺ��� ������ �ִٸ� ice �����ؼ� ǥ���ϱ�
			int ice = 0;
			for (int k = 0; k < DIR_NUM; k++) {
				int nr = i + rdir[k];
				int nc = j + cdir[k];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // ���� ���� ����
				if (MAP[nr][nc] == 0) continue; // �ֺ��� ������ 0�� ĭ�� ice ���� X

				ice++;
			}
			if (ice < 3) tmp[i][j] -= 1; // ���� �پ��� ĭ ǥ��
		}
	}

	// ������ �پ��ٸ� �پ��� ������ŭ �����ֱ�(-1)
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (tmp[i][j] != 0) MAP[i][j] += tmp[i][j];
}

// ���� �����ִ� ������ �� ���� ū ��� ã��
int bfs(int r, int c) {
	int cnt = 0; // ����� ĭ ��

	// (r, c)���� Ž�� ����
	queue<pair<int, int>> q;
	q.push({ r, c });
	visited[r][c] = 1; // �湮 ó��
	cnt++; // ����� ĭ �� ++
	sum += MAP[r][c]; // �����ִ� ������ �絵 �����ֱ�

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.first + rdir[i];
			int nc = now.second + cdir[i];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // ���� ���� ����
			if (visited[nr][nc] == 1) continue; // �̹� �湮�� ĭ�� ����
			if (MAP[nr][nc] == 0) continue; // ������ 0�̶�� Ž�� X

			// ���� Ž���� ĭ�� ���� ó��
			q.push({ nr, nc });
			visited[nr][nc] = 1; // �湮 ó��
			cnt++; // ����� ĭ �� ++
			sum += MAP[nr][nc]; // �����ִ� ������ �絵 �����ֱ�
		}
	}

	return cnt;
}

int main() {
	 // input
	int szN, Q; // szN : ���� ������(2^szN) Q : ���̾�� Ƚ��
	cin >> szN >> Q;

	N = pow(2, szN); // ������ �ǻ�����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// �� ���������� level�� ȸ���� ���� �پ��⸦ �ݺ� ����
	int level;
	for (int i = 0; i < Q; i++) {
		cin >> level;

		rotate(level);
		shrink();
	}

	int cnt = 0; // ���� ���
	int ans = 0; // ���� ū ���� ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// (i,j)�� ������ �����鼭 ���� �湮���� �ʾҴٸ� bfs Ž��
			// ��ȯ���� cnt(����� ĭ ��)�� ans�� ���Ͽ� ����
			if (MAP[i][j] > 0 && visited[i][j] == 0) {
				cnt = bfs(i, j);
				if (ans < cnt) ans = cnt;
			}
		}
	}

	cout << sum << "\n" << ans << "\n";

	return 0;
}