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

	///* ~데이터를 가진 오브젝트를 추가 */
	//void Insert(int x, int y, int z, int dx, int dy, int dz);
	//void Insert(D3DXVECTOR3 position, D3DXVECTOR3 direction);

	///* 전체 오브젝트 중에서 해당 id를 가진 오브젝트를 찾는다 */
	//CObject* FindObject(int id);

	///* 오브젝트 카테고리 중 id번째 카테고리의 오브젝트들을 반환한다 */
	//const std::vector<CObject*> FindObjectInCategory(int id) const;

	///* id ?의 오브젝트를 삭제 */
	//void DeleteObject(int id);

	///* 현재 가지고 있는 모든 오브젝트를 삭제 */
	//void DeleteObjectAll();

