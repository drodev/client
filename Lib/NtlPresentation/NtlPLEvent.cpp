#include "precomp_ntlpresentation.h"
#include "NtlPLEvent.h"


//Animation Event
RWS::CEventId g_EventAnimEnd;			//Animation�� ������ ���
RWS::CEventId g_EventAnimHit;           //Animation Attack Event
RWS::CEventId g_EventAnimFootStep;      //Running �� Character �߹ٴ��� ���� ������
RWS::CEventId g_EventWeightTime;		//Animation WeightTimeEvent
RWS::CEventId g_EventSubWeaponActive;	 //sub weapon�� active ��Ų�� ( �� : � ���� �ִ� Į�� �̴´�. )
RWS::CEventId g_EventSubWeaponDeActive;	 //sub weapon�� deactive ��Ų�� ( �� : �̾Ҵ� Į�� �ٽ� � ����. )
RWS::CEventId g_EventSummon;			 //summmon active ��Ų��.( ��ȯ���� ��ȯ���� ��ȯ��Ű�� timing event. )
RWS::CEventId g_EventAlpha;               // Alpha Fade�� �̺�Ʈ
RWS::CEventId g_EventAnimTMQ;            // TMQ ����� �̺�Ʈ
RWS::CEventId g_EventExplosion;           // ���� �̺�Ʈ
RWS::CEventId g_EventAnimPostEffect;      // Post Effect Event
RWS::CEventId g_EventAnimDirect;          // ���� �̺�Ʈ
RWS::CEventId g_EventAnimColorChange;     // ���󺯰� �̺�Ʈ
RWS::CEventId g_EventAnimStretch;         // �ȴø��� �̺�Ʈ
RWS::CEventId g_EventAnimTrigger;         // Ʈ���� �̺�Ʈ
RWS::CEventId g_EventAnimSkillCancel;	  // anim cancel point	


// world field switching effects
RWS::CEventId NPEI_IS_ANOTHER_FIELD_CHANGED;
RWS::CEventId NPEI_IS_ANOTHER_FIELD_CHANGED_WITHOUT_DELAY;

RWS::CEventId NPEI_IS_ANOTHER_BLOCK_CHANGED;
RWS::CEventId NPEI_IS_ANOTHER_BLOCK_CHANGED_WITHOUT_DELAY;

RWS::CEventId NPEI_IS_ANOTHER_OBJECT_CHANGED;
RWS::CEventId NPEI_IS_ANOTHER_OBJECT_CHANGED_WITHOUT_DELAY;

RWS::CEventId NPEI_IS_ANOTHER_SECTOR_CHANGED_WITHOUT_DELAY;
RWS::CEventId NPEI_IS_MAPNAME_CHANGE;


// trigger
RWS::CEventId g_EventTriDoodads;	// Ʈ���� �ʿ��������� �ε� �Ǵ� �����ɶ�


// Event Object
RWS::CEventId g_EventCreateEventObject; ///< �̺�Ʈ ������Ʈ�� �ε� �Ǵ� ���� �ɶ�
RWS::CEventId g_EventThreadLoadingComplete; // ��ƼƼ�� ������ �ε��� �������� �����ϴ� �̺�Ʈ


// gui event
RWS::CEventId g_EventResize;					// Resize client window

RWS::CEventId g_EventCinematicViewShow;	
RWS::CEventId g_EventCinematicBalloon;
RWS::CEventId g_EventCinematicFlash;
RWS::CEventId g_EventCinematicEcho;
RWS::CEventId g_EventResetCinematic;			// Cinematic Action�� Reset�Ѵ�. GUI������ ȣ��


RWS::CEventId g_EventCinematicFadeOut;         // �ó׸�ƽ ���� ����
RWS::CEventId g_EventCinematicFadeIn;          // �ó׸�ƽ ���� ����

RWS::CEventId g_EventCinematicBreak;			// �ó׸�ƽ ���� break

RWS::CEventId g_EventShowProfilerGui;			// ProfilerGUI Open/Close

RWS::CEventId g_EventShowSpectatorBalloon;
RWS::CEventId g_EventHideAllSpectatorBalloon;

RWS::CEventId g_EventShowPlayerName;			// PlayerName Entity�� Show/Hide

RWS::CEventId g_EventDirectPlayCancel;
