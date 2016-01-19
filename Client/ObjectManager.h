#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "stdafx.h"
#include "Object.h"

/*
*		��� : ObjectCategory
*		1) LAND�� NATURAL_FEATURE�� ������ �ϴ� ������ �����ΰ�
*			�ϴ� �� �� �浹üũO, ����O, ������X
*		2) BUFF_CRYSTAL 
*			�̸��� ���� �� ���. �������� �̸��� �ʿ��ϴ�.
*			�浹üũX, ����O�� ��ü
*/


class CObjectManager
{
public:
	CObjectManager* GetSingleton();
	~CObjectManager();

	/* ~�����͸� ���� ������Ʈ�� �߰� */
	void Insert(int x, int y, int z, int dx, int dy, int dz);
	void Insert(D3DXVECTOR3 position, D3DXVECTOR3 direction);

	/* ��ü ������Ʈ �߿��� �ش� id�� ���� ������Ʈ�� ã�´� */
	CObject* FindObject(int id);

	/* ������Ʈ ī�װ� �� id��° ī�װ��� ������Ʈ���� ��ȯ�Ѵ� */
	const std::vector<CObject*> FindObjectInCategory(int id) const;

	/* id ?�� ������Ʈ�� ���� */
	void DeleteObject(int id);

	/* ���� ������ �ִ� ��� ������Ʈ�� ���� */
	void DeleteObjectAll();

	/* ObjectList�� ī�װ�
	* LAND : ����. �ٴ�, ��
	* NATURAL_FEATURE : ����, �� ���� �⵿���. �浹üũO ����O
	* MONSTER : ���� = ����
	* PLAYER : ���� �ٸ� �������� �����ؾ� �ұ�? ��� �� �غ��߰���
	* BUFF_CRYSTAL : �ϴ� �̷��� ����µ�. �浹üũX ����O�� ������Ʈ
	*/
	enum class ObjectCategory :BYTE{
		START = 0,
		LAND = 0,
		NATURAL_FEATURE,
		MONSTER,
		PLAYER,
		BUFF_CRYSTAL,
		END
	};

private:
	std::map<BYTE, std::vector<CObject*>> m_mObjectList;

	CObjectManager();
};





#endif