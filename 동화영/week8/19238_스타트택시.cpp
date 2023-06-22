/* ��ŸƮ �ý� */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX_N = 21;
const int DIR_NUM = 4;

struct NODE {
	int r;
	int c;
};

struct COOR {
	int r;
	int c;
	int dist;

	// �Ÿ� �������� -> �� �������� -> �� ��������
	bool operator < (COOR nxt) const {
		if (dist < nxt.dist) return false;
		if (dist > nxt.dist) return true;
		if (r < nxt.r) return false;
		if (r > nxt.r) return true;
		if (c < nxt.c) return false;
		if (c > nxt.c) return true;
		return false;
	}
};

int rdir[DIR_NUM] = { -1, 1, 0, 0 }; // �����¿�
int cdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // -1: ��, 0: ��ĭ, 1~M: �°��� ��������
int N, M; // N: ������ ������, M: �°��� ��
int fuel; // ������ ��

NODE taxi; // �ý��� ��ġ
vector<NODE> sPoint; // �� �°��� �������
vector<NODE> ePoint; // �� �°��� ��������

// ���� �ý��� ��ġ�� �������� ���� ����� �°��� ����
// �Ÿ��� �� -> ���� �� -> ���� �� ���� ����
int selectPerson() {
	int num = 0; // ���õ� �°��� ��ȣ

	// visited�� pq �غ�
	// �ý��� ���� ��ġ���� ������ ǥ��
	int visited[MAX_N][MAX_N] = { 0, };
	visited[taxi.r][taxi.c] = 1;

	priority_queue<COOR> pq;
	pq.push({ taxi.r, taxi.c, 0 });

	while (!pq.empty()) {
		// �Ÿ������� ���� ��
		// ������ �Ÿ� ������ ��� ���� ������ �¿췯 �� �°��� �����ϱ� ������
		// �� �Ÿ����� size�� ���Ͽ� sz��ŭ�� ��������
		int sz = pq.size();

		for (int i = 0; i < sz; i++) {
			COOR now = pq.top();
			pq.pop();

			// nowĭ�� �°��� ��ٸ��� �ִٸ� �¿��
			if (MAP[now.r][now.c] > 0) {
				// nowĭ�� �ִ� �°��� �¿췯 ���µ� ��� ������ ���� ���� �����ִ� ������ �纸�� ũ�ٸ�
				// ��� ���� ����
				if (fuel < now.dist) return -1;

				// �¿췯 �� �� ���� ������ ���ᰡ �����Ѵٸ�
				fuel -= now.dist; // ���� �Ҹ�
				num = MAP[now.r][now.c]; // �¿췯 �� �°��� ��ȣ ���� -> ��ȯ
				taxi = { now.r, now.c }; // �ý� �̵�
				MAP[now.r][now.c] = 0; // nowĭ���� ��� ���̴� �°� �����ֱ�
				return num; // �°� ��ȣ ��ȯ
			}

			// nowĭ�� �°��� ���ٸ� �ٽ� 4���� Ž��
			for (int i = 0; i < DIR_NUM; i++) {
				int nr = now.r + rdir[i];
				int nc = now.c + cdir[i];

				if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue; // ���� ���� ����
				if (MAP[nr][nc] == -1) continue; // ���� ���� �Ұ�
				if (visited[nr][nc] == 1) continue; // �̹� �湮�� ĭ�� ����

				pq.push({ nr, nc, now.dist + 1 }); // ������ Ž���� ĭ�� �߰� - �Ÿ��� ���纸�� +1��ŭ
				visited[nr][nc] = 1; // �湮 ǥ��
			}
		}
	}

	return -1;
}

// num�� �°��� ������������ �������ֱ�
int goEnd(int num) {
	NODE sTarget = sPoint[num]; // num�� �°��� ��������
	NODE eTarget = ePoint[num]; // num�� �°��� ��������

	// visited�� queue �غ�
	// num�� �°��� �����������κ��� Ž�� �����ϱ�
	int visited[MAX_N][MAX_N] = { 0, };
	visited[sTarget.r][sTarget.c] = 1;

	queue<NODE> q;
	q.push({ sTarget.r, sTarget.c });

	while (!q.empty()) {
		NODE now = q.front();
		q.pop();

		// 4�������� Ž���ϸ� �������� ã��������
		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.r + rdir[i];
			int nc = now.c + cdir[i];

			if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue; // ���� ���� ����
			if (MAP[nr][nc] == -1) continue; // ���� ���� �Ұ�
			if (visited[nr][nc] > 0) continue; // �̹� �湮�� ĭ�� ����

			// ���������� ã�Ҵٸ� �ٷ� �������ֱ�
			if (nr == eTarget.r && nc == eTarget.c) {
				// ������������ �������ִµ� ��� ������ ���� ���� �����ִ� ������ �纸�� ũ�ٸ�
				// ��� ���� ����
				int dist = visited[now.r][now.c];
				if (fuel < dist) return -1;

				// dist��ŭ�� ���� �Ҹ� �� dist*2��ŭ�� ���ᰡ ����
				// -> ��, ���� �Ҹ���� dist��ŭ�� �������ֱ�
				fuel += dist;
				taxi = { nr, nc }; // �ý� �̵�
				return 0;
			}

			// ���� ���������� ���� ���ߴٸ� ����ĭ�� Ž��
			q.push({ nr, nc });
			visited[nr][nc] = visited[now.r][now.c] + 1; // �������������� �Ÿ��� ����
		}
	}

	return -1;
}

int main() {
	//  input
	cin >> N >> M >> fuel;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) MAP[i][j] = -1; // ���� -1�� �����Ͽ� ����
		}
	}

	int ir, ic, er, ec;;
	cin >> ir >> ic;
	taxi = { ir, ic }; // �ý��� �ʱ���ġ
	
	// 1~M �°��� ����/���� ����
	sPoint.push_back({ 0, 0 }); // �ε��� ���߱� ���� 0���� ���Ƿ� push
	ePoint.push_back({ 0, 0 });
	for (int i = 1; i <= M; i++) {
		cin >> ir >> ic >> er >> ec;
		sPoint.push_back({ ir, ic }); // i�� �°��� ��������
		ePoint.push_back({ er, ec }); // i�� �°��� ��������
		MAP[ir][ic] = i; // MAP�� i�� �°��� �������� ǥ��
	}

	// M���� �°��� �̵���Ų��
	for (int i = 0; i < M; i++) {
		int num = selectPerson(); // ���� �ִܰ�ο� ���ִ� �°��� ����
		if (num == -1) { // �°� �¿췯 ���� �濡 ���ᰡ �ٴڳ��ٸ� ���� ����
			fuel = -1; // ���� �ٴ� -1 ǥ��
			break;
		}

		// num �°��� ������������ ����
		if (goEnd(num) == -1) { // ������������ ���� �濡 ���ᰡ�ٴڳ��ٸ� ���� ����
			fuel = -1; // ���� �ٴ� -1 ǥ��
			break;
		}
	}

	// output
	cout << fuel; // ���� ������ �� ���

	return 0;
}