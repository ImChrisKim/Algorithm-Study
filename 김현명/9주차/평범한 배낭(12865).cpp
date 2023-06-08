#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int n, k;

// ��ǰ ���� ����
struct thing {
	int w;
	int val;
};

// ��ǰ��, dp�� �����Ѵ�.
// ��ǰ: ����, ��ġ
// dp: �� ��ǰ���� ���� �� �ִ� ���Դ� �ִ� ��ġ�� ����Ѵ�.
thing things[102];
int dp[102][100010];
int path[102];

// Top-down ���
// ������ ��ǰ���� Ž���ߴ�.
// now_w: ���� �� �ִ� ���� ����
// now: ���� ��ǰ ��ȣ �Ǵ� ���� ����
int dfs(int now, int now_w) {
	// ��� ��ǰ�� �� ���
	if (now < 1) {

		return 0;
	}

	// �ش� ��ǰ�� ���Ը� ���� ���� ���
	if (now_w < things[now].w) {
		return dfs(now - 1, now_w);
	}

	// �̹� �ִ밡ġ�� ��ϵ� ���
	if (dp[now][now_w] != 0) {
		return dp[now][now_w];
	}

	// ��ǰ�� ��� ���� ���� �ʴ� ���� ����Ѵ�.
	int max_val = 0;
	int case_val1 = dfs(now - 1, now_w - things[now].w) + things[now].val;
	int case_val2 = dfs(now - 1, now_w);

	max_val = max(case_val1, case_val2);

	// �ش� ��ǰ�� ���԰�쿡�� �ִ밡ġ�� ����Ѵ�.
	return dp[now][now_w] = max_val;
};

int main() {
	cin >> n >> k;

	// dp �ʱ�ȭ�ϱ�
	for (int r = 0; r < n + 1; r++)
	{
		for (int c = 0; c < 100010; c++)
		{
			dp[r][c] = 0;
		}
	}

	// ��ǰ���� ������ �Է¹ޱ�
	// weight: ���� / value: ��ġ
	for (int ti = 1; ti < n + 1; ti++)
	{
		int weight, value;
		cin >> weight;
		cin >> value;
		things[ti].w = weight;
		things[ti].val = value;
	}

	// �ִ� ��ġ�� ���Ѵ�.
	int total_max_val = 0;

	total_max_val = dfs(n, k);

	cout << total_max_val << endl;

	return 0;
}