/*****************************************************************************
 *
 * File			: NtlAtomicExt
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 27	
 * Abstract		: NTl Atomic Extension
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef _NTL_ATOMIC_EXT_H_
#define _NTL_ATOMIC_EXT_H_

#include <rwcore.h>
#include <rpworld.h>

/**< !!!!!!!!!!!!!!!!!!!!!!Clump�� ������ �ǹǷ� ���� ������ ���� ���� �Ͻø� �ȵ˴ϴ�.!!!!!!!!!!!!!!!!!!!!!!! */
enum ENtlAtomicFlag
{
	NTL_ATOMIC_FLAG_INVALID	= 0x00000000,

	NTL_TOON_NOT_EDGE		= 0x00000001, /**<Edge�� Rendering�� �������� */
	NTL_TOON_DETAIL_EDGE	= 0x00000002, /**<Edge�� Vertex�� ���� Detail�� Edge�� ����*/
	
	NTL_TWOSIDE             = 0x00000010, /**<TwoSide ���� */
	NTL_ALPHATEST			= 0x00000020, /**<AlphaTest ���� */
	NTL_ALPHA				= 0x00000040, /**<Alpha ���� */
	
	NTL_COLLISION			= 0x00001000, /**<Collision�� �Ұ��� ������ */
	NTL_NOT_VISIBLE			= 0x00002000, /**<ȭ�鿡 �׸��� �ȱ׸����� ����*/
	NTL_DECAL_VISIBLE		= 0x00004000, /**<Decal�� ǥ���� ���� ���� */
    NTL_CAMERA_COLLISION    = 0x00020000, /**<Not Visible üũ�� �Ȱ��߿��� ī�޶� �浹�� ������ ���� */

	NTL_SHADOW_MAP			= 0x00008000, /**<ShadowMap�� ������ ����(ShadowMap�� �ִ��� ����) */
	
	NTL_RUNTIME_ALPHA		= 0x00010000, /**<RunTime�� Alpha�� ������ �Ǵ� ��� */
	NTL_TOON_EDGE_OFF		= 0x00040000,
	NTL_ENVMAP_TEX			= 0x00080000, /**<Enviroment map texture name */
	NTL_EMBLEM_MARK			= 0x00100000,

	NTL_FINAL_SORT          = (NTL_ALPHA | NTL_RUNTIME_ALPHA) /**<Alpha or RunTimeAlpha */
};


RwBool		RpNtlAtomicPluginAttach(void);
void		RpNtlClumpSetData(RpClump* pClump, void *pData);
void		RpNtlAtomicSetData(RpAtomic* pAtomic, void *pData);
void*		RpNtlAtomicGetData(const RpAtomic* pAtomic);

void		RpNtlAtomicSetFlag(RpAtomic *pAtomic, RwUInt32 uiFlag);				/**<ENtlAtomicFlag Option */
RwUInt32	RpNtlAtomicGetFlag(RpAtomic *pAtomic);								/**<ENtlAtomicFlag Option */

RwTexture*	RpNtlAtomicGetUserDat4RwTex(RpAtomic* _pAtomic);
void		RpNtlAtomicSetUserDat4RwTex(RpAtomic* _pAtomic, RwTexture* _pUserDat);
void		RpNtlAtomicSetUserDat(RpAtomic* _pAtomic, void* _pUserDat);
void*		RpNtlAtomicGetUserDat(RpAtomic* _pAtomic);
void		RpNtlAtomicSetUserDatU16(RpAtomic *pAtomic, RwUInt16 uiSize);
RwUInt16	RpNtlAtomicGetUserDatU16(RpAtomic *pAtomic);					
void		RpNtlAtomicSetUserDatReal(RpAtomic *pAtomic, RwReal uiSize);
RwReal		RpNtlAtomicGetUserDatReal(RpAtomic *pAtomic);					
void		RpNtlAtomicSetEnvTexName(RpAtomic* _pAtomic, RwUInt16 _EnvTexName);
RwUInt16	RpNtlAtomicGetEnvTexName(RpAtomic* _pAtomic);

void		RpNtlAtomicSetAlpha(RpAtomic* pAtomic, RwUInt8 alpha);
RwUInt8		RpNtlAtomicGetAlpha(RpAtomic* pAtomic);

RpAtomicCallBackRender RpNtlAtomicGetRenderCallBack(RpAtomic *pAtomic);
void RpNtlAtomicSetRenderCallBack(RpAtomic *pAtomic, RpAtomicCallBackRender atomicCallBackRender);

#endif