/*****************************************************************************
*
* File			: NtlPLDef.h
* Author		: HyungSuk, Jang
* Copyright	: (��)NTL
* Date			: 2005. 8. 01	
* Abstract		: Presentation layer standard define
*****************************************************************************
* Desc         : 
*
*****************************************************************************/


#ifndef __NTL_PLDEF_H__
#define __NTL_PLDEF_H__

#include "NtlCharacter.h"

enum ENtlPLEntityLayer
{
	PLENTITY_LAYER_INVALID,
	PLENTITY_LAYER_NONE,
	PLENTITY_LAYER_FOG,
	PLENTITY_LAYER_SKY,	
	PLENTITY_LAYER_RWWORLD,				// renderware�� ���ԵǴ� ��� entity��(woody1019, jhssugi)
	PLENTITY_LAYER_DECAL,
	PLENTITY_LAYER_PLAYERNAME,
	PLENTITY_LAYER_DAMAGEBOX,
	PLENTITY_LAYER_SOUND,
	PLENTITY_LAYER_EFFECT,
	PLENTITY_LAYER_LIGHT,
	PLENTITY_LAYER_SHORELINE,
	PLENTITY_LAYER_WEATHER,
	PLENTITY_LAYER_OCCLUDER,
	PLENTITY_LAYER_HEATHAZE,
	PLENTITY_LAYER_TOOL,
	PLENTITY_LAYER_GUI,
	PLENTITY_LAYER_MAX
};


enum ENtlPLEntityType
{
	PLENTITY_SKY,
	PLENTITY_WORLD,			// woody1019
	PLENTITY_DUMMY_WORLD,	// jhssugi
	PLENTITY_OCCLUDER,
	PLENTITY_WATER,
	PLENTITY_SHORELINE,
	PLENTITY_OBJECT,
	PLENTITY_CHARACTER,
	PLENTITY_ITEM,			//by HoDong
	PLENTITY_EFFECT,	// 10 in tw?
	PLENTITY_SPLINE,		// by agebreak
	PLENTITY_DECAL,			// by jhssugi
	PLENTITY_PLAYER_NAME,
	PLENTITY_DAMAGE_BOX,
	PLENTITY_LIGHT,
	// CZ-SS
	//PLENTITY_SPOT_LIGHT,
	PLENTITY_FOG,
	PLENTITY_GUI,
	PLENTITY_SOUND,
	PLENTITY_SOUND_BGM,
	PLENTITY_BLOOM,
	PLENTITY_SUN,			// by agebreak
	PLENTITY_SUN_PLANET,	// FreeList ������ Ŭ�������� �����ϱ� ���� �߰�.
	PLENTITY_PLANT,
	PLENTITY_WORLD_LIGHT,
	PLENTITY_WEATHER,
	PLENTITY_HEATHAZE,
	PLENTITY_LIGHT_OBJECT,	// 28 in tw?
	PLENTITY_GAME_PROPERTY,
	PLENTITY_DECAL_VOLUME,
	PLENTITY_DOJO,

	PLENTITY_END,
	PLENTITY_INVALID_TYPE = 0xffffffff
};

// PLEN => presentation layer entity name�� ���.
#define NTL_PLEN_SKY			"PLSky"
#define NTL_PLEN_WORLD			"PLWorld"		// woody1019
#define NTL_PLEN_DUMMY_WORLD	"PLDummyWorld"	// jhssugi
#define NTL_PLEN_WATER			"PLWater"
#define NTL_PLEN_SHORELINE		"PLShoreLIne"
#define NTL_PLEN_OBJECT			"PLObject"
#define NTL_PLEN_CHARACTER		"PLCharacter"
#define NTL_PLEN_ITEM			"PLItem"
#define NTL_PLEN_EFFECT			"PLEffect"
#define NTL_PLEN_SPLINE			"PLSpline"
#define NTL_PLEN_DECAL			"PLDecal"
#define NTL_PLEN_PLAYER_NAME	"PLPlayerName"
#define NTL_PLEN_DAMAGE_BOX		"PLDamageBox"
#define NTL_PLEN_LIGHT			"PLLight"
// CZ-SS
//#define NTL_PLEN_SPOT_LIGHT		"PLSpotLight"
#define NTL_PLEN_FOG			"PLFog"
#define NTL_PLEN_GUI			"PLGui"
#define NTL_PLEN_SOUND			"PLSound"
#define NTL_PLEN_SOUND_BGM		"PLSoundBGM"
#define NTL_PLEN_BLOOM			"PLBloom"
#define NTL_PLEN_PLANT			"PLPlant"
#define NTL_PLEN_WORLD_LIGHT	"PLWorldLight"
#define NTL_PLEN_WEATHER		"PLWeather"
#define NTL_PLEN_HEATHAZE		"PLHeatHaze"
#define NTL_PLEN_LIGHT_OBJECT	"PLLightObject"
#define NTL_PLEN_GAME_PROPERTY	"PLGameProperty"
#define NTL_PLEN_DECAL_VOLUME	"PLDecalVolume"
#define NTL_PLEN_DOJO			"PLDojo"

/// entity flag
// CNtlPLEntity::SetFlags(RwUInt32 uiFlags); �Լ��� ����Ͽ� setting �� �ش�.
#define NTL_PLEFLAG_NOTUPDATE					0x00000001	// entity���� update �� �ʿ� ���� �� setting �Ѵ�(�� : animation�� ���� object).
#define NTL_PLEFLAG_FRUSTUMOUT_NOTUPDATE		0x00000002	// entity���� camera frustum �ۿ� ���� ��� update�� ���� �ʾƵ� �Ǵ� ��쿡 setting �� �ش�.
#define NTL_PLEFLAG_ALPHA						0x00000004	// entity�� alpha flag�� setting �� �ش�.
#define NTL_PLEFLAG_PICKING						0x00000008	// entity���� mouse picking�� �� �� �ִ� �ѵ�.( �ӵ��� ���Ͽ�...)
#define NTL_PLEFLAG_NOT_ADD_WORLD				0x00000010  // entity���� RpWorld�� �߰����� �ʾƵ� �Ǵ� entity�� ���.
#define NTL_PLEFLAG_NOT_PROPERTY_USED			0x00000020	// entity���� CNtlPLProperty �� ���� ������� �ʴ� entity ���.
#define NTL_PLEFLAG_NOT_VISIBLE					0x00000040	// entity���� rendering on/off flags.
#define NTL_PLEFLAG_ATTACH						0x00000080	// ���� entity�� attach ������ entity �̴�.
#define NTL_PLEFLAG_COLLISION					0x00000100  // ���� entity�� Collision�� �����ϰ�, �ö󰡴°��� �����ϴ�.
#define NTL_PLEFLAG_WEIGHT_ELAPSED_TIME			0x00000200  // ���� entity�� update elapsed time �ӵ��� �����Ѵ�.
#define NTL_PLEFLAG_SELECTION					0x00000400	// Ʈ���Ű� �ִ� ������Ʈ�߿��� ������ �Ǵ°� ���°��� �����Ѵ�.
#define NTL_PLEFLAG_TRIGGER					    0x00000800	// Ʈ���Ű� �ִ��� �������� �Ǵ��Ѵ�.
#define NTL_PLEFLAG_ALTERABLE					0x00001000	// ������Ʈ�� ���������� �ִ����� �Ǵ��Ѵ�.
#define NTL_PLEFLAG_PORTAL						0x00002000	// ��Ż����� �ִ��� �������� �Ǵ��Ѵ�.
#define NTL_PLEFLAG_PECOLLISION					0x00004000	// Path engine�� 2D collision mesh�� ��������� �Ǵ��Ѵ�.
#define NTL_PLEFLAG_FADE                        0x00008000  // Fade ���� ���� �÷���
#define NTL_PLEFLAG_SHADOW                      0x00010000  // Entity�� Shadow ǥ�� ���� �÷���
#define NTL_PLEFLAG_NEST_MEMBER                 0x00020000  // Nest Spawn Member
#define NTL_PLEFLAG_RESIZE_PICKING_BBOX         0x00040000  // Flag to dynamically bound the bounding box for picking
#define NTL_PLEFLAG_TOOL_PICK					0x00080000	// �������� ������������� �����̸鼭 ��ġ�ϴ� ��찡 �ִ�. �̰�춧���� ��Ŀ�� �浹�� ����� �Ǵµ� �̸� �����ϱ� ���� �� �÷��׸� ����. ���÷��װ� ���� ��쿡�� ��ŷ�� �ǵ��� NTLPicking���� ó���ȴ�.
#define NTL_PLEFLAG_OBJECT_FORCE_VISIBLE		0x00100000	// ������Ʈ�� �������� ó��(Fade, Distance Culling...)�� ������ �����ʰ�, ���� �ܺο����� Visible, Alpha���� �����ϱ� ���� �÷��� (Ʈ���� ������Ʈ�� ����ó�� ���ؼ� ���ȴ�) - ���������� ������� �ʴ´�
#define NTL_PLEFLAG_SHADOW_PROP					0x00200000	// terrain property�� �����ؾ� �� ���.
#define NTL_PLEFLAG_DUMMY						0X00400000	// ex. GUI���� character�� �����Ǵ� ��쿡 ����Ѵ�.

// entity cull flags : �켱 ������ ���� ���� ��Ʈ���� ����.
#define NTL_PLEFLAG_CULLED_PVS							0x00000001 // pvs test
#define NTL_PLEFLAG_CULLED_CAMERA_FRUSTUM_OUT			0x00000002 // camera frustum out
#define NTL_PLEFLAG_CULLED_OCCLUDER						0x00000004 // occluder culled

// Pick order
#define NTL_PICK_ORDER_NORMAL					(0)
#define NTL_PICK_ORDER_HIGH						(1)


#define NTL_PLEFLAG_MINIMAP_LAYER_NONE				(0x00000000)
#define NTL_PLEFLAG_MINIMAP_LAYER_ONE				(0x00000001)
#define NTL_PLEFLAG_MINIMAP_LAYER_TWO				(0x00000002)

// item

// Item�� Grade Enum
enum ENtlPLItemGrade
{
	ITEM_GRADE_NONE = 0,
	ITEM_GRADE_1,
	ITEM_GRADE_2,
	ITEM_GRADE_3,
	ITEM_GRADE_4,
	ITEM_GRADE_5,
	ITEM_GRADE_6,
	ITEM_GRADE_7,
	ITEM_GRADE_8,
	ITEM_GRADE_9,
	ITEM_GRADE_10,
	ITEM_GRADE_11,
	ITEM_GRADE_12,
	ITEM_GRADE_13,
	ITEM_GRADE_14,
	ITEM_GRADE_15,
};

// emblem type
enum eEmblemType
{
	EMBLEMTYPE_A,
	EMBLEMTYPE_B,
	EMBLEMTYPE_C,

	NUM_EMBLEMTYPE
};

#define NTL_ITEM_ICON_SIZE				32	
#define NTL_ITEM_SMALL_ICON_SIZE		16	


// icon name
#define MONEYICON_NAME				"I_SYS_Zenny.png"
#define UNIDENTIFIED_ICON_NAME		"i_ucap.png"
#define SEALED_ICON_NAME			"i_lot_blu.png"
#define UNABLE_SLOT_NAME			"Unable_Slot.png"

// effect key name

#define _COMPILE_OPTION_USE_HEIGHT_MAP_				// Use Height Map


#define VISIBLE_BOUND		( 2 )
#define INTERPOLATE_OFFSET	( 1.0f )

#define rwID_WORLD_PLUG_IN_ID	( 0xF3 )

// Path
#define PATH_COLLISION_OBJECT   "Object\\col_mesh\\"
#define PATH_EFFECT_RESOURCE	"Effect\\"
#define PATH_EFFECT_TEXTURE		".\\Texture\\ntlwe\\Planet\\;.\\Texture\\Effect\\;.\\Texture\\character\\;.\\Texture\\Effect\\text\\;.\\Texture\\Effect\\qest_icon\\;"

// XML ��ȣȭ �н�����
#define ENC_DATA_PASSWORD				"@#)!agebreak"

// Rendering flag
#define dFLAG_EXCEPT_GUI			0x00000001

typedef unsigned int BITFLAG;                   // ��Ʈ �÷��׿� Ÿ��



#endif


