/******************************************************************************
* File			: NtlPLCameraRT.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 3. 7
* Abstract		: 
*****************************************************************************
* Desc			: Camera render texture ���� ����
*				  1. CameraBeginUpdate()�� true �� Rendering
*				  2. CameraEndUpdate() ȣ��
*				  3. GetTexture() �� �ؽ�ó ��ȯ
* ���� ) CameraBeginUpdate()�� �Ź� ���ο� Framde buffer�� �Ҵ��Ѵ�. ����
*		 CameraBeginUpdate()�� �ؽ�ó�� �����ϰ� �ݵ�� GetTexture()�� �ؽ�ó��
*		 ���ͼ� �ؽ�ó�� ���־�� �Ѵ�.
*****************************************************************************/
#pragma once

class CNtlPLCameraRT
{
public:
	CNtlPLCameraRT();
	CNtlPLCameraRT(const CNtlPLCameraRT& camera) {}
	virtual ~CNtlPLCameraRT();

	VOID			Create(RwInt32 iWidth, RwInt32 iHeigth);
	VOID			Destroy();

	RwBool			CameraBeginUpdate();			///< t : ī�޶� �ؽ�ó�� �������� �غ� �Ǿ���
	VOID			CameraEndUpdate();

	RwTexture*		GetTexture();

protected:
	RwCamera*				m_pCamera;				///< Raster camera
	RwTexture*				m_pRenderTexture;		///< Render target texture

	RwInt32					m_iWidth, m_iHeigth;
};