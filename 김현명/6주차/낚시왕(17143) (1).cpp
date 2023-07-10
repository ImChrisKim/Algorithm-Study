#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// �ٴ� ���� ����
// ��� id�� �����Ѵ�.
int n, m, k;
int sea[100][100];

// ���� ����
// ���ӷ�, ����, ũ�Ⱑ �ִ�.
// ��� id�� ����Ǵ� �ڷᱸ��
struct node {
	int s_vel;
	int s_dir;
	int s_size;
};

node sharks[100001];

// ��� ����
// �� �Ʒ� ������ ����
// ���� �ε����� ��� �ݴ�������� �̵�
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };
int c_dir[4] = { 1,0,3,2 };

// ���� ��� ��
int get_s_size;

// ��� �̵��ϱ�
// new_sea������ ����� �̵� ����� ��´�.
// �̵� �� sea������ �����Ѵ�.
void move_shark() {
	int new_sea[100][100] = { {} };

	// �� �ִ� ���
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			if (sea[r][c] > 0) {
				int move;

				int dir;
				int nr = r;
				int nc = c;

				// ���� ������, �̵� ���� ����
				dir = sharks[sea[r][c]].s_dir;
				move = sharks[sea[r][c]].s_vel;

				// ��� �� �������� �̵�
				// �� ���� �������� ���� ��츦 �������� �̵� �Ÿ��� �����Ѵ�.
				// ����� �ִ� �̵��Ÿ��� ���� �ε����� ó�� ��ġ�� ���� ����̴�.
				// �� �Ÿ��� �̵� �� �ε��� ��� ��ġ�� ������ ���� �Ѵ�.
				if (dir == 0 || dir == 1) {
					move %= 2 * (n - 1);

					for (int i = 0; i < move; i++) {
						nr += dr[dir];

						if (nr > n - 1)
						{
							nr = n - 2;
							dir = c_dir[dir];
						}
						else if (nr < 0)
						{
							nr = 1;
							dir = c_dir[dir];
						}
					}
				}
				// ��� �� �������� �̵�
				// �� ���� �������� ���� ��츦 �������� �̵� �Ÿ��� �����Ѵ�.
				// ����� �ִ� �̵��Ÿ��� ���� �ε����� ó�� ��ġ�� ���� ����̴�.
				// �� �Ÿ��� �̵� �� �ε��� ��� ��ġ�� ������ ���� �Ѵ�.
				else if (dir == 2 || dir == 3) {
					move %= 2 * (m - 1);

					for (int i = 0; i < move; i++) {
						nc += dc[dir];

						if (nc > m - 1)
						{
							nc = m - 2;
							dir = c_dir[dir];
						}
						else if (nc < 0)
						{
							nc = 1;
							dir = c_dir[dir];
						}
					}
				}

				// ���� ����
				sharks[sea[r][c]].s_dir = dir;

				// �� �������� ���� ���
				// ���� ū �� ���´�.
				if (new_sea[nr][nc] > 0) {
					int ori_size = sharks[new_sea[nr][nc]].s_size;
					int now_size = sharks[sea[r][c]].s_size;

					if (now_size > ori_size) {
						new_sea[nr][nc] = sea[r][c];
					}
				}
				else {
					new_sea[nr][nc] = sea[r][c];
				}
			}
		}
	}

	// ���� �ٴ� ���� ����
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			sea[r][c] = new_sea[r][c];
		}
	}

}

// ���� �� ��� �ϱ�
// �� ��� ��� ���� �����ϰ� ������.
void get_shark(int sc) {
	int nc;
	nc = sc;

	for (int nr = 0; nr < n; nr++) {
		if (sea[nr][nc] > 0) {
			int s_id = sea[nr][nc];
			get_s_size += sharks[s_id].s_size;

			sea[nr][nc] = 0;
			return;
		}
	}
}

int main() {
	cin >> n >> m >> k;

	// ��� ������ �Է¹޴´�.
	// id�� �����Ѵ�.
	int s_id = 1;
	for (int i = 0; i < k; i++) {
		// ��ġ, �ӷ�, ����, ũ��
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;

		// ���� ���� ���߱�
		r -= 1;
		c -= 1;
		d -= 1;

		// id�� �����Ѵ�
		// id�� �°� ��� ���� �Է��ϱ�
		sea[r][c] = s_id;
		sharks[s_id] = { s,d,z};
		s_id += 1;
	}

	// ���� ��ĭ�� �̵��Ѵ�.
	// ������ ���� ����� �� ��´�.
	// ���� �̵��� �� ��� �̵��ϱ�
	for (int sc = 0; sc < m; sc++) {
		get_shark(sc);
		move_shark();
	}

	cout << get_s_size << endl;

	return 0;
}