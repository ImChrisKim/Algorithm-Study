#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>

using namespace std;

// ���� �� ���� ����
int n;
int board[20][20];
int last_area[20][20];

// �� �α���, ���ű� �α� �ּ� ��� �� ����
int total_num = 0;
int min_gap = 21e8;

// ������ ����Ѵ�.
void count_score(int sr, int sc, int d1, int d2) {
	// sr, sc : ���ű� �� ���� / sr_down, sc_down: ���ű� �Ʒ����� 
	// ���ű� �ִ� �α� ���, �ּ� �α� ���
	int sr_down, sc_down;
	int max_a_num = -21e8;
	int min_a_num = 21e8;
	
	sr_down = sr + d1 + d2;
	sc_down = sc - d1 + d2;

	// ���ű� 1������ �α� ����ϱ�
	int rest_num = 0;
	int tmp_s = 0;
	for (int r = 0; r < sr + d1; r++) {
		for (int c = 0; c < sc + 1; c++) {
			if (last_area[r][c] == 1) break;

			tmp_s += board[r][c];
			rest_num += board[r][c];
			last_area[r][c] = 1;
		}
	}
	if (tmp_s > max_a_num) max_a_num = tmp_s;
	if (tmp_s < min_a_num) min_a_num = tmp_s;

	// ���ű� 2������ �α� ����ϱ�
	tmp_s = 0;
	for (int r = 0; r < sr + d2 + 1; r++) {
		for (int c = n - 1; c > sc; c--) {
			if (last_area[r][c] == 1) break;

			tmp_s += board[r][c];
			rest_num += board[r][c];
			last_area[r][c] = 2;
		}
	}
	if (tmp_s > max_a_num) max_a_num = tmp_s;
	if (tmp_s < min_a_num) min_a_num = tmp_s;

	// ���ű� 3������ �α� ����ϱ�
	tmp_s = 0;
	for (int r = sr + d1; r < n; r++) {
		for (int c = 0; c < sc_down; c++) {
			if (last_area[r][c] == 1) break;

			tmp_s += board[r][c];
			rest_num += board[r][c];
			last_area[r][c] = 3;
		}
	}
	if (tmp_s > max_a_num) max_a_num = tmp_s;
	if (tmp_s < min_a_num) min_a_num = tmp_s;

	// ���ű� 4������ �α� ����ϱ�
	tmp_s = 0;
	for (int r = sr + d2 + 1; r < n; r++) {
		for (int c = n - 1; c > sc_down-1; c--) {
			if (last_area[r][c] == 1) break;

			tmp_s += board[r][c];
			rest_num += board[r][c];
			last_area[r][c] = 4;
		}
	}
	if (tmp_s > max_a_num) max_a_num = tmp_s;
	if (tmp_s < min_a_num) min_a_num = tmp_s;

	// ������ ���ű� �α� �� ���ϱ�
	int last_num = total_num - rest_num;
	if (last_num > max_a_num) max_a_num = last_num;
	if (last_num < min_a_num) min_a_num = last_num;
	
	// �ּ� �α� ��츦 �����Ѵ�.
	if (max_a_num - min_a_num < min_gap) min_gap = max_a_num - min_a_num;

}

// ���ű��� ������.
// ���� �� ������� ���������� �����Ѵ�.
// ���������� d1, d2�� ��ȭ�� ���� ���ű��� ������.
void count_case() {
	// d1, d2�� 1���� �����Ѵ�.
	// �ش� ��쿡�� ���������κ��� ���ű��� �����Ѵ�.
	// ���ű��� �������� �α� ���� ����Ѵ�.

	// d1, d2�� �ּ� �Ÿ��� 1�̴�.
	// d1, d2�� �ִ� �Ÿ��� n-2�̴�.
	for (int d1 = 1; d1 < n - 1; d1++) {
		for (int d2 = 1; d2 < n - 1; d2++) {

			for (int sr = 0; sr < n; sr++) {
				for (int sc = 0; sc < n; sc++) {
					// ���ű��� ���� ���� ���� ��츦 �����Ѵ�.
					// ���� ���: ���� �������� ���������� �����ȿ� �ִ�.
					// ���� ���: ���� �������� ���������� �����ȿ� �ִ�.

					if (sr + d1 + d2 > n - 1) continue;
					if (sc < d1 || sc > n - 1 - d2) continue;

					// ���ű� ��� ���� �ʱ�ȭ�ϱ�
					memset(last_area, 0, sizeof(last_area));
					int r = sr;
					int c = sc;

					for (int di = 0; di < d1; di++) {
						r += 1;
						c -= 1;
						last_area[r][c] = 1;
					}

					for (int di = 0; di < d2; di++) {
						r += 1;
						c += 1;
						last_area[r][c] = 1;
					}

					for (int di = 0; di < d1; di++) {
						r -= 1;
						c += 1;
						last_area[r][c] = 1;
					}

					for (int di = 0; di < d2; di++) {
						r -= 1;
						c -= 1;
						last_area[r][c] = 1;
					}

					// �α� �� ����ϱ�
					count_score(sr, sc, d1, d2);

				}
			}

		}
	}
}

int main() {
	cin >> n;

	// ���ű� �α� ���� �Է� �ޱ�
	// �� �α����� �����Ѵ�.
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			cin >> board[r][c];
			total_num += board[r][c];
		}
	}

	// ���ű��� ������.
	count_case();

	// ���ű� �ּ� �α� ��� �� ����ϱ�
	cout << min_gap << endl;

	return 0;
}