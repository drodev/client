/*****************************************************************************
 *
 * File			: NtlPLObjectProperty.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 22	
 * Abstract		: Presentation layer object property class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLOBJECT_PROPERTY_H__
#define __NTL_PLOBJECT_PROPERTY_H__

#include "NtlPLProperty.h"
#include "NtlTypeAnimData.h"

#define XML_PARSING_BUFFER_SIZE		( 1024 )

/// ������Ʈ�� Ÿ��
enum EPLObjectType
{
    E_OBJECT_NORMAL = 0,                        ///< �Ϲ� ������Ʈ
    E_OBJECT_MILEPOST,                          ///< ����ǥ�� ������Ʈ (ȭ��ǥ)
};

/// ������Ʈ �÷��� (������ Bool���鵵 �÷��׷� �ٲٰ� ������, �׷��� ���� ȣȯ���� ������)
#define OBJ_FLAG_SORT_BY_POS        0x00000001
#define OBJ_FLAG_FORCE_PICKING      0x00000002
#define OBJ_FLAG_PE_NAVI_PRESS      0x00000004
#define OBJ_FLAG_CULLTEST_ATOMIC    0x00000008

/**
* \ingroup NtlPresentation
* CNtlPLObject�� �ش��ϴ� property class�̴�.
* property data�� xml file�� �ۼ��Ǿ��� �ִ�.
*
*/
class CNtlPLObjectProperty : public CNtlPLProperty
{
public:

	static unsigned int m_strVer;			/* property file version **/
	static std::string m_strObjectDataPath;	/* Object Data File Path(*.xml) **/
	static std::string m_strMeshPath;		/* object mesh file�� path name **/
	static std::string m_strAniPath;		/* object animation file�� path name **/
	static std::string m_strTexPath;		/* object texture file�� path name **/

	std::string m_strDffFile;				/* object mesh file name **/
    std::string m_strUVAnimFileName;        ///< UVAnim File Name (��� ��� ����)
    std::string m_strAnimFileName;          ///< AnimFileName (��� ��� ����)    
    std::string m_strCollisionMeshName;     ///< Path Engine�� Collision Mesh File Name

	std::vector<SEventLinkEffect*> m_vLinkEffect; ///< Link Effect�� ����Ʈ 

protected:
    RwBBox          m_bbox;                         ///< Server Object�� BBox 
    RwBool          m_bCollision;                   ///< Server Collision ����
	RwBool          m_bShadow;                      ///< Shadow ǥ�� ����    
    RwReal          m_fUvAnimSpeed;                 ///< UVAnim Speed    
    RwReal          m_fCullingDistance;             ///< Culling Distance
    RwBool          m_bApplyPVS;                    ///< PVS ������ �޴��� �ȹ޴��� ����
    RwInt32         m_nObjectFlag;

	CNtlTypeAnimTable m_TypeAnimTable;				///< Animation Table
    EPLObjectType   m_eObjectType;                  ///< Object Type

    SEventSound     m_SoundProp;                    ///< �⺻ ��� ���� ������Ƽ

    

public:
	CNtlPLObjectProperty();
	virtual ~CNtlPLObjectProperty();

	// 'ObjectPropertyList.xml'���� ������Ƽ ���ϸ��� �������� �Լ�
	virtual RwBool	Load(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode);	
	virtual RwBool	Save(CNtlXMLDoc *pDoc, IXMLDOMNode *pNode );

    virtual RwBool  SaveScript(const std::string &strFileName);          ///< XML ��ũ��Ʈ ���Ϸ� �����Ѵ�.
    virtual RwBool  LoadScript(const RwChar* strFileName);          ///< XML ��ũ��Ʈ�� ���� �����͸� �ε��Ѵ�.

	virtual void	SaveSerialize(CNtlSerializer& sOut);											///< Serialize�� �����͸� �����ϴ� �Լ�
	virtual void	LoadSerialize(CNtlSerializer& sIn);												///< Serialize�κ��� �����͸� �������� �Լ�
	
	void                    SetDffName(const RwChar* strDffName) {m_strDffFile = strDffName;}
	const char *			GetDffName( void ) const { return m_strDffFile.c_str(); }

    void    SetEnableShadow(RwBool bEnable) {m_bShadow = bEnable;}
    RwBool  GetEnableShadow() {return m_bShadow;}

    void    SetBBox(RwBBox bbox) {m_bbox = bbox;};                                  ///< BBox�� �����Ѵ�
    RwBBox* GetBBox() {return &m_bbox;}                                             ///< ������ BBox�� ��ȯ�Ѵ�.

    void    SetUVAnimSpeed(RwReal fSpeed) {m_fUvAnimSpeed = fSpeed;}                ///< UVAnim �ӵ��� �����Ѵ�
    RwReal  GetUVAnimSpeed() {return m_fUvAnimSpeed;}                               ///< UVAnim �ӵ��� ��ȯ�Ѵ�.

    void    SetCollision(RwBool bCollision) {m_bCollision = bCollision;}            ///< Collision ���� ������ �����Ѵ�.
    RwBool  GetCollision() {return m_bCollision;}                                   ///< Collision ���� ������ ��ȯ�Ѵ�.

    void    SetCullingDistance(RwReal fDistance) {m_fCullingDistance = fDistance;}  ///< Culling Distance�� �����Ѵ�.
    RwReal  GetCullingDistance() {return m_fCullingDistance;}                       ///< Culling Distance�� ��ȯ�Ѵ�.

	CNtlTypeAnimTable* GetAnimTable() {return &m_TypeAnimTable;}                        ///< AnimTable�� ��ȯ�Ѵ�.

    void    SetObjectType(EPLObjectType eObjectType) {m_eObjectType = eObjectType;} ///< Object Type�� �����Ѵ�.
    EPLObjectType GetObjectType() {return m_eObjectType;}                           ///< Object Type�� ��ȯ�Ѵ�.

    void    SetApplyPVS(RwBool bApplyPVS) {m_bApplyPVS = bApplyPVS;}                ///< PVS�� ������ �޴��� �ȹ޴��� �����Ѵ�.
    RwBool  GetApplyPVS() {return m_bApplyPVS;}                                     ///< PVS�� ������ �޴��� �ȹ޴��� ��ȯ�Ѵ�.

    SEventSound* GetSoundProp() {return &m_SoundProp;}                              ///< ������Ʈ�� ���� ������ ��ȯ�Ѵ�.

    // �÷��� ���� �Լ���
    RwBool  IsSortByPos() {return (GetFlag() & OBJ_FLAG_SORT_BY_POS);}
    RwBool  IsForcePicking() {return (GetFlag() & OBJ_FLAG_FORCE_PICKING);}
    RwBool  IsNaviPress()   {return (GetFlag() & OBJ_FLAG_PE_NAVI_PRESS);}           ///< �н� ���������� Obstacle Mesh�� ���� ����
    RwBool  IsCullTestAllAtomic() {return (GetFlag() & OBJ_FLAG_CULLTEST_ATOMIC);}     ///< �ִϸ��̼ǿ��� Atomic�� ���ؼ� Culling Test�� ���� ������ ��ȯ�Ѵ�.

};
#endif