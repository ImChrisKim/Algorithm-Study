#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

// ���� ���� ����
int n;
char board[300][300];
int visited[300][300];

int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,1,1,1,0,-1,-1,-1 };

int click_num;

struct node {
	int r;
	int c;
};

// Ŭ���ؼ� 8������ �������� �˻��Ѵ�.
// ���� �ش� ���⿡ ���ڰ� ���� ��� �� �� �ʿ䰡 ����.
void click(int r, int c) {
	visited[r][c] = 1;
	queue<node> q;
	q.push({ r,c });

	while (!q.empty()) {
		int q_size = q.size();

		for (int s = 0; s < q_size; s++) {
			node now = q.front();
			q.pop();

			int r, c, nr, nc;
			bool is_trap = false;

			r = now.r;
			c = now.c;

			for (int i = 0; i < 8; i++) {
				nr = r + dr[i];
				nc = c + dc[i];

				if (0 > nr || nr >= n || 0 > nc || nc >= n) continue;
				if (visited[nr][nc] != 0) continue;
				if (board[nr][nc] == '*') {
					is_trap = true;
					break;
				}
			}

			if (is_trap == false) {
				for (int i = 0; i < 8; i++) {
					nr = r + dr[i];
					nc = c + dc[i];

					if (0 > nr || nr >= n || 0 > nc || nc >= n) continue;
					if (visited[nr][nc] != 0) continue;
					visited[nr][nc] = 1;
					q.push({ nr,nc });
				}
			}
		}
	}
}

int main() {
	int t = 0;
	cin >> t;

	for (int tc = 0; tc < t; tc++) {
		cin >> n;

		// ���� ���� �Է� �ޱ�
		memset(visited, 0, sizeof(visited));
		click_num = 0;

		for (int r = 0; r < n; r++) {
			string tmp;
			cin >> tmp;

			for (int c = 0; c < n; c++) {
				board[r][c] = tmp[c];
			}
		}

		// ���� �������� 8���⿡ ���ڰ� ���� ��� ã��
		// ���� ��� flood fill�� ���� �湮 ����� �����.
		// �̹� �湮�߰ų� ������ ���� �� �ʿ䰡 ����.
		int nr, nc;

		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				bool is_trap = false;
				if (visited[r][c] != 0) continue;
				if (board[r][c] == '*') continue;

				// �� �� �ִ� ���⿡ ���ڰ� �ִ����� ����
				for (int i = 0; i < 8; i++) {
					nr = r + dr[i];
					nc = c + dc[i];

					if (0 > nr || nr >= n || 0 > nc || nc >= n) continue;
					if (board[nr][nc] == '*') {
						is_trap = true;
					}
				}
				// ���ڰ� ���ٸ� Ŭ���Ѵ�.
				if (is_trap == false) {
					click_num += 1;
					click(r, c);
				}
			}
		}


		// ���ڶ� ������ ���
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				if (board[r][c] == '.' && visited[r][c] == 0) {
					click_num += 1;
				}
			}
		}

		cout << "#" << tc + 1 << " " << click_num << endl;
	}
	return 0;
}