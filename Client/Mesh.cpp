#include "stdafx.h"
#include "Mesh.h"
#include "Vertex.h"

CMesh::CMesh(ID3D11Device *pd3dDevice)
{
	m_pd3dVertexBuffer = nullptr;
	m_nVertices = 0;
	m_nStride = 0;
	m_nOffset = 0;
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_pd3dIndexBuffer = nullptr;
	m_nIndices = 0;
	m_nStartIndex = 0;
	m_nBaseVertex = 0;

	m_pd3dRasterizerState = nullptr;

	m_nReferences = 1;
}

CMesh::~CMesh()
{
	if (m_pd3dVertexBuffer) m_pd3dVertexBuffer->Release();
	if (m_pd3dIndexBuffer) m_pd3dIndexBuffer->Release();
	if (m_pd3dRasterizerState) m_pd3dRasterizerState->Release();
}

void CMesh::AddRef()
{
	m_nReferences++;
}

void CMesh::Release()
{
	m_nReferences--;
	if (m_nReferences == 0) delete this;
}

void CMesh::CreateRasterizerState(ID3D11Device *pd3dDevice)
{
}

void CMesh::Render(ID3D11DeviceContext *pd3dDeviceContext)
{
	if (m_pd3dVertexBuffer) pd3dDeviceContext->IASetVertexBuffers(0, 1, &m_pd3dVertexBuffer, &m_nStride, &m_nOffset);
	if (m_pd3dIndexBuffer) pd3dDeviceContext->IASetIndexBuffer(m_pd3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pd3dDeviceContext->IASetPrimitiveTopology(m_d3dPrimitiveTopology);
	if (m_pd3dRasterizerState) pd3dDeviceContext->RSSetState(m_pd3dRasterizerState);

	/* �ε��� ���۰� ������ �ε��� ���۸� ����Ͽ� �޽��� �������ϰ�
	������ ���� ���۸��� ����Ͽ� �޽��� �������Ѵ�. */
	if (m_pd3dIndexBuffer)
		pd3dDeviceContext->DrawIndexed(m_nIndices, m_nStartIndex, m_nBaseVertex);
	else
		pd3dDeviceContext->Draw(m_nVertices, m_nOffset);
}





CCubeMeshIlluminatedTextured::CCubeMeshIlluminatedTextured(ID3D11Device *pd3dDevice, float fWidth, float fHeight, float fDepth) : CMesh(pd3dDevice)
{
	m_nVertices = 36;
	m_nStride = sizeof(CTexturedNormalVertex);
	m_nOffset = 0;
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;

	CTexturedNormalVertex pVertices[36];
	int i = 0;
	//������ü�� �� �鿡 �ؽ��� ��ü�� ���εǵ��� �ؽ��� ��ǥ�� �����Ѵ�.
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(-fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));

	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, +fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, +fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	pVertices[i++] = CTexturedNormalVertex(D3DXVECTOR3(+fx, -fy, -fz), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f));

	//�� ������ �������͸� ����Ѵ�.
	CalculateVertexNormal((BYTE *)pVertices, NULL);

	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDesc.ByteWidth = m_nStride * m_nVertices;
	d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dBufferData;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = pVertices;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dVertexBuffer);

	SetRasterizerState(pd3dDevice);
}

CCubeMeshIlluminatedTextured::~CCubeMeshIlluminatedTextured()
{
}

void CCubeMeshIlluminatedTextured::SetRasterizerState(ID3D11Device *pd3dDevice)
{
	D3D11_RASTERIZER_DESC d3dRasterizerDesc;
	ZeroMemory(&d3dRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	d3dRasterizerDesc.CullMode = D3D11_CULL_BACK;
	d3dRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	pd3dDevice->CreateRasterizerState(&d3dRasterizerDesc, &m_pd3dRasterizerState);
}

void CCubeMeshIlluminatedTextured::Render(ID3D11DeviceContext *pd3dDeviceContext)
{
	if (m_pd3dVertexBuffer) pd3dDeviceContext->IASetVertexBuffers(0, 1, &m_pd3dVertexBuffer, &m_nStride, &m_nOffset);
	//�ε��� ���۰� ������ �ε��� ���۸� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	if (m_pd3dIndexBuffer) pd3dDeviceContext->IASetIndexBuffer(m_pd3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pd3dDeviceContext->IASetPrimitiveTopology(
		m_d3dPrimitiveTopology);
	if (m_pd3dRasterizerState) pd3dDeviceContext->RSSetState(m_pd3dRasterizerState);

	// �ε��� ���۰� ������ �ε��� ���۸� ����Ͽ� �޽��� �������ϰ�
	// ������ ���� ���۸��� ����Ͽ� �޽��� �������Ѵ�.
	if (m_pd3dIndexBuffer)
		pd3dDeviceContext->DrawIndexed(m_nIndices, m_nStartIndex, m_nBaseVertex);
	else
		pd3dDeviceContext->Draw(m_nVertices, m_nOffset);
}

void CCubeMeshIlluminatedTextured::CalculateVertexNormal(BYTE *pVertices, WORD *pIndices)
{
	switch (m_d3dPrimitiveTopology)
	{
		/*������Ƽ�갡 �ﰢ�� ����Ʈ�� �� �ε��� ���۰� �ִ� ���� ���� ��츦 �����Ͽ� ������ ���� ���͸� ����Ѵ�.
		�ε��� ���۸� ������� �ʴ� ��� �� ������ ���� ���ʹ� �� ������ ���Ե� �ﰢ���� ���� ���ͷ� ����Ѵ�.
		�ε��� ���۸� ����ϴ� ��� �� ������ ���� ���ʹ� �� ������ ���Ե� �ﰢ������ ���� ������ �������(���Ͽ�) ����Ѵ�.*/
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		if (!pIndices)
			SetTriAngleListVertexNormal(pVertices);
		else
			SetAverageVertexNormal(pVertices, pIndices, (m_nIndices / 3), 3, false);
		break;
		/*������Ƽ�갡 �ﰢ�� ��Ʈ���� �� �� ������ ���� ���ʹ� �� ������ ���Ե� �ﰢ������ ���� ������ �������(���Ͽ�) ����Ѵ�.*/
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
		SetAverageVertexNormal(pVertices, pIndices, (pIndices) ? (m_nIndices - 2) : (m_nVertices - 2), 1, true);
		break;
	default:
		break;
	}
}

void CCubeMeshIlluminatedTextured::SetTriAngleListVertexNormal(BYTE *pVertices)
{
	D3DXVECTOR3 d3dxvNormal;
	CNormalVertex *pVertex = NULL;

	/*�ﰢ��(������Ƽ��)�� ������ ���ϰ� �� �ﰢ���� ���� ���͸� ����ϰ� �ﰢ���� �����ϴ� �� ������ ���� ���ͷ� �����Ѵ�.*/
	int nPrimitives = m_nVertices / 3;
	for (int i = 0; i < nPrimitives; i++)
	{
		d3dxvNormal = CalculateTriAngleNormal(pVertices, (i * 3 + 0), (i * 3 + 1), (i * 3 + 2));
		pVertex = (CNormalVertex *)(pVertices + ((i * 3 + 0) * m_nStride));
		pVertex->SetNormal(d3dxvNormal);
		pVertex = (CNormalVertex *)(pVertices + ((i * 3 + 1) * m_nStride));
		pVertex->SetNormal(d3dxvNormal);
		pVertex = (CNormalVertex *)(pVertices + ((i * 3 + 2) * m_nStride));
		pVertex->SetNormal(d3dxvNormal);
	}
}

void CCubeMeshIlluminatedTextured::SetAverageVertexNormal(BYTE *pVertices, WORD *pIndices, int nPrimitives, int nOffset, bool bStrip)
{
	D3DXVECTOR3 d3dxvSumOfNormal(0.0f, 0.0f, 0.0f);
	CNormalVertex *pVertex = NULL;
	USHORT nIndex0, nIndex1, nIndex2;

	for (UINT j = 0; j < m_nVertices; j++)
	{
		d3dxvSumOfNormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < nPrimitives; i++)
		{
			nIndex0 = (bStrip) ? (((i % 2) == 0) ? (i*nOffset + 0) : (i*nOffset + 1)) : (i*nOffset + 0);
			if (pIndices) nIndex0 = pIndices[nIndex0];
			nIndex1 = (bStrip) ? (((i % 2) == 0) ? (i*nOffset + 1) : (i*nOffset + 0)) : (i*nOffset + 1);
			if (pIndices) nIndex1 = pIndices[nIndex1];
			nIndex2 = (pIndices) ? pIndices[i*nOffset + 2] : (i*nOffset + 2);
			if ((nIndex0 == j) || (nIndex1 == j) || (nIndex2 == j)) d3dxvSumOfNormal += CalculateTriAngleNormal(pVertices, nIndex0, nIndex1, nIndex2);
		}
		D3DXVec3Normalize(&d3dxvSumOfNormal, &d3dxvSumOfNormal);
		pVertex = (CNormalVertex *)(pVertices + (j * m_nStride));
		pVertex->SetNormal(d3dxvSumOfNormal);
	}
}

D3DXVECTOR3 CCubeMeshIlluminatedTextured::CalculateTriAngleNormal(BYTE *pVertices, USHORT nIndex0, USHORT nIndex1, USHORT nIndex2)
{
	D3DXVECTOR3 d3dxvNormal(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 d3dxvP0 = *((D3DXVECTOR3 *)(pVertices + (m_nStride * nIndex0)));
	D3DXVECTOR3 d3dxvP1 = *((D3DXVECTOR3 *)(pVertices + (m_nStride * nIndex1)));
	D3DXVECTOR3 d3dxvP2 = *((D3DXVECTOR3 *)(pVertices + (m_nStride * nIndex2)));
	D3DXVECTOR3 d3dxvEdge1 = d3dxvP1 - d3dxvP0;
	D3DXVECTOR3 d3dxvEdge2 = d3dxvP2 - d3dxvP0;
	D3DXVec3Cross(&d3dxvNormal, &d3dxvEdge1, &d3dxvEdge2);
	D3DXVec3Normalize(&d3dxvNormal, &d3dxvNormal);
	return(d3dxvNormal);
}






CImportedMesh::CImportedMesh(ID3D11Device *pd3dDevice) : CMesh(pd3dDevice)
{
	//m_nVertices = 36;
	//m_nStride = sizeof(CTexturedNormalVertex);
	//m_nOffset = 0;
	//m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	///* ���� ���� ���� */
	//D3D11_BUFFER_DESC d3dBufferDesc;
	//ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	//d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//d3dBufferDesc.ByteWidth = m_nStride * m_nVertices;
	//d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//d3dBufferDesc.CPUAccessFlags = 0;
	//D3D11_SUBRESOURCE_DATA d3dBufferData;
	//ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	//d3dBufferData.pSysMem = pVertice;/* ���� ����*/
	//pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dVertexBuffer);

	///* �ε��� ���� ���� */
	//ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	//d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//d3dBufferDesc.ByteWidth = sizeof(WORD) * m_nIndices;
	//d3dBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//d3dBufferDesc.CPUAccessFlags = 0;
	//ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	//d3dBufferData.pSysMem = pIndices;
	//pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dIndexBuffer);

	//SetRasterizerState(pd3dDevice);
}

CImportedMesh::~CImportedMesh()
{
}

void CImportedMesh::SetRasterizerState(ID3D11Device *pd3dDevice)
{
	D3D11_RASTERIZER_DESC d3dRasterizerDesc;
	ZeroMemory(&d3dRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	d3dRasterizerDesc.CullMode = D3D11_CULL_BACK;
	d3dRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	pd3dDevice->CreateRasterizerState(&d3dRasterizerDesc, &m_pd3dRasterizerState);
}

void CImportedMesh::Render(ID3D11DeviceContext *pd3dDeviceContext)
{
	if (m_pd3dVertexBuffer) pd3dDeviceContext->IASetVertexBuffers(0, 1, &m_pd3dVertexBuffer, &m_nStride, &m_nOffset);
	//�ε��� ���۰� ������ �ε��� ���۸� ����̽� ���ؽ�Ʈ�� �����Ѵ�.
	if (m_pd3dIndexBuffer) pd3dDeviceContext->IASetIndexBuffer(m_pd3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pd3dDeviceContext->IASetPrimitiveTopology(
		m_d3dPrimitiveTopology);
	if (m_pd3dRasterizerState) pd3dDeviceContext->RSSetState(m_pd3dRasterizerState);

	// �ε��� ���۰� ������ �ε��� ���۸� ����Ͽ� �޽��� �������ϰ�
	// ������ ���� ���۸��� ����Ͽ� �޽��� �������Ѵ�.
	if (m_pd3dIndexBuffer)
		pd3dDeviceContext->DrawIndexed(m_nIndices, m_nStartIndex, m_nBaseVertex);
	else
		pd3dDeviceContext->Draw(m_nVertices, m_nOffset);
}



