#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>

// ��ǥ ���ڿ��� ũ�⸦ �����Ѵ�.
// ���� �� �ִ����� ����� Ʈ���ŷ� Ȱ���Ѵ�.
int n, t_size;
bool can_make = false;
int dp[102];

using namespace std;

// ���ڿ� ���� �������� ����
// ���� ���������� t_size��ŭ Ž���Ѵٸ� ���۰����ϴ�.
// ���� �������� �ʴٸ� 0�� return�Ѵ�.
int dfs(int t_id, string t_word, string i_words[102])
{   
    // ���������� ������ �����ϴ�.
    // �� ��� Ʈ���Ÿ� true�� �����Ѵ�.
    if (t_id == t_size) {
        can_make = true;
        return 1;
    }

    if (dp[t_id] != -1)
    {
        return dp[t_id];
    }

    dp[t_id] = 0;

    // Ʈ���Ÿ� Ȱ���ߴ�.
    // �̹� ������ ��찡 �������Ƿ� �ٸ� ��쿡�� ����� �ʿ䰡 ����.
    if (can_make == true) return 1;
    
    // ���� t_id�� �������� ��Ṯ�ڿ����� ���� �� �������� ����.
    // �����ϴٸ� ���� t_id�� ������ ���Ѵ�.
    for (int i = 0; i < n; i++)
    {
        string t_part = t_word.substr(t_id, i_words[i].length());

        if (t_part != i_words[i]) continue;
        dp[t_id] = max(dp[t_id],dfs(t_id + t_part.length(), t_word, i_words));
    }
    return dp[t_id];
}

int main() {
    // ��ǥ ����, ��� ���ڵ� ����
    string t_word;
    string i_words[102];

    cin >> t_word >> n;
    
    // ��ǥ ���� ũ��
    t_size = t_word.length();
    for (int i = 0; i < n; i++)
    {
        cin >> i_words[i];
    }

    // ���ڿ� ���� ���� ����� dp �ʱ�ȭ �ϱ�
    for (int i = 0; i < t_size; i++)
    {
        dp[i] = -1;
    }

    // ��ǥ ���ڿ��� index�������� Ž���Ѵ�.
    // ���� t_id�������� ��Ṯ�ڿ� ũ�⸸ŭ�� ���Ѵ�.
    dfs(0, t_word, i_words);

    // ������ ���
    if (can_make != true) {
        cout << 0 << endl;
    }
    // �Ұ����� ���
    else if (can_make == true) {
        cout << 1 << endl;
    }

    return 0;
}