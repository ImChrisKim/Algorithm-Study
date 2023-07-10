#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// ��ǥ �˰�°� �ڵ��� ����
// ��� dp ����
int t_alg;
int t_co;
int n;
int dp[152][152];

// ������
vector<vector<int>> pros;

// ������ ��� Ž���ϱ�
int dfs(int alg, int co, int lvl)
{
    // ��ǥ �ɷ�ġ�� ���� ���
    // �� ���ʿ䰡 ����.
    if (alg >= t_alg && co >= t_co)
    {
        return 0;
    }

    // �ִ� �˰�°� �ڵ��¿� �����ϴ� ���
    // �� �̻� ������ �˰��, �ڵ����� ����� �ʿ䰡 ����.
    // �ٸ�, �ִ�ġ�� ������ ���� ������ ��찡 �ʹ� ��������. (�˰�°� �ڵ����� ���� 45000���� Ŀ�� �� �ִ�.)
    if (alg > t_alg) {
        alg = t_alg;
    }
    if (co > t_co) {
        co = t_co;
    }

    // �̹� ��ϵ� ���
    if (dp[alg][co] != 0) {
        return dp[alg][co];
    }

    dp[alg][co] = 21e8;

    // �ش� ������ Ǫ�� ���
    for (int i = 0; i < n; i++)
    {
        if (alg < pros[i][0] || co < pros[i][1]) continue;
        dp[alg][co] = min(dp[alg][co], dfs(alg + pros[i][2], co + pros[i][3], lvl + 1) + pros[i][4]);
    }

    // �˰�°� �ڵ��� ���� ������ Ǯ ���
    dp[alg][co] = min(dp[alg][co], dfs(alg + 1, co, lvl + 1) + 1);
    dp[alg][co] = min(dp[alg][co], dfs(alg, co + 1, lvl + 1) + 1);

    return dp[alg][co];
}

bool b_cmp(vector<int> a, vector<int> b) {
    if (a[1] > b[1])
    {
        return true;
    }
    return false;
}

bool a_cmp(vector<int> a, vector<int> b) {
    if (a[0] > b[0])
    {
        return true;
    }
    return false;
}

// �ʱ� �˰��, �ڵ���, �������� �־�����.
int solution(int alg, int co, vector<vector<int>> problems) {

    // ���� ������ ����ϱ�
    pros = problems;

    // ��ǥ �˰�°� �ڵ����� ����Ѵ�.
    vector<vector<int>> s_cop_pro = problems;
    vector<vector<int>> s_alg_pro = problems;
    sort(s_cop_pro.begin(), s_cop_pro.end(), b_cmp);
    sort(s_alg_pro.begin(), s_alg_pro.end(), a_cmp);

    t_alg = s_alg_pro[0][0];
    t_co = s_cop_pro[0][1];

    n = problems.size();

    // ��� �����dp �ʱ�ȭ
    for (int r = 0; r < 152; r++)
    {
        for (int c = 0; c < 152; c++)
        {
            dp[r][c] = 0;
        }
    }

    // ��� �ڵ��׽�Ʈ ������ ��츦 ����Ѵ�.
    // �� �� �˰��(alg), �ڵ���(co)�� �������� ����Ѵ�.
    // �ش� ��쿡���� �ð��� ����� ������ ���Ѵ�.
    int ans_time = dfs(alg, co, 0);

    return ans_time;
}