#include <iostream>
#include "DxLib.h"
volatile int EndFlag;

void DrawScreen(int floor, int Lwall, int Rwall, int Box1, int Box2, int Box3, int LBox1, int LBox2, int LBox3, int LBox4, int omi, int back, int select, int map[10][10], int scene, int selected[2], bool move) {
	int i, j;
	DrawRotaGraph(440, -62, 1, 0, Rwall, TRUE);
	DrawRotaGraph(200, -62, 1, 0, Lwall, TRUE);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			switch(map[i][j]) {
			case 0:
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150 - 10, 1, 0, floor, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150, 1, 0, floor, TRUE);
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
					DrawRotaGraph(24 * j - i * 24 + 310, 12 * i + 12 * j + 123 - 10, 1, 0, LBox1, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 310, 12 * i + 12 * j + 123, 1, 0, LBox1, TRUE);
				}
				map[i][j - 1] = -1;
				break;
			case 6://右下を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 332, 12 * i + 12 * j + 122 - 10, 1, 0, LBox2, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 332, 12 * i + 12 * j + 122, 1, 0, LBox2, TRUE);
				}
				map[i - 1][j] = -2;
				break;
			case 7://左奥を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 343, 12 * i + 12 * j + 117 - 10, 1, 0, LBox3, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 343, 12 * i + 12 * j + 117, 1, 0, LBox3, TRUE);
				}
				map[i - 1][j] = -2;
				break;
			case 8://右奥を向いたラージボックス
				if (selected[0] == i && selected[1] == j && scene == 1 && move) {
					DrawRotaGraph(24 * j - i * 24 + 309, 12 * i + 12 * j + 117 - 10, 1, 0, LBox4, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 309, 12 * i + 12 * j + 117, 1, 0, LBox4, TRUE);
				}
				map[i][j - 1] = -1;
				break;
			}
			if(scene == 1)DrawRotaGraph(24 * selected[1] - selected[0] * 24 + 320, 12 * selected[0] + 12 * selected[1] + 150, 1, 0, select, TRUE);
			


		}
	}
	if (scene == 0) {
		DrawRotaGraph(100, 400, 0.5, 0, omi, TRUE);
	}
	else if(scene == 1) {
		DrawRotaGraph(50, 30, 1, 0, back, TRUE);
	}
}


DWORD WINAPI MainThread(LPVOID)
{
	//初期化
	int floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, omi, select, back;
	int scene = 0;
	bool releaseKeyF = true, releaseKeyB = true, releaseKeySPACE = true, releaseKeyUP = true, releaseKeyDOWN = true;
	bool releaseKeyLEFT = true, releaseKeyRIGHT = true;
	bool sceneF = false, move = false;
	int map[10][10]{};
	int selected[2] = { 0, 0 };
	map[5][2] = 6;
	map[3][1] = 2;
	

	floor = LoadGraph("./images/floor.png", TRUE);
	Lwall = LoadGraph("./images/wallleft.png", TRUE);
	Rwall = LoadGraph("./images/wallright.png", TRUE);
	Box1 = LoadGraph("./images/miniShelfLeft.png", TRUE);
	Box2 = LoadGraph("./images/miniShelfRight.png", TRUE);
	Box3 = LoadGraph("./images/miniShelfBack.png", TRUE);
	LBox1 = LoadGraph("./images/miniLargeShelfLeft.png", TRUE);
	LBox2 = LoadGraph("./images/miniLargeShelfRight.png", TRUE);
	LBox3 = LoadGraph("./images/miniLargeShelfBackLeft.png", TRUE);
	LBox4 = LoadGraph("./images/miniLargeShelfBackRight.png", TRUE);
	omi = LoadGraph("./images/object_move_icon.png", TRUE);
	select = LoadGraph("./images/selected.png", TRUE);
	back = LoadGraph("./images/back.png", TRUE);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawScreen(floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, omi, back, select, map, scene, selected, move);
		if (CheckHitKey(KEY_INPUT_F) && releaseKeyF) {
			scene = 1;
		}
		if (CheckHitKey(KEY_INPUT_B) && releaseKeyB && scene == 1) {
			scene = 0;
			move = false;
		}
		if (scene == 1) {
			//オブジェクト移動画面
			if (CheckHitKey(KEY_INPUT_SPACE) && releaseKeySPACE) {
				move = move ? false : true;
			}
			if (move) {
				if (map[selected[0]][selected[1]] != 0) {
					if (map[selected[0]][selected[1]] == -1) {
						selected[1]++;
					}
					if (map[selected[0]][selected[1]] == -2) {
						selected[0]++;
					}
				//オブジェクト移動
				if (CheckHitKey(KEY_INPUT_UP) && releaseKeyUP) {
					//上に移動
					if (selected[0] > 0) {
						//移動先にものがなかったら
						if ((map[selected[0] - 1][selected[1] - 1] == 0) && (map[selected[0] - 1][selected[1]] == 0) && map[selected[0]][selected[1] - 1] == -1) {
							map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
							map[selected[0]][selected[1]] = 0;
							selected[0]--;
						}
						else if (map[selected[0] - 2][selected[1]] == 0 && map[selected[0] - 1][selected[1]] == -2) {
							map[selected[0] - 2][selected[1]] = map[selected[0] - 1][selected[1]];
							map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
							map[selected[0]][selected[1]] = 0;
							selected[0]--;
						}else if(map[selected[0] - 1][selected[1]] == 0 && map[selected[0]][selected[1]] <= 4) {
							map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
							map[selected[0]][selected[1]] = 0;
							selected[0]--;
						}
					}
				}
				releaseKeyUP = (CheckHitKey(KEY_INPUT_UP) == 0);
				if (CheckHitKey(KEY_INPUT_DOWN) && releaseKeyDOWN) {
					//下に移動

				}
				releaseKeyDOWN = (CheckHitKey(KEY_INPUT_DOWN) == 0);
				if (CheckHitKey(KEY_INPUT_RIGHT) && releaseKeyRIGHT) {
					//右に移動

				}
				releaseKeyRIGHT = (CheckHitKey(KEY_INPUT_RIGHT) == 0);
				if (CheckHitKey(KEY_INPUT_LEFT) && releaseKeyLEFT) {
					//左に移動

				}
				releaseKeyLEFT = (CheckHitKey(KEY_INPUT_LEFT) == 0);
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