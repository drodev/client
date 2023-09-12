////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ŀ���� ���� Ÿ�� Ÿ�� �������̼� �Դϴ�.
// �ϴ� ���ø�, ���߻�� ���� �ȉ���ϴ�. �Ϲ� ��� �Ϻ� �����Ǳ���
// ���� ������ ���� �ڵ� ���ø� �̱���
// ��Ʈ�� ���ؼ� �����ϴ°Ŵϱ� �ǽð��� ���� ���ñ���
// ������ �ؿ� ������
//
// �켱 ��������� ������ ���� ���ֱ��� mfc�� ����մϴ�.
//   
//
/*
class Cȣ��
{
	NTL_RTTI_SYSTEM_DECL;
};

class C���� : public Cȣ��
{
	NTL_RTTI_SYSTEM_DECL;

	void ȣ��������();
};

class C��� : public Cȣ��
{
	NTL_RTTI_SYSTEM_DECL;

	void �쵿���ٺ�();
};

class C��ö : public Cȣ��
{
	NTL_RTTI_SYSTEM_DECL;

	void �ǳ������������Ӷ�׷�();
};
*/
// �����ο����� ������ ���� ���ݴϴ�.
//
// �츮�� �쵿���� �θ�� ��� �޾Ҵٰ� �մϴ�.
//
// NTL_RTTI_SYSTEM_IMPL_NOPARENT(Cȣ��);
// NTL_RTTI_SYSTEM_IMPL(C����, Cȣ��);
// NTL_RTTI_SYSTEM_IMPL(C���, Cȣ��);
// NTL_RTTI_SYSTEM_IMPL(C��ö, Cȣ��);


// �̷��� �س�����
// Cȣ�� *pATM1 = new C����;
// Cȣ�� *pATM2 = new C���;
// Cȣ�� *pATM3 = new C��ö;
//
// ���� �̷��� �ǰ��� �״㿡 �ǽð��� ������ ȣ�������Ͱ� ������ �˾Ƴ�����
// ������ �����ϴ�.
//
// void Onȣ�����L��ưŬ��()
//{
//
//	// ���� ȣ�� �����Ͱ� ��ö �������� �˷���
//	if(pATM->GetCRTTIS().DerivesFrom(C��ö::s_CRTTIS))
//  {
//      // �׸��� ���⼭ Ÿ�� ĳ��Ʈ �ϰ� ��ö���� �Լ��� �θ��ϴ�.
//      reinterpret_cast<C��ö*>(pATM3)->�ǳ������������Ӷ�׷�();
//	    
//      // �̷��� �˴ϴ�.
//  }
//
//}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NTL_RTTI_SYSTEM_DECL \
public:\
	virtual const CNtlRTTI& GetCRTTIS() const { return s_CRTTIS; }\
	static const CNtlRTTI s_CRTTIS;

#define NTL_RTTI_SYSTEM_IMPL_NOPARENT(name) \
const CNtlRTTI name::s_CRTTIS(#name);

#define NTL_RTTI_SYSTEM_IMPL(name, parent) \
const CNtlRTTI name::s_CRTTIS(#name, parent::s_CRTTIS);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlRTTI
{
public:
	CNtlRTTI(const std::string& className);
	CNtlRTTI(const std::string& className, const CNtlRTTI& baseRTTI);

public:
    const std::string& GetClassName() const;
    bool IsExactly(const CNtlRTTI& rtti) const;
    bool DerivesFrom(const CNtlRTTI& rtti) const;

private:
    CNtlRTTI(const CNtlRTTI& obj);
    CNtlRTTI& operator = (const CNtlRTTI& obj);
	
private:
    const std::string m_className;
    const CNtlRTTI *m_pBaseRTTI;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////