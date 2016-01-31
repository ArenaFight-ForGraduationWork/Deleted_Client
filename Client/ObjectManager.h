#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "stdafx.h"
#include "ResourceManager.h"

/*
*		��� : ObjectCategory
*		1) LAND�� NATURAL_FEATURE�� ������ �ϴ� ������ �����ΰ�
*			�ϴ� �� �� �浹üũO, ����O, ������X
*		2) BUFF_CRYSTAL 
*			�̸��� ���� �� ���. �������� �̸��� �ʿ��ϴ�.
*			�浹üũX, ����O�� ��ü
*
*		id ���� ���� �����̶� �� ����� UINT �ϳ��� ���°� ��
*			UINT = 0~4G ����
*		���� 2xx00, ��� 3xx00���� �׳� �س��� id �ϳ��� Ÿ�Ա��� �ѹ濡.
*		���߿� �ٲ�´�� �ٲ��....
*/


class CObjectManager
{
public:
	static CObjectManager* GetSingleton(ID3D11Device *pd3dDevice);
	~CObjectManager();

	/* ~�����͸� ���� ������Ʈ�� �߰� */
	void Insert(UINT id, int x, int y, int z, int dx, int dy, int dz);
	void Insert(UINT id, D3DXVECTOR3 position, D3DXVECTOR3 direction);

	CObject* FindObject(UINT id);
	const std::vector<CObject*> FindObjectInCategory(const UINT id);

	void DeleteObject(UINT id);

	void DeleteObjectAll();

	/* ObjectList�� ī�װ�
	* LAND : ����. �ٴ�, ��
	* NATURAL_FEATURE : ����, �� ���� �⵿���. �浹üũO ����O
	* MONSTER : ���� = ����
	* PLAYER : ���� �ٸ� �������� �����ؾ� �ұ�? ��� �� �غ��߰���
	* BUFF_CRYSTAL : �ϴ� �̷��� ����µ�. �浹üũX ����O�� ������Ʈ
	*/
	enum class ObjectType :BYTE{
		START = 0,
		LAND = 0,
		NATURAL_FEATURE,
		MONSTER,
		PLAYER,
		BUFF_CRYSTAL,
		END
	};

private:
	std::map<ObjectType, std::vector<CObject*>> m_mObjects;

	CResourceManager *pResourceManager;

	CObjectManager(ID3D11Device *pd3dDevice);
};





#endif