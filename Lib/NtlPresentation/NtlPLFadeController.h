/*****************************************************************************
*
* File			: NtlPLFadeController.h
* Author		: agebreak
* Copyright		: (��)NTL
* Date			: 2007. 11. 21	
* Abstract		: Fade In/Out�� ���� ���� ��Ʈ�ѷ�
*****************************************************************************
* Desc         : Entity���� AlphaWeight��� ��Ʈ�ѷ��� ������, Entity�ܿ���
*                ������ �� ���� ������ ���� �����.
*
*****************************************************************************/

#pragma once

/// Fade �� ���� ��Ʈ�ѷ�
class CNtlPLFadeController
{
public:
    CNtlPLFadeController(void);
    virtual ~CNtlPLFadeController(void);

    void Set(RwReal fOrgValue, RwReal fDestValue, RwReal fFadeTime);
    void Update(RwReal fElapsedTime);
    
    RwReal GetValue() {return m_fValue;}    ///< ������ Fade ���� ��ȯ�Ѵ�.
    RwBool IsEnd() {return m_bEnd;}         ///< Fade�� ���������� ��ȯ�Ѵ�.

protected:
    RwReal m_fOrgValue;                     ///< ������
    RwReal m_fDestValue;                    ///< ����
    RwReal m_fValue;                        ///< ���簪
    RwReal m_fFadeTime;                     ///< Fade Time
    RwReal m_fTime;                         ///< ���� Time
    RwBool m_bEnd;                          ///< Fade�� �������� ����
};
