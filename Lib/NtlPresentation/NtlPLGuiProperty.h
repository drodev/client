/*****************************************************************************
 *
 * File			: NtlPLGuiProperty.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 22	
 * Abstract		: Presentation layer gui property class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLGUI_PROPERTY_H__
#define __NTL_PLGUI_PROPERTY_H__

#include <string>
#include "NtlPLProperty.h"

/**
 * \ingroup NtlPresentation
 * CNtlPLGui�� �ش��ϴ� property class�̴�.
 * property data�� xml file�� �ۼ��Ǿ��� �ִ�.
 *
 */

class CNtlPLGuiProperty : public CNtlPLProperty
{
public:

	static unsigned int m_strVer;			/* gui property file version **/
	static std::string m_strScriptPath;		/* gui script path name **/ 
	static std::string m_strTexPath;		/* gui texture file�� path name **/ 
	
	std::string m_strResFile;				/* gui resource script file name **/ 
	std::string m_strSurFile;				/* gui surface script file name **/ 
	std::string m_strCompFile;				/* gui component script file name **/ 

public:

	/**
    *  Default constructor for Presentation object property
    *
    */
	CNtlPLGuiProperty();

	/**
    *  destructor for Presentation object property
    *
    */
	virtual ~CNtlPLGuiProperty();

	/**
    *  xml file�κ��� object property data�� loading�ϴ� �Լ�
	*  \param pDoc�� xml wrapping class pointer.
	*  \param pNod�� ��ȿ�� xml node.
    *
    */
	virtual RwBool	Load(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);

	/**
    *  xml file�� object property data�� save�ϴ� �Լ�
	*  \param pDoc�� xml wrapping class pointer.
	*  \param pNod�� ��ȿ�� xml node.
    *
    */
	virtual RwBool	Save(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode );
};


#endif