#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>

using namespace std;

string s_path = "";
int m_k, sr, sc, er, ec, n, m;
bool can_go = true;
bool pa_find = false;

int dr[4] = { 1,0,0,-1 };
int dc[4] = { 0,-1,1,0 };
char pa_c[4] = { 'd','l','r','u', };

// �� �� �ִ� ��� �� ���� ������ ���� ����� �Ѵ�.
// d -> l -> r -> u �� �̵��� ���� ã�� ��θ� ���Ѵ�.

void m_run(int r, int c, string pa, int ck) {
    if (pa_find)
    {
        return;
    }

    if (ck == m_k && r == er && c == ec)
    {
        s_path = pa;
        pa_find = true;
        return;
    }

    int nr, nc;

    // ��ǥ ���� ������ �Ÿ��� ���� �̵� ������ Ŀ���� ���
    // ����ġ�⸦ ���ش�.
    if ((abs(r - er) + abs(c - ec)) > m_k - ck)
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        nr = r + dr[i];
        nc = c + dc[i];


        // k���� �̵����� ��� ������ ���
        // ����ġ��
        if (1 > nr || n < nr || 1 > nc || m < nc) continue;
        if (ck + 1 > m_k) continue;

        m_run(nr,nc,pa + pa_c[i], ck + 1 );
    }
}

string solution(int a, int b, int x, int y, int r, int c, int k) {
    m_k = k;
    n = a;
    m = b;
    sr = x;
    sc = y;
    er = r;
    ec = c;

    // ��ǥ �������� ���� ���� ���
    // :���� - ��ǥ������ �Ÿ��� �̵����� ������ �۴�.
    if (abs(r - x) + abs(c - y) > k) {
        can_go = false;
    }

    // ���� ��ġ���� ��ǥ��ġ���� ���� ���� �̵� ���� ����ص� �� �� ���� ���
    // k��ŭ�� �̵� ���� ����ϹǷ� �̵� �� - ��ǥ������ �Ÿ��� Ȧ �� �̸� �� �� ����.
    if ((k - (abs(r - x) + abs(c - y))) % 2 != 0) {
        can_go = false;
    }

    // ������ġ���� ��ǥ��ġ���� ����ϱ�
    if (can_go)
    {
        m_run(sr, sc, "", 0);
    }

    if (can_go)
    {
        return s_path;
    }
    else {
        return "impossible";
    }
}