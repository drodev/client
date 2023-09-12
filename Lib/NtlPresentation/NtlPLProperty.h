/*****************************************************************************
 *
 * File			: NtlPLProperty.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 01	
 * Abstract		: Presentation layer property base class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLPROPERTY_H__
#define __NTL_PLPROPERTY_H__

#define SIZE_PROP_BUF   64

#include "NtlSerializer.h"

class CNtlXMLDoc;

/**
 * \ingroup NtlPresentation
 * entity�� attibute�� ��Ÿ���� base class�̴�.
 * ��� entity���� instance�� ������ �Ŀ� SetProperty interface �Լ��� ���Ͽ� property data�� ���޵ȴ�.
 *
 */
class CNtlPLProperty
{
protected:

	RwUInt32 m_uiId;
	std::string m_strName;				/**< String describing the presentation entity property name */
	std::string m_strClassID;			/**< String describing the presentation entity property class id */
    RwUInt32    m_uiFlag;               ///< �� Entity�� ���� Flag 

public:

	/**
    *  Default constructor for Presentation entity property.
    *
    */
	CNtlPLProperty() {m_uiId = 0xffffffff; m_uiFlag = 0;}

	/**
    *  Virtual destructor for Presentation entity property.
    *
    */
	virtual ~CNtlPLProperty() {}

	/**
	*  prosentation entity property id setting.
	*  \param pName property id.
	*  \see GetId
	*/
	void SetId(const RwUInt32 uiId);

	/**
	*  prosentation entity property name setting.
	*  \return property id�� �����Ѵ�.
	*  \see SetId
	*/
	RwUInt32 GetId(void) const;

	/**
	*  prosentation entity property name setting.
	*  \param pName property name.
	*  \see GetName
	*/
	void SetName(const RwChar *pName);

	/**
	*  prosentation entity property name�� ������ �Լ�.
	*  \return property name string�� �����Ѵ�.
	*  \see SetName
	*/
	const RwChar* GetName(void);

	/**
	*  prosentation entity property class id setting.
	*  \return property name�� �����Ѵ�.
	*  \see GetClassID
	*/
	void SetClassID(const RwChar *pClassID);

	/**
	*  prosentation entity property class id�� ������ �Լ�.
	*  \return property class id string�� �����Ѵ�.
	*  \see SetClassID
	*/
	const RwChar* GetClassID(void);

	///**
	//*  property data load �Լ�.
	//*  \return �����̸�TRUE, �����̸� FALSE
	//*  \param pNode XML doc node
	//*  \see Save
	//*/
	virtual RwBool Load(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode) = 0;

	///**
	//*  property data save �Լ�.
	//*  \return �����̸�TRUE, �����̸� FALSE
	//*  \param pNode XML doc node
	//*  \see Load
	//*/
	virtual RwBool Save(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode) = 0;

	virtual void	SaveSerialize(CNtlSerializer& sOut) {}											///< Serialize�� �����͸� �����ϴ� �Լ�
	virtual void	LoadSerialize(CNtlSerializer& sIn) {}											///< Serialize�κ��� �����͸� �������� �Լ�

    virtual RwUInt32 GetFlag() {return m_uiFlag;}
    virtual void     SetFlag(RwUInt32 uiFlag) {m_uiFlag = uiFlag;}
};

inline void CNtlPLProperty::SetId(const RwUInt32 uiId)
{
	m_uiId = uiId;
}

inline RwUInt32 CNtlPLProperty::GetId(void) const
{
	return m_uiId;
}

inline void CNtlPLProperty::SetName(const RwChar *pName)
{
	m_strName = pName;
}

inline const RwChar* CNtlPLProperty::GetName(void)
{
	return m_strName.c_str(); 
}

inline void CNtlPLProperty::SetClassID(const RwChar *pClassID)
{
	m_strClassID = pClassID;
}

inline const RwChar* CNtlPLProperty::GetClassID(void) 
{
	return m_strClassID.c_str(); 
}


#endif