/* ���˹��� */
#include <iostream>
using namespace std;

int upper[500001]; // �������� ����
int lower[500001]; // ������ ����
int N, H;

int main() {
	cin >> N >> H;

	// 1. �Է°����� �������� ������ ���̸� DAT�� ī�����Ѵ�
	// �� upper[3]�� ���̰� 3�� �������� ����
	int leng;
	for (int i = 0; i < N; i++) {
		cin >> leng;
		if (i % 2 == 0) lower[leng]++;
		else upper[leng]++;
	}

	// 2. �������� ���� ������ ���� ���� ���Ѵ�
	// ��, ���̰� 3�� �������� ���̰� 1, 2�� �������� ������ ��ġ�Ƿ� �������ֱ� (���� ��������)
	for (int i = 2; i < H; i++) {
		upper[H - i] += upper[H - i + 1];
		lower[H - i] += lower[H - i + 1];
	}

	// 3. ���� �������� ������/���� ��ֹ��� ���� - �ּҰ� ���ϱ�
	// ��) ���� 5 -> 2�� ���̿��� ��ֹ��� ������ upper[2] + lower[4]
	int val = 21e8, cnt = 0;
	for (int i = 1; i <= H; i++) {
		int tmp = upper[i] + lower[H - i + 1];

		if (tmp < val) { // �� ���� ���� ���ߴٸ� val, cnt ����
			val = upper[i] + lower[H - i + 1];
			cnt = 1;
		}
		else if (tmp == val) cnt++; // ������ �ּҰ��� ������ ������ ã�Ҵٸ� cnt ī����
	}

	// output
	cout << val << " " << cnt << "\n";

	return 0;
}