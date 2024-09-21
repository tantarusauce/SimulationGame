#include <iostream>
#include "DxLib.h"
volatile int EndFlag;

void DrawScreen(int floor, int Lwall, int Rwall, int Box1, int Box2, int Box3, int LBox1, int LBox2, int LBox3, int LBox4, int map[10][10]) {
	int i, j;
	DrawRotaGraph(440, -62, 1, 0, Rwall, TRUE);
	DrawRotaGraph(200, -62, 1, 0, Lwall, TRUE);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			switch(map[i][j]) {
			case 0:
				DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150, 1, 0, floor, TRUE);
				break;
			case 1://左下を向いたボックス
				DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box1, TRUE);
				break;
			case 2://右下を向いたボックス
				DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box2, TRUE);
				break;
			case 3://右奥を向いたボックス
			case 4://左奥を向いたボックス
				DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 117, 1, 0, Box3, TRUE);
				break;
			case 5://左下を向いたラージボックス
				DrawRotaGraph(24 * j - i * 24 + 309, 12 * i + 12 * j + 121, 1, 0, LBox1, TRUE);
				break;
			case 6://右下を向いたラージボックス
				DrawRotaGraph(24 * j - i * 24 + 332, 12 * i + 12 * j + 122, 1, 0, LBox2, TRUE);
				break;
			case 7://左奥を向いたラージボックス
				DrawRotaGraph(24 * j - i * 24 + 343, 12 * i + 12 * j + 117, 1, 0, LBox3, TRUE);
				break;
			case 8://右奥を向いたラージボックス
				DrawRotaGraph(24 * j - i * 24 + 309, 12 * i + 12 * j + 117, 1, 0, LBox4, TRUE);
				break;
			}
		}
	}
}


DWORD WINAPI MainThread(LPVOID)
{
	//初期化
	int floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4;
	int map[10][10] = {0};
	map[6][7] = 8;

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

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawScreen(floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, map);

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