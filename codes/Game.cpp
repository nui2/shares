#include "Game.h"
#include "Config.h"
#include "Config_2.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "math.h"
#include "time.h"

 
                   //各種ハンドル格納用変数
static int FileHandle;  //excleハンドル格納用変数数
static int FileHandle1;  //excleハンドル格納用変数
static int FontHandle;
static int FontHandle2;
static int FontHandle3;
static int facilitybox_ImageHandle[4];
static int LandMark_ImageHandle[10];
static int LandMarkback_ImageHandle[10];
static int LandMark_thumbnail_ImageHandle[10];
static int LandMarkback_thumbnail_ImageHandle[10];
static int Facility_ImageHandle[100];
static int Facility_thumbnail_ImageHandle[100];
static int GHandle[30];
static int GHandleType[12];
static int SHandle[12];


						 //変数いろいろ
static int MouseX, MouseY,OldMouseOshita;  //マウス関連
static int card_set[4], open_num[3],number_of_player,number_of_cpu;  //設定関連
static int flagX = -1, flagY = -1, now_select;  //選択関連
static int boxX, boxY,box_flag,box_erase_flag;  //窓関連
static int flagX2 = -1, flagY2 = -1, now_select2,change_flag = 0;  //選択関連
static int boxX2, boxY2, box_flag2, box_erase_flag2,imposible_flag,rebuild_flag;  //窓関連
static int turn, now_turn;  //ターン関連
static int park_flag;  //
static int dice_result[2],dice_result_copy[2]; //ダイス関連
static int phase; //
static int maguro; //
static int win_flag = -1;
static const int have_box_x = 10;
static const int have_box_y = 5;
static int have_box[5][10][4] = { 0 };
static int deck[3][200] = {-1}, deckn[3]; //デッキ
static int supply[3][6], supplyn[3][6];  //サプライ
static const int box_y_wide = 21;
static const int card_info_x1 = 8, card_info_x2 = 101, log_x1 = 104, log_x2 = 147, config_x1 = 150, config_x2 = 194, left_box_y1 = 272, left_box_y2 = 272 + box_y_wide;
static int left_box_flag = 0;
static const int card_y_wide = 89;
static const int card_x_wide = 58;
static const int card2_y_wide = 241;
static const int card2_x_wide = 157;
static const int card_x_wide2 = card_x_wide + 20;
static const int card_y_wide2 = card_y_wide + 10;
static const int button_x = 986;
static const int button_y = 489;
static const int button_x_wide = 150;
static const int button_y_wide = 50;
static const int button_x_wide2 = button_x_wide + 20;
static const int button_y_wide2 = button_y_wide + 20;
static const int card_x = 295;
static const int card_y = 20;
static int select_player = 0;
static const int player_info_y = 1;
static const int player_info_y_wide = 122;
static const int facility_x = 220;
static const int facility_y = 360;
static const int facility_num = 13;
static int facility_view_flag = 0;
static const int select_card_x = 215;
static const int select_card_y = 30;
static int target_get, target_send,target_player;
static const int setmin[4] = { 0,15 ,25,39 };
static const int setMAX[4] = { 14,24 ,38,53 };
static const int land_setmin[4] = { 0, 4,0,0 };
static const int land_setMAX[4] = { 3, 6,0,0 };
static const int left_message_x = 10;
static const int left_message_y = 300;
static int land_set_num = 0;
static int IT_mode[4] = { 0 };//1:手動,2:自動乗せる,3:自動乗せない
static int effect_sort[4] = { 0 };//1:手動,2:自動
static int ignition_order_flag;
static int ignition_flag = 0;
static int s_count;
static int ignition_num[8] = {0};
static int ignition_type_num[8] = { 0 };
static int order_box[50];
static int go_flag[8] = { 0 };
static int gyosu;
static int begin[20];
static int end[20];
static const int width = 175;
static int message_x = 10;
static int message_y = 320;
static char message_log[5][20][256];
static int message_num[5] = {0};
static int select_log = 0;
static int scroll_log = 0;
static double ignition_ax = 0;
static const double ignition_x1 = 440;
static const double ignition_y1 = 150;
static const double ignition_x2 = ignition_x1 + card2_x_wide;
static const double ignition_y2 = ignition_y1 + card2_y_wide;
static int mask_flag = 0;
static int phase_log;
static int Disposal_box[100];
static int Disposal_select[3][6];
static int Disposal_count;
static int Disposal_box_num = 0;
static int number_of_disposal = 0;
static char DiceDisplay[256];
static int display_time = 0;
static int display_mode = 0;
static int build_count = 1;
static int reform_flag = 0;
static int cost_buf;
static int have_card_type_num[4][12] = {0};
static char type_name[12][256] = {"草花","牧畜","商店","飲食","歯車","製作所" ,"フルーツ","大施設","漁業","オフィス","宗教" };

//static const int gazounashi = 54;
static const int gazounashi = 0;
static int card_syurui = 54;

//色準備
static const int White = GetColor(255, 255, 255);//白
static const int Brack = GetColor(0, 0, 0);//黒
static const int Red = GetColor(255, 0, 0);// 赤
static const int Yellow = GetColor(255, 255, 0);// 黄
static const int Blue = GetColor(0, 0, 255);// 青
static const int Green = GetColor(0, 255, 0);// 緑
static const int Silver = GetColor(192, 192, 192);// 銀
static const int Gray = GetColor(80, 80, 80);// グレー
static const int DarkViolet = GetColor(148, 00, 208);//紫
static const int Type_Color[5] = { Gray,Green,Red,Blue, DarkViolet };

			//関数プロトタイプ宣言
static void message_initialize();//
static void shuffle(int ary[], int size);  //シャッフル関数
static void deck_build(int t);  //デッキ構築関数
static void supply_initialize();  //サプライ初期化関数
static void supply_reload();  //サプライ補充関数
static void supply_build();  //サプライ建設関数
static void landmark_build();  //ランドマーク建設関数
static void card_sort();
static void dice_check(int d);
static void dice_roll(int num);
static void turn_update();
static void ignition_card(int card, int player);
static void income_processing(int card, int player,int income);
static void card_effect(int card,int player);
static int select_card(int x, int y);  //カード選択関数
static int select_card2(int x, int y,int player);  //カード選択関数
static int select_facility(int x, int y);
static int select_facility2(int x, int y,int player);
static int select_landmark(int x, int y);
static void win();
static void build_phase();
static void Box_Draw_Facility(const char txt1[], const char txt2[]);
static void Box_Draw_LandMark(const char txt1[], const char txt2[]);
static void Button_Draw(const char txt1[], const char txt2[],const char txt3[]);
static void target_select_Draw(int player);
static void Facility_View_initialize();
static void Facility_View();
static void dice_phase();
static void ignition_initialize();
static void ignition_phase();
static void ignition_order_select();
static void ignition_display_Draw();
static void port_use();
static void tower_use();
static void IT_use();
static void business_initialize();
static void business_use();
static void TV_use();
static void remodeling_select();
static void remodeling_use(); 
static void mover_initialize();
static void mover_use();
static void cleaning_initialize();
static void cleaning_use();
static void Exhibition_initialize();
static void Exhibition_use();
static void end_phase();
static void win_phase();
static void GradX_RGB(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2);
static void butsugiri(char moji[], int wide, int FontHandle, int *begin, int *end, int *gyosu);
static void KaigyoDraw(int x, int y, int gyosu, int gyokan, int Color, int FontHandle, char moji[], int begin[], int end[]);
static void landmark_ignition_display(int id);
static void Disposal_supply_initialize(int Disposal_num);
static void Disposal_supply(int Disposal_num);
static int facility_disposal();
static void reform_use();
static void extra_build(int Expenses,int player);
static void extra_build_phase(int Expenses, int player);
static void food_stand_initialize(int player);
static void food_stand_use();
static void Land_speculator_initialize();
static void Land_speculator_use();
static void theme_park_initialize();
static void theme_park_use();
static void general_contractor_initialize();
static void general_contractor_use();


             //構造体色々
typedef struct {
	int id;//カード番号
	char name[256];//名前
	int cost;//コスト
	int income;//収入
	int dice;//出目
	char dice_display[10];//表示出目
	int type;//種類(色)
	int conditions;//条件
	int ctgry;//カテゴリー(飲食店,草花等)
	char c_txt[256];//テキスト
}Card_t;
Card_t m_Supply[100];
Card_t m_Landmark[100];

char gomi[2][8][256];

typedef struct {
	int card;//カード番号
	int Holiday_flag;//休業フラグ
	int flag;//フラグ予備
}Facility_t;
Facility_t m_tmp;
Facility_t const m_default_Facility = { -1, 0, 0};

typedef struct {
	char* name;//名前
	int coin;//コイン
	Facility_t m_Facility[100];//施設
	int facility_Num;//施設数
	int landmark[10];//ランドマーク
	int landmark_Num;//ランドマーク数
	int color;//プレイヤーカラー
	int IT;//ITベンチャーカウンター
}Player_t;
Player_t m_Player[4];
Player_t m_default_Player = { "あ",3,{{0,0,0},{1,0,0}},2,{0,0,0,0,1,0,0},Brack,0 };

typedef struct {
	char name[256];//名前
	int first;//最初
	int last;//最後
}Card_set;

Card_set m_Standard = { "街コロ",0,14 };
Card_set m_Plus = { "街コロ+",15,24 };
Card_set m_Sharp = { "街コロ#",25,38 };
Card_set m_original = { "オリジナル",39,39 };

typedef struct {
	int card;//カード番号
	int player;//プレイヤー
}ignition_t;
ignition_t m_ignition[8][50];
ignition_t const m_default_ignition = {-1,-1};



//初期化
void Game_Initialize() 
{
	int i,j;
	static char file_name[256];

	win_flag = -1;

	srand(time(NULL)); // 現在時刻の情報で初期化

	FontHandle = CreateFontToHandle(NULL, 16, 8);
	FontHandle2 = CreateFontToHandle(NULL, 26, 10);
	FontHandle3 = CreateFontToHandle(NULL, 36, 16);

	GHandle[0] = LoadGraph("images/bg_game.jpg");//背景
	GHandle[1] = LoadGraph("images/bg_game2.jpg");//背景予備
	GHandle[2] = LoadGraph("images/mask2.png");//起動時マスク
	GHandle[3] = LoadGraph("images/Cards/card.png");//スリーブ
	GHandle[4] = LoadGraph("images/thumbnails/card.png");//スリーブ小
	GHandle[5] = LoadGraph("images/coin.png");//コイン
	GHandle[6] = LoadGraph("images/Supplybox.png");//サプライ枠
	GHandle[7] = LoadGraph("images/message1.png");//メッセージ枠
	GHandle[8] = LoadGraph("images/back.png");//選択効果時背景

	for (i = 1; i <= 11; i++)
	{    //画像ファイルの個数分
		sprintf_s(file_name, "images/type%d.png", i);
		GHandleType[i] = LoadGraph(file_name);
	}

	for (i = 0; i < 4; i++)
	{    //画像ファイルの個数分
		sprintf_s(file_name, "images/facilitybox%d.png", i);
		facilitybox_ImageHandle[i] = LoadGraph(file_name);
	}
	for (i = 0; i < 7; i++)
	{    //画像ファイルの個数分
		sprintf_s(file_name, "images/Cards/LandMark%d.png", i);
		LandMark_ImageHandle[i] = LoadGraph(file_name);
		sprintf_s(file_name, "images/thumbnails/LandMark%d.png", i);
		LandMark_thumbnail_ImageHandle[i] = LoadGraph(file_name);
		sprintf_s(file_name, "images/Cards/LandMarkback%d.png", i);
		LandMarkback_ImageHandle[i] = LoadGraph(file_name);
		sprintf_s(file_name, "images/thumbnails/LandMarkback%d.png", i);
		LandMarkback_thumbnail_ImageHandle[i] = LoadGraph(file_name);
	}
	for (i = 0; i < gazounashi; i++)
	{    //画像ファイルの個数分
		sprintf_s(file_name, "images/Cards/Facility%d.png", i);
		Facility_ImageHandle[i] = LoadGraph(file_name);
		sprintf_s(file_name, "images/thumbnails/Facility%d.png", i);
		Facility_thumbnail_ImageHandle[i] = LoadGraph(file_name);
	}

	SHandle[0] = LoadSoundMem("sounds/刀で斬る5.mp3");//施設起動時
	SHandle[1] = LoadSoundMem("sounds/石が転がる.mp3");//ダイスロール
	SHandle[2] = LoadSoundMem("sounds/レジスターで精算.mp3");//建設時
	SHandle[3] = LoadSoundMem("sounds/カードをめくる.mp3");//サプライ補充
	SHandle[4] = LoadSoundMem("sounds/カードをきる2.mp3");//シャッフル
	SHandle[5] = LoadSoundMem("sounds/爆発1.mp3");//カード廃棄
	SHandle[6] = LoadSoundMem("sounds/カーソル移動2.mp3");//メニュー
	SHandle[7] = LoadSoundMem("sounds/カーソル移動5.mp3");//プレイヤー
	SHandle[8] = LoadSoundMem("sounds/ニュースタイトル表示2.mp3");//ターン切り替え
	SHandle[9] = LoadSoundMem("sounds/bgm_game.mp3");//BGM
	SHandle[10] = LoadSoundMem("sounds/bgm_win.mp3");//勝利BGM
	PlaySoundMem(SHandle[9], DX_PLAYTYPE_LOOP);

    //カードセット設定 1=初期, 2=+, 3=#
	Config_reflect(&number_of_player, &number_of_cpu,card_set,open_num);

	//ファイルを読み込む
	FileHandle = FileRead_open("dates/supply.csv");
	FileHandle1 = FileRead_open("dates/landmark.csv");
	for (i = 0; i < 2; i++)
	{//二回繰り返す
		FileRead_scanf(FileHandle, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",gomi[i][0], gomi[i][1], gomi[i][2], gomi[i][3], gomi[i][4], gomi[i][5], gomi[i][6], gomi[i][7], gomi[i][8], gomi[i][9]);//読み込む
	}

	int n = card_syurui;

	for (i = 0; i < n; i++) 
	{//二行目から2+n行目まで読み取る
		FileRead_scanf(FileHandle, "%d,%[^,],%d,%d,%d,%[^,],%d,%d,%d,%s", &m_Supply[i].id, m_Supply[i].name, &m_Supply[i].cost, &m_Supply[i].income, &m_Supply[i].dice, m_Supply[i].dice_display, &m_Supply[i].type, &m_Supply[i].conditions, &m_Supply[i].ctgry, m_Supply[i].c_txt);//読み込み
	}
	int n_2 = 7;//データの数
	for (i = 0; i < n_2; i++)
	{//二行目から2+n行目まで読み取る
		FileRead_scanf(FileHandle1, "%[^,],%d,%s", m_Landmark[i].name, &m_Landmark[i].cost,m_Landmark[i].c_txt);//読み込み
	}
	//採用ランドマーク数計算
	land_set_num = 0;
	for (i = 0; i < 4; i++)
	{
		if (card_set[i] == 1 && land_setMAX[i] != land_setmin[i])
		{
			land_set_num += land_setMAX[i] - land_setmin[i] + 1;
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < deckn[i]; j++)
		{
			deck[i][j] = -1;
		}
		deckn[i] = 0;
	}
	//デッキ構築
	for (i = 0; i < 4; i++)
	{
		if (card_set[i] == 1)
		{
			deck_build(i);
		}
	}

	//デッキシャッフル
	for (i = 0; i < 3; i++)
	{
		shuffle(deck[i], deckn[i]);
	}

	//サプライ初期化
	supply_initialize();

	//box初期化
	box_flag = 0;
	box_flag2 = 0;
	imposible_flag = 0;

	m_Player[0].color = Red;
	m_Player[1].color = Blue;
	m_Player[2].color = Yellow;
	m_Player[3].color = Green;

	turn = 0;
	phase = 1;

	//メッセージ初期化
	message_initialize();
}

//終了処理
void Game_Finalize() 
{
	int i;
	for (i = 0; i < 7; i++) 
	{
		DeleteGraph(GHandle[i]);//画像の解放
	}
	for (i = 1; i <= 11; i++)
	{
		DeleteGraph(GHandleType[i]);//画像の解放
	}
	for (i = 0; i < 7; i++) 
	{
		DeleteGraph(LandMark_ImageHandle[i]);//画像の解放
		DeleteGraph(LandMark_thumbnail_ImageHandle[i]);//画像の解放
	}
	for (i = 0; i < gazounashi; i++)
	{
		DeleteGraph(Facility_ImageHandle[i]);//画像の解放
		DeleteGraph(Facility_thumbnail_ImageHandle[i]);//画像の解放
	}
	for (i = 0; i < 11; i++)
	{
		DeleteSoundMem(SHandle[i]);
	}
	DeleteFontToHandle(FontHandle);//フォントデータの削除
	DeleteFontToHandle(FontHandle2);//フォントデータの削除
	DeleteFontToHandle(FontHandle3);//フォントデータの削除
	FileRead_close(FileHandle);//ファイルの削除
	FileRead_close(FileHandle1);//ファイルの削除
}

//更新
void Game_Update() 
{
	int i, j, k, l,m,same_flag;

	//ターンプレイヤー
	now_turn = turn % number_of_player;

	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	//サプライ補充
	supply_reload();

	//場整理
	card_sort();

	//勝利云々
	if(win_flag == -1)win();


	//カードセレクト
	//サプライ
	if (select_card(MouseX, MouseY) != -1 && box_flag == 0 && phase != 35 && phase != 14 && phase != 4 && phase != 38 && phase != 40 && phase != 46 && phase != 47 && facility_view_flag != 1)
	{
		now_select = select_card(MouseX, MouseY);
		change_flag = 1;
		butsugiri(m_Supply[now_select].c_txt, width, FontHandle, begin, end, &gyosu);
	}
	//施設
	if (select_facility(MouseX, MouseY) != -1 && box_flag == 0 && phase != 35 && phase != 14 && phase != 4 && phase != 38 && phase != 40 && phase != 46 && phase != 47 && facility_view_flag != 1)
	{
		now_select = select_facility(MouseX, MouseY);
		change_flag = 1;
		butsugiri(m_Supply[now_select].c_txt, width, FontHandle, begin, end, &gyosu);
	}
	//ランドマーク
	if (select_landmark(MouseX, MouseY) != -1 && box_flag2 == 0 && phase != 35 && phase != 14 && phase != 4 && phase != 40 && phase != 46 && phase != 47)
	{
		now_select2 = select_landmark(MouseX, MouseY);
		change_flag = 2;
		butsugiri(m_Landmark[now_select2].c_txt, width, FontHandle, begin, end, &gyosu);
	}

	//メッセージ消去
	if (imposible_flag == 1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)imposible_flag = 0;
	if (rebuild_flag == 1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)rebuild_flag = 0;
	if (facility_view_flag == 1)
	{
		if (select_facility2(MouseX, MouseY,select_player) != -1)
		{
			now_select = select_facility2(MouseX, MouseY,select_player);
			change_flag = 1;
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)facility_view_flag = 0;
	}
	if (ignition_ax == 0)
	{
		//フェイズ処理
		switch (phase) {
		case 1:
			dice_phase();//サイコロ振る
			break;
		case 2:
			build_phase();//建設する
			break;
		case 3:
			tower_use();//電波塔使うか否か
			break;
		case 4:
			ignition_order_select();//効果解決
			break;
		case 5:
			port_use();//港使うか否か
			break;
		case 6:
			win_phase();//
			break;
		case 7:
			end_phase();//エンドフェイズ
			break;
		case 13:
			TV_use();//テレビ発動時
			break;
		case 14:
			business_use();//ビジネスセンター
			break;
		case 15:
			Disposal_supply(number_of_disposal);//
			break;
		case 27:
			remodeling_select();//改装屋
			break;
		case 32:
			mover_use();//引っ越し業者発動時
			break;
		case 35:
			cleaning_use();//清掃業発動時
			break;
		case 36:
			IT_use();//ITベンチャーにコイン乗せるか否か
			break;
		case 38:
			Exhibition_use();//
			break;
		case 40:
			reform_use(); 
			break;
		case 44:
			food_stand_use();
			break;
		case 46:
			Land_speculator_use();
			break;
		case 47:
			theme_park_use();
			break;
		case 48:
			general_contractor_use();
			break;
		default:
			break;
		}
	}
	//プレイヤー選択
	for (i = 0; i < number_of_player; i++)
	{
		if (button_x < MouseX && MouseX < button_x + button_x_wide && player_info_y + player_info_y_wide * i < MouseY && MouseY < player_info_y + player_info_y_wide * (i + 1) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			PlaySoundMem(SHandle[7], DX_PLAYTYPE_BACK);
			select_player = i;
		}
	}

	if (card_info_x1 < MouseX && MouseX < card_info_x2 && left_box_y1 < MouseY && MouseY < left_box_y2 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		left_box_flag = 0;
		PlaySoundMem(SHandle[6], DX_PLAYTYPE_BACK);
	}
	if (log_x1 < MouseX && MouseX < log_x2 && left_box_y1 < MouseY && MouseY < left_box_y2 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		left_box_flag = 1;
		PlaySoundMem(SHandle[6], DX_PLAYTYPE_BACK);
	}
	if (config_x1 < MouseX && MouseX < config_x2 && left_box_y1 < MouseY && MouseY < left_box_y2 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		left_box_flag = 2;
		PlaySoundMem(SHandle[6], DX_PLAYTYPE_BACK);
	}
	switch (left_box_flag) {
	case 0:
		break;	
	case 1:
		if (turn - select_log != 0 && select_log != 4 && 10 < MouseX && MouseX < 90 && 300 < MouseY && MouseY < 320 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			select_log++;
			scroll_log = 0;
		}
		if (select_log != 0 && 110 < MouseX && MouseX < 190 && 300 < MouseY && MouseY < 320 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			select_log--;
			scroll_log = 0;
		}
		if (message_y >= 580 && 50 < MouseX && MouseX < 70 && 600 < MouseY && MouseY < 620 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)scroll_log++;
		if (scroll_log > 0 && 150 < MouseX && MouseX < 170 && 600 < MouseY && MouseY < 620 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)scroll_log--;
		break;
	case 2:
		for (i = 0; i < 2; i++)
		{
			if (left_message_x < MouseX && MouseX < left_message_x + 100 && left_message_y  + 20 * i < MouseY && MouseY < left_message_y + 20 * (i + 1) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
			{
				IT_mode[select_player] = (IT_mode[select_player] == i + 1)?(0) :(i + 1);
			}
		}
		if (left_message_x < MouseX && MouseX < left_message_x + 100 && left_message_y + 40 < MouseY && MouseY < left_message_y + 60 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			effect_sort[select_player] = (effect_sort[select_player] == 1) ? (0) : (1);
		}
		break;
	}
	//施設表示大
	if (860 < MouseX && MouseX < 980 && 280 < MouseY && MouseY < 320 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && phase != 35 && phase != 14 && phase != 4 && phase != 38)
	{
		PlaySoundMem(SHandle[6], DX_PLAYTYPE_BACK);
		Facility_View_initialize();
		facility_view_flag = 1;
	}
	//発動表示
	if (mask_flag == 1 && ignition_ax <= 0)
	{
		mask_flag = 0;
		ignition_ax = 0;
	}
	if (ignition_ax > 0) 
	{
		if (mask_flag == 0) ignition_ax += (ignition_ax > 80) ? 15 : 12;
		if (mask_flag == 1) ignition_ax -= (ignition_ax > 80) ? 15 : 12;
	}
	if (mask_flag == 0 && ignition_ax >= 157)
	{
		mask_flag = 1;
	}
	//ダイス表示
	if (display_time == 60)display_time = 0;
	if (display_time > 0)display_time++;
	//1flame前のマウスの状況
	OldMouseOshita = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

//描画
void Game_Draw()
{
	int i, j,k,s,t, m;
	int x;
	int y;
	char string[3][256] = { 0 };
	//背景
	DrawGraph(0, 0, GHandle[0], FALSE);// 画像を描画する

	//左のほう
	DrawBox(0, 0, 177, 260, Silver, TRUE);
	GradX_RGB(0, 270, 200, 639, 192, 192, 192, 120, 120, 120);	
	switch (left_box_flag) {
	case 0:
		DrawBox(card_info_x1, left_box_y1, card_info_x2, left_box_y2, Gray, TRUE);
		//選択カード表示仮
		x = 10;
		y = 301;
		if (change_flag == 1 && now_select != -1)
		{
			DrawFormatString(x, y, Brack, "%s\nコスト:%d 出目:%s", m_Supply[now_select].name, m_Supply[now_select].cost, m_Supply[now_select].dice_display);
			KaigyoDraw(x, y + 40, gyosu, 20, Brack, FontHandle, m_Supply[now_select].c_txt, begin, end);
		}
		if (change_flag == 2 && now_select2 != -1)
		{
			DrawFormatString(x, y, Brack, "%s\nコスト%d", m_Landmark[now_select2].name, m_Landmark[now_select2].cost);
			KaigyoDraw(x, y + 40, gyosu, 20, Brack, FontHandle, m_Landmark[now_select2].c_txt, begin, end);
		}
		break;
	case 1:
		message_x = 10;
		message_y = 320;
		DrawBox(log_x1, left_box_y1, log_x2, left_box_y2, Gray, TRUE);
		if (turn - select_log != 0 && select_log != 4)
		{
			DrawBox(card_info_x1, left_box_y1 + 24, card_info_x2, left_box_y2 + 24, Brack, FALSE);
			DrawString(10, 300, "前のターン", Brack);
		}
		if (select_log != 0)
		{
			DrawBox(log_x1, left_box_y1 + 24, config_x2, left_box_y2 + 24, Brack, FALSE);
			DrawString(110, 300, "次のターン", Brack);
		}
		for (i = scroll_log; (message_y < 580 && i < message_num[select_log]); i++)
		{
			butsugiri(message_log[select_log][i], width, FontHandle, begin, end, &gyosu);
			KaigyoDraw(message_x, message_y, gyosu, 20, Brack, FontHandle, message_log[select_log][i], begin, end);
			//DrawFormatStringToHandle(x, y, White,FontHandle, "%s", message_log[select_log][i]);
			message_y += 20 * gyosu;
		}
		if(message_y >= 580)DrawStringToHandle(50, 600, "↓", Brack, FontHandle);
		if(scroll_log > 0)DrawStringToHandle(150, 600, "↑", Brack, FontHandle);
		break;
	case 2:
		DrawBox(config_x1, left_box_y1, config_x2, left_box_y2, Gray, TRUE);
		DrawString(left_message_x, left_message_y, (IT_mode[select_player] == 1)?"常にITに乗せる〇":"常にITに乗せる×",Brack);
		DrawString(left_message_x, left_message_y + 20, (IT_mode[select_player] == 2) ? "ITに乗せない〇" : "ITに乗せない×", Brack);
		DrawString(left_message_x, left_message_y + 40, (effect_sort[select_player] == 1) ? "発動順自分で選ぶ〇" : "発動順自分で選ぶ×", Brack);
		break;
	}
	DrawBox(card_info_x1, left_box_y1, card_info_x2, left_box_y2, Brack, FALSE);
	DrawBox(log_x1, left_box_y1, log_x2, left_box_y2, Brack, FALSE);
	DrawBox(config_x1, left_box_y1, config_x2, left_box_y2, Brack, FALSE);
	DrawString(10, left_box_y1 + 3, "カード情報", Brack);
	DrawString(110, left_box_y1 +3, "ログ", Brack);
	DrawString(155, left_box_y1 + 3, "設定", Brack);


	if (change_flag == 1 && now_select != -1)
	{
		DrawGraph(10, 10, Facility_ImageHandle[now_select], TRUE);
		if (now_select >= gazounashi)
		{
			DrawBox(10, 10, 167, 251, Type_Color[m_Supply[now_select].type], TRUE);
			DrawBox(10, 10, 167, 251, Brack, FALSE);
			DrawFormatString(10, 10, Silver, "%s", m_Supply[now_select].name);
		}
	}
	if (change_flag == 2 && now_select2 != -1)
	{
		DrawGraph(10, 10, (m_Player[select_player].landmark[now_select2] == 1) ? LandMark_ImageHandle[now_select2] : LandMarkback_ImageHandle[now_select2], (m_Player[select_player].landmark[now_select2] == 1) ? TRUE:FALSE);
	}
	

	//マウス座標表示
	DrawFormatString(10, 600, White, "%5d,%5d", MouseX, MouseY);

	//サプライ表示仮
	DrawGraph(205, 10,GHandle[6] , TRUE);
	for (i = 0; i < 3; i++)
	{
		//DrawBox(card_x - card_x_wide2, card_y + card_y_wide2 * i, card_x + card_x_wide - card_x_wide2, card_y + card_y_wide + card_y_wide2 * i, White, FALSE);
		DrawGraph(card_x - card_x_wide2, card_y + card_y_wide2 * i, GHandle[4], TRUE);
		DrawFormatString(card_x - card_x_wide2, card_y + card_y_wide2 * i, Brack, "x%d", deckn[i]);
		for (j = 0; j < open_num[i]; j++)
		{
			if (supply[i][j] == -1)DrawString(card_x + card_x_wide2 * j, card_y + card_y_wide2 * i, "sold out", Red);
			if (supply[i][j] >= gazounashi)
			{
				DrawBox(card_x + card_x_wide2 * j, card_y + card_y_wide2 * i, card_x + card_x_wide + card_x_wide2 * j, card_y + card_y_wide + card_y_wide2 * i, Type_Color[m_Supply[supply[i][j]].type], TRUE);
				DrawBox(card_x + card_x_wide2 * j, card_y + card_y_wide2 * i, card_x + card_x_wide + card_x_wide2 * j, card_y + card_y_wide + card_y_wide2 * i, Brack, FALSE);
				DrawFormatString(card_x + card_x_wide2 * j, card_y + card_y_wide2 * i, Silver,(supply[i][j] != -1)? "%s\nx%d":"sold out", m_Supply[supply[i][j]].name, supplyn[i][j]);
			}
			else 
			{
				for (k = 0; k < supplyn[i][j]; k++)
				{
					DrawGraph(card_x + card_x_wide2 * j + k * 2, card_y + card_y_wide2 * i + 2 * k, Facility_thumbnail_ImageHandle[supply[i][j]], TRUE);
				}
				if(supplyn[i][j] > 1)DrawFormatString(card_x + card_x_wide2 * j + 20, card_y + card_y_wide2 * i + 15, Brack,"x%d" ,supplyn[i][j]);
			}
		}
	}

	//いろいろ選ぶボタン
	DrawBox(button_x, button_y, button_x + button_x_wide, button_y + button_y_wide * 3, White, FALSE);
	DrawBox(button_x + 2, button_y + 2, 1134, button_y + button_y_wide, Silver, TRUE);
	DrawBox(button_x + 2, button_y + 2 + button_y_wide, 1134, button_y + button_y_wide * 2, Silver, TRUE);
	DrawBox(button_x + 2, button_y + 2 + button_y_wide * 2, 1134, button_y + button_y_wide * 3, Silver, TRUE);

	DrawBox(860, 280, 980, 320, White, FALSE);
	DrawBox(862, 282, 978, 318, Silver, TRUE);
	DrawString(868,290,"所持施設詳細",Brack);

	for (i = 0; i < number_of_player; i++)
	{
		//DrawBox(button_x, player_info_y + player_info_y_wide * i, button_x + button_x_wide - 3, player_info_y + player_info_y_wide * (i + 1), m_Player[i].color, FALSE);
		DrawModiGraph(button_x, player_info_y + player_info_y_wide * i, button_x + button_x_wide - 3, player_info_y + player_info_y_wide * i, button_x + button_x_wide - 3, player_info_y + player_info_y_wide * (i + 1), button_x, player_info_y + player_info_y_wide * (i + 1),facilitybox_ImageHandle[i],TRUE);
		DrawFormatString(button_x, player_info_y + player_info_y_wide * i, White, "%s\n所持コイン%3d枚\nランドマーク %d/%d", m_Player[i].name, m_Player[i].coin, m_Player[i].landmark_Num,land_set_num);
	}

	//施設表示仮
	DrawGraph(205,330,facilitybox_ImageHandle[select_player],TRUE);
	DrawGraph(410, 560, GHandle[5], TRUE);// 画像を描画する
	DrawFormatStringToHandle(465, 570, White,FontHandle3, "×%d",m_Player[select_player].coin );
	DrawFormatString(facility_x, facility_y - 20, White, (select_player == now_turn) ? "---%dP:%s---(ターンプレイヤー)" : "---%dP:%s---", select_player + 1, m_Player[select_player].name);
	for (i = 0; ((i < m_Player[select_player].facility_Num) && (i < facility_num * 2) ) ; i++)
	{
		if (m_Player[select_player].m_Facility[i].card >= gazounashi)
		{
			DrawBox(facility_x + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num), facility_x + card_x_wide + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num + 1), Type_Color[m_Supply[m_Player[select_player].m_Facility[i].card].type], TRUE);
			DrawBox(facility_x + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num), facility_x + card_x_wide + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num + 1), Brack, FALSE);
			DrawFormatString(facility_x + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num), Silver, "%s", m_Supply[m_Player[select_player].m_Facility[i].card].name);
		}
		else DrawGraph(facility_x + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num), Facility_thumbnail_ImageHandle[m_Player[select_player].m_Facility[i].card], TRUE);
		if (m_Player[select_player].m_Facility[i].card == 36)DrawFormatString(facility_x + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num) + 20, Brack, "%d", m_Player[select_player].IT);
		if (m_Player[select_player].m_Facility[i].Holiday_flag == 1)DrawFormatString(facility_x + card_x_wide * (i % facility_num), facility_y + card_y_wide * (i / facility_num) + 20, Red, "休業中");
	}
	int delta_wide = 5;
	if (m_Player[select_player].facility_Num > 26) 
	{
		for (i = 26; i < m_Player[select_player].facility_Num; i++)
		{
			if (m_Player[select_player].m_Facility[i].card >= gazounashi)
			{
				DrawBox(facility_x + delta_wide * (i % facility_num), facility_y + card_y_wide * 2, facility_x + card_x_wide + delta_wide * (i % facility_num), facility_y + card_y_wide * 3, Type_Color[m_Supply[m_Player[select_player].m_Facility[i].card].type], TRUE);
				DrawBox(facility_x + delta_wide * (i % facility_num), facility_y + card_y_wide * 2, facility_x + card_x_wide + delta_wide * (i % facility_num), facility_y + card_y_wide * 3, Brack, FALSE);
				DrawFormatString(facility_x + delta_wide * (i % facility_num), facility_y + card_y_wide * 2, Silver, "%s", m_Supply[m_Player[select_player].m_Facility[i].card].name);
			}
			else DrawGraph(facility_x + delta_wide * (i % facility_num), facility_y + card_y_wide * 2, Facility_thumbnail_ImageHandle[m_Player[select_player].m_Facility[i].card], TRUE);
			if (m_Player[select_player].m_Facility[i].card == 36)DrawFormatString(facility_x + delta_wide * (i % facility_num), facility_y + card_y_wide * 2 + 20, Brack, "%d", m_Player[select_player].IT);
			if (m_Player[select_player].m_Facility[i].Holiday_flag == 1)DrawFormatString(facility_x + delta_wide * (i % facility_num), facility_y + card_y_wide * 2 + 20, Red, "休業中");
		}
	}
	//ランドマーク表示仮
	for (i = facility_num - 1; i > facility_num - 1 - land_set_num; i--)
	{
		//DrawBox(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, facility_x + card_x_wide + card_x_wide * i, facility_y + card_y_wide *3, White, FALSE);
		// (m_Player[select_player].landmark[i] == 1)?: LandMarkback_thumbnail_ImageHandle[i - 6]
		if (m_Player[select_player].landmark[i - facility_num + land_set_num] == 1)
		{
			DrawGraph(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, LandMark_thumbnail_ImageHandle[i - facility_num + land_set_num], TRUE);
			//DrawBox(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, facility_x + card_x_wide * i + card_x_wide, facility_y + card_y_wide * 2 + card_y_wide, White, TRUE);
			//DrawFormatString(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, Brack, "%s\n建設済", m_Landmark[i - facility_num + land_set_num].name);
		}
		else {
			DrawGraph(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, LandMarkback_thumbnail_ImageHandle[i - facility_num + land_set_num], FALSE);
			//DrawBox(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, facility_x + card_x_wide * i + card_x_wide, facility_y + card_y_wide * 2 + card_y_wide, Gray, TRUE);
			//DrawFormatString(facility_x + card_x_wide * i, facility_y + card_y_wide * 2, White, "%s\n未建設", m_Landmark[i - facility_num + land_set_num].name);
		}
	}

	switch (phase) {
	case 1://サイコロ振る
		DrawBox(500, 300, 900, 400, Gray, TRUE);
		DrawString(600, 350, "ダイスを振ってください", White);
		DrawFormatString(button_x + 10, button_y + 11, Brack, "ダイス");
		if(m_Player[now_turn].landmark[0] == 1)DrawFormatString(button_x + 10, button_y + 11 + button_y_wide, Brack, "2ダイス");
		break;
	case 2://建設する
		   //カードクリック時に窓を描画
		if (box_flag == 1)
		{
			Box_Draw_Facility("建設","詳細");
		}
		if (box_flag2 == 1)
		{
			Box_Draw_LandMark("建設", "詳細");
		}
		Button_Draw("", "", "パス");
		break;
	case 3://電波塔使うか否か
		Button_Draw("電波塔使う(1ダイス)","", "電波塔使わない");
		if(m_Player[now_turn].landmark[0] == 1)Button_Draw("","電波塔使う(2ダイス)","");
		break;
	case 4://効果解決
		if (effect_sort[(now_turn - ignition_order_flag - 1 + number_of_player * 3) % number_of_player] == 1 && ignition_type_num[ignition_order_flag] > 1)
		{
			DrawBox(210, 11, 980, 500, Brack, TRUE);
			DrawBox(210, 10, 980, 500, White, FALSE);
			for (i = 0; i < ignition_num[ignition_order_flag]; i++)
			{
				if (m_ignition[ignition_order_flag][i].card != -1)
				{
					if (m_ignition[ignition_order_flag][i].card >= gazounashi)
					{
						DrawBox(select_card_x + card_x_wide2 * i, select_card_y, select_card_x + card_x_wide + card_x_wide2 * i, select_card_y + card_y_wide, Silver, TRUE);
						DrawFormatString(select_card_x + card_x_wide2 * i, select_card_y, Brack, (order_box[i] != -1) ? "%s\n%d" : "%s", m_Supply[m_ignition[ignition_order_flag][i].card].name, order_box[i]);
					}
					else 
					{
						DrawGraph(select_card_x + card_x_wide2 * i, select_card_y, Facility_thumbnail_ImageHandle[m_ignition[ignition_order_flag][i].card], TRUE);
						if(order_box[i] != -1)DrawFormatString(select_card_x + card_x_wide2 * i, select_card_y - 20, White, "%d", order_box[i]);
					}
				}
			}
			DrawString(select_card_x, select_card_y + card_y_wide2, (s_count == ignition_num[ignition_order_flag]) ? "この順番でOK" : "順番を選んで", White);
		}
		break;
	case 5://港使うか否か
		Button_Draw("港使う", "港使わない", "");
		break;
	case 6://
		DrawGraph(100, 100, GHandle[7], TRUE);
		DrawFormatStringToHandle(200, 150, Brack, FontHandle2, "おめでとう!\n%s\n勝利\nヤッタネ！", m_Player[win_flag].name);
		break;
	case 7://エンドフェイズ
		break;
	case 13://テレビ発動時
		DrawBox(500, 300, 900, 400, Gray, TRUE);
		DrawString(600, 350, "テレビ局でコインをもらう相手を選択してください", White);
		for (i = 0; i < number_of_player - 1; i++)
		{
			sprintf_s(string[i],256,"%sから奪う",m_Player[(now_turn + i + 1) % number_of_player].name);
			//DrawFormatString(button_x + 10, button_y + i * button_y_wide + 11, Brack, "プレイヤー%dから奪う", (now_turn + i + 1) % number_of_player + 1);
		}
		Button_Draw(string[0], string[1], string[2]);
		break;
	case 14://ビジネスセンター発動時
		target_select_Draw(select_player);
		DrawString(300, 620, "ビジネスセンターで交換する施設を選択してください", White);
		DrawString(500, 650, "⇔", White);
		if (target_send != -1)
		{
			DrawFormatString(500,500, White, "%s", m_Supply[m_Player[now_turn].m_Facility[target_send].card].name);
		}
		if (target_get != -1)
		{
			DrawFormatString(500, 600, White, "%s", m_Supply[m_Player[target_player].m_Facility[target_get].card].name);
		}
		//カードクリック時に窓を描画
		if (box_flag == 1)
		{
			Box_Draw_Facility((select_player == now_turn) ? "あげる" : "もらう","");
		}
		break;
	case 15:
		DrawBox(500, 300, 900, 400, Gray, TRUE);
		DrawString(600, 350, "廃棄する施設を選択してください", White);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				if (Disposal_select[i][j] != 0)
				{
					DrawFormatString(card_x + card_x_wide2 * j, card_y + card_y_wide2 * i + 74, Red,"%d", Disposal_select[i][j]);
				}
			}
		}
		//カードクリック時に窓を描画
		if (box_flag == 1)
		{
			Box_Draw_Facility("廃棄する" , "");
		}
		break;
	case 27://改装屋発動時
		DrawBox(500, 300, 900, 400, Gray, TRUE);
		DrawString(600, 350, "建設前に戻すランドマークを選択してください", White);
		if (box_flag2 == 1)
		{
			Box_Draw_LandMark("畳む", "詳細");
		}
		break;
	case 32://引っ越し業者発動時
		for (i = 0; i < number_of_player - 1; i++)
		{
			sprintf_s(string[i], 256, "%sにあげる", m_Player[(now_turn + i + 1) % number_of_player].name);
		}
		Button_Draw(string[0], string[1], string[2]);
		target_select_Draw(0);
		DrawString(300, 620, "引っ越し業者で渡す施設と相手を選択してください", White);
		DrawString(500, 650, "→",White);
		if (target_send != -1)
		{
			DrawFormatString(500, 500, White, "%s", m_Supply[m_Player[now_turn].m_Facility[target_send].card].name);
		}
		if (target_player != -1)
		{
			DrawFormatString(500, 600, White, "%s", m_Player[target_player].name);
		}
		//カードクリック時に窓を描画
		if (box_flag == 1)
		{
			Box_Draw_Facility( "あげる","");
		}
		break;
	case 35://清掃業発動時
		target_select_Draw(0);
		DrawString(300, 620, "清掃業で休業にする施設を選択してください", White);
		//カードクリック時に窓を描画
		if (box_flag == 1)
		{
			Box_Draw_Facility("休業","");
		}
		break;
	case 36://ITベンチャーにコイン乗せるか否か
		Button_Draw("ITに投資する","ITに投資しない","");
		break;
	case 38://国際展示場で何発動するか
		target_select_Draw(0);
		//カードクリック時に窓を描画
		if (box_flag == 1)
		{
			Box_Draw_Facility("コピーする", "");
		}
		break;
	case 40://
		if (reform_flag == 0) 
		{
			Facility_View();
			DrawString(300, 620, "リフォーム業者で廃棄する施設を選択してください", White);
			Button_Draw("サプライ確認", "", "");
		}
		if(reform_flag == 1)
		{
			DrawBox(500, 300, 900, 400, Gray, TRUE);
			DrawString(600, 350, "入手する施設を選択してください", White);
			Button_Draw("", "", "パス");
		}
		if (reform_flag == 2)
		{
			Button_Draw("破棄選択", "", "");
		}
		if (box_flag == 1)
		{
			Box_Draw_Facility((reform_flag == 0)?"廃棄する":"入手する", "");
		}
		break;
	case 44://
		DrawBox(500, 300, 900, 400, Gray, TRUE);
		DrawFormatString(600, 330, White ,"[%s]\n入手する施設を選択してください",m_Player[target_player].name);
		if (box_flag == 1)
		{
			Box_Draw_Facility("入手する", "");
		}
		Button_Draw("", "", "パス");
		break;
	case 46://
		Facility_View();
		DrawString(300, 620, "地上げ屋でデッキに戻す施設を選択してください", White);
		if (box_flag == 1)
		{
			Box_Draw_Facility("戻す", "");
		}
		break;
	case 47://
		Facility_View();
		DrawString(300, 620, "テーマパークで購入する施設を選択してください", White);
		if (box_flag == 1)
		{
			Box_Draw_Facility("購入", "");
		}
		break;
	case 48://
		DrawBox(500, 300, 900, 400, Gray, TRUE);
		DrawString(600, 350, "建設前に戻すランドマークを選択してください", White);
		if (box_flag2 == 1)
		{
			Box_Draw_LandMark("畳む", "");
		}
		break;
	default:
		break;
	}
	//発動表示
	if (ignition_ax > 0)ignition_display_Draw();
	//施設表示大
	if (facility_view_flag == 1)
	{
		Facility_View();
	}
	//ダイス表示
	if (display_time > 0) 
	{
		DrawBox(400, 80, 800, 140, Gray, TRUE);
		DrawFormatStringToHandle(450, 100, White,FontHandle2, "%s",DiceDisplay);
	}
	//建設不可
	if (imposible_flag == 1) 
	{
		DrawGraph(100,100, GHandle[7], TRUE);
		DrawFormatStringToHandle(150, 200, Brack,FontHandle2, "お金たりないンゴ\n＿|￣|○ ");
	}
	//建設済み
	if (rebuild_flag == 1)
	{
		DrawGraph(100, 100, GHandle[7], TRUE);
		DrawFormatStringToHandle(150, 200, Brack,FontHandle2, "お前はすでに\n建設している……");
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////          関数           /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void message_initialize()
{
	int i,j;

	scroll_log = 0;
	select_log = 0;
	park_flag = 0;
	maguro = 0;
	for (i = 3; i >= 0; i--)
	{
		for (j = 0; j < 20; j++) 
		{
			sprintf_s(message_log[i + 1][j],256, message_log[i][j]);
		}
		message_num[i + 1] = message_num[i];
	}
	message_num[0] = 0;
	sprintf_s(message_log[0][message_num[0]], 256, "%sのターン", m_Player[turn % number_of_player].name);
	message_num[0]++;
}

static void shuffle(int ary[], int size)
{
	int i, r, t;
	PlaySoundMem(SHandle[4], DX_PLAYTYPE_BACK);

	for (i = 0; i < size; i++)
	{
		r = rand() % size;
		t = ary[i];
		ary[i] = ary[r];
		ary[r] = t;
	}
}

static void deck_build(int t)
{
	int which_deck, m, i, j;

	for (i = setmin[t]; i <= setMAX[t]; i++)
	{
		if (i == 38) 
		{
			m = 1;
			which_deck = 2;
		}
		else if (m_Supply[i].type == 4)
		{
			m = number_of_player;
			which_deck = 2;
		}
		else
		{
			m = 6;
			if (m_Supply[i].dice < 64)
			{
				which_deck = 0;
			}
			else
			{
				which_deck = 1;
			}
		}

		//没施設
		if (i == 10 || i == 38 || i == 41 || i == 42 || i == 43 || i == 44 || i == 45 || i == 51 || i == 53)
		{
			m = 0;
		}

		for (j = 0; j < m; j++)
		{
			deck[which_deck][deckn[which_deck]] = i;
			deckn[which_deck]++;
		}
	}
}

static void supply_initialize()
{
	int i, j,k;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < open_num[i]; j++)
		{
			supplyn[i][j] = 0;
			supply[i][j] = -1;
		}
	}

	for (i = 0; i < number_of_player; i++)
	{
		m_Player[i].facility_Num = 0;
		for (j = 0; j < 100; j++)
		{
			m_Player[i].m_Facility[j].card = -1;
		}
	}

	now_select = -1;
	now_select2 = -1;

	for (i = 0; i < number_of_player; i++)
	{
		for (j = 0; j < land_set_num; j++)
		{
			m_Player[i].landmark[j] = 0;
		}
	}

	for (i = 0; i < number_of_player; i++)
	{
		Config_2_reflect(&m_Player[i].name,i);
		m_Player[i].coin = 3;
		m_Player[i].m_Facility[m_Player[i].facility_Num].card = 0;
		m_Player[i].facility_Num++;
		m_Player[i].m_Facility[m_Player[i].facility_Num].card = 2;
		m_Player[i].facility_Num++;
		if (card_set[1] == 1)
		{
			m_Player[i].landmark[4] = 1;
			m_Player[i].landmark_Num = 1;
		}
		if (card_set[3] == 1)
		{
			m_Player[i].m_Facility[m_Player[i].facility_Num].card = 10;
			m_Player[i].facility_Num++;
			m_Player[i].m_Facility[m_Player[i].facility_Num].card = 16;
			m_Player[i].facility_Num++;
			m_Player[i].m_Facility[m_Player[i].facility_Num].card = 51;
			m_Player[i].facility_Num++;
		}
	}

}

static void supply_reload()
{
	int i, j, k, l, same_flag;

	for (i = 0; i < 3; i++)
	{
		for (k = 0; k < open_num[i]; k++)
		{
			if (supplyn[i][k] == 0 && deckn[i] != 0)
			{
				for (j = deckn[i] - 1; j >= 0; j--)
				{
					if (deck[i][j] != -1)
					{
						for (l = 0; l < open_num[i]; l++)
						{
							if (deck[i][j] == supply[i][l])
							{
								same_flag = 1;
								break;
							}
							else same_flag = 0;
						}
						if (same_flag == 1)supplyn[i][l]++;
						else
						{
							supplyn[i][k]++;
							supply[i][k] = deck[i][j];
						}
						PlaySoundMem(SHandle[3], DX_PLAYTYPE_BACK);
						deck[i][j] = -1;
						deckn[i]--;
						break;
					}
				}
			}
			if (supplyn[i][k] == 0 && deckn[i] == 0)
			{
				supply[i][k] = -1;
			}
		}
	}

}

static void card_sort() 
{
	int i, j,k,tmp;

	for (i = 0; i < number_of_player; i++)
	{
		for (j = 0; j < m_Player[i].facility_Num; j++) 
		{
			for (k = j + 1; k < m_Player[i].facility_Num; k++) 
			{
				if (m_Supply[m_Player[i].m_Facility[j].card].dice > m_Supply[m_Player[i].m_Facility[k].card].dice)
				{
					m_tmp = m_Player[i].m_Facility[j];
					m_Player[i].m_Facility[j] = m_Player[i].m_Facility[k];
					m_Player[i].m_Facility[k] = m_tmp;
				}
			}
		}
	}
}

static int select_card(int x, int y)
{
	int i, j;
	int flagx;
	int flagy;

	flagx = -1;
	flagy = -1;

	for (i = 0; i < 3; i++)
	{
		if ((i * card_y_wide2 < y - card_y) && (y - card_y_wide - card_y < i * card_y_wide2))
		{
			flagy = i;
			for (j = 0; j < open_num[i]; j++)
			{
				if ((j * card_x_wide2 < x - card_x) && (x - card_x - card_x_wide < j * card_x_wide2))
				{
					flagx = j;
					return supply[flagy][flagx];
				}
			}
		}
	}
	return -1;
}

static int select_landmark(int x, int y)
{
	int i,j;

	if (facility_y + card_y_wide * 2 < y && y < facility_y + card_y_wide *3)
	{
		for (i = facility_num - 1; i > facility_num - 1 - land_set_num; i--)
		{
			if (facility_x + card_x_wide * i < x && x < facility_x + card_x_wide + card_x_wide * i)
			{
				return i - facility_num + land_set_num;
			}
		}
	}
	return -1;
}

static void Box_Draw_Facility(const char txt1[], const char txt2[])
{
	DrawBox(boxX, boxY, boxX + 100, boxY + 50, White, FALSE);
	DrawBox(boxX + 2, boxY + 2, boxX + 98, boxY + 24, Silver, TRUE);
	DrawBox(boxX + 2, boxY + 26, boxX + 98, boxY + 48, Silver, TRUE);
	DrawFormatString(boxX + 25, boxY + 5, Brack, "%s",txt1);
	DrawFormatString(boxX + 25, boxY + 27, Brack, "%s", txt2);
}

static void Box_Draw_LandMark(const char txt1[], const char txt2[])
{
	DrawBox(boxX2, boxY2, boxX2 + 100, boxY2 + 50, White, FALSE);
	DrawBox(boxX2 + 2, boxY2 + 2, boxX2 + 98, boxY2 + 24, Silver, TRUE);
	DrawBox(boxX2 + 2, boxY2 + 26, boxX2 + 98, boxY2 + 48, Silver, TRUE);
	DrawFormatString(boxX2 + 35, boxY2 + 5, Brack, "%s",txt1);
	DrawFormatString(boxX2 + 35, boxY2 + 27, Brack, "%s",txt2);
}

static void Button_Draw(const char txt1[], const char txt2[], const char txt3[])
{
	DrawFormatString(button_x + 10, button_y + 11, Brack, "%s",txt1);
	DrawFormatString(button_x + 10, button_y + 11 + button_y_wide, Brack, "%s",txt2);
	DrawFormatString(button_x + 10, button_y + 11 + button_y_wide * 2, Brack, "%s", txt3);
}

static void target_select_Draw(int player)
{
	int i, j;

	DrawGraph(210, 10, GHandle[8], TRUE);
	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < have_box_x; j++)
		{
			if (have_box[i][j][player] != -1)
			{
				if (have_box[i][j][player] >= gazounashi)
				{
					DrawBox(select_card_x + card_x_wide2 * j, select_card_y + card_y_wide2 * i, select_card_x + card_x_wide + card_x_wide2 * j, select_card_y + card_y_wide + card_y_wide2 * i, Type_Color[m_Supply[have_box[i][j][player]].type], TRUE);
					DrawBox(select_card_x + card_x_wide2 * j, select_card_y + card_y_wide2 * i, select_card_x + card_x_wide + card_x_wide2 * j, select_card_y + card_y_wide + card_y_wide2 * i, Brack, FALSE);
					DrawFormatString(select_card_x + card_x_wide2 * j, select_card_y + card_y_wide2 * i, Silver, "%s", m_Supply[have_box[i][j][player]].name);
				}
				else
				{
					DrawGraph(select_card_x + card_x_wide2 * j, select_card_y + card_y_wide2 * i, Facility_thumbnail_ImageHandle[have_box[i][j][player]], TRUE);
				}
			}
		}
	}
}

static void Facility_View_initialize()
{
	int i, j, k;
	
	for (k = 0; k < number_of_player; k++)
	{
		for (j = 1; j <= 11; j++)
		{
			have_card_type_num[k][j] = 0;
		}
	}

	for (k = 0; k < number_of_player; k++)
	{
		for (i = 0; i < m_Player[k].facility_Num; i++)
		{
			for (j = 1; j < 11; j++)
			{
				if (m_Supply[m_Player[k].m_Facility[i].card].ctgry == j)
				{
					have_card_type_num[k][j]++;
				}
			}
		}
		have_card_type_num[k][8] += m_Player[k].landmark_Num;
	}
}

static void Facility_View()
{
	int i, j;

	DrawGraph(210, 10, GHandle[8], TRUE);
	for (i = 0;i < m_Player[select_player].facility_Num; i++)
	{
		if (m_Player[select_player].m_Facility[i].card >= gazounashi)
		{
			DrawBox(select_card_x + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num), select_card_x + card_x_wide + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num + 1), Type_Color[m_Supply[m_Player[select_player].m_Facility[i].card].type], TRUE);
			DrawBox(select_card_x + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num), select_card_x + card_x_wide + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num + 1), Brack, FALSE);
			DrawFormatString(select_card_x + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num), Silver, "%s", m_Supply[m_Player[select_player].m_Facility[i].card].name);
		}
		else DrawGraph(select_card_x + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num), Facility_thumbnail_ImageHandle[m_Player[select_player].m_Facility[i].card], TRUE);
		if (m_Player[select_player].m_Facility[i].card == 36)DrawFormatString(select_card_x + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num) + 20, Brack, "%d", m_Player[select_player].IT);
		if (m_Player[select_player].m_Facility[i].Holiday_flag == 1)DrawFormatString(select_card_x + card_x_wide * (i % facility_num), select_card_y + card_y_wide * (i / facility_num) + 20, Red, "休業中");
	}
	DrawString(300, 423, "マーク所持数", Brack);
	for (i = 1; i <= 11; i++) 
	{
		DrawGraph(270 + (i / 4) * 150, 420 + (i % 4) * 25, GHandleType[i], TRUE);
		DrawFormatString(300 + (i / 4) * 150, 423 + (i % 4) * 25, Brack, "[%s]×%d", type_name[i - 1],have_card_type_num[select_player][i]);
	}
	DrawFormatString(300, 560,Brack, "%sの街", m_Player[select_player].name);
}

static void dice_phase()
{
	//ダイスロール
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y < MouseY && MouseY < button_y + button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		dice_roll(1);
		if (m_Player[now_turn].landmark[3] == 0)
		{
			//ダイスチェック
			dice_check(dice_result_copy[0]);
		}
		else
		{
			phase = 3;
		}
	}
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide < MouseY && MouseY < button_y + button_y_wide * 2 && m_Player[now_turn].landmark[0] == 1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		dice_roll(2);//ダイスチェック
		if (m_Player[now_turn].landmark[3] == 0 && m_Player[now_turn].landmark[5] == 0)
		{
			//ダイスチェック
			dice_check(dice_result_copy[0]);
		}
		else if (m_Player[now_turn].landmark[3] == 1) phase = 3;
		else if (dice_result_copy[0] >= 10)phase = 5;
		else dice_check(dice_result_copy[0]);
	}
}


static void dice_roll(int num)
{
	int i;

	PlaySoundMem(SHandle[1], DX_PLAYTYPE_NORMAL);
	dice_result[0] = rand() % 6 + 1;
	dice_result[1] = (num == 1) ? 0 : rand() % 6 + 1;
	dice_result_copy[0] = dice_result[0] + dice_result[1];

	if (dice_result[1] == 0)
	{
		sprintf_s(DiceDisplay, 256, "ダイス結果[%d]", dice_result[0]);
		sprintf_s(message_log[0][message_num[0]], 256, "出目:%d", dice_result[0]);
		message_num[0]++;
		display_time = 1;
	}
	if (dice_result[1] != 0)
	{
		sprintf_s(DiceDisplay, 256, "ダイス結果[%d + %d = %d]", dice_result[0], dice_result[1], dice_result_copy[0]);
		sprintf_s(message_log[0][message_num[0]], 256, "出目:%d + %d = %d", dice_result[0], dice_result[1], dice_result_copy[0]);	
		message_num[0]++;
		display_time = 1;
	}
}

static void dice_check(int d)
{
	int i, j, k, l, t, s, check_flag;

	//遊園地
	if (dice_result[0] == dice_result[1] && m_Player[now_turn].landmark[2])
	{
		park_flag = 1;
		sprintf_s(message_log[0][message_num[0]], 256, "%sの遊園地が発動", m_Player[now_turn].name);
		message_num[0]++;
		landmark_ignition_display(2);
	}
	for (i = 0; i < 8; i++) 
	{
		for (j = 0; j < 50; j++) 
		{
			m_ignition[i][j] = m_default_ignition;
		}
	}
	t = 0;
	dice_result_copy[1] = 1;
	for (i = 0; i < d - 1; i++) dice_result_copy[1] *= 2;
	for (i = now_turn + (number_of_player * 2) - 1; i >= now_turn; i--)
	{
		s = 0;
		for (j = 0; j < m_Player[i % number_of_player].facility_Num; j++)
		{
			check_flag = 0;
			if (t < number_of_player - 1 && m_Supply[m_Player[i % number_of_player].m_Facility[j].card].type == 2)check_flag = 1;
			if (t == number_of_player - 1 && m_Supply[m_Player[i % number_of_player].m_Facility[j].card].type == 1)check_flag = 1;
			if (number_of_player - 1 <= t && t < (number_of_player * 2) - 1 && m_Supply[m_Player[i % number_of_player].m_Facility[j].card].type == 3)check_flag = 1;
			if (t == (number_of_player * 2) - 1 && m_Supply[m_Player[i % number_of_player].m_Facility[j].card].type == 4)check_flag = 1;
			if (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].conditions == 1 && m_Player[i % number_of_player].landmark[5] == 0)check_flag = 0;
			if (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].conditions == 2 && m_Player[i % number_of_player].landmark_Num > 2)check_flag = 0;
			if (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].conditions == 3 && m_Player[now_turn].landmark_Num < 3)check_flag = 0;
			if (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].conditions == 4 && m_Player[now_turn].landmark_Num < 4)check_flag = 0;
			if (check_flag == 1 && m_Player[i % number_of_player].m_Facility[j].Holiday_flag == 1 && (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].dice & dice_result_copy[1]) != 0) m_Player[i % number_of_player].m_Facility[j].Holiday_flag = 0;
			else if (check_flag == 1 && (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].dice & dice_result_copy[1]) != 0)
			{
				m_ignition[t][s] = { m_Player[i % number_of_player].m_Facility[j].card, i % number_of_player };
				s++;
			}
		}
		t++;
	}
	ignition_initialize();
}

static void port_use()
{
	//港使う
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y < MouseY && MouseY < button_y + button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		dice_result_copy[0] += 2;
		sprintf_s(DiceDisplay, 256, "ダイス結果[%d + %d + 2 = %d]", dice_result[0], dice_result[1], dice_result_copy[0]);
		sprintf_s(message_log[0][message_num[0]], 256, "%sの港が発動", m_Player[now_turn].name);
		message_num[0]++;
		sprintf_s(message_log[0][message_num[0]], 256, "出目:%d + %d + 2 = %d", dice_result[0], dice_result[1], dice_result_copy[0]);
		message_num[0]++;
		dice_check(dice_result_copy[0]);
		landmark_ignition_display(5);
	}
	//港使わん
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide < MouseY && MouseY < button_y + button_y_wide * 2 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		dice_check(dice_result_copy[0]);
	}
}

static void tower_use()
{
	//電波塔1ダイス
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y < MouseY && MouseY < button_y + button_y_wide && phase == 3 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		sprintf_s(message_log[0][message_num[0]], 256, "%sの電波塔が発動", m_Player[now_turn].name);
		message_num[0]++;
		dice_roll(1);
		dice_check(dice_result_copy[0]);
		landmark_ignition_display(3);
	}
	//電波塔2ダイス
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide < MouseY && MouseY < button_y + button_y_wide * 2 && m_Player[now_turn].landmark[0] == 1 && phase == 3 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		sprintf_s(message_log[0][message_num[0]], 256, "%sの電波塔が発動", m_Player[now_turn].name);
		message_num[0]++;
		dice_roll(2);
		if (dice_result_copy[0] >= 10 && m_Player[now_turn].landmark[5])phase = 5;
		else dice_check(dice_result_copy[0]);
		landmark_ignition_display(3);
	}
	//電波塔使わん
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide * 2 < MouseY && MouseY < button_y + button_y_wide * 3 && phase == 3 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		if (dice_result_copy[0] >= 10 && m_Player[now_turn].landmark[5])phase = 5;
		else dice_check(dice_result_copy[0]);
	}
}

static void ignition_initialize()
{
	int i, j,t = -1;

	for (i = 0; i < 8; i++)
	{
		ignition_type_num[i] = 0;
		go_flag[i] = 0;
		for (j = 0; j < 50; j++) 
		{
			if (m_ignition[i][j].card == -1) 
			{
				ignition_num[i] = j;
				break;
			}
			else if (t != m_ignition[i][j].card)
			{
				ignition_type_num[i]++;
				t = m_ignition[i][j].card;
			}
		}
	}
	for (i = 0; i < 50; i++) 
	{
		order_box[i] = -1;
	}
	s_count = 0;
	ignition_order_flag = 0;
	phase = 4;
}

static void ignition_order_select()
{
	int i, j,k,tmp;

	if (effect_sort[(now_turn - ignition_order_flag - 1 + number_of_player * 3) % number_of_player] == 0 || ignition_type_num[ignition_order_flag] <= 1 || go_flag[ignition_order_flag] == 1)
	{
		ignition_phase();
	}
	else
	{//順番
		for (i = 0; i < ignition_num[ignition_order_flag]; i++)
		{
			if (m_ignition[ignition_order_flag][i].card != -1 && select_card_x + i * card_x_wide2 < MouseX && MouseX < select_card_x + i * card_x_wide2 + card_x_wide && select_card_y < MouseY && MouseY < select_card_y + card_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
			{
				if (order_box[i] == -1)
				{
					s_count++;
					order_box[i] = s_count;
				}
				else if (order_box[i] == s_count)
				{
					s_count--;
					order_box[i] = -1;
				}
			}
		}
		if (s_count == ignition_num[ignition_order_flag] && select_card_x < MouseX && MouseX < select_card_x + card_x_wide && select_card_y + card_y_wide2 < MouseY && MouseY < select_card_y + card_y_wide + card_y_wide2 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			for (i = 1; i <= ignition_num[ignition_order_flag]; i++)
			{
				for (j = 0; j < ignition_num[ignition_order_flag]; j++) 
				{
					if (order_box[j] == i) 
					{
						tmp = m_ignition[ignition_order_flag][j].card;
						m_ignition[ignition_order_flag][j].card = m_ignition[ignition_order_flag][i - 1].card;
						m_ignition[ignition_order_flag][i - 1].card = tmp;
						tmp = order_box[j];
						order_box[j] = order_box[i - 1];
						order_box[i - 1] = tmp;
					}
				}
			}
			go_flag[ignition_order_flag] = 1;
		}
	}
}

static void ignition_phase()
{
	int i;

	for (i = 0; i < ignition_num[ignition_order_flag]; i++)
	{
		if (m_ignition[ignition_order_flag][i].card != -1)
		{
			ignition_flag = m_ignition[ignition_order_flag][i].card;
			ignition_card(m_ignition[ignition_order_flag][i].card, m_ignition[ignition_order_flag][i].player);
			m_ignition[ignition_order_flag][i] = m_default_ignition;
			mask_flag = 0;
			ignition_ax = 1;
			display_mode = 0;
			PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK);
			return;
		}
	}
	s_count = 0;
	ignition_order_flag++;
	if(ignition_order_flag == 8)phase = 2;
	else ignition_order_select();
}

static void ignition_card(int card, int player)
{
	if (m_Supply[card].income == 0) card_effect(card, player);
	else
	{
		income_processing(card, player, m_Supply[card].income);
	}
}

static void income_processing(int card, int player, int income)
{
	int i, j;

	if (m_Supply[card].type == 2 || m_Supply[card].ctgry == 3)
	{
		income += m_Player[player].landmark[1];
	}
	if (m_Supply[card].type == 2)
	{
		if (m_Player[now_turn].coin < income) income = m_Player[now_turn].coin;
		m_Player[now_turn].coin -= income;
	}

	m_Player[player].coin += income;
	sprintf_s(message_log[0][message_num[0]], 256, "%sの%sが%d収入", m_Player[player].name, m_Supply[card].name,income);
	message_num[0]++;
}

static void landmark_ignition_display(int id)
{
	ignition_flag = id;
	ignition_ax = 1;
	PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK);
	mask_flag = 0;
	display_mode = 1;
}

static void ignition_display_Draw() 
{
	if (ignition_flag >= gazounashi)
	{
		if (display_mode != 0)
		{
			DrawGraph(ignition_x1, ignition_y1,LandMark_ImageHandle[ignition_flag], TRUE);
		}
		else {
			DrawBox(ignition_x1, ignition_y1, ignition_x1 + card2_x_wide, ignition_y1 + card2_y_wide, Type_Color[m_Supply[ignition_flag].type], TRUE);
			DrawBox(ignition_x1, ignition_y1, ignition_x1 + card2_x_wide, ignition_y1 + card2_y_wide, Brack, FALSE);
			DrawFormatString(ignition_x1, ignition_y1, Silver, "%s", m_Supply[ignition_flag].name);
		}
	}
	else
	{
		DrawGraph(ignition_x1, ignition_y1, (display_mode == 0)?Facility_ImageHandle[ignition_flag]: LandMark_ImageHandle[ignition_flag], TRUE);
	}
	if (mask_flag == 0)
	{
		DrawExtendGraph(ignition_x1, ignition_y1, ignition_x1 + ignition_ax, ignition_y1 + ignition_ax / 157 * 241, GHandle[2], TRUE);
	}
	if (mask_flag == 1)
	{
		DrawExtendGraph(ignition_x2 - ignition_ax, ignition_y2 - ignition_ax / 157 * 241, ignition_x2, ignition_y2, GHandle[2], TRUE);
	}
}

static void card_effect(int card, int player)
{
	int i, j, k, m, max_play, max_card, min_card, get_income;

	get_income = 0;
	switch (card) {

	case 6://チーズ工場
		for (i = 0; i < m_Player[player].facility_Num; i++) if (m_Supply[m_Player[player].m_Facility[i].card].ctgry == 2) get_income += 3;
		income_processing(card, player, get_income);
		break;
	case 7://家具工場
		for (i = 0; i < m_Player[player].facility_Num; i++) if (m_Supply[m_Player[player].m_Facility[i].card].ctgry == 5) get_income += 3;
		income_processing(card, player, get_income);
		break;
	case 11://青果市場
		for (i = 0; i < m_Player[player].facility_Num; i++) if (m_Supply[m_Player[player].m_Facility[i].card].ctgry == 1) get_income += 2;
		income_processing(card, player, get_income);
		break;
	case 12://スタジアム
		for (i = player + 1; i < player + number_of_player; i++)
		{
			if (m_Player[i % number_of_player].coin < 2)
			{
				get_income += m_Player[i % number_of_player].coin;
				m_Player[i % number_of_player].coin = 0;
			}
			else
			{
				get_income += 2;
				m_Player[i % number_of_player].coin -= 2;
			}
		}
		income_processing(card, player, get_income);
		break;
	case 13://テレビ局
		phase = 13;
		break;
	case 14://ビジネスセンター
		business_initialize();
		break;
	case 17://フラワーショップ
		for (i = 0; i < m_Player[player].facility_Num; i++) if (m_Player[player].m_Facility[i].card == 16) get_income++;
		income_processing(card, player, get_income);
		break;
	case 21://食品倉庫
		for (i = 0; i < m_Player[player].facility_Num; i++) if (m_Supply[m_Player[player].m_Facility[i].card].type == 2) get_income += 2;
		income_processing(card, player, get_income);
		break;
	case 22://マグロ漁船
		if (maguro == 0) maguro = rand() % 6 + rand() % 6 + 2;
		income_processing(card, player, maguro);
		break;
	case 23://出版社
		for (i = player + 1; i < player + number_of_player; i++)
		{
			k = 0;
			for (j = 0; j < m_Player[i % number_of_player].facility_Num; j++)
			{
				if (m_Supply[m_Player[i % number_of_player].m_Facility[j].card].type == 2 || m_Supply[m_Player[i % number_of_player].m_Facility[j].card].ctgry == 3)
				{
					k++;
				}
			}
			if (m_Player[i % number_of_player].coin < k)
			{
				get_income += m_Player[i % number_of_player].coin;
				m_Player[i % number_of_player].coin = 0;
			}
			else
			{
				get_income += k;
				m_Player[i % number_of_player].coin -= k;
			}
		}
		income_processing(card, player, get_income);
		break;
	case 24://税務署
		for (i = player + 1; i < player + number_of_player; i++)
		{
			if (m_Player[i % number_of_player].coin >= 10)
			{
				get_income += (m_Player[i % number_of_player].coin / 2);
				m_Player[i % number_of_player].coin -= (m_Player[i % number_of_player].coin / 2);
			}
		}
		income_processing(card, player, get_income);
		break;
	case 27://改装屋
		if(m_Player[player].landmark_Num > 1)phase = 27;
		break;
	case 29://貸金屋
		if (m_Player[player].coin < 2)
		{
			get_income = m_Player[player].coin;
		}
		else
		{
			get_income = 2;
		}
		income_processing(card, player, -get_income);
		break;
	case 31://ワイナリー
		for (i = 0; i < m_Player[player].facility_Num; i++)
		{
			if (m_Player[player].m_Facility[i].card == 30)
			{
				get_income += 6;
			}
		}
		for (i = 0; i < m_Player[player].facility_Num; i++)
		{
			if (m_Player[player].m_Facility[i].card == 31 && m_Player[player].m_Facility[i].Holiday_flag == 0)
			{
				m_Player[player].m_Facility[i].Holiday_flag = 1;
				break;
			}
		}
		income_processing(card, player, get_income);
		break;
	case 32://引っ越し屋
		mover_initialize();
		break;
	case 33://ドリンク工場
		for (i = 0; i < number_of_player; i++) for (j = 0; j < m_Player[i].facility_Num; j++) if (m_Supply[m_Player[i].m_Facility[j].card].ctgry == 4) get_income++;
		income_processing(card, player, get_income);
		break;
	case 35://清掃業
		cleaning_initialize();
		break;
	case 36://ITベンチャー
		for (i = player + 1; i < player + number_of_player; i++)
		{
			if (m_Player[i % number_of_player].coin < m_Player[player].IT)
			{
				get_income += m_Player[i % number_of_player].coin;
				m_Player[i % number_of_player].coin = 0;
			}
			else
			{
				get_income += m_Player[player].IT;
				m_Player[i % number_of_player].coin -= m_Player[player].IT;
			}
		}
		income_processing(card, player, get_income);
		break;
	case 37://公園
		k = 0;
		for (i = 0; i < number_of_player; i++)
		{
			k += m_Player[i].coin;
		}
		for (i = k; i != 0; i++)
		{
			if (i % number_of_player == 0)
			{
				for (j = 0; j < number_of_player; j++)
				{
					m_Player[j].coin = (i / number_of_player);
				}
				break;
			}
		}
		sprintf_s(message_log[0][message_num[0]], 256, "%sの%sが発動", m_Player[player].name, m_Supply[card].name);
		message_num[0]++;
		break;
	case 38://国際展示場
		Exhibition_initialize();
		break;
	case 39://不動産屋
		build_count++;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				for (k = 0; k < supplyn[i][j]; k++)
				{
					deck[i][deckn[i]] = supply[i][j];
					deckn[i]++;
				}
				supplyn[i][j]=0;
			}
			shuffle(deck[i], deckn[i]);
		}
		sprintf_s(message_log[0][message_num[0]], 256, "%sの不動産屋が発動", m_Player[now_turn].name);
		message_num[0]++;
		break;
	case 40://リフォーム業者
		Facility_View_initialize();
		sprintf_s(message_log[0][message_num[0]], 256, "%sのリフォーム業者が発動", m_Player[now_turn].name);
		message_num[0]++;
		reform_flag = 0;
		phase = 40;
		break;
	case 41://礼拝堂
		sprintf_s(message_log[0][message_num[0]], 256, "%sの礼拝堂が発動", m_Player[now_turn].name);
		message_num[0]++;
		Disposal_supply_initialize(3);
		break;
	case 42://教会
		income_processing(42, player, 1);
		select_player = player;
		Disposal_supply_initialize(1);
		break;
	case 43://チャペル
		sprintf_s(message_log[0][message_num[0]], 256, "%sのチャペルが発動", m_Player[now_turn].name);
		message_num[0]++;
		Disposal_supply_initialize(1);
		break;
	case 44://祭りの屋台
		food_stand_initialize(player);
		break;
	case 45://個人商店
		for (i = 0; i < m_Player[player].facility_Num; i++)
		{
			if (m_Player[player].m_Facility[i].card == 45 && m_Player[player].m_Facility[i].Holiday_flag == 0)
			{
				m_Player[player].m_Facility[i].Holiday_flag = 1;
				break;
			}
		}
		get_income = 5;
		for (i = 0; i < m_Player[player].facility_Num; i++)
		{
			if (m_Player[player].m_Facility[i].card == 4)
			{
				get_income = 1;
				/*
				m = 0;
				for (i = 0; i < m_Player[player].facility_Num; i++)
				{
					if (m_Player[player].m_Facility[i].card == 45)
					{
						m = i;
					}
				}
				m_Player[player].m_Facility[m] = m_Player[player].m_Facility[m_Player[player].facility_Num - 1];
				m_Player[player].m_Facility[m_Player[player].facility_Num - 1] = m_default_Facility;
				m_Player[player].facility_Num--;
				Disposal_box[Disposal_box_num] = 45;
				Disposal_box_num++;
				*/
				break;
			}
		}
		income_processing(card, player, get_income);
		break;
	case 46://地上げ屋
		Land_speculator_initialize();
		break;
	case 47://テーマパーク
		theme_park_initialize();
		break;
	case 48://土建屋
		general_contractor_initialize();
		break;
	case 49://スーパーマーケット
		for (i = 0; i < m_Player[player].facility_Num; i++) if (m_Supply[m_Player[player].m_Facility[i].card].ctgry == 3) get_income += 2;
		income_processing(card, player, get_income);
		break;
	case 50://和食
		build_count = 0;
		break;
	case 52://観光
		for (i = 0; i < number_of_player; i++)
		{
			for (j = 0; j < m_Player[i].facility_Num; j++)
			{
				if (m_Supply[m_Player[i].m_Facility[j].card].ctgry == 4) 
				{
					get_income++;
				}
			}
			get_income += m_Player[i].landmark_Num;
		}
		income_processing(card, player, get_income);
		break;
	case 53://飲食店
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				if (m_Supply[supply[i][j]].type == 2)
				{
					get_income += 2 * supplyn[i][j];
				}
			}
		}
		income_processing(card, player, get_income);
		break;
	case 54://IT
		break;
	default:
		break;
	}
}

static int select_card2(int x, int y ,int player)
{
	int i, j;

	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < have_box_x; j++)
		{
			if ((select_card_x + j * card_x_wide2 < x) && ( x < select_card_x + card_x_wide + j * card_x_wide2) && (select_card_y + i * card_y_wide2 < y) && (y < select_card_y + card_y_wide + i * card_y_wide2))
			{
				return have_box[i][j][player];
			}
		}
	}
	return -1;
}

static int select_facility(int x, int y)
{
	int i, j;

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < facility_num; j++)
		{
			if ((facility_x + j * card_x_wide < x) && (x < facility_x + card_x_wide + j * card_x_wide) && (facility_y + i * card_y_wide < y) && (y < facility_y + card_y_wide + i * card_y_wide))
			{
				return m_Player[select_player].m_Facility[i * facility_num + j].card;
			}
		}
	}
	return -1;
}

static int select_facility2(int x, int y,int player)
{
	int i, j;

	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < facility_num; j++)
		{
			if ((select_card_x + j * card_x_wide < x) && (x < select_card_x + card_x_wide + j * card_x_wide) && (select_card_y + i * card_y_wide < y) && (y < select_card_y + card_y_wide + i * card_y_wide))
			{
				return m_Player[player].m_Facility[i * facility_num + j].card;
			}
		}
	}
	return -1;
}

static void TV_use()
{

	int i, j, m, target, get_income;
	target = -1;

	//プレイヤー選択
	for (i = 0; i < number_of_player - 1; i++) 
	{
		if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + i * button_y_wide < MouseY && MouseY < button_y + button_y_wide + i * button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			target = (now_turn + 1 + i) % number_of_player;
		}
	}

	if (target != -1)
	{
		get_income = 5;
		m = 0;
		if (m_Player[target].coin < 5) get_income = m_Player[target].coin;
		m_Player[target].coin -= get_income;
		income_processing(13, now_turn, get_income);
		phase = 4;
	}
}

static void mover_initialize()
{
	int i, j, k, s, t, have_flag;
	target_send = -1;
	target_player = -1;

	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < have_box_x; j++)
		{
			have_box[i][j][0] = -1;
		}
	}
	s = 0;
	for (i = 0; i < m_Player[now_turn].facility_Num; i++)
	{
		for (j = 0; j < card_syurui; j++)
		{
			have_flag = 0;
			if (m_Player[now_turn].m_Facility[i].card == j && m_Supply[j].type != 4)
			{
				have_box[s / have_box_x][s % have_box_x][0] = j;
				have_flag = 1;
			}
			if (have_flag == 1)s++;
		}
	}	
	phase = 32;
}

static void mover_use() 
{
	int i, j, k, get_income;

	if (select_card2(MouseX, MouseY, 0) != -1 && box_flag == 0)
	{
		now_select = select_card2(MouseX, MouseY, 0);
		change_flag = 1;
	}

	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_card2(MouseX, MouseY, 0) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0 && select_player == now_turn)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//引っ越し
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		for (i = 0; i < m_Player[now_turn].facility_Num; i++)
		{
			if (m_Player[now_turn].m_Facility[i].card == now_select)
			{
				box_flag = 0;
				box_erase_flag = 1;
				target_send = i;
				box_flag = 0;
				box_erase_flag = 1;
				break;
			}
		}
	}

	//プレイヤー選択
	for (i = 0; i < number_of_player - 1; i++)
	{
		if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + i * button_y_wide < MouseY && MouseY < button_x + button_x_wide + i * button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			target_player = (now_turn + 1 + i) % number_of_player;
		}
	}

	if (target_player != -1 && target_send != -1)
	{
		box_flag = 0;
		box_erase_flag = 1;
		m_Player[target_player].m_Facility[m_Player[target_player].facility_Num] = m_Player[now_turn].m_Facility[target_send];
		m_Player[target_player].facility_Num++;
		m_Player[now_turn].m_Facility[target_send] = m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num - 1];
		m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num - 1] = m_default_Facility;
		m_Player[now_turn].facility_Num--;
		income_processing(32, now_turn, 4);
		phase = 4;
	}
}

static void cleaning_initialize()
{
	int i,j,k,s, t,have_flag;
	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < have_box_x; j++)
		{
			have_box[i][j][0] = -1;
		}
	}

	s = 0;
	for (i = 0; i < card_syurui; i++)
	{
		have_flag = 0;
		for (j = 0; j < number_of_player; j++)
		{
			for (k = 0; k < m_Player[j].facility_Num; k++)
			{
				if (m_Player[j].m_Facility[k].card == i && m_Supply[i].type != 4)
				{
					have_box[s / have_box_x][s % have_box_x][0] = i;
					have_flag = 1;
				}
			}
		}
		if(have_flag == 1)s++;
	}
	phase = 35;
}

static void cleaning_use()
{
	int i, j,k, target,get_income;
	
	if (select_card2(MouseX, MouseY, 0) != -1 && box_flag == 0)
	{
		now_select = select_card2(MouseX, MouseY, 0);
		change_flag = 1;
	}

	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_card2(MouseX, MouseY,0) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//休業
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		get_income = 0;
		target = now_select;
		for (i = 0; i < number_of_player; i++)
		{
			for (j = 0; j < m_Player[i].facility_Num; j++)
			{
				if (m_Player[i].m_Facility[j].card == target)
				{
					m_Player[i].m_Facility[j].Holiday_flag = 1;
					get_income++;
				}
			}
		}
		box_flag = 0;
		box_erase_flag = 1;
		income_processing(35, now_turn, get_income);	
		phase = 4;
	}
}


static void business_initialize()
{
	int i, j, k, s, t, have_flag;
	target_player = -1, target_get = -1, target_send = -1;

	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < have_box_x; j++)
		{
			for (k = 0; k < number_of_player; k++)
			{
				have_box[i][j][k] = -1;
			}
		}
	}


	for (j = 0; j < number_of_player; j++)
	{
		s = 0;
		for (k = 0; k < m_Player[j].facility_Num; k++)
		{
			for (i = 0; i < card_syurui; i++)
			{
				have_flag = 0;
				if (m_Player[j].m_Facility[k].card == i && m_Supply[i].type != 4)
				{
					have_box[s / have_box_x][s % have_box_x][j] = i;
					have_flag = 1;
				}
				if (have_flag == 1)s++;
			}
		}
	}
	phase = 14;
}

static void business_use()
{
	int i;

	if (select_card2(MouseX, MouseY,select_player) != -1 && box_flag == 0)
	{
		now_select = select_card2(MouseX, MouseY,select_player);
		change_flag = 1;
	}
	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_card2(MouseX, MouseY,select_player) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//交換
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		if (select_player == now_turn) 
		{
			for (i = 0; i < m_Player[now_turn].facility_Num; i++) 
			{
				if (m_Player[now_turn].m_Facility[i].card == now_select)
				{
					target_send = i;
					box_flag = 0;
					box_erase_flag = 1;
					break;
				}
			}
		}
		else 
		{
			for (i = 0; i < m_Player[select_player].facility_Num; i++)
			{
				if (m_Player[select_player].m_Facility[i].card == now_select)
				{
					target_get = i;
					target_player = select_player;
					box_flag = 0;
					box_erase_flag = 1;
					break;
				}
			}
		}
	}
	if (target_send != -1 && target_get != -1)
	{
		m_tmp = m_Player[now_turn].m_Facility[target_send];
		m_Player[now_turn].m_Facility[target_send] = m_Player[target_player].m_Facility[target_get];
		m_Player[target_player].m_Facility[target_get] = m_tmp;
		sprintf_s(message_log[0][message_num[0]], 256, "%sのビジネスセンターが発動", m_Player[now_turn].name);
		message_num[0]++;
		select_player = now_turn;
		phase = 4;
	}
}


static void remodeling_select() 
{
	//窓消去landmark
	box_erase_flag2 = 0;
	if ((box_flag2 == 1) && ((boxX2 > MouseX) || (MouseX > boxX2 + 100) || (boxY2 > MouseY) || (MouseY > boxY2 + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag2 = 0;
		box_erase_flag2 = 1;
	}

	//窓生成landmark
	if (box_erase_flag2 == 0 && select_landmark(MouseX, MouseY) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag2 == 0)
	{
		boxX2 = MouseX + 10;
		boxY2 = MouseY - 60;
		box_flag2 = 1;
	}

	//建設landmark
	if ((box_flag2 == 1) && boxX2 < MouseX && MouseX < boxX2 + 100 && boxY2 < MouseY && MouseY < boxY2 + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag2 = 0;
		remodeling_use();
	}
}

static void remodeling_use()
{
	if (m_Player[now_turn].landmark[now_select2] == 0 || now_select2 == 4) 
	{
		remodeling_select;
	}
	else
	{
		m_Player[now_turn].landmark[now_select2] = 0;
		m_Player[now_turn].landmark_Num--;
		income_processing(27, now_turn, 8);
		phase = 4;
	}
}

static void Exhibition_initialize() 
{
	int i, j, k, s, have_flag;

	for (i = 0; i < have_box_y; i++)
	{
		for (j = 0; j < have_box_x; j++)
		{
			for (k = 0; k < number_of_player; k++)
			{
				have_box[i][j][k] = -1;
			}
		}
	}

	s = 0;
	for (i = 0; i < 4; i++)
	{
		if (card_set[i] == 1)
		{
			for (j = setmin[i]; j <= setMAX[i]; j++)
			{
				if (m_Supply[j].type != 4)
				{
					have_box[s / have_box_x][s % have_box_x][0] = j;
					s++;
				}
			}
		}
	}
	sprintf_s(message_log[0][message_num[0]], 256, "%sの国際展示場が発動", m_Player[now_turn].name);
	message_num[0]++;
	phase = 38;
}

static void Exhibition_use() 
{
	int i, m, target, get_income;

	if (select_card2(MouseX, MouseY, 0) != -1 && box_flag == 0)
	{
		now_select = select_card2(MouseX, MouseY, 0);
		change_flag = 1;
	}

	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_card2(MouseX, MouseY, 0) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//コピー
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
		target = now_select;
		m = 0;
		for (i = 0; i < m_Player[now_turn].facility_Num; i++)
		{
			if (m_Player[now_turn].m_Facility[i].card == 38)
			{
				m = i;
			}
		}
		deck[2][deckn[2]] = 38;
		deckn[2]++;
		shuffle(deck[2], deckn[2]);
		m_Player[now_turn].m_Facility[m] = m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num - 1];
		m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num - 1] = m_default_Facility;
		m_Player[now_turn].facility_Num--;
		phase = 4;
		ignition_card(target, now_turn);
	}
}

static void Disposal_supply_initialize(int Disposal_num) 
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 6; j++)
		{
			Disposal_select[i][j] = 0;
		}
	}
	Disposal_count = 0;
	number_of_disposal = Disposal_num;
	phase = 15;
}

static void Disposal_supply(int Disposal_num)
{
	int s = 0, i,j,k;

	//カードセレクト
	if (select_card(MouseX, MouseY) != -1 && box_flag == 0)
	{
		now_select = select_card(MouseX, MouseY);
		change_flag = 1;
	}
	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}
	//窓生成
	if (box_erase_flag == 0 && select_card(MouseX, MouseY) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}
	//廃棄選択
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				if (now_select == supply[i][j])
				{
					if (Disposal_select[i][j] < supplyn[i][j])
					{
						Disposal_select[i][j]++;
						Disposal_count++;
					}
					else
					{
						Disposal_count -= Disposal_select[i][j];
						Disposal_select[i][j] = 0;
					}
				}
			}
		}
	}
	if (Disposal_count == Disposal_num)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				for (k = 0; k < Disposal_select[i][j];k++)
				{
					PlaySoundMem(SHandle[5], DX_PLAYTYPE_BACK);
					Disposal_box[Disposal_box_num] = supply[i][j];
					Disposal_box_num++;
					supplyn[i][j]--;
				}
			}
		}
		select_player = now_turn;
		phase = 4;
	}
}

static void reform_use() 
{
	int disposal_target = -1;
	
	switch (reform_flag) {
	case 0:
		disposal_target = facility_disposal();
		if ( disposal_target != -1)
		{
			reform_flag = 1;
			cost_buf = m_Supply[disposal_target].cost + 3;
		}
		if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y < MouseY && MouseY < button_y + button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			reform_flag = 2;
		}
		break;
	case 1:	
		extra_build_phase(cost_buf,now_turn);
		break;
	case 2:
		//サプライ
		if (select_card(MouseX, MouseY) != -1 && box_flag == 0 && facility_view_flag != 1)
		{
			now_select = select_card(MouseX, MouseY);
			change_flag = 1;
			butsugiri(m_Supply[now_select].c_txt, width, FontHandle, begin, end, &gyosu);
		}
		//施設
		if (select_facility(MouseX, MouseY) != -1 && box_flag == 0 && facility_view_flag != 1)
		{
			now_select = select_facility(MouseX, MouseY);
			change_flag = 1;
			butsugiri(m_Supply[now_select].c_txt, width, FontHandle, begin, end, &gyosu);
		}
		//ランドマーク
		if (select_landmark(MouseX, MouseY) != -1 && box_flag2 == 0)
		{
			now_select2 = select_landmark(MouseX, MouseY);
			change_flag = 2;
			butsugiri(m_Landmark[now_select2].c_txt, width, FontHandle, begin, end, &gyosu);
		}
		if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y < MouseY && MouseY < button_y + button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			reform_flag = 0;
		}
		break;
	}
}

static void food_stand_initialize(int player)
{
	int i, m;

	m = 0;
	for (i = 0; i < m_Player[player].facility_Num; i++)
	{
		if (m_Player[player].m_Facility[i].card == 44)
		{
			m = i;
		}
	}
	sprintf_s(message_log[0][message_num[0]], 256, "%sの祭りの屋台が発動", m_Player[player].name);
	message_num[0]++;
	m_Player[player].m_Facility[m] = m_Player[player].m_Facility[m_Player[player].facility_Num - 1];
	m_Player[player].m_Facility[m_Player[player].facility_Num - 1] = m_default_Facility;
	m_Player[player].facility_Num--;
	PlaySoundMem(SHandle[5], DX_PLAYTYPE_BACK);
	Disposal_box[Disposal_box_num] = 44;
	Disposal_box_num++;
	phase = 44;
	select_player = player;
	target_player = player;
	cost_buf = m_Player[now_turn].landmark_Num + 1;
}

static void food_stand_use()
{
	extra_build_phase(cost_buf,target_player);
}

static int facility_disposal()
{
	int i, target = -1;

	if (select_facility2(MouseX, MouseY,now_turn) != -1 && box_flag == 0)
	{
		now_select = select_facility2(MouseX, MouseY,now_turn);
		change_flag = 1;
	}

	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_facility2(MouseX, MouseY, now_turn) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//廃棄
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		for (i = 0; i < m_Player[now_turn].facility_Num; i++)
		{
			if (m_Player[now_turn].m_Facility[i].card == now_select)
			{
				box_flag = 0;
				box_erase_flag = 1;
				target = i;
				box_flag = 0;
				box_erase_flag = 1;
				break;
			}
		}
	}
	if (target != -1)
	{
		PlaySoundMem(SHandle[5], DX_PLAYTYPE_BACK);
		Disposal_box[Disposal_box_num] = now_select;
		Disposal_box_num++;
		m_Player[now_turn].m_Facility[target] = m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num - 1];
		m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num - 1] = m_default_Facility;
		m_Player[now_turn].facility_Num--;
		return now_select;
	}
	else return -1;
}

static void Land_speculator_initialize() 
{
	select_player = (now_turn + 1) % number_of_player;
	sprintf_s(message_log[0][message_num[0]], 256, "%sの地上げ屋が発動", m_Player[now_turn].name);
	message_num[0]++;
	phase = 46;
}

static void Land_speculator_use()
{

	int i,wd, target = -1;

	if (select_facility2(MouseX, MouseY, select_player) != -1 && box_flag == 0)
	{
		now_select = select_facility2(MouseX, MouseY, select_player);
		change_flag = 1;
	}

	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_facility2(MouseX, MouseY, select_player) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0 && select_player != now_turn && m_Supply[now_select].type != 4)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//戻す
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		for (i = 0; i < m_Player[select_player].facility_Num; i++)
		{
			if (m_Player[select_player].m_Facility[i].card == now_select)
			{
				box_flag = 0;
				box_erase_flag = 1;
				target = i;
				box_flag = 0;
				box_erase_flag = 1;
				break;
			}
		}
	}
	if (target != -1)
	{
		wd = 0;
		if (m_Supply[now_select].dice >= 64)wd = 1;
		deck[wd][deckn[wd]] = now_select;
		deckn[wd]++;
		shuffle(deck[wd], deckn[wd]);
		m_Player[select_player].m_Facility[target] = m_Player[select_player].m_Facility[m_Player[select_player].facility_Num - 1];
		m_Player[select_player].m_Facility[m_Player[select_player].facility_Num - 1] = m_default_Facility;
		m_Player[select_player].facility_Num--;
		m_Player[select_player].coin += m_Supply[now_select].cost;
		select_player = now_turn;
		phase = 4;
	}
}

static void theme_park_initialize()
{
	select_player = (now_turn + 1) % number_of_player;
	sprintf_s(message_log[0][message_num[0]], 256, "%sのテーマパークが発動", m_Player[now_turn].name);
	message_num[0]++;
	phase = 47;
}

static void theme_park_use()
{

	int i, target = -1;

	if (select_facility2(MouseX, MouseY, select_player) != -1 && box_flag == 0)
	{
		now_select = select_facility2(MouseX, MouseY, select_player);
		change_flag = 1;
	}

	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_facility2(MouseX, MouseY, select_player) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0 && select_player != now_turn && m_Supply[now_select].type != 4)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//買う
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		if (m_Player[now_turn].coin >= m_Supply[now_select].cost)
		{
			for (i = 0; i < m_Player[select_player].facility_Num; i++)
			{
				if (m_Player[select_player].m_Facility[i].card == now_select)
				{
					box_flag = 0;
					box_erase_flag = 1;
					target = i;
					box_flag = 0;
					box_erase_flag = 1;
					break;
				}
			}
		}
		else imposible_flag = 1;
	}
	if (target != -1)
	{
		m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num] = m_Player[select_player].m_Facility[target];
		m_Player[now_turn].facility_Num++;
		m_Player[select_player].m_Facility[target] = m_Player[select_player].m_Facility[m_Player[select_player].facility_Num - 1];
		m_Player[select_player].m_Facility[m_Player[select_player].facility_Num - 1] = m_default_Facility;
		m_Player[select_player].facility_Num--;
		m_Player[now_turn].coin -= m_Supply[now_select].cost;
		m_Player[select_player].coin += m_Supply[now_select].cost;
		select_player = now_turn;
		phase = 4;
	}
}

static void general_contractor_initialize()
{
	select_player = (now_turn + 1) % number_of_player;
	sprintf_s(message_log[0][message_num[0]], 256, "%sの土建屋が発動", m_Player[now_turn].name);
	message_num[0]++;
	phase = 48;
}

static void general_contractor_use()
{
	//窓消去landmark
	box_erase_flag2 = 0;
	if ((box_flag2 == 1) && ((boxX2 > MouseX) || (MouseX > boxX2 + 100) || (boxY2 > MouseY) || (MouseY > boxY2 + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag2 = 0;
		box_erase_flag2 = 1;
	}

	//窓生成landmark
	if (box_erase_flag2 == 0 && select_landmark(MouseX, MouseY) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag2 == 0 && select_player != now_turn)
	{
		boxX2 = MouseX + 10;
		boxY2 = MouseY - 60;
		box_flag2 = 1;
	}

	//landmark
	if ((box_flag2 == 1) && boxX2 < MouseX && MouseX < boxX2 + 100 && boxY2 < MouseY && MouseY < boxY2 + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag2 = 0;
		if (m_Player[select_player].landmark[now_select2] != 0 && now_select2 != 4)
		{
			m_Player[select_player].landmark[now_select2] = 0;
			m_Player[select_player].landmark_Num--;
			m_Player[select_player].coin += m_Landmark[now_select2].cost;
			select_player = now_turn;
			phase = 4;
		}
	}
}

static void build_phase()
{
	if (m_Player[now_turn].landmark[4] == 1 && m_Player[now_turn].coin == 0)
	{
		m_Player[now_turn].coin++;
		sprintf_s(message_log[0][message_num[0]], 256, "%sの役所が発動", m_Player[now_turn].name);
		message_num[0]++;
		landmark_ignition_display(4);
	}
	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}

	//窓生成
	if (box_erase_flag == 0 && select_card(MouseX, MouseY) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}

	//建設
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		supply_build();
	}


	//窓消去landmark
	box_erase_flag2 = 0;
	if ((box_flag2 == 1) && ((boxX2 > MouseX) || (MouseX > boxX2 + 100) || (boxY2 > MouseY) || (MouseY > boxY2 + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag2 = 0;
		box_erase_flag2 = 1;
	}

	//窓生成landmark
	if (box_erase_flag2 == 0 && select_landmark(MouseX, MouseY) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag2 == 0)
	{
		boxX2 = MouseX + 10;
		boxY2 = MouseY - 60;
		box_flag2 = 1;
	}

	//建設landmark
	if ((box_flag2 == 1) && boxX2 < MouseX && MouseX < boxX2 + 100 && boxY2 < MouseY && MouseY < boxY2 + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		landmark_build();
	}

	if (build_count == 0)phase = 7;
	
	//パス
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide * 2 < MouseY && MouseY < button_y + button_y_wide * 3 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		if (m_Player[now_turn].landmark[6] == 1)
		{
			m_Player[now_turn].coin += 10;
			sprintf_s(message_log[0][message_num[0]], 256, "%sの空港が発動", m_Player[now_turn].name);
			message_num[0]++;
			landmark_ignition_display(6);
		}
		phase = 7;
	}
}

static void extra_build_phase(int Expenses, int player)
{
	//カードセレクト
	if (select_card(MouseX, MouseY) != -1 && box_flag == 0)
	{
		now_select = select_card(MouseX, MouseY);
		change_flag = 1;
		butsugiri(m_Supply[now_select].c_txt, width, FontHandle, begin, end, &gyosu);
	}
	if (select_facility(MouseX, MouseY) != -1 && box_flag == 0)
	{
		now_select = select_facility(MouseX, MouseY);
		change_flag = 1;
		butsugiri(m_Supply[now_select].c_txt, width, FontHandle, begin, end, &gyosu);
	}
	if (select_landmark(MouseX, MouseY) != -1 && box_flag2 == 0)
	{
		now_select2 = select_landmark(MouseX, MouseY);
		change_flag = 2;
		butsugiri(m_Landmark[now_select2].c_txt, width, FontHandle, begin, end, &gyosu);
	}
	//窓消去
	box_erase_flag = 0;
	if ((box_flag == 1) && ((boxX > MouseX) || (MouseX > boxX + 100) || (boxY > MouseY) || (MouseY > boxY + 50)) && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		box_flag = 0;
		box_erase_flag = 1;
	}
	//窓生成
	if (box_erase_flag == 0 && select_card(MouseX, MouseY) != -1 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0 && box_flag == 0)
	{
		boxX = MouseX + 10;
		boxY = MouseY - 60;
		box_flag = 1;
	}
	//建設
	if ((box_flag == 1) && boxX < MouseX && MouseX < boxX + 100 && boxY < MouseY && MouseY < boxY + 25 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		extra_build(Expenses, player);
	}
	//パス
	if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide * 2 < MouseY && MouseY < button_y + button_y_wide * 3 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
	{
		phase = 4;
	}
}

static void extra_build(int Expenses,int player)
{

	int i, j;

	for (i = 0; i < m_Player[player].facility_Num; i++)
	{
		if (m_Player[player].m_Facility[i].card == now_select && m_Supply[now_select].type == 4)
		{
			rebuild_flag = 1;
			box_flag = 0;
			return;
		}
	}
	if (Expenses >= m_Supply[now_select].cost)
	{
		if (now_select == 29)m_Player[player].coin += 5;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				if (now_select == supply[i][j])
				{
					m_Player[player].m_Facility[m_Player[player].facility_Num] = { supply[i][j] ,0,0 };
					supplyn[i][j]--;
					m_Player[player].facility_Num++;
				}
			}
		}
		PlaySoundMem(SHandle[2], DX_PLAYTYPE_BACK);
		select_player = now_turn;
		phase = 4;
	}
	else imposible_flag = 1;
	box_flag = 0;
}

static void supply_build()
{
	int i, j;

	for (i = 0; i < m_Player[now_turn].facility_Num; i++)
	{
		if (m_Player[now_turn].m_Facility[i].card == now_select && m_Supply[now_select].type == 4)
		{
			rebuild_flag = 1;
			box_flag = 0;
			return;
		}
	}
	if (m_Player[now_turn].coin >= m_Supply[now_select].cost)
	{
		m_Player[now_turn].coin -= m_Supply[now_select].cost;
		if(now_select == 29)m_Player[now_turn].coin += 5;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < open_num[i]; j++)
			{
				if (now_select == supply[i][j])
				{
					m_Player[now_turn].m_Facility[m_Player[now_turn].facility_Num] = { supply[i][j] ,0,0};
					supplyn[i][j]--;
					m_Player[now_turn].facility_Num++;
				}
			}
		}
		PlaySoundMem(SHandle[2], DX_PLAYTYPE_BACK);
		build_count--;
	}
	else imposible_flag = 1;
	box_flag = 0;
}

static void landmark_build()
{
	if (m_Player[now_turn].landmark[now_select2] == 1)rebuild_flag = 1;
	else if (m_Player[now_turn].coin >= m_Landmark[now_select2].cost)
	{
		m_Player[now_turn].coin -= m_Landmark[now_select2].cost;
		m_Player[now_turn].landmark[now_select2] = 1;
		m_Player[now_turn].landmark_Num++;
		build_count--;
	}
	else imposible_flag = 1;
	box_flag2 = 0;
}

static void end_phase() 
{
	int i,IT_flag;

	IT_flag = 0;

	for (i = 0; i < m_Player[now_turn].facility_Num; i++)
	{
		if (m_Player[now_turn].m_Facility[i].card == 36)
		{
			IT_flag = 1;
		}
	}

	if (IT_flag == 1) phase = 36;
	else turn_update();
}

static void IT_use()
{
	if (IT_mode[now_turn] == 0)
	{
		//ITにコイン乗せる
		if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y < MouseY && MouseY < button_y + button_y_wide && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			if (m_Player[now_turn].coin >= 1)
			{
				m_Player[now_turn].coin--;
				m_Player[now_turn].IT++;
			}
			else imposible_flag = 1;
			turn_update();
		}
		//ITにコイン乗せない
		if (button_x < MouseX && MouseX < button_x + button_x_wide && button_y + button_y_wide < MouseY && MouseY < button_y + button_y_wide * 2 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			turn_update();
		}
	}
	else if (IT_mode[now_turn] == 1)
	{
		if (m_Player[now_turn].coin >= 1)
		{
			m_Player[now_turn].coin--;
			m_Player[now_turn].IT++;
		}
		turn_update();
	}
	else if (IT_mode[now_turn] == 2)
	{
		turn_update();
	}
}

static void turn_update()
{
	if (park_flag == 0) turn++;
	else park_flag = 0;
	phase = 1;
	build_count = 1;
	message_initialize();
	select_player = turn % number_of_player;
	PlaySoundMem(SHandle[8], DX_PLAYTYPE_BACK);
}

static void win()
{
	int i;
	for (i = 0; i < number_of_player; i++)
	{
		if (m_Player[i].landmark_Num == land_set_num)win_flag = i;
	}
	if (win_flag != -1)
	{
		StopSoundMem(SHandle[9]);
		phase = 6;
		PlaySoundMem(SHandle[10], DX_PLAYTYPE_LOOP);
	}
}

static void win_phase()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)SceneMgr_ChangeScene(eScene_Menu);;
}


void GradX_RGB(int x1, int y1, int x2, int y2, BYTE r1, BYTE g1, BYTE b1, BYTE r2, BYTE g2, BYTE b2)
{
	VERTEX2D Vertex[6];

	// 左上の頂点の情報をセット( 1ポリゴン目の第1頂点 )
	Vertex[0].pos.x = (float)x1;
	Vertex[0].pos.y = (float)y1;
	Vertex[0].pos.z = 0.0f;
	Vertex[0].rhw = 1.0f;
	Vertex[0].dif.r = r1;
	Vertex[0].dif.g = g1;
	Vertex[0].dif.b = b1;
	Vertex[0].dif.a = 255;
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;

	// 右上の頂点の情報をセット( 1ポリゴン目の第2頂点 )
	Vertex[1].pos.x = (float)x2;
	Vertex[1].pos.y = (float)y1;
	Vertex[1].pos.z = 0.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[1].dif.r = r1;
	Vertex[1].dif.g = g1;
	Vertex[1].dif.b = b1;
	Vertex[1].dif.a = 255;
	Vertex[1].u = 0.0f;
	Vertex[1].v = 0.0f;

	// 左下の頂点の情報をセット( 1ポリゴン目の第3頂点 )
	Vertex[2].pos.x = (float)x1;
	Vertex[2].pos.y = (float)y2;
	Vertex[2].pos.z = 0.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[2].dif.r = r2;
	Vertex[2].dif.g = g2;
	Vertex[2].dif.b = b2;
	Vertex[2].dif.a = 255;
	Vertex[2].u = 0.0f;
	Vertex[2].v = 0.0f;

	// 右下の頂点の情報をセット( 2ポリゴン目の第1頂点 )
	Vertex[3].pos.x = (float)x2;
	Vertex[3].pos.y = (float)y2;
	Vertex[3].pos.z = 0.0f;
	Vertex[3].rhw = 1.0f;
	Vertex[3].dif.r = r2;
	Vertex[3].dif.g = g2;
	Vertex[3].dif.b = b2;
	Vertex[3].dif.a = 255;
	Vertex[3].u = 0.0f;
	Vertex[3].v = 0.0f;

	// 2ポリゴン目の第2頂点は左下の頂点なのでコピー
	Vertex[4] = Vertex[2];

	// 2ポリゴン目の第3頂点は右上の頂点なのでコピー
	Vertex[5] = Vertex[1];

	// ポリゴンを2個描画
	DrawPolygon2D(Vertex, 2, DX_NONE_GRAPH, FALSE);
}

void butsugiri(char moji[], int wide, int FontHandle, int *begin, int *end, int *gyosu)
{
	int i, j = 0, k = 0, width = 0;

	for (i = 0; i < 20; i++)
	{
		begin[i] = 0;
		end[i] = 0;
	}
	for (i = 0; moji[i] != '\0'; ++i)
	{
		unsigned char c = moji[i];
		char string[3] = { 0 };

		if (((c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xfc)) && moji[i + 1] != '\0')
		{
			// 2byte文字
			string[0] = c;
			string[1] = moji[i + 1];
			++i;
			width += GetDrawStringWidthToHandle(string, 1, FontHandle);
		}
		else {
			// 1byte文字
			string[0] = c;
			width += GetDrawStringWidthToHandle(string, 1, FontHandle);
		}
		if (width >= wide)
		{
			end[k] = i;
			k++;
			begin[k] = i + 1;
			width = 0;
			j++;
		}
	}
	end[k] = i;
	*gyosu = j + 1;
}

void KaigyoDraw(int x, int y, int gyosu, int gyokan, int Color, int FontHandle, char moji[], int begin[], int end[])
{
	int i, j, k;
	char string[30][256] = { 0 };

	for (i = 0; i < gyosu; i++)
	{
		k = 0;
		for (j = begin[i]; j <= end[i]; j++)
		{
			string[i][k] = moji[j];
			k++;
		}
		DrawFormatStringToHandle(x, y + i * gyokan, Color, FontHandle, "%s", string[i]);
	}
}
