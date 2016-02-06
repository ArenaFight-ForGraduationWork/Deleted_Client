#ifndef OBJECT_H_
#define OBJECT_H_

#define DIR_FORWARD		0x01
#define DIR_BACKWARD	0x02
#define DIR_LEFT		0x04
#define DIR_RIGHT		0x08
#define DIR_UP			0x10
#define DIR_DOWN		0x20

#include "Mesh.h"


/* ���� ���� ������ ǥ�� */
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

	/* nIndex��° �ε��� �ڸ��� �ؽ��ĸ� �����Ѵ� */
	void SetTexture(int nIndex, ID3D11ShaderResourceView *pd3dsrvTexture, ID3D11SamplerState *pd3dSamplerState);

	int getNumOfTextures() { return m_nTextures; }

	ID3D11ShaderResourceView** getShaderResourceViewTextures() { return &(m_vd3dsrvTextures[0]); }
	ID3D11SamplerState** getSamplerState() { return &(m_vd3dSamplerState[0]); }

private:
	int m_nReferences;

	std::vector<ID3D11ShaderResourceView*> m_vd3dsrvTextures;
	std::vector<ID3D11SamplerState*> m_vd3dSamplerState;

	int m_nTextures;
};











class CObject
{
public:
	CObject(UINT id);
	virtual ~CObject();

	UINT GetId() { return m_id; }

	void MoveRelative(const float fx, const float fy, const float fz);
	void MoveRelative(const D3DXVECTOR3 *d3dxVec);
	void MoveAbsolute(const float fx, const float fy, const float fz);
	void MoveAbsolute(const D3DXVECTOR3 *d3dxVec);

	void RotateRelative(const float fPitch, const float fYaw, const float fRoll);
	void RotateRelative(const D3DXVECTOR3 *d3dxVec);
	void RotateRelative(const D3DXVECTOR3 *pd3dxvAxis, const float fAngle);
	void RotateAbsolute(const float fPitch, const float fYaw, const float fRoll);
	void RotateAbsolute(const D3DXVECTOR3 *d3dxVec);
	void RotateAbsolute(const D3DXVECTOR3 *pd3dxvAxis, const float fAngle);

	D3DXVECTOR3 GetPosition();

	/* ��ü�� ���� x�� ���⺤�͸� ��ȯ�Ѵ� */
	D3DXVECTOR3 GetRight();
	/* ��ü�� ���� y�� ���⺤�͸� ��ȯ�Ѵ� */
	D3DXVECTOR3 GetUp();
	/* ��ü�� ���� z�� ���⺤�͸� ��ȯ�Ѵ� */
	D3DXVECTOR3 GetLookAt();

	///* ��ü�� ���庯ȯ����� �����Ѵ� */
	//void SetWorldMatrix(D3DXMATRIX* pMtx) { m_d3dxmtxWorld = *pMtx; }
	/* ��ü�� ���庯ȯ����� ��ȯ�Ѵ� */
	D3DXMATRIX* GetWorldMatrix() { return m_d3dxmtxWorld; }

	void SetMesh(CMesh *pMesh);
	CMesh* GetMesh() { return m_pMesh; }
	void SetMaterial(CMaterial *pMaterial);
	CMaterial* GetMaterial() { return m_pMaterial; }
	void SetTexture(CTexture *pTexture);
	CTexture* GetTexture() { return m_pTexture; }

	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

private:
	D3DXMATRIX *m_d3dxmtxWorld;	/* ���� ��ȯ ��� */

	CMesh *m_pMesh;
	CMaterial *m_pMaterial;
	CTexture *m_pTexture;

	UINT m_id;

	const D3DXMATRIX* _GetRotationMatrix();
};





#endif