#include "precomp_ntlcore.h"
#include "NtlBugTrap.h"
#include "NtlDebug.h"
#include "new.h"

void InvalidParameterHandler(const wchar_t* expression,
                             const wchar_t* function,
                             const wchar_t* file,
                             unsigned int line,
                             uintptr_t pReserved)
{
    throw NTL_NEW std::exception("InvalidParameterHandler");
}

void PurecallHandler(void)
{
    throw NTL_NEW std::exception("PurecallHandler");
}

int NewHandler( size_t )
{
    NTL_ASSERTFAIL("new Handler Fail!");
    throw NTL_NEW std::exception("NewHandler");
}

CNtlBugTrap::CNtlBugTrap(void)
{
    // Setup bug trapper
    // ����Ʈ���� ����� �� ���α׷����� �ٽ� �����ϸ� ����ȴ�.
    BT_SetAppName(_T("BugTrap Report"));    
    //BT_SetSupportEMail(_T("agebreak@ntl-inc.com"));
    BT_SetFlags(BTF_DETAILEDMODE | BTF_EDITMAIL | BTF_ATTACHREPORT | BTF_SCREENCAPTURE | BTF_INTERCEPTSUEF);
	//BT_SetFlags(BTF_NONE);
    BT_SetSupportURL(_T("https://dboglobal.to"));

    // BugTrapServer ===========================================
    //BT_SetSupportServer(_T("localhost"), 9999);    

    // C ǥ���Լ��� ���� �߸��� ���� ���
    _set_invalid_parameter_handler(InvalidParameterHandler);

    // �߸��� ���� �����Լ� ȣ��
    _set_purecall_handler(PurecallHandler);

    // �ʹ� ū �޸� �Ҵ� �� New �������� ����
    _set_new_handler( NewHandler );
}
