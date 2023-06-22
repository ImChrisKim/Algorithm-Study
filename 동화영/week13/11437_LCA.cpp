/* LCA */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// �� ����� ����
struct Node {
	int parent; // �θ���
	int level; // ����� ����
};

vector<int> al[50001]; // �Է� �뵵(����� �� ����� ��������Ʈ)
Node parent[50001]; // �� ������ ����
int N; // ����� �� ����

// �Է°��� ���� Ʈ�� �����
void makeTree() {
	queue<int> q;

	// ��Ʈ�� 1�� ����̹Ƿ� 1�������� ����
	q.push(1);
	parent[1].parent = 0;
	parent[1].level = 0;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		// now�� ���� ����� ������ Ž���ϱ�
		int sz = al[now].size();
		for (int i = 0; i < sz; i++) {
			int nxt = al[now][i];

			if (nxt == 1) continue; // root���(1��)��� ����
			if (parent[nxt].parent != 0) continue; // �̹� �θ��带 ã�� ����� ����

			// nxt ����� �θ�� now�̴�
			// nxt ����� ������ �θ���(now)�� �������� 1 ũ��
			parent[nxt].parent = now;
			parent[nxt].level = parent[now].level + 1;

			q.push(nxt); // nxt ��� Ž�� ����
		}
	}
}

// num�� ��带 lev���� �ö�� �����ֱ�
int getLevel(int num, int lev) {
	int ret = num;
	int cLev = parent[num].level;

	// num�� ����� (���� ���� - ��ǥ ����)��ŭ �θ���� Ÿ�� �ö󰡱�
	for (int i = 0; i < cLev - lev; ++i) {
		ret = parent[ret].parent;
	}

	return ret;
}

// a�� b�� ����� ���� ����� ���� ���� ã��
int findCA(int a, int b) {
	int ca = a, cb = b;

	// a�� b�� ���� ����
	int la = parent[ca].level;
	int lb = parent[cb].level;

	// la�� �� ���� ������ �ִٸ�
	if (la > lb) {
		ca = getLevel(a, lb); // a��带 b�� �������� �����ֱ�
	}
	// lb�� �� ���� ������ �ִٸ�
	else if (la < lb) {
		cb = getLevel(b, la); // b��带 a�� �������� �����ֱ�
	}

	// ca �� cb�� ���� ���� ������ ��ġ�Ѵ�
	// ��ĭ�� ���� �ö󰡴ٰ� ���� ���� �߰� �� ����
	while (ca != cb) {
		ca = parent[ca].parent;
		cb = parent[cb].parent;
	}

	return ca;
}

int main() {
	// input
	cin >> N;
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		al[a].push_back(b); // ����� ����
		al[b].push_back(a);
	}

	// 1. Ʈ�� ����
	makeTree();

	// M���� ���� �Է¹ޱ�
	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;

		// 2. a�� b ����� ���� ����� ���� ���� ã�Ƽ� ���
		cout << findCA(a, b) << "\n";
	}

	return 0;
}