#pragma once


/**
 * \ingroup NtlPresentation
 * \brief UVAnim�� ó���ϴ� Ŭ����
 * \date 2006-07-11
 * \author agebreak
 */
class CNtlPLUVAnim
{
public:
    CNtlPLUVAnim(void);
    virtual ~CNtlPLUVAnim(void);

    RwBool Create(const char* szUVFileName);
    RwBool SetClump(RpClump* pClump);
    RwBool Create(const char* szUVFileName, RpClump* pClump);       ///< UVAnim�� �����Ѵ�.
    void   Destory();                                               ///< �Ҵ�� �޸𸮸� �����Ѵ�.
    void   Update(RwReal fElapsedTime);                             ///< UVAim�� Update�Ѵ�.
    void   SetUVAnimSpeed(RwReal fSpeed) {m_fUVAnimTime = fSpeed;}  ///< UVAnim�� �ӵ��� �����Ѵ�

protected:
    RtDict* UVAnimDictLoad(const RwChar* strFullName);              ///< *.uva ������ �ε��Ѵ�.

protected:
    RtDict*							m_pUvAnimDict;                 ///< UVAnim dict ��ü
    RwSList*						m_pAnimationMaterialList;      ///< UVAnim�� ������ Material list
    RwReal                          m_fUVAnimTime;                 ///< UVAnim Speed
    
    
};
