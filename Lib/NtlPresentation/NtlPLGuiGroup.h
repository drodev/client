/*****************************************************************************
 * File			: NtlPLGuiGroup.h
 * Author		: Hong Sungbock
 * Copyright	: (��)NTL
 * Date			: 2007. 12. 13
 * Abstract		: PL���� Gui group�� �����Ѵ�
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#pragma once

class CNtlPLSceneChangerGui;
class CNtlPLProfilerGui;


class CNtlPLGuiGroup
{
public:
	CNtlPLGuiGroup();
	~CNtlPLGuiGroup();

	RwBool	Create(void);
	void	Destroy(void);

protected:
	CNtlPLSceneChangerGui*		m_pSceneChanger;
	CNtlPLProfilerGui*			m_pProfilerGui;
};
