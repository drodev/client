#include "precomp_ntlsound.h"
#include "NtlSoundEvent.h"


RWS::CEventId g_EventSoundReleaseSound;				// �� �� ä���� ���尡 �����Ǿ���

RWS::CEventId g_EventSoundFinishFade;				// ���̵� ��/�ƿ��� ������

RWS::CEventId g_EventSoundDSP;						// ȿ���� ���� �̺�Ʈ

RWS::CEventId g_EventSoundEventMusic;				// �̺�Ʈ���� ä�� �̺�Ʈ

RWS::CEventId g_EventSoundRestTime;					// �ݺ��Ǵ� ������ ���� �÷��̱��� �޽� �ð�

RWS::CEventId g_EventSoundKnockdown;				// �˴ٿ� �� ��

RWS::CEventId g_EventSoundMinMaxRate;				// 3D ������ ��ü Min, Max���� �ٲ۴�