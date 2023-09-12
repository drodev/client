#include "precomp_ntlsimulation.h"
#include "DboTSCQRecv.h"
#include "DboTSCQCtrl.h"
#include "DboTSCQAgency.h"
#include "NtlSLLogic.h"
#include "NtlSLGlobal.h"
#include "NtlSLApi.h"
#include "NtlSob.h"
#include "NtlSobAvatar.h"
#include "NtlSobPlayerAttr.h"
#include "NtlSobItem.h"
#include "NtlSobItemAttr.h"
#include "NtlSobQuestItem.h"
#include "NtlSobQuestItemAttr.h"
#include "NtlSobManager.h"
#include "TableContainer.h"
#include "ItemTable.h"
#include "SkillTable.h"
#include "QuestItemTable.h"
#include "ObjectTable.h"
#include "NtlSLEventFunc.h"


/** 
	Client quest receiver
*/


NTL_TS_IMPLEMENT_RTTI( CDboTSCQRecv, CDboTSQRecv )


NTL_TSRESULT CDboTSCQRecv::Search( CNtlTSEntity* pEntity, void* pParam )
{
	return NTL_TSRESULT_TYPE_SUCCESS;
}

NTL_TSRESULT CDboTSCQRecv::Run( CNtlTSEntity* pEntity, void* pParam )
{
	sCQRUN_PARAM* pQParam = (sCQRUN_PARAM*)pParam;

	NTL_TSRESULT tsResult = NTL_TSRESULT_TYPE_SUCCESS;

	switch ( pEntity->GetEntityType() )
	{

//////////////////////////////////////////////////////////////////////////
//
//	Event
//	Ŭ���̾�Ʈ������ �̺�Ʈ�� ���ؼ��� �� �˻� ó���� �ǹǷ� �̰�������
//	�˻縦 �������� �ʴ´�
//
//////////////////////////////////////////////////////////////////////////

	case DBO_EVENT_TYPE_ID_CLICK_NPC:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_CLICK_NPC &&
				 ((CDboTSClickNPC*)pEntity)->GetNPCIdx() == pQParam->GetCtrl()->GetEventGenId() ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_CLICK_OBJECT:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_CLICK_OBJECT &&
				 ((CDboTSClickObject*)pEntity)->GetWorldIdx() == GetNtlSLGlobal()->GetAvatarInfo()->sWorldInfo.tblidx && 
				 ((CDboTSClickObject*)pEntity)->HasObjectIdx( pQParam->GetCtrl()->GetEventGenId() ) ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_COL_OBJECT:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_COL_OBJECT &&
				 ((CDboTSColObject*)pEntity)->GetWorldIdx() == GetNtlSLGlobal()->GetAvatarInfo()->sWorldInfo.tblidx && 
				 ((CDboTSColObject*)pEntity)->HasObjectIdx( pQParam->GetCtrl()->GetEventGenId() ) ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_ITEM_USE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_ITEM_USE )
			{
				if ( ((CDboTSItemUse*)pEntity)->GetItemIdx() == pQParam->GetCtrl()->GetEventGenId() )
				{
					eEVENT_ITEM_TARGET_TYPE eTargetType = ((CDboTSItemUse*)pEntity)->GetItemTargetType();
					if ( eEVENT_ITEM_TARGET_TYPE_ALL == eTargetType )
					{
						break;
					}

					bool bFind = false;
					vecdef_ItemTargetList& defItemTargetList = pQParam->GetCtrl()->GetEventGenItemTargetInfo();
					vecdef_ItemTargetList::iterator it = defItemTargetList.begin();
					for ( ; it != defItemTargetList.end(); ++it )
					{
						if ( eEVENT_ITEM_TARGET_TYPE_NPC == eTargetType &&
							 SLCLASS_NPC == (*it).uiClassID &&
							 (*it).tblIdx == ((CDboTSItemUse*)pEntity)->GetItemTargetIdx() )
						{
							bFind = true;
							break;
						}

						if ( eEVENT_ITEM_TARGET_TYPE_MOB == eTargetType &&
							 SLCLASS_MONSTER == (*it).uiClassID &&
							 (*it).tblIdx == ((CDboTSItemUse*)pEntity)->GetItemTargetIdx() )
						{
							bFind = true;
							break;
						}

						if ( eEVENT_ITEM_TARGET_TYPE_AVATAR == eTargetType &&
							 SLCLASS_AVATAR == (*it).uiClassID )
						{
							bFind = true;
							break;
						}
					}

					if ( !bFind )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				else
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_ITEM_GET:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_ITEM_GET &&
				 ((CDboTSItemGet*)pEntity)->GetItemIdx() == pQParam->GetCtrl()->GetEventGenId() ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_ITEM_EQUIP:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_ITEM_EQUIP &&
				 ((CDboTSItemEquip*)pEntity)->GetItemIdx() == pQParam->GetCtrl()->GetEventGenId() ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_SCOUT_USE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_SCOUT_USE )
			{
				if ( ((CDboTSScoutUse*)pEntity)->GetItemIdx() == pQParam->GetCtrl()->GetEventGenId() )
				{
					eEVENT_SCOUTER_TARGET_TYPE eTargetType = ((CDboTSScoutUse*)pEntity)->GetTargetType();
					if ( eEVENT_SCOUTER_TARGET_TYPE_ALL == eTargetType )
					{
						break;
					}

					bool bFind = false;

					SScouterUseTargetInfo& sTargetInfo = pQParam->GetCtrl()->GetEventGenScouterUseTargetInfo();

					if ( eEVENT_SCOUTER_TARGET_TYPE_NPC == eTargetType &&
						 SLCLASS_NPC == sTargetInfo.uiClassID &&
						 sTargetInfo.tblIdx == ((CDboTSScoutUse*)pEntity)->GetTargetIdx() )
					{
						bFind = true;
					}

					if ( eEVENT_SCOUTER_TARGET_TYPE_MOB == eTargetType &&
						 SLCLASS_MONSTER == sTargetInfo.uiClassID &&
						 sTargetInfo.tblIdx == ((CDboTSScoutUse*)pEntity)->GetTargetIdx() )
					{
						bFind = true;
					}

					if ( eEVENT_SCOUTER_TARGET_TYPE_AVATAR == eTargetType &&
						 SLCLASS_AVATAR == sTargetInfo.uiClassID )
					{
						bFind = true;
					}

					if ( !bFind )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				else
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;
	case DBO_EVENT_TYPE_ID_RCV_SVR_EVT:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_RCV_SVR_EVT &&
				 ((CDboTSRcvSvrEvt*)pEntity)->GetEvtID() == pQParam->GetCtrl()->GetEventGenId() ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_SKILL_USE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_SKILL_USE )
			{
				CSkillTable* pSkillTable = API_GetTableContainer()->GetSkillTable();

				// Skill type �˻�
				if ( eEVENT_SKILL_TYPE_SKILLIDX == pQParam->GetCtrl()->GetEventGenSkillUseInfo().eSkillType )
				{
					if ( 0xffffffff == ((CDboTSSkillUse*)pEntity)->GetSkillIdx() || ( pSkillTable->FindBasicSkillTblidx( ((CDboTSSkillUse*)pEntity)->GetSkillIdx() ) == pSkillTable->FindBasicSkillTblidx( pQParam->GetCtrl()->GetEventGenId() ) ) )
					{
						// Skill target �˻�
						eEVENT_SKILL_TARGET_TYPE eTargetType = ((CDboTSSkillUse*)pEntity)->GetSkillTargetType();
						if ( eEVENT_SKILL_TARGET_TYPE_ALL != eTargetType )
						{
							bool bFind = false;
							vecdef_SkillTargetList& defSkillTargetList = pQParam->GetCtrl()->GetEventGenSkillUseInfo().defSkillTargetList;
							vecdef_SkillTargetList::iterator it = defSkillTargetList.begin();
							for ( ; it != defSkillTargetList.end(); ++it )
							{
								if ( eEVENT_SKILL_TARGET_TYPE_NPC == eTargetType &&
									 SLCLASS_NPC == (*it).uiClassID &&
									 (*it).tblIdx == ((CDboTSSkillUse*)pEntity)->GetSkillTargetIdx() )
								{
									bFind = true;
									break;
								}

								if ( eEVENT_SKILL_TARGET_TYPE_MOB == eTargetType &&
									 SLCLASS_MONSTER == (*it).uiClassID &&
									 (*it).tblIdx == ((CDboTSSkillUse*)pEntity)->GetSkillTargetIdx() )
								{
									bFind = true;
									break;
								}
							}

							if ( !bFind )
							{
								tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								break;
							}
						}
					}
				}
				else
				{
					if ( ((CDboTSSkillUse*)pEntity)->GetSkillType() != pQParam->GetCtrl()->GetEventGenSkillUseInfo().eSkillType )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
						break;
					}
				}

				// Skill RP �˻�
				{
					unsigned int uiSkillRPFlags = ((CDboTSSkillUse*)pEntity)->GetSkillRPFlags();

					// uiSkillRPFlags == 0 �̸� RP �˻縦 �������� �ʴ´�
					if ( 0 != uiSkillRPFlags )
					{
						unsigned char byRpBonusType = pQParam->GetCtrl()->GetEventGenSkillUseInfo().byRpBonusType;

						switch ( byRpBonusType )
						{
						case DBO_RP_BONUS_TYPE_KNOCKDOWN:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_KNOCKDOWN )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case DBO_RP_BONUS_TYPE_RESULT_PLUS:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_POWER )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case DBO_RP_BONUS_TYPE_EP_MINUS:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_EP_MINUS )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case DBO_RP_BONUS_TYPE_KEEP_TIME_PLUS:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_KEEP_TIME_PLUS )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case DBO_RP_BONUS_TYPE_CASTING_TIME_MINUS:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_CASTING_TIME_MINUS )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case DBO_RP_BONUS_TYPE_COOL_TIME_MINUS:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_COOL_TIME_NINUS )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case DBO_RP_BONUS_TYPE_GUARD_CRASH:
							{
								if ( !(uiSkillRPFlags & (1<<eEVENT_SKILL_RP_GUARD_CRASH )) )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						default:
							{
								tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
							}
							break;
						}

						if ( tsResult & NTL_TSRESULT_TYPE_COND_CAN_PROGRESS )
						{
							break;
						}
					}
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_COL_RGN:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_COL_REGION )
			{
				CDboTSColRgn* pColRgnEntity = (CDboTSColRgn*)pEntity;
				sCOL_RGN_DATA& sColRgnData = pQParam->GetCtrl()->GetEventGenColRgnInfo();

				if ( 0xffffffff == pColRgnEntity->GetWorldIdx() )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
					break;
				}

				if ( pColRgnEntity->GetWorldIdx() == sColRgnData.uiWorldIdx )
				{
					switch ( sColRgnData.eWorldChangeType )
					{
					case sCOL_RGN_DATA::eWORLD_CHANGE_TYPE_ENTER:
						{
							if ( !(eCOL_RESULT_TYPE_ENTER & pColRgnEntity->GetColCheckType()) ||
								 !pColRgnEntity->InCheck( sColRgnData.fBeginX, sColRgnData.fBeginZ ) )
							{
								tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
							}
						}
						break;

					case sCOL_RGN_DATA::eWORLD_CHANGE_TYPE_LEAVE:
						{
							if ( !(eCOL_RESULT_TYPE_LEAVE & pColRgnEntity->GetColCheckType()) ||
								 !pColRgnEntity->InCheck( sColRgnData.fBeginX, sColRgnData.fBeginZ ) )
							{
								tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
							}
						}
						break;

					case sCOL_RGN_DATA::eWORLD_CHANGE_TYPE_NO:
						{
							if ( !pColRgnEntity->ColCheck( sColRgnData.fBeginX, sColRgnData.fBeginZ, sColRgnData.fEndX, sColRgnData.fEndZ ) )
							{
								tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
							}
						}
						break;

					default:
						{
							tsResult |= NTL_TSRESULT_TYPE_ERROR;
						}
						break;
					}
				}
				else
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_RB:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_RB )
			{
				SRB_DATA& sRBData = pQParam->GetCtrl()->GetEventGenRBData();

				CDboTSRB* pRB = (CDboTSRB*)pEntity;
				unsigned int uiRBTblIdx = pRB->GetRBTblIdx();
				unsigned int uiRBCondition = pRB->GetRBCondition();

				if ( 0xffffffff == uiRBTblIdx )
				{
					if ( eRB_COND_FLAG_INVALID == (uiRBCondition & sRBData.eRBCondFlag) )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				else
				{
					if ( pQParam->GetCtrl()->GetEventGenId() == uiRBTblIdx )
					{
						if ( eRB_COND_FLAG_INVALID == (uiRBCondition & sRBData.eRBCondFlag) )
						{
							tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
						}
					}
					else
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_CLICK_MOB:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_CLICK_MOB &&
				 ((CDboTSClickMob*)pEntity)->GetMobGroupIdx() == pQParam->GetCtrl()->GetEventGenId() ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_BIND_STONE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_BIND_STONE ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_SEARCH_QUEST:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_SEARCH_QUEST ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_ITEM_UPGRADE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_ITEM_UPGRADE ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_TELEPORT:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_TELEPORT ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_BUDOKAI:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_BUDOKAI ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_SLOTMACHINE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_SLOTMACHINE ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_HOIPOIMIX:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_HOIPOIMIX ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_PRIVATESHOP:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_PRIVATESHOP ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_FREEBATTLE:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_FREEBATTLE ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_ITEMIDENTITY:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_ITEMIDENTITY ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

	case DBO_EVENT_TYPE_ID_USERMAIL:
		{
			// ����Ʈ ��ũ �˻���� ��� �̺�Ʈ �˻�� Success�� ó���Ѵ�
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_USEMAIL ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

		case DBO_EVENT_TYPE_ID_PARTY:
		{
			// For the quest mark check, the event check is treated as Success
			if ( pQParam->IsForCheckQuestMark() ) break;

			if ( pQParam->IsQuestShare() ) break;

			if ( !( pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_PARTY ) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

		case DBO_EVENT_TYPE_ID_CLICK_SIDEICON:
		{
			// For the quest mark check, the event check is treated as Success
			if (pQParam->IsForCheckQuestMark()) break;

			if (pQParam->IsQuestShare()) break;

			if (!(pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_CLICK_SIDEICON))
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

		case DBO_EVENT_TYPE_ID_DIALOGOPEN:
		{
			// For the quest mark check, the event check is treated as Success
			if (pQParam->IsForCheckQuestMark()) break;

			if (pQParam->IsQuestShare()) break;

			if (!(pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_DIALOGOPEN))
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

		case DBO_EVENT_TYPE_ID_QUEST:
		{
			// For the quest mark check, the event check is treated as Success
			if (pQParam->IsForCheckQuestMark()) break;

			if (pQParam->IsQuestShare()) break;

			if (!(pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_QUEST))
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

		case DBO_EVENT_TYPE_ID_LEVELCHECK:
		{
			// For the quest mark check, the event check is treated as Success
			if (pQParam->IsForCheckQuestMark()) break;

			if (pQParam->IsQuestShare()) break;

			if (!(pQParam->GetCtrl()->GetEventGenType() == eEVENT_GEN_TYPE_LEVELCHECK))
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
			}
		}
		break;

//////////////////////////////////////////////////////////////////////////
//
//	Condition
//	Ŭ���̾�Ʈ ��⿡�� ó�� �Ǿ�� ��
//
//////////////////////////////////////////////////////////////////////////

	case DBO_COND_TYPE_ID_CHECK_LVL:
		{
			int nLvl = Logic_GetLevel( GetNtlSLGlobal()->GetSobAvatar() );
			CDboTSCheckLvl* pLvl = (CDboTSCheckLvl*)pEntity;

			if ( pLvl->GetMinLvl() > nLvl )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_LEVEL", FALSE, pQuestText );
				}
			}
			else if ( pLvl->GetMaxLvl() < nLvl )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_LEVEL", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_PCCLS:
		{
			unsigned int uiCls = (unsigned int)((CNtlSobPlayerAttr*)GetNtlSLGlobal()->GetSobAvatar()->GetSobAttr())->GetClass();

			if ( !(((CDboTSCheckPCCls*)pEntity)->GetClsFlags() & (1<<uiCls)) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_PC_CLASS", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_PCRACE:
		{
			unsigned int uiRace = (unsigned int)((CNtlSobPlayerAttr*)GetNtlSLGlobal()->GetSobAvatar()->GetSobAttr())->GetRace();

			if ( !(((CDboTSCheckPCRace*)pEntity)->GetRaceFlags() & (1<<uiRace)) )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_PC_RACE", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_QITEM:
		{
			CDboTSCheckQItem* pQItem = (CDboTSCheckQItem*)pEntity;

			int nSum = 0;

			CNtlQuestInventory* pQuestInventory = GetNtlSLGlobal()->GetSobAvatar()->GetQuestInventory();
			for ( int i = 0; i < MAX_QUEST_INVENTORY_SLOT; ++i )
			{
				CNtlSobQuestItem* pSobQItem = pQuestInventory->GetQuestItemFromIdx( i );
				if ( pSobQItem )
				{
					CNtlSobQuestItemAttr* pSobQItemAttr = reinterpret_cast<CNtlSobQuestItemAttr*>(pSobQItem->GetSobAttr());
					if ( pSobQItemAttr->GetQuestItemTbl()->tblidx == pQItem->GetItemIdx() )
					{
						nSum += pSobQItemAttr->GetStackNum();
					}
				}
			}

			switch ( pQItem->GetCheckType() )
			{
			case eQUEST_ITEM_CHECK_TYPE_EQUAL:
				{
					if ( nSum != pQItem->GetItemCnt() )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

						if ( pQParam->IsQuestShareOutMsg() )
						{
							const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
							CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_QITEM", FALSE, pQuestText );
						}
					}
				}
				break;
			case eQUEST_ITEM_CHECK_TYPE_MORE:
				{
					if ( nSum < pQItem->GetItemCnt() )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

						if ( pQParam->IsQuestShareOutMsg() )
						{
							const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
							CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_QITEM", FALSE, pQuestText );
						}
					}
				}
				break;
			case eQUEST_ITEM_CHECK_TYPE_LESS:
				{
					if ( nSum > pQItem->GetItemCnt() )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

						if ( pQParam->IsQuestShareOutMsg() )
						{
							const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
							CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_QITEM", FALSE, pQuestText );
						}
					}
				}
				break;

			default:
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				break;
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_CLRQST:
		{
			CDboTSCheckClrQst* pClrQst = (CDboTSCheckClrQst*)pEntity;
			std::vector<NTL_TS_T_ID>::const_iterator it;

			const std::vector<NTL_TS_T_ID>& AndList = pClrQst->GetAndIdList();
			if ( !AndList.empty() )
			{
				bool bCleared = true;
				for ( it = AndList.begin(); it != AndList.end(); ++it )
				{
					bCleared &= pQParam->GetAgency()->GetCompletedQInfo()->HasBeenClearQuest( *it );
				}
				if ( !bCleared )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

					if ( pQParam->IsQuestShareOutMsg() )
					{
						const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
						CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_COMPLETE", FALSE, pQuestText );
					}
				}
			}

			const std::vector<NTL_TS_T_ID>& OrList = pClrQst->GetOrIdList();
			if ( !OrList.empty() )
			{
				bool bCleared = false;
				for ( it = OrList.begin(); it != OrList.end(); ++it )
				{
					bCleared |= pQParam->GetAgency()->GetCompletedQInfo()->HasBeenClearQuest( *it );
					if ( bCleared ) break;
				}
				if ( !bCleared )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

					if ( pQParam->IsQuestShareOutMsg() )
					{
						const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
						CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_COMPLETE", FALSE, pQuestText );
					}
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_STOCEVT:
		{
			switch ( pQParam->GetCtrl()->GetServerEvtDataType() )
			{
			case eSTOC_EVT_DATA_TYPE_MOB_KILL_CNT:
				{
					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_MOB_KILL; ++i )
					{
						if ( 0xffffffff == pQParam->GetCtrl()->GetServerEvtData().sMobKillCnt[i].uiMobIdx ) continue;

						bRet &= ( pQParam->GetCtrl()->GetServerEvtData().sMobKillCnt[i].nMobCnt <= 
								  pQParam->GetCtrl()->GetServerEvtData().sMobKillCnt[i].nCurMobCnt ) ? true : false;
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;
			case eSTOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT:
				{
					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_MOB_KILL_ITEM; ++i )
					{
						if ( 0xffffffff == pQParam->GetCtrl()->GetServerEvtData().sMobKillItemCnt[i].uiMobLIIdx ) continue;

						bRet &= ( pQParam->GetCtrl()->GetServerEvtData().sMobKillItemCnt[i].nMobLICnt <= 
								  pQParam->GetCtrl()->GetServerEvtData().sMobKillItemCnt[i].nCurMobLICnt ) ? true : false;
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;
			case eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM:
				{
					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_DELIVERY_ITEM; ++i )
					{
						if ( 0xffffffff == pQParam->GetCtrl()->GetServerEvtData().sDeliveryItemCnt[i].uiItemIdx ) continue;

						bRet &= ( 0 >= pQParam->GetCtrl()->GetServerEvtData().sDeliveryItemCnt[i].nCurItemCnt ) ? true : false;
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;
			case eSTOC_EVT_DATA_TYPE_OBJECT_ITEM:
				{
					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_OBJECT_ITEM; ++i )
					{
						if ( 0xffffffff == pQParam->GetCtrl()->GetServerEvtData().sObjectItemCnt[i].uiItemIdx ) continue;

						bRet &= ( pQParam->GetCtrl()->GetServerEvtData().sObjectItemCnt[i].nItemCnt <= 
								  pQParam->GetCtrl()->GetServerEvtData().sObjectItemCnt[i].nCurItemCnt ) ? true : false;
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;
			case eSTOC_EVT_DATA_TYPE_PUBLIC_MOB_ITEM_CNT:
				{
					CNtlQuestInventory* pQInventory = GetNtlSLGlobal()->GetSobAvatar()->GetQuestInventory();

					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_PUBLIC_MOB_ITEM; ++i )
					{
						if ( !bRet )
						{
							break;
						}

						if ( 0xffffffff == pQParam->GetCtrl()->GetServerEvtData().sPublicMobItemCnt[i].uiItemIdx ) continue;

						bRet &= ( pQParam->GetCtrl()->GetServerEvtData().sPublicMobItemCnt[i].nItemCnt <=
								  pQParam->GetCtrl()->GetServerEvtData().sPublicMobItemCnt[i].nCurItemCnt ) ? true : false;

						if ( !bRet )
						{
							break;
						}

						// �ʿ��� �������� Invalid �� ��� �ʿ� �������� ���� ���� ����
						unsigned int uiNeedItemIdx = pQParam->GetCtrl()->GetServerEvtData().sPublicMobItemCnt[i].uiRequireItemIdx;
						if ( 0xffffffff == uiNeedItemIdx ) continue;

						// �ش� ����Ʈ �������� ������ ������ �ִ��� �˻��Ѵ�
						{
							int nSumCnt = 0;

							// Quest inventory�� �˻�
							for ( int j = 0; j < MAX_QUEST_INVENTORY_SLOT; ++j )
							{
								CNtlSobQuestItem* pQItem = pQInventory->GetQuestItemFromIdx( j );
								if ( 0 == pQItem ) continue;

								CNtlSobQuestItemAttr* pQItemAttr = reinterpret_cast< CNtlSobQuestItemAttr* > ( pQItem->GetSobAttr() );

								if ( pQItemAttr->GetQuestItemTbl()->tblidx == uiNeedItemIdx )
								{
									nSumCnt += pQItemAttr->GetStackNum();
								}
							}

							bRet &= (nSumCnt > 0 ? true : false);

							if ( !bRet )
							{
								break;
							}
						}
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;

			case eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT:
				{
					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_CUSTOM_EVT_CNT; ++i )
					{
						if ( 0xffffffff == pQParam->GetCtrl()->GetServerEvtData().sCustomEvtCnt[i].uiCustomEvtID ) continue;

						bRet &= ( pQParam->GetCtrl()->GetServerEvtData().sCustomEvtCnt[i].nMaxCnt <= 
								  pQParam->GetCtrl()->GetServerEvtData().sCustomEvtCnt[i].nCurCnt ) ? true : false;
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;

			case eSTOC_EVT_DATA_TYPE_VISIT:
				{
					bool bRet = true;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_VISIT_EVT; ++i )
					{
						if ( 0xff == pQParam->GetCtrl()->GetServerEvtData().sVisitEvt[i].byObjType ) continue;

						bRet &= pQParam->GetCtrl()->GetServerEvtData().sVisitEvt[i].bCompleted;
					}

					if ( !bRet )
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				break;
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_ITEM:
		{
			CDboTSCheckItem* pItem = (CDboTSCheckItem*)pEntity;

			CNtlInventory *pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();

			int nSumCnt = 0;

			// Equip â�� �˻�
			for ( int i = 0; i < NTL_MAX_EQUIP_ITEM_SLOT; ++i )
			{
				CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetEquipItem( i ) ) );
				if ( 0 == pSobItem ) continue;

				CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
				if ( pSobItemAttr->GetTblIdx() == pItem->GetItemIdx() )
				{
					nSumCnt += pSobItemAttr->GetStackNum();
				}
			}

			// Bag â�� �˻�
			for ( int i = 0; i < NTL_MAX_BAGSLOT_COUNT; ++i )
			{
				CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetBagItem( i ) ) );
				if ( 0 == pSobItem ) continue;

				int nChildCnt = pSobItem->GetChildNum();
				for ( int j = 0; j < nChildCnt; ++j )
				{
					CNtlSobItem* pChildSobItem = pSobItem->GetChildItem( j );
					if ( 0 == pChildSobItem ) continue;

					CNtlSobItemAttr* pChildSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pChildSobItem->GetSobAttr());
					if ( pChildSobItemAttr->GetTblIdx() == pItem->GetItemIdx() )
					{
						nSumCnt += pChildSobItemAttr->GetStackNum();
					}
				}

				CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
				if ( pSobItemAttr->GetTblIdx() == pItem->GetItemIdx() )
				{
					nSumCnt += pSobItemAttr->GetStackNum();
				}
			}

			if ( pItem->GetItemCnt() > nSumCnt )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_ITEM", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_WITEM:
		{
			CDboTSCheckItem* pItem = (CDboTSCheckItem*)pEntity;

			CNtlInventory *pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();

			bool bFind = false;

			// Equip â�� �˻�
			for ( int i = 0; i < NTL_MAX_EQUIP_ITEM_SLOT; ++i )
			{
				CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetEquipItem( i ) ) );
				if ( 0 == pSobItem ) continue;

				CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
				if ( pSobItemAttr->GetTblIdx() == pItem->GetItemIdx() &&
					 pSobItemAttr->GetStackNum() >= pItem->GetItemCnt() )
				{
					bFind = true;
					break;
				}
			}

			if ( !bFind )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_EQUIP_ITEM", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_SSM:
		{
			CDboTSCheckSSM* pSSM = (CDboTSCheckSSM*)pEntity;

			switch ( pSSM->GetOPType() )
			{
			case eSSM_OP_TYPE_EQUAL:
				if ( pSSM->GetVariable() != pQParam->GetCtrl()->GetSSM( pSSM->GetSSMId() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				break;
			case eSSM_OP_TYPE_NOT_EQUAL:
				if ( pSSM->GetVariable() != pQParam->GetCtrl()->GetSSM( pSSM->GetSSMId() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				break;
			case eSSM_OP_TYPE_LESS:
				if ( pSSM->GetVariable() != pQParam->GetCtrl()->GetSSM( pSSM->GetSSMId() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				break;
			case eSSM_OP_TYPE_LESS_EQUAL:
				if ( pSSM->GetVariable() != pQParam->GetCtrl()->GetSSM( pSSM->GetSSMId() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				break;
			case eSSM_OP_TYPE_MORE:
				if ( pSSM->GetVariable() != pQParam->GetCtrl()->GetSSM( pSSM->GetSSMId() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				break;
			case eSSM_OP_TYPE_MORE_EQUAL:
				if ( pSSM->GetVariable() != pQParam->GetCtrl()->GetSSM( pSSM->GetSSMId() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				break;
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_OBJITEM:
		{
			// Object �� �������� �� �� �ִ��� �˻��ϴ� ������
			// ����Ʈ������ �������� �ʴ´�
			CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
							pQParam->GetCtrl()->GetTrigger()->GetID(),
							((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
							((CNtlTSCont*)pEntity->GetParent())->GetID(),
							TS_CODE_TRACE() );
			tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_IN_NPC:
		{
			CDboTSCheckInNPC* pInNPC = (CDboTSCheckInNPC*)pEntity;

			RwV3d v3AvatarPos = GetNtlSLGlobal()->GetSobAvatar()->GetPosition();

			CNtlSob* pSobObj = GetNtlSobManager()->GetSobObject( GetNtlSobManager()->GetNpcTriggerSerialFromId( pInNPC->GetNPCIndex() ) );
			if ( pSobObj )
			{
				RwV3d v3DestPos = pSobObj->GetPosition();

				float fSDist = (v3DestPos.x-v3AvatarPos.x)*(v3DestPos.x-v3AvatarPos.x) + (v3DestPos.z-v3AvatarPos.z)*(v3DestPos.z-v3AvatarPos.z);
				if ( fSDist - (pInNPC->GetRadius()*pInNPC->GetRadius()) > 0.f )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

					if ( pQParam->IsQuestShareOutMsg() )
					{
						const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
						CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_NPC_REGION", FALSE, pQuestText );
					}
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_NPC_REGION", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_OBJ_STATE:
		{
			// ����Ʈ������ �������� �ʴ´�
			CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
							pQParam->GetCtrl()->GetTrigger()->GetID(),
							((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
							((CNtlTSCont*)pEntity->GetParent())->GetID(),
							TS_CODE_TRACE() );
			tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_IN_WORLD:
		{
			CDboTSCheckInWorld* pInWorld = (CDboTSCheckInWorld*)pEntity;

			if ( pInWorld->GetWorldTblIdx() != GetNtlSLGlobal()->GetAvatarInfo()->sWorldInfo.tblidx )
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;

				if ( pQParam->IsQuestShareOutMsg() )
				{
					const wchar_t* pQuestText = pQParam->GetAgency()->GetQuestText( pQParam->GetCtrl()->GetTrigger()->GetID() );
					CNtlSLEventGenerator::FormatSysMsg( INVALID_SERIAL_ID, "DST_QUEST_SHARE_COND_IN_WORLD", FALSE, pQuestText );
				}
			}
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_OPERATEOBJECT:
		{
			// ����Ʈ������ �������� �ʴ´�
			CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
							pQParam->GetCtrl()->GetTrigger()->GetID(),
							((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
							((CNtlTSCont*)pEntity->GetParent())->GetID(),
							TS_CODE_TRACE() );
			tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_HASCOUPON:
		{
			// ����Ʈ������ �������� �ʴ´�
			CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
							pQParam->GetCtrl()->GetTrigger()->GetID(),
							((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
							((CNtlTSCont*)pEntity->GetParent())->GetID(),
							TS_CODE_TRACE() );
			tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_NPCDEAD:
		{
			// ������ ���� Ÿ�̸ӿ����� ���� �ϴ� �ڵ��
			// Ŭ���̾�Ʈ�� �̰��� ȣ�� �Ǹ� �ȵ�.
			CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
							pQParam->GetCtrl()->GetTrigger()->GetID(),
							((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
							((CNtlTSCont*)pEntity->GetParent())->GetID(),
							TS_CODE_TRACE() );
			tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_DIST_WITH_NPC:
		{
			// ������ ���� Ÿ�̸ӿ����� ���� �ϴ� �ڵ��
			// Ŭ���̾�Ʈ�� �̰��� ȣ�� �Ǹ� �ȵ�.
			CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
							pQParam->GetCtrl()->GetTrigger()->GetID(),
							((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
							((CNtlTSCont*)pEntity->GetParent())->GetID(),
							TS_CODE_TRACE() );
			tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
		}
		break;

	case DBO_COND_TYPE_ID_CHECK_STOC_DELIVERTY:
		{
			CDboTSCQCtrl* pCtrl = pQParam->GetCtrl();

			// 1. ����Ʈ�� Fail �Ǵ� Error ������ ��� �������� �� �� ����.
			if ( !pCtrl->IsFailed() && !pCtrl->IsError() )
			{
				// 2. Delivery item ���� �̺�Ʈ�� ���� ������ �˻��Ѵ�.
				if ( eSTOC_EVT_DATA_TYPE_DELIVERY_ITEM == pCtrl->GetServerEvtDataType() )
				{
					// 3. ���� ���� ���� ��츸 ���� �˻縦 ����Ѵ�.

					CDboTSCheckSToCDelivery* pDelivery = (CDboTSCheckSToCDelivery*) pEntity;

					uSTOC_EVT_DATA& uSToCData = pCtrl->GetServerEvtData();

					bool bCanProcess = true;
					int nCheckCnt;
					for ( int i = 0; i < uSTOC_EVT_DATA::MAX_DELIVERY_ITEM; ++i )
					{
						if ( 0xffffffff == uSToCData.sDeliveryItemCnt[i].uiItemIdx ) continue;

						nCheckCnt = pDelivery->GetItemCntFromItemIdx( uSToCData.sDeliveryItemCnt[i].uiItemIdx );
						if ( -1 == nCheckCnt ) continue;

						if ( uSToCData.sDeliveryItemCnt[i].nCurItemCnt + nCheckCnt < uSToCData.sDeliveryItemCnt[i].nItemCnt )
						{
							bCanProcess &= true;
						}
						else
						{
							bCanProcess &= false;
						}
					}

					if ( bCanProcess )
					{
						// 4. SToC Condition �˻�

						uSTOC_EVT_COND_DATA& uSToCCondData = pCtrl->GetServerEvtCondData();

						CNtlInventory *pInventory = GetNtlSLGlobal()->GetSobAvatar()->GetInventory();

						switch ( pCtrl->GetServerEvtCondDataType() )
						{
						case eSTOC_EVT_COND_DATA_TYPE_AUTO_EQUIP_ITEM:
							{
								bool bSatisfyCond = true;

								for ( int i = 0; i < uSTOC_EVT_COND_DATA::MAX_AUTO_EQUIP_ITEM; ++i )
								{
									if ( 0xffffffff == uSToCCondData.sAutoEquipItem[i].uiItemTblIdx ) continue;

									// Equip â���� ������ �˻�
									bool bFind = false;
									for ( int j = 0; j < NTL_MAX_EQUIP_ITEM_SLOT; ++j )
									{
										CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetEquipItem( j ) ) );
										if ( 0 == pSobItem ) continue;

										CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
										if ( pSobItemAttr->GetTblIdx() == uSToCCondData.sAutoEquipItem[i].uiItemTblIdx )
										{
											bFind = true;
											break;
										}
									}

									bSatisfyCond &= bFind;
								}

								if ( !bSatisfyCond )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case eSTOC_EVT_COND_DATA_TYPE_EQUIP_ITEM:
							{
								bool bSatisfyCond = true;

								for ( int i = 0; i < uSTOC_EVT_COND_DATA::MAX_EQUIP_ITEM; ++i )
								{
									if ( 0xffffffff == uSToCCondData.sEquipItem[i].uiItemTblIdx ) continue;

									// Equip â���� ������ �˻�
									bool bFind = false;
									for ( int j = 0; j < NTL_MAX_EQUIP_ITEM_SLOT; ++j )
									{
										CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetEquipItem( j ) ) );
										if ( 0 == pSobItem ) continue;

										CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
										if ( pSobItemAttr->GetTblIdx() == uSToCCondData.sEquipItem[i].uiItemTblIdx )
										{
											bFind = true;
											break;
										}
									}

									bSatisfyCond &= bFind;
								}

								if ( !bSatisfyCond )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case eSTOC_EVT_COND_DATA_TYPE_HAVE_ITEM:
							{
								bool bSatisfyCond = true;

								for ( int i = 0; i < uSTOC_EVT_COND_DATA::MAX_HAVE_ITEM; ++i )
								{
									if ( 0xffffffff == uSToCCondData.sHaveItem[i].uiItemTblIdx ) continue;

									bool bFind = false;

									// Equip â���� ������ �˻�
									for ( int j = 0; j < NTL_MAX_EQUIP_ITEM_SLOT; ++j )
									{
										CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetEquipItem( j ) ) );
										if ( 0 == pSobItem ) continue;

										CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
										if ( pSobItemAttr->GetTblIdx() == uSToCCondData.sHaveItem[i].uiItemTblIdx )
										{
											bFind = true;
											break;
										}
									}

									// Bag â���� ������ �˻�
									if ( !bFind )
									{
										for ( int k = 0; i < NTL_MAX_BAGSLOT_COUNT; ++k )
										{
											CNtlSobItem* pSobItem = reinterpret_cast<CNtlSobItem*>( GetNtlSobManager()->GetSobObject( pInventory->GetBagItem( k ) ) );
											if ( 0 == pSobItem ) continue;

											CNtlSobItemAttr* pSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pSobItem->GetSobAttr());
											if ( pSobItemAttr->GetTblIdx() == uSToCCondData.sHaveItem[k].uiItemTblIdx )
											{
												bFind = true;
												break;
											}

											int nChildCnt = pSobItem->GetChildNum();
											for ( int j = 0; j < nChildCnt; ++j )
											{
												CNtlSobItem* pChildSobItem = pSobItem->GetChildItem( j );
												if ( 0 == pChildSobItem ) continue;

												CNtlSobItemAttr* pChildSobItemAttr = reinterpret_cast<CNtlSobItemAttr*>(pChildSobItem->GetSobAttr());
												if ( pChildSobItemAttr->GetTblIdx() == uSToCCondData.sHaveItem[i].uiItemTblIdx )
												{
													bFind = true;
													break;
												}
											}

											if ( bFind ) break;
										}
									}

									bSatisfyCond &= bFind;
								}

								if ( !bSatisfyCond )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						case eSTOC_EVT_COND_DATA_TYPE_HAVE_QITEM:
							{
								bool bSatisfyCond = true;

								for ( int i = 0; i < uSTOC_EVT_COND_DATA::MAX_HAVE_QITEM; ++i )
								{
									if ( 0xffffffff == uSToCCondData.sHaveQItem[i].uiQItemTblIdx ) continue;

									// ����Ʈ ������ �κ��丮���� ����Ʈ ������ �˻�

									int nSum = 0;
									CNtlQuestInventory* pQuestInventory = GetNtlSLGlobal()->GetSobAvatar()->GetQuestInventory();
									for ( int j = 0; j < MAX_QUEST_INVENTORY_SLOT; ++j )
									{
										CNtlSobQuestItem* pSobQItem = pQuestInventory->GetQuestItemFromIdx( j );
										if ( pSobQItem )
										{
											CNtlSobQuestItemAttr* pSobQItemAttr = reinterpret_cast<CNtlSobQuestItemAttr*>(pSobQItem->GetSobAttr());
											if ( pSobQItemAttr->GetQuestItemTbl()->tblidx == uSToCCondData.sHaveQItem[i].uiQItemTblIdx )
											{
												nSum += pSobQItemAttr->GetStackNum();
											}
										}
									}

									if ( nSum < uSToCCondData.sHaveQItem[i].nQITemCnt )
									{
										bSatisfyCond &= false;
									}
								}

								if ( !bSatisfyCond )
								{
									tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
								}
							}
							break;
						}

						// 5. SToC Sub Condition �˻�
						// Delivery�� Sub condition�� ���� �˻��� �ʿ� ����.
					}
					else
					{
						tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
					}
				}
				else
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
			}
			else
			{
				tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
			}
		}
		break;

		case DBO_COND_TYPE_ID_CHECK_ATTACH_OBJ:
			{
				// Object trigger������ �����ϴ� condition
				CNtlTSLog::Log( "Not supported condition. Info[%d,%d,%d]. [%s]",
								pQParam->GetCtrl()->GetTrigger()->GetID(),
								((CNtlTSGroup*)pEntity->GetParent()->GetParent())->GetID(),
								((CNtlTSCont*)pEntity->GetParent())->GetID(),
								TS_CODE_TRACE() );
				tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
			}
			break;

		case DBO_COND_TYPE_ID_CHECK_PROG_QUEST:
			{
				CDboTSCheckProgQuest* pProgQuest = (CDboTSCheckProgQuest*) pEntity;

				if ( NULL == pQParam->GetAgency()->FindProgressTrigger( pProgQuest->GetQuestID() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
				}
			}
			break;

		case DBO_COND_TYPE_ID_CHECK_REPUTATION:
			{
				RwUInt32 uiRT = Logic_GetReputation( GetNtlSLGlobal()->GetSobAvatar() );
				CDboTSCheckReputation* pRT = (CDboTSCheckReputation*)pEntity;

				if ( pRT->GetMinReputation() > uiRT )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
				else if ( pRT->GetMaxReputation() < uiRT )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
				}
			}
			break;

		case DBO_COND_TYPE_ID_CHECK_BUDOKAI_STATE:
			{
				CDboTSCheckBudokaiState* pBudokai = (CDboTSCheckBudokaiState*)pEntity;
				if ( !pBudokai->IsConditionYes( GetNtlSLGlobal()->GetSobAvatar()->GetTenkaichiBudokai()->GetBudokaiMainState() ) )
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CANT_PROGRESS;
				}
			}
			break;

		case DBO_COND_TYPE_ID_CHECK_CUSTOMEVENT:
			{
				// Server-only condition
			}
			break;

			case DBO_COND_TYPE_ID_CHECK_AVATARDEAD:
			{
				// Server-only condition
			}
			break;

			case DBO_COND_TYPE_ID_CHECK_OUTRGN:
			{
				// Server-only condition
			}
			break;

			case DBO_COND_TYPE_ID_LEVEL_CHECK:
			{
				int nLvl = GetNtlSLGlobal()->GetAvatarInfo()->sCharPf.byLevel;
				CDboTSCheckLvl* pLvl = (CDboTSCheckLvl*)pEntity;

				if (nLvl < pLvl->GetMinLvl() || nLvl > pLvl->GetMaxLvl()) //check if pc lower than min lv or higher than max lv
				{
					tsResult |= NTL_TSRESULT_TYPE_COND_CAN_PROGRESS;
				}
			}
			break;

//////////////////////////////////////////////////////////////////////////
//
//	Action
//
//////////////////////////////////////////////////////////////////////////

	case DBO_ACT_TYPE_ID_ACT_ITEM:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			// Ŭ���̾�Ʈ������ �������� �ʴ� ���� ���� �׼�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_EXCEPT_TIMER_S:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActETimerS* pTimer = (CDboTSActETimerS*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pTimer->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pTimer->GetParent())->GetID();
			sKey.taID = pTimer->GetActionId();

			pQParam->GetCtrl()->TG_Avatar_TS_ExceptTimerStartNfy( sKey, pTimer );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_EXCEPT_TIMER_E:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActETimerE* pTimer = (CDboTSActETimerE*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pTimer->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pTimer->GetParent())->GetID();
			sKey.taID = pTimer->GetActionId();

			pQParam->GetCtrl()->TG_Avatar_TS_ExceptTimerEndNfy( sKey, pTimer );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_STOCEVT:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActSToCEvt* pEvt = (CDboTSActSToCEvt*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pEvt->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pEvt->GetParent())->GetID();
			sKey.taID = pEvt->GetActionId();

			pQParam->GetCtrl()->TU_ServerEvent( sKey, pEvt );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_QITEM:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			// Ŭ���̾�Ʈ������ �������� �ʴ� ���� ���� �׼�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_NPCCONV:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActNPCConv* pConv = (CDboTSActNPCConv*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pConv->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pConv->GetParent())->GetID();
			sKey.taID = pConv->GetActionId();

			pQParam->GetCtrl()->TU_ShowNPCConv( sKey, pConv );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_REGQINFO:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActRegQInfo* pRegQInfo = (CDboTSActRegQInfo*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pRegQInfo->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pRegQInfo->GetParent())->GetID();
			sKey.taID = pRegQInfo->GetActionId();

			pQParam->GetCtrl()->TU_RegisterQuestInfo( sKey, pRegQInfo );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_DIR:
		{
			// Ŭ���̾�Ʈ������ �ƹ��͵� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_OPCAM:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActOPCam* pCam = (CDboTSActOPCam*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pCam->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pCam->GetParent())->GetID();
			sKey.taID = pCam->GetActionId();

			pQParam->GetCtrl()->TU_CameraDirection( sKey, pCam );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TWAITTS:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActTWaitTS* pWaitTS = (CDboTSActTWaitTS*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pWaitTS->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pWaitTS->GetParent())->GetID();
			sKey.taID = pWaitTS->GetActionId();

			pQParam->GetCtrl()->TG_WaitTSNfy( sKey, pWaitTS );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_INSSM:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActInSSM* pSSM = (CDboTSActInSSM*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pSSM->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pSSM->GetParent())->GetID();
			sKey.taID = pSSM->GetActionId();

			pQParam->GetCtrl()->TG_InSSMNfy( sKey, pSSM );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TSSTATE:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActTSState* pTSState = (CDboTSActTSState*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pTSState->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pTSState->GetParent())->GetID();
			sKey.taID = pTSState->GetActionId();

			pQParam->GetCtrl()->TG_TSStateNfy( sKey, pTSState );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_PORTAL:
		{
			// Ŭ���̾�Ʈ���� ��Ż�� �������� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_OBJSTATE:
		{
			// Ŭ���̾�Ʈ���� ������Ʈ�� ���¸� �����ϴ� �ڵ�� �������� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_CONC_CHECK:
		{
			// Ŭ���̾�Ʈ���� ���� üũ�� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_OBJCONV:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActObjConv* pConv = (CDboTSActObjConv*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pConv->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pConv->GetParent())->GetID();
			sKey.taID = pConv->GetActionId();

			pQParam->GetCtrl()->TU_ShowObjConv( sKey, pConv );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_HINT:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActHint* pHint = (CDboTSActHint*)pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pHint->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pHint->GetParent())->GetID();
			sKey.taID = pHint->GetActionId();

			pQParam->GetCtrl()->TU_Hint( sKey, pHint );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_SEND_SVR_EVT:
	case DBO_ACT_TYPE_ID_ACT_TMQ_STAGE:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			// Send server event �� TMQ stage ����� 1�������� �����̸� �д�
			pQParam->GetCtrl()->StartTimeWait( 1000 );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_OPEN_WINDOW:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActOpenWindow* pAct = (CDboTSActOpenWindow*) pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pAct->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pAct->GetParent())->GetID();
			sKey.taID = pAct->GetActionId();

			pQParam->GetCtrl()->TU_Open_Window( sKey, pAct );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TMQ_TIMEBONUS:
		{
			// Ŭ���̾�Ʈ���� Ÿ�� ���ʽ��� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TELECAST:
		{
			// Ŭ���̾�Ʈ���� ��ۿ� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_DIRINDICATOR:
		{
			// Ŭ���̾�Ʈ���� ���� ���ÿ� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_OPERATEOBJECT:
		{
			// Ŭ���̾�Ʈ���� ������Ʈ ���ۿ� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_DROP:
		{
			// Ŭ���̾�Ʈ���� ����� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_RMV_COUPON:
		{
			// Ŭ���̾�Ʈ���� ����� ���� ������ ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_ESCORT:
		{
			// Ŭ���̾�Ʈ���� ������Ʈ �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TMQINFOTYPE:
		{
			// Ŭ���̾�Ʈ���� TMQ info type �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_WORLDPLAYSCRIPT:
		{
			// Ŭ���̾�Ʈ���� World play script �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_SWPROBSF:
		{
			// Ŭ���̾�Ʈ���� Switch probability success fail �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_PCCONV:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActPCConv* pAct = (CDboTSActPCConv*) pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pAct->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pAct->GetParent())->GetID();
			sKey.taID = pAct->GetActionId();

			pQParam->GetCtrl()->TU_PC_ConvNfy( sKey, pAct );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_CUSTOMEVT:
		{
			// Ŭ���̾�Ʈ���� custom event�� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TELMUDOSA:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActTelMudosa* pAct = (CDboTSActTelMudosa*) pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pAct->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pAct->GetParent())->GetID();
			sKey.taID = pAct->GetActionId();

			pQParam->GetCtrl()->TU_TelMudosa( sKey, pAct );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TELMINORMATCH:
		{
			// Ŭ���̾�Ʈ���� teleport minor match�� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_PIDGN:
		{
			// Ŭ���̾�Ʈ���� Party instance dungeon�� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TLQ:
		{
			// Ŭ���̾�Ʈ���� Time leap quest dungeon�� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_DO_SKILL:
		{
			// Ŭ���̾�Ʈ���� Do skill �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_TOBJ_FRIENDLY:
		{
			// Ŭ���̾�Ʈ���� Trigger object friendly �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_BROAD_MSG:
		{
			// Ŭ���̾�Ʈ���� Broad message �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_MINI_NARRATION:
		{
			// Ŭ���̾�Ʈ���� Mini narration �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_REG_C_TIMING:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActRegCTiming* pAct = (CDboTSActRegCTiming*) pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pAct->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pAct->GetParent())->GetID();
			sKey.taID = pAct->GetActionId();

			pQParam->GetCtrl()->TU_RegCTiming( sKey, pAct );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_EXC_C_GROUP:
		{
			// ����Ʈ ��ũ �˻���� ��� Action�� �������� �ʴ´�
			if ( pQParam->IsForCheckQuestMark() ) break;

			CDboTSActExcCGroup* pAct = (CDboTSActExcCGroup*) pEntity;

			sTS_KEY sKey; sKey.Init();
			sKey.tID = pQParam->GetCtrl()->GetTrigger()->GetID();
			sKey.tgID = ((CNtlTSGroup*)pAct->GetParent()->GetParent())->GetID();
			sKey.tcID = ((CNtlTSCont*)pAct->GetParent())->GetID();
			sKey.taID = pAct->GetActionId();

			pQParam->GetCtrl()->TU_ExcCGroup( sKey, pAct );
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_SKIP_CONT:
		{
			// Ŭ���̾�Ʈ���� Skip cont �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

	case DBO_ACT_TYPE_ID_ACT_OBJ_WPS:
		{
			// Ŭ���̾�Ʈ���� Obj WPS �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

		case DBO_ACT_TYPE_ID_ACT_DOJO:
		{
			// Ŭ���̾�Ʈ���� Dojo �� �����ؼ��� ���� ���� �ʴ´�
		}
		break;

		case DBO_ACT_TYPE_ID_ACT_OUT_MSG:
		{
			// to do by daneos
		}
		break;

		case DBO_ACT_TYPE_ID_ACT_WPSFD:
		{
			// to do by daneos
		}
		break;

		case DBO_ACT_TYPE_ID_ACT_MAIL:
		{
			// to do by daneos
		}
		break;

		case DBO_ACT_TYPE_ID_ACT_AVATARDEAD:
		{
			// to do by daneos
		}
		break;

		case DBO_ACT_TYPE_ID_ACT_SKYDGN:
		{
			// to do by daneos
		}
		break;
	}

	return tsResult;
}
