//***********************************************************************************
//	File		:	NtlStringUtil.h
//	Desc		:	
//	Begin		:	2007. 4. 4
//	Author		:	avooo
//	Update		:	
//***********************************************************************************

#pragma once


// �Է¹��� ��Ʈ���� char�� ����Ʈ ���� ��ȯ�Ѵ�
// wchar_t ���� ��� ���ڰ� 2����Ʈ������ �� char ���� 1~3 ����Ʈ�� �������̴�.
// �������� �����ϴ� ���ڿ��� ����(byte)�� ���߱� ���� ���ڿ��� �� ����Ʈ�ΰ� �˾ƺ��� ���� ����

// ���ڸ� char ������ �޴´ٸ� �Ϻ� ���ڸ� ����� �ν����� ���Ѵ�
// ��) �� : �����δ� 2����Ʈ�̳� �ν��� ���� ?�� ��ȯ�ǰ� 1����Ʈ�� �νĵȴ�
RwUInt32 GetByte(const wchar_t* pwcText);


// �Է¹��� ���ڰ� ���ڸ� �������� �˾ƺ���
RwInt32 GetNumberLength(RwInt32 iNumber);
RwInt32 GetNumberLength(RwUInt32 uiNumber);


// �Է¹��� ���������� ���� ��Ʈ���� ����� ��ȯ�Ѵ�
// ��) MakeStr("�ڽ��ǰ� %f%s ���� %f����Ʈ�� �����߽��ϴ�", 23.3, "����Ʈ", 2003.23);
char* MakeStr(char* pcText, ...);

void		StringTokenize(std::vector<std::string>& strOutToken, const std::string& strText, const std::string& strToken);
std::string StringReplace(const std::string& strText, const std::string& strSrc, const std::string& strReplace);