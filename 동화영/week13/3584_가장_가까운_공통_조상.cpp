/* ���� ����� ���� ���� */
// LCA ����
// �������� Ǯ�̴�
// 1. ta�� tb�� ������ ���� �����
// 2. �ϳ��� ���� �ö���鼭 ���� ������ ã�´�.
#include <iostream>
#include <cstring>
using namespace std;

int visited[10001];
int parent[10001];
int N;

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// init
		memset(visited, 0, sizeof(visited));
		memset(parent, 0, sizeof(parent));
		int ans = 0;

		// input
		cin >> N;
		int p, c;
		for (int i = 0; i < N - 1; i++) { // �� ����� �θ� ��� �����ϱ�
			cin >> p >> c;
			parent[c] = p;
		}

		int ta, tb; // ta�� tb�� ���� ����� ���� ���� ã�°� �����̴�
		cin >> ta >> tb;

		// root�� parent�� 0�̴�
		int ca = ta, cb = tb; // ca, cb : ta�� tb ���� ���� �ö󰡱�
		while (visited[ca] == 0 && visited[cb] == 0) { // �� ��� ��� �̹湮�ߴٸ� ���� ���� Ž��
			if (ca == cb) break; // ���ÿ� ������ ��忡 �����ߴٸ� Ž�� ����

			// ca�� cb �湮 ǥ��
			if(ca != 0) visited[ca] = 1;
			if(cb != 0) visited[cb] = 1;

			// �� ����� �θ���� �ö󰡱�
			ca = parent[ca];
			cb = parent[cb];
		}
		
		// �� ���ϱ�
		if (ca == cb) ans = ca; // ������ ��忡�� ������ ���
		else if (ca != 0 && visited[ca] != 0) ans = ca; // ta�� ans�� �� ����� ���
		else if (cb != 0 && visited[cb] != 0) ans = cb; // tb�� ans�� �� ����� ���

		// output
		cout << ans << "\n";
	}

	return 0;
}