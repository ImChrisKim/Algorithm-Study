#include <iostream>
#include <vector>
using namespace std;

struct ROBOT {
	int y;
	int x;
	int d;
};

int dy[4] = { -1, 0, 1, 0 }; // �ϼ����� (�ݽð�)
int dx[4] = { 0, -1, 0, 1 };

vector<ROBOT> robots; // N���� �κ� ����
int MAP[102][102]; // ���� ���� ����
int A, B; // ���� ������ A*B
int N, M; // N: �κ��� ��, M: ����� ��

// 'L', 'R'�� ��� ���� - ȸ��
void turnRobot(int rob, char dir, int cnt) {
	ROBOT curr = robots[rob];
	int cDir = curr.d;
	if (dir == 'L') { // �������� 90�� ȸ��(�ݽð�)
		curr.d = (cDir + (cnt % 4)) % 4;
	}
	else { // ���������� 90�� ȸ��(�ð�)
		curr.d = ((cDir - (cnt % 4)) + 4) % 4;
	}
	robots[rob].d = curr.d; // ȸ�� �� �ٶ󺸴� �������� �κ� ���� ����
}

// 'F'�� ��� ���� - ������ ����
int forwardRobot(int rob, int cnt) {
	ROBOT curr = robots[rob];
	int ny = curr.y;
	int nx = curr.x;
	for (int i = 1; i <= cnt; i++) { // cnt ĭ��ŭ �����Ѵ�
		ny += dy[curr.d];
		nx += dx[curr.d];

		// �� ĭ�� �����ϴ� ���� ���̳� �ٸ� �κ��� ���� ��� ��ȯ
		if (ny > 100 || nx > B || ny <= 100 - A || nx <= 0) return -1;
		if (MAP[ny][nx] != 0) return MAP[ny][nx];
	}

	// cntĭ ���� ���� �浹 �̹߻��Ѵٸ� ��, �κ� ���� ����
	MAP[ny][nx] = rob;
	MAP[curr.y][curr.x] = 0;
	robots[rob].y = ny;
	robots[rob].x = nx;

	return 0;
}

int main() {
	// input
	int x, y, d;
	char dir;

	int crashed = 0; // ��� ���� �浹 �߻� ����

	robots.push_back({ 0,0,0 });
	cin >> B >> A >> N >> M;

	for (int i = 1; i <= N; i++) {
		cin >> x >> y >> dir;
		MAP[100 - y + 1][x] = i; // ���� ���� ���� (�� �ε��� ����)
		d = dir == 'N' ? 0 : dir == 'W' ? 1 : dir == 'S' ? 2 : 3; // �ϼ����� ����
		robots.push_back({ 100 - y + 1, x, d }); // �κ��� ���� ����
	}

	for (int i = 0; i < M; i++) {
		cin >> x >> dir >> y;
		if (dir == 'F') { // ���� ���
			int robNum = forwardRobot(x, y);
			// -1 ��ȯ: �� �浹
			// �ڿ��� ��ȯ: �κ� �浹
			// 0: �浹 �߻� X
			if (robNum > 0) cout << "Robot " << x << " crashes into robot " << robNum << "\n";
			else if (robNum == -1) cout << "Robot " << x << " crashes into the wall\n";

			if (robNum != 0) { // �浹 �߻��ߴٸ� ���̻� ��� ���� X
				crashed = 1;
				break;
			}
		}
		else { // ȸ�� ���
			turnRobot(x, dir, y);
		}
	}

	// �浹 �̹߻� �� output
	if (crashed == 0) cout << "OK\n";

	return 0;
}