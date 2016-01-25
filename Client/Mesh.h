

// ===========================================================================================
//
//
//		CMeshIlluminated�� ��ӹ޾Ƽ� CCubeMeshIlluminatedTextured�� ���� �Ǿ��ִµ�
//		��� CMeshIlluminated �ʿ� ����. �׷��� ��ġ�°� ���ڴ�
//
//
// ===========================================================================================



#ifndef MESH_H_
#define MESH_H_




/* Mesh�� ǥ���ϴ� �߻� Ŭ���� */
class CMesh
{
public:
	CMesh(ID3D11Device *pd3dDevice);

	void AddRef();
	void Release();

	/* �����Ͷ����� ���¸� �����Ѵ� */
	virtual void CreateRasterizerState(ID3D11Device *pd3dDevice);

	/* ���� �����͸� �������Ѵ� */
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

protected:
	ID3D11Buffer *m_pd3dVertexBuffer;	/* ���� ���� �������̽� ������. ���� ������ ����� */
	UINT m_nVertices;	/* ���� ������ ���� ���� */
	UINT m_nStride;	/* ������ ����Ʈ ũ�� */
	UINT m_nOffset;	/* ���� �����Ͱ� ���� ������ ��𼭺��� �����ϴ°� */
	D3D11_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology;	/* ���� �����Ͱ� � ������Ƽ�긦 ǥ���ϰ� �ִ°� */

	ID3D11Buffer *m_pd3dIndexBuffer;	/* �ε��� ���� �������̽� ������. �ε��� ���� ����� */
	UINT m_nIndices;	/* �ε��� ������ �ε��� ���� */
	UINT m_nStartIndex;	/* �ε��� ���ۿ��� ����� ���� �ε��� */
	int m_nBaseVertex;	/* �� �ε����� ������ �ε��� */

	ID3D11RasterizerState *m_pd3dRasterizerState;	/* �����Ͷ����� ���� ��ü�� ���� �������̽� ������*/

	virtual ~CMesh();

private:
	int m_nReferences;	/* �� ��ü�� ������ Ƚ�� */
};




/* ������ ������ �޴� �޽��� ���̽� Ŭ���� */
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D11Device *pd3dDevice);

	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);

protected:
	virtual ~CMeshIlluminated();

	/* ������ ���� ���� ���. ���� �����Ϳ� �ε��� ������ ��� */
	void CalculateVertexNormal(BYTE *pVertices, WORD *pIndices);

private:
	void SetTriAngleListVertexNormal(BYTE *pVertices);	/* ������ ���� ���� ���. �ε��� ���۸� ���� �ʴ� �ﰢ�� ����Ʈ�� */
	void SetAverageVertexNormal(BYTE *pVertices, WORD *pIndices, int nPrimitives, int nOffset, bool bStrip);	/* ������ ���������� ��� ���. �ε��� ���۸� ����� ��� */
	D3DXVECTOR3 CalculateTriAngleNormal(BYTE *pVertices, USHORT nIndex0, USHORT nIndex1, USHORT nIndex2);	/* �ﰢ���� ���� ���� ���. �ﰢ���� �� ������ ��� */
};




/* ����, �ؽ�ó�� �̿��ϴ� ������ü �޽��� ǥ�� */
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