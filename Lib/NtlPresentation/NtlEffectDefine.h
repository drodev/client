

#ifndef _NTLEFFECT_DEFINE_
#define _NTLEFFECT_DEFINE_

#include "NtlSoundDefines.h"
#include "NtlMath.h"

#include <string>

class CNtlInstanceEffect;


#define EFFECT_FILE_EXE			"eff"
#define EFFECT_FILE_HEADER		"effect"
#define EFFECT_FILE_VERSION		104

const RwV3d VEC_X = { 1.f, 0.f, 0.f };
const RwV3d VEC_Y = { 0.f, 1.f, 0.f };
const RwV3d VEC_Z = { 0.f, 0.f, 1.f };

const RwRGBA RGBA_BASE = { 255, 255, 255, 255 };

#define NTLPRTSTD_SRAND_MAX                    0xFFFFFFFF
#define NTLPRTSTD_SRAND_IMAX                   ((RwReal) 1.0 / (RwReal) NTLPRTSTD_SRAND_MAX)

#define NTLPRTSTD_SRAND(_seed)                 ((_seed) = ((_seed) * 196314165 + 907633515))
#define NTLPRTSTD_RSRAND(_seed)                (((RwReal)((RwUInt32) (_seed) * NTLPRTSTD_SRAND_IMAX) * (RwReal) 2.0) - (RwReal) 1.0)

#define EFFECT_NAME_TRACE       "TraceEffect"
#define EFFECT_NAME_GRADE       "GradeEffect"

// Blur Effect ����
#define EFFECT_BLUR_TEXTURE_WIDTH   512
#define EFFECT_BLUR_TEXTURE_HEIGHT  384

#define EFFECT_BLUR_ALPHA   100         ///< Blur Alpha �� (0 ~ 255)


// Predefined flags in renderware.
// Custom flags should use the following flags except for the following flags.
/*
#define rpPRTSTDEMITTERDATAFLAGSTANDARD                     0x00000001
#define rpPRTSTDEMITTERDATAFLAGPRTCOLOR                     0x00000002
#define rpPRTSTDEMITTERDATAFLAGPRTTEXCOORDS                 0x00000004
#define rpPRTSTDEMITTERDATAFLAGPRT2DROTATE                  0x00000008
#define rpPRTSTDEMITTERDATAFLAGPRTSIZE                      0x00000010
#define rpPRTSTDEMITTERDATAFLAGPTANK                        0x00000020
#define rpPRTSTDEMITTERDATAFLAGPRTMATRIX                    0x00000040

#define rpPRTADVEMITTERDATAFLAGPRTEMITTER                   0x00000100
#define rpPRTADVEMITTERDATAFLAGMULTICOLOR                   0x00000200
#define rpPRTADVEMITTERDATAFLAGMULTITEXCOORDS               0x00000400
#define rpPRTADVEMITTERDATAFLAGMULTITEXCOORDSSTEP           0x00000800
#define rpPRTADVEMITTERDATAFLAGMULTISIZE                    0x00001000

#define rpPRTADVEMITTERDATAFLAGPOINTLIST                    0x00010000
#define rpPRTADVEMITTERDATAFLAGCIRCLE                       0x00020000
#define rpPRTADVEMITTERDATAFLAGSPHERE                       0x00030000

*/

// ����� ���� Flag
#define rpPRTSTDEMITTERDATAFLAGPRTORBITPOINT				0x00000080

#define rpPRTADVEMITTERDATAFLAGMULTIROTATE					0x00002000
#define rpPRTSTDEMITTERDATAFLAGTRAIL                        0x00004000                  ///< Trail Action �÷��� 
#define rpPRTSTDEMITTERDATAFLAGUVANIM						0x00008000                  ///< UV Anim �÷��� (Decal���� ���)

#define rpPRTADVEMITTERDATAFLAGMULTITEXTURES				0x01000000
#define rpPRTSTDEMITTERDATAFLAGPRTHURRICANE					0x02000000
#define rpPRTSTDEMITTERDATAFLAGPRTFADEOUT					0x04000000

#define rpPRTADVEMITTERDATAFLAGSPLINEPATH					0x10000000
#define rpPRTSTDEMITTERDATAFLAGPRTFINISH                    0x40000000

// ��ƼŬ ���� ���� Flag
#define NTLrpPRTADVEMITTERDATAFLAGFOLLOW                    0x80000000                  ///< ���� ��ġ�� ����ٴϴ� ��ƼŬ �÷���
#define NTLrpPRTSTDEMITTERDATAFLAGPRTYBILLBOARD             0x00100000                  ///< ��ƼŬ�� Y������ �÷���
#define NTLrpPRTSTDEMITTERDATAFLAGPRTXBILLBOARD             0x00200000                  ///< ��ƼŬ�� X������ �÷���
#define NTLrpPRTSTDEMITTERDATAFLAGPRTZBILLBOARD             0x00400000                  ///< ��ƼŬ�� Z������ �÷���
#define NTLrpPRTSTDEMITTERDATAFLAGPRTZWRITE					0x00800000					///< ��ƼŬ���� Z Write ���� �÷���

// ����Ʈ ����Ʈ ���� Flag
#define NTLrpPRTSTDEMITTERDATAFLAGPRTCENTERFIX			    0x08000000					///< ��ƼŬ���� Z Write ���� �÷���

// Fade In/Out�� ���Ǵ� �÷���
enum EFadeStatus
{
	FADE_STATUS_IN,
	FADE_STATUS_ING,
	FADE_STATUS_OUT,
	FADE_STATUS_OUT_ING,
	FADE_STATUS_IN_ING,	
};

struct SNtlPrtStdEmitterPrtOrbitPoint
{
	RwV3d point;
};

struct SNtlPrtEmitterSplinePath
{
	RwChar			strName[MAX_PATH];

	RwBool			loop;
	RwBool			useRotate;

	RwV3d			vPosition;
	RwV3d			vRotate;

	RwReal			rwUnknown;
};

struct SNtlPrtStdEmitterPrtSize
{
    RwV3d                       prtStartSize,
                                prtStartSizeBias;
    RwV3d                       prtEndSize,
                                prtEndSizeBias;

	RwReal						rwUnknown;
};

struct SNtlPrtStdEmitterPrtRotate
{
    RwV3d                       prtStartRotate,
                                prtStartRotateBias;
    RwV3d                       prtEndRotate,
                                prtEndRotateBias;

    SNtlPrtStdEmitterPrtRotate()
    {
        ZeroMemory(&prtStartRotate, sizeof(RwV3d));
        ZeroMemory(&prtStartRotateBias, sizeof(RwV3d));
        ZeroMemory(&prtEndRotate, sizeof(RwV3d));
        ZeroMemory(&prtEndRotateBias, sizeof(RwV3d));
    }
};

struct SNtlAdvEmtPrtSizeItem
{
	RwReal                              time;           /**<Time.*/
	RwReal                              timeBias;       /**<Time bias.*/
	RwV3d                               midSize;        /**<Size.*/
	RwV3d                               midSizeBias;    /**<Size bias.*/
};
struct SNtlAdvMultiSizeEmitter
{
	RwUInt32                            numSize;
	SNtlAdvEmtPrtSizeItem               *list;    
};

struct SNtlAdvEmtPrtRotateItem
{
    RwReal                              time;           /**<Time.*/
    RwReal                              timeBias;       /**<Time bias.*/
    RwV3d                               midRotate;      /**<Size.*/
    RwV3d                               midRotateBias;	/**<Size bias.*/
};
struct SNtlAdvMultiRotateEmitter
{
    RwUInt32							numRotate;
    SNtlAdvEmtPrtRotateItem*			list;

    SNtlAdvMultiRotateEmitter() : list(NULL),
                                  numRotate(0)
    {

    }
};


struct SNtlPrtStdEmitterPrtHurricane
{
	RwReal			fSpeed;
    RwReal			radius;
	RwReal			revolutionCount;
	RwReal			revolutionAngle;
};

struct SNtlPrtStdEmitterPrtFadeOut
{
	RwReal			time;
	RwBool			follow;
	RwChar			strFollowSystem[MAX_PATH];
};

/// UV Animation ���� ������Ƽ ����ü (Decal���� ����Ѵ�)
struct SNtlPrtStdEmitterPrtUVAnim
{
	RwV3d			vDir;			///< UV Anim���� (X, Z ���� ���)
	RwReal			fVelocity;		///< UV Anim �ӵ�
	RwReal			fMaxOffset;		///< Max Offset �� (�� ���� �����ϸ� Offset ���� �պ��ϴ� UV Anim�� �ȴ�)
	
	SNtlPrtStdEmitterPrtUVAnim()
	{
		vDir.x = 1.0f;
		vDir.y = vDir.z = 0.0f;
		fVelocity = 0.0f;
		fMaxOffset = 0.0f;
	}
};

struct RpPrtAdvEmtPrtTextureItem
{
    RwReal                              time;
    RwReal                              timeBias;

	std::string							strTexture;
};

struct RpPrtAdvEmtPrtMultiTextures
{
    RwReal                              time;
	RwBool								bLoop;
    RwUInt32							numTextures;
    RpPrtAdvEmtPrtTextureItem			*list;
};

struct SNtlPostEffectEmitterStandard
{
	RwBool			bDrawFullScreen;
	RwInt32			nLoopCount;
    RwInt32         nVertexCount;               ///< Post Effect�� Vertex ����
    RwReal          fRadius;                    ///< ������ (����)

    SNtlPostEffectEmitterStandard()
    : nVertexCount(16), nLoopCount(1), bDrawFullScreen(FALSE), fRadius(512.0f)
    {
    }
};

struct SNtlMeshEmitterStandard
{
	RwV3d			prtSize;
	RwRGBA			prtColor;
	RwV3d			prtRotate;
	RwBool			bWriteEnable;

	SNtlMeshEmitterStandard()
	{
		prtSize = ZeroAxis;
		ZeroMemory(&prtColor, sizeof(RwRGBA));
		prtRotate = ZeroAxis;
		bWriteEnable = FALSE;
	}
};

struct SNtlBeamEmitterStandard
{
	RwReal			fSpeed;
	RwV3d			prtSize;
	RwRGBA			prtColor;

	RwChar			strHeadSystem[MAX_PATH];
};

struct SNtlLightningEmitterStandard
{
	RwRGBA			prtColor;
	RwV3d			prtSize;		// X = start width, Y = end width, Z = center width

	RwReal			fAmp;
	RwReal			fRough;

	RwReal			fUpdateTime;
};

/// Decal System�� ������ ������ �ִ� ����ü
struct SNtlDecalEmitterStandard_Old
{
	RwTextureAddressMode 			eWrapType;			///< Texture�� Wrap Type
	RwReal							fVisibleDistance;	///< Decal Effect�� ���̴� �þ� �Ÿ�
	RwV3d							vSize;				///< Decal�� Size
	RwReal							fScale;				///< Decal Effect�� Scale��    
	
	SNtlDecalEmitterStandard_Old()
	: eWrapType(rwTEXTUREADDRESSCLAMP), fVisibleDistance(40.0f),
	  fScale(1.0f)
	{	
		vSize.x = vSize.y = vSize.z = 1.0f;
	}
};

/// Y Offset ���� �߰��� ������ (��ũ��Ʈ ���� 8�� �߰�)
struct SNtlDecalEmitterStandard
{
    RwTextureAddressMode 			eWrapType;			///< Texture�� Wrap Type
    RwReal							fVisibleDistance;	///< Decal Effect�� ���̴� �þ� �Ÿ�
    RwV3d							vSize;				///< Decal�� Size
    RwReal							fScale;				///< Decal Effect�� Scale��   
    RwReal                          fYOffset;           ///< Y Offset
    RwRGBA                          color;              ///< �⺻ �÷���

    SNtlDecalEmitterStandard()
    : eWrapType(rwTEXTUREADDRESSCLAMP), fVisibleDistance(40.0f),
      fScale(1.0f)
    {
        vSize.x = vSize.y = vSize.z = 1.0f;
        fYOffset = 0.02f;
        color.red = color.green = color.blue = color.alpha = 255;
    }
};

struct SNtlHurricaneEmitterStandard
{
	RwReal			fSpeed;
	RwV3d			prtSize;
	RwRGBA			prtColor;

	RwInt32			maxPolygonCount;

	RwBool			bEternity;
	RwReal			lifeTime;

    RwReal			radius;
    RwReal			radiusGap;

	RwInt32			revolutionCount;

	RwReal			revolutionAngle;
};

/// Line System�� �⺻ �Ӽ�����
struct SNtlLineEmitterStandard
{
    // ������Ƽ �Ӽ���
    RwReal  m_fLineLifeTime;            ///< ������ LifeTime
    RwInt32 m_nMaxCount;                ///< ������ �ִ� ���� ����
    RwInt32 m_nEmitterCount;            ///< �� Frame�� �����Ǵ� ������ ����
    RwReal  m_fEmitterGap;              ///< Emitter���� ����� �����Ǵ� Gap
    RwReal  m_fEmitterRaduis;           ///< Emitter�� ������
    RwReal  m_fEmitterBias;             ///< Emitter�� Bias��
    RwReal  m_fTargetRadius;            ///< ������ �̵��� Target�� ������
    RwV2d   m_sizeLine;                 ///< �����Ǵ� Line�� ũ�� (x: ����, y:����)
    RwReal  m_fVelocity;                ///< ������ �̵��ϴ� �ӵ�    
    RwBool  m_bShake;                   ///< ������ ��鸲 ����
    RwReal  m_fShakeBias;               ///< ��鸲 ��
    RwBool  m_bMoveLine;                ///< ������ Dir�������� �̵�����, ���� �þ�⸸ ���� ����
    RwBool  m_bZBufferEnable;           ///< Z-Buffer ��� ����
    RwBool  m_bZBiilBoard;              ///< Z-BillBoard ���� ����

    SNtlLineEmitterStandard() : m_fLineLifeTime(1.0f),
                                m_nMaxCount(100),
                                m_nEmitterCount(1),
                                m_fEmitterGap(0.03f),
                                m_fEmitterRaduis(0.0f),
                                m_fEmitterBias(0.0f),
                                m_fTargetRadius(1.0f),
                                m_fVelocity(50.0f),
                                m_bShake(FALSE),
                                m_fShakeBias(0.1f),
                                m_bMoveLine(TRUE),
                                m_bZBufferEnable(TRUE),
                                m_bZBiilBoard(TRUE)
    {
        m_sizeLine.x = 0.2f;
        m_sizeLine.y = 10.0f;
    }
};

// ���� Emitter ������Ƽ (Ÿ������ ��������, Line System�� Emitter�� ���ȴ�)
struct SNtlPrtStdEmitterPrtSphere
{
    RwV3d   m_vEmitterSize;    

    SNtlPrtStdEmitterPrtSphere() 
    {
        m_vEmitterSize.x = 1.0f;
        m_vEmitterSize.y = 1.0f;
        m_vEmitterSize.z = 1.0f;
    }
};

// Effect�� Finish Ÿ�� �÷���
enum EPrtFinishType
{
    FINISH_TYPE_ALPHA   = 1,      ///< ���İ� �������鼭 �������.
    FINISH_TYPE_SIZE    = 2,      ///< ����� �۾����鼭 �������.
    FINISH_TYPE_FOLLOW  = 4,      ///< ������ ���� ù���� �̵��ϸ鼭 ���̰� �۾����鼭 �������.
};

// Finish Action�� ���� ������Ƽ
struct SNtlPrtStdEmitterPrtFinish
{
    RwInt32        m_nFinishTypeFlag;
    RwReal         m_fFinishTime;       ///< Finish �۾��� �ɸ��� �ð�

    SNtlPrtStdEmitterPrtFinish()
    {
        m_nFinishTypeFlag = FINISH_TYPE_ALPHA;
        m_fFinishTime = 0.5f;
    }
};


/// Trace Action�� ���� ������Ƽ ����ü
struct SNtlPrtStdEmitterTrail
{
    RwReal  fEdgeLifeTime;            ///< Edge�� Life Time       
    RwReal  fMaxLength;               ///< ������ �ִ� ����
    RwReal  fWidth;                   ///< ������ ����  
    RwChar  strTexture[MAX_PATH];     ///< Texture File Name
    RwReal  fEdgeGap;                 ///< The value of whether Edge should be generated every few seconds
    RwInt32 nSplinePointCount;        ///< Spline���� �����ϴ� ���ؽ��� ���� (�ΰ��� Edge���̿� �����Ǵ� ���ؽ��� �����̴�)
    RwInt32 nMaxEdgeCount;            ///< �ִ� Edge Count    
    RwBlendFunction eSrcBlend;        ///< Src Blend State
    RwBlendFunction eDestBlend;       ///< Dest Blend State
    RwRGBA  colStartColor;            ///< ���� Color��
    RwRGBA  colEndColor;              ///< �� Color��   
    RwV3d   vOffset;                  ///< Offset from center point where trajectory will occur

    SNtlPrtStdEmitterTrail() : fEdgeLifeTime(0.3f),
                    fEdgeGap(0.003f),	// by daneos from 0.0 to 0.003
                    nSplinePointCount(10),
                    nMaxEdgeCount(500), // by daneos from 100 to 500
                    fMaxLength(1.0f),
                    fWidth(0.5f)
    {
        eSrcBlend = rwBLENDSRCALPHA;
        eDestBlend = rwBLENDONE;                       
        ZeroMemory(&vOffset, sizeof(RwV3d));
        colStartColor.red = colStartColor.green = colStartColor.blue = 255;
        colEndColor.red = colEndColor.green = colEndColor.blue = 255;
        colStartColor.alpha = 255;
        colEndColor.alpha = 0;
        ZeroMemory(strTexture, MAX_PATH);
    }
};

/// ����Ʈ ���� ����ü
struct SEffectSound
{
    RwChar	chSoundName[128]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
    RwChar	chSoundName2[128]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
    RwChar	chSoundName3[128]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
    RwChar	chSoundName4[128]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)    
    RwBool  bLoop;                              ///< Sound Loop ����
    RwReal  fSoundVolume;                       ///< Sound Volume
    RwReal  fSoundDist;                         ///< ��ȿ �Ÿ�
    RwReal  fSoundDecayDist;                    ///< ���� ���� �Ÿ�
    RwReal  fSoundPitchMin;                     ///< ���� ��ġ �ּҰ�    

    SEffectSound()
    {
        ZeroMemory(chSoundName, sizeof(chSoundName));
        ZeroMemory(chSoundName2, sizeof(chSoundName2));
        ZeroMemory(chSoundName3, sizeof(chSoundName3));
        ZeroMemory(chSoundName4, sizeof(chSoundName4));        
        bLoop = FALSE;
        fSoundVolume = 100.0f;
        fSoundDist = 4.0f;
        fSoundDecayDist = 18.0f;
        fSoundPitchMin = dNTLSOUND_PITCH_DEFAULT;        
    }
};

struct SEffectSoundEx : public SEffectSound
{
    RwReal fSoundPitchMax;

    SEffectSoundEx()
    {
        fSoundPitchMax = dNTLSOUND_PITCH_DEFAULT;
    }
};

/// ����Ʈ �ٿ�� ���Ǿ�
struct SEffectBoundingSphere
{
    RwBool      bDisableAuto;           ///< �ٿ�� ���Ǿ �������� �����Ҷ� True, False�� �ڵ������� �ٿ�� ���Ǿ� ���
    RwReal      fRadius;                ///< �ٿ�� ���Ǿ� ������. ���� �����϶��� ��ȿ

    SEffectBoundingSphere()
    {
        bDisableAuto = FALSE;
        fRadius = 5.0f;
    }
};

/**
* \ingroup NtlPresentation
* \brief LoopEffect List�� ���Ǵ� ����ü, Effect-Bone ������ �����ȴ�.
* \date 2006-08-21
* \author agebreak
*/
struct SLoopEffect
{
	CNtlInstanceEffect* pLoopEffectIntance;     ///< LoopEffect�� ������
	char*               szBoneName;             ///< LoopEffect�� �ٴ� Bone�� �̸�
};

typedef std::list<SLoopEffect*> ListLoopEffect;
typedef std::list<SOUND_HANDLE> ListSoundHandle;

/// �ٴڿ��� ǥ�õǴ� ����Ʈ �ý����� �����ϱ� ���� ����ü
struct SGroundFlag
{
    RwBool bGround;                             ///< ������ ���̿��� ǥ�õ����� ���� �÷���
    RwReal fOffsetY;                            ///< Y Offset ����

    SGroundFlag()
    {
        bGround = FALSE;
        fOffsetY = 0.0f;
    }
};

#endif