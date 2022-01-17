#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

const static int GAME_Y = 405;    //�u�Q�[���v������y�ʒu
const static int CONFIG_Y = 490;    //�u�ݒ�v������y�ʒu
static int MouseX, MouseY;
static char StrBuf[128], StrBuf2[32];
static int GHandle[3];
static int StringCr, BoxCr;
static int OldMouseOshita;
static int FontHandle;
static int SHandle[4];


typedef enum 
{
	eMenu_Config,        //�Q�[��
	eMenu_Custom,    //�ݒ�

	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Config;    //���݂̑I�����(�����̓Q�[���I��)

						//������
void Menu_Initialize() 
{
	//�摜�̃��[�h
	GHandle[0] = LoadGraph("images/bg_menu.png");//�摜�̃��[�h

	FontHandle = CreateFontToHandle(NULL, 50, 3);

	SHandle[0] = LoadSoundMem("sounds/bgm_menu.mp3");
	SHandle[1] = LoadSoundMem("sounds/menu.wav");
	SHandle[2] = LoadSoundMem("sounds/playerenter.wav");

	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	// ���F�̒l���擾
	StringCr = GetColor(255, 255, 255);

	// ���̒l���擾
	BoxCr = GetColor(0, 0, 0);

	PlaySoundMem(SHandle[0], DX_PLAYTYPE_LOOP);
}

//�I������
void Menu_Finalize() 
{
	int i;
	//�摜�̉��
	for (i = 0; i < 1; i++)
	{
		DeleteGraph(GHandle[i]);//�摜�̉��
	}
	for (i = 0; i < 3; i++)
	{
		DeleteSoundMem(SHandle[i]);
	}
}

//�X�V
void Menu_Update() 
{
	// �}�E�X�̈ʒu���擾
	GetMousePoint(&MouseX, &MouseY);
	
	/*
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Config://�Q�[���I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Config);//�V�[�����Q�[����ʂɕύX
			break;
		case eMenu_Custom://�ݒ�I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Custom);//�V�[����ݒ��ʂɕύX
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
	// �\�����镶������쐬
	{
		lstrcpy(StrBuf, "���W �w"); // ������"���W �w"��StrBuf�ɃR�s�[	
		itoa(MouseX, StrBuf2, 10); // MouseX�̒l�𕶎���ɂ���StrBuf2�Ɋi�[
		lstrcat(StrBuf, StrBuf2); // StrBuf�̓��e��StrBuf2�̓��e��t������
		lstrcat(StrBuf, "�@�x "); // StrBuf�̓��e�ɕ�����"�x"��t������
		itoa(MouseY, StrBuf2, 10); // MouseY�̒l�𕶎���ɂ���StrBuf2�Ɋi�[
		lstrcat(StrBuf, StrBuf2); // StrBuf�̓��e��StrBuf2�̓��e��t������
	}
	OldMouseOshita = (GetMouseInput() & MOUSE_INPUT_LEFT);
}

//�`��
void Menu_Draw() 
{
	DrawGraph(0, 0, GHandle[0], FALSE);// �摜��`�悷��
	int y = 0;
	switch (NowSelect) 
	{//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Config://�Q�[���I�𒆂Ȃ�
		y = GAME_Y;    //�Q�[���̍��W���i�[
		break;
	case eMenu_Custom://�ݒ�I�𒆂Ȃ�
		y = CONFIG_Y;    //�ݒ�̍��W���i�[
		break;
	}
	DrawStringToHandle(350, GAME_Y, "GAME",BoxCr, FontHandle);
	DrawStringToHandle(350, CONFIG_Y, "CONFIG", BoxCr, FontHandle);
	DrawStringToHandle(285, y, "��", BoxCr, FontHandle);
	// ��ʍ���̗̈�ɍ����l�p��`���O�ɕ`���Ă�����
	// �����������
	//DrawBox(0, 0, 200, 32, BoxCr, TRUE);
	// ���W�������`��
	//DrawString(0, 0, StrBuf, StringCr);
}
