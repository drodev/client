/*****************************************************************************
 *
 * File			: NtlPackImage
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2007. 3. 22	
 * Abstract		: Load Pack Image(dds, png, bmp)
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef _NTL_PACK_IMAGE_H_
#define _NTL_PACK_IMAGE_H_

struct SNtlPackImage
{
	const RwChar	*pName;				//Texture �̸�
	const RwChar	*pMaskName;			//Mask �̸�
	
	std::string		strPackFileName;	//Pack �̸�
	RwUInt32		uiPackOffset;		//Offset
	RwUInt32		uiPackSize;			//File Size
	
	SNtlPackImage() : pName(NULL), pMaskName(NULL), uiPackOffset(0), uiPackSize(0) {}
};

RwTexture	*Ntl_D3D9DDSTextureRead(SNtlPackImage *pPackImage);
RwTexture	*Ntl_PNGTextureRead(SNtlPackImage *pPackImage);
RwTexture	*Ntl_BMPTextureRead(SNtlPackImage *pPackImage);

#endif

