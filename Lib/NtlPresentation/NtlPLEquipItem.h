/*****************************************************************************
 *
 * File			: NtlPLEquipItem
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2006. 11. 6.
 * Abstract		: NTL PLEquipItem
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef _NTL_PL_EQUIP_ITEM_
#define _NTL_PL_EQUIP_ITEM_

#include "NtlPLItem.h"
#include "NtlDefaultItemData.h"

typedef	std::list< CNtlPLItem *>						EQUIP_ITEM_LIST;
typedef	std::list< CNtlPLItem *>::iterator				EQUIP_ITEM_LIST_ITER;

typedef	std::map<RwUInt32, CNtlPLItem *>				DEFAULT_ITEM_MAP;
typedef	std::map<RwUInt32, CNtlPLItem *>::iterator		DEFAULT_ITEM_MAP_ITER;

struct SEquipItemScheduleResInfo
{
	RwUInt32	uiClass;
	RwUInt32	uiRace;
	RwUInt32	uiGender;
	RwUInt32	uiHeadType;
	RwUInt32	uiFaceType;
	RwUInt32	uiSkinColorType;
	RwUInt32	uiHeadColorType;
    RwBool      bIsAdult;

	RwBool		bApplyedFace;
	RwBool		bApplyedHead;
    

	SEquipItemScheduleResInfo() : bApplyedFace( FALSE ), bApplyedHead( FALSE ), bIsAdult(FALSE) {}
};

class CNtlPLEquipItem
{
public:
	CNtlPLEquipItem();
	~CNtlPLEquipItem();

private:
	EQUIP_ITEM_LIST			m_listItem;											// ���� ������ Item�� list 
	DEFAULT_ITEM_MAP		m_mapDefaultItem;									// Default Body Item
	
	CNtlPLCharacter			*m_pOwner;											// ������								
	SEquipItemScheduleResInfo	m_sScheduleResInfo;								// ResLoad�� �� �� ���� 
	
	RwReal					m_fFaceTexAniDefaultChangeTime;						// Face Texture Change Delay Time Default
	RwReal					m_fFaceTexAniChangeTime;							// Face Texture Change Delay Time
	RwReal					m_fFaceTexAniDisplayTime;							// Face Texture Display Delay Time
	
	RwReal					m_fFaceTexAniCounter;								// Face Time �� counter
	RwInt32					m_iFaceTexAniNum;									// Current Face Texture

	RwTexture				*m_pFaceTexture[2];									// Face Texture;
	RwTexture				*m_pBaseFaceTexture;								// Base Face
	RwTexture				*m_pHeadTexture;									// Head Texture(Namek)

    RwBool                  m_bFaceChange;                                      // �� �ؽ��� ��ȭ ���� �÷���

private:
	void	SetDefItem(CNtlPLItem *pItem, RwUInt32 uiEquip);
	
	RwBool	SetChangeDefHeadItem(EClassGenderType eClassGenderType, RwUInt32 uiHeadType, RwUInt32 uiColorType);
	RwBool	SetChangeDefFaceItem(EClassGenderType eClassGenderType, RwUInt32 uiFaceType, RwUInt32 uiColorType);
	RwBool	SetChangeDefBodyItem(EClassGenderType eClassGenderType, RwUInt32 uiEquip, RwUInt32 uiColorType);
	
	void	SetApplyHeadData(CNtlPLItem *pItem);

	void AddItem(EItemEquipSlotType _eIEST);
	void RemoveItem(EItemEquipSlotType _eIEST);

public:
	void	SetOwner(CNtlPLCharacter *pOwner) { m_pOwner = pOwner; }
	void	Destroy();
	RwBool	Update(RwReal fElapsed);

	void	AddItem(CNtlPLItem *pItem, RwBool bAttach = TRUE);
	void	RemoveItem(CNtlPLItem *pItem);
	void	AddCItem(CNtlPLItem* _pItem, RwBool bAttach, RwUInt32 _CBitSet);
	void	RemoveCItem(CNtlPLItem* _pItem, RwUInt32 _CBitSet);

	void	SetCullFlags(RwUInt32 uiFlag, RwBool bCulled);
	void	SetCullFlags(RwUInt32 uiFlag);
	
	CNtlPLItem *GetDefItem(RwUInt32 uiEquip);
	
	EQUIP_ITEM_LIST	*GetEquipItemList() { return &m_listItem; }
	DEFAULT_ITEM_MAP *GetDefaultItemList() { return &m_mapDefaultItem; }

	RwBool	RenderToTexture();
	void	SetDefItemAlpha( RwUInt8 byValue );
	void	SetDefItemWeightAlpha( RwReal fWeightValue );
	void	SetDefItemColor( RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue );
	void	SetDefItemAddColor( RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue );
	void	SetDefItemVisible( RwBool bVisible );
	
	RwBool	Create( RwUInt32 uiClass, RwUInt32 uiRace, RwUInt32 uiGender, RwUInt32 uiHeadType, RwUInt32 uiFaceType, RwUInt32 uiSkinColorType, RwUInt32 uiHeadColorType, RwBool bIsAdult);

    void	SetApplyFaceData(CNtlPLItem *pItem);
    void    SetChangeFaceEnable(RwBool bEnable);          ///< �� �ؽ��� ���� ������ �����Ѵ�.
	VOID	SetToonEdgeVisibility4CurEquipItem(RwBool _Visibility);
	void	SetSimpleMaterial(RwBool _SimpleMaterial);
	VOID	SetPetrifyMaterial(RwBool _PetrifyFlag);
};

#endif
