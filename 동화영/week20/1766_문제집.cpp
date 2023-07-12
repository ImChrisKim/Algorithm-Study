// 1766 ������
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> al[32001]; // �� �������� ������ �ܹ��� ������ ���� ����
int indegree[32001]; // �� ������ ������ ������ ��
int N; // ������ ��

int main() {
	// input
	int A, B;
	int M;
	cin >> N >> M;


	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		al[A].push_back(B); // A->B
		indegree[B]++; // B�� ������ ������ ���� ����
	}

	priority_queue<int, vector<int>, greater<int>> pq; // ������ȣ(=���̵�) ���� ��������
	for (int i = 1; i <= N; i++) {
		// ������ ������ ���� ������ȣ�� ���� Ž��
		if (indegree[i] == 0) pq.push(i);
	}

	// 1�� ����. N���� ������ ��� Ǯ��� �Ѵ�.
	for (int i = 1; i <= N; i++) {
		// ���� �켱������ ������ ���� Ǭ��
		int now = pq.top();
		pq.pop();

		cout << now << " "; // �ٷ� output

		// now�� ������ Ǯ������ now���� ������ ������ ���������� indegree ����
		for (int j = 0; j < al[now].size(); j++) {
			int nxt = al[now][j];

			indegree[nxt]--;
			if (indegree[nxt] == 0) pq.push(nxt); // ������ ������ 0���� �Ǿ��ٸ� Ž�� ���
		}
	}

	return 0;
}