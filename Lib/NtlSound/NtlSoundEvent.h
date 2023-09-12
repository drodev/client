/*****************************************************************************
 *
 * File			: DboEvent.h
 * Author		: Hong Sungbock
 * Copyright	: (��)NTL
 * Date			: 2007. 5. 29
 * Abstract		: Ntl sound event.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#pragma once

#include "ceventhandler.h"
#include "NtlSoundDefines.h"

extern RWS::CEventId g_EventSoundReleaseSound;				// �� �� ä���� ���尡 �����Ǿ���

extern RWS::CEventId g_EventSoundFinishFade;				// ���̵� ��/�ƿ��� ������

extern RWS::CEventId g_EventSoundDSP;						// ȿ���� ���� �̺�Ʈ

extern RWS::CEventId g_EventSoundEventMusic;				// ä�� �̺�Ʈ

extern RWS::CEventId g_EventSoundRestTime;					// �ݺ��Ǵ� ������ ���� �÷��̱��� �޽� �ð�

extern RWS::CEventId g_EventSoundKnockdown;					// �˴ٿ� �� ��

extern RWS::CEventId g_EventSoundMinMaxRate;				// 3D ������ ��ü Min, Max���� �ٲ۴�

extern RWS::CEventId g_EventSoundAddListRangeBGM;			// Range BGM�� ����Ʈ�� �߰�

extern RWS::CEventId g_EventSoundDelListRangeBGM;			// Range BGM�� ����Ʈ���� ����

extern RWS::CEventId g_EventSoundChangeListRangeBGM;		// Range BGM�� ���� ����

extern RWS::CEventId g_EventSoundAddListShareBGM;			// Shard BGM�� ����Ʈ�� �߰�

extern RWS::CEventId g_EventSoundDeleteAllListShareBGM;		// Shard BGM�� ����Ʈ���� ��� ����

extern RWS::CEventId g_EventSoundShareBGMPlayRate;			// Shard BGM�� �÷��� �� �� �ִ� Ȯ�� ����

extern RWS::CEventId g_EventSoundReleaseObjectGroup;		// Object Group�� ��� ���带 �����Ѵ�

//////////////////////////////////////////////////////////////////////////
//	Structure
//////////////////////////////////////////////////////////////////////////

enum eDSPEvent
{
	DSP_ADD_REVERV,							///< Ư�� ä�α׷쿡 reverv ȿ���� �����Ѵ�
	DSP_REMOVE_REVERV,						///< Ư�� ä�α׷쿡 reverv ȿ���� ��������
	DSP_REMOVE_ALL,							///< Ư�� ä�α׷쿡 ��� ȿ���� �����Ѵ�
};

struct SNtlEventDSP
{
	RwUInt8			byType;
};

enum eEventMusic
{
	EVENT_MUSIC_EVENT_MUSIC_HAD_PLAY,			///< Event ������ �÷��̸� �����ߴ�
	EVENT_MUSIC_ALL_EVENT_MUSIC_FINISH,			///< ��� Event ������ �÷��̸� �����ߴ�

	EVENT_MUSIC_LEAVE_MAIN_WORLD_CONCEPT,		///< ���ο��� �������� �ٸ� �������� ������ �Ǿ���

	EVENT_MUSIC_START_PVP_BGM,					///< PVP BGM ����
	EVENT_MUSIC_END_PVP_BGM,					///< PVP BGM ��

	EVENT_MUSIC_START_PRIVATE_RANKBATTLE_BGM,	///< ��ũ��Ʋ ������ BGM ����
	EVENT_MUSIC_END_PRIVATE_RANKBATTLE_BGM,		///< ��ũ��Ʋ ������ ��

	EVENT_MUSIC_START_PARTY_RANKBATTLE_BGM,		///< ��ũ��Ʋ ��Ƽ�� BGM ����
	EVENT_MUSIC_END_PARTY_RANKBATTLE_BGM,		///< ��ũ��Ʋ ��Ƽ�� ��

	EVENT_MUSIC_END_CINEMATIC_BGM,				///< �ó׸�ƽ BGM ��

	EVENT_MUSIC_START_MAIN_THEME,				///< �����׸� BGM ����
	EVENT_MUSIC_PROLOG_THMEM_BGM_PLAY,			///< Prolog BGM Play
	EVENT_MUSIC_END_MAIN_THEME,					///< �����׸� ��
	EVENT_MUSIC_IMMEDIATELY_END_MAIN_THEME,		///< �����׸� FadeOut ���� �ٷ� ����	

	EVENT_MUSIC_VOLUME_DOWN_BECAUSE_MOVIE_PLAY,	///< Movie�� �÷����ϱ⿡ Master ������ ���δ�
	EVENT_MUSIC_VOLUME_UP_BECAUSE_MOVIE_PLAY,	///< Movie�� �÷��� ����Ǿ� Master ������ ���δ�

	EVENT_MUSIC_FINISH_THEME_BGM,				///< THEME BGM�� �÷��� ���̸� �����϶�	

	EVENT_MUSIC_LOOP_THEME_BGM,					///< THEME BGM�� Loop �Ѵ�
	EVENT_MUSIC_NOT_LOOP_THEME_BGM,				///< THEME BGM�� �� ���� �÷��� �Ѵ�

	EVENT_MUSIC_TEMP_FINISH_TMQ,				///< �ӽ� TMQ ����

	EVENT_MUSIC_TB_DIRECTION_BGM_PLAY,			///< õ������ ����ȸ ���� BGM Play
	EVENT_MUSIC_TB_DIRECTION_BGM_STOP,			///< õ������ ����ȸ ���� BGM Stop

	EVENT_MUSIC_TB_PARTY_BGM_PLAY,				///< õ������ ����ȸ ��Ƽ�� BGM Play
	EVENT_MUSIC_TB_PARTY_BGM_STOP,				///< õ������ ����ȸ ��Ƽ�� BGM Stop

	EVENT_MUSIC_TB_PRIVATE_BGM_PLAY,			///< õ������ ����ȸ ������ BGM Play
	EVENT_MUSIC_TB_PRIVATE_BGM_STOP,			///< õ������ ����ȸ ������ BGM Stop

	EVENT_MUSIC_RAGNE_STOP,						///< Range BGM Stop
	EVENT_MUSIC_REMOVE_RAGNE_BGM,				///< BGM �׷쿡�� Range BGM ����Ʈ�� ������

	EVENT_MUSIC_START_SCRAMBLE_READY_BGM,		///< ���� ��Ż��
	EVENT_MUSIC_STOP_SCRAMBLE_READY_BGM,
	EVENT_MUSIC_START_SCRAMBLE_START_BGM,
	EVENT_MUSIC_END_SCRAMBLE_START_BGM,
};

struct SNtlEeventMusic
{
	RwUInt8			byType;
};

struct SNtlEventMusicRestTime
{
	RwUInt8			byChannelGroup;
	RwReal			fRestTime;				///< ���� : ��
	RwUInt8			byBGMType;				///< BGM ä�� �׷��� ���� ��ȿ�ϴ�
};

struct SNtlEventKnockdown
{
	RwBool			bKnockdown;
};

struct SNtlEventMinMaxRate
{
	RwReal			fMinMaxRate;
};

struct SNtlEventAddListRangeBGM
{
	RwUInt32*		phResultHandle;
	const RwChar*	pcFileName;
	RwReal			fRadius;
	RwV3d*			pPosition;
};

struct SNtlEventDelListRangeBGM
{
	RwUInt32		hSound;
};

struct SNtlEventRangeBGMChangeParam
{
	RwUInt32		hSound;
	const RwChar*	pcFileName;
	RwReal			fRadius;
	RwV3d*			pPosition;
};

struct SNtlEventAddListShareBGM
{
	const RwChar*	pcFileName;
};

struct SNtlEventShareBGMPlayRate
{
	RwReal			fPlayRate;
};