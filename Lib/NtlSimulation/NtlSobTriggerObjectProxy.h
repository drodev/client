/*****************************************************************************
*
* File			: CNtlSobTriggerObjectProxy
* Author		: Peessi
* Copyright		: (��)NTL
* Date			: 2006. 10. 23	
* Abstract		: Simulation trigger object Proxy
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_SOB_TRIGGEROBJECT_PROXY_H__
#define __NTL_SOB_TRIGGEROBJECT_PROXY_H__

#include "NtlSLDef.h"
#include "NtlSobProxy.h"

class CNtlPLPlayerName;
class CNtlPLDecal;
class CNtlPLObject;
class CNtlShareTargetMark;

class CNtlSobTriggerObjectProxy : public CNtlSobProxy
{
	DECLEAR_MEMORY_POOL( CNtlSobTriggerObjectProxy, NTL_DEFAULT_MEMORY_POOL )

public:
	typedef std::list<RwInt32> ANIMATION_CHAIN;

	struct SFADE_IN_OUT_INFO
	{
		RwReal				fCurAlpha;
		RwReal				fDestAlpha;
		RwBool				bShow;
	};

	#define TLQ_STAND_TIME	(2.f)
	#define PID_STAND_TIME	(2.f)

private:

	CNtlPLObject			*m_pPLObject;					/** trigger object */
	CNtlPLPlayerName		*m_pObjName;					/** presentation trigger object name entity */
	CNtlPLEntity			*m_pTargetMark;					/** trigger object target mark */
	CNtlPLEntity			*m_pQuestMark;					/**	trigger object quest mark */
	CNtlPLEntity			*m_pDojoSealEff;				/**	Dojo seal effect */
    CNtlShareTargetMark     *m_pShareTargetMark;            ///< ���� Ÿ�� ��ũ

	RwReal					m_fObjectWidth;					/** trigger object width */
	RwReal					m_fObjectHeight;				/** trigger object height */
	RwReal					m_fObjectDepth;					/** trigger object depth */

	RwUInt8					m_byMainState;
	RwUInt8					m_bySubState;
	ANIMATION_CHAIN			m_AnimChain;
	RwBool					m_bPlay;
	RwReal					m_fPlayTime;

	const RwReal			FADE_RATIO;
	SFADE_IN_OUT_INFO		m_sFadeInOutInfo;

	RwReal					m_fTLQTime;
	RwReal					m_fPIDTime;

protected:

	/** 
	* trigger object �̸� ����.
	*/
	void CreatePLObjectName(void);
	void DeletePLObjectName(void);

	/** 
	* trigger object target mark
	*/ 
	void CreatePLTargetMark(void);
	void DeletePLTargetMark(void);

	/** 
	* trigger object quest mark
	*/ 
	void CreatePLQuestMark(const RwChar *pKey);
	void DeletePLQuestMark(void);

	/** 
	* Dojo seal effect
	*/ 
	void CreateDojoSealEffect(RwUInt8 uiMainState);
	void DeleteDojoSealEffect(void);

    /// ���� Ÿ�� ��ũ
    void CreateShareTargetMark(RwUInt8 bySlot, RwInt32 type);
    void DeleteShareTargetMark();
	
public:

	CNtlSobTriggerObjectProxy(VOID);
	virtual ~CNtlSobTriggerObjectProxy(VOID);

	virtual RwBool Create(RwUInt32 uiCompType);
	virtual void Destroy(VOID);
	virtual void Update(RwReal fElapsed);
	virtual void HandleEvents( RWS::CMsg& msg );

//-------------------------------------------------------------------------------
// event handler
//-------------------------------------------------------------------------------

public:

	void SobCreateEventHandler(RWS::CMsg &pMsg);
	void SobTargetSelectEventHandler(RWS::CMsg &pMsg);
	void SobAttackSelectEventHandler(RWS::CMsg &pMsg);
	void SobTargetSelectReleaseEventHandler(RWS::CMsg &pMsg);
    void SobShareTargetSelectHandler(RWS::CMsg& msg);
    void SobShareTargetReleaseHandler(RWS::CMsg& msg);
	void SobQuestMark(RWS::CMsg &pMsg);
	void SobUpdateState(RWS::CMsg &pMsg);
	void SobAnimEnd(RWS::CMsg &pMsg);

public:

	//---------------------------------------------------
	// main presentation entity�� ���õ� �Լ� 
	//---------------------------------------------------

	/**
	* transform�� ������ �Լ�.
	*/

	virtual void	SetPosition(const RwV3d *pPos);
	virtual void	SetDirection(const RwV3d *pDir);
	virtual RwV3d	GetDirection(void);
	virtual void	SetAngleY(RwReal fAngle);

	// 
	virtual void EnableVisible(RwBool bEnable);

	/**
	* entity ������ ���� �Լ�.
	*/

	// presentation main entity
	CNtlPLEntity*			GetPLMainEntity(void);

	// pl entity�� ���� ���´�.
	virtual RwReal			GetPLEntityWidth(void); 

	// pl entity�� ���̸� ���´�.
	virtual RwReal			GetPLEntityHeight(void);

	// pl entity�� depth�� ���´�.
	virtual RwReal			GetPLEntityDepth(void); 

    // material�� ������ �Լ�.
    virtual void			SetAlpha(RwUInt8 byAlpha);

	/**
	* Decoration�� ���õ� �Լ�
	*/

	// Entity ����� �̸��� �������� ����
	void					EnableNameVisible(RwBool bVisible);

	// Entity ����� �̸� ������ �����Ѵ�
	virtual void			SetNameColor(const WCHAR* pwcName, COLORREF color);

protected:
	RwBool					IsScouterObject(void);
	RwBool					IsTLQObject(void);
	RwBool					IsPIDObject(void);
	RwBool					IsDojoSealObject(void);

	void					InitState(RwUInt8 byMainState, RwUInt8 bySubState);
	void					UpdateState(RwUInt8 byMainState, RwUInt8 bySubState, RwUInt32 uiStateTime);

	void					UpdateTLQObject(RwReal fElapsed);

	void					UpdatePIDObject(RwReal fElapsed);

	void					PlayAnimation(RwReal fPlayTime);

	void					Fade(RwBool bFadeIn);
	void					UpdateFadeInOut(RwReal fElapsed);
};

inline CNtlPLEntity* CNtlSobTriggerObjectProxy::GetPLMainEntity(VOID) 
{
	return reinterpret_cast<CNtlPLEntity*>( m_pPLObject );
}


#endif