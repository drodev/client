

#ifndef _NTLEFFECT_API_
#define _NTLEFFECT_API_

#include <rphanim.h>
#include <rpskin.h>
#include <rpuvanim.h>
#include <rtdict.h>


RpAtomic*	API_GetSkinHierarchy(RpAtomic *atomic, void *data);
void		API_SetAnimation(RpClump* pClump, RtAnimAnimation* pAnimation);

RpAtomic*	API_MeshColorUpdate(RpAtomic *pAtomic, void *data __RWUNUSED__);

/// Clump���� UVAnim�� ����� Material�� ã�Ƽ� List�� �߰��Ѵ�.
RwSList*	API_AddAnimatedMaterialsList(RwSList* pList, RpClump* pClump);

/// UVAnim�� �ð��� ������Ʈ�Ѵ� (�ð� �߰�)
void		API_MaterialsInterpolatorsAddAnimTime(RwSList *animatedMaterials, RwReal deltaTime);
/// UVAnim�� �ð��� ������Ʈ �Ѵ� (�ð� ����)
void        API_MaterialsInterpolatorsSetCurrentTime(RwSList* animatedMaterials, RwReal fTime);
/// UVAnim�� ������Ʈ�Ѵ�.
void		API_MaterialsAnimApply(RwSList *animatedMaterials);

#endif