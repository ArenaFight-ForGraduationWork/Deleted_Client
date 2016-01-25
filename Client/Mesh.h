

// ===========================================================================================
//
//
//		CMeshIlluminated를 상속받아서 CCubeMeshIlluminatedTextured를 쓰게 되어있는데
//		사실 CMeshIlluminated 필요 없음. 그러니 합치는게 좋겠다
//
//
// ===========================================================================================



#ifndef MESH_H_
#define MESH_H_




/* Mesh를 표현하는 추상 클래스 */
class CMesh
{
public:
	CMesh(ID3D11Device *pd3dDevice);

	void AddRef();
	void Release();

	/* 래스터라이저 상태를 생성한다 */
	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);

	/* 정점 데이터를 렌더링한다 */
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

protected:
	ID3D11Buffer *m_pd3dVertexBuffer;	/* 정점 버퍼 인터페이스 포인터. 정점 데이터 저장용 */
	UINT m_nVertices;	/* 정점 버퍼의 정점 개수 */
	UINT m_nStride;	/* 정점의 바이트 크기 */
	UINT m_nOffset;	/* 정점 데이터가 정점 버퍼의 어디서부터 시작하는가 */
	D3D11_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology;	/* 정점 데이터가 어떤 프리미티브를 표현하고 있는가 */

	ID3D11Buffer *m_pd3dIndexBuffer;	/* 인덱스 버퍼 인터페이스 포인터. 인덱스 버퍼 저장용 */
	UINT m_nIndices;	/* 인덱스 버퍼의 인덱스 개수 */
	UINT m_nStartIndex;	/* 인덱스 버퍼에서 사용할 시작 인덱스 */
	int m_nBaseVertex;	/* 각 인덱스에 더해질 인덱스 */

	ID3D11RasterizerState *m_pd3dRasterizerState;	/* 래스터라이저 상태 객체에 대한 인터페이스 포인터*/

	virtual ~CMesh();

private:
	int m_nReferences;	/* 이 객체가 참조된 횟수 */
};




/* 조명의 영향을 받는 메쉬의 베이스 클래스 */
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D11Device *pd3dDevice);

	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);

protected:
	virtual ~CMeshIlluminated();

	/* 정점의 법선 벡터 계산. 정점 데이터와 인덱스 데이터 사용 */
	void CalculateVertexNormal(BYTE *pVertices, WORD *pIndices);

private:
	void SetTriAngleListVertexNormal(BYTE *pVertices);	/* 정점의 법선 벡터 계산. 인덱스 버퍼를 쓰지 않는 삼각형 리스트용 */
	void SetAverageVertexNormal(BYTE *pVertices, WORD *pIndices, int nPrimitives, int nOffset, bool bStrip);	/* 정점의 법선벡터의 평균 계산. 인덱스 버퍼를 사용할 경우 */
	D3DXVECTOR3 CalculateTriAngleNormal(BYTE *pVertices, USHORT nIndex0, USHORT nIndex1, USHORT nIndex2);	/* 삼각형의 법선 벡터 계산. 삼각형의 세 정점을 사용 */
};




/* 조명, 텍스처를 이용하는 정육면체 메쉬를 표현 */
class CCubeMeshIlluminatedTextured : public CMeshIlluminated
{
public:
	CCubeMeshIlluminatedTextured(ID3D11Device *pd3dDevice, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

private:
	virtual ~CCubeMeshIlluminatedTextured();
};





#endif