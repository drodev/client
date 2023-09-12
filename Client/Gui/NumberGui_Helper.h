/******************************************************************************
* File			: NumberGui_Helper.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 11. 21
* Abstract		: 
*****************************************************************************
* Desc			: CNumberGui�� �������� ������ ����� ��Ƶд�
*****************************************************************************/

#pragma once

class CNumberGui;

// core
#include "NtlCallbackWidget.h"


//////////////////////////////////////////////////////////////////////////
//	�Էµ� CNumberGui�� ���ʵǷ� ũ�Ⱑ ���Ѵ�
//  1. AddNumberGui() �Լ��� ������ CNumberGui��ŭ ȣ��
//  2. Play(true) ȣ��
//  3. Update() �Լ��� ���� ȣ���� �ش�
//////////////////////////////////////////////////////////////////////////

class CNumberGui_ZoomHelper
{
public:
	struct sZoomData
	{
		RwBool				bFinish;
		RwReal				fStartRate;
		RwReal				fEndRate;
		RwReal				fRemainTime;
		RwReal				fElapsed;
		CNumberGui*			pNumberGui;
	};

	typedef std::list<sZoomData*>				LIST_ZOOM;


	CNumberGui_ZoomHelper();
	virtual ~CNumberGui_ZoomHelper();

	VOID		Update(RwReal fElapsed);
	VOID		Play(RwBool bPlay);
	VOID		Restart();

	// fStartRate ���� fEndRate ���� fRemainTime �ð����� ũ�Ⱑ ����ȴ�
	// Scale ȿ���� �� CNumberGui�� �߰��� ������ ��� false�� ��ȯ�Ѵ�
	RwBool		AddNumberGui(CNumberGui* pNumberGui, RwReal fStartRate, RwReal fEndRate, RwReal fRemainTime);
	VOID		RemoveAll();

	RwBool		IsFinish();
	RwBool		IsPlay();


	template <class Callbackclass>	
	VOID LinkFinishCallback(Callbackclass *cbclass, RwInt32 (Callbackclass::*callback)())
	{	
		if(m_pCallback)
		{
			NTL_DELETE(m_pCallback);
		}

		m_pCallback = NTL_NEW CNtlCallbackWidget0<Callbackclass> (cbclass,callback);
	}

protected:
	sZoomData*				GetCurData();

protected:
	RwBool					m_bFinish;
	RwBool					m_bPlay;
	CNtlCallbackParam0*		m_pCallback;
	LIST_ZOOM				m_listZoom;
	LIST_ZOOM::iterator		m_itCur;
};