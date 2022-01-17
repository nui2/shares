#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

const static int GAME_Y = 405;    //「ゲーム」文字のy位置
const static int CONFIG_Y = 490;    //「設定」文字のy位置
static int MouseX, MouseY;
static char StrBuf[128], StrBuf2[32];
static int GHandle[3];
static int StringCr, BoxCr;
static int OldMouseOshita;
static int FontHandle;
static int SHandle[4];


typedef enum 
{
	eMenu_Config,        //ゲーム
	eMenu_Custom,    //設定

	eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Config;    //現在の選択状態(初期はゲーム選択中)

						//初期化
void Menu_Initialize() 
{
	//画像のロード
	GHandle[0] = LoadGraph("images/bg_menu.png");//画像のロード

	FontHandle = CreateFontToHandle(NULL, 50, 3);

	SHandle[0] = LoadSoundMem("sounds/bgm_menu.mp3");
	SHandle[1] = LoadSoundMem("sounds/menu.wav");
	SHandle[2] = LoadSoundMem("sounds/playerenter.wav");

	// マウスを表示状態にする
	SetMouseDispFlag(TRUE);

	// 白色の値を取得
	StringCr = GetColor(255, 255, 255);

	// 黒の値を取得
	BoxCr = GetColor(0, 0, 0);

	PlaySoundMem(SHandle[0], DX_PLAYTYPE_LOOP);
}

//終了処理
void Menu_Finalize() 
{
	int i;
	//画像の解放
	for (i = 0; i < 1; i++)
	{
		DeleteGraph(GHandle[i]);//画像の解放
	}
	for (i = 0; i < 3; i++)
	{
		DeleteSoundMem(SHandle[i]);
	}
}

//更新
void Menu_Update() 
{
	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);
	
	/*
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		switch (NowSelect) {//現在選択中の状態によって処理を分岐
		case eMenu_Config://ゲーム選択中なら
			SceneMgr_ChangeScene(eScene_Config);//シーンをゲーム画面に変更
			break;
		case eMenu_Custom://設定選択中なら
			SceneMgr_ChangeScene(eScene_Custom);//シーンを設定画面に変更
			break;
		}
	}
	*/
	if ((345 <= MouseX) && (MouseX <= 700) && (390 <= MouseY) && (MouseY <= 455)) {
		NowSelect = eMenu_Config;
		//PlaySoundMem(SHandle[1], DX_PLAYTYPE_BACK);
	}
	if (345 <= MouseX && MouseX <= 550 && 456 <= MouseY && MouseY <= 550) {
		NowSelect = eMenu_Custom;
		//PlaySoundMem(SHandle[1], DX_PLAYTYPE_BACK);
	}
	if ((345 <= MouseX) && (MouseX <= 700) && (390 <= MouseY) && (MouseY <= 455) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0) {
		PlaySoundMem(SHandle[2], DX_PLAYTYPE_NORMAL);
		SceneMgr_ChangeScene(eScene_Config);
	}
	if ((345 <= MouseX) && (MouseX <= 550) && (456 <= MouseY) && (MouseY <= 550) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0) {
		PlaySoundMem(SHandle[2], DX_PLAYTYPE_NORMAL);
		SceneMgr_ChangeScene(eScene_Custom);
	}
	// 表示する文字列を作成
	{
		lstrcpy(StrBuf, "座標 Ｘ"); // 文字列"座標 Ｘ"をStrBufにコピー	
		itoa(MouseX, StrBuf2, 10); // MouseXの値を文字列にしてStrBuf2に格納
		lstrcat(StrBuf, StrBuf2); // StrBufの内容にStrBuf2の内容を付け足す
		lstrcat(StrBuf, "　Ｙ "); // StrBufの内容に文字列"Ｙ"を付け足す
		itoa(MouseY, StrBuf2, 10); // MouseYの値を文字列にしてStrBuf2に格納
		lstrcat(StrBuf, StrBuf2); // StrBufの内容にStrBuf2の内容を付け足す
	}
	OldMouseOshita = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

//描画
void Menu_Draw() 
{
	DrawGraph(0, 0, GHandle[0], FALSE);// 画像を描画する
	int y = 0;
	switch (NowSelect) 
	{//現在の選択状態に従って処理を分岐
	case eMenu_Config://ゲーム選択中なら
		y = GAME_Y;    //ゲームの座標を格納
		break;
	case eMenu_Custom://設定選択中なら
		y = CONFIG_Y;    //設定の座標を格納
		break;
	}
	DrawStringToHandle(350, GAME_Y, "GAME",BoxCr, FontHandle);
	DrawStringToHandle(350, CONFIG_Y, "CONFIG", BoxCr, FontHandle);
	DrawStringToHandle(285, y, "→", BoxCr, FontHandle);
	// 画面左上の領域に黒い四角を描き前に描いてあった
	// 文字列を消す
	//DrawBox(0, 0, 200, 32, BoxCr, TRUE);
	// 座標文字列を描く
	//DrawString(0, 0, StrBuf, StringCr);
}
