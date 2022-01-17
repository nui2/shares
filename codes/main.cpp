#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"

#define SCREEN_SIZE_X 1136
#define SCREEN_SIZE_Y 639

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	int WindowFullSize;
	int WindowPosX;
	int WindowPosY;
	int DesktopSizeX;
	int DesktopSizeY;

	SetMainWindowText("Toaru_BoardGame");
	SetGraphMode(1136, 639, 32);
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0) return -1;

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	GetDefaultState(&DesktopSizeX, &DesktopSizeY, NULL);

	// フルスクリーンモードかどうかのフラグを倒しておく
	WindowFullSize = FALSE;

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{//画面更新 & メッセージ処理 & 画面消去
		
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
		{
			if (WindowFullSize)
			{
				// フルスクリーンモードだった場合は通常モードに変更する
				WindowFullSize = FALSE;

				// ウインドウスタイルを標準に変更
				SetWindowStyleMode(0);

				// ウインドウサイズを 640x480 に変更
				SetWindowSize(SCREEN_SIZE_X, SCREEN_SIZE_Y);

				// ウインドウを最大化前の座標に移動
				SetWindowPosition(WindowPosX, WindowPosY);
			}
			else
			{
				// 通常モードだった場合はフルスクリーンモードに変更する
				WindowFullSize = TRUE;

				// 現在のウインドウの位置を取得しておく
				GetWindowPosition(&WindowPosX, &WindowPosY);

				// ウインドウスタイルを枠なしに変更
				SetWindowStyleMode(4);

				// ウインドウのサイズをデスクトップと同じにする
				SetWindowSize(DesktopSizeX, DesktopSizeY);

				// ウインドウの位置を画面左上に変更
				SetWindowPosition(0, 0);
			}

		}
		Keyboard_Update();    //キーボードの更新

		SceneMgr_Update();  //更新
		SceneMgr_Draw();    //描画
	}
	
	SceneMgr_Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}