/*****************************************************************************
*
* File			: NtlPLDecal.h
* Author		: agebreak
* Copyright	: (��)NTL
* Date			: 2006. 6. 15	
* Abstract		: Presentation layer decal entity class
*****************************************************************************
* Desc         : Effect�� World���� ���Ǵ� Decal Ŭ����. (�׸��� ǥ������ ���ȴ�)
*
*****************************************************************************/

#ifndef __NTL_PLDECAL_H__
#define __NTL_PLDECAL_H__

#include "NtlPLAttach.h"
#include "NtlEffectDefine.h"

/// Decal�� ����
enum EDecalType
{
	DECAL_EFFECT,					///< Effect�� Decal
	DECAL_TERRAIN,					///< ������ Decal
};

// Decal Effect������ ���� �÷���
enum EDecalEffectFlag
{
	E_FLAG_DECAL_RENDER_OBJECT = 0x00100000,					///< ������Ʈ�� Decal�� ����
	E_FLAG_DECAL_RENDER_WORLD  = 0x00200000,					///< World�� Decal�� ����
	E_FLAG_DECAL_WATER		   = 0x00400000,					///< �� ������ ��Ÿ���� Decal�̶�� �� Flag�� ���ش� (�⺻�� False)
	E_FLAG_DECAL_DAYNIGHT 	   = 0x00800000						///< Day&Night�� ������ �޴� Decal�̶�� �� Flag�� ���ش� (�⺻�� False)
};


/// Object�� Decal�� �׸��� ���� �ݹ��Լ����� �Ѱ��ִ� �Ķ���� ����ü
struct DecalCallbackParam
{
	RwV3d vPos;
	RwMatrix *matTrans;
	RwMatrix *matAtomicTrans;
	RwInt32 *pBufferCnt;
	RwIm3DVertex *pVertices;

	float fIntersectionRadius;
	float fScale;
	RwInt32 nMaxVertextCnt;				///< ������ Decal�� �ִ� Vertex ����
	RwReal fYOffset;
};

class CNtlPLWorldEntity;

struct SPLDecalCreateParam : public SPLEntityCreateParam
{
	RwInt32	nTexNameLen;
	const RwChar *pTexName;
	const RwChar *pTexPath;
	RwReal fIntersectionRadius;
	RwV3d  vSize;								///< Decal's Size (use only X, Z values)
	RwReal fScale;
	RwReal fVisibleSquaredDist;					///< The square of the visual distance the decal is visible
	RwReal fYOffset;							///< Y Offset value (Decal height from ground)
	RwTextureAddressMode rwWrapType;			///< Texture Adress Mode
	RwInt32	nFlagEffect;						///< Effect flags
	EDecalType eDecalType;						///< Decal Type

	SPLDecalCreateParam()
	: rwWrapType(rwTEXTUREADDRESSCLAMP), fScale(1.0f), fIntersectionRadius(3.0f), 
	  fVisibleSquaredDist(1600.0f), fYOffset(0.1f)
	{ 
		vSize.x = vSize.y = vSize.z = 1.0f;
		pPos = NULL;
		nFlagEffect = E_FLAG_DECAL_RENDER_OBJECT | E_FLAG_DECAL_RENDER_WORLD;		
		eDecalType = DECAL_EFFECT;
	}
};

class CNtlPLDecal : public CNtlPLAttach
{
public:

	CNtlPLDecal();
	virtual ~CNtlPLDecal();

	void* operator new(size_t size);
	void operator delete(void *pObj);

	virtual RwBool Create( const SPLEntityCreateParam * pParam = NULL );
	virtual RwBool SetProperty(const CNtlPLProperty *pData);
	virtual void Destroy(void);
	virtual RwBool Update(RwReal fElapsed);
	virtual RwBool Render(void);
	
	virtual void SetNameLen(RwInt32 len) { m_iNameLen = len; }
	virtual void SetPosition(const RwV3d *pPos);	
	virtual void SetAlpha(RwUInt8 byAlpha);
	virtual void SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);
	virtual void SetScale(RwReal fScale);
    virtual void SetScaleSize(RwReal fScale);
	virtual void SetSize(RwReal fXSize, RwReal fZSize);
	virtual void SetRotate(RwReal fDegree);															///< Decal�� ȸ����Ų��. Y���� �������θ� ȸ���Ѵ�.Rotate Action�� ����Ǿ� �ִ� ��쿣 ������� �ʴ´�.
	virtual void SetMatrix(RwMatrix& matWorld);														///< World Matrix�� �����Ѵ�. 
	virtual void SetYOffset(RwReal fYOffset) {m_fYOffset = fYOffset;}								///< Decal�� YOffset ��(�������κ��� �� ���� �׸����ΰ�)�� �����Ѵ�

	virtual RwInt32	GetNameLen() { return m_iNameLen; }

	virtual RwV3d	GetPosition() {return m_vPos;}
	virtual RwRGBA	GetColor() {return m_color;}
	virtual RwReal	GetScale() {return m_fScale;}
	virtual RwReal	GetBaseScale() { return m_fStartScale; }
	virtual RwV3d	GetSize() {return m_vSize;}
	virtual RwReal	GetRotate() {return m_fDegree;}
	virtual RwMatrix& GetMatrix() {return m_matWorld;}
	virtual RwReal	GetYOffset() {return m_fYOffset;}
	virtual RwReal  GetVisibleDist() { return m_fVisibleSquaredDist; }
	virtual SNtlPrtStdEmitterPrtUVAnim& GetUVChunk() { return m_EmitterPrtUVAnim; }
    virtual RwUInt32 GetMemoryUseSize() {return m_uiMemoryUseSize;}                                 ///< �޸� ��뷮�� ��ȯ�Ѵ�.

	void			GetRotateActionValue(RwReal& fAngle, RwReal& fTimeGap);
	void			GetScaleActionValue(RwReal& _StartScale, RwReal& _EndScale, RwReal& _TimeGap);
	
	void SetLifeTime(RwReal fLifeTime) {m_fLifeTime = fLifeTime;}									///< Decal�� LifeTime�� �����Ѵ�. (���� Decal�� ��� 0�� ����)
	
	void SetAlphaBlend(RwBool bBlend, RwBlendFunction srcBlend, RwBlendFunction destBlend);			///< ���� ���带 �����Ѵ�.
	RwInt32	GetVerexCount() {return m_nRenderVertexCnt;}											///< ���� �׷����� �ִ� ���ؽ��� ������ ��ȯ�Ѵ�.

	// Effect Flag
	RwInt32	GetEffectFlag() {return m_nFlagEffect;}
	void	SetEffectFlag(RwInt32 nFlag) {m_nFlagEffect = nFlag;}

	// Action
	void	Set2DRoateAction(RwReal fAngle, RwReal fTimeGap = 1.0f);						///< ȸ�� �׼��� �����Ѵ�. (1�ʿ� ���� ȸ���ϴ� ������ �����Ѵ� (������ Degree�̴�.))
	void	SetColorAction(const RwRGBA& colStart, const RwRGBA& colEnd, RwReal fTimeGap);	///< Color Action�� �����Ѵ�.
	void	SetMultiColorAction(const RpPrtAdvPrtMultiColorEmitter& emitterPrtMulticol);		///< Multi Color Action�� �����Ѵ�.
	void	SetSizeAction(RwReal fStartScale, RwReal fEndScale, RwReal fTimeGap);			///< Size Action�� �����Ѵ�.
	void	SetMultiSizeAction(const SNtlAdvMultiSizeEmitter& emitterPrtMultiSize);			///< Multi Size Action�� �����Ѵ�.
	void	SetMultiTextureAction(const RpPrtAdvEmtPrtMultiTextures& emitterMultiTexture);	///< Multi Texture Action�� �����Ѵ�.
	void	SetUVAnimAction(const SNtlPrtStdEmitterPrtUVAnim& emitterUVAnim);				///< UV Animation�� �����Ѵ�.
    void    SetUpdateVertex(RwBool bUpdate) {m_bVertexUpdate = bUpdate;}                    ///< ���ؽ��� ���� ������Ʈ�Ҷ� �÷��׸� �ٲپ��ش�.

protected:
	RwBool	UpdateVertices();						///< Decal Vertex�� ������ �����Ѵ�.
	void	SetVertexColor(const RwRGBA& color);	///< Vertex���� Color�� �����Ѵ�.	
	void	UpdateUV();								///< Vertex���� UV���� Update�Ѵ�
	
	void	UpdateRoate(RwReal fElapsedTime);		///< Rotate Action ���� �����Ѵ�.
	void	UpdateColor(RwReal fElapsedTime);		///< Color Action ���� �����Ѵ�.
	void	UpdateScale(RwReal fElapsedTime);		///< Scale Action ���� �����Ѵ�.
	void	UpdateMultiTexture(RwReal fElapsedTime);///< Multi Texture Action ���� �����Ѵ�.
	void	UpdateMultiColor(RwReal fElapsedTime);	///< Multi Color Action ���� �����Ѵ�.
	void	UpdateMultiSize(RwReal fElapsedTime);	///< Multi Size Action ���� �����Ѵ�. (size�� X���� �����Ѵ�)
	void	UpdateUVAnim(RwReal fElapsedTime);		///< UV Anim Action ���� �����Ѵ�.
	void	UpdateFade(RwReal fElapsedTime);		///< Fade In/Out�� Update�Ѵ�.

	void	GetObjectDecalVertex();					///< Object�� �׷����� Decal�� ����Ѵ�.		
	RwBool	GetWaterDecalVertex();					///< ������ �׷����� Decal�� ����Ѵ�.
	RwBool	IsVisble();								///< ī�޶� �ø��� Visible Distance�� ����ؼ� �������� ������ ��ȯ�Ѵ�.
    void    ChangeBigVB();                          ///< ���ؽ� ���۰� ������ ��쿡 ū ���۷� �����Ѵ�.

	void	SetTextureMatrix(RwIm3DVertex* pVertices, RwInt32 nVertCnt, RwMatrix* pMatrix);	///< Vertex���� UV�� Texture Matrix�� �����Ѵ�.

protected:

	RwInt32	m_iNameLen;

    RwInt32 m_nMaxVertexCnt;
	RwV3d m_vPos;
	RwV3d m_vSize;
	RwReal m_fIntersectionRadius;
	RwReal m_fScale;
	RwReal m_fVisibleSquaredDist;
	RwTextureAddressMode m_rwWrapType;				///< �ؽ����� Wrap Type
	RwMatrix m_matWorld;							///< World Matrix
	RwReal m_fYOffset;								///< Y Offset ��
	RwBool m_bVertexUpdate;							///< Vertex�� Update���� ���� �÷���
	RwV3d  m_vOriginPos;							///< ���� ������ World Vertex�� ���� ��ġ
	RwReal m_fRadiusWorldVertex;					///< ���� ������ World Vertex�� ������
	RwReal m_fDegree;								///< Rotation�� (Degree)
	EDecalType m_eDecalType;						///< DecalType

	RwTexture* m_pTexture;
	RwTexture* m_pCurrentTexture;
	RwTexture** m_ppMultiTextures;
	RwRGBA m_color;	

	// Render State
	RwBool				m_bBlend;			///< ���� ���� ����
	RwBlendFunction		m_blendSrc;			///< �ҽ� ����
	RwBlendFunction		m_blendDest;		///< Ÿ�� ����

	RwIm3DVertex*		m_pIm3DBuffer;		///< Vertex Buffer 
	RwInt32				m_nRenderVertexCnt;	///< �������� Vertex�� ����	

	// Emitter Action
	RwInt32				m_nFlagEffect;		///< ����Ʈ �Ӽ� Flag
	RwReal				m_fTotalElapsedTime;///< �����Ǽ� ���ݱ����� �ð�
	RwReal				m_fElapsedTime;		///< �� �������� Ÿ��
	RwReal				m_fLifeTime;		///< Decal�� Life Time

	RwReal				m_f2DRoateAngle;	///< 2D Roate Action�� ȸ���ϴ� ����
	RwBool				m_bFirstRotate;		///< ������Ʈ�� �ؽ����� ������ ������ üũ�ϱ� ���ؼ� ����ϴ� ����
	RwReal				m_fOrgRotateAngle;	///< ���� ������ Rotate Angle��
	RwReal				m_fRotateTimeGap;	///< ������ Rotate Time Gap

	RwMatrix			m_matTexture;		///< UV ��ǥ ���濡 ���Ǵ� �ؽ��� ��Ʈ����

	RwRGBA				m_colStart;			///< Color Action�� ���Ǵ� Start Color
	RwRGBA				m_colEnd;			///< Color Action�� ���Ǵ� End Color
	RwReal				m_fColorActionTime;	///< Color Action�� ���Ǵ� Time

	RwReal				m_fStartScale;		///< Size Aciton�� ���Ǵ� Start Scale
	RwReal				m_fEndScale;		///< Scale Action�� ���Ǵ� End Scale;
	RwReal				m_fScaleActionTimeGap; ///< Scale Action ���Ǵ� Time

	RwUInt32			m_nCurrentTexture;		  ///< Multi Texture Action���� ���� ������ �Ǵ� �ؽ����� �ε��� ��ȣ
	RwReal				m_fMultiTextureDeltaTime; ///< Multi Texture Acion�� ���Ǵ� Time

	RwRGBA				m_colPrev;				  ///< Multo Color Action�� ���Ǵ� ������ Color
	RwUInt32			m_nNextColorIndex;		  ///< Multi Color Action�� ���Ǵ� Index
	RwReal				m_fMultiColorDeltaTime;	  ///< Multi Color Action�� ���Ǵ� Time

	RwReal				m_fPrevSize;			  ///< Multi Size Action�� ���Ǵ� ������ Size
	RwUInt32			m_nNextSizeIndex;		  ///< Multi Size Action�� ���Ǵ� Index
	RwReal				m_fMultiSizeDeltaTime;	  ///< Multi Size Action�� ���Ǵ� Time

	RpPrtAdvPrtMultiColorEmitter	m_EmitterPrtMultiCol;		///< Multi Color Action ������ ��� �ִ� ����ü
	RpPrtAdvEmtPrtMultiTextures		m_EmitterMultiTextures;		///< Multi Texture Action ���� ����ü
	SNtlAdvMultiSizeEmitter			m_EmitterPrtMultiSize;		///< Multi Size Action ���� ����ü
	SNtlPrtStdEmitterPrtUVAnim		m_EmitterPrtUVAnim;			///< UV Anim Action ���� ����ü

	EFadeStatus			m_eFadeStatus;			  ///< Fade ���� ���� (���� Decal�� ��쿡�� ���ȴ�)
	RwInt32 			m_uiFadeAlpha;			  ///< Fade�� ���Ǵ� Alpha 
	RwReal				m_fFadeGap;

    RwUInt32            m_uiMemoryUseSize;        ///< �޸� ��뷮

	static const RwReal		m_cfFadeTime;
};

#endif
