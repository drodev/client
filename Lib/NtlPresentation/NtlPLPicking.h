/*****************************************************************************
*
* File			: NtlPLPinking.h
* Author		: All Author
* Copyright	: (��)NTL
* Date			: 2005. 8. 11	
* Abstract		: Presentation picking.
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_PLPICKING_H__
#define __NTL_PLPICKING_H__

#include <rwcore.h>
#include <rpworld.h>
#include <rtpick.h>
#include <rpcollis.h>
#include "NtlPLEntity.h"

// picking
typedef struct _SWorldIntersect
{
	RpIntersection Intersection;
	RwReal fMinDist;
	RpAtomic *pAtomic;
	RwV3d vCollPos;
	RwV3d vNormal;
	RwBool bCollision;
}SWorldIntersect;

typedef struct _SWorldPickInfo
{
	RwBool bTerrainExclusion;		// ������ ������ ���ΰ�?
	RwBool bCharacterExclusion;		// character�� ������ ���ΰ�?
	RwReal fMinDist;				// ��꿡 �ʿ��� ���� ����
	RpAtomic *pAtomic;				// ��꿡 �ʿ��� ���� ����
	CNtlPLEntity *pPLEntity;		// picking�� �����ϸ� NULL�� �ƴϰ�, �����ϸ� NULL
	RwV3d vPickPos;

	_SWorldPickInfo()
	{
		bTerrainExclusion	= FALSE;
		bCharacterExclusion = FALSE;
		pAtomic				= NULL;
		pPLEntity			= NULL;
	}

}SWorldPickInfo;

// character
#define NTL_MAX_CHAR_INTERSECION	10

typedef struct _SWorldCharIntersectionData
{
	RpAtomic *pAtomic;
	RwBool bCollision;
	RwReal fMinDist;
	RwV3d vCollPos;
	RwV3d vNormal;
}SWorldCharIntersectionData;

typedef struct _SWorldCharIntersectionInfo
{
	RwUInt8 byAtomicCount;							// character�� �浹�ϴ� object atomic ����.
	RpAtomic *pAtomic[NTL_MAX_CHAR_INTERSECION];	// atomic buffer.
}SWorldCharIntersectionInfo;

// camera
#define NTL_MAX_CAMERA_INTERSECION	20

typedef struct _SWorldCameraRayAtomicData
{
	RwUInt8 byCollCount;
	RpAtomic *pAtomic[NTL_MAX_CAMERA_INTERSECION];
	RwBool bCollision[NTL_MAX_CAMERA_INTERSECION];
	RwReal fMinDist[NTL_MAX_CAMERA_INTERSECION];
	RwV3d vCollPos[NTL_MAX_CAMERA_INTERSECION];
}SWorldCameraLineAtomicData;

typedef struct _SWorldCameraIntersectionData
{
	RwBool bCollision;
	SWorldCameraLineAtomicData sLineAtomicData;
	RwBool bSphereCollision;
	RwReal fBackwardDist;
	RwBool bBackwardCollision;
}SWorldCameraIntersectionData;

/**
* �浹 ���� Atomic���� �˻��Ѵ�
**/
RwBool IsCollisionAtomic(RpAtomic* pAtomic);

/**
* mouse picking�� �Ѵ�.
*/
void Pick_WorldIntersectionLine(RwLine& Line, SWorldPickInfo& sPickInfo, RwReal fRayDist);

/**
* �浹�Ǵ� height field ���̸� ���ϴ� collision logic�� optimize �Ǿ� �ִ�.
*/
RwBool Collision_HeightFieldIntersectionLineTopDown(RwLine& Line, SWorldIntersect& sInter);

/**
* �浹�Ǵ� Indoor ���̸� ���ϴ� collision logic�� optimize �Ǿ� �ִ�.
*/
RwBool Collision_IndoorIntersectionLineTopDown(RwLine& Line, SWorldIntersect& sInter);

/**
* �浹�Ǵ� object ���̸� ���ϴ� collision logic�� optimize �Ǿ� �ִ�.
*/
RwBool Collision_WorldIntersectionLineTopDown(RwLine& Line, SWorldIntersect& sInter);

/**
* �浹�Ǵ� mini indoor object ���̸� ���ϴ� collision logic�� optimize �Ǿ� �ִ�.
*/
RwBool Collision_MiniIndoorIntersectionLineTopDown(RwLine& Line, SWorldIntersect& sInter);

/**
* world object�߿� �浹�Ǵ� atomic�� ���Ѵ�.
*/
RwBool Collision_WorldIntersectionCharacter(RwBBox& box, SWorldCharIntersectionInfo& sCharInfo);

/**
* world �߿� �浹�Ǵ� RpWorldSector(Indoor) Triangle�� ���Ѵ�.
*/
RwBool Collision_WorldIntersectionWorldSector(RwLine& Line, SWorldCharIntersectionData& sCharDataInfo);

/**
* world object�߿� �浹�Ǵ� atomic�� ���Ѵ�.
*/
RwBool Collision_WorldIntersectionCharacterData(RwLine& Line, RpAtomic *pAtomic, SWorldCharIntersectionData& sCharDataInfo);

/**
* world���� �������� camera �浹 ������ ���Ѵ�.
*/
RwBool Collision_WorldIntersectionCameraData(const RwV3d *pCameraPos, const RwV3d *pLookAt, RwReal fRadius, RwV3d& vNewPos);

/**
* �浹�Ǵ� Object�� �ִ��� ���θ� �˻��Ѵ�. (LensFlare��. by agebreak)
*/
RwBool Collision_WorldIntersectionObject(const RwLine& line, SWorldPickInfo* pPickInfo );

/**
* �浹�Ǵ� Object�� �ִ��� ���θ� �˻��Ѵ�. (Targeting��)
*/
RwBool Collision_WorldIntersectionObjectForTarget(const RwLine& line, SWorldPickInfo* pPickInfo );

#endif