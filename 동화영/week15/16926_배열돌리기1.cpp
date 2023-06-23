// 16926 �迭 ������1
#include <iostream>
using namespace std;

int MAP[300][300]; // �迭
int N, M; // �迭�� ������ N*M

// ȸ��
void Rotate() {
	int cnt = N > M ? M / 2 : N / 2; // �迭 �� ȸ���� �Ͼ�� �簢���� ����

	// �� �簢������ ȸ�� ����
	for (int i = 0; i < cnt; i++) {
		int tmp = MAP[i][i]; // �������� ���� ���� ����

		// upper side
		for (int j = i; j < M - 1 - i; j++) {
			MAP[i][j] = MAP[i][j + 1];
		}

		// right side
		for (int j = i; j < N - 1 - i; j++) {
			MAP[j][M - 1 - i] = MAP[j + 1][M - 1 - i];
		}

		// lower side
		for (int j = M - 1 - i; j > i; j--) {
			MAP[N - 1 - i][j] = MAP[N - 1 - i][j - 1];
		}

		// left side
		for (int j = N - 1 - i; j > i; j--) {
			MAP[j][i] = MAP[j - 1][i];
		}

		MAP[i + 1][i] = tmp; // �����ص� ���������� ȸ�� �Ϸ�
	}
}

int main() {
	// input
	int R;
	cin >> N >> M >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// R���� ȸ�� ����
	for (int i = 0; i < R; i++) Rotate();

	// output
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}