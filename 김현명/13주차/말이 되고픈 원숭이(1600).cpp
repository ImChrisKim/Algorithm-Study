#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int k;
int w, h;
int forest[202][202];
int vi[202][202][32] = {};

int dr[12] = { -2,-1,1,2,2,1,-1,-2 ,-1,0,1,0};
int dc[12] = { 1,2,2,1,-1,-2,-2,-1,0,1,0,-1 };

bool possible = false;
int min_a = 21e8;

struct node {
    int r;
    int c;
    int pk;
};

// �����̴� �� ������ ���� �̵��� �� �� �ִ�.
// bfs Ư�� �� �ּ� ��� ������ ã�� �� �ִ�.
// �ٸ�, �� ������ ��� ��� �������� �ϴ� ���� �������� �˱� �����.
// ���, �湮��Ͽ��� �� ������ ��츦 �߰��Ѵ�.
// Ư�� ��ġ���� �� ������ ����ߴ����� ����ϱ� ������ �������� ���������� ���� ������ ����� �� �ִ�.
void bfs(int r, int c)
{
    vi[r][c][0] = 1;
    queue<node> q = {};
    q.push({ r,c,0 });

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        int r, c;
        r = now.r;
        c = now.c;

        if (r == h - 1 && c == w - 1)
        {
            min_a = vi[now.r][now.c][now.pk] - 1;
            possible = true;
            return;
        }
        int nr, nc, npk;
        for (int i = 0; i < 12; i++)
        {
            nr = r + dr[i];
            nc = c + dc[i];

            // �� ������ �ϴ� ���
            if (0 <= i && i < 8)
            {
                if (0 > nr || h - 1 < nr || 0 > nc || w - 1 < nc) continue;
                if (forest[nr][nc] == 1) continue;
                if (now.pk >= k) continue;
                if (vi[nr][nc][now.pk+1] != 0) continue;

                vi[nr][nc][now.pk + 1] = vi[r][c][now.pk] + 1;
                q.push({ nr,nc, now.pk + 1 });
            }
            // �׳� ������ �ϴ� ���
            else {
                if (0 > nr || h - 1 < nr || 0 > nc || w - 1 < nc) continue;
                if (forest[nr][nc] == 1) continue;
                if (vi[nr][nc][now.pk] != 0) continue;

                vi[nr][nc][now.pk] = vi[r][c][now.pk] + 1;
                q.push({ nr,nc, now.pk});
            }
        }
    }
}

int main() {
    // �� ���� ���� Ƚ��: k
    // ���� ����, ����: h, w
    cin >> k;
    cin >> w >> h;

    // ���� ���� �Է� �ޱ�
    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
        {
            cin >> forest[r][c];
        }
    }

    // �����̰� ����Ѵ�.
    // ���� ���� h-1, w-1������ �ּ� ��θ� ���Ѵ�.
    bfs(0, 0);

    // ������ �� ���ٸ� -1, 
    // �����ϸ� �ּ� ��� ���
    if (possible == false)
    {
        cout << -1 << endl;
    }
    else {

        cout << min_a << endl;
    }
    return 0;
}