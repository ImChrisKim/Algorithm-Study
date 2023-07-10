#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// ���� ����ġ ����
// dp �����: �� ������ ��κ� �ּ� ���
int n;
int city[18][18];
int dp[18][(1<<18)];

// ������ ���� ��ȯ ��θ� ����Ѵ�.
// �� ��, ���� ���������� ���� ��θ� ����.
// ���� ��δ� �� ���� ������ ������ ��� ��θ� �ǹ��Ѵ�.
int dfs(int now, int vi)
{
    // �ش� ���ÿ����� ��δ� vi�� ����Ѵ�.
    // ��� ������ ������ ���
    if (vi == ((1<<n)-1)){
        // ��ȯ�� �������� ���� ���
        if (city[now][0] == 0) {
            return 10e8;
        }
        // ��ȯ�� ������ ���
        else {
            return city[now][0];
        }
    }

    // �̹� �ּҰ��� ���ŵ� ����
    if (dp[now][vi] != -1)
    {
        return dp[now][vi];
    }

    // ���
    dp[now][vi] = 10e8;

    // ���� �������� ������ ��θ� ����.
    // �� �� ���� ����� ���� �̹� �ش� ������ �湮�� ���� �� �ʿ䰡 ����.
    for (int i = 0; i < n; i++)
    {
        if (city[now][i] == 0) continue;
        if ((vi & (1 << i)) == (1 << i)) continue;
        dp[now][vi] = min(dp[now][vi], dfs(i, vi | (1 << i)) + city[now][i]);
    }

    // �ּ� ���
    return dp[now][vi];
}
int main() {
    cin >> n;

    // ���ú� ����ġ �Է¹ޱ�
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            int w;
            cin >> w;
            city[r][c] = w;
        }
    }

    // dp ���� �ʱ�ȭ �ϱ�
    memset(dp, -1, sizeof(dp));

    // ���� �ּ� ��ȯ��� ���ϱ�
    cout << dfs(0,1) << endl;

    return 0;
}