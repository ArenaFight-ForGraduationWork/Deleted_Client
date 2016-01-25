#ifndef SHADER_H_
#define SHADER_H_



class CMaterial;
class CTexture;
class CObject;



struct VS_CB_WORLD_MATRIX
{
	D3DXMATRIX m_d3dxmtxWorld;
};





class CShader
{
public:
	CShader();
	~CShader();

	void CreateVertexShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11VertexShader **ppd3dVertexShader, D3D11_INPUT_ELEMENT_DESC *pd3dInputLayout, UINT nElements, ID3D11InputLayout **ppd3dVertexLayout);
	void CreatePixelShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11PixelShader **ppd3dPixelShader);
	void CreateGeometryShaderFromFile(ID3D11Device *pd3dDevice, WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11GeometryShader **ppd3dGeometryShader);

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void CreateShaderVariables(ID3D11Device *pd3dDevice);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, D3DXMATRIX *pd3dxmtxWorld = NULL);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, CMaterial *pMaterial = NULL);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, CTexture *pTexture);

	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void ReleaseObjects();
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

protected:
	ID3D11VertexShader *m_pd3dVertexShader;
	ID3D11InputLayout *m_pd3dVertexLayout;

	ID3D11PixelShader *m_pd3dPixelShader;

	ID3D11GeometryShader *m_pd3dGeometryShader;

	CObject **m_ppObjects;
	int m_nObjects;

	ID3D11Buffer *m_pd3dcbWorldMatrix;
	ID3D11Buffer *m_pd3dcbMaterial;
};


// ������ ������� �ʰ� �������ϱ� ���� CDiffusedShader Ŭ����
class CDiffusedShader : public CShader
{
public:
	CDiffusedShader();
	~CDiffusedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void CreateShaderVariables(ID3D11Device *pd3dDevice);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, D3DXMATRIX *pd3dxmtxWorld = NULL);

	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void ReleaseObjects();
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};
// ������ ����Ͽ� �������ϱ� ���� CIlluminatedShader Ŭ����
class CIlluminatedShader : public CShader
{
public:
	CIlluminatedShader();
	~CIlluminatedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void CreateShaderVariables(ID3D11Device *pd3dDevice);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, D3DXMATRIX *pd3dxmtxWorld = NULL);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, CMaterial *pMaterial = NULL);

	virtual void BuildObjects(ID3D11Device *pd3dDevice);
	virtual void ReleaseObjects();
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};
// �ؽ��� ������ ����Ͽ� �������ϱ� ���� CTexturedShader Ŭ����
class CTexturedShader : public CShader
{
public:
	CTexturedShader();
	~CTexturedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void BuildObjects(ID3D11Device *pd3dDevice);
};
// �ؽ��� ���ΰ� ������ ����Ͽ� �������ϱ� ���� CIlluminatedTexturedShader Ŭ����
class CIlluminatedTexturedShader : public CIlluminatedShader
{
public:
	CIlluminatedTexturedShader();
	~CIlluminatedTexturedShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void BuildObjects(ID3D11Device *pd3dDevice);
};


class CPlayerShader : public CDiffusedShader
{
public:
	CPlayerShader();
	virtual ~CPlayerShader();

	virtual void CreateShader(ID3D11Device *pd3dDevice);
	virtual void CreateShaderVariables(ID3D11Device *pd3dDevice);
	virtual void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext, D3DXMATRIX *pd3dxmtxWorld = NULL);

	virtual void ReleaseObjects();
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};




#endif