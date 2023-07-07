// 17142 ������3
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX_N 50

struct NODE {
	int r;
	int c;
};

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

vector<NODE> viruses; // �ʱ� ��Ȱ�� ���̷������� ��ġ
vector<int> vec; // ������ ���� vector
int MAP[MAX_N][MAX_N]; // �ʱ� ��
int N, M; // N: �� ������, M: Ȱ��ȭ��ų ���̷����� ��
int notWall; // �� ĭ�� ��

int bfs() {
	int cnt = 0, ret = 1; // cnt: �۶߷��� �� ĭ�� ��, ret: �ҿ�ð�
	// bfs�� ���� ����
	int visited[MAX_N][MAX_N] = { 0, };
	queue<NODE> q;

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == 1) { // �̹� �Ͽ� Ȱ��ȭ��ų ���̷������� ����
			visited[viruses[i].r][viruses[i].c] = 1;
			q.push({ viruses[i].r, viruses[i].c });
		}
	}

	while (!q.empty()) {
		NODE now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = now.r + dr[i];
			int nc = now.c + dc[i];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // ���� ���� ����
			if (visited[nr][nc] > 0) continue; // ��湮�� ĭ�� ����
			if (MAP[nr][nc] == 1) continue; // ���� ���� �Ұ�

			q.push({ nr, nc }); // Ž�� ����
			if(MAP[nr][nc] == 0) cnt++; // �� ĭ�� ���� ���޽� cnt ����

			visited[nr][nc] = visited[now.r][now.c] + 1; // �� ĭ�� �����ϴµ� �ҿ�ð� ����
			if(MAP[nr][nc] != 2) ret = visited[nr][nc]; // �� ĭ�� ��� �ҿ�ð� ����(��Ȱ�� ���̷����� ��� X)
		}
	}
	
	if (cnt < notWall) return 213456789; // ��� ĭ�� ���� ���� ���
	return ret - 1; // ��ȯ (1�� �����Ͽ����Ƿ� -1 �ؼ� ��ȯ)
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2) viruses.push_back({ i, j }); // ���̷��� ��ġ ����
			if (MAP[i][j] == 0) notWall++; // �� ĭ�� �� ����
		}
	}

	int ans = 213456789;; // ��
	// ������ ���� ���� ����
	for (int i = 0; i < viruses.size() - M; i++) vec.push_back(0);
	for (int i = 0; i < M; i++) vec.push_back(1);

	// ���� ���鼭 �� ���̽��� �ùķ��̼�
	do {
		int ret = bfs();
		if (ret < ans) ans = ret; // �ּ� �ð����� ����
	} while (next_permutation(vec.begin(), vec.end()));

	// output
	if (ans == 213456789) ans = -1;
	cout << ans << "\n";

	return 0;
}