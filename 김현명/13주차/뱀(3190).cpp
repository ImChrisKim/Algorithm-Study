#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>

using namespace std;

int n;
int k;
int a_n;
int forest[102][102];

int hr, hc;
int tr, tc;
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

struct s_info {
    int t;
    char c_di;
};

struct s_p {
    int r;
    int c;
};

s_info coms[102];
queue<s_p> snake;

int main() {
    // �ð�, ó�� ����
    int s_t = 0;
    int s_di = 1;

    // �ʱ� �� �Ӹ�, ���� ��ġ
    hr = 1;
    hc = 1;
    tr = 1;
    tc = 1;

    cin >> n;

    // ���� �����ڸ� ������ ������ �����Ѵ�.
    for (int r = 0; r < n + 2; r++)
    {
        forest[r][0] = -1;
        forest[r][n + 1] = -1;
    }

    for (int c = 0; c < n + 2; c++)
    {
        forest[0][c] = -1;
        forest[n + 1][c] = -1;
    }

    // ����� �Է¹޴´�.
    // ��� : 2
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int r, c;
        cin >> r >> c;

        forest[r][c] = 2;
    }
    
    // ��� ����(L: ���� ȸ��, D:���� ȸ��) �Է� �ޱ�
    cin >> a_n;
    for (int i = 0; i < a_n; i++)
    {
        int c;
        char com;
        cin >> c >> com;
        coms[i] = { c,com };
    }

    // ���� ��ġ ������ queue�� �����Ѵ�.
    // ���̰� �پ���� �ʴ� ��� ���� �κи� �������ָ� �ȴ�.
    // FIRST IN FIRST OUT
    forest[hr][hc] = 1;
    snake.push({ hr,hc });

    // ���� �Ӹ� ��ġ ����
    // ��ɾ� ID
    int n_hr, n_hc;
    int c_id = 0;

    // �ð��� �帥��.
    while (true)
    {
        n_hr = hr + dr[s_di];
        n_hc = hc + dc[s_di];
        
        bool a_eat = false;

        // �����ڸ��� ���ų� ���� ��ġ�� �� ���
        if (forest[n_hr][n_hc] == -1 || forest[n_hr][n_hc] == 1) {
            s_t += 1;
            break;
        }
        
        // ����� ���� ���
        if (forest[n_hr][n_hc] == 2)
        {
            a_eat = true;
        }

        // ���� ������ ���ư���.
        forest[n_hr][n_hc] = 1;
        snake.push({ n_hr,n_hc });

        // ����� ���� ���� ���
        // ���� �̵��Ѵ�.
        // ���̰� �پ���� �ʴ´�.
        if (a_eat == false)
        {
            s_p now = snake.front();
            snake.pop();

            tr = now.r;
            tc = now.c;
            forest[tr][tc] = 0;
        }

        // ��� ���� �ð��� �ٴٸ� ���
        // L:��ȸ��, D:��ȸ��
        s_t += 1;
        if (coms[c_id].t == s_t)
        {
            if (coms[c_id].c_di == 'L')
            {
                s_di -= 1;
                if (s_di < 0)
                {
                    s_di = 3;
                }
            }
            else {
                s_di = (s_di + 1) % 4;
            }
            c_id += 1;
        }

        // ���� ��ġ ���� �����ϱ�
        hr = n_hr;
        hc = n_hc;
    }
    
    cout << s_t << endl;
    return 0;
}