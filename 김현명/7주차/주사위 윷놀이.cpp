#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// ���� ����
// road1 ~ road4: ��ġ�� �ʴ� ���� ���
// road5: ���ΰ� ��ġ�� ���
int road1[22] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
int road2[20] = { 0,13,16,19,25};
int road3[20] = { 0,22,24,25};
int road4[20] = { 0,28,27,26,25};
int road5[20] = { 0,30,35,40 };

// ���� ���� ��ġ ������ ����Ѵ�.
// ���ΰ� ��ġ�� ���� vi5���� ����Ѵ�.
// �̹� ���� �ִ� ��츦 �����Ѵ�.
int vi1[20];
int vi2[20];
int vi3[20];
int vi4[20];
int vi5[20];

// ������ ��ġ�� ����
//road1: 20�̻�
//road2: 4�̻�
//road3: 3�̻�
//road4: 4�̻�

// �����ϴ� ���
int r1_end = 21;
int r2_end = 8;
int r3_end = 7;
int r4_end = 8;

// �� ���� ����
struct node {
    int id;
    int r_num;
    int now;
    bool end ;
};

// �� ����
node dolls[5];

int m_nums[10];
int max_score;

node dolls_path[10];

// �ֻ����� ��쿡�� ������ �����δ�.
// �ִ� ������ �����Ѵ�.
void dfs(int m_id, int score){
    // ��� �ֻ�����ŭ ��������.
    if (m_id >= 10) {
        if (score > max_score) {
            max_score = score;

        }
        return;
    }

    // 1������ 4������ �����δ�.
    // - ���� ���� r_type�� ���� ��η� �����δ�.
    // - ���� �����϶� ���� ���� ��츦 ����.
    // - ���� ���� ������ ���� ��� ���� ���� �����Ѵ�.
    for (int i = 1; i < 5; i++) {
        node doll = dolls[i];
        int to = doll.now + m_nums[m_id];
        int r_type = doll.r_num;

        // ���� �̹� ������ ���
        if (doll.end == true) continue;

        // 1�� ���ο� �ִ� ���
        if (r_type == 1) {
            if (vi1[to] == 1) continue;
            
            if (to == 5 || to == 10 || to == 15) {
                // ���� �� ��ġ�� �Ķ� ���� ��, ���� 2, 3, 4�� ���� ���
                int n_road = to / 5 + 1;

                // ���� �湮 ��ϰ� �������� �湮 ����� �����Ѵ�.
                if (n_road == 2) {
                    if (vi2[0] == 1) continue;
                    vi1[doll.now] = 0;
                    vi2[0] = 1;
                }
                else if (n_road == 3) {
                    if (vi3[0] == 1) continue;
                    vi1[doll.now] = 0;
                    vi3[0] = 1;
                }
                else if (n_road == 4) {
                    if (vi4[0] == 1) continue;
                    vi1[doll.now] = 0;
                    vi4[0] = 1;
                }

                // ���� ���� Ÿ��, ���ο����� ��ġ�� �����Ѵ�.
                dolls[i].r_num = n_road;
                dolls[i].now = 0;

                dolls_path[m_id] = doll;
                dfs(m_id + 1, score + road1[to]);
                dolls_path[m_id] = {};


                // �ռ� ������ �������� �����Ѵ�.
                dolls[i].r_num = 1; 
                dolls[i].now = doll.now;

                if (n_road == 2) {
                    vi1[doll.now] = 1;
                    vi2[0] = 0;
                }
                else if (n_road == 3) {
                    vi1[doll.now] = 1;
                    vi3[0] = 0;
                }
                else if (n_road == 4) {
                    vi1[doll.now] = 1;
                    vi4[0] = 0;
                }
                continue;
            }
            else {
                // ���� �����ϴ� ���
                if (to > 19) {
                    // ������ �� ���� road5�� vi5�� �����Ѵ�.
                    int vi_to = to - 17;
                    if (vi5[vi_to] == 1) continue;

                    vi1[doll.now] = 0;
                    dolls[i].r_num = 5;
                    dolls[i].now = vi_to;
                    vi5[vi_to] = 1;

                    dolls_path[m_id] = doll;

                    // road1�� ���� �����ϴ� ���, road5�� �߰��� �����ϴ� ���
                    if (vi_to == 0) {
                        dfs(m_id + 1, score + road1[to]);
                    }
                    else {
                        dfs(m_id + 1, score + road5[vi_to]);
                    }
                    dolls_path[m_id] = {};

                    vi5[vi_to] = 0;
                    dolls[i].now = doll.now;
                    dolls[i].r_num = 1;
                    vi1[doll.now] = 1;
                    continue;
                }

                // ���� �湮 ��ϰ� �������� �湮 ����� �����Ѵ�.
                vi1[doll.now] = 0;
                dolls[i].now = to;
                vi1[to] = 1;

                dolls_path[m_id] = doll;
                dfs(m_id + 1, score + road1[to]);
                dolls_path[m_id] = {};

                vi1[to] = 0;
                dolls[i].now = doll.now;
                vi1[doll.now] = 1;
            }
        }
        // 2�� ���ο� �ִ� ���
        else if (r_type == 2) {
            if (to > 3) {
                int vi_to = to - 4;
                if (vi5[vi_to] == 1) continue;

                vi2[doll.now] = 0;
                dolls[i].r_num = 5;
                dolls[i].now = vi_to;
                vi5[vi_to] = 1;

                dolls_path[m_id] = doll;
                if (vi_to == 0) {
                    dfs(m_id + 1, score + road2[to]);
                }
                else {
                    dfs(m_id + 1, score + road5[vi_to]);
                }
                dolls_path[m_id] = {};

                vi5[vi_to] = 0;
                dolls[i].r_num = 2;
                dolls[i].now = doll.now;
                vi2[doll.now] = 1;
                continue;
            }

            if (vi2[to] == 1) continue;

            vi2[doll.now] = 0;
            dolls[i].now = to;
            vi2[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road2[to]);
            dolls_path[m_id] = {};

            vi2[to] = 0;
            dolls[i].now = doll.now;
            vi2[doll.now] = 1;
        }

        // 3�� ���ο� �ִ� ���
        else if (r_type == 3) {
            if (to > 2) {
                int vi_to = to - 3;
                if (vi5[vi_to] == 1) continue;

                vi3[doll.now] = 0;
                dolls[i].r_num = 5;
                dolls[i].now = vi_to;
                vi5[vi_to] = 1;

                dolls_path[m_id] = doll;
                if (vi_to == 0) {
                    dfs(m_id + 1, score + road3[to]);
                }
                else {
                    dfs(m_id + 1, score + road5[vi_to]);
                }
                dolls_path[m_id] = {};

                vi5[vi_to] = 0;
                dolls[i].r_num = 3;
                dolls[i].now = doll.now;
                vi3[doll.now] = 1;
                continue;
            }

            if (vi3[to] == 1) continue;

            vi3[doll.now] = 0;
            dolls[i].now = to;
            vi3[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road3[to]);
            dolls_path[m_id] = {};

            vi3[to] = 0;
            dolls[i].now = doll.now;
            vi3[doll.now] = 1;
        }

        // 4�� ���ο� �ִ� ���
        else if (r_type == 4) {
            if (to > 3) {
                int vi_to = to - 4;
                if (vi5[vi_to] == 1) continue;

                vi4[doll.now] = 0;
                dolls[i].r_num = 5;
                dolls[i].now = vi_to;
                vi5[vi_to] = 1;

                dolls_path[m_id] = doll;
                if (vi_to == 0) {
                    dfs(m_id + 1, score + road4[to]);
                }
                else {
                    dfs(m_id + 1, score + road5[vi_to]);
                }
                dolls_path[m_id] = {};

                vi5[vi_to] = 0;
                dolls[i].r_num = 4;
                dolls[i].now = doll.now;
                vi4[doll.now] = 1;
                continue;
            }

            if (vi4[to] == 1) continue;

            vi4[doll.now] = 0;
            dolls[i].now = to;
            vi4[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road4[to]);
            dolls_path[m_id] = {};

            vi4[to] = 0;
            dolls[i].now = doll.now;
            vi4[doll.now] = 1;
        }

        // 5�� ���ο� �ִ� ���
        else if (r_type == 5) {
            if (to > 3) {
                // ���� �����ϴ� ���
                // ���� �湮 ����� �����Ѵ�.
                vi5[doll.now] = 0;
                dolls[i].end = true;
                dolls_path[m_id] = doll;
                dfs(m_id + 1, score);
                dolls_path[m_id] = {};
                dolls[i].end = false;
                vi5[doll.now] = 1;
                continue;
            }

            if (vi5[to] == 1) continue;

            vi5[doll.now] = 0;
            dolls[i].now = to;
            vi5[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road5[to]);
            dolls_path[m_id] = {};

            vi5[to] = 0;
            dolls[i].now = doll.now;
            vi5[doll.now] = 1;
        }
    }
}

int main() {
    // �ֻ��� ��� �Է� �ޱ�
    for (int i = 0; i < 10; i++) {
        cin >> m_nums[i];
    }

    // �� ���� �ʱ�ȭ
    // �� id, road Ÿ��, road�� ��ġ, ���� ����
    for (int i = 1; i < 5; i++) {
        dolls[i] = { i,1,0,false };
    }

    // ����� �� ����
    dfs(0, 0);
    
    // �ִ� ���� ���
    cout << max_score << endl;

    return 0;
}