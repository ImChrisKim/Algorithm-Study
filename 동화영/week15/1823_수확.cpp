// 1823 ��Ȯ
#include <iostream>
#include <algorithm>
using namespace std;

// DP ���� - ������ �ٸ� ����� Ǯ�̸� ���Ҵ�..
// 

int dp[2001][2001]; // [left, right] ���� ������ �� �� �ִ� �ִ� ����
int values[2001]; // �� ĭ�� ���� ��ġ
int N; // ���� ������

int agriculture(int st, int en, int point) {
	if (st > en) return 0; // �ε��� ���� �ʰ��� 0 ��ȯ

	if (dp[st][en] > 0) return dp[st][en]; // �̹� ���� ���� �ִٸ� �ش� �� ��ȯ

	// ���� ���� ���ٸ� ���ؿ���
	// [st, en] ���� ������ ���� (left�� ������ ���)�� (right�� ������ ���) �� ū �� ��������
	return dp[st][en] = max(agriculture(st + 1, en, point + 1) + values[st] * point,
							agriculture(st, en - 1, point + 1) + values[en] * point);
}

int main() {
	// input
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> values[i];

	// solve & output
	cout << agriculture(1, N, 1);

	return 0;
}