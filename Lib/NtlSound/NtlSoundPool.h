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

extern RWS::CEventId g_EventSoundReleaseSound;				// �� �� ä���� ���尡 �����Ǿ���

extern RWS::CEventId g_EventSoundFinishFade;				// ���̵� ��/�ƿ��� ������

extern RWS::CEventId g_EventSoundDSP;						// ȿ���� ���� �̺�Ʈ

extern RWS::CEventId g_EventSoundEventMusic;				// �̺�Ʈ���� ä�� �̺�Ʈ

extern RWS::CEventId g_EventSoundRestTime;					// �ݺ��Ǵ� ������ ���� �÷��̱��� �޽� �ð�

extern RWS::CEventId g_EventSoundKnockdown;					// �˴ٿ� �� ��

extern RWS::CEventId g_EventSoundMinMaxRate;				// 3D ������ ��ü Min, Max���� �ٲ۴�

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
	EVENT_MUSIC_EVENT_MUSIC_HAD_PLAY,		///< Event ������ �÷��̸� �����ߴ�
	EVENT_MUSIC_ALL_EVENT_MUSIC_FINISH,		///< ��� Event ������ �÷��̸� �����ߴ�
};

struct SNtlEeventMusic
{
	RwUInt8			byType;
};

struct SNtlEventMusicRestTime
{
	RwUInt8			byChannelGroup;
	RwReal			fRestTime;				///< ���� : ��
};

struct SNtlEventKnockdown
{
	RwBool			bKnockdown;
};

struct SNtlEventMinMaxRate
{
	RwReal			fMinMaxRate;
};