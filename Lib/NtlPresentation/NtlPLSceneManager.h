/*****************************************************************************
 *
 * File			: NtlPLSceneManager.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 01	
 * Abstract		: Presentation scene manager base class 
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLSCENEMANAGER_H__
#define __NTL_PLSCENEMANAGER_H__

#include <rwcore.h>
#include <rpworld.h>
#include "NtlPLEntity.h"
#include "NtlPLSceneManagerFactory.h"
#include "NtlPLPicking.h"

class	CNtlPLDojoContainer;

class	CNtlPLFog;
class	CNtlPLSky;
class	CNtlPLPlant;
class	CNtlPlLightEvent;
class   CNtlPLWorldEntity;
struct	sNPE_COLLISION_PARAM;

enum EActiveWorldType
{
	AW_NONE,
	AW_RWWORLD,
	AW_HEGITHFIELD
};

/**
 * \ingroup NtlPresentation
 * presentation�� scene manager �߻�ȭ class �̴�.
 * ������� ������ �߻��Լ��� �����Ǿ� �ִ�.
 * Dbo client�� editor������ �� class�� ��ӹ޾� ������ �Ѵ�.
 *
 */
class CNtlPLSceneManager
{
public:

	/**
    *  presentation scene manager�� ������ ���� ȣ���ϴ� interface �Լ�.
	*  \return �����ϸ� true�� �����ְ�, �����ϸ� false�� �����ش�.
    *
    */
	virtual RwBool Create(void) = 0;

	/**
    *  presentation scene manager�� �Ҹ�Ǳ� ���� ȣ���ϴ� interface �Լ�.
    *
    */
	virtual void Destroy(void) = 0;


	/**
    *  presentation scene manager update �Լ�.
    *
    */
	virtual void Update(RwReal fElapsed) = 0;

	/**
    *  presentation scene manager update ���� ui�� entity�� rendering �ϱ� ���� �Լ�.
	* render ware�� camera update���� ��ġ�� �ȵȴ�.
	* UI�� camera texture�� ����ϹǷ�, main scene camera�� update�� ��ġ�� �ȵȴ�.
    *
    */
	virtual void UpdateBeforeCamera(RwReal fElapsed) = 0;


	/**
    *  presentation scene manager render �Լ�.
    *
    */
	virtual void Render(void) = 0;
	virtual void Render4RWWorld(void) = 0;

	/**
    *  presentation scene manager postrender �Լ�.
    *
    */
	virtual void PostRender(void) = 0;

	/**
    *  presentation scene active on/off flag.
    *
    */
	virtual void SetThreadLoad(RwBool bThreadLoad) = 0;


	/**
    *  reset gui manager
    *
    */
	virtual void ResetGuiManager(RwInt32 iScreenWidth, RwInt32 iScreenHeight) = 0;

	/**
    *  entity�� create �ϴ� factory interface  �Լ�.
	*  entity factory class�� ���� ����������� �����ؾ� �Ѵ�.
	*  \return �����ϸ� entity base pointer�� �����ְ�, �����ϸ� NULL�� �����ش�.
	*  \see DeleteEntity
    *
    */
	virtual CNtlPLEntity* CreateEntity(ENtlPLEntityType eType, const RwChar *pKey, const SPLEntityCreateParam *pParam = NULL) = 0;

	/**
    *  entity�� delete �ϴ� factory interface �Լ�.
	*  entity factory class�� ���� ����������� �����ؾ� �Ѵ�.
	*  \param pEntity ������ entity pointer
	*  \see CreateEntity
    *
    */
	virtual void DeleteEntity(CNtlPLEntity *pEntity) = 0;

	/**
    *  entity�� scene manager�� add interface �Լ�.
	*  \param pEntity scene manager�� �߰��� entity pointer
	*  \see RemovePLEntity
    *
    */
	virtual RwBool AddPLEntity(CNtlPLEntity *pEntity) = 0;

	/**
    *  entity�� scene manager���� remove�ϴ� interface �Լ�.
	*  \param pEntity scene manager�� ������ entity pointer
	*  \see AddPLEntity
    *
    */
	virtual void RemovePLEntity(CNtlPLEntity *pEntity) = 0;


	/**
    *  entity�� scene manager�� update�� add�ϴ� interface �Լ�.
	*  \param pEntity scene manager�� add�� entity pointer
	*  \see RemoveUpdate
    *
    */
	virtual void AddUpdate(CNtlPLEntity *pEntity) = 0;

	/**
    *  entity�� scene manager�� update�� remove�ϴ� interface �Լ�.
	*  \param pEntity scene manager�� remove�� entity pointer
	*  \see AddUpdate
    *
    */
	virtual void RemoveUpdate(CNtlPLEntity *pEntity) = 0;

	/**
    *  entity�� distance filtering manager�� �߰��Ѵ�.
	*  \param pEntity distance filtering manager�� add�� entity pointer
	*  \see RemoveDistanceFilter
    *
    */
	virtual void AddDistanceFilter(CNtlPLEntity *pEntity) = 0;

	/**
    *  entity�� distance filtering manager�� �����Ѵ�.
	*  \param pEntity distance filtering manager�� remove�� entity pointer
	*  \see AddDistanceFilter
    *
    */
	virtual void RemoveDistanceFilter(CNtlPLEntity *pEntity) = 0;

	/**
    *  ���� active �Ǿ� �ִ� world type(renderware world or height field�ΰ�?)
    *
    */
	virtual EActiveWorldType GetActiveWorldType(void) = 0;

	/**
	*  world �� �غ� �Ǿ� �ִ°�?
	*  \return ready is TRUE or FALSE
	*
	*/
	virtual RwBool IsWorldReady(void) = 0;

	/**
    *  world position�� �ش��ϴ� terrain �� ������Ʈ�� ������ world�� height�� ���ϴ� interface �Լ�.
	*  \return terrain or object height value�� �����Ѵ�.
	*  \param pWorldPos world position�� �ش��ϴ� RwV3d pointer
	*
    */
	virtual RwBool GetWorldHeight(const RwV3d *pWorldPos, RwReal& fHeight, RwV3d *pNormal, RwReal fLineLen = 1000.0f) = 0;

	/**
    *  world position�� �ش��ϴ� terrain ������ �ش��ϴ� height�� ���ϴ� interface �Լ�.
	*  \return terrain height value�� �����Ѵ�.
	*  \param pWorldPos world position�� �ش��ϴ� RwV3d pointer
	*
    */
	virtual RwBool GetTerrainHeight(const RwV3d *pWorldPos, RwReal& fHeight) = 0;

	/**
    *  mouse picking�ÿ� picking�� entity�� �����ϴ� interface �Լ�.
	*  \param iPosX mouse�� screen x-��ǥ
	*  \param iPosX mouse�� screen y-��ǥ
	*
    */
	virtual RwBool PickWorld(RwInt32 iPosX, RwInt32 iPosY, SWorldPickInfo& sPickInfo, RwReal fPickTerrainLimit, RwReal fPickObjLimit) = 0;

	/**
	*  World�� ���� ������ Ray InterSection�� �����Ѵ�.
	*/
	virtual RwBool PickTerrian(RwV3d& vStartPos, RwV3d& vEndPos, SWorldPickInfo& sPickInfo) = 0;
	virtual RwBool PickTerrianAndWater(RwV3d& vStartPos, RwV3d& vEndPos, SWorldPickInfo& sPickInfo) = 0;

	/**
    *  camera �浹 �˻縦 �Ͽ�, ���ο� �浹 camera ��ġ�� ���Ѵ�.
	*  \param1 pCameraPos ���� camera�� position
	*  \param2 pLookAt ���� camera�� look at position
	*  \param2 ���ο� camera�� position
	*
    */
	virtual RwBool GetCameraCollision(const RwV3d *pCameraPos, const RwV3d *pLookAt, RwReal fRadius, RwV3d& vNewPos) = 0;

	/**
	*  character �浹 ó�� �Լ�.
	*/
// 	virtual RwBool CTChar2Poly(sNPE_COLLISION_PARAM& sNPECollisionParam) = 0;
// 	virtual RwBool CTLine2Sphere(RwLine* _pLine, sNPE_COLLISION_PARAM& sNPECollisionParam) = 0;

	/**
    *  RpWorld pointer�� ������ interface �Լ�.
	*
    */
	virtual RpWorld* GetWorldPtr(void) = 0;

	virtual void SetDistanceFilter(RwBool bEnable) = 0;

    virtual RwBool GetDistanceFilterEnable() = 0;

	/**
	* world attribute
	* \return world�� attribute value�� �����Ѵ�.
	* \see GetWorldNormalAttribute
	* \see GetWorldSpecialAttribute
	*/
	virtual DWORD GetWorldAttribute(RwV3d vPos) = 0;

	/**
	* world normal attribute
	* \return world�� normal attribute value�� �����Ѵ�.
	* \see GetWorldSpecialAttribute
	*/
	virtual DWORD GetWorldNormalAttribute(RwV3d vPos) = 0;

	/**
	* world special attribute(�ϹݼӼ� �� Ư���Ӽ����� ������)
	* \return world�� special attribute value�� �����Ѵ�.
	* \see GetWorldNormalAttribute
	*/
	virtual DWORD GetWorldSpecialAttribute(RwV3d vPos) = 0;

	/**
	* world material attribute
	* \return world�� material attribute value�� �����Ѵ�.
	*/
	virtual BYTE GetWorldMaterialAttribute(RwV3d vPos) = 0;

	/**
	* �Ϲ������� world�� normal attribute�� üũ�Ͽ� ���� ��쿡�� ����Ѵ�.
	* \return world�� water ����.
	*/
	virtual RwReal GetWorldWaterHeight(RwV3d vPos) = 0;



	/**
	* ���� ��ġ�� Bloom effect power factor�� ���ؿ´�.
	* \return if TRUE �̸� ���� ��ȿ�ϰ�, FALSE�̸� ��ȿ���� �ʴ�.
	*/
	virtual RwReal						GetActiveBloomFactor(void) = 0; 

	virtual VOID						SetActiveSky(CNtlPLSky* _pNtlPLSky) = 0;

	virtual	CNtlPLDojoContainer*		GetDojoContainer(void) = 0; 

	virtual CNtlPLSky*					GetSky(void) = 0;
	virtual CNtlPLFog*					GetFog(void) = 0;
	virtual CNtlPLPlant*				GetPlant(void) = 0;
	virtual CNtlPLWorldEntity*			GetWorld(void) = 0;

	// ���� ���� ��ǥ�� �̵��Ҽ� �ִ��� �������� üũ���ش�.
	virtual RwBool	GetAvailablePos(RwV3d& _CurPos) = 0;

	// ���ӿ��� �ǽð����� ���κз������� PVS ��� ������ �����ϰ� ������
	virtual VOID	SetWorldPVSActivation(RwBool _Flag) = 0;

	// ���� ���� ��ǥ�� ������ ������ ȸ�� ��Ʈ��Ʈ�� ��´�.
	virtual RwBool	GetWorldTerrainRotate(RwMatrix* pmatOut, RwV3d* pvPos, RwBool bPosHeightChange, RwReal fLineLen = 1000.0f) = 0;

    // ���带 ��� ������ ��ü�� �����Ѵ�. (NULL�� �����ϸ� ī�޶� ��ġ �߽����� ���尡 �鸰��)
    virtual VOID	SetSoundListener(CNtlPLEntity* pEntity) = 0;

	// ������ ��ġ�� �׸��� ������ ��� ���� �� ���
	virtual RwBool	GetWorldShadowColor(RwV3d& vPos, RwRGBA* pOutColor) = 0;

	// ������ ��ġ�� ����� ��������� �˰� ���� �� ���
	virtual RwBool	GetWorldLightColor(RwV3d& vPos, RwRGBA* pOutColor, RwBool bCalcShadow) = 0;

    virtual void	SetEntityVisible(ENtlPLEntityType eLayer, RwBool bVisible) = 0;             ///< �������̾��� �������� On/Off �Ѵ�. (�׽�Ʈ��)

	// PLENTITY_SUN Entity Visible�� �����Ѵ�.
	virtual void	SetVisiblePlanet(RwBool bVisible) = 0;

	virtual void	RunableRainBloomLight(RwReal fBloomShaderFadeInTime, RwReal fBloomShaderFadeOutTime) = 0;

	virtual void	RunableRainSkyLight(RwReal fSkyFadeInTime, RwReal fSkyFadeOutTime) = 0;
};

/**
*  scene manager�� instace �Լ�.
*
*/
inline CNtlPLSceneManager* GetSceneManager(void)
{
	return CNtlPLSceneManagerFactory::GetInstance(); 
}

#endif