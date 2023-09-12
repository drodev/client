#pragma once

//|-------------------------------------------------------------------------------------------------------------------
//|	Topic	| CNtlPLOptionManager
//|---------|---------------------------------------------------------------------------------------------------------
//|	Content | Visual Option Test�� ���� Class
//|---------|---------------------------------------------------------------------------------------------------------
//|	Author	| Cz
//|-------------------------------------------------------------------------------------------------------------------

class CNtlPLOptionManager
{
private:
	static CNtlPLOptionManager*		g_pOptionManager;

public:
	static CNtlPLOptionManager*		GetInstance() { return g_pOptionManager; }
	static void						CreateInstance();
	static void						DestroyInstance();

public:
	CNtlPLOptionManager();
	virtual ~CNtlPLOptionManager();

	RwBool		Create();
	void		Destroy();

	RwBool		Update(const RwCamera* pCameram, RwReal fElapsed);

public:
	// Object ���ðŸ�
	void		SetObjectFar(RwReal fFar);
	RwReal		GetObjectFar();	
	
	// Terrain ���ðŸ�
	void		SetTerrainFar(RwReal fFar);
	RwReal		GetTerrainFar();

	// Terrain Shadow Render ����
	void		SetTerrainShadow(RwBool bRender);
	RwBool		GetTerrainShadow();

	void		SetWaterSpecular(RwBool bRender);
	RwBool		GetWaterSpecular();

	// ���� ���� ����
	void		SetWeatherLevel(RwUInt32 uiLevel);
	RwUInt32	GetWeatherLevel();

	// Ǯ ���ðŸ�
	void		SetPlantClipDist(RwReal fDist);
	RwReal		GetPlantClipDist();

	// �������� ����
	void		SetHeatHaze(RwBool bUse);
	RwBool		GetHeatHaze();

	// �ؽ��� ���� // �������� ����. 0 == ����.
	void		SetTextureQuality(RwUInt32 uiQualityLevel);
	RwUInt32	GetTextureQuality();

#ifdef dNTL_WORLD_COMBINE
	// Terrain Texture Combine // I will not use it.
	void		SetTerrainTextrueCombine(RwBool bUse);
	RwBool		GetTerrainTextrueCombine();
#endif

private:
	RwReal			m_fFarObject;
	RwReal			m_fFarTerrain;

	RwBool			m_bWaterSpecular;

	RwUInt32		m_uiWeatherLevel;

#ifdef dNTL_WORLD_COMBINE
	RwBool			m_bTerrainCombine;
#endif
};

inline CNtlPLOptionManager* GetNtlPLOptionManager(void)
{
	return CNtlPLOptionManager::GetInstance(); 
}