#include "precomp_ntlsound.h"
#include "NtlSoundEvent.h"


RWS::CEventId g_EventSoundReleaseSound;				// �� �� ä���� ���尡 �����Ǿ���

RWS::CEventId g_EventSoundFinishFade;				// ���̵� ��/�ƿ��� ������

RWS::CEventId g_EventSoundDSP;						// ȿ���� ���� �̺�Ʈ

RWS::CEventId g_EventSoundEventMusic;				// ä�� �̺�Ʈ

RWS::CEventId g_EventSoundRestTime;					// �ݺ��Ǵ� ������ ���� �÷��̱��� �޽� �ð�

RWS::CEventId g_EventSoundKnockdown;				// �˴ٿ� �� ��

RWS::CEventId g_EventSoundMinMaxRate;				// 3D ������ ��ü Min, Max���� �ٲ۴�

RWS::CEventId g_EventSoundAddListRangeBGM;			// Range BGM�� ����Ʈ�� �߰�

RWS::CEventId g_EventSoundDelListRangeBGM;			// Range BGM�� ����Ʈ���� ����

RWS::CEventId g_EventSoundChangeListRangeBGM;		// Range BGM�� ���� ����

RWS::CEventId g_EventSoundAddListShareBGM;			// Shard BGM�� ����Ʈ�� �߰�

RWS::CEventId g_EventSoundDeleteAllListShareBGM;	// Shard BGM�� ����Ʈ���� ��� ����

RWS::CEventId g_EventSoundShareBGMPlayRate;			// Shard BGM�� �÷��� �� �� �ִ� Ȯ�� ����

RWS::CEventId g_EventSoundReleaseObjectGroup;		// Turn off all sounds in the Object Group