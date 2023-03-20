/* ���ÿ� */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MAX_RC 101
#define DIR_NUM 4

// ����� ����
struct shark {
	int r; // ��ġ
	int c;
	int s; // �ӷ�
	int d; // ����
	int z; // ũ��
};

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // �����Ͽ�
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

queue<shark> sharks; // ����ִ� ������ ����

int MAP[MAX_RC][MAX_RC]; // ������ - ����� ũ�⸸ ����
int R, C; // R*C �������� ũ��
int ans; // ���ÿ��� ���� ������ ũ���� ��

// king������ �����ϱ�
int grab(int king) {
	int ret = -1;

	for (int i = 1; i <= R; i++) {
		// king������ ���� ���� ����� �� ã�Ҵٸ� �ش� ���� ind ��ȯ
		if (MAP[i][king] > 0) {
			ret = i;
			ans += MAP[i][king]; // ���� ����� ũ�� ���ϱ�
			break;
		}
	}

	return ret;
}

// ���� �̵�
// (tr, tc)�� ��ġ�� ���� ��� �������Ƿ� ����
void move(int tr, int tc) {
	int TMP[MAX_RC][MAX_RC] = { 0, }; // �̹� ���� �̵������ ���

	int sz = sharks.size();

	for (int i = 0; i < sz; i++) {
		shark now = sharks.front();
		sharks.pop();
		
		// ��� ���� ���� ���̻��� �̵� X
		if (now.r == tr && now.c == tc) continue;

		// ������ �̵� �� �� ū ������� ��Ƹ��� ��� ���� �̵� X
		if (MAP[now.r][now.c] > now.z) continue;

		// ����ִ� ���� �̵� O
		int nr = now.r + rdir[now.d] * now.s;
		int nc = now.c + cdir[now.d] * now.s;

		if (now.d % 2 == 0) { // ����
			// ���� ���� �� ������ �ε��� ���
			while (!(nr > 0 && nr <= R)) {
				if (nr <= 0) nr = 2 - nr;
				else if (nr > R) nr = R - (nr - R);

				now.d = (now.d + 2) % DIR_NUM; // �� �ȿ� ���Դٴ� ���� ���ڸ� ����� -> ���� ��ȯ
			}
		}
		else { // �¿�
			// ���� ���� �� ������ �ε��� ���
			while (!(nc > 0 && nc <= C)) {
				if (nc <= 0) nc = 2 - nc;
				else if (nc > C) nc = C - (nc - C);

				now.d = (now.d + 2) % DIR_NUM; // �� �ȿ� ���Դٴ� ���� ���ڸ� ����� -> ���� ��ȯ
			}
		}

		// �ε��� ����ϱ� �Ⱦ �Ʒ�ó�� ����� �̵��� �����Ͽ����� �ð��ʰ� �߻�,,
		/*int nr = now.r;
		int nc = now.c;
		for (int j = 0; j < now.s; j++) {
			nr += rdir[now.d];
			nc += cdir[now.d];

			if (nr <= 0 || nc <= 0 || nr > R || nc > C) {
				nr -= rdir[now.d];
				nc -= cdir[now.d];

				now.d = (now.d + 2) % DIR_NUM;

				nr += rdir[now.d];
				nc += cdir[now.d];
			}
		}*/

		// �� ĭ Ȥ�� �� ���� �� �ִ� ĭ���� ����
		if (TMP[nr][nc] < now.z) {
			TMP[nr][nc] = now.z;
			sharks.push({ nr, nc, now.s, now.d, now.z });
		}
	}

	// �̹� ���� �̵������ MAP�� ����
	memcpy(MAP, TMP, sizeof(TMP));
}

int main() {
	int M; // �ʱ� ����� ��
	cin >> R >> C >> M;

	for (int i = 0; i < M; i++) {
		int ir, ic, is, id, iz;
		cin >> ir >> ic >> is >> id >> iz;

		id = id == 1 ? 0 : id == 4 ? 1 : id; // �����Ͽ� ������ ����
		sharks.push({ ir, ic, is, id, iz });
		MAP[ir][ic] = iz;
	}

	int king = 0;

	while (king <= C && sharks.size() > 0) {
		int ind = grab(++king); // (ind, king)�� �� ������
		move(ind, king); // ���� �̵��ϱ�
	}

	// output
	cout << ans << '\n';

	return 0;
}