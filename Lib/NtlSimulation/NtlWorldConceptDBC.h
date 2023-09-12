#pragma once

#include "NtlWorldConceptController.h"
#include "NtlSoundDefines.h"
#include "NtlDragonBall.h"

class CNtlPLCharacter;
class CNtlSob;
class CNtlSobItem;

typedef std::list<CNtlSobItem*>	ListSobItem;

/**
 * \ingroup NtlSimulation
 * \brief ��� ��ȯ�� �巡�ﺼ ���� ���¸� �����ϴ� ��Ʈ�ѷ�
 * \date 2007-06-14
 * \author agebreak
 */
class CNtlWorldConceptDBC : public CNtlWorldConceptController
{
public:
	CNtlWorldConceptDBC(void);
	~CNtlWorldConceptDBC(void);

	virtual void		Update(RwReal fElapsedTime);				///< �� ������ �´� ������� Updateó�� �Լ�
	virtual RwBool		IsEnableAction(EAvatarAction eAction);		///< Avatar�� Action�� ���� ó�� ���������� �� ������ ���� �Ǻ��Ѵ�.
	virtual void		ChangeState(RwInt32 iState);				///< State ���¸� �����Ѵ�.	

    // DragonBall List	
	void				AddDragonBall(CNtlSobItem* pItem);			///< ����Ʈ�� �巡�ﺼ �������� �߰��Ѵ�.
	void				RemoveDragonBall(CNtlSobItem* pItem);		///< ����Ʈ���� �巡�ﺼ �������� �����Ѵ�.
	ListSobItem*		GetDBList() {return &m_listDragonBall;}

    // Property
    void				SetDBKind(eDRAGON_BALL_TYPE eDBKind) {m_eDragonBallKind = eDBKind;}	///< ���� �������� �巡�ﺼ�� ������ �����Ѵ�.
    eDRAGON_BALL_TYPE	GetDBKind() {return m_eDragonBallKind;}		                        ///< ���� �������� �巡�ﺼ�� ������ ��ȯ�Ѵ�.			

    void				SetAltarSerialID(RwUInt32 nSerialID) {m_uiAltarID = nSerialID;}
    RwUInt32			GetAltarSerialID() {return m_uiAltarID;}

    void				ResetRemainTime();							///< ���� ���ѽð��� �����Ѵ�.
    RwUInt32			GetReaminTime();	                        ///< ���� ���ѽð��� �����´�.

    void                SetMyDragon(RwBool bMyDragon) {m_bMyDragon = bMyDragon;}    ///< �ڽ��� ��ȯ�� ��������� �����Ѵ�.
    RwBool              IsMyDragon() {return m_bMyDragon;}                          ///< �ڽſ� ��ȯ�� ������� ���θ� ��ȯ�Ѵ�.

protected:	

protected:
	RwUInt32				m_uiAltarID;							///< ������ Serial ID
	eDRAGON_BALL_TYPE		m_eDragonBallKind;						///< ���� �������� �巡�ﺼ ������ ����
	RwUInt32				m_uiRemainTime;							///< ���� ���ѽð�
	ListSobItem				m_listDragonBall;						///< �巡�ﺼ �����۵�
    RwBool                  m_bMyDragon;                            ///< �ڱⰡ ��ȯ�� ��������� Ȯ���ϱ� ���� �÷���
    RwBool                  m_bUpdateRemainTime;                    ///< ���� �ð� ������Ʈ ���� �÷���
    SOUND_HANDLE            m_hBGMHandle;                           ///< ��� ������ ������ �ڵ�
};
