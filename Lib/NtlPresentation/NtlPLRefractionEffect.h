#pragma once

struct WaveElement
{
    RwV2d   v2Pos;          //�����Ĺ߻�����
    RwReal  fRound;         //�İ��������ִ������
    RwReal  fMaxHeight;     //�������ʳ���(z��)
    RwReal  fDelta;         //��������Ƚð�(���������ǹ�����)
};

/**
 * \ingroup NtlPresentation
 * \brief ȭ���� ���� �ݻ� ����Ʈ Ŭ����
 *
 * \date 2008-08-20
 * \author agebreak
 */
class CNtlPLRefractionEffect
{
public:
    CNtlPLRefractionEffect(void);
    ~CNtlPLRefractionEffect(void);

    void Init(RwIm2DVertex* pVertices, RwInt32 nVertexCount);
    void Update(RwReal fElapsedTime);

    void InsertWave(RwReal fX, RwReal fY, RwReal fRound, RwReal fMaxHeight);

protected:

protected:
    std::list<WaveElement*> m_listWaveElement;           ///< �ĵ��� ����Ʈ
    RwInt32     m_nVertexCnt;    
    RwIm2DVertex* m_pVertices;
    RwV2d*      m_pUVVerticesOrg;
};
