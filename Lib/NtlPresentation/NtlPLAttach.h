/*****************************************************************************
 *
 * File			: NtlPLAttach.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 11	
 * Abstract		: Presentation layer attach entity class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLATTACH_H__
#define __NTL_PLATTACH_H__

#include <list>
#include <string>
#include "NtlPLEntity.h"
#include "NtlMath.h"

class CNtlPLAttach;

enum EPLAttachType
{
	PL_ATTACH_BONE,
	PL_ATTACH_BONE_OFFSET_POS_ROOT_ROTATE_Y,//Character Bone���� Offset��ġ�� Root�� Y�� ȸ������ ����

	PL_ATTACH_WORLD_POS,
	PL_ATTACH_WORLD_POSANDROTATE,			//�켱 ���Ƿ� ��������(By HoDong)
    PL_ATTACH_WORLD_POS_HEIGHT,             ///< ��ġ�� Attach�ǳ� ���̴� World Height

    PL_ATTACH_NONE,                         ///< Bone�̳� World�� Attach���� �ʰ�, ���� Attach List���� ���� ��� (Trace Effect, Grade Effect)
};

#define MAX_ATTR_BONE_NAME	128

typedef struct _SPLAttachAttr
{
	CNtlPLAttach *pPLEntity;
	EPLAttachType eType;
	char chBoneName[MAX_ATTR_BONE_NAME];
	RwV3d vOffsetPos;
	RwV3d vScale;
	RwV3d vRot;

    _SPLAttachAttr()
    {
        ZeroMemory(chBoneName, sizeof(chBoneName));
        vScale.x = vScale.y = vScale.z = 1.0f;
		vRot.x = vRot.y = vRot.z = 0.0f;
        vOffsetPos = ZeroAxis;
    }
}SPLAttachAttr;
typedef std::list<SPLAttachAttr*> ListAttachAttr;


class CNtlPLAttach : public CNtlPLEntity
{
private:

	static RwFreeList *m_pAttachAttrFreeList;	/* attach attribute data memory pool **/

public:

	static RwBool AllocFreeList(void);
	static void DeAllocFreeList(void);

protected:
	CNtlPLAttach *m_pAttachParent;
	ListAttachAttr m_listAttachAttr;

private:

	RwBool Find(const CNtlPLAttach *pPLAttachEntity);
	void AttachDestroy(void);

public:

	CNtlPLAttach();
	virtual ~CNtlPLAttach();

	virtual RwBool Update(RwReal fElapsed);
	virtual RwBool RenderToTexture(void);

	RwBool AttachBone(CNtlPLAttach *pPLAttachEntity, const RwChar *pBoneName, SPLAttachAttr* _pSPLAttachAttr = NULL);
    //RwBool AttachBoneOffset(CNtlPLAttach* pPLAttachEntity, const RwChar* pBoneName, RwV3d vOffset);
	RwBool AttachBoneOffsetPosRootRotateY(CNtlPLAttach *pPLAttachEntity, const RwChar* pBoneName, RwV3d vOffset);

	RwBool AttachWorldPos(CNtlPLAttach *pPLAttachEntity, RwV3d vOffset);
	RwBool AttachWorldPosAndRotate(CNtlPLAttach *pPLAttachEntity, RwV3d vOffset);
    RwBool AttachWorldPosHeight(CNtlPLAttach* pPLAttachEntity); ///< ���� ���̿� Attach �Ѵ�.

    RwBool Attach(CNtlPLAttach* pPLAttachEntity);               ///< Bone�̳� World�� Attach ���� �ʰ�, Attach List���� ����
    
	void Detach(CNtlPLAttach *pPLAttachEntity);

	virtual void SetAttachParent(CNtlPLAttach *pPLAttachEntity);
	virtual CNtlPLAttach* GetAttachParent(void) const;

	virtual void CreateWeightElapsedController(RwReal fLifeTime, RwReal fWeightValue); 
	virtual void DeleteWeightElapsedController(void);

	virtual void SetVisible(RwBool bVisible);
	virtual void SetCullFlags(RwUInt32 uiFlag, RwBool bCulled);
	virtual void SetCullFlags(RwUInt32 uiFlag);

	virtual RwMatrix* GetBoneMatrix(const RwChar *pBoneName) { return NULL; }
	virtual RwFrame* GetFrame(void) { return NULL; }

	virtual ListAttachAttr* GetAttachAttrList() { return &m_listAttachAttr; }
};

#endif