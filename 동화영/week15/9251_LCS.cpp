// 9251 LCS
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Longest Common Subsequence ���� ���� �κ� ����
// �־��� �� ���� ��ο� ���ԵǴ� �κ� ���� �� ���� �� ���� ã��
// ���ӵǴ� ���ڿ��� �ƴϴ�

int dp[1010][1010];

int main() {
	// input
	string a, b;
	int n, m;

	cin >> a >> b;
	n = a.size();
	m = b.size();

	// a[i] == b[j] �� ���, dp[i-1][j-1] ���� 1 ����
	// a[i] != b[j] �� ���, dp[i][j-1] �� dp[i-1][j] �� �� ū ���� ����
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	// output
	cout << dp[n][m] << "\n";

	return 0;
}