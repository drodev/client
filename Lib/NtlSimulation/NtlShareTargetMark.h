#pragma once

class CNtlSob;
class CNtlPLEntity;

/**
 * \ingroup NtlSimulation
 * \brief ���� Ÿ�� ��ũ�� �����ϴ� Ŭ����
 *
 * \date 2009-08-13
 * \author agebreak
 */
class CNtlShareTargetMark
{
public:
    // ���� Ÿ�� Ÿ��
    enum EShareTargetType
    {
        SHARE_TARGET_NORMAL,        
        SHARE_TARGET_TARGET,        
        SHARE_TARGET_ATTACK,
        SHARE_TARGET_NONE,
    };

    CNtlShareTargetMark(CNtlSob* pSobObject);
    virtual ~CNtlShareTargetMark();

    void    CreateShareTargetMark(RwUInt8 bySlot, RwInt32 type);               ///< ����Ÿ�� ��ũ�� �����Ѵ�.
    void    DeleteShareTargetMark();                                            ///< ����Ÿ�� ��ũ�� �����Ѵ�.
    RwBool  IsShareTargeting();                                                 ///< ����Ÿ���� �����Ǿ��ִ����� ��ȯ�Ѵ�.
    RwUInt8 GetSlot() {return m_bySlot;}                                        ///< ���� ������ ������ ��ȯ�Ѵ�.    

protected:

protected:
    CNtlSob*            m_pSobObj;                  ///< ����Ÿ���� ���� ���� ��ƼƼ
    CNtlPLEntity*       m_pShareTargetMark;         ///< ����Ÿ�� ����Ʈ
    RwUInt8             m_bySlot;                   ///< ����Ÿ�� �ѹ�(����)
    EShareTargetType    m_type;                     ///< ����Ÿ�� Ÿ��  
    
};