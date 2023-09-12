/*****************************************************************************
*
* File			: NtlPLEmblemMaker.h
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2008. 3. 4
* Abstract		: Presentation layer emblem maker
*****************************************************************************
* Desc          : ��� ������ ����/��ȯ �Ѵ�
*				  ��� �ؽ�ó : ������ ����� ���� �����ϴ� ���û��� �ؽ�ó
*****************************************************************************/

#ifndef __NTL_PLEMBLEM_MAKER_H__
#define __NTL_PLEMBLEM_MAKER_H__

#include "NtlPLDef.h"
#include "NtlPLEmblemStuffList.h"


#define dPLEMBLEM_INVALID_FACTOR			(0xff)

#define dMAX_EMBLEM_TEXTURE_SIZE			(256)
#define dEMBLEM_TEXTURE_DEFAULT_SIZE		(64)


class CNtlPLCameraRT;

struct sEmblemFactor
{
	RwUInt8		byTypeA;
	RwUInt8		byTypeB;
	RwUInt8		byTypeC;
	RwUInt8		byTypeAColor;
	RwUInt8		byTypeBColor;
	RwUInt8		byTypeCColor;

	sEmblemFactor()
	:byTypeA(dPLEMBLEM_INVALID_FACTOR)
	,byTypeB(dPLEMBLEM_INVALID_FACTOR)
	,byTypeC(dPLEMBLEM_INVALID_FACTOR)
	,byTypeAColor(0)
	,byTypeBColor(0)
	,byTypeCColor(0)
	{
	}
};

class CNtlPLEmblemMaker
{
public:
	struct sEmblemData
	{
		sEmblemFactor	factor;
		RwTexture*		pTexture;
	};

	typedef std::map<std::string, sEmblemData*>					MAP_TEXTURE;
	typedef std::map<std::string, sEmblemData*>::iterator		ITER_MAP_TEXTURE;

	typedef std::map<RwUInt8, CNtlPLCameraRT*>					MAP_RT_CAMERA;
	typedef std::map<RwUInt8, CNtlPLCameraRT*>::iterator		ITER_RT_CAMERA;

public:
	static CNtlPLEmblemMaker* GetInstance() { return m_pInstance; }
	


	CNtlPLEmblemMaker();
	virtual ~CNtlPLEmblemMaker();

	static VOID	CreateInstance();
	static VOID	DestoryInstance();

	VOID		DestoyEmblem(const char* pcTextureName);
	VOID		DestoyEmblem(RwTexture* pTexture);

	///< ���� �ؽ�ó�� ��ȯ, ���ٸ� ���� �����Ͽ� ��ȯ
	///< ���� : ������ Ÿ�ӿ� �� �Լ��� ȣ��ǰ� ��ȯ�Ǵ� RwTexture�� NULL�� �ƴϸ� ���� ����.
	///<		�� �Լ��� ���ο��� ȣ��Ǵ� Camera->CameraBeginUpdate�� ���� �������ǰ� �ִ�
	///<		Current Camera�� �����͸� �����ϴ� �ݵ�� �� �Լ��� ������ �̿��� Ÿ�ӿ� ȣ���Ѵ�.
	RwTexture*	CreateEmblem(const sEmblemFactor* pEmblemFactor,
							 RwUInt8 byEmblemSize = dEMBLEM_TEXTURE_DEFAULT_SIZE,
							 const RwChar* pcBaseTextureName = NULL);


	///< ���û� �����ϴ� ���� ��� �ؽ�ó�� �̸��� ���·� ���� ��ȯ�Ѵ�
	VOID		MakeEmblemResourceName(eEmblemType eType, RwUInt8 byValue, char* pcOutBuffer, RwInt32 iBufferLength,
									   RwUInt8 byEmblemSize = dEMBLEM_TEXTURE_DEFAULT_SIZE);
	
	const MAP_STUFF* GetStuffList(eEmblemType eType);

protected:
	///< ��� �ؽ�ó�� ���ڷ� ������� ���� �ؽ�ó�� �̸��� ��ȯ�Ѵ�, ĳ���� ���� ������ ��ȿ���� �ʴ�
	///< Suffix : ���̻�
	VOID		MakeEmblemTextureName(char* pcOutBuffer, RwInt32 iBufferLength, const sEmblemFactor* pEmblemFactor,
									  RwUInt8 byEmblemSize, const RwChar* pcBaseTextureName);

	RwTexture*	MakeEmblemImmidately(const sEmblemFactor* pEmblemFactor, const char* pcEmblemName,
									 RwUInt8 byEmblemSize, const RwChar* pcBaseTextureName = NULL);

	///< ������ ���ۿ� �Ѱܹ��� �ؽ�ó�� �׸���
	VOID		RecoatEmblem(RwTexture* pTexture, RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);
	RwTexture*	CopyToTexture(RwTexture* pTexture);

	///< �ؽ�ó ����� �´� ī�޶� ��ȯ
	///< ������ �� �ؽ�ó�� ����� ���� �پ������� ���� ���̱⿡ ������ ����
	///< ī�޶� ���� ����� �ؽ�ó�� ��´�
	CNtlPLCameraRT* GetRTCamera(RwUInt8 bySize);

protected:
	static CNtlPLEmblemMaker* m_pInstance;

	MAP_RT_CAMERA			m_mapRTCamera;
	RwIm2DVertex			m_2dVertices[4];
	MAP_TEXTURE				m_mapTexture;

	CNtlPLEmblemStuffList*	m_pStuffList;
};

static CNtlPLEmblemMaker* GetEmblemMaker(VOID)
{
	return CNtlPLEmblemMaker::GetInstance();
}

#endif