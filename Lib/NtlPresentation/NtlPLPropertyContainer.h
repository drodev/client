/*****************************************************************************
*
* File			: NtlPLPropertyContaier.h
* Author		: HyungSuk, Jang
* Copyright	: (��)NTL
* Date			: 2005. 8. 09	
* Abstract		: Presentation object property container class
*****************************************************************************
* Desc         : 
*
*****************************************************************************/


#ifndef __NTL_PLPROPERTY_CONTAINER_H__
#define __NTL_PLPROPERTY_CONTAINER_H__

#include "NtlWorldCommon.h"
#include "NtlPLDef.h"
#include "NtlFileSerializer.h"

#pragma warning(disable : 4996)

class CNtlPLProperty;

/**
* \ingroup NtlPresentation
* Presentation�� ����ϴ� ��� property�� �����ϴ� conatiner class �̴�.\
* �� ��ü�� singleton ��ü�̴�. GetInstance() �Լ��� ����Ѵ�.
*
*/
class CNtlPLPropertyContainer
{
public:

	typedef std::map<std::string, CNtlPLProperty*> MapProp;

private:

	static CNtlPLPropertyContainer* m_pInstance;

protected:

	MapProp m_mapSky;			/* sky property **/
	MapProp m_mapNtlWorld;		/* woody1019 **/
	MapProp m_mapSound;			/* woody1019 **/
	MapProp m_mapShoreLine;		/* woody1019 **/
	MapProp m_mapWater;			
	MapProp m_mapObject;		/* object property **/
	MapProp m_mapCharacter;		/* character property **/
	MapProp m_mapEffect;		/* effect property **/	
	MapProp m_mapSpline;		/* by agebreak **/	
	MapProp m_mapGui;
	MapProp m_mapItem;          /* by hodong **/
	MapProp m_mapPlant;
	MapProp m_mapWeather;

public:

	/**
	*  property�� container�� add�Ѵ�.
	*  \param eType entity type.
	*  \param pProp add�� property pointer.
	*/
	// by agebreak
	virtual RwBool AddProp(ENtlPLEntityType eType, CNtlPLProperty *pProp);

protected:

	// woody1019
	RwBool	LoadNtlWorld(const RwChar *pFileName);
	RwBool	LoadWater(const RwChar *pFileName);
	RwBool	LoadShoreLine(const RwChar *pFileName);
	RwBool	LoadSound(const RwChar *pFileName);

	/**
	*  effect property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*  \see LoadObject
	*  \see LoadCharacter
	*/
	RwBool	LoadEffect(const RwChar *pFileName);

	/**
	*  effect property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*  \see LoadObject
	*  \see LoadCharacter
	*  \see LoadEffect
	*/
	RwBool	LoadGui(const RwChar *pFileName);

	/**
	*  plant property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*/
	RwBool	LoadPlant(const RwChar *pFileName);

	/**
	*  weather property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*/
	RwBool	LoadWeather(const RwChar *pFileName, RwUInt32 uiLevel);

	/**
	*  field bgm/env/share property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*/
	RwBool	LoadSoundField(const RwChar *pFileName, const RwChar* pName);

	// Serialize ����/�ε� ���� �޼ҵ��
	RwBool	SaveCharacterSerialize(CNtlFileSerializer& sl);
	RwBool	LoadCharacterSerialize(CNtlFileSerializer& sl);

	RwBool	SaveObjectSerialzie(CNtlFileSerializer& sl);
	RwBool	LoadObjectSerialize(CNtlFileSerializer& sl);

	RwBool	SaveItemSerialize(CNtlFileSerializer& sl);
	RwBool	LoadItemSerialize(CNtlFileSerializer& sl);

public:

	/**
	*  Default constructor for Presentation property container
	*
	*/
	CNtlPLPropertyContainer();

	/**
	*  destructor for Presentation property container
	*
	*/
	virtual ~CNtlPLPropertyContainer();

	/**
	*  property container ��ü�� ������ ���� ȣ���ϴ� �Լ�.
	*  \see Destroy
	*/
	virtual RwBool Create(void);

	/**
	*  property container ��ü�� ������ ���� ȣ���ϴ� �Լ�.
	*  \see Destroy
	*/
	virtual void Destroy(void);

	/**
	*  property container instaince �Լ�.
	*  �� �Լ��� ����Ͽ� ��� �Լ�/������ �����Ѵ�.
	*  \see Destroy
	*/
	static CNtlPLPropertyContainer* GetInstance(void);

	/**
	*  presentation�� ����ϴ� ��� property file�� loading�ϴ� �Լ�.
	*  \param pFileName�� filename�̴�.
	*/
	virtual RwBool Load();

	/**
	*  object property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*  \see LoadCharacter
	*  \see LoadEffect
	*/
	RwBool LoadObject(const RwChar *pFileName);

	/**
	*  character property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*  \see LoadObject
	*  \see LoadEffect
	*/
	RwBool LoadCharacter(const RwChar *pFileName);

	/**
	*  item property�� load �ϴ� �Լ�.
	*  \param pFileName property file name.
	*  \return �����ϸ� TRUE, �����ϸ� FALSE.
	*  \see LoadObject
	*  \see LoadEffect
	*/
	RwBool LoadItem(const RwChar *pFileName);


	virtual RwBool LoadSerialize(RwBool bEncrypt = FALSE, RwChar* szCryptPassword = NULL);				///< ���̳ʸ��� �����õ� �����͵��� �ε��Ѵ�.
	virtual RwBool SaveSerialize(RwBool bEncrypt = FALSE, RwChar* szCryptPassword = NULL);				///< ���̳ʸ��� �����õ� �����͵��� ���̺��Ѵ�.

	void		SaveObjectScript(std::string &strFileName);
	void		SaveCharacterScript(std::string &strFileName);
	void		SaveItemScript(std::string &strFileName);

	/**
	*  presentation�� ����ϴ� ��� property file�� loading�ϴ� �Լ�.
	*  \param eType�� entity type
	*  \param uiId ���� property id
	*  \return �����ϸ� property ��ü pointer, �����ϸ� NULL �̴�.
	*/
	CNtlPLProperty* GetProperty(ENtlPLEntityType eType, const RwChar *pKey);

	/**
	*  entity type�� �ش��ϴ� property container�� ���� ������ ���´�.
	*  \param eType�� entity type
	*  \param mapProps property container�� ���� ���� ����.
	*/
	MapProp& Gets(ENtlPLEntityType eType);

#ifdef dNTL_WORLD_TOOL_MODE
	RwBool ReloadPlant();
	RwBool ReloadWeather();
#endif
};

#endif
