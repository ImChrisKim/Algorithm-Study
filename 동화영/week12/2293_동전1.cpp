/* ���� 1 */
#include <iostream>
#include <algorithm>
using namespace std;

int dp[10001]; // �� �ݾ��� ���� �� �ִ� ����� ��
int coins[100]; // �־����� n���� ���� �ݾ�
int n, k; // n: ���� ���� k: ��ǥ�ݾ�

int main() {
	// input
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> coins[i];
	}
	
	// dp[nxt] = dp[nxt] + dp[nxt - coins[i]]
	// nxt�� ����� = ������ nxt�� ���� �� + ������ (nxt-coins[i])�� ���� ��
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		int coin = coins[i];
		for (int j = coin; j <= k; j++) {
			if (dp[j - coin] > 0) {
				dp[j] += dp[j - coin];
			}
		}
	}

	cout << dp[k];

	return 0;
}