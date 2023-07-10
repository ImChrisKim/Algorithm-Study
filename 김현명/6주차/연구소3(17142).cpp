#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

// ������ ���� ����
int n, m;
int board[50][50];
int visited[50][50];

// ���� ����
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// �ּ� �ð� �����ϱ�
// �۶߸� ���� ��: b_num
// ���̷��� ��: v_num
int min_time = 21e8;
int b_num;
int v_num;

struct node {
	int r;
	int c;
};

// ���̷��� ���, ������ ��� ����
node virus[2500];
int possible[10];

// ���̷����� �۶߸���.
// �� ��, ���̷������� ���ÿ� �۶߸��� �Ѵ�.
// queue�� ��Ƽ� 1�ʸ��� ���� �۶߸��� �Ѵ�.
void extend() {

	int time = 0;
	int t_num = b_num;
	queue<node> q = {};

	// �ð� ����
	if (t_num == 0) {
		if (time < min_time) min_time = time;
		return;
	}

	// ó�� ���̷��� ����
	for (int i = 0; i < 10; i++) {
		if (possible[i] == 0) continue;
		int r, c;
		r = virus[i].r;
		c = virus[i].c;

		q.push({ r, c });
		visited[r][c] = 1;
	}

	// ���̷��� �۶߸���
	while (!q.empty()) {
		int q_size = q.size();
		time += 1;

		for (int s = 0; s < q_size; s++) {
			node now = q.front();
			q.pop();
			
			int r, c, nr, nc;
			r = now.r;
			c = now.c;

			// ���̸� ����������.
			// �۶߸� ��ҿ� �����ߴٸ� t_num �����Ѵ�.
			// ��� ��ҿ� �����ߴٸ� �ð� �����ϰ� �����Ѵ�.
			for (int i = 0; i < 4; i++) {
				nr = r + dr[i];
				nc = c + dc[i];
				
				if (0 > nr || nr >= n || 0 > nc || nc >= n) continue;
				if (board[nr][nc] == 1) continue;
				if (visited[nr][nc] != 0) continue;

				if (board[nr][nc] == 0) t_num -= 1;

				if (t_num == 0) {
					if (time < min_time) min_time = time;

					return;
				}
				
				visited[nr][nc] = visited[r][c] + 1;
				q.push({ nr,nc });
			}
		}
	}

	return;
}

void count_case(int a, int idx) {
	// ���̷��� ��� �ϼ�
	// ���̷��� �۶߸��鼭 �ð� �����ϱ�
	if (a >= m) {
		memset(visited, 0, sizeof(visited));
		extend();

		return;
	}

	// ����� �� �����
	for (int i = idx; i < v_num; i++) {
		possible[i] = 1;
		count_case(a + 1, i + 1);
		possible[i] = 0;
	}

	return;
}

int main() {

	cin >> n >> m;

	// ������ ���� �Է¹ޱ�
	// b_num ����
	// ���̷��� ��ġ �����ϱ�
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			cin >> board[r][c];

			if (board[r][c] == 0) b_num += 1;
			else if (board[r][c] == 2) {
				virus[v_num] = { r,c };
				v_num += 1;
			}

		}
	}

	// ���̷����� �۶߸� ��� ��츦 ����Ѵ�.
	count_case(0, 0);

	// �ּ� �ð� ����ϱ�
	if (min_time != 21e8) {
		cout << min_time << endl;
	}
	else if (min_time == 21e8) {
		cout << -1 << endl;
	}

	return 0;
}