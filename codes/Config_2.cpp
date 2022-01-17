#include "Config.h"
#include "Config_2.h"
#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "math.h"

static const int  White = GetColor(255, 255, 255), Brack = GetColor(0, 0, 0);
static int MouseX, MouseY, OldMouseOshita, Count;
static int GHandle[3];
static int SHandle[12];
static int FontHandle0;
static int x_posi = 200, y_posi = 50, y_wide = 50;
static int player_num, cpu_num,card_set,open_num;
static int player_flag = -1;


typedef struct
{
	char name1[128];
	char name2[128];
} MenuElement_2_t;

MenuElement_2_t MenuElement[6] = {
	{ "1P 名前" ,"プレイヤー１"},
	{ "2P 名前" ,"プレイヤー２" },
	{ "3P 名前" ,"プレイヤー３" },
	{ "4P 名前" ,"プレイヤー４" },
	{ "", "ゲームスタート"},
	{ "","戻る" }
};

//初期化
void Config_2_Initialize()
{
	Config_reflect(&player_num, &cpu_num, &card_set,&open_num);
	//画像のロード
	GHandle[0] = LoadGraph("images/bg_config.png");//画像のロード
	GHandle[1] = LoadGraph("images/bg_config3.png");//画像のロード

	SHandle[1] = LoadSoundMem("sounds/カーソル移動2.mp3");
	SHandle[2] = LoadSoundMem("sounds/決定、ボタン押下40.mp3");

	// マウスを表示状態にする
	SetMouseDispFlag(TRUE);

	PlaySoundMem(SHandle[0], DX_PLAYTYPE_LOOP);
}

//終了処理
void Config_2_Finalize()
{
	int i;
	//画像の解放
	for (i = 0; i < 2; i++)
	{
		DeleteGraph(GHandle[i]);//画像の解放
	}
	for (i = 0; i < 3; i++)
	{
		DeleteSoundMem(SHandle[i]);
	}
}

//更新
void Config_2_Update()
{
	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	int i;
	for (i = 0; i < player_num + 2; i++)
	{
		if ( x_posi + 150 < MouseX && MouseX < x_posi + 270 && y_posi + y_wide * i < MouseY && MouseY < y_posi + 30 + y_wide * i && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			if (i == player_num)
			{
				SceneMgr_ChangeScene(eScene_Game);//シーンをゲームに変更
			}
			else if (i == player_num + 1)
			{
				SceneMgr_ChangeScene(eScene_Config);//シーンをメニューに変更
			}
			else
			{
				PlaySoundMem(SHandle[1], DX_PLAYTYPE_BACK);
				player_flag = i;
			}
		}
	}
	OldMouseOshita = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

//描画
void Config_2_Draw()
{
	int i, j;
	DrawGraph(0, 0, GHandle[0], FALSE);// 画像を描画する
	DrawGraph(0, 0, GHandle[1], TRUE);// 画像を描画する

	for (i = 0; i < player_num; i++)
	{
		DrawFormatString(x_posi, y_posi + y_wide * i, White, MenuElement[i].name1);
		if (player_flag != i)
		{
			DrawFormatString(x_posi + 150, y_posi + y_wide * i, White, MenuElement[i].name2);
		}
		DrawBox(x_posi + 150, y_posi + y_wide * i - 1, x_posi + 300, y_posi + y_wide * i + 19, White, FALSE);
	}
	for (j = 4; j <= 5; j++)
	{
		DrawFormatString(x_posi + 150, y_posi + y_wide * i, White, MenuElement[j].name2);
		i++;
	}
	if (player_flag != -1)
	{
		KeyInputString(x_posi + 150, y_posi + y_wide * player_flag, 31, MenuElement[player_flag].name2, FALSE);
		PlaySoundMem(SHandle[2], DX_PLAYTYPE_BACK);
		player_flag = -1;		
	}
}

void Config_2_reflect(char** player_name,int n)
{
	*player_name = MenuElement[n].name2;
}