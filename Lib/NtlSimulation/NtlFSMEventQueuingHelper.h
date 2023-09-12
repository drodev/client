/*****************************************************************************
 *
 * File			: NtlFSMEventQueuingHelper.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2006. 9. 26	
 * Abstract		: FSM event queuing helper
 *****************************************************************************
 * Desc         :  ��� ��� �ӽ÷� ����.
 *				  - state�� stack �ϴ� ����� agent�� �����.
 *
 *****************************************************************************/


#ifndef __NTL_FSM_EVENTQUEUING_HELPER_H__
#define __NTL_FSM_EVENTQUEUING_HELPER_H__

class CNtlFSMAgent;

void AgentQueuingTerrainClick(CNtlFSMAgent *pAgent, RwV3d vPos);

void AgentQueuingKeyboardMove(CNtlFSMAgent *pAgent, RwUInt8 byMoveFlags);

#endif