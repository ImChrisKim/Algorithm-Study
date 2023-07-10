#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n;

// ����� ����, ��� ���� ����
struct node {
	int f_id;
	int r;
	int c;
	int dir;
	bool live;
};

struct s_node {
	int r;
	int c;
	int dir;
};

// �ٴ����� ����
int sea[20][20];
node fishes[20];
s_node shark;

// �� ��� �� >> 8���� ����
int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,-1,-1,-1,0,1,1,1 };

int max_f_num;

void go_fish() {
	for (int i = 1; i < n * n + 1; i++) {

		int r, c, dir;
		int nr, nc, n_dir;
		node now = fishes[i];

		r = now.r;
		c = now.c;
		dir = now.dir;

		if (now.live == false) continue;

		for (int s = 0; s < 8; s++) {
			int n_dir = (dir + s) % 8;
			nr = r + dr[n_dir];
			nc = c + dc[n_dir];

			if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
			if (sea[nr][nc] == 20) continue;
			
			node next = fishes[sea[nr][nc]];
			int now_id = now.f_id;
			int next_id = next.f_id;

			if (sea[nr][nc] > 0) {
				sea[nr][nc] = now_id;
				sea[r][c] = next_id;

				fishes[next_id].r = now.r;
				fishes[next_id].c = now.c;
				fishes[now_id].r = nr;
				fishes[now_id].c = nc;
			}
			else {
				fishes[now_id].r = nr;
				fishes[now_id].c = nc;
				sea[nr][nc] = now_id;
				sea[r][c] = 0;
			}

			fishes[now_id].dir = n_dir;
			break;
		}


	}


};

// ����Ⱑ �����̰� �� �����δ�.
// �� ��, ���ϴ� �ٴ��� ������ ������� �������� �����Ѵ�.
// ���� �б������� ���ٿ��� �� ��, ���� �������� �����Ѵ�.
void go_shark(int f_num) {
	// ����� �����̱�
	go_fish();

	// ���� ���� ���
	int ori_sea[20][20] = { {} };
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			ori_sea[r][c] = sea[r][c];
		}
	}

	node ori_fishes[20] = {};
	for (int i = 0; i < 20; i++) {
		ori_fishes[i] = fishes[i];
	}

	int sr, sc, dir;
	int s_id;

	// ���� ��� ����
	sr = shark.r;
	sc = shark.c;
	dir = shark.dir;
	
	// ����� �� ����
	if (f_num > max_f_num) {
		max_f_num = f_num;
	}

	int nr, nc;

	// ��� �̵�
	// �Ÿ�1, �Ÿ�2, �Ÿ�3�� �°� �̵��Ѵ�.
	// ����Ⱑ �ִ°����� �̵� �����ϴ�.
	for (int s = 1; s < n; s++) {
		nr = sr + dr[dir] * s;
		nc = sc + dc[dir] * s;

		if (0 > nr || n <= nr || 0 > nc || n <= nc) break;
		if (sea[nr][nc] == 0) continue;

		// ��� �̵�
		// �ٴ� ���� �����ϱ�
		// ���� ����� ����ϱ�
		
		int n_id = sea[nr][nc];
		shark.r = nr;
		shark.c = nc;
		shark.dir = fishes[n_id].dir;

		sea[sr][sc] = 0;
		sea[nr][nc] = 20;

		fishes[n_id].live = false;

		go_shark(f_num + n_id);


		// �б����� ���ƿ��� ���
		// ���� �����, �ٴ� ����, ��� ������ �����Ѵ�.

		fishes[n_id].live = true;
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				sea[r][c] = ori_sea[r][c];
			}
		}

		for (int i = 0; i < 20; i++) {
			fishes[i] = ori_fishes[i];
		}

		shark.dir = dir;
		shark.c = sc;
		shark.r = sr;

	}
};


int main() {
	// �ٴ� ũ��, ����� ���� ��
	n = 4;
	int f_num = 0;

	// ���� �ٴ����� �Է¹ޱ�
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			int id, dir;
			cin >> id;
			cin >> dir;
			dir -= 1;

			// ��� ���� ����, �ʿ� ǥ���ϱ�
			if (r == 0 && c == 0) {
				shark = { 0,0, dir };
				f_num += id;
				sea[r][c] = 20;
				continue;
			}

			// ����� ���� ����, �ʿ� ǥ���ϱ�
			fishes[id] = { id,r,c,dir,true };
			sea[r][c] = id;
		}
	}

	// ��� ���
	go_shark(f_num);

	cout << max_f_num << endl;

	return 0;
}