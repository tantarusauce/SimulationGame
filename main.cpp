#include <iostream>
#include "DxLib.h"
volatile int EndFlag;

DWORD WINAPI MainThread(LPVOID)
{
	int floor;
	int i, j;
	floor = LoadGraph("./images/floor.png", TRUE);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			DrawRotaGraph(22 * j - i * 23 + 300, 12 * i + 12 * j + 150, 1, 0, floor, TRUE);
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