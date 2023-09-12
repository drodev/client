/******************************************************************************
* File			: SurfaceCamera.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 1. 21
* Abstract		: 
*****************************************************************************
* Desc			: SurfaceGui�� Render texture camera
*****************************************************************************/
#pragma once

#include "SurfaceGui.h"

class CSurfaceCamera
{
public:
	CSurfaceCamera();
	CSurfaceCamera(const CSurfaceCamera& camera) {}
	virtual ~CSurfaceCamera();

	VOID			Create(RwInt32 iWidth, RwInt32 iHeight);
	VOID			Destroy();

	RwBool			CameraBeginUpdate();			///< t : ī�޶� �ؽ�ó�� �������� �غ� �Ǿ���
	VOID			CameraEndUpdate();

	VOID			CreateTexture();				///< gui::CTexture�� �����Ѵ�
	gui::CTexture*	GetTexture();

protected:
	RwCamera*				m_pCamera;				///< Raster camera
	RwTexture*				m_pRenderTexture;		///< Render target texture

	gui::CTexture			m_GUITexture;			///< Dbo Texture
};