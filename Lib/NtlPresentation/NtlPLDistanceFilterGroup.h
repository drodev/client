/*****************************************************************************
*
* File			: NtlPLDistanceFilterGroup.h
* Author		: HyungSuk, Jang
* Copyright	: (��)NTL
* Date			: 2006. 12. 12	
* Abstract		: Presentation distance filtering group 
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_PLDISTANCEFILTER_GROUP_H__
#define __NTL_PLDISTANCEFILTER_GROUP_H__

class CNtlPLEntity;

/**
* \ingroup NtlPresentation
* ���� ������ entity�� group �����ϴ� ��ü.
* stl ���� �迭 map�� ����Ѵ�.
*
*/

class CNtlPLDistanceFilterGroup
{
public:

	enum { MAX_DIST_FILTER_GROUP = 200 };

	typedef std::map<CNtlPLEntity*, CNtlPLEntity*> MapSet;
	typedef std::list<MapSet*> ListGroup;


private:

	RwBool					m_bFirst;
	ListGroup::iterator		m_itCurr;
	ListGroup				m_listGroup;

	MapSet*		AllocateSet(void);
	void		DeAllocateSet(MapSet *pSet);
	MapSet*		FindInsert(void);

public:

	/**
	*  constructor for Presentation distance filtering group
	*
	*/

	CNtlPLDistanceFilterGroup();

	/**
	*  destructor for Presentation distance filtering group
	*
	*/

	~CNtlPLDistanceFilterGroup();

	/**
	*  distance filtering group ��ü�� ������ ���� ȣ���ϴ� �Լ�.
	*  \see Destroy
	*/
	RwBool Create(void);

	/**
	*  distance filtering group ��ü�� �����Ǳ� ���� ȣ���ϴ� �Լ�.
	*  \see Create
	*/
	void Destroy(void);

	/**
	*  distance filtering group�� entity�� �߰��Ѵ�.
	*  \see RemoveEntity
	*/
	void AddEntity(CNtlPLEntity *pPLEntity);

	/**
	*  distance filtering group�� entity�� �����Ѵ�.
	*  \see RemoveEntity
	*/
	void RemoveEntity(CNtlPLEntity *pPLEntity);

	/**
	*  next update filter�� ���´�.
	*/
	const MapSet* GetNextUpdateSet(void);

	/**
	*  distance filtering group�� ���´�.
	*/
	const ListGroup& GetEntities(void) const;

	/**
	*  distance filtering set ����.
	*/
	RwInt32 GetFilterSetCount(void);

	/**
	*  distance filtering group�� ���Ե� �� entity�� ����.
	*/
	RwInt32 GetEntityCount(void);
};

#endif
