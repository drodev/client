#pragma once

#include "NtlWorldConceptController.h"

class CNtlPLCharacter;
class CNtlPLEntity;

/**
 * \ingroup NtlSimulation
 * \brief PVP�� �Ҷ��� ���� Ŭ���� 
 * \date 2007-06-14
 * \author agebreak
 */
class CNtlWorldConceptPVP : public CNtlWorldConceptController
{
public:
	CNtlWorldConceptPVP(void);
	~CNtlWorldConceptPVP(void);

	virtual void	Update(RwReal fElapsedTime);	
	virtual void	ChangeState(RwInt32 iState);

	//---- PVP ���� �޼ҵ�
	void				SetFreePvPTarget(SERIAL_HANDLE hTarget);					///< PVP Ÿ���� �����Ѵ�.
	SERIAL_HANDLE		GetFreePvPTarget(void) const;								///< ���� ������ PVP Target�� Serail ID�� ��ȯ�Ѵ�.

	void				SetFreePvPReferPos(RwV3d vPos);
	RwV3d				GetFreePvPReferPos(void) const;

	void				CreateFreePvPMark(void);							///< PVP ��ũ(����� ����)�� �����Ѵ�.
	void				DestroyFreePvPMark(void);							///< PVP ��ũ�� �����Ѵ�.

	void				SetPvpName(SERIAL_HANDLE hTarget);

protected:
	/// PVP ���� ���� ����ü
	struct FreeBattleInfo
	{
		CNtlPLCharacter		*pCharacter;
        CNtlPLEntity*       pBoundEffect;
		SERIAL_HANDLE		hFreePvPTarget;
		RwV3d				vFreePvPPos;
	};

protected:
	FreeBattleInfo		m_FreeBattleInfo;		///< PVP ���� ����ü
};


// �ζ��� �Լ���

inline void	CNtlWorldConceptPVP::SetFreePvPTarget(SERIAL_HANDLE hTarget)
{
	m_FreeBattleInfo.hFreePvPTarget = hTarget;
}

inline SERIAL_HANDLE CNtlWorldConceptPVP::GetFreePvPTarget(void) const
{
	return m_FreeBattleInfo.hFreePvPTarget;
}

inline void	CNtlWorldConceptPVP::SetFreePvPReferPos(RwV3d vPos)
{
	m_FreeBattleInfo.vFreePvPPos = vPos;
}

inline RwV3d CNtlWorldConceptPVP::GetFreePvPReferPos(void) const
{
	return m_FreeBattleInfo.vFreePvPPos;
}