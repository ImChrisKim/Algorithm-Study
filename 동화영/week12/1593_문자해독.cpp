/* ���� �ص� */
#include <iostream>
using namespace std;

char gword[3000000] = { 0, }; // ���ڿ�
int Word[60] = { 0, }; // 0:A~Z 26:a~z
int used[60] = { 0, }; // ���� Ž������ �κ� ���ڿ����� ������� ���ĺ��� ��
int g, slen; // W�� S�� ����

// Word �迭�� �ε��� ����� ����
// ���ĺ��� ���ڷ� ��ȯ���ִ� �Լ�
// A ~ Z : 0 ~ 25
// a ~ z : 26 ~ 51
int charToInt(char ch) {
	if (ch >= 'A' && ch <= 'Z') { // �빮��
		return (int)(ch - 'A');
	}
	else if (ch >= 'a' && ch <= 'z') { // �ҹ���
		return (int)(ch - 'a') + 26;
	}

	return -1; // ���ĺ��� �ƴ� ���
}

// ���ĺ� ���� ����
bool checkWord() {
	for (int i = 0; i < 52; i++) {
		if (Word[i] != used[i]) return false; // �־��� �κ� ���ڿ��� ������� ���ĺ��� ���� ��
	}

	return true; // ��� �����ϸ� true ��ȯ
}

// 65 : A, 97 : a
int main() {
	char inp;

	// input
	cin >> g >> slen;
	for (int i = 0; i < g; i++) {
		cin >> inp;
		Word[charToInt(inp)]++; // W�� ���ԵǴ� ���ĺ� ���� ����
	}

	for (int i = 0; i < slen; i++) {
		cin >> gword[i];
		if (i < g) { // W ���̸�ŭ�� ���ĺ� ����
			used[charToInt(gword[i])]++;
		}
	}

	int cnt = 0; // ���� ��

	if(checkWord()) cnt++; // ������� ���ĺ� ������ ��� �����ϴٸ� cnt ����
	for (int i = 0; i < slen - g; i++) {
		// ���� �κ� ���ڿ� ��
		// �տ� �� ĭ�� ���ĺ� ���ֱ�
		// �ڿ� �� ĭ�� ���ĺ� �����ֱ�
		used[charToInt(gword[i])]--;
		used[charToInt(gword[i + g])]++;

		if (checkWord()) cnt++; // ������� ���ĺ� ������ ��� �����ϴٸ� cnt ����
	}

	// output
	cout << cnt << "\n";

	return 0;
}