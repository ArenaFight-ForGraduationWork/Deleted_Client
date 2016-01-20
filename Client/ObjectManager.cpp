#include "stdafx.h"
#include "ObjectManager.h"





CObjectManager::CObjectManager()
{
	for (BYTE i = (BYTE)ObjectCategory::START; i < (BYTE)ObjectCategory::END; ++i)
		m_mObjectList[i] = std::vector<CObject*>();
}

CObjectManager::~CObjectManager()
{
}

CObjectManager* CObjectManager::GetSingleton()
{
	static CObjectManager instance;
	return &instance;
}

void CObjectManager::Insert(int x, int y, int z, int dx, int dy, int dz)
{

}
void CObjectManager::Insert(D3DXVECTOR3 position, D3DXVECTOR3 direction)
{
}

	///* ~�����͸� ���� ������Ʈ�� �߰� */
	//void Insert(int x, int y, int z, int dx, int dy, int dz);
	//void Insert(D3DXVECTOR3 position, D3DXVECTOR3 direction);

	///* ��ü ������Ʈ �߿��� �ش� id�� ���� ������Ʈ�� ã�´� */
	//CObject* FindObject(int id);

	///* ������Ʈ ī�װ� �� id��° ī�װ��� ������Ʈ���� ��ȯ�Ѵ� */
	//const std::vector<CObject*> FindObjectInCategory(int id) const;

	///* id ?�� ������Ʈ�� ���� */
	//void DeleteObject(int id);

	///* ���� ������ �ִ� ��� ������Ʈ�� ���� */
	//void DeleteObjectAll();

