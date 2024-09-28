#include <iostream>
#include "DxLib.h"
volatile int EndFlag;

void DrawScreen(int floor, int Lwall, int Rwall, int Box1, int Box2, int Box3, int LBox1, int LBox2, int LBox3, int LBox4, int LBox5, int LBox6, int LBox7, int LBox8, int Box1f, int Box2f, int Box3f, int LBox1f, int LBox2f, int LBox3f, int LBox4f, int LBox5f, int LBox6f, int LBox7f, int LBox8f, int counter, int omi, int back, int select, int product_display, int object_round_left, int map[10][10], int scene, int selected[2], bool move) {
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
				}
			}
		}
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			switch (map[i][j]) {
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
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150 - 10, 1, 0, counter, TRUE);
				}
				else {
					DrawRotaGraph(24 * j - i * 24 + 320, 12 * i + 12 * j + 150, 1, 0, counter, TRUE);
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
	int floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, LBox5, LBox6, LBox7, LBox8, Box1f, Box2f, Box3f, LBox1f, LBox2f, LBox3f, LBox4f, LBox5f, LBox6f, LBox7f, LBox8f, counter, omi;
	int humanw1lb, humanw1rb, humanw1lf, humanw1rf, humanw2lb, humanw2rb, humanw2lf, humanw2rf, humanw3lb, humanw3rb, humanw3lf, humanw3rf, humanw4lb, humanw4rb, humanw4lf, humanw4rf, humanm1lb, humanm1rb, humanm1lf, humanm1rf, humanm2lb, humanm2rb, humanm2lf, humanm2rf, humanm3lb, humanm3rb, humanm3lf, humanm3rf;
	int select, back, product_display, object_round_left;
	int scene = 0;
	bool releaseKeyF = true, releaseKeyB = true, releaseKeySPACE = true, releaseKeyUP = true, releaseKeyDOWN = true, releaseKeyTurn = true;
	bool releaseKeyLEFT = true, releaseKeyRIGHT = true, releaseKeyI = true;
	bool sceneF = false, move = false;
	int map[10][10]{};
	int selected[2] = { 0, 0 };
	map[3][3] = 2;
	map[3][1] = 8;
	map[8][8] = 17;


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
	counter = LoadGraph("./images/counter_right_right.png", TRUE);
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

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawScreen(floor, Lwall, Rwall, Box1, Box2, Box3, LBox1, LBox2, LBox3, LBox4, LBox5, LBox6, LBox7, LBox8, Box1f, Box2f, Box3f, LBox1f, LBox2f, LBox3f, LBox4f, LBox5f, LBox6f, LBox7f, LBox8f, counter, omi, back, select, product_display, object_round_left, map, scene, selected, move);
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
							if (map[selected[0] - 1][selected[1] - 1] == 0 && map[selected[0] - 1][selected[1]] == 0 && ((map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8))) {

								map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = 0;
								map[selected[0]][selected[1] - 1] = 0;
								selected[0]--;
							}
							else if (map[selected[0] - 2][selected[1]] == 0 && (map[selected[0] - 1][selected[1]] == -2 || map[selected[0] - 1][selected[1]] == -3 || map[selected[0] - 1][selected[1]] == -6 || map[selected[0] - 1][selected[1]] == -7)) {
								if (selected[0] > 1) {
									map[selected[0] - 2][selected[1]] = map[selected[0] - 1][selected[1]];
									map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									selected[0]--;
								}
							}
							else if (map[selected[0] - 1][selected[1]] == 0 && ((map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 8)))) {
								map[selected[0] - 1][selected[1]] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = 0;
								selected[0]--;
							}
						}
					}
					releaseKeyUP = (CheckHitKey(KEY_INPUT_UP) == 0);
					if (CheckHitKey(KEY_INPUT_DOWN) && releaseKeyDOWN) {
						//下に移動(座標９より小さかったら動けるヨ)
						if (selected[0] < 9) {
							//移動先にものがなかったら
							if (map[selected[0] + 1][selected[1] - 1] == 0 && map[selected[0] + 1][selected[1]] == 0 && (map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8)) {
								map[selected[0] + 1][selected[1]] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = 0;
								map[selected[0]][selected[1] - 1] = 0;
								selected[0]++;
							}
							else if (map[selected[0] + 1][selected[1]] == 0 && (map[selected[0]][selected[1]] == 6 || map[selected[0]][selected[1]] == 7 || map[selected[0]][selected[1]] == 14 || map[selected[0]][selected[1]] == 15)) {
								map[selected[0] + 1][selected[1]] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = map[selected[0] - 1][selected[1]];
								map[selected[0] - 1][selected[1]] = 0;
								selected[0]++;
							}
							else if (map[selected[0] + 1][selected[1]] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 8))) {
								map[selected[0] + 1][selected[1]] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = 0;
								selected[0]++;
							}
						}
					}
					releaseKeyDOWN = (CheckHitKey(KEY_INPUT_DOWN) == 0);
					if (CheckHitKey(KEY_INPUT_RIGHT) && releaseKeyRIGHT) {
						//右に移動
						if (selected[1] < 9) {
							//移動先にものがなかったら
							if ((map[selected[0] - 1][selected[1] + 1] == 0) && map[selected[0]][selected[1] + 1] == 0 && (map[selected[0] - 1][selected[1]] == -2 || map[selected[0] - 1][selected[1]] == -3 || map[selected[0] - 1][selected[1]] == -6 || map[selected[0] - 1][selected[1]] == -7)) {
								map[selected[0]][selected[1] + 1] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = 0;
								map[selected[0] - 1][selected[1]] = 0;
								selected[1]++;
							}
							else if (map[selected[0]][selected[1] + 1] == 0 && (map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8)) {
								map[selected[0]][selected[1] + 1] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = map[selected[0]][selected[1] - 1];
								map[selected[0]][selected[1] - 1] = 0;
								selected[1]++;
							}
							else if (map[selected[0]][selected[1] + 1] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 8))) {
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
							if (map[selected[0] - 1][selected[1] - 1] == 0 && map[selected[0]][selected[1] - 1] == 0 && ((map[selected[0] - 1][selected[1]] == -2 || map[selected[0] - 1][selected[1]] == -3 || map[selected[0] - 1][selected[1]] == -6 || map[selected[0] - 1][selected[1]] == -7))) {
								map[selected[0]][selected[1] - 1] = map[selected[0]][selected[1]];
								map[selected[0]][selected[1]] = 0;
								map[selected[0] - 1][selected[1]] = 0;
								selected[1]--;

							}
							else if (map[selected[0]][selected[1] - 2] == 0 && ((map[selected[0]][selected[1] - 1] == -1 || map[selected[0]][selected[1] - 1] == -4 || map[selected[0]][selected[1] - 1] == -5 || map[selected[0]][selected[1] - 1] == -8))) {
								if (selected[1] > 1) {
									map[selected[0]][selected[1] - 2] = map[selected[0]][selected[1] - 1];
									map[selected[0]][selected[1] - 1] = map[selected[0]][selected[1]];
									map[selected[0]][selected[1]] = 0;
									selected[1]--;
								}
							}
							else if (map[selected[0]][selected[1] - 1] == 0 && (map[selected[0]][selected[1]] <= 4 || (map[selected[0]][selected[1]] <= 12 && map[selected[0]][selected[1]] >= 8))) {
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
							if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0)) {
								currentObject = 6;
								map[selected[0]][selected[1] - 1] = 0;
								map[selected[0] - 1][selected[1]] = -1;
								std::cout << map;
								break; // ラージボックス左下→右下
							}
						case 13:
							if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0)) {
								currentObject = 14;
								map[selected[0]][selected[1] - 1] = 0;
								map[selected[0] - 1][selected[1]] = -5;
								std::cout << map;
								break; // ラージボックス左下→右下
							}
						case 6:
							if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0)) {
								currentObject = 8;
								map[selected[0] - 1][selected[1]] = 0;
								map[selected[0]][selected[1] - 1] = -2;
								break; // ラージボックス右下→右奥
							}
						case 14:
							if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0)) {
								currentObject = 16;
								map[selected[0] - 1][selected[1]] = 0;
								map[selected[0]][selected[1] - 1] = -6;
								break; // ラージボックス右下→右奥
							}
						case 7:
							if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0)) {
								currentObject = 5;
								map[selected[0] - 1][selected[1]] = 0;
								map[selected[0]][selected[1] - 1] = -3;
								break; // ラージボックス左奥→左下
							}
						case 15:
							if ((selected[1] - 1 > -1) && (map[selected[0]][selected[1] - 1] == 0)) {
								currentObject = 13;
								map[selected[0] - 1][selected[1]] = 0;
								map[selected[0]][selected[1] - 1] = -7;
								break; // ラージボックス左奥→左下
							}
						case 8:
							if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0)) {
								currentObject = 7;
								map[selected[0]][selected[1] - 1] = 0;
								map[selected[0] - 1][selected[1]] = -4;
								break; // ラージボックス右奥→左奥
							}
						case 16:
							if ((selected[0] - 1 > -1) && (map[selected[0] - 1][selected[1]] == 0)) {
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