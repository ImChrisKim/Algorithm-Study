// 1229 ������
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 213456789;
int dp[1000000];
vector<int> nums;

// �������� �� ��� �� ����
void calcCnt(int N) {
	nums.push_back(0);
	int sum = 1, prev = 0, ind = 2;

	while (sum <= N) {
		prev = sum;
		nums.push_back(prev);
		dp[prev] = 1;

		// ��ġ�� �κ� �����ϰ� ���� �߰��Ǵ� �������� ���� ������
		// (ind - 1) * 4 + 1 ���̴�
		sum += (ind - 1) * 4 + 1;
		ind++;
	}
}

int main() {
	// input
	int N;
	cin >> N;

	// �������� �� ���
	calcCnt(N);

	int sz = nums.size();
	dp[1] = 1;
	for (int i = 2; i <= N; ++i) { // 2���� N����
		if(dp[i] == 0) dp[i] = INF;
		else continue;

		// �������� �� �������� �ʿ��� ���� + 1 ��
		// ������ ���� ���Ͽ� min������ ����
		for (int j = 1; j < sz; ++j) {
			if (nums[j] > i) break;
			dp[i] = min(dp[i - nums[j]] + 1, dp[i]);
		}
	}

	// output
	cout << dp[N] << "\n";

	return 0;
}