// 14938 �����׶���
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 213456789;

vector<pair<int, int>> al[101]; // ���� ���� ��������Ʈ
int items[101]; // �� ������ �ִ� �������� ��
int n, m, r; // n: ������ ��, m: ���� ������ �Ÿ�, r: ������ ��, 

// spot �������� �����Ͽ� ���� �� �ִ� �������� �� ���ϱ�
int playGround(int spot) {
	int sum = 0; // ���� �� �ִ� �������� ��
	int visited[101]; // �� ���������� �Ÿ�
	for (int i = 1; i <= n; i++) visited[i] = INF;

	queue<int> q;
	q.push(spot); // spot���� ����
	visited[spot] = 0;
	sum += items[spot];
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		// now ������ ����� �������� Ž��
		for (int i = 0; i < al[now].size(); i++) {
			int nxt = al[now][i].first;
			int dist = visited[now] + al[now][i].second;

			if (dist > m) continue; // m���� �� �Ÿ��� ���� �Ұ�
			if (dist >= visited[nxt]) continue; // �̹� ������ �Ÿ��� ã�Ҵٸ� ����

			if (visited[nxt] == INF) sum += items[nxt]; // ���� ���� �� �������� �� �߰�
			q.push(nxt); // nxt ���� Ž�� ����
			visited[nxt] = dist;
		}
	}

	return sum; // spot �������� �����Ͽ� ���� �� �ִ� �������� ���� ��ȯ
}

int main() {
	// input
	int a, b, c;

	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) cin >> items[i];
	for (int i = 0; i < r; i++) {
		cin >> a >> b >> c;
		al[a].push_back({ b, c });
		al[b].push_back({ a, c });
	}

	// solve
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int ret = playGround(i); // �� �������� ���ӽ����� �ùķ��̼� ����
		if (ret > ans) ans = ret; // �ִ밪 ����
	}

	// output
	cout << ans << "\n";

	return 0;
}