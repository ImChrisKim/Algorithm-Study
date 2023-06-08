#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <math.h>
#include <iostream>

using namespace std;

int n, q;

// ���� ���� ����
int ice[102][102];
int new_ice[102][102];
int visited[102][102];

// ����
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

// ���� ���� ��
// �ִ� ���� ��� ũ��
// ���� ��� ũ��
int i_num;
int max_g_num ;
int g_num;

// ���� ��� Ž���ϱ�
// ��� ũ�⵵ ����.
void g_view(int r, int c)
{
    int nr, nc;

    for (int di = 0; di < 4; di++)
    {
        nr = r + dr[di];
        nc = c + dc[di];

        if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
        if (ice[nr][nc] == 0) continue;
        if (visited[nr][nc] != 0) continue;

        visited[nr][nc] = 1;
        g_num += 1;
        g_view(nr, nc);
    }
};

// ���� ���̱�
// ���ǿ� �����ؼ� 1�� ���̱�
void storm()
{
    memset(new_ice, 0, sizeof(new_ice));
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (ice[r][c] == 0) continue;

            int i_num = 0;
            int nr, nc;
            bool melt = true;

            for (int di = 0; di < 4; di++)
            {
                nr = r + dr[di];
                nc = c + dc[di];

                if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
                if (ice[nr][nc] == 0) continue;

                i_num += 1;
            }

            if(i_num < 3)
            {
                new_ice[r][c] = ice[r][c] - 1;
            }
            else {
                new_ice[r][c] = ice[r][c];
            }
        }
    }
    memcpy(ice, new_ice, sizeof(new_ice));
};

// Ư������ ȸ���ϱ�
// new_ice �ڷḦ Ȱ���Ѵ�.
void i_cycle(int sr, int sc, int m)
{
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < m; c++)
        {
            new_ice[sr+r][sc+c] = ice[sr+m-1-c][sc + r];
        }
    }


    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < m; c++)
        {
            ice[sr + r][sc + c] = new_ice[sr + r][sc + c];
        }
    }


};

// �κ�ȭ�� ������ ������ 90�� ȸ���Ѵ�.
// m ũ��� ���� �ε����� Ȱ���Ѵ�.
void fire(int m)
{
    memset(new_ice, 0, sizeof(new_ice));
    for (int sr = 0; sr < n; sr+=m)
    {
        for (int sc = 0; sc < n; sc+=m)
        {
            i_cycle(sr, sc, m);
        }
    }

};

int main() {
    cin >> n >> q;

    // ������ ���߱�
    n = pow(2, n);

    // ���� ���� �Է� �ޱ�
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            cin >> ice[r][c];
        }
    }

    // ���� �����ϱ�
    // fire: ���� ȸ��
    // storm: ���� ���̱�
    for (int qi = 0; qi < q; qi++)
    {
        int m;
        cin >> m;

        fire(pow(2,m));
        storm();
    }

    // ���� ���� ���� ����
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (ice[r][c] == 0) continue;
            i_num += ice[r][c];
        }
    }

    // ���� ������� ���� ����
    // ������ �ִ� �������� g_view�� �Ѵ�.
    // g_view�� �ش� �������� ������ ��ŭ ������ ���� ��� ũ�⸦ �����Ѵ�.
    // �湮����� ���ܼ� Ž���� �ߺ������� ����Ѵ�.
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (ice[r][c] == 0) continue;
            if (visited[r][c] != 0) continue;

            g_num = 1;
            visited[r][c] = 1;
            g_view(r,c);

            // �ִ� ���� ��� �� ����
            if (g_num > max_g_num) {
                max_g_num = g_num;
            }
        }
    }
    
    cout << i_num << endl;
    cout << max_g_num << endl;

    return 0;
};