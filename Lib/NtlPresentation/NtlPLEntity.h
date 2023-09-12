/*****************************************************************************
 *
 * File			: NtlPLEntity.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 01	
 * Abstract		: Presentation object entity base class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_PLENTITY_H__
#define __NTL_PLENTITY_H__

#define dNTL_WORLD_CULLING_NEW

#include <string>
#include <rwcore.h>
#include <rpworld.h>
#include "NtlPLDef.h"
#include "NtlPLGlobal.h"
#include "NtlPLProperty.h"

#define ENABLE_PLENTITY_FLAGS(flags,check)  (styles & check) 

typedef struct _SPLEntityCreateParam
{
	const RwV3d *pPos;
	RwReal		fAnimSpeed;
	RwReal		fAnimOffset;
	void*		_pUserData;

public:
	inline void operator = (_SPLEntityCreateParam& _EntityCreateParam)
	{
		pPos		= _EntityCreateParam.pPos;
		fAnimSpeed	= _EntityCreateParam.fAnimSpeed;
		fAnimOffset = _EntityCreateParam.fAnimOffset;

		// careful for shallow copy
		_pUserData	= _EntityCreateParam._pUserData;
	}	

	_SPLEntityCreateParam()
	{
		_pUserData = NULL;
	}

}SPLEntityCreateParam;

class CNtlPLResource;
class CNtlElapsedControllerGroup;
class CNtlPLEntityBlendController;


/**
 * \ingroup NtlPresentation
 * Presentation entity base class�̴�.
 * 
 */
class CNtlPLEntity
{	
protected:
#ifdef dNTL_WORLD_CULLING_NEW
	RwUInt16	m_uiRenderFrame;
#endif

	std::string m_strName;				/**< String describing the presentation entity name */
	RwUInt32 m_uiClassID;				/**< presentation entity class type */
	RwUInt32 m_uiLayer;					/**< presentation entity layer */
	RwUInt32 m_uiMinimapLayer;			/**< presentation entity minimap layer : is flags */
	RwUInt32 m_uiFlags;					/**< presentation entity flags */
	RwUInt32 m_uiSID;					/**< trigger entity id(0xffffffff for default; means triggers are not existed) */
	RwUInt32 m_uiSerialID;				/**< simulaion layer object serial id */
#ifndef dNTL_WORLD_CULLING_NEW
	RwUInt32 m_uiCullIID;				/**< Culling Id */
#endif
	DWORD	 m_ObjNameIdx;				// object name index; not available for client
	RwUInt16 m_byPickOrder;				/**< Picking order */

	RwUInt32 m_uiCullFlags;				/**< presentation entity Culling flags */

	RwReal m_fWeightAlpha;				/**< alpha weight value */
	RwReal m_fWeightElapsedTime;		/**< update weight elapsed time */
	RwReal m_fVisibleCullingDistance;	/**< Object Culling Distance */

	CNtlElapsedControllerGroup *m_pElapController;
	CNtlPLEntityBlendController *m_pBlendController;

public:

	/**
    *  Default constructor for Presentation entity 
    *
    */
	CNtlPLEntity(); 

	/**
    *  Virtual destructor for Presentation entity 
    *
    */
	virtual ~CNtlPLEntity();

	/**
	*  entity�� ������ ���� ȣ���ϴ� interface �Լ�.
	*  \see Destroy
	*/
	virtual RwBool Create(const SPLEntityCreateParam *pParam = NULL) = 0;

	/**
	*  entity�� creat �Լ��� ȣ��� ���� ����Ǵ� interface �Լ�.
	*  \see Destroy
	*/
	virtual RwBool PostCreate(void) { return TRUE; }

	/**
	*  entity�� �����Ǳ� ���� ȣ���ϴ� interface �Լ�.
	*  \see Create
	*/
	virtual void Destroy(void) = 0;

	/**
	*  entity update interface �Լ�
	*  \param fElapsed update delta time
	*  \see Render
	*/
	virtual RwBool Update(RwReal fElapsed);

	/**
	*  entity CullingTest interface �Լ�
	*  \see SetCull
	*  \see IsCulled
	*/
#ifdef dNTL_WORLD_CULLING_NEW
	virtual RwBool	CullingTest(RwCamera* pRwCamera, RwUInt16 uiRenderFrame);
#else
	virtual RwBool	CullingTest(RwCamera* pRwCamera);	
#endif
	//virtual RwBool	CullingTest(RwCamera* pRwCamera, const RpAtomic* pAtomic);

    /************************************************************************/
    /* When you exit and delete the current update without deleting the Entity immediately*/
    /* Interface to call                                                  */
    /************************************************************************/
    virtual void   Finish() {}

	/**
	*  entity rendering interface �Լ�
	*  \see Upate
	*/
	virtual RwBool Render(void) = 0;

	/**
	*  entity rendertotexture interface �Լ�
	*/
	virtual RwBool RenderToTexture(void) { return TRUE; }

	/**
	*  entity property setting interface �Լ�
	*  \param pData Property base pointer
	*/
	virtual RwBool SetProperty(const CNtlPLProperty *pData) = 0;

	/**
	*  Add renderware resource to world.
	*  \see RemoveWorld
	*/
	virtual void AddWorld(void)		{}

	/**
	*  renderware resource�� world���� �����Ѵ�.
	*  \see AddWorld
	*/
	virtual void RemoveWorld(void)	{}

	/**
	*  resource manager���� scheduling �� resource�� �����ϱ� ���� �˷��ش�.
	*/
	virtual void CallPreSchedulingResource(void) {}

	/**
	*  resource manager���� scheduling �� resource�� �˷��ش�.
	*/
	virtual void CallSchedulingResource(CNtlPLResource *pResource) {}
	virtual void CallSchedulingResourceOnly() {}
    virtual RwBool IsSchedulingLoadingComplete() {return TRUE;}

	/**
	*  entity position interface �Լ�
	*  \param pPos entity position pointer.
	*  \see GetPosition
	*/
	virtual void SetPosition(const RwV3d *pPos) { }

	/**
	*  entity direction interface function
	*  \param pDir entity dir pointer.
	*/
	virtual void SetDirection(const RwV3d *pDir) { }
    virtual RwV3d GetDirection() {RwV3d dir;dir.x = dir.y = 0.0f;dir.z = 1.0f; return dir;}

	/**
	*  entity position�� �����ϴ� interface �Լ�.
	*  \return entity position�� �����Ѵ�.
	*  \see SetPosition
	*/
	// by agebreak
	// Would not it be better to use the return type as a pointer or a reference?
	virtual RwV3d GetPosition(void) { return CNtlPLGlobal::m_vZeroV3; }

	/**
	*  entity scale �Լ�.
	*  \param fScale entity scale value.
	*  \see GetScale
	*/
	virtual void SetScale(RwReal fScale) {}

	/**
	*  entity scale value�� ������ �Լ�.
	*  \return fScale entity scale value.
	*  \see SetScale
	*/
	virtual RwReal GetScale(void) { return 1.0f; }

	/**
	*  entity scale vector�� ������ �Լ�.
	*  \return entity scale vector value.
	*  \see SetScale
	*/
	virtual const RwV3d* GetScaleVector(void) const { return NULL; }

	/**
	*  entity rotate�� ��Ű�� �Լ�.
	*  \param fXAngle x-axis rotate.
	*  \param fXAngle y-axis rotate.
	*  \param fXAngle z-axis rotate.
	*/
	virtual void SetRotate(RwReal fXAngle, RwReal fYAngle, RwReal fZAngle) {;}

	/**
	*  entity rotate vector�� ������ �Լ�.
	*  \return entity rotate value.
	*  \see SetRotate
	*/
	virtual const RwV3d* GetRotate(void) const { return NULL;} 

	/**
	*  entity bounding sphere�� ������ �Լ�.
	*  \return bounding sphere pointer.
	*/
	virtual const RwSphere* GetBoundingSphere(void) { return NULL; }

	/**
	*  entity bounding box�� ������ �Լ�.
	*  \return bounding box pointer.
	*/
	virtual const RwBBox* GetBoundingBox(void) { return NULL; }

	/**
	*  entity matrix setting��Ű�� �Լ�.
	*  \param matWorld RwMatrix ����.
	*/
	virtual void SetMatrix(RwMatrix& matWorld) {;}

	/**
	*  entity matrix setting��Ű�� �Լ�.
	*  \return matrix 
	*/
	virtual RwMatrix& GetMatrix(void) { return CNtlPLGlobal::m_matIden; } 

	/**
	*  entity alpha ���� setting �Ѵ�.
	*/
	virtual void SetAlpha(RwUInt8 byValue) { }

	/**
	*  entity color ���� setting �Ѵ�.
	*/
	virtual void SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue) { }

	/**
	*  entity Addcolor ���� setting �Ѵ�.
	*/
	virtual void SetAddColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue) { }

	/**
	*  entity distance culling value�� setting �Ѵ�.
	*/
	virtual void SetVisibleCullingDistance(RwReal fDistance);

	/** 
	*  entity ���� distance culling value
	*  \return culling value
	*/
	virtual RwReal	GetVisibleCullingDistance(void) const { return m_fVisibleCullingDistance; }

	/**
	*  entity weight alpha value�� setting �Ѵ�.
	*/
	virtual void SetWeightAlpha(RwReal fWeightValue);

	/** 
	*  entity ���� weight alpha
	*  \return weight alpha
	*/
	RwReal GetWeightAlpha(void) const;

	/**
	*  atomic weight alpha value�� setting �Ѵ�.
	*/
	virtual void SetAtomicWeightAlpha(const RwChar *pAtomicName, RwReal fWeightValue) {}

	/** 
	*  entity ���� weight alpha
	*  \return weight alpha
	*/
	CNtlPLEntityBlendController* GetAlphaBlendController(void);

	/**
	*  weight elapsed time value�� setting �Ѵ�.
	*/
	void SetWeightElapsedTime(RwReal fWeightValue);

	/** 
	*  entity ���� weight elapsed time
	*  \return weight elapsed time
	*/
	RwReal GetWeightElapsedTime(void) const;

	/** 
	*  entity ���� weight elapsed controller ����.
	*/
	virtual void CreateWeightElapsedController(RwReal fLifeTime, RwReal fWeightValue); 

	/** 
	*  entity ���� weight elapsed controller �Ҹ�.
	*/
	virtual void DeleteWeightElapsedController(void);

	/** 
	*  entity rendering on/off ��Ű�� �Լ�.
	*  \param rendering on/off flag ����.
	*/
	virtual void	SetVisible(RwBool bVisible);	
	/** 
	*  entity  ���� rendering�� �ǰ� �ִ� entity �ΰ�?
	*  \param  �Բ� ����� CullFlags.
	*  \return rendering on�̸� TRUE, rendering off�̸� FALSE
	*/
	virtual RwBool	IsVisible(RwUInt32 uiFlags = 0xFFFFFFFF);

	/** 
	*  entity camera collision�� ���� �����ϴ� Visible �˻� �Լ���
	*  Performance ����� ���� Culling�� ������� ���� �Լ�
	*  \return rendering ���̸� TRUE, �׷��� ������ FALSE
	*/
	//virtual RwBool	IsVisibleForCameraCollision(void);

	/** 
	*  entity cullflags setting ��Ű�� �Լ�.
	*  \param cullflags check bit ����.
	*  \param cullflasgs on/off ����.
	*/
	virtual void	SetCullFlags(RwUInt32 uiFlag, RwBool bCulled);
	virtual void	SetCullFlags(RwUInt32 uiFlag);

	virtual RwUInt32 GetCullFlags();

	/** 
	*  entity picking on/off ��Ű�� �Լ�.
	*  \param picking on/off flag ����.
	*/
	virtual void SetPicking(RwBool bPicking);

	/** 
	*  entity picking order ���� �Լ�.
	*  \param picking order ����.
	*/
	virtual RwUInt16 GetPickingOrder(void);

	virtual void SetPickingOrder(RwUInt16 byPickOrder);

	/** 
	*  entity weight elapsed time flag on/off ��Ű�� �Լ�.
	*/
	virtual void EnableWeightElapsedTime(RwBool bEnable);
  
	/**
	*  entity name setting
	*  \see GetName
	*/
	void SetName(const RwChar *pName);

	/**
	*  entity name�� ������ �Լ�.
	*  \return entity name�� �����Ѵ�.
	*  \see SetName
	*/
	const RwChar* GetName(void); 

	/**
	*  entity class id setting.
	*  RTTI ��ü�����ν� class id�� ���������ν� entity ������ �Ǻ��Ѵ�.
	*  \see GetClassID
	*/
	void SetClassType(const ENtlPLEntityType eType);

	/**
	*  entity class id�� ������ �Լ�.
	*  \return class id�� �����Ѵ�.
	*  \see SetClassID
	*/
	ENtlPLEntityType GetClassType(void) const;

	/**
	*  entity layer�� setting
	*  entity layer�� ����Ͽ�, rendering ������ ������ �� �ִ�.
	*  entity layer�� NtlPLEntity.h�� enum���� ���ǵǾ� �ְ�, �ʿ信 ���� �߰��� �� �ִ�.
	*  \see GetLayer
	*/
	void SetLayer(RwUInt32 wLayer);

	/**
	*  entity layer�� ��� ���� �Լ�.
	*  \return entity�� layer value.
	*  \see SetLayer
	*/
	RwUInt32 GetLayer(void) const;

	/**
	*  entity flag�� setting �Ѵ�.
	*  \see GetFlags
	*/
	virtual void SetFlags(RwUInt32 uiFlags);

	/**
	*  entity flag�� ���´�.
	*  \see SetFlags
	*/
	RwUInt32 GetFlags(void);

	/**
	*  entity minimap layer�� setting
	*  entity minimap layer�� ����Ͽ�, ���� minimap layer ��¿��� ���ȴ�.
	*  entity minimap layer�� NtlPLEntity.h�� enum���� ���ǵǾ� �ְ�, �ʿ信 ���� �߰��� �� �ִ�.
	*  \see GetMinimapLayer
	*/
	void SetMinimapLayer(RwUInt32 uiLayerFlags);

	/**
	*  entity layer�� ��� ���� �Լ�.
	*  \return entity�� minimap layer flags value.
	*  \see SetMinimapLayer
	*/
	RwUInt32 GetMinimapLayer(void) const;

	/**
	*  simulation object serial id�� setting �Ѵ�.
	*  \see GetSerialID
	*/
	void SetSerialID(RwUInt32 uiSerialID);

	/**
	*  simulation object serial id�� ���´�.
	*  \see SetSerialID
	*/
	RwUInt32 GetSerialID(void);

	VOID		SetSID(RwUInt32 _uiSID);
	RwUInt32	GetSID(VOID);
	VOID		SetObjNameIdx(DWORD _Idx);
	DWORD		GetObjNameIdx();

#ifndef dNTL_WORLD_CULLING_NEW
	void		SetCullingID(RwUInt32 uiCullID);
	RwUInt32	GetCullingID(void);
#endif

	/**
	*  entity�� layer �� class id�� layer�� ��ȿ�� �����͸� ������ �ִ����� �Ǻ��Ͽ�, entity�� ��Ȯ�� ������ ���
	*  �ִ����� �˻��ϴ� �Լ�.
	*  \return class id �� layer�� ��ȿ�� ������ ��� ������ true, �׷��� ������ false
	*/
	RwBool IsValid(void) const;

	/**
	*  update time�� �ڵ����� �����Ǵ� entity�ΰ�..
	*/
	virtual RwBool IsAutoDelete(void);


//-------------------------------------------------------------------------------
// event function
//-------------------------------------------------------------------------------

	// ��ż�ȯ�� ����Ǵ� �Լ�
	virtual void OnDragonSkyAppearence(RwBool _FlgDragonAppeared) {}

	/**
	*  entity �� click �Ǿ��� �� �߻��Ѵ�.
	*/
	virtual void	OnClicked(void) {}

	/**
	*  entity �� double click �Ǿ��� �� �߻��Ѵ�.
	*/
	virtual void	OnDbClicked(void) {}

	/**
	*  entity�� mouse focus�� ���� �� �߻��Ѵ�.
	*/
	virtual void	OnGotFocus(void) {}

	/**
	*  entity�� mouse focus�� �Ҿ������ �� ȣ���Ѵ�.
	*/
	virtual void	OnLostFocus(void) {}

//-------------------------------------------------------------------------------
// World Editor�� ���� Ʈ���� ������ �������� �������̽� (by agebreak 2006-11-28)
//-------------------------------------------------------------------------------
    virtual RwBBox  GetTriggerAABBInfo() {RwBBox bbbox; ZeroMemory(&bbbox, sizeof(RwBBox)); return bbbox;}                                  ///< ���忡������ Ʈ���� ������ ����ϱ� ���� AABB�� ������ ��ȯ�Ѵ�.
    virtual RwBBox  GetTriggerAABBInfo(const RwV3d& vPos, const RwV3d& vRotate, const RwV3d& vScale) {RwBBox bbbox; ZeroMemory(&bbbox, sizeof(RwBBox)); return bbbox;}

};

inline VOID	CNtlPLEntity::SetObjNameIdx(DWORD _Idx)
{
	m_ObjNameIdx = _Idx;
}

inline DWORD CNtlPLEntity::GetObjNameIdx()
{
	return m_ObjNameIdx;
}

#ifndef dNTL_WORLD_CULLING_NEW
inline void CNtlPLEntity::SetCullingID(RwUInt32 uiCullID)
{
	m_uiCullIID = uiCullID;
}

inline RwUInt32 CNtlPLEntity::GetCullingID(void)
{
	return m_uiCullIID;
}
#endif

inline void CNtlPLEntity::SetVisible(RwBool bVisible)
{
	if(bVisible)
		m_uiFlags = m_uiFlags & (~NTL_PLEFLAG_NOT_VISIBLE);
	else
		m_uiFlags = m_uiFlags | NTL_PLEFLAG_NOT_VISIBLE;
}

inline void CNtlPLEntity::SetCullFlags(RwUInt32 uiFlag, RwBool bCulled)
{
	if(bCulled)
		m_uiCullFlags = m_uiCullFlags | uiFlag;
	else
		m_uiCullFlags = m_uiCullFlags & (~uiFlag);
}

inline void CNtlPLEntity::SetCullFlags(RwUInt32 uiFlag)
{
	m_uiCullFlags = uiFlag;
}

inline RwUInt32 CNtlPLEntity::GetCullFlags()
{
	return m_uiCullFlags;
}

inline RwBool CNtlPLEntity::IsVisible(RwUInt32 uiFlags)
{
	// USER VISIBLE CHECK
	if ((m_uiFlags & NTL_PLEFLAG_NOT_VISIBLE))
	{
		return FALSE;
	}

    if(CNtlPLGlobal::m_bEntityNotCulling)
	{
        return TRUE;
	}

#ifdef dNTL_WORLD_CULLING_NEW
	// If m_uiRenderFrame is equal to the initial value (-1), it is an entity that does not perform CullingTest.
	if (uiFlags)
	{
		uiFlags &= m_uiCullFlags;
		// PVS Flags are owned by every Entitiy. PVS Flags exist even if CullingTest is not performed.
		if (((uiFlags & NTL_PLEFLAG_CULLED_PVS) && CNtlPLGlobal::m_UseTerrainPVSMode))
		{
			return FALSE;
		}		
		// Except for PVS, the Flag should have the same RenderFrame but is up-to-date and not different.
		// However, if the RenderFrame is -1 and the FrameTest is not used, the Flag information has no value.
		if (m_uiRenderFrame == static_cast<RwUInt16>(-1))
		{
			return TRUE;
		}
		
		if ((CNtlPLGlobal::m_uiRenderFrame != m_uiRenderFrame) ||
			(uiFlags & (NTL_PLEFLAG_CULLED_CAMERA_FRUSTUM_OUT | NTL_PLEFLAG_CULLED_OCCLUDER)))
		{
			return FALSE;
		}
	}
	return TRUE;
#endif

#ifndef dNTL_WORLD_CULLING_NEW
	// CULL VISIBLE CHECK
	if (uiFlags)
	{
		uiFlags &= m_uiCullFlags;
		if (((uiFlags & NTL_PLEFLAG_CULLED_PVS) && CNtlPLGlobal::m_UseTerrainPVSMode) ||
			(uiFlags & NTL_PLEFLAG_CULLED_CAMERA_FRUSTUM_OUT) ||
			(uiFlags & NTL_PLEFLAG_CULLED_OCCLUDER))
		{
			return FALSE;
		}
	}

	return TRUE;
#endif
}

/*inline RwBool CNtlPLEntity::IsVisibleForCameraCollision(void)
{
	if ( m_uiFlags & NTL_PLEFLAG_NOT_VISIBLE )
	{
		return FALSE;
	}
	return TRUE;
}*/

inline void CNtlPLEntity::SetPicking(RwBool bPicking)
{
	if(bPicking)
		m_uiFlags = m_uiFlags | NTL_PLEFLAG_PICKING;
	else
		m_uiFlags = m_uiFlags & (~NTL_PLEFLAG_PICKING);
}

inline RwUInt16 CNtlPLEntity::GetPickingOrder(void)
{
	return m_byPickOrder;
}

inline void CNtlPLEntity::SetPickingOrder(RwUInt16 byPickOrder)
{
	m_byPickOrder = byPickOrder;
}

inline void CNtlPLEntity::EnableWeightElapsedTime(RwBool bEnable)
{
	if(bEnable)
		m_uiFlags = m_uiFlags | NTL_PLEFLAG_WEIGHT_ELAPSED_TIME;
	else
		m_uiFlags = m_uiFlags & (~NTL_PLEFLAG_WEIGHT_ELAPSED_TIME);
}


inline void CNtlPLEntity::SetName(const RwChar *pName)
{
	if(pName)
	{
		m_strName = pName;
	}
}

inline const RwChar* CNtlPLEntity::GetName(void)
{
	return m_strName.c_str();
}


inline void CNtlPLEntity::SetClassType(const ENtlPLEntityType eType)
{
	m_uiClassID = eType;
}

inline ENtlPLEntityType CNtlPLEntity::GetClassType(void) const
{
	return (ENtlPLEntityType)m_uiClassID;
}

inline void CNtlPLEntity::SetLayer(RwUInt32 uiLayer)
{
	m_uiLayer = uiLayer;
}

inline RwUInt32 CNtlPLEntity::GetLayer(void) const
{
	return m_uiLayer;
}

inline void CNtlPLEntity::SetMinimapLayer(RwUInt32 uiLayerFlags)
{
	m_uiMinimapLayer = uiLayerFlags;
}

inline RwUInt32 CNtlPLEntity::GetMinimapLayer(void) const
{
	return m_uiMinimapLayer;
}


inline void CNtlPLEntity::SetFlags(RwUInt32 uiFlags)
{
	m_uiFlags = uiFlags;
}

inline RwUInt32 CNtlPLEntity::GetFlags(void)
{
	return m_uiFlags;
}

inline void CNtlPLEntity::SetSerialID(RwUInt32 uiSerialID)
{
	m_uiSerialID = uiSerialID;
}

inline RwUInt32 CNtlPLEntity::GetSerialID(void)
{
	return m_uiSerialID;
}

inline void CNtlPLEntity::SetSID(RwUInt32 _uiSID)
{
	m_uiSID = _uiSID;
}

inline RwUInt32 CNtlPLEntity::GetSID(void)
{
	return m_uiSID;
}


inline RwReal CNtlPLEntity::GetWeightAlpha(void) const
{
	return m_fWeightAlpha;
}


inline void CNtlPLEntity::SetWeightElapsedTime(RwReal fWeightValue)
{
	m_fWeightElapsedTime = fWeightValue;
}


inline RwReal CNtlPLEntity::GetWeightElapsedTime(void) const
{
	return m_fWeightElapsedTime;
}

inline RwBool CNtlPLEntity::IsValid(void) const
{
	return (m_uiLayer == PLENTITY_LAYER_INVALID || m_uiClassID == PLENTITY_INVALID_TYPE)  ? FALSE : TRUE;
}


inline RwBool CNtlPLEntity::IsAutoDelete(void)
{
	return FALSE;
}

#endif
