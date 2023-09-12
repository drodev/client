/*****************************************************************************
 *
 * File			: NtlPLEvent.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 9. 29	
 * Abstract		: presentation layer event type
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLEVENT_H__
#define __NTL_PLEVENT_H__

#include "ceventhandler.h"

//AnimationEvent ����
extern RWS::CEventId g_EventAnimEnd;			 //Animation�� ������ ���
extern RWS::CEventId g_EventAnimHit;             //Animation Hit Event
extern RWS::CEventId g_EventAnimFootStep;		 //Animation �߹ٴ� ���� ������
extern RWS::CEventId g_EventWeightTime;			 //Animaiton Weight Event
extern RWS::CEventId g_EventSubWeaponActive;	 //sub weapon�� active ��Ų�� ( �� : � ���� �ִ� Į�� �̴´�. )
extern RWS::CEventId g_EventSubWeaponDeActive;	 //sub weapon�� deactive ��Ų�� ( �� : �̾Ҵ� Į�� �ٽ� � ����. )
extern RWS::CEventId g_EventSummon;				 //summmon active ��Ų��.( ��ȯ���� ��ȯ���� ��ȯ��Ű�� timing event. )
extern RWS::CEventId g_EventAlpha;               // Alpha Fade�� �̺�Ʈ
extern RWS::CEventId g_EventAnimTMQ;             // TMQ ����� �̺�Ʈ
extern RWS::CEventId g_EventExplosion;           // ���� �̺�Ʈ
extern RWS::CEventId g_EventAnimPostEffect;      // Post Effect Event
extern RWS::CEventId g_EventAnimDirect;          // ����� �̺�Ʈ
extern RWS::CEventId g_EventAnimColorChange;     // ���󺯰� �̺�Ʈ
extern RWS::CEventId g_EventAnimStretch;         // ���� �þ�� �̺�Ʈ
extern RWS::CEventId g_EventAnimTrigger;         // �پ��ϰ� ���Ǵ� Ʈ���� �̺�Ʈ
extern RWS::CEventId g_EventAnimSkillCancel;	 // ��ųanimation ���� animatin�� cancel�� ������ point.

struct SNtlEventAnimEnd
{
	RwUInt32 uiSerialId;
	RwUInt32 uiBaseAnimKey;
	RwUInt32 uiUpperAnimKey;
};

struct SNtlEventAnimHit
{
	RwUInt32	uiSerialId;
	void		*pData;							//SEventAnimHit(Character\Base  NtlAnimEventData.h)
};


struct SNtlEventFootStep
{
	RwUInt32 uiSerialId;                        ///< ĳ���� ��ü�� �ø��� ID
    void*    pData;                             // SEventFootStep

    //RwBool   bLeftFoot;                         ///< �� ���� (True : ����, False : ������)
};

struct SNtlEventWeightTime						//SEventWeightTime(Character\Base NtlAnimEventData.h)
{
	RwUInt32	uiSerialId;
	void		*pData;
};

struct SNtlEventSubWeaponActive					//sub weapon�� active ��Ų�� ( �� : � ���� �ִ� Į�� �̴´�. )
{
	RwUInt32 uiSerialId;
};

struct SNtlEventSubWeaponDeActive				//sub weapon�� deactive ��Ų�� ( �� : �̾Ҵ� Į�� �ٽ� � ����. )
{
	RwUInt32 uiSerialId;
};

struct SNtlEventSummon							//summmon active ��Ų��.( ��ȯ���� ��ȯ���� ��ȯ��Ű�� timing event. )
{
	RwUInt32 uiSerialId;
};

struct SNtlEventAlpha                           /// Alpha Fade Event
{
    RwUInt32 uiSerialId;
    void*    pData;                             ///< Alpha Fade Event ��ü�� ������
};

struct SNtlPLEventTMQ
{
    RwUInt32    uiSeiralID;                         ///< �̺�Ʈ�� ���� Ÿ�Ӹӽ� ������Ʈ�� �ø��� ID
    RwBool      bIn;                                ///< TMQ ���� ���� (True�� ����/False�� �ƿ�)
};

struct SNtlPlEventExplosion
{
    RwUInt32    uiSerialID;                     ///< ������Ʈ�� �ø��� ID
    void*       pData;                          ///< Explosion Event ����ü�� ������
};

struct SNtlEventPostEffect
{
    RwUInt32    uiSerialID;                     ///< �̺�Ʈ�� �߻��ϴ� �ƹ�Ÿ�� ID
    void*       pData;                          ///< Post Effect Event ����ü�� ������
};

/// ����� �̺�Ʈ
struct SNtlEventDirect
{
    RwUInt32    uiSerialID;                     ///< �̺�Ʈ�� �߻��ϴ� ��ü�� ID
    void*       pData;                          ///< SEventDirect ����ü�� ������
};

/// �÷� ���� �̺�Ʈ
struct SNtlEventColorChange
{
    RwUInt32    uiSerialID;
    void*       pData;                          ///< SEventColorChange ����ü�� ������
};

/// ���ø��� �̺�Ʈ
struct SNtlEventStretch
{
    RwUInt32    uiSerialID;
    void*       pData;                          ///< SEventStretch ����ü�� ������
};

struct SNtlEventTrigger
{
    RwUInt32    uiSerialID;
    void*       pData;                          ///< SEventTrigger ����ü�� ������
};

struct SNtlEventAnimSkillCancel
{
	RwUInt32    uiSerialID;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// world field switching effects
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern RWS::CEventId NPEI_IS_ANOTHER_FIELD_CHANGED;
extern RWS::CEventId NPEI_IS_ANOTHER_FIELD_CHANGED_WITHOUT_DELAY;

extern RWS::CEventId NPEI_IS_ANOTHER_BLOCK_CHANGED;
extern RWS::CEventId NPEI_IS_ANOTHER_BLOCK_CHANGED_WITHOUT_DELAY;

extern RWS::CEventId NPEI_IS_ANOTHER_OBJECT_CHANGED;
extern RWS::CEventId NPEI_IS_ANOTHER_OBJECT_CHANGED_WITHOUT_DELAY;

extern RWS::CEventId NPEI_IS_ANOTHER_SECTOR_CHANGED_WITHOUT_DELAY;
extern RWS::CEventId NPEI_IS_MAPNAME_CHANGE;

// struct sNTL_EVENT_FOG
// {
// 	void *pData;
// };
// 
// struct sNTL_EVENT_VARIATION
// {
// 	void *pData;
// };
// 
struct sNTL_EVENT_MAPNAME
{
 	void *pData;
};
// 
// struct sNTL_EVENT_SECTOR_CHANGED
// {
// 	void *pData;
// };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trigger
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern RWS::CEventId g_EventTriDoodads;

struct sNTL_EVENT_TRI_DOODADS
{
	// 0 : Create, 1 : Delete
	RwBool				FlgTriDoodads;
	std::vector<void*>	vecDat;
};

extern RWS::CEventId g_EventCreateEventObject;
extern RWS::CEventId g_EventThreadLoadingComplete; // ��ƼƼ�� ������ �ε��� �������� �����ϴ� �̺�Ʈ

/// EVENT Object
struct SNtlPLEventEventObject
{
    RwBool          bCreate;        // TRUE : Create, FALSE : Delete
    void*           pData;          // CNtlPlObject Entity
};

struct SNtlPlThreadLoadingComplete
{
    RwUInt32    uiSerialID;                     ///< ��ƼƼ�� �ø��� ID
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gui Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////
/**
* Resolution Resize
*/
//////////////////////////////////////////////

extern RWS::CEventId g_EventResize;						// Resize client window

struct SNtlPLEventResize
{
	RwInt32 iWidht;
	RwInt32 iHeight;
	RwBool bRestore_from_Minimize;
};

//////////////////////////////////////////////
/**
* Cinematic view show / hide
*/
//////////////////////////////////////////////

extern RWS::CEventId g_EventCinematicViewShow;
extern RWS::CEventId g_EventCinematicBalloon;
extern RWS::CEventId g_EventCinematicFlash;
extern RWS::CEventId g_EventCinematicEcho;
extern RWS::CEventId g_EventResetCinematic;				// Cinematic Action�� Reset�Ѵ�. GUI������ ȣ��


//////////////////////////////////////////////
/**
* Cinematic view show / hide
*/
//////////////////////////////////////////////

extern RWS::CEventId g_EventCinematicFadeOut;           // �ó׸�ƽ ���� ����
extern RWS::CEventId g_EventCinematicFadeIn;	        // �ó׸�ƽ ���� ����

//////////////////////////////////////////////
/**
* Cinematic Break
*/
//////////////////////////////////////////////

extern RWS::CEventId g_EventCinematicBreak;


//////////////////////////////////////////////
/**
* ProfilerGui show / hide
*/
//////////////////////////////////////////////
extern RWS::CEventId g_EventShowProfilerGui;

//////////////////////////////////////////////
/**
* Chat Balloon
*/
//////////////////////////////////////////////
extern RWS::CEventId g_EventShowSpectatorBalloon;		
extern RWS::CEventId g_EventHideAllSpectatorBalloon;	

//////////////////////////////////////////////
/**
* Player ����
*/
//////////////////////////////////////////////
extern RWS::CEventId g_EventShowPlayerName;                     ///< Name Show/Hide

extern RWS::CEventId g_EventDirectPlayCancel;



struct SNtlEventCinematicViewShow
{
	RwBool			bShow;
};

struct SNtlEventCinematicBalloon
{
	enum CINEMATICBALLOONPLAY
	{
		PLAY_BEGIN,
		PLAY_PROGRESS
	};

	RwBool			bShow;
	RwUInt32		hSerialId;
	RwUInt32		uiQuestTextTblId;
	RwUInt8			byBalloonType;
	RwUInt8			byEmotionType;
	RwUInt8			byPlayType;
};

struct SNtlEventCinematicFlash
{
	// Flash 
	enum PLAYTIMETYPEFLAG 
	{
		FLAG_BEGIN	= 0x01,
		FLAG_PLAY	= 0x02,
		FLAG_END	= 0x04,

		BEGIN_PLAY_END	= FLAG_BEGIN | FLAG_PLAY | FLAG_END,	// begin + play + end time
		BEGIN_PLAY		= FLAG_BEGIN | FLAG_PLAY,				// begin + play time
		PLAY_END		= FLAG_PLAY | FLAG_END,					// play + end time
		PLAY			= FLAG_PLAY								// play time
	};

	RwBool			bShow;
	RwChar*			pFilename;
	RwBool			bUseTime;							// True : �ð��� False : 1ȸ����
	RwReal			fLifeTime;
	void*			pEchoData;
	RwReal			fBeginAlphaTime;
	RwReal			fEndAlphaTime;		
	RwUInt32		flagPlayTimeType;										
};

struct SNtlEventCinematicEcho
{
	void*			hCinematic;
};

struct SNtlEventResetCinematic
{
	enum TYPE { CINEMATIC, QUESTNARRATION, DBCNARRATION };

	RwUInt32	eDemandResetObject;
};

enum ECinematicFadeInOutType
{
	CINEMATIC_FADEINOUT_SCREEN_PANEL,
	CINEMATIC_FADEINOUT_SHUTDOWN_TV,

	CINEMATIC_INVALID
};

struct SNtlEventCinematicFadeInOut
{
	RwUInt8		byType;
	RwReal		fLifeTime;		// ���� �ð�.
	RwUInt8		byRed;
	RwUInt8		byGreen;
	RwUInt8		byBlue;
	RwUInt8		byEndAlpha;
};

struct SNtlEventShowProfilerGui
{
	RwBool		bShow;
};

struct SNtlEventShowSpectatorBalloon
{
	RwV3d		vPos;
	WCHAR*		szMessage;
	RwReal		fLifeTime;
	RwReal		fFadeInTime;
	RwUInt8		byBalloonType;
};

struct SNtlEventShowPlayerName
{
	RwUInt32	hSerialId;
	RwBool		bShow;
};

struct SNtlEventCharCreateComplete
{
    RwUInt32    hSerialId;
};


#endif