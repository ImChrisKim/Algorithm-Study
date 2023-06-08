#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n;
char opers[12][12];
int nums[22];
int ans_num[12];

// ��Ͱ� ����Ǹ鼭 �ش� ��찡 ���������� ����.
// �ܰ谡 ���� ���� ���� ���ǵ� �����Ѵ�.
// �ش� ������ ���� opers�� ���ǰ� �´����� ����.
bool isPossible(int now)
{
	if (now == 0) return true;
	int t_sum = 0;

	for (int sr = now - 1; sr > -1; sr--)
	{
		t_sum = 0;

		for (int i = 0; i < (now-1-(sr))+1; i++) {
			t_sum += ans_num[now - 1 - i];
		}

		if (t_sum > 0 && opers[sr][now - 1] != '+') return false;
		if (t_sum < 0 && opers[sr][now - 1] != '-') return false;
		if (t_sum == 0 && opers[sr][now - 1] != '0') return false;
	}

	return true;
}

// ������ ��츦 Ž���Ѵ�.
// ���� ������ �Ǵ� ��ΰ� ������ �ش� ��츦 ����Ѵ�.
// true�� ��ȯ�ϰ� �����Ѵ�.
bool dfs(int now)
{
	if (!isPossible(now)) return false;

	if (now == n)
	{
		for (int i = 0; i < n; i++)
		{
			cout << ans_num[i] << " ";
		}
		return true;
	}

	for (int i = 0; i < 21; i++)
	{
		ans_num[now] = nums[i];
		if (dfs(now + 1)) return true;
	}

	return false;
}
 
int main() {
	// ������ ������ ���� �����Ѵ�.
	int num = -10;

	for (int i = 0; i < 21; i++)
	{
		nums[i] = num;
		num += 1;
	}

	// ������ ���� �������� �Է¹ޱ�
	// n���� ���� -> n*(n+1)/2 ���� ����
	cin >> n;
	for (int r = 0; r < n; r++)
	{
		for (int c = r; c < n; c++)
		{
			cin >> opers[r][c];
		}
	}

	// ans_num�� ù��° ��쿡������ ������ ������ ����.
	// ���ڴ� -10���� 10������ �� �� �ְ� �� ��쿡�� ���������� ����.
	// �� ��, �ܰ谡 ����� ���� ������ ��쵵 ���� �����Ѵ�.
	// ���������� �� �� �ִ� ���ɼ��� �پ��� ���� ��θ� ã�Ҵٸ�
	// ��Ʈ��ŷ �б����� ���������ν� ȿ���� ���δ�.
	dfs(0);

	return 0;
}