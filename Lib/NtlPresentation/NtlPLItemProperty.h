#ifndef __NTL_ITEM_PROPERTY_H__
#define __NTL_ITEM_PROPERTY_H__

#include "NtlPLProperty.h"
#include "NtlAnimEventData.h"
#include "NtlPLItemData.h"
#include "NtlTypeAnimData.h"

// Item Flag��
#define ITEM_FLAG_APPLY_EMBLEM        0x00000001

class CNtlPLItemProperty : public CNtlPLProperty
{
public:
	static unsigned int m_strVer;				///< Property File Version
	static std::string m_strItemDataPath;		///< Item Data File Path

    std::vector<SEventLinkEffect*> m_vLinkEffect;     ///< Link Effect�� ����Ʈ     
    SEventTrace        m_eventTrace;            //< Trajectory Effect Properties

protected:
	std::string			m_TypeMeshPath;			///< Item Mesh File Path
	std::string			m_TypeMeshFileName;		///< Item Mesh File Name(*.dff)

	EItemResType		m_TypeResType;			///< ResType
	EItemEquipSlotType	m_TypeEquipSlotType;	///< Equip Slot Type

    CNtlTypeAnimTable   m_TypeAnimTable;        ///< Animation Table
    RwV3d               m_v3dAttachOffset;      ///< Item Attach Offset

    RwBool              m_bTraceEnableDefault;  ///< Whether or not the trajectory effect is displayed Default value
    
    SUpgradeEffectProperty m_UpgradeEffectProp; ///< Upgrade Effect Related Properties  

public:
	CNtlPLItemProperty();
	virtual ~CNtlPLItemProperty();

	// 'ItemPropertyList.xml'���� ������Ƽ ��ϵ��� �������� �Լ�
	virtual RwBool	Load(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);
	virtual RwBool	Save(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode );

    RwBool	LoadScript(const std::string &strFileName);							    	///< XML Script �ε�
    RwBool  SaveScript(const std::string &strFileName);                                 ///< XML Script Save    

	virtual void	SaveSerialize(CNtlSerializer& sOut);											///< Serialize�� �����͸� �����ϴ� �Լ�
	virtual void	LoadSerialize(CNtlSerializer& sIn);												///< Serialize�κ��� �����͸� �������� �Լ�

    CNtlTypeAnimTable* GetAnimTable() {return &m_TypeAnimTable;}                        ///< AnimTable�� ��ȯ�Ѵ�.
	
	std::string	&GetMeshFileName()	{ return m_TypeMeshFileName; }						///< Get Mesh Name
	void SetMeshFileName(const std::string &strName) { m_TypeMeshFileName = strName; }	///< Set Mesh Name

	const std::string &GetMeshPath() { return m_TypeMeshPath; } 						///< Get Mesh Path
	void SetMeshPath(const std::string &strPath)	{ m_TypeMeshPath = strPath; }		///< Set Mesh Path

	void SetResType(EItemResType eResType) { m_TypeResType = eResType; }
	EItemResType GetResType() { return m_TypeResType; }

	void SetEquipSlotType(EItemEquipSlotType eEquipSlotType) { m_TypeEquipSlotType = eEquipSlotType; }
	EItemEquipSlotType GetEquipSlotType() { return m_TypeEquipSlotType; }

    void SetAttachOffset(const RwV3d& v3dOffset) {m_v3dAttachOffset = v3dOffset;}       ///< Item�� Attach Offset���� �����Ѵ�.
    RwV3d GetAttachOffset() {return m_v3dAttachOffset;}                                 ///< Item�� Attach Offset���� ��ȯ�Ѵ�.

    void    SetTraceEnableDefault(const RwBool bEnable) {m_bTraceEnableDefault = bEnable;}  ///< ���� ǥ�� ���� Default���� �����Ѵ�.
    RwBool  GetTraceEnableDefault() {return m_bTraceEnableDefault;}                         ///< ���� ǥ�� ���� Default���� ��ȯ�Ѵ�.

    SUpgradeEffectProperty* GetUpgradeEffectProperty() {return &m_UpgradeEffectProp;}    ///< Upgrade Effect�� Property�� ��ȯ�Ѵ�.

    // Flag �� �Լ���
    RwBool  IsApplyEmblem() {return (GetFlag() & ITEM_FLAG_APPLY_EMBLEM);}                ///< Emblem ���� ���������� ��ȯ�Ѵ�.
};

#endif