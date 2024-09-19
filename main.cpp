#include <iostream>
#include "DxLib.h"
volatile int EndFlag;

int abs(int a) {
	if (a > 0) {
		return a;
	}
	else {
		return -a;
	}
}

DWORD WINAPI MainThread(LPVOID)
{
	int floor;
	int i, j;
	floor = LoadGraph("./images/floor.png", TRUE);
	for (i = -8; i < 8; i++) {
		for (j = -8; j < 8; j++) {
			if (7 - abs(i) > abs(j)) {
				DrawRotaGraph(20 * j + 150, 30 * i + 150, 1, 0, floor, TRUE);
			}
		}
	}
	
	return 0;
}

// プログラムは WinMain から始まります
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