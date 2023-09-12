/*****************************************************************************
 *
 * File			: NtlSobProxy.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2006. 4. 26	
 * Abstract		: Simulation object proxy base class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_SOB_PROXY_H__
#define __NTL_SOB_PROXY_H__

#include "ceventhandler.h"
#include "NtlMath.h"
#include "NtlSobProxyDef.h" 


class CNtlSobProxy : public RWS::CEventHandler
{
public:

	typedef std::list<CNtlPLEntity*>						ListPLEntity;
	typedef std::list<CNtlSobProxySystemEffect*>		    ListProxySystemEffect;	

protected:

	RwUInt32						m_uiSystemFlags;
	RwUInt32						m_uiCompType;
	CNtlSob							*m_pSobObj;
	ListPLEntity					m_listPLChild;
	
	RwUInt8							m_byAlpha;
	CNtlSobProxySystemEffectColor	*m_pWorldLight;
	ListProxySystemEffect			m_listProxySystemEffect;	
    
    RwBool                          m_bEnableCameraAlpha;
    CNtlSobProxySystemEffect*       m_pCameraAlphaEffect;

	bool							m_bDisableAniChange;

protected:

	void							ResetRemoveSystemEffectAlpha(void);

	void							UpdateSystemEffectColor(RwReal fElapsed);
	void							UpdateSystemEffectAlpha(RwReal fElapsed);	
    void							UpdateSystemEffectScale(RwReal fElapsed);

public:

	CNtlSobProxy();
	virtual ~CNtlSobProxy();

	virtual RwBool	Create(RwUInt32 uiCompType);
	virtual void	Destroy(void);
	virtual void	Update(RwReal fElapsed);
	virtual void	HandleEvents(RWS::CMsg &pMsg) {}

	
	
public:

	void			SetDisableAniChange(bool bFlag) { m_bDisableAniChange = bFlag; }
	bool			GetDisableAniChange() { return m_bDisableAniChange; }

	//---------------------------------------------------
	// proxy system flag ������ ���� �Լ�.
	//---------------------------------------------------

	virtual	void	EnableProxySystemVisible(RwBool bVisible);
	RwBool			IsProxySystemVisible(void);

	virtual void	EnableProxySystemGUILPVisible(RwBool bVisible);
	RwBool			IsProxySystemGUILPVisible(void);

	//---------------------------------------------------
	// owner simulation object  ������ ���� �Լ�.
	//---------------------------------------------------

	void			SetSobObj(CNtlSob *pSobObj);
	void			SetCompType(RwUInt32 uiCompType);
	RwUInt32		GetCompType(void) const;

	virtual void	NotifyStateEnter(RwUInt32 uiStateId)	{}
	virtual void	NotifyStateExit(RwUInt32 uiOldState, RwUInt32 uiNewState)		{}

	//---------------------------------------------------
	// presentation entity ���� �Լ�.                                                                      
	//---------------------------------------------------

	// attach ��Ű�� �ʰ� effect ����.
	CNtlPLEntity*			CreatePLEffect(const RwChar *pKey, const RwV3d *pPos = NULL, RwBool bIgnoreVisible = FALSE );

	// attach ��Ű�� �ʰ� effect ����
	// child list�� �߰��Ѵ�.
	CNtlPLEntity*			CreatePLChildEffect(const RwChar *pKey, RwBool bIgnoreVisible = FALSE);
	
	// bone attach��Ű�鼭 effect ����.
    virtual CNtlPLEntity*	CreatePLChildEffect(const RwChar *pKey, const RwChar *pAttachBoneName, RwV3d vOffset = ZeroAxis, RwBool bIgnoreVisible = FALSE) {return NULL;}

	// offset position�� attach��Ű�鼭 effect ����.
	virtual CNtlPLEntity*	CreatePLChildEffect(const RwChar *pKey, RwV3d vOffset, RwBool bIgnoreVisible = FALSE, RwBool bApplyRotate = FALSE)  { return NULL; }

	// offset position�� attach��Ű�鼭 effect ����.
	CNtlPLEntity*			CreatePLDamageBox(RwV3d vPos, RwUInt32 uiDamage, RwBool bHealing = FALSE);

	// child�� ������ effect�� �����Ѵ�.
	virtual void			DeletePLChildEffect(CNtlPLEntity *pPLEntity);

	//---------------------------------------------------
	// main presentation entity�� ���õ� �Լ� 
	//---------------------------------------------------

	/**
	* Functions related to add and remove in world.
	*/

	virtual void			AddWorld(void)		{}
	virtual void			RemoveWorld(void)	{}

	/**
	* transform�� ������ �Լ�.
	*/

	virtual void			SetPosition(const RwV3d *pPos)	{}
	virtual RwV3d			GetPosition(void);

	virtual void			SetDirection(const RwV3d *pDir) {}
	virtual RwV3d			GetDirection(void);

	virtual void			SetAngleY(RwReal fAngle)		{}
	virtual void			SetDeltaAngleY(RwReal fAngle)	{}
	virtual void			SetAngleX(RwReal fAngle) {}
	virtual void			SetDeltaAngleX(RwReal fAngle) {}

	virtual void			SetScale(RwReal fScale)			{}

	/**
	* material�� ������ �Լ�.
	*/

	virtual void			SetAlpha(RwUInt8 byAlpha);
	
	RwUInt8					GetAlpha(void);

	void					AddAlpha(RwUInt8 byAddValue);

	virtual void			SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue) {} 

	void					EnableWorldLight(RwBool bEnable, RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);

	virtual	void			SetInkThicknessWeight(RwReal fWeightValue = 1.0f) {}

	virtual void			SetInkThickness(RwReal fValue = NTL_INK_THICKNESS) {}

	virtual void			SetInkColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue) {}
	
	/**
	* animation�� ���õ� �Լ�.
	*/
	
	// animation setting
	virtual void			SetBaseAnimation(RwUInt32 uiAnimKey, RwBool bLoop = TRUE, RwReal fStartTime = 0.0f) {}

	virtual RwBool			IsExistBaseAnimation(RwUInt32 uiAnimKey) { return FALSE; }

	// ���� play �ϴ� animation key�� ���´�.
	virtual RwUInt32		GetBaseAnimationKey(void)		{ return 0; }

	virtual RwBool			IsBaseAnimationEnd(void)		{ return TRUE; }

	virtual void			SetAnimSpeed(RwReal fAniSpeed)	{}
    virtual RwReal          GetAnimSpeed()					{return 1.0f;}

	virtual void			SetAnimBlendNoneOneTime(void)	{}

	/**
	* Decoration�� ���õ� �Լ�
	*/

	// Entity ����� �̸� ������ �����Ѵ�
	virtual void			SetNameColor(const WCHAR* pwcName, COLORREF color) {}

	virtual void			SetNickNameColor(const WCHAR* pwcNickName, COLORREF nickNameColor) {}

	virtual void			SetEmblemFactor(RwUInt8 byTypeA, RwUInt8 byTypeAColor,	
											RwUInt8 byTypeB, RwUInt8 byTypeBColor, 
											RwUInt8 byTypeC, RwUInt8 byTypeCColor) {}

	virtual void			SetDecorationProxyAlpha(RwUInt8 byAlpha) {}
	virtual void			EnableDecorationProxyVisible(RwBool bShow) {}

	/**
	* entity ������ ���� �Լ�.
	*/

	// main entity�� ������ �Լ�.
	virtual CNtlPLEntity*	GetPLMainEntity(void) { return NULL; }

	// bone position�� ���´�.
	virtual RwV3d			GetBonePosition(const RwChar *pBoneName);

	// ������ ������ bone position
	virtual RwV3d			GetWeaponBonePosition(const RwChar *pBoneName);

	// ������ sub weapon�� bone position
	virtual RwV3d			GetSubWeaponBonePosition(const RwChar *pBoneName);

	// pl entity�� ���� ���´�.
	virtual RwReal			GetPLEntityWidth(void); 

	// pl entity�� ���̸� ���´�.
	virtual RwReal			GetPLEntityHeight(void);

	// pl entity�� depth�� ���´�.
	virtual RwReal			GetPLEntityDepth(void); 

	// pl entity�� base scale�� ���´�.
	virtual RwReal			GetPLEntityBaseScale(void);

    // ���Ƿ� ������ Scale�� ���´�.
    virtual RwReal          GetScale();

	/**
	* child presentation entity�� ���õ� �Լ�  
	*/

	// child entity �߰�.
	void					AddPLChildEntity(CNtlPLEntity *pPLEntity);

	// child entity ���� ������.
	RwInt32					GetPLChildEntityCount(void) const;

	// child entity transform.
	void					TransformPLChildEntity(RwMatrix& mat);

	/** 
	* dynamic effect control.
	*/
	CNtlSobProxySystemEffect*	AddVisualSystemEffectAlphaBlend(RwReal fWeightAlpha, RwReal fLifeTime, RwBool bLoop, RwBool bExceptDecorationProxy = FALSE);	
	CNtlSobProxySystemEffect*	AddVisualSystemEffectAlphaBlend(RwReal fStartWeightAlpha, RwReal fEndWeightAlpha, RwReal fBlendTime, RwReal fLifeTime, RwBool bLoop, RwBool bExceptDecorationProxy = FALSE);	
	void						RemoveVisualSystemEffectAlpha(CNtlSobProxySystemEffect *pSystemEffect);	

    CNtlSobProxySystemEffect*   AddVisualSystemEffectColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue, RwBool bAddColor = FALSE);
    void                        RemoveVisualSystemEffectColor(CNtlSobProxySystemEffect* pSystemEffect);

	CNtlSobProxySystemEffect*	AddVisualSystemEffectColorFlickering(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue, RwReal fFlickerTime);
	void						RemoveVisualSystemEffectColorFlickering(CNtlSobProxySystemEffect *pSystemEffect);	

    CNtlSobProxySystemEffect*   AddVisualSystemEffectScale(RwReal fEndScale, RwReal fTime);    

    RwBool                      IsExitSystemEffect(CNtlSobProxySystemEffect* pSystemEffect);
	
    //////////////////////////////////////////////////////////////////////////
	virtual void EnableVisible(RwBool bEnable);
	virtual void EnablePicking(RwBool bEnable) {}
	virtual void EnableShadowRendering(RwBool bEnable) {}
	virtual void EnableHighlight(RwBool bEnable) {}	
	virtual void CreateElapsedController(RwReal fCtrlTime, RwReal fWeightValue);
	virtual void DeleteElapsedController(void);
    virtual void EnableCameraAlpha(RwBool bEnable);             ///< ī�޶� �Ÿ��� ���� ���ĸ� �����Ѵ�.

//------------------------------------------------------------------------------------------------------------
// event�� ���õ� �Լ�.  
//------------------------------------------------------------------------------------------------------------

public:

	
	// mouse focus�� �޾��� ���.
	virtual void SetFocus(void) {}

	// mouse focus�� �о� ������ ���.
	virtual void ReleaseFocus(void) {}

};

inline RwBool CNtlSobProxy::IsProxySystemVisible(void)
{
	if(m_uiSystemFlags & NTL_PROXYSYSTEM_NOT_VISIBLE)
		return FALSE;

	return TRUE;
}

inline RwBool CNtlSobProxy::IsProxySystemGUILPVisible(void)
{
	if(m_uiSystemFlags & NTL_PROXYSYSTEM_LP_VISIBLE)
		return FALSE;

	return TRUE;
}

inline void CNtlSobProxy::SetSobObj(CNtlSob *pSobObj)
{
	m_pSobObj = pSobObj;
}

inline void CNtlSobProxy::SetCompType(RwUInt32 uiCompType)
{
	m_uiCompType = uiCompType;
}

inline RwUInt32 CNtlSobProxy::GetCompType(void) const
{
	return m_uiCompType;
}

inline RwInt32 CNtlSobProxy::GetPLChildEntityCount(void) const
{
	return m_listPLChild.size();
}

// pl entity�� ���� ���´�.
inline RwReal CNtlSobProxy::GetPLEntityWidth(void)
{
	return 1.0f;
}

inline RwReal CNtlSobProxy::GetPLEntityHeight(void)
{
	return 2.0f;
}

// Retrieves the depth of pl entity.
inline RwReal CNtlSobProxy::GetPLEntityDepth(void)
{
	return 1.0f;
}

inline RwReal CNtlSobProxy::GetPLEntityBaseScale(void)
{
	return 1.0f;
}
inline RwReal CNtlSobProxy::GetScale()
{
    return 1.0f;
}


#endif