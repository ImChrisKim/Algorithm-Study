#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
int board[102][102];
int b_air[102][102];

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };
int vi[102][102];

int t_time;

struct node {
    int r;
    int c;
};

// ���ⱸ��:ġ� �ѷ����� ����� �̷���� ����

// ġ�� �׷���� ���ɴ�.
// ���ÿ� ġ���̸鼭 ���� �湮 ������ ���ⱸ���� �ƴ� ������ ����Ѵ�.
void m_chesse(int sr, int sc)
{

    queue<node> q = {};
    q.push({ sr,sc });

    vi[sr][sc] = 1;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        int nr, nc;
        for (int i = 0; i < 4; i++)
        {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            if (0 > nr || n - 1 < nr || 0 > nc || m - 1 < nc) continue;
            if (vi[nr][nc] != 0) continue;

            // ġ���̸鼭 ���� �湮 ������ ���ⱸ���� �ƴ� �����̴�.
            if (board[nr][nc] == 0 && b_air[nr][nc] == 0) {
                vi[now.r][now.c] = 2;
            }
            if (board[nr][nc] == 0) continue;

            vi[nr][nc] = 1;
            q.push({ nr,nc });

        }
    }

}

// ��� ġ�� ����� ����Ѵ�.
void f_chesse()
{
    memset(vi, 0, sizeof(vi));
    for (int r = 1; r < n - 1; r++)
    {
        for (int c = 1; c < m - 1; c++)
        {
            if (vi[r][c] != 0) continue;
            if (board[r][c] == 0) continue;
            m_chesse(r, c);
        }
    }
    return;
};

// ���� ���� ����ϱ�
// �����ڸ��� �� �� �ִٸ� ���� ������ �ƴϴ�.
// ���� �����̶�� b_air�� ����Ѵ�.
void a_record(int sr, int sc)
{
    queue<node> q = {};
    q.push({ sr,sc });

    queue<node> tmp = {};
    tmp.push({ sr,sc });

    vi[sr][sc] = 1;
    bool is_air = true;

    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        int nr, nc;
        for (int i = 0; i < 4; i++)
        {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            // �����ڸ��� �� �� �ִٸ� ���� ������ �ƴϴ�.
            if (0 == nr || n <= nr - 1 || 0 == nc || m == nc - 1)
            {
                is_air = false;
            }
            if (0 > nr || n - 1 < nr || 0 > nc || m - 1 < nc) continue;
            if (board[nr][nc] == 1) continue;
            if (vi[nr][nc] != 0) continue;

            vi[nr][nc] = 1;
            tmp.push({ nr,nc });
            q.push({ nr,nc });

        }
    }

    // ���ⱸ���̶�� b_air�� ����ϱ�
    if (is_air == true)
    {
        while (!tmp.empty())
        {
            node now = tmp.front();
            tmp.pop();
            b_air[now.r][now.c] = 1;
        }
    }
    return;
}

// ġ��� �׿��� ���� ���� ã��
// ġ� �ƴ� ������ �������� ã�´�.
void a_find()
{
    memset(vi, 0, sizeof(vi));
    memset(b_air, 0, sizeof(b_air));
    for (int r = 1; r < n-1; r++)
    {
        for (int c = 1; c < m-1; c++)
        {
            if (vi[r][c] != 0) continue;
            if (board[r][c] == 1) continue;
            a_record(r,c);
        }
    }
    return;
}
int main() {
    cin >> n >> m;

    // ġ�� ���� �Է¹ޱ�
    // �����ڸ��� ġ� �� �� ����.
    // ġ���� ���� ����
    int t_chesse = 0;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < m; c++)
        {
            cin >> board[r][c];
            if (board[r][c] == 1)
            {
                t_chesse += 1;
            }
        }
    }

    // ���� �� ġ�� ���� ���
    int now_chesse = 0;
    while (t_chesse > 0)
    {
        // ġ��� �׿��� ���� ã��
        a_find();
        now_chesse = t_chesse;

        // �쿩���ϴ� ġ�� ���� ã��
        // vi�� 2�� ����Ѵ�.
        f_chesse();

        // ������ ã�� ġ� ���̰� ��ü ġ�� ������ �����Ѵ�.
        for (int r = 1; r < n - 1; r++)
        {
            for (int c = 1; c < m - 1; c++)
            {
                if (vi[r][c] == 2)
                {
                    board[r][c] = 0;
                    t_chesse -= 1;
                }
            }
        }
        t_time += 1;
    }

    // ��ü �ð�, ��� ��� �� ġ�� ���� ���
    cout << t_time << endl;
    cout << now_chesse << endl;
    return 0;
}