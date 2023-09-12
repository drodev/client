 /*****************************************************************************
 *
 * File			: NtlActionMapDef.h
 * Author		: Haesung, Cho
 * Copyright	: (��)NTL
 * Date			: 2008. 1. 15	
 * Abstract		: Simulation ActionMap definition
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_ACTIONMAP_DEF_H__
#define __NTL_ACTIONMAP_DEF_H__

///////////////////////////////////////////////////////////////////////////////
// NTL Key Definition
///////////////////////////////////////////////////////////////////////////////
#define NTL_KEY_BACKSPACE	   0x08
#define NTL_KEY_TAB			   0x09
#define NTL_KEY_RETURN		   0x0D
#define NTL_KEY_NUMPAD0        0x60
#define NTL_KEY_NUMPAD1        0x61
#define NTL_KEY_NUMPAD2        0x62
#define NTL_KEY_NUMPAD3        0x63
#define NTL_KEY_NUMPAD4        0x64
#define NTL_KEY_NUMPAD5        0x65
#define NTL_KEY_NUMPAD6        0x66
#define NTL_KEY_NUMPAD7        0x67
#define NTL_KEY_NUMPAD8        0x68
#define NTL_KEY_NUMPAD9        0x69
#define NTL_KEY_MULTIPLY       0x6A
#define NTL_KEY_ADD            0x6B
#define NTL_KEY_SEPARATOR      0x6C
#define NTL_KEY_SUBTRACT       0x6D
#define NTL_KEY_DECIMAL        0x6E
#define NTL_KEY_DIVIDE         0x6F
#define NTL_KEY_F1             0x70
#define NTL_KEY_F2             0x71
#define NTL_KEY_F3             0x72
#define NTL_KEY_F4             0x73
#define NTL_KEY_F5             0x74
#define NTL_KEY_F6             0x75
#define NTL_KEY_F7             0x76
#define NTL_KEY_F8             0x77
#define NTL_KEY_F9             0x78
#define NTL_KEY_F10            0x79
#define NTL_KEY_F11            0x7A
#define NTL_KEY_F12            0x7B

#define NTL_KEY_SHIFT          0x10
#define NTL_KEY_CONTROL        0x11
#define NTL_KEY_MENU           0x12
#define NTL_KEY_PAUSE          0x13
#define NTL_KEY_CAPITAL        0x14
#define NTL_KEY_TOCHINESE	   0x19
#define NTL_KEY_ESCAPE         0x1B
#define NTL_KEY_CONVERT        0x1C
#define NTL_KEY_NONCONVERT     0x1D
#define NTL_KEY_ACCEPT         0x1E
#define NTL_KEY_MODECHANGE     0x1F
#define NTL_KEY_SPACE          0x20
#define NTL_KEY_PRIOR          0x21
#define NTL_KEY_NEXT           0x22
#define NTL_KEY_END            0x23
#define NTL_KEY_HOME           0x24
#define NTL_KEY_LEFT           0x25
#define NTL_KEY_UP             0x26
#define NTL_KEY_RIGHT          0x27
#define NTL_KEY_DOWN           0x28
#define NTL_KEY_SELECT         0x29
#define NTL_KEY_PRINT          0x2A
#define NTL_KEY_EXECUTE        0x2B
#define NTL_KEY_SNAPSHOT       0x2C
#define NTL_KEY_INSERT         0x2D
#define NTL_KEY_DELETE         0x2E
#define NTL_KEY_HELP           0x2F
#define NTL_KEY_LEFTWINDOW	   0x5b
#define NTL_KEY_RIGHTWINDOW    0x5c
#define NTL_KEY_NUMLOCK        0x90
#define NTL_KEY_SCROLL         0x91
#define NTL_KEY_COMMA		   0xBC		// ','
#define NTL_KEY_DASH		   0xBD
#define NTL_KEY_PERIOD		   0xBE		// '.'
#define NTL_KEY_OEM_2		   0xBF		// '/'
#define NTL_KEY_EQUAL		   0xBB
#define NTL_KEY_WAVE		   0xC0		// '~'
#define NTL_KEY_WON			   0xDC		// '\'
#define NTL_KEY_LBRACKET		0xDB	// '['
#define NTL_KEY_RBRACKET		0xDD	// ']'

///////////////////////////////////////////////////////////////////////////////
// DragonBall Online Action
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// ActionMap Key ����
///////////////////////////////////////////////////////////////////////////////

#define NTL_ALT_BIT   0x0100
#define NTL_CTRL_BIT  0x0200			// ����Ű
#define NTL_SHIFT_BIT 0x0400

#define NTL_KEY_UPDATE 0x4000
#define NTL_KEY_EMPTY 0x8000

///////////////////////////////////////////////////////////////////////////////
// ETC
///////////////////////////////////////////////////////////////////////////////

enum eACTION
{
	// 0 ~ 19 ���� �ƹ�Ÿ �ൿ
	ACTION_AVATAR_FORWARD = 0,		///< ����
	ACTION_AVATAR_BACKWARD,			///< ����
	ACTION_AVATAR_LEFTTURN,			///< ��ȸ��
	ACTION_AVATAR_RIGHTTURN,		///< ��ȸ��
	ACTION_AVATAR_SITDOWN,			///< �ɱ�
	ACTION_AVATAR_JUMP,				///< ����
	ACTION_AVATAR_AUTORUN,			///< �ڵ��޸���
	ACTION_AVATAR_SCOUTER,			///< ��ī���� ����ϱ�
	ACTION_AVATAR_CHARGE,			///< �� ������
	ACTION_AVATAR_LOOTING,			///< ������ �ݱ�
	ACTION_AVATAR_BLOCKING,			///< �ƹ�Ÿ ���ŷ
	ACTION_AVATAR_LEFTSIDE,
	ACTION_AVATAR_RIGHTSIDE,
	ACTION_AVATAR_FREEDOWN,

	// 20 ~ 39 ���� Ÿ�� �ൿ
	ACTION_TARGET_SELF = 20,		///< �ڽ� ����
	ACTION_TARGET_1STPARTY,			///< ��Ƽ��1 ����
	ACTION_TARGET_2NDPARTY,			///< ��Ƽ��2 ����
	ACTION_TARGET_3RDPARTY,			///< ��Ƽ��3 ����
	ACTION_TARGET_4THPARTY,			///< ��Ƽ��4 ����
	ACTION_TARGET_MEMBER,
	ACTION_TARGET_AUTO,				///< ����� �� ����
	ACTION_TARGET_AUTOATK,			///< �ڵ�����
	ACTION_TARGET_AUTOFOLLOW,		///< �ڵ� ���󰡱�
	ACTION_TARGET_MARKING_1,		///< ���� Ÿ��1 ����
	ACTION_TARGET_MARKING_2,		///< ���� Ÿ��2 ����
	ACTION_TARGET_MARKING_3,		///< ���� Ÿ��3 ����
	ACTION_TARGET_MARKING_4,		///< ���� Ÿ��4 ����
	ACTION_TARGET_MARKING_5,		///< ���� Ÿ��5 ����
	ACTION_TARGET_SELECTING_1,		///< ���� Ÿ��1 ����
	ACTION_TARGET_SELECTING_2,		///< ���� Ÿ��2 ����
	ACTION_TARGET_SELECTING_3,		///< ���� Ÿ��3 ����
	ACTION_TARGET_SELECTING_4,		///< ���� Ÿ��4 ����
	ACTION_TARGET_SELECTING_5,		///< ���� Ÿ��5 ����
	ACTION_TARGET_AUTOTARGET_PARTY,	///< ��Ƽ�� �ڵ� ����

	// 40 ~ 59 ���� �� �ൿ
	ACTION_QUICK_1 = 40,			///< ������1��
	ACTION_QUICK_2,					///< ������2��
	ACTION_QUICK_3,					///< ������3��
	ACTION_QUICK_4,					///< ������4��
	ACTION_QUICK_5,					///< ������5��
	ACTION_QUICK_6,					///< ������6��
	ACTION_QUICK_7,					///< ������7��
	ACTION_QUICK_8,					///< ������8��
	ACTION_QUICK_9,					///< ������9��
	ACTION_QUICK_0,					///< ������0��
	ACTION_QUICK_MIN,				///< ������-��
	ACTION_QUICK_PLUS,				///< ������+��
	ACTION_QUICK_PREV,				///< ���� ������
	ACTION_QUICK_NEXT,				///< ���� ������
	ACTION_QUICK_2NDCAP,			///< 2�� ĸ��ŰƮ
	ACTION_QUICK_3RDCAP,			///< 3�� ĸ��ŰƮ
	ACTION_QUICK_4THCAP,			///< 4�� ĸ��ŰƮ
	ACTION_QUICK_5THCAP,			///< 5�� ĸ��ŰƮ

	// 60 ~ 79 ���� ������ �ൿ
	ACTION_WINDOW_PROFILE = 60,			///< ������ ������
	ACTION_WINDOW_SKILL,			///< ��ų���� ������
	ACTION_WINDOW_QUEST,			///< ����Ʈ ������
	ACTION_WINDOW_MINIMAP,			///< �̴ϸ�
	ACTION_WINDOW_WORLDMAP,			///< �����
	ACTION_WINDOW_MAINCAP,			///< ���� ĸ��ŰƮ
	ACTION_WINDOW_PARTY,			///< ��Ƽ����					///< ��ȹ �ܰ迡�� �����
	ACTION_WINDOW_GUILD,			///< �������
	ACTION_WINDOW_FRIEND,			///< ģ������
	ACTION_WINDOW_OPTION,			///< �ɼ�
	ACTION_WINDOW_HELP,				///< ����
	ACTION_WINDOW_MAIN,				///< ���θ޴�
	ACTION_WINDOW_RANKBOARD,		///< ��ũ����
	ACTION_WINDOW_HOIPOIMIX,
	ACTION_WINDOW_MASCOT,
	ACTION_WINDOW_DWC,

	// 80 ~ 159 ���� ���ڸ� ����
	ACTION_QUICK_1_EX = 80,				///< ������ ù��° Ȯ�� 1��
	ACTION_QUICK_2_EX,					///< ������2��
	ACTION_QUICK_3_EX,					///< ������3��
	ACTION_QUICK_4_EX,					///< ������4��
	ACTION_QUICK_5_EX,					///< ������5��
	ACTION_QUICK_6_EX,					///< ������6��
	ACTION_QUICK_7_EX,					///< ������7��
	ACTION_QUICK_8_EX,					///< ������8��
	ACTION_QUICK_9_EX,					///< ������9��
	ACTION_QUICK_0_EX,					///< ������0��
	ACTION_QUICK_MIN_EX,				///< ������-��
	ACTION_QUICK_PLUS_EX,				///< ������+��
	ACTION_QUICK_1_EX2,					///< ������ ù��° Ȯ�� 1��
	ACTION_QUICK_2_EX2,					///< ������2��
	ACTION_QUICK_3_EX2,					///< ������3��
	ACTION_QUICK_4_EX2,					///< ������4��
	ACTION_QUICK_5_EX2,					///< ������5��
	ACTION_QUICK_6_EX2,					///< ������6��
	ACTION_QUICK_7_EX2,					///< ������7��
	ACTION_QUICK_8_EX2,					///< ������8��
	ACTION_QUICK_9_EX2,					///< ������9��
	ACTION_QUICK_0_EX2,					///< ������0��
	ACTION_QUICK_MIN_EX2,				///< ������-��
	ACTION_QUICK_PLUS_EX2,				///< ������+��
	ACTION_QUICK_SUMMON,
	ACTION_QUICK_SUMMON2,

	// 160 ~ 169 ���� �̴ϸ� ����
	ACTION_MINIMAP_ZOOMOUT = 160,			///< �̴ϸ� ���
	ACTION_MINIMAP_ZOOMIN,					///< �̴ϸ� Ȯ��

	// 170 ~ 179 ���� ä��â ����
	ACTION_CHAT_PGUP = 170,				///< ä��â ���� ������
	ACTION_CHAT_PGDN,					///< ä��â ���� ������

	// 180 ~ 199 ���� ��ü ��� ����
	ACTION_GLOBAL_CANCLE = 180,			///< ���(Targeting, Windows, Main Menu)
	ACTION_GLOBAL_SNAPSHOT,				///< ��ũ����
	ACTION_GLOBAL_CHAT,					///< ä���Է�
	ACTION_GLOBAL_RENDERGUI,

	ACTION_NUMS = 255,
	ACTION_INVALID = ACTION_NUMS, 				///< �׼� ID�� ����ȣ
};

#define dNTL_KEY_EMPTY		0x8000		// ���ǵ� Ű�� ����.
#define dNTL_KEY_INVALID	0xffff		// Ű ���� INVALID.

/**
* \breif NTL�� Ű Ÿ��
* NTL Define:
* 0 0 0 0 0 0 0 0    00000000
* E           C A    Key Data
* ���� 8��Ʈ : C = CTRL, A = ALT
* ���� 8��Ʈ : Key Data
*/
typedef union _uNtlKey
{
	unsigned short key;			// 16Bit

	/**
	* key�� ���� ��Ʈ�� ���� ��Ʈ�� ����� ����ϴ� ���� ����ü
	*/
	struct _BIT
	{
		unsigned short ori:8;	// �������� Key�� ���
		unsigned short bit8:1;	// ����Ű�� ���Ǵ� Bit flags
		unsigned short bit7:1;
		unsigned short bit6:1;
		unsigned short bit5:1;
		unsigned short bit4:1;
		unsigned short bit3:1;
		unsigned short bit2:1;
		unsigned short bit1:1;
	} BIT;
} uNtlKey;

/**
* \brief ACTIONMAP�� Action�� Key�� �����ϴ� ����Ÿ��
* KEY		: unsigned short
* DATA		: unsigned short 
*/
typedef std::map< unsigned short, unsigned short > ACTIONMAP;

/**
* \brief �׼��� �����ϰ� �ֱ� ���� ����
*/
typedef std::vector< unsigned short > ACTIONVEC;

/**
* \brief �׼Ǹ��� Setting �ϴµ��� Result
*/
enum eACTIONMAP_SET_RESULT
{
	SET_RESULT_FAILED = 0,					// �˼� ���� ����
	SET_RESULT_FIXED_KEY,					// Ű�� �����Ǿ� �־ �������� ���Ѵ�.
	SET_RESULT_FIXED_ACTION,				// �׼��� �������� ���ϴ� �׼��̴�.
	SET_RESULT_NOT_COMBINE_ACTION,			// ����Ű�� ������� ���ϴ� �׼��̴�.
	SET_RESULT_ALREADY_KEY,					// Key�� �̹� ������		(������ �ִ� Key�� �Ҿ����)
	SET_RESULT_ALREADY_ACTION,				// Action�� �̹� ������		(������ �ִ� Action�� �Ҿ����)
	SET_RESULT_SAME_KEY,					// ���� Key�� ���õǾ� �־���
	SET_RESULT_NEGATIVE_MODE,				// �Ұ����� ���
	SET_RESULT_OK,							// ���������� ����
	SET_RESULT_NUMS,						// RESULT ����
	SET_RESULT_INVALID = SET_RESULT_NUMS
};

/**
* \brief �׼Ǹ��� ���� �ڵ带 ��� �ִ� ����
*/
typedef std::vector< BYTE > RESULTVEC;

/**
* \brief �׼Ǹ��� �Ӽ� ( KEY�� ACTION �Ѵ� ���� )
* �߰��� �� �ִ�.
*/
// #define TYPE_NONE			0x00000000		// �ƹ� �Ӽ��� ����.
#define TYPE_FIXED			0x00000001		// ������ Ÿ��, �������� ���Ѵ�.
#define TYPE_COMBINE		0x00000002		// ����Ű�� ���Ǵ����� ����
#define TYPE_EXCLUSIVE		0x00000004		// ����Ű�δ� ������� ���ϴ� �׼�

/**
* \brief Ű�� �׼��� �Ӽ��� �����ϰ� �ִ� ��
*/
typedef std::map< unsigned short, int >		TYPEMAP;

/**
* \brief Ű�� �̸��� �����ϰ� �ִ� ��
*/
typedef std::map<unsigned short, std::wstring> KEYNAMEMAP;

/**
* \brief ACTIONMAP�� ����ϴ� ��带 �����Ѵ�.
*/
enum eACTIONMAP_MODE
{
	ACTIONMAP_MODE_USERSETTING = 0,
	ACTIONMAP_MODE_DEFAULT,

	ACTIONMAP_MODE_NUMS,
	ACTIONMAP_MODE_INVALID = ACTIONMAP_MODE_NUMS
};

// Ű�� ���������� ���õǾ�� �� �� ���Ǵ� Count Define
#define ACTIONMAP_IGNORE_KEY_UNLIMITED_IGNORE	0xFF

#endif//__NTL_ACTIONMAP_DEF_H__