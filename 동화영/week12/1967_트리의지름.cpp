/* Ʈ���� ���� */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int num; // ��� ��ȣ
	int cost; // num ����ȣ 
};

int used[10001]; // leaf ��带 ã�� ���� �迭
vector<Node> el[10001]; // �� ��庰 ��������Ʈ
vector<int> ch; // leaf ���
int n; // ����� ��

// �� leaf ��忡������ �ٸ� leef �������� �Ÿ� ���ϱ�
int bfs(int ind) {
	int st = ch[ind]; // �̹��� Ž�� ������ ��� ��ȣ

	// bfs Ž�� �غ�
	queue<int> q;
	int visited[10001] = { 0, };

	q.push(st);
	visited[st] = 1;

	// bfs Ž��
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		int sz = el[now].size();
		for (int i = 0; i < sz; i++) {
			int nxt = el[now][i].num;
			int cst = el[now][i].cost;

			if (visited[nxt] > 0) continue;
			q.push(nxt);
			visited[nxt] = visited[now] + cst; // �Ÿ����� cost ��ŭ �����ֱ�
		}
	}

	// leaf ��常 ������������ �Ǵ��Ͽ� �ִ밪 ���ϱ�
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] > ret) ret = visited[i];
	}

	// �������� 1�� �ױ� ������ -1 ���ֱ�
	return ret - 1;
}

int main() {
	// input
	int a, b, c;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b >> c;
		// ��� a�� b ������ cost�� c�� ���� (��������Ʈ)
		el[a].push_back({ b, c });
		el[b].push_back({ a, c });
		used[a] = 1; // ��� a�� �ڽ� ��尡 �ִٸ� ǥ��
	}

	// leaf ���� ���ϱ�
	for (int i = 1; i < 10001; i++) {
		if (el[i].size() > 0 && used[i] == 0) ch.push_back(i);
	}

	// leaf ������ ��ȸ�ϸ�
	// �� ��忡�� �ٸ� leaf ��������� �Ÿ� �� �ִ밪 ���ϱ�
	int maxi = 0;
	for (int i = 0; i < ch.size(); i++) {
		int cost = bfs(i);
		if (cost > maxi) maxi = cost; // �� ����
	}

	// output
	cout << maxi;

	return 0;
}