/*****************************************************************************
 *
 * File			: NtlRender.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 14	
 * Abstract		: Main Render.
 *****************************************************************************
 * ���� : 
 *
 *****************************************************************************/

#ifndef __NTL_RENDER__
#define __NTL_RENDER__

#include "ceventhandler.h"
#include "NtlSysEvent.h"

/**
 * \ingroup Client
 * client�� rendering ��ü�� system event�� ������ ��ü�̴�.
 * ��� rendering ��ü�� update �Ѵ�.
 *
 */

class CNtlRender
{
private:
    
	bool m_bEnabled;

	float m_fFreeElapsed;		/**< free sync tick*/

public:

	CNtlRender();

	// CNtlRender ��ü�� ������ ���� ��ٷ� ȣ��ȴ�.
    bool Create(void);

	// CNtlRender ��ü�� �����Ǳ� ���� �ٷ� ȣ��ȴ�.
	void Destroy(void);

	/**
	* \ingroup Client
	* client�� rendering ��ü�� tick event�� ������.
	*
	*/
	void Update(float fElapsed);

	// rendering enable �� disable
	void SetEnabled(bool bEnabled); 
};


inline void CNtlRender::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}


#endif
