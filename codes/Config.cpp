#include "Config.h"
#include "Config_2.h"
#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "math.h"

#define MENU_NUM 13

static int MouseX, MouseY, White, OldMouseOshita, Count;
static int GHandle[3];
static int SHandle[12];
static int x_posi = 100,y_posi = 50,y_wide = 80,y_wide2 = 50,x_wide2 = 568;
static int FontHandle;
static int FontHandle2;

typedef struct 
{
	int x, y;
	char name[128];
	int flag_type;
	int flag;
	int flag_num;
} MenuElement_t;

MenuElement_t MenuElement[MENU_NUM] = {
	{ x_posi + 50, y_posi, "�v���C���[�ݒ�" ,0,0,0 },
	{ x_posi, y_posi + y_wide2, "�v���C�l��:" ,4,2,3},
	{ x_posi, y_posi + y_wide2 * 2, "CPU��(������):" ,3,0,4},
	{ x_posi + 50, y_posi + y_wide2 * 2 + y_wide, "�ǉ��J�[�h�Z�b�g" ,0,0,0 },
	{ x_posi, y_posi + y_wide2 * 3 + y_wide, "�{:" ,2,1,2},
	{ x_posi, y_posi + y_wide2 * 4 + y_wide, "��:" ,2,1,2},
	{ x_posi, y_posi + y_wide2 * 5 + y_wide, "Custom:" ,2,0,2},
	{ x_posi + x_wide2 + 50, y_posi, "�T�v���C��" ,0,0,0},
	{ x_posi + x_wide2, y_posi + y_wide2, "�U�ȉ�:" ,6,5,6 },
	{ x_posi + x_wide2, y_posi + y_wide2 * 2, "�V�ȏ�:" ,6,5,6 },
	{ x_posi + x_wide2, y_posi + y_wide2 * 3, "��:" ,6,2,6 },
	{ x_posi + x_wide2, y_posi + y_wide2 * 3 + y_wide, "����" ,1,0,2},
	{ x_posi + x_wide2, y_posi + y_wide2 * 4 + y_wide, "�߂�" ,5,0,2}
};

//������
void Config_Initialize() 
{

	FontHandle = CreateFontToHandle(NULL, 16, 8);
	FontHandle2 = CreateFontToHandle(NULL, 26, 10);

	//�摜�̃��[�h
	GHandle[0] = LoadGraph("images/bg_config.png");//�摜�̃��[�h
	GHandle[1] = LoadGraph("images/bg_config2.png");//�摜�̃��[�h

	SHandle[1] = LoadSoundMem("sounds/�J�[�\���ړ�2.mp3");
	SHandle[2] = LoadSoundMem("sounds/����A�{�^������40.mp3");

	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	// ���F�̒l���擾
	White = GetColor(255, 255, 255);

	PlaySoundMem(SHandle[0], DX_PLAYTYPE_LOOP);
}

//�I������
void Config_Finalize() 
{
	int i;
	//�摜�̉��
	for (i = 0; i < 2; i++)
	{
		DeleteGraph(GHandle[i]);//�摜�̉��
	}
	for (i = 0; i < 3; i++)
	{
		DeleteSoundMem(SHandle[i]);
	}
	DeleteFontToHandle(FontHandle);//�t�H���g�f�[�^�̍폜
	DeleteFontToHandle(FontHandle2);//�t�H���g�f�[�^�̍폜
}

//�X�V
void Config_Update() 
{
	// �}�E�X�̈ʒu���擾
	GetMousePoint(&MouseX, &MouseY);

	int i;
	for (i = 0; i < MENU_NUM; i++)
	{
		if (MenuElement[i].x < MouseX && MouseX < MenuElement[i].x + 200 && MenuElement[i].y < MouseY && MouseY < MenuElement[i].y + 30 && (GetMouseInput() & MOUSE_INPUT_LEFT != 0) && OldMouseOshita == 0)
		{
			PlaySoundMem(SHandle[1], DX_PLAYTYPE_BACK);
			switch (MenuElement[i].flag_type)
			{
			case 0:
				break;
			case 1:
				SceneMgr_ChangeScene(eScene_Config_2);//�V�[�����Q�[���ɕύX
				break;
			case 2:
				MenuElement[i].flag = (MenuElement[i].flag + 1) % MenuElement[i].flag_num;
				break;
			case 3:
				MenuElement[i].flag = (MenuElement[i].flag + 1) % MenuElement[1].flag;
				break;
			case 4:
				MenuElement[i].flag = (MenuElement[i].flag - 1) % MenuElement[i].flag_num + 2;
				MenuElement[2].flag = 0;
				break;
			case 5:
				SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
				break;
			case 6:
				MenuElement[i].flag = MenuElement[i].flag % MenuElement[i].flag_num + 1;
				break;
			}
		}
	}
	OldMouseOshita = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

//�`��
void Config_Draw()
{
	int x_wide,i, j;
	x_wide = 200;
	DrawGraph(0, 0, GHandle[0], FALSE);// �摜��`�悷��
	DrawGraph(0, 0, GHandle[1], TRUE);// �摜��`�悷��
	for (i = 0; i < MENU_NUM; i++)
	{
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, White, MenuElement[i].name);
		switch (MenuElement[i].flag_type)
		{
		case 1:
			break;
		case 2:
			if (MenuElement[i].flag == 1)DrawFormatString(MenuElement[i].x + x_wide, MenuElement[i].y, White, "�Z");
			else DrawFormatString(MenuElement[i].x + x_wide, MenuElement[i].y, White, "�~");
			break;
		case 3:
		case 4:
			DrawFormatString(MenuElement[i].x + x_wide, MenuElement[i].y, White, "%d�l", MenuElement[i].flag);
			break;
		case 5:
			break;
		case 6:
			DrawFormatString(MenuElement[i].x + x_wide, MenuElement[i].y, White, "%d��", MenuElement[i].flag);
			break;
		}
	}
	//�}�E�X���W�\��
	DrawFormatString(10, 600, White, "%5d,%5d", MouseX, MouseY);

}

void Config_reflect(int *player_num,int *cpu_num,int card_set[],int open_num[])
{
	int i;
	*player_num = MenuElement[1].flag;
	*cpu_num = MenuElement[2].flag;
	card_set[0] = 1;
	for (i = 1; i <= 3; i++)card_set[i] = MenuElement[i + 3].flag;
	for (i = 0; i < 3; i++)open_num[i] = MenuElement[i + 8].flag;
}