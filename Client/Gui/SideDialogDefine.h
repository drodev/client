#pragma once

// Dilaog�� �ε����� ��ġ�� �ʵ��� �����Ѵ�
enum eSideDialogType
{
	SDIALOG_FIRST = 500,
	

	// �⺻������ ��Ȳ�� �´ٸ� �׻� ��������� ���̾�α�
	SDIALOG_DEFAULT_FIRST = SDIALOG_FIRST,

	SDIALOG_RANKBATTLE_INFO = SDIALOG_DEFAULT_FIRST,	///< ��ũ��Ʋ ����â
	SDIALOG_BUDOKAI_MINORMATCH_INFO,			///< õ������ ����ȸ ��������â
	SDIALOG_BUDOKAI_MAJORMATCH_INFO,			///< õ������ ����ȸ ��������â
	SDIALOG_BUDOKAI_FINALMATCH_INFO,			///< õ������ ����ȸ �ἱ����â
	SDIALOG_QUEST_INDICATOR,					///< �⺻ ����Ʈ �ε�������
	SDIALOG_TMQ_STATUS,							///< TMQ ���� ����â
	SDIALOG_SCRAMBLE_STATUS,					///< ���� ��Ż ����â
	SDIALOG_SCS_AUTOCHECK,						///< AutoCheck ����â
	SDIALOG_CCBD_STATUS,

	SDIALOG_DEFAULT_LAST = SDIALOG_CCBD_STATUS,
	

	// Event Dialog
	SDIALOG_EVENT_FIRST,

    SDIALOG_SCOUTER_PC_VIEWER = SDIALOG_EVENT_FIRST, ///< ��ī���� PC ��񺸱�
	
	SDIALOG_EVENT_LAST = SDIALOG_SCOUTER_PC_VIEWER,    


	// ������ ���ۿ� ���� ȭ�鿡 �׷����� ���̾�α�
	SDIALOG_NORMAL_FIRST = SDIALOG_EVENT_LAST,	///< �̰��� ���̾�αװ� ���ǵ� ������
	//SDIALOG_NORMAL_FIRST,

	SDIALOG_NORMAL_LAST = SDIALOG_NORMAL_FIRST,


	SDIALOG_LAST = SDIALOG_NORMAL_LAST,

	SDIALOG_UNKNOWN								///< �߸��� ���̾�α� �ε���
};

// side dialog attribute
#define dSDA_NONE							0x00000000
#define dSDA_INDEPENDENTLY					0x00000001	///< �ٸ� ���̵� ���̾�α׿� �ڸ��� ���� ������ ���� ���� �ʴ´�
#define dSDA_FREE_Y_POSITION				0x00000002	///< ���̵� ���̾�α׿� ���ؼ� Y��ǥ�� �������� �ʰ� ���� ���̾�α��� ���̷� �����Ѵ�

// side dialog default font color
#define SIDE_DIALOG_FONT_GREEN_COLOR_RED	131
#define SIDE_DIALOG_FONT_GREEN_COLOR_GREEN	255
#define SIDE_DIALOG_FONT_GREEN_COLOR_BLUE	143
#define SIDE_DIALOG_FONT_GREEN_COLOR		RGB(SIDE_DIALOG_FONT_GREEN_COLOR_RED,SIDE_DIALOG_FONT_GREEN_COLOR_GREEN,SIDE_DIALOG_FONT_GREEN_COLOR_BLUE)

#define SIDE_DIALOG_FONT_YELLOW_COLOR_RED	253
#define SIDE_DIALOG_FONT_YELLOW_COLOR_GREEN	243
#define SIDE_DIALOG_FONT_YELLOW_COLOR_BLUE	107
#define SIDE_DIALOG_FONT_YELLOW_COLOR		RGB(SIDE_DIALOG_FONT_YELLOW_COLOR_RED,SIDE_DIALOG_FONT_YELLOW_COLOR_GREEN,SIDE_DIALOG_FONT_YELLOW_COLOR_BLUE)