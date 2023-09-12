/****************************************************************************
* File			: DboScriptLinkDef.h
* Author		: HaeSung, Cho
* Copyright		: (��)NTL
* Date			: 2008. 5. 26	
* Abstract		: DBO �� ��ũ��Ʈ ��ũ ���̺��� ���ǵ� ID��
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __DBO_SCRIPT_LINK_DEF_H___
#define __DBO_SCRIPT_LINK_DEF_H___

// ����� �������� Ÿ��
enum eScriptLinkType
{
	eLINKTYPE_TENKAICHIBUDOKAI = 0,
	eLINKTYPE_TIMEMACHINEQUEST,
	eLINKTYPE_RANKBATTLE,

	eLINKTYPE_NUMS,
	eLINKTYPE_INVALID = 0xFF
};

// õ�����Ϲ���ȸ�� �׼� �ѹ�
enum eTenKaichiBudokaiAction
{
	eBUDOKAI_NEWSMAIN = 0,					///< �ҽ��� NEWS ������ ����.
	eBUDOKAI_REQUEST,						///< ��û�� UI�� ����.
	eBUDOKAI_TOURNAMENT,					///< ��ʸ�Ʈ ����ǥ ����
	eBUDOKAI_HTML,							///< ���� HTML ����
	eBUDOKAI_CLOSE,							///< �������̽� �ݱ�

	eBUDOKAI_NUMS,
	eBUDOKAI_INVALID = 0xFF
};

#endif
