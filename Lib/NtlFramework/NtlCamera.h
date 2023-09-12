/*****************************************************************************
 *
 * File			: NTLCamera.h
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 14	
 * Abstract		: NTl Camera
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef __NTL_CAMERA__
#define __NTL_CAMERA__

#include "NtlDebug.h"
#include "NtlMath.h"

//#define DEFAULT_ASPECTRATIO (4.0f/3.0f)
//#define DEFAULT_VIEWWINDOW (0.5f)

/**
 * \ingroup Toolkit
 * Renderware Camera Wrappler Class �̴�.
 *
 *
 */
class CNtlCamera
{
protected:

	RwCamera*		m_pCamera;
	RwReal			m_fViewWindow;
	RwReal			m_fFov;
	
protected:

	void SetCalcFov(RwCamera* pCamera, RwReal fFov);

public:

	CNtlCamera(void);
	virtual ~CNtlCamera(void);

	virtual RwCamera* Create( RwInt32 width,
						      RwInt32 height, 
						      RwBool zBuffer, 
						      RwReal fNearClipPlane = 100.f, 
						      RwReal fFarClipPlane = 50000.f);
	
	virtual void SetCameraSize(RwRect* rect);												///< ȭ�� Size�� ������ ��� ȣ��Ǵ� �Լ�(OnResize)															
	
	void SetCameraResize(RwCamera* pCamera, RwRect* rect);									///< ȭ�� Size�� ������ ��� ���� ó���� �ϴ� �Լ�
	
	virtual void Destroy();
	void SetCalcFov(RwReal fFov);			
																							///< Fov ������ �ϴ� �Լ�
	virtual RwCamera*	CameraClear(RwRGBA *rgba, RwInt32 uiClearMode);
	virtual void		CameraShowRaster(HWND hWnd, RwUInt32 uiFlags);

	virtual RwCamera* PostCameraBeginUpdate(RwReal fElapsed);
	virtual void PostCameraEndUpdate(void);

	virtual RwCamera* MainCameraBeginUpdate(RwReal fElapsed);
	virtual void MainCameraEndUpdate(void);

	virtual void UpdatePostEffectFilter(void) {}
	virtual void UpdateHeatHaze(RwReal fElapsedTime) {}										
    virtual void UpdateMotionBlur(RwReal fElapsedTime) {}									///< ��� �� �ؽ��ĸ� �����Ѵ�.
    virtual void SetEnableBlur(RwBool bEnable, RwReal fFadeTime = 0.0f) {}					///< ��� �� ���� ������ �����Ѵ�.
    virtual RwBool GetEnableBlur() {return FALSE;}											///< ��� �� ���� ������ ��ȯ�Ѵ�.

	inline RwCamera* GetCamera()									{ return m_pCamera; }
	inline void SetCamera(RwCamera* pCamera)						{ m_pCamera = pCamera; }

	virtual RwCamera* GetMainCamera()								{ return m_pCamera; }

	
	inline RwReal	GetNearPlane()									{ NTL_ASSERTE(m_pCamera != NULL) return m_pCamera->nearPlane; }				///< Near Plane�� ��´�.
	inline RwReal	GetFarPlane()									{ NTL_ASSERTE(m_pCamera != NULL) return m_pCamera->farPlane; }				///< Far Plane�� ��´�.

	inline void		SetFov(RwReal fFov)								{ m_fFov = fFov; m_fViewWindow = RwTan(NTL_DEG2RAD(fFov * 0.5f)); }		///< Camera�� Fov�� �����Ѵ�.
	inline RwReal	GetFov()										{ return m_fFov; }				

    void     SetProjection(RwCameraProjection rwCameraProjection);  ///< ī�޶��� ���������� �����Ѵ�.
};

RwFrustumTestResult RpNtlCameraFrustumTestSphere(const RwCamera* pCamera, const RwSphere* pSphere, RwReal* pfUserFarDist);
RwFrustumTestResult RpNtlCameraFrustumTestSphere(const RwCamera* pCamera, const RwSphere* pSphere, RwPlane* pfUserFarPlane);
RwFrustumTestResult RpNtlFarPlaneFrustumTestSphere(const RwCamera* pCamera, const RwSphere* pSphere, RwPlane* pfUserFarPlane);

RwCamera*			RpNtlActiveCameraSetFarDistance(RwReal fFarDistance);
RwReal				RpNtlActiveCameraGetFarDistance();

RwBBox				RpNtlCameraFrustumGetStandardBBox(const RwCamera* pCamera, RwInt32 iStandardSize);

#endif