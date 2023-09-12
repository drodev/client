/*****************************************************************************
 *
 * File			: NtlLocalize.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2007. 3. 19	
 * Abstract		: Localizing�� ���� ����.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

//----------------------------------------
// DBO Launcher������ �Լ��� ���� ����
//----------------------------------------

// 1. Local_Init();
// 2. Local_DetectData();
// 3. Local_DBOEncryptConfig();
// 4. DBO Client ������ �� command�� DBO encrypt config data�� �־��ش�.
// 5. Local_Terminate();


//----------------------------------------
// DBO client ������ �Լ��� ���� ����
//----------------------------------------

// 1. Local_Init();
// 2. Local_DBODecryptConfig();  command������ ���� �־��ش�.
// 3. Local_Terminate();


#ifndef __NTL_LOCALIZE__
#define __NTL_LOCALIZE__

#include "NtlLocalizeDef.h"

void			Local_Init(void);
void			Local_Terminate(void);

unsigned char	Local_GetType(void);	
SLocalConfig*	Local_GetConfig(void);

// Localizing data ����.(launcher�� �Ѿ���� decrypt key)
bool			Local_DetectData(const char *pKey);


// DBO data make
const char*		Local_DBOEncryptConfig(void);
bool			Local_DBODecryptConfig(const char *pConfig);


#endif
