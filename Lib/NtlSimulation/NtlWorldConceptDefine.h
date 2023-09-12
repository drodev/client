/*****************************************************************************
 *
 * File			: NtlWorldConceptDefine.h
 * Author		: Hong Sungbock
 * Copyright	: (��)NTL
 * Date			: 2007. 7. 13
 * Abstract		: Simulation world concept defines
 *****************************************************************************
 * Desc         : World Concept�� ���õ� ������ ������ �д�
 *
 *****************************************************************************/


#ifndef __NTL_WORLDCONCEPT_DEFINE_H__
#define __NTL_WORLDCONCEPT_DEFINE_H__

#define WORLD_CONCEPT_FIRST_GRADE	0x00010000
#define WORLD_CONCEPT_SECOND_GRADE	0x00020000
#define WORLD_CONCEPT_THIRD_GRADE	0x00040000
#define WORLD_CONCEPT_FOURTH_GRADE	0x00080000

/// World Concept Ŭ�������� �����ϴ� ������ ����
// avooo's comment : Logic_WorldConceptMessage �� �ε����� �߰��� �ּ���
enum EWorldPlayConcept
{
	WORLD_PLAY_NONE					= 0,

	//-- 1�ܰ� ����--//
	WORLD_PLAY_TUTORIAL				= 0x00010001,		///< Ʃ�͸���
	WORLD_PLAY_TIME_MACHINE			= 0x00010002,		///< Ÿ�Ӹӽ� ����Ʈ
	WORLD_PLAY_RANK_BATTLE			= 0x00010003,		///< ��ũ ��Ʋ
	WORLD_PLAY_T_BUDOKAI			= 0x00010004,		///< õ������ ����ȸ(��Ʋ����)
	WORLD_PLAY_PARTY_DUNGEON		= 0x00010005,		///< Party Dungeon
	WORLD_PLAY_TLQ					= 0x00010006,		///< Ÿ�� �� ����Ʈ ( TLQ )
	WORLD_PLAY_DOJO_SCRAMBLE		= 0x00010007,		///< ���� ��Ż��
	WORLD_PLAY_DOJO_DUEL			= 0x00010008,		///< ���� ����
	WORLD_PLAY_CCBD					= 0x00010009,
	WORLD_PLAY_DWC					= 0x00010010,

	//-- 2�ܰ� ���� --//
	WORLD_PLAY_FREEPVP				= 0x00020000,		///< PVP(Battle) state
	WORLD_PLAY_NPC_COMMU			= 0x00020001,		///< NPC ��ȭ ����
	WORLD_PLAY_TRADE				= 0x00020002,		///< ���� Trade ����
	WORLD_PLAY_DRAGONBALL_COLLECT	= 0x00020003,		///< �巡�ﺼ�� �����Ͽ�, ����� �ҷ����� �̺�Ʈ ����
	WORLD_PLAY_PRIVATESHOP			= 0x00020004,		///< ���λ��� ����(�Ǹ���)
	WORLD_PLAY_PRIVATESHOP_VISITOR	= 0x00020005,		///< ���λ��� ����(������)
	WORLD_PLAY_REMOTE_BEHAVIOUR		= 0x00020006,
	WORLD_PLAY_MASCOTEX_SKILL		= 0x00020007,
	
	//-- 3�ܰ� ���� --//
	WORLD_PLAY_DIRECT				= 0x00040006,		///< ���� ����(cinematic, narraion)

	WORLD_PLAY_DRAGONBALL_SCRAMBLE	= 0x00080001,

	WORLD_PLAY_FREEPVP_ZONE			= 0x00100001,	// free pvp for all
};


/// World Concept�� ���� ���� �÷���
enum EWorldState
{
	WORLD_STATE_NONE,
	WORLD_STATE_ENTER,
	WORLD_STATE_IDLE,
	WORLD_STATE_EXIT,

	// �巡�ﺼ �÷��� ���� ����
	WORLD_DBC_ALTAR_UI,
	WORLD_DBC_NIGHT_ON,
	WORLD_DBC_ALTAR_EFFECT,
	WORLD_DBC_SPAWN_DRAGON,
	WORLD_DBC_NARRATION_START,
	WORLD_DBC_REWARD_UI,
	WORLD_DBC_NARRATION_END,
	WORLD_DBC_DESTROY_DRAGON,
	WORLD_DBC_DESTROY_DB,
	WORLD_DBC_NIGHT_OFF,
};

enum EWorldStateNPC
{
	WORLD_NPC_SHOP = WORLD_STATE_EXIT + 1,
	WORLD_NPC_TRAINER,
	WORLD_NPC_ITEM_UPGRADE,
	WORLD_NPC_WAREHOUSE,
	WORLD_NPC_GUILD_WAREHOUSE,
};

/// �ƹ�Ÿ �׼� ���� ������ �Ǵ��ϱ� ���� �÷��� ����Ʈ
enum EAvatarAction
{
	E_ACTION_MOVE,
	E_ACTION_PICK_WORLD,
	E_ACTION_PICK_OBJECT,
	E_ACTION_TARGETTING,
	E_ACTION_ATTACK,
	E_ACTION_CHANGE_HEADING,
	E_ACTION_CAMERA_CONTROL,
	E_ACTION_CHARGING,
	E_ACTION_LOOTING,
	E_ACTION_CAN_COMMUNICATION,
};

enum EWorldStateTMQ
{
	WORLD_STATE_TMQ_WAIT,					// TMQ �����ϰ� �÷��̾� ���� ���
	WORLD_STATE_TMQ_TERRAIN_READY,			// ���� �ε� �Ϸ�
	WORLD_STATE_TMQ_PREPARE,				// ��� �÷��̾� ������ ����� üũ �� ���� ���� ����
	WORLD_STATE_TMQ_ARRIVE,					// ���� ���� ( TS������ �̺�Ʈ ���, ���� ��Ÿ���� �ð� �̺�Ʈ ��� )
	WORLD_STATE_TMQ_BEGIN,					// ���� ���� ( ��ũ��Ʈ ���� )
	WORLD_STATE_TMQ_STAGE_READY,			// �������� �غ� ( ��ũ��Ʈ ���� )
	WORLD_STATE_TMQ_STAGE_START,			// �������� ���� ( ��ũ��Ʈ ���� )
	WORLD_STATE_TMQ_STAGE_FINISH,			// �������� ���� ( ��ũ��Ʈ ���� )
	WORLD_STATE_TMQ_END,					// ���� ��
	WORLD_STATE_TMQ_LEAVE,					// ���� ������ ����
	WORLD_STATE_TMQ_FAIL,					// ���� �� ( TMQ ���� )
	WORLD_STATE_TMQ_CLOSE,					// TMQ ����
};

#endif