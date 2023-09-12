/*****************************************************************************
*
* File			: NtlPLAccelController
* Author		: agebreak
* Copyright		: (��)NTL
* Date			: 2007. 12. 29	
* Abstract		: ���ӵ� ���� ��Ʈ�ѷ�
*****************************************************************************
* Desc         : UI�� �����̵��� ���Ǵ� ���ӵ� ���� ��Ʈ�ѷ�
*
*****************************************************************************/

#pragma once

/// ���ӵ� ��� ��Ʈ�ѷ�
class CNtlPLAccelController
{
public:
    CNtlPLAccelController(void);
    ~CNtlPLAccelController(void);
	
    void    SetAccel(RwReal fStartVal, RwReal fEndVal, RwReal fStartVelocity, RwReal fAccel);       /// ���� �����Ѵ�.
    RwBool  Update(RwReal fElapsed);                           ///< ������Ʈ
	void	Stop();
    RwReal  GetCurrentValue() {return m_fCurrentVal;}          ///< ���簪
    RwReal  GetCurrentVelocity() {return m_fCurrVel;}          ///< ���� �ӵ�
	RwReal	GetCurrentProgress();								///< 0.0(����) ~ 1.0(��) ������ ���� ����

protected:
    RwReal  m_fStartVal;                      ///< ���۰�
    RwReal  m_fEndVal;                        ///< ����
    RwReal  m_fCurrentVal;                    ///< ���簪
    RwReal  m_fStartVelocity;                 ///< ���� �ӵ�
    RwReal  m_fAccel;                         ///< ���ӵ�
    RwReal  m_fCurrVel;                       ///< ���� �ӵ�
	RwReal	m_fCurrProgress;				  ///< ���� ����ġ ( 0.0f ~ 1.0f )
    RwBool  m_bUpdate;                        ///< ������Ʈ ���� �÷���
};
