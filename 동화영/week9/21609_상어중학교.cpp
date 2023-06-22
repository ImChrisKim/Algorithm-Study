/* ��� ���б� */
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 20
#define DIR_NUM 4

// ��� �׷�
struct Node {
	int cnt; // ����� ����
	int rainbow; // ����������� ����
	int y; // ���� ����� ��ǥ
	int x;

	bool operator < (Node nxt) const {
		if (cnt > nxt.cnt) return false;
		if (cnt < nxt.cnt) return true;
		if (rainbow > nxt.rainbow) return false;
		if (rainbow < nxt.rainbow) return true;
		if (y > nxt.y) return false;
		if (y < nxt.y) return true;
		if (x > nxt.x) return false;
		if (x < nxt.x) return true;
		return false;
	}
};

int ydir[DIR_NUM] = { -1, 1, 0, 0 };
int xdir[DIR_NUM] = { 0, 0, -1, 1 };

priority_queue<Node> pq;

int visited[MAX_N][MAX_N];
int MAP[MAX_N][MAX_N]; // -2: ��ĭ, -1: ������, 0: ������, 1~M: �Ϲ�
int N, M; // N: ���� ������, M: �Ϲ� ��� ������ ��

int ans; // ȹ�� ����

// ��� �׷� Ž��
// ã�� �׷��� ��� ���� ��ȯ
int findGroup(int cy, int cx) {
	int color = MAP[cy][cx]; // ���� ����� ����
	int oriy = cy, orix = cx; // ���� ��� ��ǥ (y, x)
	int eCnt = 1, rCnt = 0; // eCnt: �׷� �� ����� �� ����, rCnt: �׷� �� ����������� ����

	// bfsŽ���� ���� used�迭�� queue �غ�
	int used[MAX_N][MAX_N] = { 0, };
	used[cy][cx] = 1;
	queue<pair<int, int>> q;
	q.push({ cy, cx });

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // ���� ���� ����
			if (used[ny][nx] == 1) continue; // ��湮�� ĭ�� ����
			if (MAP[ny][nx] < 0) continue; // �Ϲ�/������ ��ϸ� Ž��
			if (MAP[ny][nx] > 0 && MAP[ny][nx] != color) continue; // �Ϲ� ��� �߿����� ���� ����� ����� ���� ������ Ž��

			// (ny, nx) �湮 Ž��
			q.push({ ny, nx });
			used[ny][nx] = 1;
			
			if (MAP[ny][nx] > 0) { // �Ϲ� ���
				// ��ü �湮��Ͽ� ����
				visited[ny][nx] = 1;

				// �׷��� ���� ��� ����
				// �� �ּ� -> �� �ּ�
				if (ny < oriy) {
					oriy = ny;
					orix = nx;
				}
				else if (ny == oriy) {
					if (nx < orix) {
						orix = nx;
					}
				}
			}
			// ������ ��� - ���� ����
			// ������ ����� ��ü �湮��Ͽ� �������� �ʴ´�
			// Ž�� ���� ��ġ�� �Ϲ� ��� �������� �Ǵ��ϹǷ�
			else rCnt++;

			eCnt++; // ����� �� ���� ����
		}
	}

	if(eCnt > 1) pq.push({ eCnt, rCnt, oriy, orix }); // ��� ������ 2�� �̻��� �׷��̶�� pq�� �߰�

	return eCnt; // ��� Ž���� �׷��� �� ��� ������ ��ȯ
}

// ���� ū ��� �׷��� ����
void Remove() {
	Node t = pq.top(); // �켱���� �������� �ִ� ��� �׷� ����
	while (!pq.empty()) pq.pop(); // �������� pop

	int color = MAP[t.y][t.x]; // ������ ��� �׷��� ���� ����
	MAP[t.y][t.x] = -2; // �����Ͽ� ��ĭ ó��

	int used[MAX_N][MAX_N] = { 0, }; // Ÿ�� �׷��� �����ϴµ� ���
	used[t.y][t.x] = 1;

	queue<pair<int, int>> q; // bfs Ž���� ���� queue �غ�
	q.push({ t.y, t.x });

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // ���� ���� ����
			if (used[ny][nx] == 1) continue; // ��湮�� ĭ�� ����
			if (MAP[ny][nx] < 0) continue; // �Ϲ�/������ ��ϸ� Ž��
			if (MAP[ny][nx] > 0 && MAP[ny][nx] != color) continue; // �Ϲ� ��� �߿����� Ÿ�� ����� ������ ��ϸ� Ž��

			// Ž���� (ny, nx) ��� �湮 ó�� �� ��ĭ ó��
			q.push({ ny, nx });
			used[ny][nx] = 1;
			MAP[ny][nx] = -2;
		}
	}

	ans += (t.cnt*t.cnt); // ������ ����� ����^2 ��ŭ ���� ȹ��
}

// �߷� �ۿ�
void Gravity() {
	for (int i = 0; i < N; i++) { // �� ���� ����
		int ind = N - 1; // ���� �Ϲ�/������ ����� ������ �� ind������ ����� ����߸���
		for (int j = N - 1; j >= 0; j--) { // �ؿ������� �� ���� Ž��
			if (MAP[j][i] == -2) {
				// �� ĭ�̸� �׳� �о�
			}
			else if (MAP[j][i] == -1) { // ���� �����ٸ� 
				ind = j - 1; // ���� ����� �� �� �ٷ� ���� ��������
			}
			else if (MAP[j][i] >= 0) { // �Ϲ�/������ ����� �����ٸ�
				// ind������ ��� ����߸���
				// ����߸��� j���� -2(��ĭ)���� ��������� �ϱ� ������
				// tmp�� ���
				int tmp = MAP[j][i];
				MAP[j][i] = -2;
				MAP[ind][i] = tmp;
				ind--; // ���� ����� �� ���� ��������
			}
		}
	}
}

// �ݽð� 90�� ȸ��
void Rotate() {
	int TMP[MAX_N][MAX_N] = { 0, };

	// �ε��� ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			TMP[N - j - 1][i] = MAP[i][j];
		}
	}

	memcpy(MAP, TMP, sizeof(MAP));
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve
	while (1) {
		// �� �ϸ��� �׷� ������ �Ͽ������� üũ����� �ϱ� ������ �Ź� �ʱ�ȭ �ʿ�
		memset(visited, 0, sizeof(visited));

		int cnt = 0; // �̹� �Ͽ� ������ �׷��� ��
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 1. �Ϲ� ����̸鼭 �̹湮�� ĭ�� �������� �׷� Ž��
				// �� �׷쿡 �Ϲ� ����� �ּ� 1�� �ʿ��ϱ� ������ �������� �Ϲ� ������� ���
				if (MAP[i][j] > 0 && visited[i][j] == 0) {
					// (i, j) ���� ������ �׷� Ž��
					// �ش� �׷��� ��� ���� ��ȯ
					int tmp = findGroup(i, j);
					if (tmp > 1) cnt++; // �� �׷쿡�� �ּ� 2�� �̻��� ����� ���ԵǾ�� �Ѵ�
				}
			}
		}
		if (cnt == 0) break; // ������ �׷��� 0����� ����

		Remove(); // 2. 1���� ã�� �ִ� ��� �׷� ����

		Gravity(); // 3. �߷� �ۿ�
		Rotate(); // 4. �ݽð� 90�� ȸ��
		Gravity(); // 5. �߷� �ۿ�
	}

	// output
	cout << ans;

	return 0;
}