#ifndef OBJECT_H_
#define OBJECT_H_

#define DIR_FORWARD		0x01
#define DIR_BACKWARD	0x02
#define DIR_LEFT		0x04
#define DIR_RIGHT		0x08
#define DIR_UP			0x10
#define DIR_DOWN		0x20

class CMesh;




struct MATERIAL
{
	D3DXCOLOR m_d3dxcAmbient;
	D3DXCOLOR m_d3dxcDiffuse;
	D3DXCOLOR m_d3dxcSpecular; //(r,g,b,a=power)
	D3DXCOLOR m_d3dxcEmissive;
};

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	void AddRef();
	void Release();

	MATERIAL* getMaterial() { return m_Material; }

private:
	int m_nReferences;
	MATERIAL* m_Material;
};

class CTexture
{
public:
	CTexture(int nTextures);
	virtual ~CTexture();

	void AddRef();
	void Release();

	void SetTexture(ID3D11ShaderResourceView *pd3dsrvTexture, ID3D11SamplerState *pd3dSamplerState);

	int getNumOfTextures() { return m_nTextures; }

	ID3D11ShaderResourceView** getShaderResourceViewTextures() { return &(m_vd3dsrvTextures[0]); }
	ID3D11SamplerState** getSamplerState() { return &(m_vd3dSamplerState[0]); }

private:
	int m_nReferences;

	std::vector<ID3D11ShaderResourceView*> m_vd3dsrvTextures;
	std::vector<ID3D11SamplerState*> m_vd3dSamplerState;

	int m_nTextures;
};











class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	//��ü�� ��ġ�� �����Ѵ�.
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(D3DXVECTOR3 d3dxvPosition);

	//���� x-��, y-��, z-�� �������� �̵��Ѵ�.
	virtual void MoveStrafe(float fDistance = 1.0f);
	virtual void MoveUp(float fDistance = 1.0f);
	virtual void MoveForward(float fDistance = 1.0f);

	//���� x-��, y-��, z-�� �������� ȸ���Ѵ�.
	virtual void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	virtual void Rotate(D3DXVECTOR3 *pd3dxvAxis, float fAngle);

	//��ü�� ��ġ, ���� x-��, y-��, z-�� ���� ���͸� ��ȯ�Ѵ�.
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetLookAt();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetRight();
private:
	int m_nReferences;
public:
	void AddRef();
	void Release();

	D3DXMATRIX m_d3dxmtxWorld;
	CMesh *m_pMesh;
	CMaterial *m_pMaterial;
	CTexture *m_pTexture;
	void SetTexture(CTexture *pTexture);

	virtual void SetMesh(CMesh *pMesh);
	void SetMaterial(CMaterial *pMaterial);
	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};




//class CRotatingObject : public CGameObject
//{
//public:
//	CRotatingObject();
//	virtual ~CRotatingObject();
//
//	virtual void Animate(float fTimeElapsed);
//	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);
//
//	//���� �ӵ��� ȸ���� ���͸� �����ϴ� �Լ��̴�.
//	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
//	void SetRotationAxis(D3DXVECTOR3 d3dxvRotationAxis) { m_d3dxvRotationAxis = d3dxvRotationAxis; }
//
//private:
//	//���� �ӵ��� ȸ���� ���͸� ��Ÿ���� ��� ������ �����Ѵ�.
//	float m_fRotationSpeed;
//	D3DXVECTOR3 m_d3dxvRotationAxis;
//};




#endif