#include <iostream>
#include <list>
#include "DxLib.h"
#include <queue>
#include <vector>


volatile int EndFlag;
#define MAP_SIZE 10

struct Position {
	int x, y;
};

std::vector<Position> findBoxes(int map[MAP_SIZE][MAP_SIZE]) {
	std::vector<Position> boxPositions;
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			// 0以外、かつ17ではない位置を箱としてリストに追加
			if (map[i][j] != 0 && map[i][j] != 17) {
				boxPositions.push_back({ i, j });
			}
		}
	}
	return boxPositions;
}

// 仮のレジの位置（デフォルトでは 5, 5）
Position registerPos = { 9, 5 };

// 現在の目的地のインデックス
int currentDestinationIndex = 0;

// 次の目的地を取得する関数
Position getNextDestination(const std::vector<Position>& boxes) {
	if (currentDestinationIndex >= boxes.size()) {
		currentDestinationIndex = 0;  // インデックスをリセット
		return registerPos;  // すべての箱を回ったらレジに行く
	}
	else {
		return boxes[currentDestinationIndex++];
	}
}

// BFSを使って目的地までの最短経路を探す
std::vector<Position> BFS(int startX, int startY, int humanmap[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]) {
	std::queue<std::pair<Position, std::vector<Position>>> q;
	bool visited[MAP_SIZE][MAP_SIZE] = { false };  // 訪問フラグ
	std::vector<Position> initialPath = { {startX, startY} };

	q.push({ {startX, startY}, initialPath });
	visited[startX][startY] = true;

	// 4方向に移動するためのオフセット
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };

	// 目的地を取得
	std::vector<Position> boxes = findBoxes(map);  // 箱の位置を動的に取得
	Position target;

	// 箱が見つからなかった場合はレジの位置を変更
	if (boxes.empty()) {
		registerPos = { 5, 6 };  // レジの位置を5,6に変更
		target = registerPos;
	}
	else {
		target = getNextDestination(boxes);   // 次の目的地を取得
	}

	while (!q.empty()) {
		Position current = q.front().first;
		std::vector<Position> path = q.front().second;
		q.pop();

		// 目的地に到達したらその経路を返す
		if (current.x == target.x && current.y == target.y) {
			return path;
		}

		// 上下左右に探索
		for (int i = 0; i < 4; i++) {
			int newX = current.x + dx[i];
			int newY = current.y + dy[i];

			// 範囲チェックと訪問済みチェック
			if (newX >= 0 && newX < MAP_SIZE && newY >= 0 && newY < MAP_SIZE && !visited[newX][newY]) {
				if (humanmap[newX][newY] == 0 && map[newX][newY] == 0) {  // 人がいない、かつmapが0の場所のみ探索
					visited[newX][newY] = true;
					std::vector<Position> newPath = path;
					newPath.push_back({ newX, newY });
					q.push({ {newX, newY}, newPath });
				}
			}
		}
	}

	// 目的地が見つからない場合は、現在位置のみを返す
	return initialPath;
}

void MoveCustomer(int& x, int& y, int humanmap[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int intervalMs) {
	// BFSを使って、最も近いmapが0でない場所への経路を探索
	std::vector<Position> path = BFS(x, y, humanmap, map);

	if (path.size() > 1) {
		// 現在位置をクリア
		humanmap[x][y] = 0;

		// 次の位置に移動
		x = path[1].x;
		y = path[1].y;

		// インターバルを追加
		WaitTimer(intervalMs);

		// 新しい位置にお客さんを描画
		humanmap[x][y] = 1;
	}
}


void DrawScreen(int floor, int Lwall, int Rwall, int Box1, int Box2, int Box3, int LBox1, int LBox2, int LBox3, int LBox4, int LBox5, int LBox6, int LBox7, int LBox8, int Box1f, int Box2f, int Box3f, int LBox1f, int LBox2f, int LBox3f, int LBox4f, int LBox5f, int LBox6f, int LBox7f, int LBox8f, int counter1, int counter2, int humanw1lb, int humanw1rb, int humanw1lf, int humanw1rf, int humanw2lb, int humanw2rb, int humanw2lf, int humanw2rf, int humanw3lb, int humanw3rb, int humanw3lf, int humanw3rf, int humanw4lb, int humanw4rb, int humanw4lf, int humanw4rf, int humanm1lb, int humanm1rb, int humanm1lf, int humanm1rf, int humanm2lb, int humanm2rb, int humanm2lf, int humanm2rf, int humanm3lb, int humanm3rb, int humanm3lf, int humanm3rf, int omi, int back, int select, int product_display, int object_round_left, int map[10][10], int humanmap[10][10], int scene, int selected[2], bool move) {
	int i, j, k;
	DrawRotaGraph(440, -62, 1, 0, Rwall, TRUE);
	DrawRotaGraph(200, -62, 1, 0, Lwall, TRUE);
	if (move && map[selected[0]][selected[1]] >= 1 && map[selected[0]][selected[1]] <= 8) {
		DrawRotaGraph(100, 350, 0.4, 0, product_display, TRUE);
	}
	if (move && scene == 1) {
		DrawRotaGraph(180, 350, 1, 0, object_round_left, TRUE);
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			switch (map[i][j]) {
				{
			case 5://左下を向いたラージボックス
				map[i][j - 1] = -1;
				break;
			case 6://右下を向いたラージボックス
				map[i - 1][j] = -2;
				break;
			case 7://左奥を向いたラージボックス
				map[i - 1][j] = -3;
				break;
			case 8://右奥を向いたラージボックス
				map[i][j - 1] = -4;
				break;
			case 13://左下を向いたラージボックス
				map[i][j - 1] = -5;
				break;
			case 14://右下を向いたラージボックス
				map[i - 1][j] = -6;
				break;
			case 15://左奥を向いたラージボックス
				map[i - 1][j] = -7;
				break;
			case 16://右奥を向いたラージボックス
				map[i][j - 1] = -8;
				break;
			case 17://カウンター
				map[i - 1][j] = -9;
				break;
				}
			}
		}
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			//オブジェクトの描画
			switch (map[i][j]) {
			case -9:
				if (selected[0] - 1 == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 130 - 10, 1, 0, counter2, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 130, 1, 0, counter2, TRUE);
				}
				break;
			case -8:
				if (selected[0] == i && selected[1] - 1 == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 130 - 10, 1, 0, LBox8f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 130, 1, 0, LBox8f, TRUE);
				}
				break;
			case -7:
				if (selected[0] - 1 == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 130 - 10, 1, 0, LBox7f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 130, 1, 0, LBox7f, TRUE);
				}
				break;
			case -6:
				if (selected[0] - 1 == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 133 - 10, 1, 0, LBox6f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 133, 1, 0, LBox6f, TRUE);
				}
				break;
			case -5:
				if (selected[0] == i && selected[1] - 1 == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 135 - 10, 1, 0, LBox5f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 135, 1, 0, LBox5f, TRUE);
				}
				break;
			case -4:
				if (selected[0] == i && selected[1] - 1 == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 130 - 10, 1, 0, LBox8, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 130, 1, 0, LBox8, TRUE);
				}
				break;
			case -3:
				if (selected[0] - 1 == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 130 - 10, 1, 0, LBox7, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 130, 1, 0, LBox7, TRUE);
				}
				break;
			case -2:
				if (selected[0] - 1 == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 133 - 10, 1, 0, LBox6, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 323, 12 * i + 12 * j + 133, 1, 0, LBox6, TRUE);
				}
				break;
			case -1:
				if (selected[0] == i && selected[1] - 1 == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 135 - 10, 1, 0, LBox5, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 318, 12 * i + 12 * j + 135, 1, 0, LBox5, TRUE);
				}
				break;
			case 0:
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150 - 10, 1, 0, floor, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150, 1, 0, floor, TRUE);
				}
				//人の描画
				switch (humanmap[i][j]) {
					//ワンピース女性
				case 1:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw1lb, TRUE);
					break;
				case 2:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw1rb, TRUE);
					break;
				case 3:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw1lf, TRUE);
					break;
				case 4:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw1rf, TRUE);
					break;
					//ズボン女性店員
				case 5:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw2lb, TRUE);
					break;
				case 6:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw2rb, TRUE);
					break;
				case 7:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw2lf, TRUE);
					break;
				case 8:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw2rf, TRUE);
					break;
					//スカート女性店員
				case 9:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw3lb, TRUE);
					break;
				case 10:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw3rb, TRUE);
					break;
				case 11:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw3lf, TRUE);
					break;
				case 12:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw3rf, TRUE);
					break;
					//女学生
				case 13:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw4lb, TRUE);
					break;
				case 14:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw4rb, TRUE);
					break;
				case 15:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw4lf, TRUE);
					break;
				case 16:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanw4rf, TRUE);
					break;
					//私服男性1
				case 17:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm1lb, TRUE);
					break;
				case 18:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm1rb, TRUE);
					break;
				case 19:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm1lf, TRUE);
					break;
				case 20:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm1rf, TRUE);
					break;
					//私服男性2
				case 21:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm2lb, TRUE);
					break;
				case 22:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm2rb, TRUE);
					break;
				case 23:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm2lf, TRUE);
					break;
				case 24:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm2rf, TRUE);
					break;
					//男性店員
				case 25:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm3lb, TRUE);
					break;
				case 26:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm3rb, TRUE);
					break;
				case 27:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm3lf, TRUE);
					break;
				case 28:
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 120, 0.5, 0, humanm3rf, TRUE);
					break;
				}
				break;
			case 1://左下を向いたボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117 - 10, 1, 0, Box1, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box1, TRUE);
				}
				break;
			case 2://右下を向いたボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117 - 10, 1, 0, Box2, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box2, TRUE);
				}
				break;
			case 3://右奥を向いたボックス
			case 4://左奥を向いたボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117 - 10, 1, 0, Box3, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box3, TRUE);
				}
				break;
			case 5://左下を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 121 - 10, 1, 0, LBox1, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 121, 1, 0, LBox1, TRUE);
				}
				break;
			case 6://右下を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 119 - 10, 1, 0, LBox2, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 119, 1, 0, LBox2, TRUE);
				}
				break;
			case 7://左奥を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 117 - 10, 1, 0, LBox3, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 117, 1, 0, LBox3, TRUE);
				}
				break;
			case 8://右奥を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 117 - 10, 1, 0, LBox4, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 117, 1, 0, LBox4, TRUE);
				}
				break;
			case 9://左下を向いたボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117 - 10, 1, 0, Box1f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box1f, TRUE);
				}
				break;
			case 10://右下を向いたボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117 - 10, 1, 0, Box2f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box2f, TRUE);
				}
				break;
			case 11://右奥を向いたボックス
			case 12://左奥を向いたボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117 - 10, 1, 0, Box3f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box3f, TRUE);
				}
				break;
			case 13://左下を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 121 - 10, 1, 0, LBox1f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 121, 1, 0, LBox1f, TRUE);
				}
				break;
			case 14://右下を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 119 - 10, 1, 0, LBox2f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 119, 1, 0, LBox2f, TRUE);
				}
				break;
			case 15://左奥を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 117 - 10, 1, 0, LBox3f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 315, 12 * i + 12 * j + 117, 1, 0, LBox3f, TRUE);
				}
				break;
			case 16://右奥を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 117 - 10, 1, 0, LBox4f, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 325, 12 * i + 12 * j + 117, 1, 0, LBox4f, TRUE);
				}
				break;
			case 17:
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 310, 12 * i + 12 * j + 117 - 10, 1, 0, counter1, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 310, 12 * i + 12 * j + 117, 1, 0, counter1, TRUE);
				}
				break;
			}
			if (scene == 1)DrawRotaGraph(24 * selected[1] - selected[0] * 24 + 320, 12 * selected[0] + 12 * selected[1] + 150, 1, 0, select, TRUE);
		}
	}
	if (scene == 0) {
		DrawRotaGraph(100, 400, 0.5, 0, omi, TRUE);
	}
	else if (scene == 1) {
		DrawRotaGraph(50, 30, 1, 0, back, TRUE);
	}
}


DWORD WINAPI MainThread(LPVOID)
{
	//初期化
	int Music;
	int floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, LBox5, LBox6, LBox7, LBox8, Box1f, Box2f, Box3f, LBox1f, LBox2f, LBox3f, LBox4f, LBox5f, LBox6f, LBox7f, LBox8f, counter1, counter2, omi;
	int humanw1lb, humanw1rb, humanw1lf, humanw1rf, humanw2lb, humanw2rb, humanw2lf, humanw2rf, humanw3lb, humanw3rb, humanw3lf, humanw3rf, humanw4lb, humanw4rb, humanw4lf, humanw4rf, humanm1lb, humanm1rb, humanm1lf, humanm1rf, humanm2lb, humanm2rb, humanm2lf, humanm2rf, humanm3lb, humanm3rb, humanm3lf, humanm3rf;
	int select, back, product_display, object_round_left;
	int scene = 0, money = 0;
	bool releaseKeyF = true, releaseKeyB = true, releaseKeySPACE = true, releaseKeyUP = true, releaseKeyDOWN = true, releaseKeyTurn = true;
	bool releaseKeyLEFT = true, releaseKeyRIGHT = true, releaseKeyI = true, releaseKeyC = true, releaseKeyG = true, releaseKeyH = true;
	bool releaseKeyD = true;
	bool sceneF = false, move = false, waitting_guest = true;
	std::list<int> money_gest{5,55,555};
	int map[10][10]{};
	int humanmap[10][10]{};
	int selected[2] = { 0, 0 };
	int humanselected[2] = { 8, 9 }; //humanmapと同じにしておく
	map[3][3] = 2;
	map[3][1] = 8;
	map[9][8] = 17;
	humanmap[8][9] = 5;
	//humanmap[5][6] = 9;
	//humanmap[5][6] = 25;


	//お客さんの位置
	int x = 0, y = 6;
	int startTime = GetNowCount();
	int timeLimit = 5000; // 5000ミリ秒 (5秒)
	srand((unsigned)time(NULL)); // ランダムシードの設定
	int intervalMs = 500;  // 500msのインターバル


	floor = LoadGraph("./images/floor.png", TRUE);
	Lwall = LoadGraph("./images/wallleft.png", TRUE);
	Rwall = LoadGraph("./images/wallright.png", TRUE);
	Box1 = LoadGraph("./images/miniShelfLeft.png", TRUE);
	Box2 = LoadGraph("./images/miniShelfRight.png", TRUE);
	Box3 = LoadGraph("./images/miniShelfBack.png", TRUE);
	LBox1 = LoadGraph("./images/miniLargeShelfLeft1.png", TRUE);
	LBox2 = LoadGraph("./images/miniLargeShelfRight1.png", TRUE);
	LBox3 = LoadGraph("./images/miniLargeShelfBackLeft1.png", TRUE);
	LBox4 = LoadGraph("./images/miniLargeShelfBackRight1.png", TRUE);
	LBox5 = LoadGraph("./images/miniLargeShelfLeft2.png", TRUE);
	LBox6 = LoadGraph("./images/miniLargeShelfRight2.png", TRUE);
	LBox7 = LoadGraph("./images/miniLargeShelfBackLeft2.png", TRUE);
	LBox8 = LoadGraph("./images/miniLargeShelfBackRight2.png", TRUE);
	Box1f = LoadGraph("./images/miniShelfLeftfilled.png", TRUE);
	Box2f = LoadGraph("./images/miniShelfRightfilled.png", TRUE);
	Box3f = LoadGraph("./images/miniShelfBack.png", TRUE);
	LBox1f = LoadGraph("./images/miniLargeShelfLeft1filled.png", TRUE);
	LBox2f = LoadGraph("./images/miniLargeShelfRight1filled.png", TRUE);
	LBox3f = LoadGraph("./images/miniLargeShelfBackLeft1.png", TRUE);
	LBox4f = LoadGraph("./images/miniLargeShelfBackRight1.png", TRUE);
	LBox5f = LoadGraph("./images/miniLargeShelfLeft2filled.png", TRUE);
	LBox6f = LoadGraph("./images/miniLargeShelfRight2filled.png", TRUE);
	LBox7f = LoadGraph("./images/miniLargeShelfBackLeft2.png", TRUE);
	LBox8f = LoadGraph("./images/miniLargeShelfBackRight2.png", TRUE);
	counter1 = LoadGraph("./images/counter_right_right1.png", TRUE);
	counter2 = LoadGraph("./images/counter_right_right2.png", TRUE);
	humanw1lb = LoadGraph("./images/human/woman/woman_one-piece/woman_left_back_one-piece.png", TRUE);
	humanw1rb = LoadGraph("./images/human/woman/woman_one-piece/woman_right_back_one-piece.png", TRUE);
	humanw1lf = LoadGraph("./images/human/woman/woman_one-piece/woman_left_front_one-piece.png", TRUE);
	humanw1rf = LoadGraph("./images/human/woman/woman_one-piece/woman_right_front_one-piece.png", TRUE);
	humanw2lb = LoadGraph("./images/human/woman/woman_pants_shop/woman_left_back_pants_shop.png", TRUE);
	humanw2rb = LoadGraph("./images/human/woman/woman_pants_shop/woman_right_back_pants_shop.png", TRUE);
	humanw2lf = LoadGraph("./images/human/woman/woman_pants_shop/woman_left_front_pants_shop.png", TRUE);
	humanw2rf = LoadGraph("./images/human/woman/woman_pants_shop/woman_right_front_pants_shop.png", TRUE);
	humanw3lb = LoadGraph("./images/human/woman/woman_skirt_shop/woman_left_back_skirt_shop.png", TRUE);
	humanw3rb = LoadGraph("./images/human/woman/woman_skirt_shop/woman_right_back_skirt_shop.png", TRUE);
	humanw3lf = LoadGraph("./images/human/woman/woman_skirt_shop/woman_left_front_skirt_shop.png", TRUE);
	humanw3rf = LoadGraph("./images/human/woman/woman_skirt_shop/woman_right_front_skirt_shop.png", TRUE);
	humanw4lb = LoadGraph("./images/human/woman/woman_student/woman_student_left_back.png", TRUE);
	humanw4rb = LoadGraph("./images/human/woman/woman_student/woman_student_right_back.png", TRUE);
	humanw4lf = LoadGraph("./images/human/woman/woman_student/woman_student_left_fornt.png", TRUE);
	humanw4rf = LoadGraph("./images/human/woman/woman_student/woman_student_right_front.png", TRUE);
	humanm1lb = LoadGraph("./images/human/man/man_1/man_left_back_1.png", TRUE);
	humanm1rb = LoadGraph("./images/human/man/man_1/man_right_back_1.png", TRUE);
	humanm1lf = LoadGraph("./images/human/man/man_1/man_left_front_1.png", TRUE);
	humanm1rf = LoadGraph("./images/human/man/man_1/man_right_front_1.png", TRUE);
	humanm2lb = LoadGraph("./images/human/man/man_2/man_left_back_2.png", TRUE);
	humanm2rb = LoadGraph("./images/human/man/man_2/man_right_back_2.png", TRUE);
	humanm2lf = LoadGraph("./images/human/man/man_2/man_left_front_2.png", TRUE);
	humanm2rf = LoadGraph("./images/human/man/man_2/man_right_front_2.png", TRUE);
	humanm3lb = LoadGraph("./images/human/man/man_shop/man_left_back_shop.png", TRUE);
	humanm3rb = LoadGraph("./images/human/man/man_shop/man_right_back_shop.png", TRUE);
	humanm3lf = LoadGraph("./images/human/man/man_shop/man_left_front_shop.png", TRUE);
	humanm3rf = LoadGraph("./images/human/man/man_shop/man_right_flont_shop.png", TRUE);
	omi = LoadGraph("./images/object_move_icon.png", TRUE);
	select = LoadGraph("./images/selected.png", TRUE);
	back = LoadGraph("./images/back.png", TRUE);
	product_display = LoadGraph("./images/product_display.png", TRUE);
	object_round_left = LoadGraph("./images/object_round_left.png", TRUE);

	Music = LoadSoundMem("./Music/異世界の街.ogg");
	PlaySoundMem(Music, DX_PLAYTYPE_LOOP);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawScreen(floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, LBox5, LBox6, LBox7, LBox8, Box1f, Box2f, Box3f, LBox1f, LBox2f, LBox3f, LBox4f, LBox5f, LBox6f, LBox7f, LBox8f, counter1, counter2, humanw1lb, humanw1rb, humanw1lf, humanw1rf, humanw2lb, humanw2rb, humanw2lf, humanw2rf, humanw3lb, humanw3rb, humanw3lf, humanw3rf, humanw4lb, humanw4rb, humanw4lf, humanw4rf, humanm1lb, humanm1rb, humanm1lf, humanm1rf, humanm2lb, humanm2rb, humanm2lf, humanm2rf, humanm3lb, humanm3rb, humanm3lf, humanm3rf, omi, back, select, product_display, object_round_left, map, humanmap, scene, selected, move);
		
		// 一定時間経過後にhumanmap[0][7]を変更
		if (GetNowCount() - startTime >= timeLimit) {
			MoveCustomer(x, y, humanmap, map, intervalMs);
		}

		if (CheckHitKey(KEY_INPUT_F) && releaseKeyF) {
			scene = 1;
		}
		if (CheckHitKey(KEY_INPUT_B) && releaseKeyB && scene == 1) {
			scene = 0;
			move = false;
		}
		if (scene == 0) {
			//人移動
			if (CheckHitKey(KEY_INPUT_UP) && releaseKeyUP) {
				//上に移動
				if (humanselected[0] > 0) {
					if (5 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 8) { //女性ズボン店員
						humanmap[humanselected[0]][humanselected[1]] = 6;
					}
					else if (9 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 12) { //女性スカート店員
						humanmap[humanselected[0]][humanselected[1]] = 10;
					}
					else if (25 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 28) { //男性店員
						humanmap[humanselected[0]][humanselected[1]] = 26;
					}
					//移動先にものがなかったら
					if (map[humanselected[0] - 1][humanselected[1]] == 0) {
						humanmap[humanselected[0] - 1][humanselected[1]] = humanmap[humanselected[0]][humanselected[1]];
						humanmap[humanselected[0]][humanselected[1]] = 0;
						humanselected[0]--;
					}
				}
			}
			releaseKeyUP = (CheckHitKey(KEY_INPUT_UP) == 0);
			if (CheckHitKey(KEY_INPUT_DOWN) && releaseKeyDOWN) {
				//下に移動(座標９より小さかったら動ける)
				if (humanselected[0] < 9) {
					if (5 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 8) { //女性ズボン店員
						humanmap[humanselected[0]][humanselected[1]] = 7;
					}
					else if (9 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 12) { //女性スカート店員
						humanmap[humanselected[0]][humanselected[1]] = 11;
					}
					else if (25 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 28) { //男性店員
						humanmap[humanselected[0]][humanselected[1]] = 27;
					}
					//移動先にものがなかったら
					if (map[humanselected[0] + 1][humanselected[1]] == 0) {
						humanmap[humanselected[0] + 1][humanselected[1]] = humanmap[humanselected[0]][humanselected[1]];
						humanmap[humanselected[0]][humanselected[1]] = 0;
						humanselected[0]++;
					}
				}
			}
			releaseKeyDOWN = (CheckHitKey(KEY_INPUT_DOWN) == 0);
			if (CheckHitKey(KEY_INPUT_RIGHT) && releaseKeyRIGHT) {
				//右に移動
				if (humanselected[1] < 9) {
					if (5 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 8) { //女性ズボン店員
						humanmap[humanselected[0]][humanselected[1]] = 8;
					}
					else if (9 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 12) { //女性スカート店員
						humanmap[humanselected[0]][humanselected[1]] = 11;
					}
					else if (25 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 28) { //男性店員
						humanmap[humanselected[0]][humanselected[1]] = 28;
					}
					//移動先にものがなかったら
					if (map[humanselected[0]][humanselected[1] + 1] == 0) {
						humanmap[humanselected[0]][humanselected[1] + 1] = humanmap[humanselected[0]][humanselected[1]];
						humanmap[humanselected[0]][humanselected[1]] = 0;
						humanselected[1]++;
					}
				}
			}
			releaseKeyRIGHT = (CheckHitKey(KEY_INPUT_RIGHT) == 0);
			if (CheckHitKey(KEY_INPUT_LEFT) && releaseKeyLEFT) {
				//左に移動
				if (humanselected[1] > 0) {
					if (5 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 8) { //女性ズボン店員
						humanmap[humanselected[0]][humanselected[1]] = 5;
					}
					else if (9 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 12) { //女性スカート店員
						humanmap[humanselected[0]][humanselected[1]] = 9;
					}
					else if (25 <= humanmap[humanselected[0]][humanselected[1]] and humanmap[humanselected[0]][humanselected[1]] <= 28) { //男性店員
						humanmap[humanselected[0]][humanselected[1]] = 25;
					}
					//移動先にものがなかったら
					if (map[humanselected[0]][humanselected[1] - 1] == 0) {
						humanmap[humanselected[0]][humanselected[1] - 1] = humanmap[humanselected[0]][humanselected[1]];
						humanmap[humanselected[0]][humanselected[1]] = 0;
						humanselected[1]--;
					}
				}
			}
			releaseKeyLEFT = (CheckHitKey(KEY_INPUT_LEFT) == 0);
			//お金巻き上げ機構
			if (waitting_guest) {
				if (CheckHitKey(KEY_INPUT_C) && releaseKeyC) {
					if (humanmap[humanselected[0]][humanselected[1]] == humanmap[8][9]) {
						humanmap[1][1] = 1; //動作確認用
						std::list<int>::iterator it = money_gest.begin();
						money = *it;
						money_gest.pop_front();
						if (money_gest.size() == 0) {
							waitting_guest = false;
							humanmap[1][1] = 0; //動作確認用
						}
					}
				}
			}
			releaseKeyC = (CheckHitKey(KEY_INPUT_C) == 0);
		}
		else if (scene == 1) {
				//オブジェクト移動画面
				if (CheckHitKey(KEY_INPUT_SPACE) && releaseKeySPACE) {
					move = move ? false : true;
				}
				if (move) {
					//1*1の棚の追加
					if (CheckHitKey(KEY_INPUT_G) && releaseKeyG) {
						if (map[selected[0]][selected[1]] == 0 && humanmap[selected[0]][selected[1]] == 0) {
							map[selected[0]][selected[1]] = 1;
						}
					}
					releaseKeyG = (CheckHitKey(KEY_INPUT_G) == 0);
					//1*2の棚の追加
					if (CheckHitKey(KEY_INPUT_H) && releaseKeyH) {
						if (selected[1] > 0) {
							if (map[selected[0]][selected[1] - 1] == 0 && map[selected[0]][selected[1]] == 0) {
								if (humanmap[selected[0]][selected[1] - 1] == 0 && humanmap[selected[0]][selected[1]] == 0) {
									map[selected[0]][selected[1]] = 5;
								}
							}
						}
					}
					releaseKeyH = (CheckHitKey(KEY_INPUT_H) == 0);
					//棚の削除
					if (CheckHitKey(KEY_INPUT_D) && releaseKeyD) {
						if (map[selected[0]][selected[1]] == 0) {

						}
						else if (map[selected[0]][selected[1]] >= 1 && map[selected[0]][selected[1]] <= 4 || map[selected[0]][selected[1]] >= 9 && map[selected[0]][selected[1]] <= 12) {
							map[selected[0]][selected[1]] = 0;
						}
						else if (map[selected[0]][selected[1]] == 5 || map[selected[0]][selected[1]] == 8 || map[selected[0]][selected[1]] == 9 || map[selected[0]][selected[1]] == 12) {
							map[selected[0]][selected[1] - 1] = 0;
							map[selected[0]][selected[1]] = 0;
						}
						else {
							map[selected[0] - 1][selected[1]] = 0;
							map[selected[0]][selected[1]] = 0;
						}
					}
					if (map[selected[0]][selected[1]] >= 1 && map[selected[0]][selected[1]] <= 8) {
						if (CheckHitKey(KEY_INPUT_I) && releaseKeyI) {
							map[selected[0]][selected[1]] += 8;
						}
						releaseKeyI = (CheckHitKey(KEY_INPUT_I) == 0);
					}
					if (map[selected[0]][selected[1]] != 0) {
						if (map[selected[0]][selected[1]] == -1 || map[selected[0]][selected[1]] == -4 || map[selected[0]][selected[1]] == -5 || map[selected[0]][selected[1]] == -8) {
							selected[1]++;
						}
						if (map[selected[0]][selected[1]] == -2 || map[selected[0]][selected[1]] == -3 || map[selected[0]][selected[1]] == -6 || map[selected[0]][selected[1]] == -7) {
							selected[0]++;
						}

						//オブジェクト移動
						if (CheckHitKey(KEY_INPUT_UP) && releaseKeyUP) {
							//上に移動
							if (selected[0] > 0) {
								//移動先にものがなかったら
								if (map[selected[0] - 1][selected[1] - 1] == 0 && map[selected[0] - 1][selected[1]] == 0 && (map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8 ) && humanmap[selected[0] - 1][selected[1] - 1] == 0 && humanmap[selected[0] - 1][selected[1]] == 0) {
									map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									map[selected[0]][selected[1] - 1] = 0;
									selected[0]--;
								}
								else if (map[selected[0] - 2][selected[1]] == 0 && (map[selected[0] - 1][selected[1]] == -2 || map[selected[0] - 1][selected[1]] == -3 || map[selected[0] - 1][selected[1]] == -6 || map[selected[0] - 1][selected[1]] == -7) && humanmap[selected[0] - 2][selected[1]] == 0) {
									if (selected[0] > 1) {
										map[selected[0] - 2][selected[1]] = map[selected[0] - 1][selected[1]];
										map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
										map[selected[0]][selected[1]] = 0;
										selected[0]--;
									}
								}
								else if (map[selected[0] - 1][selected[1]] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 9)) && humanmap[selected[0] - 1][selected[1]] == 0) {
									map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									selected[0]--;
								}
							}
						}
						releaseKeyUP = (CheckHitKey(KEY_INPUT_UP) == 0);
						if (CheckHitKey(KEY_INPUT_DOWN) && releaseKeyDOWN) {
							//下に移動(座標９より小さかったら動ける)
							if (selected[0] < 9) {
								//移動先にものがなかったら
								if (map[selected[0] + 1][selected[1]] == map[7][9]) {
									if (map[selected[0] + 1][selected[1] - 1] == 0 && map[selected[0] + 1][selected[1]] == 0 && (map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8) && humanmap[selected[0] + 1][selected[1] - 1] == 0 && humanmap[selected[0] + 1][selected[1]] == 0) {
										map[selected[0] + 1][selected[1]] = map[selected[0]][selected[1]];
										map[selected[0]][selected[1]] = 0;
										map[selected[0]][selected[1] - 1] = 0;
										selected[0]++;
									}
									else if (map[selected[0] + 1][selected[1]] == 0 && (map[selected[0]][selected[1]] == 6 || map[selected[0]][selected[1]] == 7 || map[selected[0]][selected[1]] == 14 || map[selected[0]][selected[1]] == 15) && humanmap[selected[0] + 1][selected[1]] == 0) {
										map[selected[0] + 1][selected[1]] = map[selected[0]][selected[1]];
										map[selected[0]][selected[1]] = map[selected[0] - 1][selected[1]];
										map[selected[0] - 1][selected[1]] = 0;
										selected[0]++;
									}
									else if (map[selected[0] + 1][selected[1]] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 9)) && humanmap[selected[0] + 1][selected[1]] == 0) {
										map[selected[0] + 1][selected[1]] = map[selected[0]][selected[1]];
										map[selected[0]][selected[1]] = 0;
										selected[0]++;
									}
								}
							}
						}
						releaseKeyDOWN = (CheckHitKey(KEY_INPUT_DOWN) == 0);
						if (CheckHitKey(KEY_INPUT_RIGHT) && releaseKeyRIGHT) {
							//右に移動
							if (selected[1] < 9) {
								//移動先にものがなかったら
								if (map[selected[0] - 1][selected[1] + 1] == 0 && map[selected[0]][selected[1] + 1] == 0 && (map[selected[0] - 1][selected[1]] == -2 || map[selected[0] - 1][selected[1]] == -3 || map[selected[0] - 1][selected[1]] == -6 || map[selected[0] - 1][selected[1]] == -7) && humanmap[selected[0] - 1][selected[1] + 1] == 0 && humanmap[selected[0]][selected[1] + 1] == 0) {
									map[selected[0]][selected[1] + 1] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									map[selected[0] - 1][selected[1]] = 0;
									selected[1]++;
								}
								else if (map[selected[0]][selected[1] + 1] == 0 && (map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8)&& humanmap[selected[0]][selected[1] + 1] == 0) {
									map[selected[0]][selected[1] + 1] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = map[selected[0]][selected[1] - 1];
									map[selected[0]][selected[1] - 1] = 0;
									selected[1]++;
								}
								else if (map[selected[0]][selected[1] + 1] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 9)) && humanmap[selected[0]][selected[1] + 1] == 0) {
									map[selected[0]][selected[1] + 1] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									selected[1]++;
								}
							}
						}
						releaseKeyRIGHT = (CheckHitKey(KEY_INPUT_RIGHT) == 0);
						if (CheckHitKey(KEY_INPUT_LEFT) && releaseKeyLEFT) {
							//左に移動
							if (selected[1] > 0) {
								//移動先にものがなかったら
								if (map[selected[0] - 1][selected[1] - 1] == 0 && map[selected[0]][selected[1] - 1] == 0 && (map[selected[0] - 1][selected[1]] == -2 || map[selected[0] - 1][selected[1]] == -3 || map[selected[0] - 1][selected[1]] == -6 || map[selected[0] - 1][selected[1]] == -7) && humanmap[selected[0] - 1][selected[1]-1] == 0 && humanmap[selected[0]][selected[1] - 1] == 0) {
									map[selected[0]][selected[1] - 1] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									map[selected[0] - 1][selected[1]] = 0;
									selected[1]--;
								}
								else if (map[selected[0]][selected[1] - 2] == 0 && (map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8) && humanmap[selected[0]][selected[1] - 2] == 0) {
									if (selected[1] > 1) {
										map[selected[0]][selected[1] - 2] = map[selected[0]][selected[1] - 1];
										map[selected[0]][selected[1] - 1] = map[selected[0]][selected[1]];
										map[selected[0]][selected[1]] = 0;
										selected[1]--;
									}
								}
								else if (map[selected[0]][selected[1] - 1] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 9)) && humanmap[selected[0]][selected[1] - 1] == 0) {
									map[selected[0]][selected[1] - 1] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									selected[1]--;
								}
							}
						}
						releaseKeyLEFT = (CheckHitKey(KEY_INPUT_LEFT) == 0);

						if (CheckHitKey(KEY_INPUT_Z) && releaseKeyTurn) {
							int& currentObject = map[selected[0]][selected[1]];

							// オブジェクトの向きを切り替える処理
							switch (currentObject) {
							case 1: currentObject = 2; break; // 左下→右下
							case 9: currentObject = 10; break; // 左下→右下
							case 2: currentObject = 3; break; // 右下→右奥
							case 10: currentObject = 11; break; // 左下→右下
							case 3: currentObject = 4; break; // 右奥→左奥
							case 11: currentObject = 12; break; // 左下→右下
							case 4: currentObject = 1; break; // 左奥→左下
							case 12: currentObject = 9; break; // 左下→右下
							case 5:
								if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0) && humanmap[selected[0] - 1][selected[1]] == 0) {
									currentObject = 6;
									map[selected[0]][selected[1] - 1] = 0;
									map[selected[0] - 1][selected[1]] = -1;
									std::cout << map;
									break; // ラージボックス左下→右下
								}
							case 13:
								if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0) && humanmap[selected[0] - 1][selected[1]] == 0) {
									currentObject = 14;
									map[selected[0]][selected[1] - 1] = 0;
									map[selected[0] - 1][selected[1]] = -5;
									std::cout << map;
									break; // ラージボックス左下→右下
								}
							case 6:
								if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0) && humanmap[selected[0]][selected[1] - 1] == 0) {
									currentObject = 8;
									map[selected[0] - 1][selected[1]] = 0;
									map[selected[0]][selected[1] - 1] = -2;
									break; // ラージボックス右下→右奥
								}
							case 14:
								if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0) && humanmap[selected[0]][selected[1] - 1] == 0) {
									currentObject = 16;
									map[selected[0] - 1][selected[1]] = 0;
									map[selected[0]][selected[1] - 1] = -6;
									break; // ラージボックス右下→右奥
								}
							case 7:
								if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0) && humanmap[selected[0]][selected[1] - 1] == 0) {
									currentObject = 5;
									map[selected[0] - 1][selected[1]] = 0;
									map[selected[0]][selected[1] - 1] = -3;
									break; // ラージボックス左奥→左下
								}
							case 15:
								if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0) && humanmap[selected[0]][selected[1] - 1] == 0) {
									currentObject = 13;
									map[selected[0] - 1][selected[1]] = 0;
									map[selected[0]][selected[1] - 1] = -7;
									break; // ラージボックス左奥→左下
								}
							case 8:
								if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0) && humanmap[selected[0] - 1][selected[1]] == 0) {
									currentObject = 7;
									map[selected[0]][selected[1] - 1] = 0;
									map[selected[0] - 1][selected[1]] = -4;
									break; // ラージボックス右奥→左奥
								}
							case 16:
								if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0) && humanmap[selected[0] - 1][selected[1]] == 0) {
									currentObject = 15;
									map[selected[0]][selected[1] - 1] = 0;
									map[selected[0] - 1][selected[1]] = -8;
									break; // ラージボックス右奥→左奥
								}
							}
							// 新しいオブジェクトをその位置に設定
							map[selected[0]][selected[1]] = currentObject;
						}
						releaseKeyTurn = (CheckHitKey(KEY_INPUT_Z) == 0);

					}
				}
				else {
					//カーソル移動
					if (CheckHitKey(KEY_INPUT_UP) && releaseKeyUP) {
						//上に移動
						if (0 < selected[0]) {
							selected[0]--;
						}
					}
					releaseKeyUP = (CheckHitKey(KEY_INPUT_UP) == 0);
					if (CheckHitKey(KEY_INPUT_DOWN) && releaseKeyDOWN) {
						//下に移動
						if (selected[0] < 9) {
							selected[0]++;
						}
					}
					releaseKeyDOWN = (CheckHitKey(KEY_INPUT_DOWN) == 0);
					if (CheckHitKey(KEY_INPUT_RIGHT) && releaseKeyRIGHT) {
						//右に移動
						if (selected[1] < 9) {
							selected[1]++;
						}
					}
					releaseKeyRIGHT = (CheckHitKey(KEY_INPUT_RIGHT) == 0);
					if (CheckHitKey(KEY_INPUT_LEFT) && releaseKeyLEFT) {
						//左に移動
						if (0 < selected[1]) {
							selected[1]--;
						}
					}
					releaseKeyLEFT = (CheckHitKey(KEY_INPUT_LEFT) == 0);
				}
				releaseKeySPACE = (CheckHitKey(KEY_INPUT_SPACE) == 0);

			}
			releaseKeyF = (CheckHitKey(KEY_INPUT_F) == 0);
			releaseKeyB = (CheckHitKey(KEY_INPUT_B) == 0);
		}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetAlwaysRunFlag(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	HANDLE hand;
	DWORD id;
	hand = CreateThread(NULL, 0, MainThread, 0, 0, &id);
	while (ProcessMessage() == 0)Sleep(10);
	EndFlag = 1;
	while (EndFlag == 0)Sleep(10);
	ClearDrawScreen();
	DrawFormatString(500, 130, GetColor(128, 64, 255), ("Finish Game"));
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}