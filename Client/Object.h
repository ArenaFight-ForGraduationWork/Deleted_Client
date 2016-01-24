#ifndef OBJECT_H_
#define OBJECT_H_

#define DIR_FORWARD		0x01
#define DIR_BACKWARD	0x02
#define DIR_LEFT		0x04
#define DIR_RIGHT		0x08
#define DIR_UP			0x10
#define DIR_DOWN		0x20

class CMesh;




/* 재질 관련 정보를 표현 */
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

	/* nIndex번째 인덱스 자리에 텍스쳐를 설정한다 */
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

	void AddRef();
	void Release();

	UINT GetId() { return m_id; }

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(D3DXVECTOR3 d3dxvPosition);

	/* 로컬 x축 방향으로 이동한다 */
	virtual void MoveStrafe(float fDistance = 1.0f);
	/* 로컬 y축 방향으로 이동한다 */
	virtual void MoveUp(float fDistance = 1.0f);
	/* 로컬 z축 방향으로 이동한다 */
	virtual void MoveForward(float fDistance = 1.0f);

	/* x축(Pitch), y축(Yaw), z축(Roll)방향으로 지정값만큼 회전한다 */
	virtual void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	/* pd3dxvAxis를 축으로 fAngle만큼 회전한다 */
	virtual void Rotate(D3DXVECTOR3 *pd3dxvAxis, float fAngle);

	D3DXVECTOR3 GetPosition();

	/* 객체의 로컬 x축 방향벡터를 반환한다 */
	D3DXVECTOR3 GetRight();
	/* 객체의 로컬 y축 방향벡터를 반환한다 */
	D3DXVECTOR3 GetUp();
	/* 객체의 로컬 z축 방향벡터를 반환한다 */
	D3DXVECTOR3 GetLookAt();

	///* 객체의 월드변환행렬을 설정한다 */
	//void SetWorldMatrix(D3DXMATRIX* pMtx) { m_d3dxmtxWorld = *pMtx; }
	/* 객체의 월드변환행렬을 반환한다 */
	D3DXMATRIX* GetWorldMatrix() { return m_d3dxmtxWorld; }

	void SetMesh(CMesh *pMesh);
	CMesh* GetMesh() { return m_pMesh; }
	void SetMaterial(CMaterial *pMaterial);
	CMaterial* GetMaterial() { return m_pMaterial; }
	void SetTexture(CTexture *pTexture);
	CTexture* GetTexture() { return m_pTexture; }

	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);

protected:
	D3DXMATRIX *m_d3dxmtxWorld;	/* 월드 변환 행렬 */
	CMesh *m_pMesh;

private:
	int m_nReferences;

	CMaterial *m_pMaterial;
	CTexture *m_pTexture;

	UINT m_id;
	// hp, mp, atk, def, ...

};





#endif