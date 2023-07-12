// 2637 �峭�� ����
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<pair<int, int>> al[101]; // �� ��ǰ�� ����� ���� { ���, ���� }
int indegree[101]; // �� ��ǰ�� ����µ� �ʿ��� ����� ��
int ans[101]; // �� ��ǰ�� �ʿ��� ����

int main() {
	// input
	int N, M;
	int X, Y, K;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> X >> Y >> K;
		al[X].push_back({ Y, K }); // X�� ����µ� Y�� K�� �ʿ��ϴ�
		indegree[Y]++; // (������) ��ᰡ ���̴� ���� ������ ����
	}

	queue<pair<int, int>> q;
	q.push({ N, 1 }); // N�� ����ǰ�� 1�� ����°� ��ǥ�� ����
	ans[N] = 1;

	// N���� ����ǰ/��ǰ�� ��� ����� �ᱹ N������ �ϳ��� ���� Ȯ���ϱ�
	for (int i = 1; i <= N; i++) {
		pair<int, int> now = q.front();
		q.pop();

		int sz = al[now.first].size();
		for (int j = 0; j < sz; j++) {
			pair<int, int> nxt = al[now.first][j];
			
			indegree[nxt.first]--; // nxt.first�� �ʿ�� �ϴ� ��ǰ �ϳ� ����
			int nxtCnt = now.second * nxt.second; // now ��ǰ�� ����� ���� �ʿ��� nxt ��ǰ�� ����
			ans[nxt.first] += nxtCnt;
			if (indegree[nxt.first] == 0) // nxt.first�� ��ǰ�� �ʿ��� ��ǰ�� ��� �Ϸ��ߴٸ�
				q.push({ nxt.first, ans[nxt.first] }); // queue�� �־ ���� Ž�� ����
		}
	}

	// output
	for (int i = 1; i <= N; i++) {
		// i�� ��ǰ�� ����� ���� �ʿ��� ��ǰ�� 0���� ���
		// �� �⺻ ��ǰ�� ��쿡�� { ��ȣ, ���� }�� ���
		if (al[i].size() == 0) cout << i << " " << ans[i] << "\n";
	}

	return 0;
}