/*****************************************************************************
 * File			: JudgeDump.h
 * Author		: Hong Sungbock
 * Copyright	: (��)NTL
 * Date			: 2008. 11. 29
 * Abstract		: 
 *****************************************************************************
 * Desc			: �޼����� ���� �� �� �ִ��� ���θ� �Ǵ��Ͽ� �����ϸ� �޼�����
 *				  ��ȯ�Ѵ�
 *****************************************************************************/

#pragma once

enum eDUMP_TYPE
{
	DUMP_DEFAULT,			// Default Dump Message�� ��û�ϸ� ������ ����� �����ϴ�
	DUMP_ACTION,
	DUMP_SOB_CREATE_DESTROY,
	DUMP_FSM,
	DUMP_CONTENTS,

	NUM_DUMP
};


class CJudgeDump
{
public:
	CJudgeDump() {}
	virtual ~CJudgeDump() {}

	virtual char*			GetDump_SendPacket(void* pPacket) { return NULL; }
	virtual char*			GetDump_RecvPacket(void* pPacket) { return NULL; }
	virtual const char*		GetDump_Message(const RwChar* pcMessage) { return NULL; }
	virtual const char*		GetDump_Message(const WCHAR*  pwcMessage) { return NULL; }
};

class CJudgeDefaultDump : public CJudgeDump
{
public:
	CJudgeDefaultDump() {}
	virtual ~CJudgeDefaultDump() {}

	virtual const char*		GetDump_Message(const RwChar* pcMessage) { return pcMessage; }
	virtual const char*		GetDump_Message(const WCHAR*  pwcMessage);
};

class CJudgeActionDump : public CJudgeDump
{
public:
	CJudgeActionDump() {}
	virtual ~CJudgeActionDump() {}

	virtual char*			GetDump_SendPacket(void* pPacket);
	virtual char*			GetDump_RecvPacket(void* pPacket);
};

class CJudgeSobCreateDestoryDump : public CJudgeDump
{
public:
	CJudgeSobCreateDestoryDump() {}
	virtual ~CJudgeSobCreateDestoryDump() {}

	virtual char*			GetDump_RecvPacket(void* pPacket);
};

class CJudgeFSMDump : public CJudgeDump
{
public:
	CJudgeFSMDump() {}
	virtual ~CJudgeFSMDump() {}
};

class CJudgeContentsDump : public CJudgeDump
{
public:
	CJudgeContentsDump() {}
	virtual ~CJudgeContentsDump() {}
};