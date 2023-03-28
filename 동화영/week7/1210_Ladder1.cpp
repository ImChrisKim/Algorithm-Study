/* Ladder 1 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
const int SIZE_N = 100;

struct NODE {
	int y;
	int x;
};

int ydir[] = { 0, 0, -1 }; // 0�� 1�� 2��
int xdir[] = { -1, 1, 0 };

int MAP[SIZE_N][SIZE_N]; // ���Ÿ�� ������
NODE target; // ��������

// ��������(2)�� �������� ���������� ã���� ����
// 1. ���� ���� ������ ���̴� -> �¿�ĭ�� ���� ������ �� �ö󰣴�
// 2. ���� ���� ������ �¿��̴� -> �������� �� | 0�� ���� ������ �� ������ ����
int bfs() {
	int ndir = 2; // �ʱ������ ��
	NODE now = { target.y, target.x }; // ���������� �������� �Ѵ�

	// 0��° �࿡ ������ ������ Ž���Ѵ�
	while (now.y != 0) {
		if (ndir == 2) { // ��
			// ������ ����� ���� �� �ö󰡴ٰ�
			for (int i = now.y; i >= 0; i--) {
				if (i == 0) { // 0��° �࿡ �����ϸ� ��ǥ ���� �� ������
					now = { i, now.x };
					break;
				}

				if (now.x > 0 && MAP[i][now.x - 1] == 1) { // ���ʿ� ���� �ִٸ�
					// ���� ��ȯ �� ��ǥ ���� �� ������
					ndir = 0;
					now = { i, now.x - 1 };
					break;
				}
				else if (now.x < SIZE_N - 1 && MAP[i][now.x + 1] == 1) { // �����ʿ� ���� �ִٸ�
					// ���� ��ȯ �� ��ǥ ���� �� ������
					ndir = 1;
					now = { i, now.x + 1 };
					break;
				}
			}
		}
		else if (ndir == 1) { // ��
			// ������ ������ ���������� �� ���ٰ�
			for (int i = now.x; i <= SIZE_N; i++) {
				// �������� ����ų� 0�� ������
				if (i == SIZE_N || MAP[now.y][i] == 0) {
					// ������ ������ ��ȯ �� ��ǥ ����
					ndir = 2;
					// now.y - 1�� ������ �ؾ� �Դ� �� �ǵ��ư��� �ʴ´� -> now.y�� �����ϸ� �� ��� �ٽ� �ǵ��ư���.. (���� ���⵵ ����)
					now = { now.y - 1, i - 1 }; // 0�� ������ �� if�� �ȿ� �������Ƿ� i-1�� ����
					break;
				}
			}
		}
		else if (ndir == 0) { // ��
			// ������ ������ �������� �� ���ٰ�
			for (int i = now.x; i >= -1; i--) {
				// �������� ����ų� 0�� ������
				if (i == -1 || MAP[now.y][i] == 0) {
					// ������ ������ ��ȯ �� ��ǥ ����
					ndir = 2;
					now = { now.y - 1, i + 1 }; // 0�� ������ �� if�� �ȿ� �������Ƿ� i+1�� ����
					break;
				}
			}
		}

		//cout << now.y << " " << now.x << "\n";
	}

	return now.x;
}

int main() {
	//freopen("input_1210.txt", "r", stdin);

	int T = 10;
	for (int tc = 1; tc <= T; tc++) {
		// input
		int num;
		cin >> num;

		for (int i = 0; i < SIZE_N; i++) {
			for (int j = 0; j < SIZE_N; j++) {
				cin >> MAP[i][j];
				if (i == SIZE_N - 1 && MAP[i][j] == 2) {
					target = { i,j }; // ���������� ����
				}
			}
		}

		// solve & output
		cout << "#" << num << " " << bfs() << "\n";
	}

	return 0;
}