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

#ifndef __NTL_PLRENDERGROUP_H__
#define __NTL_PLRENDERGROUP_H__

#include <rwcore.h>
#include <rpworld.h>
#include <map>
#include <list>

class CNtlPLEntity;

/**
* \ingroup NtlPresentation
* ���� ������ entity�� group �����ϴ� ��ü.
* stl ���� �迭 map�� ����Ѵ�.
*
*/

class CNtlPLRenderGroup
{
public:

	typedef std::map<RwUInt32, CNtlPLEntity*> MapEntity;

private:

	RwUInt32 m_uiLayer;
	MapEntity m_mapEntity;		/* entity map container **/

public:

	/**
	*  destructor for Presentation render group
	*
	*/

	~CNtlPLRenderGroup();

	/**
	*  render group ��ü�� ������ ���� ȣ���ϴ� �Լ�.
	*  \see Destroy
	*/
	RwBool Create(void);

	/**
	*  render group ��ü�� �����Ǳ� ���� ȣ���ϴ� �Լ�.
	*  \see Create
	*/
	void Destroy(void);

	/**
	*  render group layer setting.
	*  \see GetLayer
	*/
	void SetLayer(RwUInt32 uiLayer);

	/**
	*  render group layer ������.
	*  \see SetLayer
	*/
	RwUInt32 GetLayer(void) const;

	/**
	*  group�� entity�� add �Ѵ�.
	*  \param pEntity�� add�� entity pointer�̴�.
	*  \see RemoveEntity
	*/
	RwBool AddEntity(const CNtlPLEntity *pEntity);

	/**
	*  group�� entity�� remove �Ѵ�.
	*  \param pEntity�� remove�� entity pointer�̴�.
	*  \see AddEntity
	*/
	void RemoveEntity(CNtlPLEntity *pEntity);

	/**
	*  group���� �ش� entity�� ã�´�.
	*  \param pEntity�� container���� ã�� entity pointer
	*  \return �����ϸ� TRUE, �����ϸ� FALSE
	*/
	RwBool FindEntity(const CNtlPLEntity *pEntity);

	/**
	*  group���� entity ������ ���Ѵ�.
	*  \return entity ����.
	*/
	RwInt32 GetEntityCount(void);

	/**
	*  group�� �ش��ϴ� entity container ������ �����Ѵ�.
	*  \return entity container(m_mapEntity) ������ ����.
	*/
	MapEntity* GetEntities(void);

	/**
	*  group�� �ش��ϴ� ��� entity�� ��´�.
	*/
	void Gets(std::list<CNtlPLEntity*>& listEntities);
};

inline void CNtlPLRenderGroup::SetLayer(RwUInt32 uiLayer)
{
	m_uiLayer = uiLayer;
}

inline RwUInt32 CNtlPLRenderGroup::GetLayer(void) const
{
	return m_uiLayer;
}


inline CNtlPLRenderGroup::MapEntity* CNtlPLRenderGroup::GetEntities(void)
{
	return &m_mapEntity;
}


#endif