/* ������ 3 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_N 50
#define DIR_NUM 4

struct Node {
	int y;
	int x;
};

vector<Node> virus; // ���̷����� ��ġ ����
vector<int> target; // ���� M���� ���̷���

int ydir[DIR_NUM] = { -1, 1, 0, 0 }; // �����¿�
int xdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // �������� ��
int N, M; // N: �������� ������, M: ������ ���̷����� ��

int aCnt; // ���� ������ ������ ��
int ans; // �ּ� �ð�

// M���� ���̷����� ������ �� ���Դ�
// ���� �����µ� �ɸ��� �ð��� ����Ѵ�
int bfs() {
	int ret = 0; // �ɸ� �ð�

	int cnt = 0; // ������ ĭ�� �� (�� ĭ�� aCnt�� �����ؾ� �� ������ �����ٰ� �Ǵ�)
	int visited[MAX_N][MAX_N] = { 0, }; // �� ĭ�� �����µ� �ɸ� �ð��� ����
	queue<Node> q;

	// �ݹ��� Ȱ��ȭ�� ���̷����鿡�� ���� ó��
	for (int i = 0; i < virus.size(); i++) {
		if (target[i] == 1) {
			Node t = virus[i];
			visited[t.y][t.x] = 1;
			q.push({ t.y, t.x });
			cnt++;
		}
	}

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) { // ������ 4�������� ������
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // ���� ���� ����
			if (MAP[ny][nx] == -1) continue; // ���� ���ԺҰ�

			if (visited[ny][nx] > 0) continue; // �̹� �湮�� ĭ�� ����

			// ���� ����� �湮�ص� �Ǵ� ĭ�̴�
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
			cnt++;

			// �ش� ĭ�� ���̷����� �ƴ϶�� �ɸ� ���� �ð��� ����
			// �ش� ĭ�� ���̷������ ������ �ʿ� X
			if(MAP[ny][nx] != 2) ret = visited[ny][nx];
		}
	}

	if (cnt < aCnt) return -1; // ��� ĭ�� �������� ���� ��� -1 ����
	
	if (ret == 0) return 0; // ��� ĭ�� ������ �Ǳ� ������, �ҿ�ð��� 0�� ��� - ��Ȱ��ȭ ���̷����� �� ��

	return ret - 1; // ���� ������ 1�� ���������Ƿ� -1 ���ֱ�
}

int main() {
	// input
	cin >> N >> M;

	aCnt = N * N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 1) { // ��
				MAP[i][j] = -1;
				aCnt--;
			}
			else if (MAP[i][j] == 2) { // ���̷���
				virus.push_back({ i,j });
			}
		}
	}

	// ���� ������ ���� vector
	// 1: Ȱ��ȭ, 0: ��Ȱ��ȭ
	for (int i = 0; i < virus.size() - M; i++) target.push_back(0);
	for (int i = 0; i < M; i++) target.push_back(1);

	ans = 21e8;
	
	do {
		int sec = bfs(); // �̹��� ���̷����� �����µ� �ɸ� �ð�

		// �� ������ ���̷����� ���� ���̽� �߿� �ּ� �ð��� ����
		if (sec != -1 && sec < ans) ans = sec;
	} while (next_permutation(target.begin(), target.end())); // Ȱ��ȭ��ų ���̷��� M���� �����Ѵ�

	// �� �ѹ��� ������ �ȵƴٸ� ���̷��� �۶߸��� ���� -> -1 ���
	if (ans == 21e8) ans = -1;
	cout << ans;

	return 0;
}}