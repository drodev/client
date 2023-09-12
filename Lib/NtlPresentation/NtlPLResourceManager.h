/*****************************************************************************
 *
 * File			: NtlPLResourceManager.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 21	
 * Abstract		: Presentation layer resource manager class
 *****************************************************************************
 * Desc         : 
 * Adjust		: HuunSuk, Jang(2005. 7 29)
 *			        - renderware texture reseouce �߰�. 
 *				    - resorce�� dictory type �߰�(texture�� group���� �����ϱ� ���� interface) 
 *
 *****************************************************************************/

#ifndef __NTL_PLRESOURCE_MANAGER_H__
#define __NTL_PLRESOURCE_MANAGER_H__

#include <rwcore.h>
#include <rpworld.h>
#include <string>
#include <map>
#include "NtlPLResource.h"

//RwBool TextureLoadLevelPath(const RwChar* pInPath, RwChar** ppOutPath, RwInt32* pOutPathSize);

class CNtlPLEntity;
class CNtlResourceScheduleManager;

/**
* \ingroup NtlPresentation
* RenderWare resource manager class�̴�.
* world, clump, atomic, texture�� �����ǰ� ������, uva file�� ���� ���� ������ �����Ѵ�.
* Note : module�� ���� �������� �ʾ����Ƿ� ����ڴ� �����ؾ� �Ѵ�.
*        ���� resource container�� clump �� atomic�� ���� ������ ������ �����ؾ� �Ѵ�.
* 
*/
class CNtlPLResourceManager
{
public:

	enum EResDictType	 
	{
		RES_TEX_DEFAULT_DICT,
		RES_TEX_TERRAIN_DICT,
		RES_TEX_OBJECT_DICT,
		RES_TEX_CHARACTER_DICT,
		RES_TEX_EFFECT_DICT,
		RES_TEX_UI_DICT,
	};

	// TEST
// public:
// 	void SetTextureLoadLevel(RwUInt32 eResDictType, RwUInt32 uiLevel);
// 
// 	struct STextureLoadLevelDirectory
// 	{
// 		std::string strDirectory;
// 		RwUInt32	uiLevelCur;
// 		RwUInt32	uiLevelMax;
// 	};
// 
// 	
// 	typedef std::map<RwUInt32, STextureLoadLevelDirectory>	TextureLoadDirectoryMap;
// 	TextureLoadDirectoryMap m_mapTextureLoadDirectroy;	
// 
// 	std::string m_strImagePath;
// 	RwInt32		m_iImagePathSize;
	//TEST : END

private:
	typedef std::map<std::string, CNtlPLResource*> ResourceMap;
	typedef std::multimap<std::string, CNtlPLResource*> ResourceMultiMap;

	ResourceMap m_mapResTbl; /**< CNtlPlResource�� container*/

	ResourceMap m_mapWorld;
	ResourceMap m_mapClump;
	ResourceMap m_mapAtomic;
	ResourceMultiMap m_mmapCloneClump; 
	ResourceMultiMap m_mmapCloneAtomic;
	ResourceMap m_mapAnim;
	
	RwBool	m_bLoadScheduling;
	RwBool	m_bDeleteScheduling;

	CNtlResourceScheduleManager *m_pScheduleManager;

private:
	
	/**
    *  RenderWare data�� �д� �Լ�.
    *
	*  \param pStrName file name
	*  \param pResourcePath resource path
	*  \param uiType RednerWare resource type
	*  \param bClone container�� file name�� ���� resource�� �����Ѵٸ�? clone���� ������ ���ΰ�?
	*  \return resource class pointer
	*/
	CNtlPLResource* LoadDefault(const char *pStrName, const char * pResourcePath, unsigned int uiType);

	/**
    *  CNtlPLResource ��ü�� �����ϴ� �Լ�.
    *
    *  \param pName resource name�� CNtlPLResource�� ��´�.
	*  \param uiType renderware data�� type.
	*  \param bClone renderware data�� clone flag.
	*  \param pData renderware data�� pointer.
	*  \return resource class pointer
    */
	CNtlPLResource* CreateResource(const char *pName, unsigned int uiType, bool bClone,	void *pData);

	/**
    *  CNtlPLResource ��ü�� container�� ����ϴ� �Լ�.
    *
    *  \param pResource container ����� resource pointer
	*  \see UnRegisterResource
    */
	void RegisterResource(const CNtlPLResource *pResource);

	/**
    *  CNtlPLResource ��ü�� container���� �����ϴ� �Լ�.
    *
    *  \param pResource container ������ resource pointer
	*  \see RegisterResource
    */
	void UnRegisterResource(const CNtlPLResource *pResource);

	/**
    *  renderware data type�� �ش��ϴ� data�� �����ϴ� �Լ�.
    *
    *  \param pSteam stream ��ü pointer.
	*  \param iType renderware data type.
    */
	void* CreateRwData(RwStream *pSteam, unsigned int iType);

	/**
    *  renderware data�� �ش��ϴ� clone data�� �����Ѵ�.
	*  type�� ���Ͽ� ������ renderware clone �Լ��� �����Ѵ�.
    *
    *  \param iType renderware data type.
	*  \param pData clone�� renderware data.
	*  \return renderware data pointer
	*  \see DestroyRwData
    */
	void* CreateCloneRwData(unsigned int iType, void *pData); 

	/**
    *  renderware data�� �ش��ϴ� type�� �����ϰ� �����Ѵ�.
    *
    *  \param iType renderware data type.
	*  \param pData ������ renderware data.
    */
	void  DestroyRwData(unsigned int iType, void *pData);

	/**
    *  renderware world�� �����ϴ� �Լ�.
    *
	*  \param pStream world stream data
	*  \return RenderWare world pointer
	*  \see AtomicStreamRead
	*  \see ClumpStreamRead
    */
	RpWorld* WorldStreamRead (RwStream *pStream);
	
	/**
    *  renderware clump�� �����ϴ� �Լ�.
    *
	*  \param pStream clump stream data
	*  \return RenderWare clump pointer
	*  \see WorldStreamRead
	*  \see AtomicStreamRead
    */
	RpClump* ClumpStreamRead (RwStream *pStream);

	/**
    *  renderware atomic�� �����ϴ� �Լ�.
    *
	*  \param pStream atomic stream data
	*  \return RenderWare atomic pointer
	*  \see WorldStreamRead
	*  \see ClumpStreamRead
    */
	RpAtomic* AtomicStreamRead (RwStream *pStream);

	/**
    *  container���� name���� CNtlPLResource�� ã�´�.
    *
	*  \param pName name string
	*  \param uiType the resource type
	*  \param uiType the resource dictory type
	*  \return pName�� �ش��ϴ� resource class pointer
    */
	CNtlPLResource* Find(const char *pName, unsigned int uiType, EResDictType eDictType = RES_TEX_DEFAULT_DICT);

    /**
    *  application�� ���� �Ǿ��� �� �������� ���� resource�� debugging�� ���� �Լ�.
	*  debugging ������ file or output window�� display �� �� �ֵ��� �Ѵ�.
    *
	*/
	void DebugResource(void);

public:

	CNtlPLResourceManager();

	/**
    *  singleton CNtlPLResourceManager interface �Լ�.
    *
	*/
	static CNtlPLResourceManager* GetInstance(void);

	/**
    * Initial �Լ�.
	*  \return resource manager�� �ʱ�ȭ�� ���������� true, �����ϸ� false
    *
	*/
	bool Crate(void);

	/**
    *  Terminate �Լ�.
    *
	*/
	void Destroy(void);

	/**
    *  Update �Լ�.
    *
	*/
	void Update(RwReal fElapsed);

	/**
    *  RenderWare world data�� �д� �Լ�.
    *
	*  \param pStrName file name
	*  \param pResourcePath resource path
	*  \return Pointer resource class
	*  \see LoadClump	
	*  \see LoadAtomic
	*  \see LoadTexture
	*  \see UnLoad
	*/
	CNtlPLResource* LoadWorld(const char *pStrName, const char * pResourcePath);

	/**
    *  RenderWare clump data�� �д� �Լ�.
    *
	*  \param pStrName file name
	*  \param pResourcePath resource path
	*  \param bClone clump�� clone���� ������ �������� �����ϴ� ����.
	*  \return Pointer resource class
	*  \see LoadWorld
	*  \see LoadAtomic
	*  \see LoadTexture
	*  \see UnLoad
	*/
	CNtlPLResource* LoadClump(const char *pStrName, const char * pResourcePath);


	/**
    *  RenderWare clump data�� �д� �Լ�. ������ �ð����� scheduling �ϸ鼭 loading �Ѵ�(thread loading ��ü��)
    *
	*  \param pStrName file name
	*  \param pResourcePath resource path
	*  \param bClone clump�� clone���� ������ �������� �����ϴ� ����.
	*  \return Pointer resource class
	*  \see LoadWorld
	*  \see LoadAtomic
	*  \see LoadTexture
	*  \see UnLoad
	*/
	void LoadSchedulingClump(const char *pStrName, const char * pResourcePath, CNtlPLEntity *pEntity);

	/**
    *  RenderWare atomic data�� �д� �Լ�.
    *
	*  \param pStrName file name
	*  \param pResourcePath resource path
	*  \param bClone atomic�� clone���� ������ �������� �����ϴ� ����.
	*  \return Pointer resource class
	*  \see LoadWorld
	*  \see LoadClump
	*  \see LoadTexture
	*  \see UnLoad
	*/
	CNtlPLResource* LoadAtomic(const char *pStrName, const char * pResourcePath);

	
	/**
    *  RenderWare animation data�� �д� �Լ�.
    *
	*  \param pStrName file name
	*  \return Pointer resource class
	*  \see LoadWorld
	*  \see LoadClump
	*  \see LoadTexture
	*  \see LoadAtomic
	*  \see UnLoad
	*/
	CNtlPLResource* LoadAnimation(const char *pStrName);

	/**
    *  RenderWare texture data�� �д� �Լ�.
    *
	*  \param pStrName file name
	*  \param pResourcePath resource path
	*  \param eFilterMode texture�� filtering mode. renderware RwTextureFilterMode�� ����.
	*  \param EResDictType texture�� group���� ������ ������ ��쿡 group�� id�� �ȴ�.
	*         group���� �����ϴ� ������ �˻� �ӵ��� ������ �� �� �ִ�.     
	*         �Ϲ������� object, character, terrain, texture, ui���� group�� ������ �� �� �ִ�.
	*  \return Pointer resource class
	*  \see UnLoadTexture
	*/
	RwTexture* LoadTexture(const char *pStrName, const char * pResourcePath, EResDictType eType = RES_TEX_DEFAULT_DICT, const char *pStrMaskName = NULL);

	/**
    *  RenderWare texture�� ���������� �����ϴ� �Լ�.
    *
	*  \param pStrName file name.
	*  \param iWidth texture width.
	*  \param iHeight texture height.
	*  \param iDepth pixel ����.
	*  \param eFilterMode texture filter mode.
	*  \param eFormat raster format.
	*  \param eType texture dictionary type.(CNtlPLResourceManager �� EResDictType ���).
	*  \return Pointer renderware texture pointer
	*  \see LoadTexture
	*  \see UnLoadTexture
	*/

	RwTexture* CreateTexture(const char *pStrName, 
							RwInt32 iWidth, 
							RwInt32 iHeight,
							RwInt32 iDepth,
							RwRasterFormat eFormat, 
							EResDictType eType = RES_TEX_DEFAULT_DICT);

	/**
    *  resource�� unload �Ѵ�.
    *
	*  \param pResource unload�� resource pointer
	*  \see LoadWorld	
	*  \see LoadClump	
	*  \see LoadAtomic
	*  \see LoadTexture
	*/
	void UnLoad(CNtlPLResource *pResource);

	
	/**
    *  scheduling�� ��ϵǾ� �ִ� entity�� �ش��ϴ� scheduling node�� �����Ѵ�.
    *
	*/
	void UnLoadScheduling(CNtlPLEntity *pPLEntity, CNtlPLResource *pResource);

	/**
    *  texture�� unload �Ѵ�.
    *
	*  \param pResource unload�� resource pointer
	*  \see LoadTexture	
	*/
	void UnLoadTexture(RwTexture *pTexture);

	// woody1019
	//RwBool SetAlphaValue(RwTexture *pTexture, RwUInt8 Value, RwV2d Pos);
	RwBool	SetColor(RwTexture* _pTexture, DWORD _FillColor);
	RwBool	SetColor(RwTexture *pTexture, RwReal OpaLvl, POINT& TexelPos);
	RwBool	SetColor(RwTexture *pTexture, RwInt32 Value, RwV2d Pos);
	RwBool	SetAlphaValueInc(RwTexture *pTexture, RwInt32 Value, RwV2d Pos);
	RwBool	SetAlphaValueDec(RwTexture *pTexture, RwInt32 Value, RwV2d Pos);
	RwBool	SetAlphaBits(RwTexture *pTexture, RwUInt8 Value, RwV2d Pos);
	RwBool	SaveAlphaBits(RwTexture *pTexture, FILE *pFile);
	RwBool	SaveTexture(RwTexture *pTexture, FILE *pFile);
	RwBool	LoadTexture(RwTexture *pTexture, FILE *pFile);
	RwBool	LoadTexture(RwTexture *pTexture, BYTE* pBuff);
	RwBool	LoadAlphaBits(RwTexture *pTexture, RwUInt8 *pPreparedBits);
	RwBool	LoadAlphaBitsShadowMap(RwTexture *pTexture, FILE* pFile, RwRGBA* pShdowClr);
	RwBool	SaveAlphaBitsShadowMap(RwTexture *pTexture, FILE* pFile);
	RwBool	SaveTextureShadowMap(RwTexture *pTexture, FILE *pFile);
	RwBool	LoadTextureShadowMap(RwTexture *pTexture, FILE *pFile);

	RwBool	CopyRaster(RwTexture *pSrcTex, RwTexture *pDstTex);


	void	SetLoadScheduling(RwBool bSchedule); 
	RwBool	IsLoadScheduling();

	void	SetDeleteScheduling(RwBool bSchedule);
	RwBool	IsDeleteScheduling();

	RwBool	IsEmptyLoadScheduling(void);

	RwReal	GetAlphaAverageDensity(RwTexture* _pTex);
	RwReal	GetAlphaAverageDensity(BYTE* _pAlphaBits, RwInt32 _Cnt);

	RwBool	TextureLoadLevelPath(const RwChar* pInPath, RwChar** ppOutPath, RwInt32* pOutPathSize);
};


static CNtlPLResourceManager* GetNtlResourceManager(void)
{
	return CNtlPLResourceManager::GetInstance();
}

inline void	CNtlPLResourceManager::SetLoadScheduling(RwBool bSchedule)
{
	m_bLoadScheduling = bSchedule;
}

inline void	CNtlPLResourceManager::SetDeleteScheduling(RwBool bSchedule)
{
	m_bDeleteScheduling = bSchedule;
}

inline RwBool CNtlPLResourceManager::IsLoadScheduling()
{
	return m_bLoadScheduling;
}

#endif
