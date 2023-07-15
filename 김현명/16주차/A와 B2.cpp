#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

string s_word;
string t_word;

int s_n;
int t_n;

bool can_con;

// t���ڿ��� �����ؼ� �Ѵܰ辿 ��������.
// ������ ���ڰ� A�� ���:
// ó�� ���ڰ� A: now_t�� ������ ���ڸ� �����Ѵ�.
// ó�� ���ڰ� B: ���� �ܰ迡�� �ΰ��� ����� ���� ���°��� �����ϹǷ� �Ѵ� �Ѱ��ش�.

// ������ ���ڰ� B�� ���:
// ó�� ���ڰ� A: �̷� ��찡 �� �� ����. �׷��Ƿ� ������� �ʴ´�.
// ó�� ���ڰ� B: ���� �ܰ迡�� B�� ���̴� ���� ���°��� �����ϹǷ� ���� ��ȯ �� �Ѱ��ش�.

void is_con(int tid, string now_t) {
    // S���ڿ� ���̰� �������� ���
    // �������� ���Ѵ�.
    if (tid == s_n-1)
    {
     
        if (s_word == now_t)
        {
            can_con = true;
        }
        return;
    }

    if (now_t[tid] == 'A') {
        if (now_t[0] == 'A') {
            is_con(tid - 1, now_t.substr(0, now_t.length() - 1));
        }
        else if (now_t[0] == 'B') {
            is_con(tid - 1, now_t.substr(0, now_t.length() - 1));
            string tmp1 = now_t.substr(1, now_t.length());
            string tmp2 = "";

            for (int i = 0; i < tmp1.length(); i++) {
                tmp2 += tmp1[tmp1.length() - i - 1];
            }
            is_con(tid - 1, tmp2);
        }
    }
    else if (now_t[tid] == 'B') {

        if (now_t[0] == 'B') {
            string tmp1 = now_t.substr(1, now_t.length());
            string tmp2 = "";

            for (int i = 0; i < tmp1.length(); i++) {
                tmp2 += tmp1[tmp1.length() - i - 1];
            }
            is_con(tid - 1, tmp2);
        }
    }
    return;
}

int main() {
    // s���ڿ� t���� �Է�
    cin >> s_word;
    cin >> t_word;

    s_n = s_word.length();
    t_n = t_word.length();

    // t���ڿ��� �Ѵܰ辿 ���ƿ��鼭 �Ǵ��Ѵ�. 
    is_con(t_word.length()-1,t_word);

    // ��ȯ ���� ���� ����ϱ�
    if (can_con) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }
    return 0;
};