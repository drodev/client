#pragma once

#include "NtlDebug.h"
#include "ntlworldcommon.h"
#include "NtlPLEntity.h"

#ifdef dNTL_WORLD_TOOL_MODE

#include "NtlPLObject.h"
#include "NtlWorldPaletteDefine.h"

#endif

enum EPLWorldLightType
{
	EPLWORLDLIGHT_BASE,			// CNtlPLWorldLight_Base // ������� �ʴ´�.
	EPLWORLDLIGHT_SPHERE,		// CNtlPLWorldLight_Sphere
	EPLWORLDLIGHT_BOX			// CNtlPLWorldLight_Box
};

struct SPLWorldLightCreateParam : public SPLEntityCreateParam
{
	RwUInt8			uiRed;
	RwUInt8			uiGreen;
	RwUInt8			uiBlue;
};

class CNtlPLWorldLight_Base : public CNtlPLEntity
{
protected:
#ifdef dNTL_WORLD_TOOL_MODE
	CNtlPLObject*	m_pNtlPLObj;
#endif

	RwSphere		m_Sphere;
	RwRGBAReal		m_clrfLight;

public:
	CNtlPLWorldLight_Base();
	virtual ~CNtlPLWorldLight_Base();

	virtual RwBool				Create(const SPLEntityCreateParam* pParam = NULL)				= 0;
	virtual void				Destroy()														= 0;

	virtual RwBool				SetProperty(const CNtlPLProperty *pData);
	virtual RwBool				Render();
	virtual RwBool				Update(RwReal fElapsed);

	virtual void				SetPosition(const RwV3d* pvPos);
	virtual RwV3d				GetPosition();

	// Radius �������� Light�� �˻��Ѵ�.
	virtual void				SetRadius(RwReal fRadius);
	virtual RwReal				GetRadius();

	virtual void				SetColor(RwUInt8 uiRed, RwUInt8 uiGreen, RwUInt8 uiBlue);
	virtual	RwRGBA				GetColor();
	virtual void				SetColorf(RwReal fRed, RwReal fGreen, RwReal fBlue);
	virtual	RwRGBAReal			GetColorf();

	virtual EPLWorldLightType	GetWorldLightType()																= 0;
	virtual RwBool				GetWorldLightColorf(const RwV3d* pvPos, RwRGBAReal* pclrfOut, void* pUserData)	= 0;

	virtual void				SetVision(RwBool _Flag) = 0;
	
protected:
	/*
	IsIn :	�⺻���� �˻� ����� Shpere�� �������.
			�׷��Ƿ� m_Sphere�� Radius ���� �ʿ��ϴ�. Create�� ���� �Է�����.
			���� ������� �ʴ´ٸ� IsIn �Լ��� Overriding �Ѵ�.
	*/
	virtual RwBool				IsIn(const RwV3d* pvPos, RwReal* pfOutDistance = NULL);
	virtual RwBool				IsInSphere(const RwV3d* pvPos, RwReal* pfOutDistance = NULL);
};