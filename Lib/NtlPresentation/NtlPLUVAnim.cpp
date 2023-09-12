#include "precomp_ntlpresentation.h"
#include "NtlEffectAPI.h"
#include "NtlPLUVAnim.h"
#include "NtlTimer.h"
#include "NtlPLResourcePack.h"
#include "NtlPLApi.h"

CNtlPLUVAnim::CNtlPLUVAnim(void)
: m_fUVAnimTime(1.0f)
{
    m_pUvAnimDict = NULL;
    m_pAnimationMaterialList = NULL;
}

CNtlPLUVAnim::~CNtlPLUVAnim(void)
{
    Destory();
}

void CNtlPLUVAnim::Destory() 
{
    if (m_pAnimationMaterialList != NULL)
    {
        rwSListDestroy(m_pAnimationMaterialList);
        m_pAnimationMaterialList = NULL;
    }

    if (m_pUvAnimDict != NULL)
    {
        RtDictDestroy(m_pUvAnimDict);
        m_pUvAnimDict = NULL;
    }

    m_fUVAnimTime = 1.0f;
}


/**
 * uva���Ϸ� ���� UVAnim�� �����Ͽ� Clump�� �����Ѵ�.
 * \param szUVFileName ������ uvAnim ���ϰ�� (*.uva)
 * \param pClump UVAnim�� ������ Clump ��ü
 * return ���� ����
 */
RwBool CNtlPLUVAnim::Create( const char* szUVFileName, RpClump* pClump ) 
{
    if(!szUVFileName || !pClump)
        return FALSE;

    if(m_pUvAnimDict)
    {
        Destory();
    }

    m_pUvAnimDict = UVAnimDictLoad(szUVFileName);
    if(!m_pUvAnimDict)
        return FALSE;

    RtDictSchemaSetCurrentDict(RpUVAnimGetDictSchema(), m_pUvAnimDict);    
    
    m_pAnimationMaterialList = rwSListCreate(sizeof(RpMaterial*), rwID_NAOBJECT);
    API_AddAnimatedMaterialsList(m_pAnimationMaterialList, pClump);

    return TRUE;
}

RwBool CNtlPLUVAnim::Create( const char* szUVFileName ) 
{
    if(m_pUvAnimDict)
    {
        Destory();
    }

    m_pUvAnimDict = UVAnimDictLoad(szUVFileName);
    if(!m_pUvAnimDict)
        return FALSE;


    // NOTE: ȭ�鿡 ���δٸ� UVAnim�� ����� Object�� �ΰ��̻�������. ������ ���� ������?
    // ���Ŀ� ����� ����, ������ ������ �����Ѵ�.
    // DIct��ü�� Entry(RpUVAnim*)�� �߰��ϴ� ���·� ������ �ʿ������� �𸣰ڴ�.
    RtDictSchemaSetCurrentDict(RpUVAnimGetDictSchema(), m_pUvAnimDict);    

    return TRUE;
}

RwBool CNtlPLUVAnim::SetClump( RpClump* pClump ) 
{
    m_pAnimationMaterialList = rwSListCreate(sizeof(RpMaterial*), rwID_NAOBJECT);
    API_AddAnimatedMaterialsList(m_pAnimationMaterialList, pClump);

    return TRUE;
}

void CNtlPLUVAnim::Update( RwReal fElapsedTime ) 
{
    if(!m_pAnimationMaterialList)
        return;

    //API_MaterialsInterpolatorsAddAnimTime(m_pAnimationMaterialList, fElapsedTime * m_fUVAnimTime);    

    // �������� Clump�� Material�� ���������� �����̵Ǳ� ������, AddTime�� �ƴ� SetCurrentTime�� �����Ѵ�.
    API_MaterialsInterpolatorsSetCurrentTime(m_pAnimationMaterialList, CNtlTimer::GetAppTime() * m_fUVAnimTime);

    API_MaterialsAnimApply(m_pAnimationMaterialList);
}

/**
 * *.uva ������ �ε��Ѵ�.
 * \param strFullName uva���ϰ��
 * return uva������ �ε��� RtDict ��ü
 */
RtDict* CNtlPLUVAnim::UVAnimDictLoad( const RwChar* strFullName ) 
{
	return API_PL_LoadUVAnimDict(strFullName);
}


