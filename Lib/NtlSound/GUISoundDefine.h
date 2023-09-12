/******************************************************************************
* File			: GUISoundDefine.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 2. 21
* Abstract		: 
*****************************************************************************
* Desc			: System���� ���̴� ���� ������ �̸��� ����
*****************************************************************************/

#pragma once

#include "NtlSoundManager.h"


#define GSD_SYSTEM_ICON_SET					"System\\SYSTEM_ICON_SET.wav"
///< Skill Icon, etc. to put in the Quick Slot. "Patch"

#define GSD_SYSTEM_ICON_SELECT				"System\\SYSTEM_ICON_SELECT.wav"
///< The sound when I picked Icon.

#define GSD_SYSTEM_ICON_WASTE				"System\\SYSTEM_ICON_WASTE.wav"	
///< Icon�� Quick Slot�κ��� ������ ���� �Ҹ�.��ī�衹.(���̸� �������뿡 �־��� ���� �̹�����.)

#define GSD_SYSTEM_BUTTON_CLICK				"System\\SYSTEM_BUTTON_CLICK.wav"
///< Button�� ������ ���� Click��.��īġ��.

#define GSD_SYSTEM_BUTTON_CANCEL			"System\\SYSTEM_BUTTON_CANCEL.wav"
///< Cancel�� ������ ���� �Ҹ�.��Ʈ��.

#define GSD_SYSTEM_BUTTON_FOCUS				"System\\SYSTEM_Button_Focus.wav"
///< ��ư Focus �Ǿ��� ���� �Ҹ�.

#define GSD_SYSTEM_BUTTON_DISABLE			"System\\SYSTEM_Button_Disable_Alarm.wav"
///< Disable ��ư Click �Ǿ��� ���� �Ҹ�.

#define GSD_SYSTEM_WINDOW_OPEN				"System\\SYSTEM_WINDOW_OPEN.wav"
///< Window�� ���� ���� �Ҹ�.������.

#define GSD_SYSTEM_WINDOW_CLOSE				"System\\SYSTEM_WINDOW_CLOSE.wav"
///< Window�� ���� ���� �Ҹ�.���衹.

#define GSD_SYSTEM_ITEM_REPAIR				"System\\SYSTEM_ITEM_REPAIR.wav"
///< Item ���� ���� �Ҹ�.��ĵ��.(���尣�� �̹�����.)

#define GSD_SYSTEM_WINDOW_ALERT				"System\\SYSTEM_WINDOW_ALART.wav"
///< ��� Window�� ���� ���� �Ҹ�.���.

#define GSD_SYSTEM_NOTICE					"System\\SYSTEM_NOTICE.wav"
///< ȭ�鿡 ���� ���� �˸��� Message�� ������ ���� �Ҹ�.����!��.

#define GSD_SYSTEM_ITEM_SPEND				"System\\SYSTEM_ITEM_SPEND.wav"
///< �Һ� Item�� ����� �������� ���� �Ҹ�.��������.

#define GSD_SYSTEM_ITEM_EQUIP				"System\\SYSTEM_ITEM_EQUIP.wav"
///< ��� Item�� ������� ���� �Ҹ�.����衹.(�ʿ� �ҸŸ� ���ϴ� �̹���.)

#define GSD_SYSTEM_ITEM_TAKEOFF				"System\\SYSTEM_ITEM_TAKEOFF.wav"
///< ��� Item�� �������� ���� �Ҹ�.���衹.(�ʿ� �ҸŸ� ���ϴ� �̹���.)

#define GSD_SYSTEM_TAB_CLICK				"System\\SYSTEM_TAB_CLICK.wav"
///< Tab�� �������� ���� Sound.���衹.(���̸� ���Ƴ��� �̹���.)

//******************************************��ȭ�� �ʿ���.....?
#define GSD_SYSTEM_POPUPWINDOW_OPEN			"System\\SYSTEM_POPWIN_OPEN.wav"
///< PopWindow ���� ���� �Ҹ�

#define GSD_SYSTEM_POPUPWINDOW_CLOSE		"System\\SYSTEM_POPWIN_CLOSE.wav"
///< PopWindow ���� ���� �Ҹ�

#define GSD_SYSTEM_TAB_FOCUS				"System\\SYSTEM_TAB_FOCUS.wav"
//< Tab ���콺�� �ö����� �Ҹ�

#define GSD_SYSTEM_TREE_OPEN				"System\\SYSTEM_TREE_OPEN.wav"
//< Ʈ���� ��������

#define GSD_SYSTEM_TREE_CLOSE				"System\\SYSTEM_TREE_CLOSE.wav"
//< Ʈ���� ��������

#define GSD_SYSTEM_TUTORIAL_MSGBOX			"System\\TUTORIAL_MSGBOX.wav"
//< tutorial msgbox 

#define GSD_SYSTEM_CHECKBOX					"System\\GENERAL_CHKBOX.wav"
//< üũ�ڽ� üũ�ɶ�

//******************************************�Ϸ�

#define GSD_SYSTEM_MESSAGEBOX				"System\\SYSTEM_MSGBOX.wav"
//#define GSD_SYSTEM_MESSAGEBOX				""
/////< MES Box ���ö��� �Ҹ�.
//
#define GSD_SYSTEM_ENEMY_SELECT				"System\\SYSTEM_ENEMY_FOCUS.wav"	
////<��������������
//
#define GSD_SYSTEM_ENEMY_FOUSE				"System\\SYSTEM_ENEMY_SELECT.wav"	
////<���� ���콺�� �÷� ��������
//
#define GSD_SYSTEM_CHARACTER_ROTATE			"System\\SYSTEM_CHAR_ROTATE.wav"
/////< Character  ȸ��
//
#define GSD_SYSTEM_PARTS_EQUIP				"System\\SYSTEM_EQUIP.wav"	
////< ��ī��Ʈ ���� �����Ҷ�
//
#define GSD_SYSTEM_ABILITY_UI_OPEN			"System\\SYSTEM_SKILL_OPEN.wav"
////< ��ų �����Ƽ UI��Ÿ����
//
#define GSD_SYSTEM_GUARD_GAGE				"System\\SYSTEM_GUARD_GAGEDOWN.wav"
////< ���� �������� �پ�鶧
//
#define GSD_SYSTEM_GUARD_GAGE_END			"System\\SYSTEM_GUARD_GAGEDOWN_END.wav"
////< ���� �������� �پ�鶧
//

#define GSD_SYSTEM_PUBLIC_NOTIFY			"System\\SYSTEM_NOTICE.wav"	
///< ������ �㶧 �˶���

#define GSD_SYSTEM_ACTION_NOTIFY			"System\\SYSTEM_NOTICE_ACTION.wav"
/////< � �ൿ�� ����� ���� ������ �˸���
//
#define GSD_SYSTEM_WARNING_NOTIFY			"System\\SYSTEM_NOTICE_WARNING.wav"
/////< �ؼ��� �ȵǴ� �ൿ�� ���� ���� �˸���				ps. Class �� CCautionNotifyGui ��
//
#define GSD_SYSTEM_PARTY_NOTIFY				"System\\SYSTEM_NOTICE_PARTY.wav"
/////< ��Ƽ�Ǵ� ��忡�� ������ �θ� ���� �˸���
//
#define GSD_SYSTEM_TERRAIN_NOTIFY			"System\\SYSTEM_NOTICE_TERRAIN.wav"	

/////< ���ο� ������ ������ �����̸��� �˷��ִ� �˸���
//
#define GSD_SYSTEM_ITEM_LIGHT_ON			"System\\SYSTEM_ITEM_UPGRADE.wav"

////< �Ӽ��� �´� ������ ���Ҷ� ( ���׷��̵� ������ �������� �̵��� )

#define GSD_SYSTEM_KEY_DOWN					"System\\GENERAL_TEXTINPUT.wav"
//< Ÿ�� ġ�� �Ҹ�

//
#define GSD_SYSTEM_DRAGOBALL_UI_OPEN		"System\\SYSTEM_DB_OPEN.wav"	

////< �巡�ﺼ ���� ������
//
#define GSD_SYSTEM_DRAGOBALL_UI_CLOSE		"System\\SYSTEM_DB_CLOSE.wav"	
	
////< �巡�ﺼ ���� ������
//
#define GSD_SYSTEM_POTAL_ICON_MOUSE_OVER	"System\\SYSTEM_PORTAL_MOUSE_OVER.wav"

#define GSD_SYSTEM_MOUSE_CLICK_HV			"System\\SYSTEM_MOUSE_CLICK_HV.wav"

////< ��Ż Ż�� �ִ� ��ġ�� �����ܿ� ���콺�� �÷� ������ ��
//

#define GSD_SYSTEM_DRAGOBALL_REGISTRATION	"System\\SYSTEM_DB_REG.wav"	
//< �巡�ﺼ�� ���� ������

#define GSD_SYSTEM_DRAGOBALL_UI_LIGHT		"System\\SYSTEM_DB_LIGHT.wav"	

////< �巡�ﺼ ���ܿ� ���� ������
//
//
#define GSD_SYSTEM_NEW_MAIL_ALRAM			"System\\SYSTEM_NEW_MAIL.wav"	

////< ���ο� ������ ����������
//
#define GSD_SYSTEM_MAIL_SEND				"System\\SYSTEM_SEND_MAIL.wav"	

////< ������ ������
//
#define GSD_SYSTEM_SCOUTER_LOOP				"System\\GENERAL_Scouter_Loop.wav"
//< ��ī��Ʈ ������

#define GSD_SYSTEM_SCOUTER_SCAN				"System\\GENERAL_Scouter_Scan.wav"
//< ��ī��Ʈ Ÿ�� ������
//******************************************�Ϸ�

#define GSD_SYSTEM_USE_MONEY				"System\\SYSTEM_USE_MONEY.wav"
///< Money�� ������� ���� Sound.��� ���� �Ҹ���, ���� �Ρ�.

#define GSD_SYSTEM_DROP_NORMAL				"System\\SYSTEM_DROP_NORMAL.wav"
///< Item Drop - Mob�� ����� Capsule�� Zenny�� �������� Sound.���� �Ϳ� �Ž����� �Ҹ��� ���� �ʴ� �Ҹ���, ������.

#define GSD_SYSTEM_DROP_LUCKY				"System\\SYSTEM_DROP_LUCKY.wav"
///< Item Drop - Lucky!! ���� ���Ƽ� ��Һ��� ���� Capsule�� ���� Zenny�� �������� Sound.���� �Ϳ� �Ž����� �Ҹ��� ���� �ʴ� �Ҹ���, �����桹.

#define GSD_SYSTEM_ITEM_GET					"System\\SYSTEM_ITEM_GET.wav"
///< Item Drop - Drop�� �� Item�� ����� ���� Sound.������.

#define GSD_SYSTEM_SKILL_LEARN				"System\\SYSTEM_SKILL_LEARN.wav"
///< Skill�� ����� ���� Sound.��ȸ�� ���� ���� �Ҹ���, ���.

#define GSD_SYSTEM_SKILL_DISABLE			"System\\SYSTEM_SKILL_DISABLE.wav"
///< Skill�� Item�� ����� �� ���� ���� Sound.�Ϳ� �Ž����� �Ҹ��� ���� �ʴ� ����Ʈ�� ���� �Ҹ���, ���.

#define GSD_SYSTEM_QUEST_GIVE_UP			"System\\SYSTEM_QUEST_GIVE_UP.wav"
///< Quest�� Give up �� ���� Sound.���������� �Ҹ���, ������������.

#define GSD_SYSTEM_TRIGGER_OBJECT_CLICK		"System\\GENERAL_Click_01.wav"
///< Trigger object�� Ŭ�� ���� �� ���� �Ҹ�

#define GSD_JINGLE_QUEST_START				"BGM\\JINGLE_QUEST_START.ogg"
///< Quest�� ������ �� ������ ���� ������ �ִ� �밨�� ����.

#define GSD_JINGLE_QUEST_FINISH				"BGM\\JINGLE_QUEST_FINISH.ogg"
///< Quest�� �������� Ī���ϴ°� ���� �ູ�� ����

#define GSD_JINGLE_LEVEL_UP					"BGM\\JINGLE_LEVEL_UP.ogg"
///< LevelUp

#define GSD_JINGLE_PVP_START				"BGM\\JINGLE_PVP_START.ogg"
///< PvP Start

#define GSD_JINGLE_PVP_END					"BGM\\JINGLE_PVP_END.ogg"
///< PvP End

#define GSD_GET_EXP							"System\\SYSTEM_Exp_Get.wav"
///< Exp Get

#define GSD_QUEST_ITEM_GET					"System\\SYSTEM_Quest_item_Get.wav"
///< Quest Item Get

#define GSD_RP_FULL							"System\\GENERAL_RP_Full.wav"
///< RP Full



#define GSD_HEART_BEAT						"Syatem\\GENERAL_Radar.wav"	// �ӽ�
///< HeartBeat HP���Ͻ� �ݺ�

/// ��� ������� �������
#define GSD_JINGLE_DRAGON                   "BGM\\JINGLE_SHENRON.ogg"

///< ���ǰ� �ʿ��Ͽ� ����ڿ��� �˸��� ȿ����
#define GSD_SYSTEM_WINDOW_ALREAT					"System\\SYSTEM_WINDOW_ALART.wav"

///< ©��©��
#define GSD_GENERAL_CLOCK_SECOND					"System\\GENERAL_Clock_Second.wav"

///< Music when you catch a HERO BOSS in a dungeon
#define GSD_FINISH_HERO_MOB							"BGM\\JINGLE_BOSS_DOWN.ogg"



//////////////////////////////////////////////////////////////////////////
//						Background Mugic								//
//////////////////////////////////////////////////////////////////////////

#define GSD_BGM_PVP							"BGM\\BGM_PVP.ogg"

#define GSD_BGM_PRIVATE_RANKBATTLE			"BGM\\BGM_RANK_BATTLE_2m.ogg"
#define GSD_BGM_PARTY_RANKBATTLE			"BGM\\BGM_RANK_BATTLE_3m.ogg"

#define GSD_BGM_MAIN_THEME					"BGM\\BGM_MAIN_THEME.ogg"
#define GSD_BGM_PROLOG						"BGM\\BGM_PROLOGE.ogg"


//////////////////////////////////////////////////////////////////////////
//						õ������ ����ȸ									//
//////////////////////////////////////////////////////////////////////////

#define GSD_BGM_TB_STANDBY					"BGM\\BGM_TB_STANDBY.ogg"
#define GSD_BGM_TB_PRIVATE_BATTLE			"BGM\\BGM_TB_MAIN_m3.ogg"
#define GSD_BGM_TB_PARTY_BATTLE				"BGM\\BGM_TB_MAIN_m4.ogg"

#define GSD_TB_TOURNAMENT_START				"BGM\\JINGLE_TB_START.ogg"
#define GSD_TB_ROUND_END					"BGM\\JINGLE_PVP_END.ogg"
#define GSD_TB_MATCH_RESULT					"BGM\\JINGLE_TB_RESULT.ogg"


//////////////////////////////////////////////////////////////////////////
//						���� ��Ż��										//
//////////////////////////////////////////////////////////////////////////

#define GSD_BGM_DOJO_SCRAMBLE_READY			"BGM\\BGM_PROLOGE_B.ogg"
#define GSD_BGM_DOJO_SCRAMBLE_START			"BGM\\BGM_DOJO_BATTLE.ogg"