// SSOWebLib.h: interface for the CSSOWebLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSOWEBLIB_H__B6EC3473_CBDF_4B60_8B92_75E4962873EE__INCLUDED_)
#define AFX_SSOWEBLIB_H__B6EC3473_CBDF_4B60_8B92_75E4962873EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////
typedef void* HWEBCTRL;

typedef void (SWEBCALLBACK_ONBN2)(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, LPCTSTR lpszPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
typedef void (SWEBCALLBACK_ONNC2)(LPCTSTR strURL);
typedef void (SWEBCALLBACK_ONQUIT)();

// SSO ���������� Shared DLL�� ����ϱ� ���� ȣ���ϴ� �Լ�(InitSSOWebBrowser() ������ ȣ��Ǿ�� ��)
void PresetSSOWebBrowserToSharedDll();

// ���� ����Ʈ�� ���� ��Ű �̸��� �����ϱ� ���Ͽ� ȣ���ϴ� �Լ�(InitSSOWebBrowser() ������ ȣ��Ǿ�� ��)
// ���������� ��� "daum"�� �ѱ�(�ݸ����� ���� ȣ���� �ʿ䰡 ����)
void PresetSSOWebBrowserSetSiteName(LPCTSTR strSiteName);

void PresetSSOWebBrowserBaseFolder(LPCTSTR strFolder);

// SSO �������� �ʱ�ȭ �Լ�
BOOL InitSSOWebBrowser(HWND hWndMain, LPCTSTR strAuthCookie, LPCTSTR strDataCookie, LPCTSTR strCpCookie);

// �׽�Ʈ�� �ʱ�ȭ �Լ�
BOOL InitSSOWebBrowser2(LPCSTR strBaseDir, HWND hWndMain, LPCTSTR strAuthCookie, LPCTSTR strDataCookie, LPCTSTR strCpCookie);

// SSO �������� �ı� �Լ�(���� �����찡 �ı��Ǳ� ���� ȣ���ؾ��Ѵ�)
BOOL UnInitSSOWebBrowser();

// ��Ű Ȱ��ȭ ������ URL�� ��� �Լ�
LPCTSTR GetActCookieURL();

// ��Ű �������� ������ URL�� ��� �Լ�
LPCTSTR GetRefreshCookieURL();

// SSO ���������κ��� ��Ű�� ��� �Լ�(���������� ��ȯ�Ǳ� ������ ���� �״�� put_cookie�ϸ� �ȴ�)
BOOL GetSSOWebCookieString(LPSTR pstrAuth, LPSTR pstrData, LPSTR pstrCp);

//////////////////////////////////////////////////////////////////////
// SSO �������� Ŭ����

class CSSOWebBrowser  
{
public:

	HWEBCTRL		m_hWeb;

	CSSOWebBrowser();
	virtual ~CSSOWebBrowser();

	// �� ������ �ʱ�ȭ �� ����
	BOOL Create(DWORD dwStyle, RECT& rect, HWND hWndParent, UINT nID);
	void Destroy();

	void SetOption(BOOL bHideBorder);
	BOOL PutCharSet(LPCTSTR strCharset);
	BOOL InsertHTML(LPCTSTR strHtml);
	BOOL ExecJavascript(LPCTSTR strScript);

	BOOL Navigate(LPCTSTR strURL);
	BOOL GetNetmarbleCookie(LPSTR pstrAuthCookie, LPSTR pstrDataCookie, LPSTR pstrCpCookie);

	void* GetWnd();
	int  GetUserNavigatedCount();
	void SetUserNavigatedCount(int count);
	void ResetUserNavigatedCount();

	static HMODULE	m_hDllModule;
	static BOOL		m_bInitialized;

	//virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	//virtual void OnNavigateComplete2( LPCTSTR strURL );
	//virtual void OnQuit();

	// �ݹ� �Լ�
	//void (*m_pCallback_OnBeforeNavigate2)(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, void* pbaPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	//void (*m_pCallback_OnNavigateComplete2)( LPCTSTR strURL );
	//void (*m_pCallback_OnQuit)();

	void SetCallback_OnBeforeNavigate2(SWEBCALLBACK_ONBN2* pCallback);
	void SetCallback_OnNavigateComplete2(SWEBCALLBACK_ONNC2* pCallback);
	void SetCallback_OnQuit(SWEBCALLBACK_ONQUIT* pCallback);
};

#endif // !defined(AFX_SSOWEBLIB_H__B6EC3473_CBDF_4B60_8B92_75E4962873EE__INCLUDED_)
