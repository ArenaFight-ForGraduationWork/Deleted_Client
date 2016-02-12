#include "stdafx.h"
#include "Object.h"





CMaterial::CMaterial()
{
	m_nReferences = 0;
}

CMaterial::~CMaterial()
{
}

void CMaterial::AddRef()
{
	m_nReferences++;
}

void CMaterial::Release()
{
	if (m_nReferences > 0) m_nReferences--;
	if (m_nReferences == 0) delete this;
}





CTexture::CTexture(int nTextures)
{
	m_nReferences = 0;
	m_nTextures = nTextures;
	for (short i = 0; i < m_nTextures; ++i)
	{
		m_vd3dsrvTextures.push_back(nullptr);
		m_vd3dSamplerState.push_back(nullptr);
	}
}

CTexture::~CTexture()
{
	for (int i = 0; i < m_vd3dsrvTextures.size(); ++i)
		delete m_vd3dsrvTextures[i];
	m_vd3dsrvTextures.clear();
	for (int i = 0; i < m_vd3dSamplerState.size(); ++i)
		delete m_vd3dSamplerState[i];
	m_vd3dSamplerState.clear();
}

void CTexture::AddRef()
{
	m_nReferences++;
}

void CTexture::Release()
{
	if (m_nReferences > 0) m_nReferences--;
	for (int i = 0; i < m_vd3dsrvTextures.size(); ++i)
		delete m_vd3dsrvTextures[i];
	m_vd3dsrvTextures.clear();
	for (int i = 0; i < m_vd3dSamplerState.size(); ++i)
		delete m_vd3dSamplerState[i];
	m_vd3dSamplerState.clear();

	if (m_nReferences == 0) delete this;
}

void CTexture::SetTexture(int nIndex, ID3D11ShaderResourceView *pd3dsrvTexture, ID3D11SamplerState *pd3dSamplerState)
{
	if (m_vd3dsrvTextures[nIndex]) m_vd3dsrvTextures[nIndex]->Release();
	m_vd3dsrvTextures[nIndex] = pd3dsrvTexture;
	if (m_vd3dsrvTextures[nIndex]) m_vd3dsrvTextures[nIndex]->AddRef();

	if (m_vd3dSamplerState[nIndex]) m_vd3dSamplerState[nIndex]->Release();
	m_vd3dSamplerState[nIndex] = pd3dSamplerState;
	if (m_vd3dSamplerState[nIndex]) m_vd3dSamplerState[nIndex]->AddRef();
}





CObject::CObject(unsigned int id)
{
	m_d3dxmtxWorld = new D3DXMATRIX();
	D3DXMatrixIdentity(m_d3dxmtxWorld);

	m_pMesh = nullptr;
	m_pMaterial = nullptr;
	m_pTexture = nullptr;

	m_id = id;
}

CObject::~CObject()
{
	if (m_pMesh) m_pMesh->Release();
	if (m_pMaterial) m_pMaterial->Release();
	if (m_pTexture) m_pTexture->Release();
}

void CObject::SetMesh(CMesh *pMesh)
{
	if (m_pMesh) m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) m_pMesh->AddRef();
}

void CObject::SetMaterial(CMaterial *pMaterial)
{
	if (m_pMaterial) m_pMaterial->Release();
	m_pMaterial = pMaterial;
	if (m_pMaterial) m_pMaterial->AddRef();
}

void CObject::SetTexture(CTexture *pTexture)
{
	if (m_pTexture) m_pTexture->Release();
	m_pTexture = pTexture;
	if (m_pTexture) m_pTexture->AddRef();
}

D3DXVECTOR3 CObject::GetPosition()
{
	return D3DXVECTOR3(m_d3dxmtxWorld->_41, m_d3dxmtxWorld->_42, m_d3dxmtxWorld->_43);
}

D3DXVECTOR3 CObject::GetLookAt()
{
	D3DXVECTOR3 d3dxvLookAt(m_d3dxmtxWorld->_31, m_d3dxmtxWorld->_32, m_d3dxmtxWorld->_33);
	D3DXVec3Normalize(&d3dxvLookAt, &d3dxvLookAt);
	return(d3dxvLookAt);
}

D3DXVECTOR3 CObject::GetUp()
{
	D3DXVECTOR3 d3dxvUp(m_d3dxmtxWorld->_21, m_d3dxmtxWorld->_22, m_d3dxmtxWorld->_23);
	D3DXVec3Normalize(&d3dxvUp, &d3dxvUp);
	return(d3dxvUp);
}

D3DXVECTOR3 CObject::GetRight()
{
	D3DXVECTOR3 d3dxvRight(m_d3dxmtxWorld->_11, m_d3dxmtxWorld->_12, m_d3dxmtxWorld->_13);
	D3DXVec3Normalize(&d3dxvRight, &d3dxvRight);
	return(d3dxvRight);
}

void CObject::MoveRelative(const float fx, const float fy, const float fz)
{
	D3DXVECTOR3 d3dxvPosition = GetPosition();

	D3DXVECTOR3 d3dxvRight = GetRight();
	D3DXVECTOR3 d3dxvUp = GetUp();
	D3DXVECTOR3 d3dxvLookAt = GetLookAt();

	d3dxvPosition += fx * d3dxvRight;
	d3dxvPosition += fy * d3dxvUp;
	d3dxvPosition += fz * d3dxvLookAt;

	MoveAbsolute(&d3dxvPosition);
}
void CObject::MoveRelative(const D3DXVECTOR3 *d3dxVec)
{
	D3DXVECTOR3 d3dxvPosition = GetPosition();

	D3DXVECTOR3 d3dxvRight = GetRight();
	D3DXVECTOR3 d3dxvUp = GetUp();
	D3DXVECTOR3 d3dxvLookAt = GetLookAt();

	d3dxvPosition += d3dxVec->x * d3dxvRight;
	d3dxvPosition += d3dxVec->y * d3dxvUp;
	d3dxvPosition += d3dxVec->z * d3dxvLookAt;

	MoveAbsolute(&d3dxvPosition);
}
void CObject::MoveAbsolute(const float fx, const float fy, const float fz)
{
	m_d3dxmtxWorld->_41 = fx;
	m_d3dxmtxWorld->_42 = fy;
	m_d3dxmtxWorld->_43 = fz;
}
void CObject::MoveAbsolute(const D3DXVECTOR3 *d3dxVec)
{
	m_d3dxmtxWorld->_41 = d3dxVec->x;
	m_d3dxmtxWorld->_42 = d3dxVec->y;
	m_d3dxmtxWorld->_43 = d3dxVec->z;
}
void CObject::MoveForward(const float fDistance)
{
	D3DXVECTOR3 d3dxvPosition = GetPosition();
	D3DXVECTOR3 d3dxvLookAt = GetLookAt();
	d3dxvPosition += fDistance * d3dxvLookAt;
	MoveAbsolute(&d3dxvPosition);
}

void CObject::RotateRelative(const float fPitch, const float fYaw, const float fRoll)
{
	D3DXMATRIX mtxRotate;
	D3DXMatrixRotationYawPitchRoll(&mtxRotate, (float)D3DXToRadian(fYaw), (float)D3DXToRadian(fPitch), (float)D3DXToRadian(fRoll));
	(*m_d3dxmtxWorld) = mtxRotate * (*m_d3dxmtxWorld);
}
void CObject::RotateRelative(const D3DXVECTOR3 *d3dxVec)
{
	D3DXMATRIX mtxRotate;
	D3DXMatrixRotationYawPitchRoll(&mtxRotate, (float)D3DXToRadian(d3dxVec->y), (float)D3DXToRadian(d3dxVec->x), (float)D3DXToRadian(d3dxVec->z));
	(*m_d3dxmtxWorld) = mtxRotate * (*m_d3dxmtxWorld);
}
void CObject::RotateRelative(const D3DXVECTOR3 *pd3dxvAxis, const float fAngle)
{
	D3DXMATRIX mtxRotate;
	D3DXMatrixRotationAxis(&mtxRotate, pd3dxvAxis, (float)D3DXToRadian(fAngle));
	(*m_d3dxmtxWorld) = mtxRotate * (*m_d3dxmtxWorld);
}
void CObject::RotateAbsolute(const float fPitch, const float fYaw, const float fRoll)
{
	// 1) 회전각을 0,0,0으로 되돌리기 = 현재 회전행렬 얻어오기 > 행렬을 역행렬로 바꾸기 > 역행렬을 현재 월드변환행렬에 곱해주기
	D3DXMATRIX mtxPresentRotation = (*_GetRotationMatrix());
	D3DXMatrixInverse(&mtxPresentRotation, 0, &mtxPresentRotation);
	(*m_d3dxmtxWorld) = mtxPresentRotation * (*m_d3dxmtxWorld);

	// 2) fPitch, fYaw, fRoll로 회전하기
	RotateRelative(fPitch, fYaw, fRoll);
}
void CObject::RotateAbsolute(const D3DXVECTOR3 *d3dxVec)
{
	// 1) 회전각을 0,0,0으로 되돌리기 = 현재 회전행렬 얻어오기 > 행렬을 역행렬로 바꾸기 > 역행렬을 현재 월드변환행렬에 곱해주기
	D3DXMATRIX mtxPresentRotation = (*_GetRotationMatrix());
	D3DXMatrixInverse(&mtxPresentRotation, 0, &mtxPresentRotation);
	(*m_d3dxmtxWorld) = mtxPresentRotation * (*m_d3dxmtxWorld);

	// 2) d3dxVec만큼 회전하기
	RotateRelative(d3dxVec);
}
void CObject::RotateAbsolute(const D3DXVECTOR3 *pd3dxvAxis, const float fAngle)
{
	// 1) 회전각을 0,0,0으로 되돌리기 = 현재 회전행렬 얻어오기 > 행렬을 역행렬로 바꾸기 > 역행렬을 현재 월드변환행렬에 곱해주기
	D3DXMATRIX mtxPresentRotation = (*_GetRotationMatrix());
	D3DXMatrixInverse(&mtxPresentRotation, 0, &mtxPresentRotation);
	(*m_d3dxmtxWorld) = mtxPresentRotation * (*m_d3dxmtxWorld);

	// 2) fPitch, fYaw, fRoll로 회전하기
	RotateRelative(pd3dxvAxis, fAngle);
}
void CObject::RotateAbsolute(D3DXVECTOR3 *pRight, D3DXVECTOR3 *pUp, D3DXVECTOR3 *pLookAt)
{
	// LookAt벡터를 기준으로 세 축이 서로 직교하게 만들자

	// 1) LookAt벡터를 단위벡터화
	D3DXVec3Normalize(pLookAt, pLookAt);

	// 2) LookAt벡터와 Up벡터를 외적하여 Right벡터 계산+단위벡터화
	D3DXVec3Cross(pRight, pUp, pLookAt);
	D3DXVec3Normalize(pRight, pRight);

	// 3) LookAt벡터와 Right벡터를 외적하여 Up벡터 계산+단위벡터화
	D3DXVec3Cross(pUp, pLookAt, pRight);
	D3DXVec3Normalize(pUp, pUp);

	// 4) Right, Up, LookAt벡터를 이용하여 월드변환행렬 재배열
	m_d3dxmtxWorld->_11 = pRight->x;
	m_d3dxmtxWorld->_12 = pRight->y;
	m_d3dxmtxWorld->_13 = pRight->z;
	m_d3dxmtxWorld->_21 = pUp->x;
	m_d3dxmtxWorld->_22 = pUp->y;
	m_d3dxmtxWorld->_23 = pUp->z;
	m_d3dxmtxWorld->_31 = pLookAt->x;
	m_d3dxmtxWorld->_32 = pLookAt->y;
	m_d3dxmtxWorld->_33 = pLookAt->z;
}


const D3DXMATRIX* CObject::_GetRotationMatrix()
{
	D3DXMATRIX mtxRotate;
	D3DXMatrixIdentity(&mtxRotate);

	/* Scale을 하지 않는다는 가정 하의 회전행렬... 
		Scale해버리면 다른 방법을 찾아야 하는데,
		어차피 DirectX에서는 Scale하면 퍼포먼스가 매우 떨어진다 하셨으므로 안 할 것이다 */
	m_d3dxmtxWorld->_11 = mtxRotate._11;
	m_d3dxmtxWorld->_12 = mtxRotate._12;
	m_d3dxmtxWorld->_13 = mtxRotate._13;
	m_d3dxmtxWorld->_21 = mtxRotate._21;
	m_d3dxmtxWorld->_22 = mtxRotate._22;
	m_d3dxmtxWorld->_23 = mtxRotate._23;
	m_d3dxmtxWorld->_31 = mtxRotate._31;
	m_d3dxmtxWorld->_32 = mtxRotate._32;
	m_d3dxmtxWorld->_33 = mtxRotate._33;

	return &mtxRotate;
}

void CObject::Animate(float fTimeElapsed)
{
}

void CObject::Render(ID3D11DeviceContext *pd3dDeviceContext)
{
	if (m_pMesh) m_pMesh->Render(pd3dDeviceContext);
}



///* 로컬 x축 방향으로 이동한다 */
//void CObject::MoveStrafe(float fDistance)
//{
//	D3DXVECTOR3 d3dxvPosition = GetPosition();
//	D3DXVECTOR3 d3dxvRight = GetRight();
//	d3dxvPosition += fDistance * d3dxvRight;
//	CObject::MoveAbsolute(d3dxvPosition);
//}
//
///* 로컬 y축 방향으로 이동한다 */
//void CObject::MoveUp(float fDistance)
//{
//	D3DXVECTOR3 d3dxvPosition = GetPosition();
//	D3DXVECTOR3 d3dxvUp = GetUp();
//	d3dxvPosition += fDistance * d3dxvUp;
//	CObject::MoveAbsolute(d3dxvPosition);
//}
//