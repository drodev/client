/*****************************************************************************
 *
 * File			: NtlTimer
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 14	
 * Abstract		: NTL Timer
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef __NTL_TIMER__
#define __NTL_TIMER__


#define GETTIMESTAMP GetTickCount

/**
 * \ingroup Util
 * Time�� ��� �ϴ� �Լ� �̴�.
 *
 * 
 */
class CNtlTimer
{
public:

	static float m_fAppTime;
	static float m_fElapsedTime;
	static float m_fFps;
	
	enum TIMER_COMMAND 
	{ 
		TIMER_RESET, TIMER_START, TIMER_STOP, TIMER_ADVANCE,
		TIMER_GETABSOLUTETIME, TIMER_GETAPPTIME, TIMER_GETELAPSEDTIME
	};

	//  ���� �ǵ��� ����(����) �ǵ� �ʿ䰡 �ִ� ����� �ǳ��� ��...
private:

	static float __stdcall	DXUtil_Timer( TIMER_COMMAND command );
	static void __stdcall	UpdateFrame(float &fps);
	static void __stdcall	InterpolationElapsedTime(float fOldElapsedTime);

public:

	static void __stdcall	StartTimer(void);
	static void __stdcall	UpdateTimer(void);

	static float __stdcall	GetAppTime(void);
	static float __stdcall	GetElapsedTime(void);
	static float __stdcall	GetFps(void);

	static void __stdcall	ActiveInterpolation(bool bActive);

	static float __stdcall  AdjustBestFpsToSec(void);
};

#endif