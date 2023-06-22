#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> al[20001]; // ��������Ʈ
int visited[20001]; // �� ����� �׷� 1:A�׷�, -1:B�׷�, 0:�̹湮
int V, E; // V: ����� ����, E: ������ ����

void init() {
	for (int i = 0; i < 20001; i++) {
		al[i].clear();
		visited[i] = 0;
	}
}

// 1. start ������ Ž�� ���� (A�׷��� �������� �α�)
// 2. now�� ���� ������ ���鸸 Ž��
int bfs(int start) {
	queue<int> q;
	q.push(start);
	visited[start] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		int flag = visited[now];

		for (int i = 0; i < al[now].size(); i++) {
			int nxt = al[now][i];

			if (visited[now] == visited[nxt]) return 0; // now�� nxt�� �����Ѵ�. �ٵ� �̹� Ȯ���� �׷쵵 �����ϴٸ� �ش� �׽�Ʈ���̽��� �̺б׷����� �ƴϴ�.
			if (visited[nxt] != 0) continue; // now�� nxt�� �̹� �ٸ� �׷����� �з��Ǿ���. �׷��Ƿ� nxt ���� Ž���� �ʿ� X

			q.push(nxt);
			visited[nxt] = flag * -1;
		}
	}

	return 1;
}

int main() {
	int tc;
	cin >> tc;

	int a, b;
	for (int t = 0; t < tc; t++) {
		// init
		init();

		// input
		cin >> V >> E;
		for (int i = 0; i < E; i++) { // ��������Ʈ�� �׷��� ����
			cin >> a >> b;
			al[a].push_back(b);
			al[b].push_back(a);
		}

		// 1. �̹湮�� ������ bfs Ž�� ����
		// 2. Ž�� ��� 0�̸� �̺б׷����� ������� ������ �߰��� ����
		// 3. ans�� ���� 0���� ������ �� Ž�� ����
		int ans = 1;
		for (int i = 1; i <= V; i++) {
			if (visited[i] == 0) {
				if (bfs(i) == 0) {
					ans = 0;
					break;
				}
			}
		}

		if (ans == 1) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}