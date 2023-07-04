// 2623 �������α׷�
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ��������
// DAG(Directed Acyclic Graph)�� �׷������� ���� ����

queue<int> q;
vector<int> ans; // ������ ���� (�������� ����)
vector<int> orders[1001]; // ���� (������ ������ ����)
int indegree[1001]; // �� ������ indegree (������ ȭ��ǥ�� ��)
int N, M; // N: ������ ��, M: ����PD�� ��

int main() {
	// input
	int cnt, prev, nxt;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> cnt;

		cin >> prev;
		for (int j = 1; j < cnt; j++) {
			cin >> nxt;
			orders[nxt].push_back(prev); // nxt �Ϸ� �� prev�� indegree�� ���ҽ�Ű�� ���� �������� ����
			indegree[prev]++; // prev���� ������ ȭ��ǥ�� �� ����
			prev = nxt;
		}
	}

	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) q.push(i); // indegree�� 0�� ���� queue�� �ֱ�
	}

	// N�� �ݺ��ϸ鼭 �ϳ��� ������ ans�� �ֱ�
	for (int i = 1; i <= N; i++) {
		// N�� �ݺ��Ǳ� ���� queue�� ����ٸ� ���̻� �湮 ������ ������ ����
		// ��, ����Ŭ�� ����
		if (q.empty()) break;

		int now = q.front();
		q.pop();
		ans.push_back(now);

		// now �������� ���� �湮�ؾ� �ϴ� nxt ������ indegree ���� ó��
		for (int j = 0; j < orders[now].size(); j++) {
			int nxt = orders[now][j];
			indegree[nxt]--;
			if (indegree[nxt] == 0) q.push(nxt); //indegree�� 0�� �ȴٸ� queue�� �ֱ�
		}
	}

	// ����Ŭ ���� �� 0 ��� �� ����
	if (ans.size() < N) {
		cout << 0 << "\n";
		return 0;
	}

	// output
	for (int i = 1; i <= N; i++) {
		cout << ans[N - i] << "\n";
	}

	return 0;
}