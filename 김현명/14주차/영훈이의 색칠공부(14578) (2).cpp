#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#define MOD 1000000007

using namespace std;

typedef long long ll;

// ���� ���Ǹ鼭 int���� �ʰ��� �� �ִ�.
// ��� long long�� ����Ѵ�.
ll fac[100002];
ll dp[100002];

// ������ ����� �������� ��� : n*(n-1)*(n-2)*...
// �� ����� �����ǰ� �ٸ� ����� ��츦 �����ؾ� �Ѵ�.
// �� �� ���� ������ ���ȴ�. ������: (n-1)*(dp[n-2] + dp[n-1])
// �� ��ȭ��: n!*((n-1)*(dp[n-2] + dp[n-1])))

int main() {
    ll n, f_n;

    cin >> n;
    f_n = 1;

    // ���丮�� ���� �����Ѵ�.
    for (ll i = 1; i < n + 1; i++)
    {
        f_n = (f_n*i)%MOD;
        fac[i] = f_n;
    }

    // �������� �����Ѵ�.
    dp[0] = 1, dp[1] = 0;
    for (ll i = 2; i < n + 1; i++)
    {
        dp[i] = (i-1)*(dp[i - 1] + dp[i - 2])%MOD;
    }

    // ���� ����� ���� ���Ѵ�.
    cout << (fac[n]*dp[n])%MOD << endl;
    return 0;
}