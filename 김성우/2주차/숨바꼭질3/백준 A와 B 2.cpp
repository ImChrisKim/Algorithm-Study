#include <iostream>
#include <string>
using namespace std;

string s, t;

bool dfs(string current) {
    // ���� ����: ���� ���ڿ��� ��ǥ ���ڿ��� t�� ���� ���
    if (current == t)
        return true;

    // ���� ����: ���� ���ڿ��� ���̰� t���� ū ���
    if (current.length() > t.length())
        return false;

    // ���� ���ڿ��� ���� 'A'�� ���
    if (current.back() == 'A') {
        current.pop_back(); // ������ ���� 'A' ����
        if (dfs(current)) // ��� ȣ��
            return true;
        current.push_back('A'); // ����
    }

    // ���� ���ڿ��� ������ 'B'�̰�, ���� 'A'�� ���
    if (current.front() == 'B' && current.back() == 'A') {
        current.pop_back(); // ������ ���� 'A' ����
        reverse(current.begin(), current.end()); // ���ڿ� ������
        if (dfs(current)) // ��� ȣ��
            return true;
        reverse(current.begin(), current.end()); // ����
        current.push_back('A'); // ����
    }

    return false; // �� ���� ���ǿ� �ش����� �ʴ� ���
}

int main() {
    cin >> s >> t;

    if (dfs(s))
        cout << "1\n";
    else
        cout << "0\n";

    return 0;
}
