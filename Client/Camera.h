#ifndef CAMERA_H_
#define CAMERA_H_



struct VS_CB_VIEWPROJECTION_MATRIX
{
	D3DXMATRIX m_d3dxmtxView;
	D3DXMATRIX m_d3dxmtxProjection;
};





class CCamera
{
public:
	CCamera();
	~CCamera();

	enum class Type : BYTE{
		START = 0,
		THIRD_PERSON_CAMERA = 0,
		END
	};

protected:
	Type m_Mode;

	D3DXVECTOR3 m_d3dxvPosition;

	// ī�޶��� ���� x - ��(Right), y - ��(Up), z - ��(Look)�� ��Ÿ���� �����̴�.
	D3DXVECTOR3 m_d3dxvRight;
	D3DXVECTOR3 m_d3dxvUp;
	D3DXVECTOR3 m_d3dxvLook;

	/* x, y, z������ ȸ���� ���� */
	D3DXVECTOR3 m_fPitchYawRoll;

	//ī�޶� �ٶ󺸴� ��(������ǥ��)�� ��Ÿ���� �����̴�.
	D3DXVECTOR3 m_d3dxvLookAtWorld;
	//�÷��̾�� ī�޶��� �������� ��Ÿ���� �����̴�. �ַ� 3��Ī ī�޶󿡼� ���ȴ�.
	D3DXVECTOR3 m_d3dxvOffset;
	//�÷��̾ ȸ���� �� �󸶸�ŭ�� �ð��� ������Ų �� ī�޶� ȸ����ų ���ΰ��� ��Ÿ����.
	float m_fTimeLag;


	//ī�޶� ��ȯ ��İ� ���� ��ȯ ����� ��Ÿ���� ��� ������ �����Ѵ�.
	D3DXMATRIX *m_d3dxmtxView;
	D3DXMATRIX *m_d3dxmtxProjection;

	//��-��Ʈ�� ��Ÿ���� ��� ������ �����Ѵ�.
	D3D11_VIEWPORT m_d3dViewport;

	//ī�޶� ��ȯ ��İ� ���� ��ȯ ����� ���� ��� ���� �������̽� �����͸� �����Ѵ�.
	ID3D11Buffer *m_pd3dcbViewProjection;
	ID3D11Buffer *m_pd3dcbCamera;

private:
	const D3DXVECTOR3& GetRight();
	const D3DXVECTOR3& GetUp();
	const D3DXVECTOR3& GetLookAt();
};

//class CCamera
//{
//public:
//	CCamera(CCamera *pCamera);
//	~CCamera();
//
//	enum class Type : BYTE{
//		START = 0,
//		THIRD_PERSON_CAMERA = 0,
//		END
//	};
//
//	void GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fAspectRatio, float fFOVAngle);
//
//	void CreateShaderVariables(ID3D11Device *pd3dDevice);
//	void UpdateShaderVariables(ID3D11DeviceContext *pd3dDeviceContext);
//
//	void SetViewport(ID3D11DeviceContext *pd3dDeviceContext, DWORD xStart, DWORD yStart, DWORD nWidth, DWORD nHeight, float fMinZ = 0.0f, float fMaxZ = 1.0f);
//	D3D11_VIEWPORT GetViewport() { return(m_d3dViewport); }
//
//	D3DXMATRIX GetViewMatrix() { return(m_d3dxmtxView); }
//	D3DXMATRIX GetProjectionMatrix() { return(m_d3dxmtxProjection); }
//	ID3D11Buffer *GetCameraConstantBuffer() { return(m_pd3dcbCamera); }
//
//	void SetPosition(D3DXVECTOR3 d3dxvPosition) { m_d3dxvPosition = d3dxvPosition; }
//	D3DXVECTOR3& GetPosition() { return(m_d3dxvPosition); }
//
//	void SetLookAtPosition(D3DXVECTOR3 d3dxvLookAtWorld) { m_d3dxvLookAtWorld = d3dxvLookAtWorld; }
//	D3DXVECTOR3& GetLookAtPosition() { return(m_d3dxvLookAtWorld); }
//
//	D3DXVECTOR3& GetRightVector() { return(m_d3dxvRight); }
//	D3DXVECTOR3& GetUpVector() { return(m_d3dxvUp); }
//	D3DXVECTOR3& GetLookVector() { return(m_d3dxvLook); }
//
//	float& GetPitch() { return(m_fPitch); }
//	float& GetRoll() { return(m_fRoll); }
//	float& GetYaw() { return(m_fYaw); }
//
//	void SetOffset(D3DXVECTOR3 d3dxvOffset) { m_d3dxvOffset = d3dxvOffset; m_d3dxvPosition += d3dxvOffset; }
//	D3DXVECTOR3& GetOffset() { return(m_d3dxvOffset); }
//
//	void SetTimeLag(float fTimeLag) { m_fTimeLag = fTimeLag; }
//	float GetTimeLag() { return(m_fTimeLag); }
//
//	//ī�޶� d3dxvShift ��ŭ �̵��ϴ� �����Լ��̴�.
//	virtual void Move(const D3DXVECTOR3& d3dxvShift) { m_d3dxvPosition += d3dxvShift; }
//	//ī�޶� x-��, y-��, z-������ ȸ���ϴ� �����Լ��̴�.
//	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f) { }
//	//ī�޶��� �̵�, ȸ���� ���� ī�޶��� ������ �����ϴ� �����Լ��̴�.
//	virtual void Update(float fTimeElapsed) { }
//	/*3��Ī ī�޶󿡼� ī�޶� �ٶ󺸴� ������ �����ϴ� �����Լ��̴�. �Ϲ������� �÷��̾ �ٶ󺸵��� �����Ѵ�.*/
//	virtual void SetLookAt(D3DXVECTOR3& vLookAt) { }
//
//	//ī�޶� ��ȯ����� �����Ѵ�.
//	void GenerateViewMatrix();
//	// ī�޶� ������ ȸ���� �ϰ� �Ǹ� ������ �Ǽ������� ����Ȯ�� ������
//	// ī�޶��� ���� x-��(Right), y-��(Up), z-��(LookAt)�� ���� �������� ���� �� �ִ�.
//	// ī�޶��� ���� x-��(Right), y-��(Up), z-��(LookAt)�� ���� �����ϵ��� ������ش�.
//	void GenerateViewMatrix(D3DXVECTOR3 d3dxvEyePosition, D3DXVECTOR3 d3dxvLookAt, D3DXVECTOR3 d3dxvUp);
//
//
//protected:
//	//ī�޶��� ��ġ(������ǥ��) �����̴�.
//	D3DXVECTOR3 m_d3dxvPosition;
//	// ī�޶��� ���� x - ��(Right), y - ��(Up), z - ��(Look)�� ��Ÿ���� �����̴�.
//	D3DXVECTOR3 m_d3dxvRight;
//	D3DXVECTOR3 m_d3dxvUp;
//	D3DXVECTOR3 m_d3dxvLook;
//
//	/* x, y, z������ ȸ���� ���� */
//	D3DXVECTOR3 m_fPitchYawRoll;
//
//
//	// ī�޶��� ����(1��Ī ī�޶�, �����̽�-�� ī�޶�, 3��Ī ī�޶�)�� ��Ÿ����.
//	Type m_Mode;
//
//	//ī�޶� �ٶ󺸴� ��(������ǥ��)�� ��Ÿ���� �����̴�.
//	D3DXVECTOR3 m_d3dxvLookAtWorld;
//	//�÷��̾�� ī�޶��� �������� ��Ÿ���� �����̴�. �ַ� 3��Ī ī�޶󿡼� ���ȴ�.
//	D3DXVECTOR3 m_d3dxvOffset;
//	//�÷��̾ ȸ���� �� �󸶸�ŭ�� �ð��� ������Ų �� ī�޶� ȸ����ų ���ΰ��� ��Ÿ����.
//	float m_fTimeLag;
//
//
//	//ī�޶� ��ȯ ��İ� ���� ��ȯ ����� ��Ÿ���� ��� ������ �����Ѵ�.
//	D3DXMATRIX m_d3dxmtxView;
//	D3DXMATRIX m_d3dxmtxProjection;
//
//	//��-��Ʈ�� ��Ÿ���� ��� ������ �����Ѵ�.
//	D3D11_VIEWPORT m_d3dViewport;
//
//	//ī�޶� ��ȯ ��İ� ���� ��ȯ ����� ���� ��� ���� �������̽� �����͸� �����Ѵ�.
//	ID3D11Buffer *m_pd3dcbViewProjection;
//	ID3D11Buffer *m_pd3dcbCamera;
//
//private:
//	void RegenerateViewMatrix();
//};





//class CSpaceShipCamera : public CCamera
//{
//public:
//	CSpaceShipCamera(CCamera *pCamera);
//
//	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
//};
//
//class CFirstPersonCamera : public CCamera
//{
//public:
//	CFirstPersonCamera(CCamera *pCamera);
//
//	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
//};
//
class CThirdPersonCamera : public CCamera
{
public:
	CThirdPersonCamera(CCamera *pCamera);

	virtual void Update(float fTimeScale);
	virtual void SetLookAt(D3DXVECTOR3& vLookAt);
};



#endif