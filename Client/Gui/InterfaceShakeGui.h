/*****************************************************************************
 *
 * File			: InterfaceShakeGui.h
 * Author		: Haesung, Cho
 * Copyright	: (��)NTL
 * Date			: 2007. 12. 10	
 * Abstract		: DBO KnockDown Recovery UI(WAKE UP GUI).
 *****************************************************************************
 * Desc         : 
 * 1. �˴ٿ� ���� �� UI�� ���� �Ѵ�.
 * 2. ProgressBar�� �ϳ� �߸� �� ���� �˴ٿ��� ȸ���ȴ�. (�ּ� 4�ʿ��� 8�� ����)
 * 3. ���콺�� �¿�� ��� �� �������� ���� �Ѵ�.
 * 4. Ű������ �¿� ����Ű �Է��� �޾ƾ� �Ѵ�. (InputActionMap)
 * 5. ���콺�� ���� �ӵ��� Ű������ �Է� �ӵ��� �˸°� ���� �Ѵ�.
 *
 * Todo : ���� Ű����� ���ܵ� ��Ȳ, �Ŀ� Ű���尡 ���Եȴٰ� �ϸ� �ּ��� �� ����� �ȴ�.
 * (script ����)
 *****************************************************************************/

#ifndef __INTERFACE_SHAKE_H__
#define __INTERFACE_SHAKE_H__

#include "NtlPLGui.h"
#include "ceventhandler.h"
 
// Define
#define dSHAKE_MAX_WAKEUP 8.0f		// WakeUp UI�� �ִ� �ð�
#define dSHAKE_MIN_WAKEUP 4.0f		// WakeUp UI�� �ּ� �ð�

#define dSHAKE_MOVE_DISTANCE 0		// ���콺�� ������ �ּ� �Ÿ�

#define dSHAKE_MOUSE_LEFT_X		55		// ���콺�� �������� �������� �� �̵��� ���콺 �̹����� ��ġ
#define dSHAKE_MOUSE_RIGHT_X	70		// ���콺�� ���������� �������� �� �̵��� ���콺 �̹����� ��ġ

#define dSHAKE_MOUSE_Y			48		// ���콺�� ����

// File Locate
#define dSHAKE_FILE_SURFACE "gui\\InterfaceShakeGui.srf"
#define dSHAKE_FILE_FRAME "gui\\InterfaceShakeGui.frm"

/**
* �̵��� �޴� �ð����� Define (ù��° �ð��� �ι�° �ð����� ����� �Ѵ�.)
* ù��° �ð�	: +3
* �ι�° �ð�	: +2
* �׿�			: +1
*/
#define dSHAKE_MOUSE_FIRSTTIME 0.3f		// ���콺: �̵��� ���� �� �ִ� ù��° �ð�
#define dSHAKE_MOUSE_SECONDTIME 0.5f	// ���콺: �̵��� ���� �� �ִ� �ι�° �ð�
#define dSHAKE_KEYBOARD_FIRSTTIME 0.1f	// Ű����
#define dSHAKE_KEYBOARD_SECONDTIME 0.3f	// Ű����

/**
* �̵��� �޴� ��ġ
*/
#define dSHAKE_ADVANTAGE_FIRST	3		// ù��° �ð� ��
#define dSHAKE_ADVANTAGE_SECOND	2		// �ι�° �ð� ��
#define dSHAKE_ADVANTAGE_THIRD	1		// �׿�

/**
* \ingroup client
* \brief �������̽� ����(WakeUp GUI)
* ���� ���� ĳ���Ͱ� ��-�ٿ� �Ǿ��� �� ������ ���콺 �̵����� �� �� ���� �ð�����
* �˴ٿ� ���°� ȸ���� �� �ְ� �Ѵ�.
*/
class CInterfaceShakeGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CInterfaceShakeGui( const RwChar* pName );
	virtual ~CInterfaceShakeGui();

	// Create & Destroy
	RwBool		Create();
	VOID		Destroy();

	// HandleEvents & SwitchDialog
	VOID		HandleEvents(RWS::CMsg &msg);
	RwInt32		SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close

	// Update
	VOID		Update( RwReal fElapsed );
	VOID		ProgressUpdateFromMouse();
	VOID		ProgressUpdateFromKeyboard();

	// Interface
	VOID		ShowInterface( VOID );			///< WakeUp Gui �� �ٿ��.
	VOID		CloseInterface( VOID );			///< �ݴ´�.

	// CallBack
	VOID		OnKeyDown( gui::CComponent* pComponent, CInputDevice* pDevice, const CKey& key);
	VOID		OnKeyUp( gui::CComponent* pComponent, CInputDevice* pDevice, const CKey& key);
	
protected:
	gui::CProgressBar*	m_pPgbTrack;		///< Track
	gui::CPanel*		m_pPanTrack;		///< Track Panel
	gui::CFlash*		m_pFlashLeftArrow;	///< LeftArrow Flash
	gui::CFlash*		m_pFlashRightArrow;	///< RightArrow Flash
	gui::CFlash*		m_pFlashMouseBack;	///< MouseBack Flash
	gui::CButton*		m_pBtnLeftKey;		///< Left Key
	gui::CButton*		m_pBtnRightKey;		///< Right Key
	gui::CStaticBox*	m_pStbMouse;		///< Mouse Static Box
		
	gui::CSlot	m_slotKeyDown;				///< KeyDown Signal
	gui::CSlot	m_slotKeyUp;				///< KeyUp Signal

	RwInt32		m_nOldMouseX;				///< Old Mouse X ��ǥ
	RwInt32		m_nMouseX;					///< ���ο� Mouse X ��ǥ
	RwInt32		m_nOffsetX;					///<  ���콺 X ��ǥ�� �̵��� �Ÿ� ( -, + )
	RwInt32		m_nTrackValue;				///< ProgressBar�� ��ġ
	RwInt32		m_nTrackMax;				///< Track�� �ִ� ����
	RwInt32		m_nTrackMin;				///< Track�� �ּ� ����

	RwBool		m_bMouseToggle;				///< ���콺�� ����, ������ (TRUE, FALSE)
	RwBool		m_bKeyToggle;				///< Ű�� ����, ������ (TRUE, FALSE)
	RwBool		m_bComplete;				///< ȸ�� ��������

	RwReal		m_fElapsedTime;				///< UI�� �ɸ� �ð�
	RwReal		m_fShakeElapsedTime;		///< ���콺�� �ѹ� �����ɶ� �ɸ� �ð�
	RwReal		m_fKeyDownElapsedTime;		///< Ű����� �ѹ� �����ɶ� �ɸ� �ð�
	RwReal		m_fElapsedShakeTime;		///< ���� Ÿ��

	RwUInt32	m_dwLeftKey;				///< ActionMap�� �¿� ����Ű
	RwUInt32	m_dwRightKey;
};
 
#endif