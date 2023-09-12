/*****************************************************************************
 *
 * File			: NtlCoreUtil.h
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 14	
 * Abstract		: NTl CoreUtil Function
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef _NTL_CORE_UTIL_
#define _NTL_CORE_UTIL_

#include "rwcore.h"


#define NTL_MAX_DIR_PATH	512	


extern float g_fElapsedTime;


void  g_SetElapsedTime(float fElapsedTime);
float g_GetElapsedTime();

//------------------------------------------------------------------------------
// file attribute ���� util function
//------------------------------------------------------------------------------

void NtlFileAttrReadOnlyRelease(const RwChar *pFileName);

RwUInt32 NtlGetFileSize(const RwChar *pFileName);	

RwBool DeleteFolder(const RwChar* strFolder);


//------------------------------------------------------------------------------
// log file util function
//------------------------------------------------------------------------------

// log file name�� �����Ѵ�.
void NtlLogFilePath(RwChar *pFilePath);

// logfile print �Լ�.
void NtlLogFilePrint(RwChar *pLog);
void NtlLogFilePrintArgs(RwChar *fmt, ... );

void NtlTraceEnable_inRelease(bool bEnable);

// trace file name�� �����Ѵ�.
void NtlTraceInitFilePath();
void NtlTraceInitFilePath(RwChar *pFilePath);

// logfile print �Լ�.
void NtlTraceFilePrint(RwChar *pLog);
void NtlTraceFilePrintArgs(RwChar *fmt, ... );


//------------------------------------------------------------------------------
// error handler function
//------------------------------------------------------------------------------

typedef void(*fpFuncLastErrorHandler)(const RwChar *pError);

void LinkLastErrorHandler(fpFuncLastErrorHandler fp);
void UnLinkLastErrorHandler(void);

void NtlSetLastError(const RwChar *pError);

//------------------------------------------------------------------------------
// error handler function
//------------------------------------------------------------------------------

bool HaveMagicKeyword(const char* pcFileName, const char* pcKeyword);

//------------------------------------------------------------------------------
// System Info
//------------------------------------------------------------------------------

bool GetSystemMemorySize(unsigned __int64* pMemorySizeAvailPhys, unsigned __int64* pMemorySizeTotalPhys, unsigned __int64* pMemorySizeAvailVirtual, unsigned __int64* pMemorySizeTotalVirtual, unsigned __int64* pMemorySizeAvailPageFile, unsigned __int64* pMemorySizeTotalPageFile);
bool GetVideoMemorySize(DWORD* pMemorySizeAvail, DWORD* pMemorySizeTotal);

#endif


