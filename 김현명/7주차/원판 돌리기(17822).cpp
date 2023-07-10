#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// ���� ����, ���� ���� �� ����
int n, m, t;
int board[50][50];
int b_nums;

// ȸ�� �� ���ǿ� ���� ���� ������ �����ϱ�
// ������ ���ڰ� �ִ� ���: board 0���� ����
// ������ ���ڰ� ���� ���: mid���� ���� board ���� ����
void board_change() {
	// ������ ���� �ִ��� Ȯ���Ѵ�.
	// ������ ����� ���� ������ c_board�� ����ϰ� �̿��Ѵ�.
	bool one_s = false;
	int c_board[50][50] = { {} };

	// �� ���� ������ �� ����ϱ�
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m - 1; c++) {
			if (board[r][c] == 0) continue;
			if (board[r][c] == board[r][c + 1]) {
				one_s = true;
				c_board[r][c] = 1;
				c_board[r][c + 1] = 1;
			}
		}

		if (board[r][m - 1] == board[r][0]) {
			if (board[r][m-1] == 0) continue;
			one_s = true;
			c_board[r][m - 1] = 1;
			c_board[r][0] = 1;
		}

	}

	// �� ���� ������ �� ����ϱ�
	for (int c = 0; c < m; c++) {
		for (int r = 0; r < n - 1; r++) {
			if (board[r][c] == 0) continue;
			if (board[r][c] == board[r + 1][c]) {
				one_s = true;
				c_board[r][c] = 1;
				c_board[r + 1][c] = 1;
			}
		}
	}

	// ������ ���� �ִ� ���
	if (one_s == true) {
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < m; c++) {
				if (c_board[r][c] == 0) continue;
				board[r][c] = 0;
			}
		}
	}
	// ������ ���� ���� ���
	else if (one_s == false) {
		// ���ǿ� ���� ������ ����� ���ϱ�
		float mid = 0;
		int cnt = 0;

		for (int r = 0; r < n; r++) {
			for (int c = 0; c < m; c++) {
				if (board[r][c] == 0) continue;

				mid += board[r][c];
				cnt += 1;
			}
		}

		mid = (float)mid/cnt;

		// ��� ���� ���� ���� ���� �����ϱ�
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < m; c++) {
				if (board[r][c] == 0) continue;
				if (board[r][c] > mid) {
					board[r][c] -= 1;
				}
				else if (board[r][c] < mid) {
					board[r][c] += 1;
				}
			}
		}
	}
};

// ���� ȸ��
// �ݽð� ������ ��� ��ü ���� ũ�� - k �� ȸ���Ѵ�. --> �ð� ���� ȸ��
// �ð������ ��� k�� ȸ���Ѵ�.
void cycle(int r, int d, int k) {
	if (d == 1) {
		k = m - k;
	}

	for (int i = 0; i < k; i++) {
		int tmp = board[r][m - 1];
		for (int c = m - 1; c > 0; c--) {
			board[r][c] = board[r][c - 1];
		}
		board[r][0] = tmp;
	}
};

int main() {

	cin >> n >> m >> t;

	// ���� ���� �Է�
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			cin >> board[r][c];
		}
	}

	// ȸ�� ���� �Է�
	for (int c = 0; c < t; c++) {
		// x��� ��ŭ, d����, k�� ȸ���Ѵ�.
		int x, d, k;
		cin >> x >> d >> k;
		
		// x�� ��� ��ŭ ȸ���ϱ�
		for (int i = x; i < n + 1; i += x) {
			cycle(i - 1, d, k);
		}

		// ���� ���� �����ϱ�
		board_change();
	}

	// ���� ���� �� ���ϱ�
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			b_nums += board[r][c];
		}
	}

	cout << b_nums << endl;

	return 0;
};
