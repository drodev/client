/*****************************************************************************
 *
 * File			: NtlDebug.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 28	
 * Abstract		: memory / debug wrapping(RenderWare Studio ����).
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_DEBUG_H__
#define __NTL_DEBUG_H__

#include "debugmacros.h"
#include "memoryhandler.h"


/**
*
* \ingroup debugmacros
*
* debug �����ؼ� renderware studio�� macro�� wrapping.
* debugmacors.h/cpp�� ������ �ּ���.
* ASSERT �� Function Profiler�� ����.
*
*/

#define NTL_HEX(a)						RWS_HEX(a)
#define NTL_DEC(a)						RWS_DEC(a)
#define NTL_FIX(a, b)					RWS_FIX(a, b)
#define NTL_LEX(a)						RWS_LEX(a)
#define NTL_VALIDSTRING(a)				RWS_VALIDSTRING(a)


//#define NTL_DEBUGSTREAM_WARN(a)			RWS_DEBUGSTREAM_WARN(a)
//#define NTL_DEBUGSTREAM_ERR(a)			RWS_DEBUGSTREAM_ERR(a)
//#define NTL_TRACE_NO_FUNC(a)			RWS_TRACE_NO_FUNC(a)
//#define NTL_RWS_TRACEIF(cond, a)		RWS_RWS_TRACEIF(cond, a)


//////////////////////////////////////////////////////////////////////////
//							NTL assert macro							//
//////////////////////////////////////////////////////////////////////////

#define NTL_ASSERTFAIL(msg)					RWS_ASSERTFAIL(msg)
#define NTL_ASSERT(condition, msg)			RWS_ASSERT(condition, msg)
#define NTL_ASSERTE(condition)				RWS_ASSERTE(condition)

#define NTL_TABLE_ASSERT_FAIL(msg)			RWS_TABLE_ASSERT_FAIL(msg)
#define NTL_TABLE_ASSERT(condition, msg)	RWS_TABLE_ASSERT(condition, msg)
#define NTL_TABLE_ASSERTE(condition)		RWS_TABLE_ASSERTE(condition)

#define NTL_ARRAY_ASSERT_FAIL(msg)			DEBUG_ARRAY_ASSERT_FAIL(msg)
#define NTL_ARRAY_ASSERT(max, index, msg)	DEBUG_ARRAY_ASSERT(max, index, msg)
#define NTL_ARRAY_ASSERTE(max, index)		DEBUG_ARRAY_ASSERTE(max, index)

#define NTL_ARRAY_MIN_ASSERT_FAIL(msg)				DEBUG_ARRAY_MIN_ASSERT_FAIL(msg)
#define NTL_ARRAY_MIN_ASSERT(min, max, index, msg)	DEBUG_ARRAY_MIN_ASSERT(min, max, index, msg)
#define NTL_ARRAY_MIN_ASSERTE(min, max, index)		DEBUG_ARRAY_MIN_ASSERTE(min, max, index)


#define NTL_REGISTER_DEBUG_OUTPUT_CALLBACK(callback)			RWS_RESISTER_DEBUG_CALLBACK(callback)
#define NTL_UNREGISTER_DEBUG_OUTPUT_CALLBACK(callback)			RWS_UNRESISTER_DEBUG_CALLBACK(callback)


//////////////////////////////////////////////////////////////////////////
//							NTL warning macro							//
//////////////////////////////////////////////////////////////////////////

#define NTL_WARNING_MESSAGE(msg)			RWS_WARNING_MESSAGE(msg)
#define NTL_WARNING(condition, msg)			RWS_WARNING(condition, msg)
#define NTL_WARNINGE(condition)				RWS_WARNINGE(condition)

#define NTL_TABLE_WARNING_MESSAGE(msg)		RWS_TABLE_WARNING_MESSAGE(msg)
#define NTL_TABLE_WARNING(condition, msg)	RWS_TABLE_WARNING(condition, msg)
#define NTL_TABLE_WARNINGE(condition)		RWS_TABLE_WARNINGE(condition)


//////////////////////////////////////////////////////////////////////////
//							NTL trace macro								//
//////////////////////////////////////////////////////////////////////////

#define NTL_TRACE_MESSAGE(msg)				DEBUG_TRACE_MESSAGE(msg)
#define NTL_TRACE(condition, msg)			DEBUG_TRACE(condition, msg)
#define NTL_TRACEE(condition)				DEBUG_TRACEE(condition)


#define NTL_REGISTER_TRACE_OUTPUT_CALLBACK(callback)			RWS_RESISTER_TRACE_CALLBACK(callback)
#define NTL_UNREGISTER_TRACE_OUTPUT_CALLBACK(callback)			RWS_UNRESISTER_TRACE_CALLBACK(callback)



#define NTL_PRE(condition)				RWS_PRE(condition)
#define NTL_POST(condition)				RWS_POST(condition)


#define NTL_FUNCTION(a)					RWS_FUNCTION(a)
#define NTL_RETURN(_rwsreturnval)		RWS_RETURN(_rwsreturnval)
#define NTL_RETURNVOID()				RWS_RETURNVOID()

//#define NTL_FUNCTION(a)					
//#define NTL_RETURN(_rwsreturnval)		return _rwsreturnval
//#define NTL_RETURNVOID()				return;


/*********************************************************************
**	Assert�� trace�� ������ �����Ͽ� �۾��� �ߴ��� ���θ�
**  �Ǻ��ϱ� ���� ���� ��ũ�θ� �̿��Ͽ� �ֽʽÿ�.
**  �۾��� �Ϸ�Ǹ� �̸��� �ϰ������� �ٲٵ��� �ϰڽ��ϴ�.
**********************************************************************/

#define DBO_FAIL(msg)					NTL_ASSERTFAIL(msg)
#define DBO_ASSERT(condition, msg)		NTL_ASSERT(condition, msg)
#define DBO_ASSERTE(condition)			NTL_ASSERTE(condition)

#define DBO_TABLE_ASSERT_FAIL(msg)			NTL_TABLE_ASSERT_FAIL(msg)
#define DBO_TABLE_ASSERT(condition, msg)	NTL_TABLE_ASSERT(condition, msg)
#define DBO_TABLE_ASSERTE(condition)		NTL_TABLE_ASSERTE(condition)

#define DBO_ARRAY_ASSERT_FAIL(msg)			NTL_ARRAY_ASSERT_FAIL(msg)
#define DBO_ARRAY_ASSERT(max, index, msg)	NTL_ARRAY_ASSERT(max, index, msg)
#define DBO_ARRAY_ASSERTE(max, index)		NTL_ARRAY_ASSERTE(max, index)

#define DBO_ARRAY_MIN_ASSERT_FAIL(msg)				NTL_ARRAY_MIN_ASSERT_FAIL(msg)
#define DBO_ARRAY_MIN_ASSERT(min, max, index, msg)	NTL_ARRAY_MIN_ASSERT(min, max, index, msg)
#define DBO_ARRAY_MIN_ASSERTE(min, max, index)		NTL_ARRAY_MIN_ASSERTE(min, max, index)


#define DBO_REGISTER_DEBUG_OUTPUT_CALLBACK(callback)			NTL_REGISTER_DEBUG_OUTPUT_CALLBACK(callback)
#define DBO_UNREGISTER_DEBUG_OUTPUT_CALLBACK(callback)			NTL_UNREGISTER_DEBUG_OUTPUT_CALLBACK(callback)


// NTL warning macro
#define DBO_WARNING_MESSAGE(msg)			NTL_WARNING_MESSAGE(msg)
#define DBO_WARNING(condition, msg)			NTL_WARNING(condition, msg)
#define DBO_WARNINGE(condition)				NTL_WARNINGE(condition)

#define DBO_TABLE_WARNING_MESSAGE(msg)		NTL_TABLE_WARNING_MESSAGE(msg)
#define DBO_TABLE_WARNING(condition, msg)	NTL_TABLE_WARNING(condition, msg)
#define DBO_TABLE_WARNINGE(condition)		NTL_TABLE_WARNINGE(condition)


// NTL trace macro
#define DBO_TRACE_MESSAGE(msg)				NTL_TRACE_MESSAGE(msg)
#define DBO_TRACE(condition, msg)			NTL_TRACE(condition, msg)
#define DBO_TRACEE(condition)				NTL_TRACEE(condition)


#define DBO_REGISTER_TRACE_OUTPUT_CALLBACK(callback)			NTL_REGISTER_TRACE_OUTPUT_CALLBACK(callback)
#define DBO_UNREGISTER_TRACE_OUTPUT_CALLBACK(callback)			NTL_UNREGISTER_TRACE_OUTPUT_CALLBACK(callback)

/**
*
* \ingroup MemHandler
*
* memory �����ؼ� renderware studio�� macro�� wrapping.
* ��� ����� memoryhandelr.h/cpp�� ������ �ּ���.
* RenderWare Studio������ new, delete operator �����ڸ� ������ �ϰ� ������, memory profiler ����� �����ȴ�.
* ���������� malloc �Լ��� ����Ѵ�.
* ���� macro NTL_OP_NEW, NTL_NEW, NTL_OP_NEW_TYPE, NTL_NEW_TYPE �� new �����ڸ� ����ϰ� ������, 
* __FILE__ , __LINE__ , Memory type���� momery profiler�� �ΰ����� ������ �߰��ϵ��� �Ǿ� �ִ�.
* memory type���� RWS_MEMORY_TYPE_RW, RWS_MEMORY_TYPE_STD, RWS_MEMORY_TYPE_RWS, RWS_MEMORY_TYPE_USER ���� 
* �����ǰ� �ִµ�, ����� �Ӹ��ƴ϶� ����ϴ� �Լ��� �ٸ���.
* RWS_MEMORY_TYPE_RW => RenderWare allocations �� RwMalloc, RwCalloc and RwRealloc functions�� ����Ѵ�.
* RWS_MEMORY_TYPE_STD => standard memory allocations, via the global operator new �� ����Ѵ�.
* RWS_MEMORY_TYPE_RWS => standard memory allocations, via the global operator new �� ����ϰ�, 'RWS_NEW' and 'RWS_OP_NEW'
*						 macro�� ���ȴ�.	
* RWS_MEMORY_TYPE_USER => standard memory allocations, via the global operator new �� ����ϰ�, 'NTL_NEW_TYPE' and 'NTL_OP_NEW_TYPE'
*						 macro�� ���ȴ�.	
*
*/


/*
// RWS_MEMORY_TYPE_RW ���ڷ� ���ȴ�.
void *RWSMalloc(size_t size, RwUInt32 hint);
void RWSFree(void *pMem);
void *RWSReAlloc(void *pMem, size_t newSize, RwUInt32 hint);
void *RWSCalloc(size_t num, size_t size, RwUInt32 hint);
*/

/**
* \ingroup MemHandler
* ============= ����� =============
* int *pTemp = NTL_NEW int;
* int *pTemp = NTL_NEW int[10];
* ====================================
*/

#define NTL_NEW							RWS_NEW

// by agebreak
#define NTL_DELETE( p )					RWS_DELETE( p )
#define NTL_ARRAY_DELETE( p )			RWS_ARRAY_DELETE( p )

#define B2b(val) (val ? true : false)           ///< BOOL���� bool������ �����Ѵ�.


#endif

