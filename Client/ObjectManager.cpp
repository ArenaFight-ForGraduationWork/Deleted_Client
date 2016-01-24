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

void CObjectManager::Insert(UINT id, int x, int y, int z, int dx, int dy, int dz)
{
	/* id관련 설명은 ObjectManager헤더파일 맨 위를 참고 */
	CObject *pObject = new CObject(id);
	pObject->SetPosition(x, y, z);
	/* 앗 setdirection이 없다 */
	m_mObjectList[id / 10000].push_back(pObject);
}
void CObjectManager::Insert(UINT id, D3DXVECTOR3 position, D3DXVECTOR3 direction)
{
	/* id관련 설명은 ObjectManager헤더파일 맨 위를 참고 */
	CObject *pObject = new CObject(id);
	pObject->SetPosition(position);
	/* 앗 setdirection이 없다 */
	m_mObjectList[id / 10000].push_back(pObject);

}

CObject* CObjectManager::FindObject(UINT id)
{
	for (auto obj : m_mObjectList[id / 10000])
	{
		if (id == obj->GetId())
			return obj;
	}
}

const std::vector<CObject*> CObjectManager::FindObjectInCategory(const UINT id)
{
	return m_mObjectList[id / 10000];
}

void CObjectManager::DeleteObject(UINT id)
{
	for (short i = 0; i < m_mObjectList[id / 10000].size(); ++i)
	{
		if (id == m_mObjectList[id / 10000][i]->GetId())
		{
			CObject *pObject = m_mObjectList[id / 10000][i];
			m_mObjectList[id / 10000].erase(m_mObjectList[id / 10000].begin() + i);
			pObject->~CObject();
		}

	}
}

void CObjectManager::DeleteObjectAll()
{
	for (short i = 0; i < m_mObjectList.size(); ++i)
	{
		for (auto obj : m_mObjectList[i])
		{
			obj->~CObject();
		}
		m_mObjectList[i].clear();
	}
	m_mObjectList.clear();
}