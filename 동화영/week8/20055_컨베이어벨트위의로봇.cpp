/* �����̾� ��Ʈ ���� �κ� */
#include <iostream>
#include <queue>
using namespace std;
const int MAX_N = 201;

// ��� ������ ���������� 1~2*N ĭ���� �������� �ʴ´�
// ���� �ø��� ��ġ�� ������ ��ġ�� ����ΰ��� �������ش�
// ��, �����̾� ��Ʈ ��ü�� �̵��̸� ȸ���� ������ �ø���/������ ��ġ�� �ݽð�� ���ٰ� ����

queue<int> robots; // �κ����� ��ġ�� ĭ
int used[MAX_N]; // ���� �� ĭ�� �κ��� ��ġ���ִ°�
int MAP[MAX_N]; // �� ĭ�� ������
int N, K; // N: �����̾� ��Ʈ�� ����, K: ������ 0�� ĭ�� ����
int cnt; // �������� 0�� ĭ�� ����

int enterInd, exitInd; // ���� �ø��� ��ġ�� ������ ��ġ�� ����Ű�� �ε���

// 1. �����̾� ��Ʈ�� ��°�� ȸ��
// �����̾ �ð���� ȸ�� -> �����̾�� ���� -> �Ʒ����� �ݽð�� ȸ���Ѵٰ� ����
void rotate() {
	enterInd--;
	exitInd--;

	// 1�� ������ 2*N�� ����ų �� �ְԲ�
	if (enterInd == 0) enterInd = 2 * N;
	if (exitInd == 0) exitInd = 2 * N;
}

// 2. �� �κ��� ���� �̵�
void move() {
	// �κ��� ����ŭ �̵� ���� ���� Ȯ�� �� �̵� ó��
	int sz = robots.size();
	for (int i = 0; i < sz; i++) {
		int now = robots.front();
		robots.pop();

		// ������ �����̾� ȸ������ ���� ������ ��ġ�� �� �κ��̶��
		// �ٷ� ������
		if (now == exitInd) {
			used[now] = 0;
			continue;
		}

		// �̵��Ϸ��� ĭ�� �κ��� ���� �������� 1 �̻��̶�� �̵��Ѵ�
		int tmp = now + 1 > 2 * N ? 1 : now + 1;
		if (used[tmp] == 0 && MAP[tmp] > 0) {
			used[now] = 0; // ���� ĭ used ����ֱ�
			now = tmp; // �̵� ó��
			used[now] = 1; // used ����
			MAP[now]--; // ���ο� ĭ�� ������ --
			if (MAP[now] == 0) cnt++; // ��� �̵����� ���� �ش� ĭ�� �������� 0�� �Ǿ��ٸ� cnt++

			if (now == exitInd) { // �̵��ؿԴ��� ������ ��ġ��� ������
				used[now] = 0; // used ����ֱ�
				continue;
			}
		}

		// �̵��ߴٸ� ���ο� ĭ�� push�� ���̰�
		// �̵����� ���ߴٸ� ������ ĭ�� �ٽ� push�� ���̴�
		robots.push(now);
	}
}

void add() {
	// �ø��� ��ġ�� �κ��� �ø� ���� used�� Ȯ������ �ʴ´� (���ǿ� ��� X)
	if (MAP[enterInd] > 0) { // �������� 1�̻��̶�� �κ� �߰�
		used[enterInd] = 1; // used ����
		MAP[enterInd]--; // �ø��� ��ġ�� ������ --
		if (MAP[enterInd] == 0) cnt++; // ��� �߰��� ���� �������� 0�� �Ǿ��ٸ� cnt++
		robots.push(enterInd); // �κ����� ��ġ�� �߰����ֱ�
	}
}

int main() {
	// input
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++) {
		cin >> MAP[i];
	}

	int lev = 0; // �� ��° ��
	cnt = 0; // �ʱ⿡�� ��ü ĭ�� �������� 1 �̻�
	enterInd = 1, exitInd = N; // �ʱ⿡�� 1�� N�� �ø��� ��ġ/������ ��ġ
	while (cnt < K) { // �������� 0�� ĭ�� K���� �ȴٸ� ����
		rotate(); // 1. �����̾� ��Ʈ�� ��°�� ȸ��
		move(); // 2. �� �κ��� ���� �̵�
		add(); // 3. �ø��� ��ġ�� �κ� �߰�
		lev++; // ��++
	}

	// output
	cout << lev;

	return 0;
}