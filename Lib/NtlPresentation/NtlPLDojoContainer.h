#pragma once

#include "NtlPLEmblemMaker.h"

struct SNtlPLDojoProp
{
	SNtlPLDojoProp::SNtlPLDojoProp()
	{
		iLevel = 1;
	}

	RwInt32			iLevel;
	sEmblemFactor	sEmblem;
};

class CNtlPLDojoContainer
{
public:
	typedef std::map<RwInt32, SNtlPLDojoProp>	MAP_DOJO;
	typedef MAP_DOJO::iterator					MAP_DOJO_IT;

public:
	CNtlPLDojoContainer();
	virtual ~CNtlPLDojoContainer();

	virtual RwBool					Create();
	virtual void					Destroy();
	
	virtual void					Clear();
	
	virtual void					SetDojo(RwInt32 iID, RwInt32 iLevel, sEmblemFactor* pEmblem);	// iID�� 0���� Ŀ�� �Ѵ�.
	virtual void					SetDojo_Level(RwInt32 iID, RwInt32 iLevel);						// iID�� 0���� Ŀ�� �Ѵ�.
	virtual void					SetDojo_Emblem(RwInt32 iID, sEmblemFactor* pEmblem);			// iID�� 0���� Ŀ�� �Ѵ�.
	virtual RwBool					GetDojo(RwInt32 iID, SNtlPLDojoProp* pEmblemOut);

	virtual void					SetDojoWorld(RwInt32 iLevel, sEmblemFactor* pEmblem);
	virtual void					SetDojoWorld_Level(RwInt32 iLevel);
	virtual void					SetDojoWorld_Emblem(sEmblemFactor* pEmblem);
	virtual RwBool					GetDojoWorld(SNtlPLDojoProp* pEmblemOut);

	virtual void					RefreshDojo(); // Upgrade �Ǵ� Downgrade Effect�� ���� �۵� �ȴ�.

private:
	MAP_DOJO						m_mapDojoContainer;
};