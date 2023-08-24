#include<iostream>
#include<algorithm>
using namespace std;

int N;
double e, s, w, n;
int visited[30][30];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
double prob[4];
double ans;

void dfs(int row, int col, int cnt, double pro) {

	if (cnt == N) {
		ans += pro;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nr = row + dr[i];
		int nc = col + dc[i];

		if (visited[nr][nc]) continue;
		visited[nr][nc] = 1;
		dfs(nr, nc, cnt + 1, pro * prob[i]);
		visited[nr][nc] = 0;
	}

}

void sol() {

	visited[14][14] = 1;
	dfs(14, 14, 0, 1);


}

void input() {

	cin >> N;
	double te, ts, tw, tn;
	cin >> te >> tw >> ts >> tn;
	e = te / 100;
	w = tw / 100;
	s = ts / 100;
	n = tn / 100;
	prob[0] = e;
	prob[1] = w;
	prob[2] = s;
	prob[3] = n;
}

int main() {

	input();

	sol();

	cout.precision(10);

	cout << fixed << ans;

}