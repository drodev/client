#pragma once

#include "DboGlobal.h"

/// DBO ���� ���Ǳ׹� ��ũ��Ʈ ���ϵ��� ��ȣȭ/��ȣȭ �ϴ� Ŭ����
class CDBOEncrypter
{
public:
    CDBOEncrypter();
    ~CDBOEncrypter();    

    // ConfigOptions.Xml 
    RwBool  EncryptConfig(const RwChar* szFilePath);                 ///< Config ������ Encrypt�Ѵ�.
    RwBool  DecryptConfig(OUT SConfigData* pConfigData, const RwChar* szFilePath);                 ///< Config ������ Decrypt�Ѵ�.

    // Lua ������ 
    RwBool  CompileLuaFiles();                                      ///< Script �����ȿ� �ִ� ��� Lua ���ϵ��� �������Ѵ�.

protected:    
    

    // ConfigOptions.Xml 
    RwBool LoadConfigOptions(OUT SConfigData* pConfigData, const RwChar* szFilePath);             ///< Config ������ Load �Ѵ�.
    RwBool SaveConfigOptions(SConfigData* pConfigData, const RwChar* szDestPath, const RwChar* szCryptPassword);

protected:

};

static CDBOEncrypter* GetDBOEncrypter()
{
    static CDBOEncrypter dboEnctyper;

    return &dboEnctyper;
}