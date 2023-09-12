/*****************************************************************************
 *
 * File			: NtlLocalizeDef.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2007. 3. 19	
 * Abstract		: Localizing�� ���� ����.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_LOCALIZEDEF__
#define __NTL_LOCALIZEDEF__


//-------------------------------------------------------------------------
// Localizing �ν��� ���� 
//-------------------------------------------------------------------------

// localize tupe.
#define NTL_LOCALIZE_DEV			0x01		// ������
#define NTL_LOCALIZE_GLOBAL			0x02		// ������

// localize config data
#define MAX_LOCAL_ADDR				32
#define MAX_LOCAL_USER_IDPW			32
#define MAX_CP_DATA					2048

union UCPData
{
	char chData[MAX_CP_DATA];
	char chCJData[MAX_CP_DATA];
};

typedef struct _SLocalConfig
{
	unsigned char	byLocalType;
	char			chAddr[MAX_LOCAL_ADDR];
	unsigned int	uiPort;
	UCPData			uCP;
}SLocalConfig;




#endif