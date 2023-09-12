#pragma once

#include "NtlXMLDoc.h"

// ��ǳ�� ����ü
struct STeleCastBalloon
{
    RwV2d v2dOffset;
    RwV2d v2dSize;
    std::string strFileName;

    STeleCastBalloon()
    {
        ZeroMemory(&v2dOffset, sizeof(RwV2d));
        ZeroMemory(&v2dSize, sizeof(RwV2d));
    }
};

// ��� Ÿ���� ���â�� �θ��� ����
enum TELECAST_TYPE
{
    TELECAST_TYPE_TMQ,                  
    TELECAST_TYPE_TUTORIAL,
    TELECAST_TYPE_SERVER_NOTIFY,
};

/// Telecast���� UIConfig ����ü
struct SUIConfigTeleCast
{
    TELECAST_TYPE           m_eTelecastType; ///< ������ ������ ���â Ÿ��
    RwInt32     nYPos;                      ///< Y ��ġ
    RwV2d       v2dSize;                    ///< ũ��
    RwReal      fFadeTime;                  ///< Fade ���⿡ �ɸ��� Time
    std::string strFadeFlashFile;           ///< Fade ���� �÷��� ���ϸ�
    std::string strOpeningFlashFile;        ///< Open ���� �÷��� ���ϸ�
    std::string strClosingFlashFile;        ///< Close ���� �÷��� ���ϸ�
    std::string strBackNormalFlashFile;     ///< �Ϲݻ��� ��� �÷��� ���ϸ�
    std::string strBackWarnFlashFile;       ///< ���/���� ���� ��� �÷��� ���ϸ�
    RwReal      fShakeFreq;                 ///< Shake ����� �ʴ� ������
    RwInt32     nShakeAmp;                  ///< Shake ����� ���� (�ȼ� ����)    
    std::map<RwInt32, STeleCastBalloon>  mapBalloonRes; ///< ��ǳ�� ���ҽ� ���ϸ� ��
    RwReal      fSlideStartVel;             ///< �����̵� ���� �ӵ�
    RwReal      fSlideAccel;                ///< �����̵� ���ӵ�
    
    RwUInt32    uiNPCID;                    ///< NPC ���̺� ID (���� �˸�â������ ���)
    RwReal      fShowTime;                  ///< ǥ�õ� �ð� (���� �˸�â������ ���)
    
    SUIConfigTeleCast() 
    : fShakeFreq(0), nShakeAmp(0), nYPos(578), fFadeTime(5.0f), m_eTelecastType(TELECAST_TYPE_TMQ)
    {        
        v2dSize.x = 235.0f;
        v2dSize.y = 176.0f;
        fSlideStartVel = 50.0f;
        fSlideAccel = 20.0f;        
    }
};

#define dBROADCAST_SHAKE_TYPE_NUMS	3

/**
* \brief BroadCast UIConfig
*/
struct SUIConfigBroadCast
{
	RwReal		fPosXRate;									///< X Pos Rate
	RwReal		fPosYRate;									///< Y Pos Rate
	RwReal		fSlideStartVel;								///< Sliding : ���� �ӵ�
	RwReal		fSlideAccelVel;								///< Sliding : ���ӵ�
	RwReal		fBlendStartVel;								///< UI Blending : ���� �ӵ�
	RwReal		fBlendAccelVel;								///< UI Blending : ���ӵ�
	RwReal		fBlendTextStartVel;							///< Blend text �ؽ�Ʈ : ���� �ӵ�
	RwReal		fBlendTextAccelVel;							///< Blend text : ���ӵ�
	RwReal		fIntervalTextTime;							///< Line : ������Ʈ Ÿ��
	RwReal		fIntervalPresNum;							///< Line : �ѹ��� ��Ÿ�� ���� ��
	RwReal		fFadeSlidePos;								///< Fade-Slide : ���� OffsetX
	RwReal		fFadeSlideStartVel;							///< Fade-Slide : ���� �ӵ�
	RwReal		fFadeSlideAccelVel;							///< Fade-Slide : ���ӵ�
	RwReal		fShakeXAmp[dBROADCAST_SHAKE_TYPE_NUMS];		///< ShakeX : ������ ��
	RwReal		fShakeXFreq[dBROADCAST_SHAKE_TYPE_NUMS];	///< ShakeX : ������ �ӵ�
	RwReal		fShakeYAmp[dBROADCAST_SHAKE_TYPE_NUMS];		///< ShakeY : ������ ��
	RwReal		fShakeYFreq[dBROADCAST_SHAKE_TYPE_NUMS];	///< ShakeY : ������ �ӵ�
};

// Notify ���� ����ü
struct SUIConfigNotifyPosition
{
	SUIConfigNotifyPosition(VOID)
	{
		fActionNotify_YPosRate = 0.215f;
		fPublicNotify_YPosRate = 0.123f;
		fTerritoryNotify_YPosRate = 0.345f;
		fCautionNotiry_YPosRate = 0.293f;
		fGroupNotiry_YPosRate = .7f;
		fNameNotiry_YPosRate = .6f;
		fBroadcastNotiry_YPosRate = 0.345f;
	}

	RwReal		fActionNotify_YPosRate;						///< YPos / 768; 
	RwReal		fPublicNotify_YPosRate;				
	RwReal		fTerritoryNotify_YPosRate;
	RwReal		fCautionNotiry_YPosRate;
	RwReal		fGroupNotiry_YPosRate;
	RwReal		fNameNotiry_YPosRate;
	RwReal		fBroadcastNotiry_YPosRate;
};

/// /script/UIConfig.XML �κ��� UI �������� �о�ͼ� �����ϰ� �ִ� �̱��� Ŭ����
class CDBOUIConfig : CNtlXMLDoc
{
public:
    CDBOUIConfig(void);
    ~CDBOUIConfig(void);

    RwBool Load();                              ///< Read Config information from XML file.
    RwBool Reflash();                           ///< Reloads the information from the XML file.

    RwBool LoadTeleCast(TELECAST_TYPE eType);   ///< TeleCast�� �������� �ε��Ѵ�.    
	RwBool LoadBroadCast();						///< BroadCast�� ���� �ε�
	RwBool LoadNotify();					

    SUIConfigTeleCast*  GetTeleCastConfig()		{	return &m_TeleCast;		} ///< TeleCast�� Config ������ ��ȯ�Ѵ�.
	SUIConfigBroadCast*	GetBroadCastConfig()	{	return &m_BroadCast;	}
	SUIConfigNotifyPosition* GetNotifyConfig()	{	return &m_Notify; }

protected:    
    RwBool LoadTest();                          ///< �׽�Ʈ�� �����͵��� �ε��Ѵ�.

protected:    
    char   szBuf[64];                           ///< ��� ����

    SUIConfigTeleCast       m_TeleCast;         ///< Telecast�� ���� ��ü
	SUIConfigBroadCast		m_BroadCast;		///< BroadCast
	SUIConfigNotifyPosition	m_Notify;			///< Notify
    
    RwReal                  m_fCameraTargetRatio; ///< Follow Camera�� Ÿ�� ���� ���� (ĳ������ Ű�� ���� ����) - �׽�Ʈ��
  
};
