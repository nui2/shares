#pragma once

//初期化
void Config_Initialize();

//終了処理
void Config_Finalize();

//更新
void Config_Update();

//描画
void Config_Draw();

//設定反映
void Config_reflect(int *player_num, int *cpu_num, int *card_set,int *open_num);
