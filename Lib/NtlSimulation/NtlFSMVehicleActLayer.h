/*****************************************************************************
 *
 * File			: NtlFSMVehicleActLayer.h
 * Author		: JeongHo, Rho
 * Copyright	: (��)NTL
 * Date			: 2008. 11. 12	
 * Abstract		: fsm vehicle act layer
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_FSM_VEHICLE_LAYER_H__
#define __NTL_FSM_VEHICLE_LAYER_H__


#include "NtlFSMLayer.h"


class CNtlFSMVehicleActLayer : public CNtlFSMLayer
{
	DECLEAR_MEMORY_POOL( CNtlFSMVehicleActLayer, NTL_DEFAULT_MEMORY_POOL )

private:

	void CreateController( RwUInt32 uiController );

public:

	CNtlFSMVehicleActLayer( void );

	/**
    *  �� class�� ������ �� �ٷ� ȣ���ϴ� �Լ�
    *
    */
	virtual RwBool Create( RwUInt32 uiController );

	/**
    *  �� class�� �Ҹ�Ǳ� ���� ȣ���ϴ� �Լ�
    *
    */
	virtual void Destroy( void );

	/**
    *  layer update �Լ�.
    *
    */
	virtual void Update( RwReal fElapsed );

	/**
    *  layer event handler �Լ�.
    *
    */
	virtual RwUInt32 HandleEvents( RWS::CMsg &pMsg );
};


#endif
