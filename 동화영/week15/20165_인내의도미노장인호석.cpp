#include <iostream>
using namespace std;

// ���� �迭
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int MAP[102][102]; // ���� �� ���̳��� ���� ����
char visited[102][102]; // ���� �� ���̳밡 �Ѿ������� ���� ����
int  N, M; // N*M ������ ������

// 1. ����
int Attack() {
	// �� ������ ���� ����
	int x, y;
	char d;
	cin >> x >> y >> d;

	int cnt = 0; // �� ���忡 ���ݼ��� �����߸� ���̳��� ���� - ��ȯ��

	int dir = d == 'E' ? 0 : d == 'W' ? 1 : d == 'S' ? 2 : 3; // �� ������ ���� ����
	int len = MAP[x][y]; // ������ �����߸� �� �ִ� ���̳��� ���� ����
	while (len > 0) {
		if (x <= 0 || y <= 0 || x > N || y > M) break; // ���� �ۿ� �����ߴٸ� ���̻� ���� X

		// ������ ������ ���̳밡 ���ִ� ���¶��
		// 1) �̹� ������ �������� ȹ��
		// 2) �ش� ������ ���̳� �Ѿ��� ���·� ����
		// 3) ���� �������� ���� ĭ�� ���̳� ���̰� �� ���ٸ� ����
		if (visited[x][y] == 'S') {
			cnt++;
			visited[x][y] = 'F';
			if (MAP[x][y] > len) len = MAP[x][y];
		}

		// ���� ĭ���� ���� �� �Ѿ�߸� �� �ִ� ���� ���� ����
		x += dx[dir];
		y += dy[dir];
		len--;
	}

	return cnt;
}

// 2. ����
void Defence() {
	int x, y;
	cin >> x >> y;

	visited[x][y] = 'S'; // �Է¹޴� (x,y) ������ ���̳� ����� - flag ����
}

int main() {
	// init
	int R;

	cin >> N >> M >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
			visited[i][j] = 'S'; // �ʱ⿡�� ��ü ���̳밡 �Ͼ�ִ�
		}
	}

	// R���� ����
	int ans = 0; // ���ݼ��� �����߸� ���̳��� ����
	for (int i = 0; i < R; i++) {
		ans += Attack();
		Defence();
	}

	// output
	cout << ans << "\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << visited[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}