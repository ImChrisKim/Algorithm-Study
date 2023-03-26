/* 주사위 윷놀이 */
// play 상황 - 0(시작) ~ 42(도착)
// 기본 이동 map - 다음 칸을 담는다
// 파란칸에서 시작한다면 새로운 map으로 간다
// 특수 map도 다음 칸을 가리킨다
// 현재 기본or특수 map에 있는가를 저장하는 KIND

// 모든 경우의 수를 다 본다 dfs
// 말 4개의 현재 위치

#include <iostream>
#include <vector>
using namespace std;

struct NODE {
	int ind; // map 종류
	int num; // map 내 위치
};

// [5][22]
vector<int> MAP[5]; // 윷놀이 판 - 0:기본, 1~3:파란화살표 진입 이후, 4: 25지점 이후
int used[5][22]; // 현재 말이 존재하는가 아닌가를 표기
NODE player[4]; // 4개의 말의 현위치

int dice[10]; // 주사위 순서 (1~5)

int ans; // 최대 점수 (답)

void init() {
	// 기본 맵 초기화 - 제일 바깥 라인
	for (int i = 0; i <= 21; i++) {
		MAP[0].push_back(i * 2); // 각 칸의 점수
	}

	MAP[1].push_back(10); MAP[1].push_back(13); MAP[1].push_back(16); MAP[1].push_back(19); MAP[1].push_back(25);
	MAP[2].push_back(20); MAP[2].push_back(22); MAP[2].push_back(24); MAP[2].push_back(25);
	MAP[3].push_back(30); MAP[3].push_back(28); MAP[3].push_back(27); MAP[3].push_back(26); MAP[3].push_back(25);
	MAP[4].push_back(25); MAP[4].push_back(30); MAP[4].push_back(35); MAP[4].push_back(40); MAP[4].push_back(42);

	// 말 초기화
	for (int i = 0; i < 4; i++) {
		player[i] = { 0, 0 };
	}
}

void play(int turn, int sum) {
	// 기저조건 - 10번의 턴을 다 돌았다면 점수 갱신 및 종료
	if (turn == 9) {
		if (sum > ans) ans = ans;

		return;
	}

	// 4개의 말 중 이동이 가능하다면 이동시킨 후 다음 플레이로 넘어간다
	for (int i = 0; i < 4; i++) {
		NODE now = player[i];

		if (MAP[now.ind][now.num] == 42) continue; // 이미 도착한 말은 이동 불가
		
		int dInd = 0, dNum = 0;
		if (now.num + dice[turn] > MAP[now.ind].size()) {
			if (now.ind == 0) {
				dInd = 0; dNum = 21;
			}
			else {

			}
		}
		else {
			 
		}
	}
}

int main() {
	init(); // 윷놀이판, 말 초기화
	
	// input
	for (int i = 0; i < 10; i++) cin >> dice[i];

	play(i, 0);

	cout << ans;

	return 0;
}