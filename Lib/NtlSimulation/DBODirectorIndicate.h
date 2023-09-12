/*****************************************************************************
*
* File			: DBODirectorIndicate
* Author		: agebreak
* Copyright	: (��)NTL
* Date			: 2007. 11. 20	
* Abstract		: 
*****************************************************************************
* Desc         : TS/TMQ�� ���Ǵ� ���� ���� �ý��� ���� Ŭ����
*
*****************************************************************************/
#pragma once

#include "ceventhandler.h"
#include "NtlSLGlobal.h"
#include "NtlPLFadeController.h"

class CNtlPLCharacter;
class CNtlInstanceEffect;

/// TS/TMQ�� ���Ǵ� ���� ���� �ý��� ���� Ŭ����
class CDBODirectorIndicate
{
public:
    CDBODirectorIndicate(CNtlPLCharacter* pPLCharacter);
    ~CDBODirectorIndicate(void);

    RwBool Create();
    VOID   Destory();
    RwBool Update(RwReal fElapsedTime);
    VOID   HandleEvents(RWS::CMsg &pMsg);
    VOID   SetCharacter(CNtlPLCharacter* pPLCharacter) {m_pCharacter = pPLCharacter;}

protected:
    RwBool      CreateDirector();        ///< ���� ���� ������Ʈ�� �����Ѵ�.
    RwBool      CreateTargetEffect();    ///< Ÿ���� ����Ʈ�� �����Ѵ�.       
    RwBool      CalcDistance();          ///< �Ÿ��� ����Ѵ�.
    VOID        UpdateDirection();       ///< ������Ʈ�� ������ ������Ʈ�Ѵ�.
    VOID        SetVisibleEffect(RwBool bVisible);  ///< ����Ʈ���� ǥ�� ������ �����Ѵ�.                
    VOID        SetTargetEffectPos(RwV3d vPos);    ///< Ÿ�� ����Ʈ�� Ÿ�� ��ġ�� ��ġ��Ų��.

protected:
    CNtlPLCharacter*                    m_pCharacter;             ///< �÷��̾� ĳ����    
    CNtlInstanceEffect*                 m_pDirectorEffect;        ///< ���� ���ø� ǥ���ϴ� ����Ʈ
    CNtlInstanceEffect*                 m_pTargetEffect;          ///< Ÿ���� ��Ÿ���� ����Ʈ            
    RwV3d                               m_vTargetPos;             ///< Ÿ���� ��ġ
    RwBool                              m_bUpdate;                ///< ������Ʈ ���� �÷���
};
