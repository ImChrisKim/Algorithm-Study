#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>

using namespace std;

// ü���� ���� : board
// ���� �� �̵� ����: board_id
int n, k;
int board[20][20];

vector<int> board_id[20][20];

// ������ ��ġ, ���� ����: dolls
struct node {
	int r;
	int c;
	int di;
};

node dolls[400];

// ���� ����
int dr[4] = { 0,0,-1,1 };
int dc[4] = { 1,-1,0,0 };
int c_di[4] = { 1,0,3,2 };

// ü�� ���� ����
bool is_ok = false;

// ���� �̵��ϱ�
// 1������ k������ ������ �̵���Ų��.
// ������ ������ �̵� ���� ���� ���� �ൿ�� �����Ѵ�.

void doll_go() {
	
	for (int id = 1; id < k + 1; id++) {
		// ���� �� ����
		int r, c, di;

		// ������ �� ����
		int nr, nc, n_di;

		r = dolls[id].r;
		c = dolls[id].c;
		di = dolls[id].di;

		nr = r + dr[di];
		nc = c + dc[di];
		n_di = di;

		// ��ĭ���� �̵��ϱ�
		if (board[nr][nc] == 0) {

			// �� �̵��� �ش� id������ ���� ���� ������ ���� �̵��Ѵ�.
			// ���, �̵��Ǵ� ����� �̵����� �ʴ� ������ �����Ѵ�.
			bool d_s = false;
			vector<int> ori_tmp = {};
			vector<int> n_tmp = {};

			for (int i = 0; i < board_id[r][c].size(); i++) {
				if (board_id[r][c][i] == id) d_s = true;

				if (d_s == false)
				{
					ori_tmp.push_back({ board_id[r][c][i] });
				}
				else if (d_s == true)
				{
					n_tmp.push_back({ board_id[r][c][i] });
				}
			}
			// ���� ������ ������ �̵���Ű��
			vector<int> n_ori_tmp = board_id[nr][nc];
			for (int i = 0; i < n_tmp.size(); i++) {
				n_ori_tmp.push_back(n_tmp[i]);
			}

			// �� �̵� ���� ����
			board_id[nr][nc] = n_ori_tmp;
			board_id[r][c] = ori_tmp;

			// ���� �̵��Ǵ� ������ ������ �����Ѵ�.
			for (int i = 0; i < n_tmp.size(); i++) {
				int n_id = n_tmp[i];
				dolls[n_id].r = nr;
				dolls[n_id].c = nc;
			}

			// ü�� ���� ����
			if (n_ori_tmp.size() >= 4) {
				is_ok = true;
				return;
			}
		}

		// �� �̵��� �ش� id������ ���� ���� ������ ���� �̵��Ѵ�.
		// ���������̹Ƿ� ����� �̵��Ѵ�.
		else if (board[nr][nc] == 1) {
			bool d_s = false;
			vector<int> ori_tmp = {};
			vector<int> n_tmp = {};

			for (int i = 0; i < board_id[r][c].size(); i++) {
				if (board_id[r][c][i] == id) d_s = true;

				if (d_s == false)
				{
					ori_tmp.push_back({ board_id[r][c][i] });
				}
				else if (d_s == true)
				{
					n_tmp.push_back({ board_id[r][c][i] });
				}
			}

			// ���� ������ ������ �̵���Ű��
			vector<int> n_ori_tmp = board_id[nr][nc];
			int n_size = n_tmp.size();
			for (int i = 0; i < n_size; i++) {
				n_ori_tmp.push_back(n_tmp[n_size-1-i]);
			}

			// �� �̵� ���� ����
			board_id[nr][nc] = n_ori_tmp;
			board_id[r][c] = ori_tmp;


			// ���� �̵��Ǵ� ������ ������ �����Ѵ�.
			for (int i = 0; i < n_tmp.size(); i++) {
				int n_id = n_tmp[i];
				dolls[n_id].r = nr;
				dolls[n_id].c = nc;
			}

			// ü�� ���� ����
			if (n_ori_tmp.size() >= 4) {
				is_ok = true;
				return;
			}
		}

		// �� �̵��� �ش� id������ ���� ���� ������ ���� �̵��Ѵ�.
		// �Ķ��������� ��������.
		// ���� ���������� ���ŵȴ�. �� ��, ���� ��ġ���� ���ŵ� �������� �̵��� ����Ѵ�.
		// �� ��, ���� �̵������� �������� ���� ������ش�.
		else if (board[nr][nc] == 2) {
			bool d_s = false;
			vector<int> ori_tmp = {};
			vector<int> n_tmp = {};

			for (int i = 0; i < board_id[r][c].size(); i++) {
				if (board_id[r][c][i] == id) d_s = true;

				if (d_s == false)
				{
					ori_tmp.push_back({ board_id[r][c][i] });
				}
				else if (d_s == true)
				{
					n_tmp.push_back({ board_id[r][c][i] });
				}
			}

			// ��������, ���� �̵� ��ġ ����ϱ�
			n_di = c_di[di];
			nr = r + dr[n_di];
			nc = c + dc[n_di];

			// ���� ������ ������ �̵���Ű��
			// �� �� �ش� ������ ������ ����Ѵ�.
			// �Ķ��� ���
			if (board[nr][nc] == 2) {
				nr = r;
				nc = c;
			}
			else {
				vector<int> n_ori_tmp = board_id[nr][nc];

				// ����� �������� ����ϱ�
				if (board[nr][nc] == 0) {
					for (int i = 0; i < n_tmp.size(); i++) {
						n_ori_tmp.push_back(n_tmp[i]);
					}

				}
				else if (board[nr][nc] == 1) {
					int n_size = n_tmp.size();
					for (int i = 0; i < n_size; i++) {
						n_ori_tmp.push_back(n_tmp[n_size - 1 - i]);
					}
				}
				// �� �̵� ���� ����
				board_id[nr][nc] = n_ori_tmp;
				board_id[r][c] = ori_tmp;

				// ���� �̵��Ǵ� ������ ������ �����Ѵ�.
				for (int i = 0; i < n_tmp.size(); i++) {
					int n_id = n_tmp[i];
					dolls[n_id].r = nr;
					dolls[n_id].c = nc;
				}
				// ü�� ���� ����
				if (n_ori_tmp.size() >= 4) {
					is_ok = true;
					return;
				}


			}
		}

		dolls[id].di = n_di;
	}
}

int main() {

	cin >> n >> k;

	// ü�� ��� ����
	// ��
	for (int r = 0; r < n + 2; r++) {
		board[r][0] = 2;
		board[r][n + 1] = 2;
	}

	// ��
	for (int c = 0; c < n + 2; c++) {
		board[0][c] = 2;
		board[n + 1][c] = 2;
	}

	// ü���� ���� �Է�
	for (int r = 1; r < n + 1; r++) {
		for (int c = 1; c < n + 1; c++) {
			int num;
			cin >> num;
			board[r][c] = num;
		}
	}

	// ���� ���� �Է� : dolls
	// ���� �̵� ���� �Է� : board_id
	for (int id = 1; id < k + 1; id++) {
		int r, c, di;
		cin >> r >> c >> di;

		di -= 1;

		dolls[id] = { r,c,di };
		board_id[r][c].push_back(id);
	}

	// ���� �����ϱ�
	int turn = 1;

	while (turn <= 1000) {
		// ���� �̵��ϱ�
		doll_go();

		// ���� 4ĭ �̻� ���� ���
		if (is_ok == true) break;
		turn += 1;
	}

	if (turn > 1000) cout << -1 << endl;
	else cout << turn << endl;

	return 0;
}