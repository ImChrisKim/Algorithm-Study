#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>

using namespace std;

int n, k;
int f_sec;

int vi[200002][20];

struct p_no {
    int now_n;
    int jn;
};

// ������ -> �������� �ּ� �ð��� ����Ѵ�.
// �� ��, 2��� ���� ���� ��� �ð��� �ٸ� �ͺ��� ����.
// ��� �� ��츦 ���� Ž�����ش�.
// ���� �������� ��ġ�� ���� 2�� ���� �ϴ� ��찡 �޶�����.
// 2������, -1, 1�� ���� ���� Ž���Ѵ�.

void b_find()
{
    queue<p_no> q = {};
    q.push({ n,0 });
    vi[n][0] = 1;
    if (n == k)
    {
        f_sec = 0;
        return;
    }
    while (!q.empty())
    {
        p_no now_p = q.front();
        q.pop();

        if (now_p.now_n == k)
        {
            f_sec = vi[now_p.now_n][now_p.jn] - 1;
            return;
        }

        int to_n = 2 * now_p.now_n;
        if (to_n > 200000) continue;
        if (vi[to_n][now_p.jn + 1] != 0) continue;

        vi[to_n][now_p.jn + 1] = vi[now_p.now_n][now_p.jn];
        q.push({ to_n, now_p.jn + 1 });

        for (int di = -1; di < 2; di += 2)
        {
            to_n = now_p.now_n + di;
            if (to_n > 200000 || to_n < 0) continue;
            if (vi[to_n][now_p.jn] != 0) continue;

            vi[to_n][now_p.jn] = vi[now_p.now_n][now_p.jn] + 1;
            q.push({ to_n, now_p.jn });

        }
    }
}

int main() {
    // ���� ��ġ:N
    // ���� ��ġ:K
    cin >> n >> k;

    // ���� -> ���� �������� ����
    b_find();
    cout << f_sec << endl;
    return 0;
};