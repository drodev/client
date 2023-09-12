#pragma once

enum eSoundResultType
{	
	SOUNDRESULT_OK,								// ���� ����/Ȥ�� List�� �����ϱ⸦ �����ߴ�.

	SOUNDRESULT_RECOVERY_FROM_FADE_OUT,			///< Fade out �Ǿ� ��������� ���尡 Fade in�Ǿ� ��� �÷��� �ȴ�

	SOUNDRESULT_NOT_CREATED_SOUND,				///< FMOD::Sound ���� ����

	SOUNDRESULT_FAIL_PLAY,						///< FMOD ���� playSound �Լ��� �����ߴ�

	SOUNDRESULT_INVALID_CHANNELGROUP,			///< eChannelGroupType�� ���� type

	SOUNDRESULT_INVALID_HANDLE_PTR,				///< �߸��� �ڵ鰪�̴�.

	SOUNDRESULT_OUT_OF_RANGE,					///< ���� ������ ������ �����.

	SOUNDRESULT_FULL_DUPLICATION,				///< ���ÿ� ������ �� �ִ� ���� �̸��� ������ Ƚ���� �ʰ��Ͽ���.(���� ���� �÷��� ����)

	SOUNDRESULT_ALREADY_PLAY_SAME_SOUND,		///< ���� �̸��� ���尡 �̹� ���ֵǰ� �ִ�.(���� ���� �÷��� �Ұ�)	

	SOUNDRESULT_EMPTY_FILENAME,					///< �÷����Ϸ��� ���� �̸��� �����ִ�

	SOUNDRESULT_MORE_WAIT_EFFECT_SOUND,			///< ���� �̸��� ����Ʈ ������ ���� ����� �ð����� �÷��� ���� �ʾҴ�

	SOUNDRESULT_MAX_EFFECT_CHANNELS,			///< ������ ����Ʈ ä���� ��� ���� �ִ�

	SOUNDRESULT_NOT_EXIST_FILE,					///< ���� ������ �������� �ʴ´�

	SOUNDRESULT_PROHIBITION_STATE,				///< Mute ����� �ƴ϶� �ƿ� �÷��� ���� �ʰ� �ִ� �����̴�

	SOUNDRESULT_DISABLE_FLASH_MUSIC,			///< �÷��� ���Ǳ׷��� ���� ������� �ʱ�� �Ͽ���

	SOUNDRESULT_FAILT_STORE_SOUND,				///< ���� ������ �����ϴ� ������ �����ߴ�

	SOUNDRESULT_NUM
};