#include "precomp_ntlsound.h"
#include "NtlJingleGroup.h"

#include "NtlSoundEventGenerator.h"

CNtlJingleGroup::CNtlJingleGroup(eChannelGroupType eGroup)
:CNtlChannelGroup(eGroup)
{
}

CNtlJingleGroup::~CNtlJingleGroup()
{
	Destory();
}

eStoreResult CNtlJingleGroup::StoreSound(CNtlSound* pSound, sNtlSoundPlayParameta* pParameta)
{
	if( m_mapGroup.size() == 0 )
	{
		CNtlSoundEventGenerator::SendEventMusic(EVENT_MUSIC_EVENT_MUSIC_HAD_PLAY);
	}

	return CNtlChannelGroup::StoreSound(pSound, pParameta);
}

bool CNtlJingleGroup::Stop(SOUND_HANDLE hHandle)
{
	bool bResult = CNtlChannelGroup::Stop(hHandle);

	// ��� Jingle Music�� ����Ǿ���
	if( bResult && m_mapGroup.size() == 0 )
		CNtlSoundEventGenerator::SendEventMusic(EVENT_MUSIC_ALL_EVENT_MUSIC_FINISH);

	return bResult;
}

void CNtlJingleGroup::StopGroup()
{
	bool bExistChannel = m_mapGroup.size() > 0 ? true : false;

	CNtlChannelGroup::StopGroup();

	// �÷��� �Ǵ� ��� Jingle Music�� ����Ǿ���
	if( bExistChannel )
		CNtlSoundEventGenerator::SendEventMusic(EVENT_MUSIC_ALL_EVENT_MUSIC_FINISH);
}

void CNtlJingleGroup::ReleaseFinishedSound(float fElapsed)
{
	bool bExistChannel = m_mapGroup.size() > 0 ? true : false;

	CNtlChannelGroup::ReleaseFinishedSound(fElapsed);

	// �÷��� �Ǵ� ��� Jingle Music�� ����Ǿ���
	if( bExistChannel && m_mapGroup.size() == 0 )
		CNtlSoundEventGenerator::SendEventMusic(EVENT_MUSIC_ALL_EVENT_MUSIC_FINISH);
}