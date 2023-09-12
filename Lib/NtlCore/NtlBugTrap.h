#pragma once

#include "BugTrap.h"

#ifdef _UNICODE
#pragma comment(lib, "BugTrapU.lib")  // Link to Unicode DLL
#else
#pragma comment(lib, "BugTrap.lib")      // Link to ANSI DLL
#endif

/**
 * \ingroup NtlCore
 * \brief BugTrap�� �̿��ϴ� Ŭ���� (http://www.codeproject.com/tools/BugTrap.asp)
 * �� ����� Include�ϸ� ���α׷��� ������ ����Ʈ���� ����ȴ�.
 * ��� �޽����� �����ϱ� ���ؼ��� cpp ������ �ּ��� �����Ѵ�.
 * \date 2006-12-08
 * \author agebreak
 */
class CNtlBugTrap
{
public:
    CNtlBugTrap(void);    
};

static CNtlBugTrap g_dumpTrap; 