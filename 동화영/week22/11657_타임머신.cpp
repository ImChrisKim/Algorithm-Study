// 11657 Ÿ�Ӹӽ�
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const long long INF = 1e10; // INF ���� �������� ũ�� ��ƾ���,,

queue<pair<int, int>> q; // { ����, ��� }
vector<pair<int, int>> al[501]; // { ��������, ��� }
long long visited[501]; // �ʱ⿡ INF���� ���Ƿ� long long���� ���
int N, M; // N: ������ ��, M: ���� �뼱�� ��

int main() {
	int s, e, p; // ���� �뼱�� ���� (s:������, e:������, p:�ҿ�ð�)

	// input
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> s >> e >> p;
		al[s].push_back({ e, p }); // s���� ����Ͽ� e�� �����ϴµ� p�ð� �ҿ�
	}

	// init - �� ������ �����ϴµ� �ҿ�Ǵ� �ð��� �ִ밪���� �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		visited[i] = INF;
	}

	// ������ N���� �׷������� 1������ �ٸ� �������� �����Ϸ���
	// �־��� ��� (N-1)���� ������ �����ľ� �Ѵ�
	// �׷��� N-1���� Ž���Ѵ�
	// �������������� �����ϵ�
	// �� �ϸ��� queue�� ���ִ� ���鿡������ ������ �̵��ϰ�
	// �� �� �ּ� ��θ� ã�´ٸ� �����Ѵ�
	// ���⼭ ������ �������� ���Ե� ����Ŭ�̴�.
	// Ư��, ����Ŭ�� �� ������ ��ΰ� �� �۾����ٸ� ���Ѵ�� �۾��� ���� �ִ�.
	// �̷��� ��� ������ ���� ������ �ǵ��ư��� ������ ��츦 ������ �Ѵ�.
	// �� ����� isCycled ������ ���� ����Ŭ�� ���� �Ǻ����ֱ�
	// ������ (N-1)�� ���� ������ N�� �����Ѵ�.
	// N�� �������� �� �ּ��� ��θ� ã�Ҵٸ� �װ��� ������ ���� ������ ���ư��� ���̽��̴�.
	// ���� �̷� ��� ������ true�� �������ָ� �ȴ�.

	bool isCycled = false; // ������ �۾����� ����Ŭ�� ���� ����
	visited[1] = 0; // 1�� �������� ����
	q.push({ 1, 0 });
	for (int i = 1; i <= N; i++) {
		// i��° �Ͽ����� ���� ���� queue�� �ִ� ��� ������������ ������ �̵��Ѵ�.
		int sz = q.size();
		for (int j = 0; j < sz; j++) {
			pair<int, int> curr = q.front();
			q.pop();

			int tsz = al[curr.first].size(); // curr.first�� ����� ���� Ž��
			for (int k = 0; k < tsz; k++) {
				pair<int, int> nxt = al[curr.first][k];
				
				if (visited[nxt.first] <= visited[curr.first] + nxt.second) continue; // �̹� �� ���� ��θ� �����ϰ� �ִٸ� ����
				if (i == N) isCycled = true; // N��° �����ε� �� ���� ��θ� �߰��ߴٸ� ������ �۾����� ���̽��̹Ƿ� ���� ����

				visited[nxt.first] = visited[curr.first] + nxt.second; // ������ Ž�� ����
				q.push({ nxt.first, visited[nxt.first] });
			}
		}
	}

	if (isCycled) { // ������ �۾����� ����Ŭ�� �����Ѵٸ� -1 ���
		cout << -1 << "\n";
	}
	else {
		for (int i = 2; i <= N; i++) {
			if (visited[i] == INF) cout << "-1\n"; // i�� ������ �� ���� �������� ���ߴٸ� -1 ���
			else cout << visited[i] << "\n";
		}
	}

	return 0;
}