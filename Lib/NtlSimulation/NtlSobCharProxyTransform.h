#pragma once

#include "NtlSLEvent.h"

class RWS::CEventHandler;
class CNtlSobActor;
class CNtlPLCharacter;
class CNtlPLItem;
class CNtlInstanceEffect;
class CNtlSobProxySystemEffect;
struct SEquipItem;



/**
* \ingroup NtlSimulation
* \brief ���Ű��� ������� ó���ϴ� Ŭ����
*
* \date 2008-10-07
* \author agebreak
*/
class CNtlSobCharProxyTransform : public RWS::CEventHandler
{
public:
    CNtlSobCharProxyTransform(CNtlSobActor* pActor, CNtlPLCharacter* pPLCharacter);
    virtual ~CNtlSobCharProxyTransform(void);

    void	        Update(RwReal fElapsed);
    void	        HandleEvents(RWS::CMsg &pMsg);
    void            Destory();

    void            SetActor(CNtlSobActor* pActor, CNtlPLCharacter* pPLCharacter);          ///< ĳ���͸� �����Ѵ�. (�����Ͱ� ����� ���)        
    void            PostChangeAdult();                                                      ///< �/���̷� ������ ȣ��Ǵ� �Լ�
    RwBool          IsTransform()   {return m_bIsTransform;}        ///< �����ߴ��� ���θ� ��ȯ�Ѵ�.    

    // ���� ����/�������� �̺�Ʈ �Լ�
    void            AddWorld();
    void            RemoveWorld();

protected:
    // Event
    void            EventSobTransform(SNtlEventTransform* pData);     ///< ���� �̺�Ʈ ó��
    void            EventSobSkillAction(RWS::CMsg& pMsg);             ///< ��ų ��� �̺�Ʈ�� ó���Ѵ�.
    void            EventSobChangeAdult(RWS::CMsg& pMsg);             ///< �������� ������ ó���Ѵ�.

    // Transform
    void            OnTransform_SuperSaiyan(RwBool bTransform);     ///< �ʻ��̾��� ���� ó��
    void            OnTransform_KaiOuKen(RwBool bTransform, BYTE byLevel);        ///< ��ձ� ���� ó��
    void            OnTransform_BigNamek(RwBool bTransform);        ///< �Ŵ� ����ũ ���� ó��
    void            OnTransform_PureMajin(RwBool bTransform);       ///< ���� ���� ���� ó��
    void            OnTransform_Mob(RwUInt32 tblIdx);               ///< �� ���� ó��
    void            OnTransform_Candy(RwBool bTransform);           ///< ĵ�� ��ų ���� ó��
    void            DetachEffect();                                 ///< ���Ž��� ���� ����Ʈ ����

	void            OnTransform_CinematicScale(float fScale, float fTime);

    // Super Saiyan
    void            AttachEffectSuperSaiyan(CNtlPLCharacter* pPLCharacter);                      ///< �ʻ��̾��� ����Ʈ ����
    CNtlPLItem*     GetTransformItem();                             ///< �ʻ��̾��� ���� �������� ��ȯ�Ѵ�.

    // ��ձ�
    void            AttachEffectKaiouKen(CNtlPLCharacter* pPLCharacter, BYTE byLevel);    ///< ��ձ� ����Ʈ ����    

    // �Ŵ� ����
    void            DetachWeapon();                         ///< ���� �����ϰ� �ִ� ���⸦ �����Ѵ�.
    void            AttachWeapon();                         ///< ���� �����ϰ� �ִ� ���⸦ �����Ѵ�.
    void            ChangeWeapon(RWS::CMsg& pMsg);          ///< ���� ���¿��� ���⸦ �����Ͽ�����

    // ���� ����
    CNtlPLCharacter* CreatePureMajinModel();                ///< ���� ���� ���� �����ϰ� ��ȯ�Ѵ�.

    // ĵ�� ����
    CNtlPLCharacter* CreateCandyModel();                    ///< ĵ�� ���� �����ϰ� ��ȯ�Ѵ�.

protected:
    CNtlSobActor*       m_pActor;                           ///< Actor ��ü
    CNtlPLCharacter*    m_pPLCharacter;                     ///< Actor�� PLEntity
    SNtlEventTransform  m_transFormData;                    ///< ���� ���� ����ü
    CNtlPLCharacter*    m_pPLCharacterUI;                   ///< UI�� ǥ���Ǵ� ĳ���� (�ƹ�Ÿ�� ���)
	CNtlPLCharacter*    m_pPLCharacterUI_Dogi;              ///< Dogi UI�� ǥ���Ǵ� ĳ���� (�ƹ�Ÿ�� ���)
    RwBool              m_bIsTransform;                     ///< �����ߴ��� ���� �÷���    
    RwUInt32            m_uiTransformId;                    ///< �������� �����ߴ����� ID
    RwBool              m_bReadyTransform;                  ///< ���� ��ų�� ����ߴ�
    RwBool              m_bScheduleLoadingCheck;            ///< ������ �ε� üũ �÷���
    BYTE                m_byTransformLevel;                 ///< ���� ����    
    std::vector<CNtlInstanceEffect*> m_vecEffect;           ///< ���Ž��� ����Ʈ    

    // �ʻ��̾���
    CNtlPLItem*         m_pItemTransform;                   ///< �ʻ��̾��� ���Ž��� ���
	CNtlPLItem*         m_pItemTransformUI;                 ///< UI�� ������
    CNtlPLItem*         m_pItemTransformUI_Dogi;            ///< Dogi UI�� ������
    RwTexture*          m_pFaceTransform;                   ///< �ʻ��̾��� ���� �� �ؽ���
    CNtlSobProxySystemEffect* m_pSystemEffectColor[2];      ///< �ʻ��̾��� ���Ž� Effect Color ��Ʈ�ѷ�

    // ��ձ�
    CNtlSobProxySystemEffect* m_pKaiOuKenColor[2];          ///< ��ձ� ���Ž� �÷� ��Ʈ�ѷ�

    // �Ŵ� ����
    SEquipItem*         m_pItemOrgWeapon;                   ///< ����ũ ���Žÿ� ���� ���� �ִ� ���� 
    SEquipItem*         m_pItemOrgSubWeapon;                ///< ����ũ ���Žÿ� ���� ���� �ִ� ���� ����
    RwReal              m_fOrgAttackRange;                  ///< �������� ���� ���� ����

    // ���� ����    
    CNtlPLCharacter*    m_pMajinOrgModel;                   ///< ���� ���� ��
    CNtlPLCharacter*    m_pMajinOrgModelUI;                 ///< UI�� ���� ���� ��
	CNtlPLCharacter*    m_pMajinOrgModelUI_Dogi;            ///< Dogi UI�� ���� ���� ��
    CNtlPLCharacter*    m_pMajinPureModel;                  ///< ������ ���� ���� ��    
    CNtlPLCharacter*    m_pMajinPureModelUI;                ///< UI�� ���� ���� ��    
	CNtlPLCharacter*    m_pMajinPureModelUI_Dogi;           ///< Dogi UI�� ���� ���� ��    

    // ĵ�� ����
    CNtlPLCharacter*    m_pCandyOrgModel;                   ///< ĵ��� �����ϱ��� ���� ��
    CNtlPLCharacter*    m_pCandyOrgModelUI;                 ///< UI�� ���� ��
	CNtlPLCharacter*    m_pCandyOrgModelUI_Dogi;            ///< Dogi UI�� ���� ��
    CNtlPLCharacter*    m_pCandyModel;                      ///< ĵ�� ���� ��
	CNtlPLCharacter*    m_pCandyModelUI;                    ///< UI�� ĵ�� ��
	CNtlPLCharacter*    m_pCandyModelUI_Dogi;               ///< Dogi UI�� ĵ�� ��
};
