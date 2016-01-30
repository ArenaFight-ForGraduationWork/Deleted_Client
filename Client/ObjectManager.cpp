#include "stdafx.h"
#include "ObjectManager.h"

#include "Object.h"
#include "Shader.h"





CObjectManager::CObjectManager()
{
	for (BYTE i = (BYTE)ObjectType::START; i < (BYTE)ObjectType::END; ++i)
	{
		m_mObjects[(ObjectType)i] = std::vector<CObject*>();
	}

	m_mShaders[ShaderType::IlluminatedTextured] = new CIlluminatedTexturedShader();
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
	m_mShaders[ShaderType::IlluminatedTextured]->InsertObject(pObject);/* 해당하는 shader에 넣을것. 어느 쉐이더인지는 ResourceManager에서 알려줄거야 */

	m_mObjects[(ObjectType)(id / 10000)].push_back(pObject);
}
void CObjectManager::Insert(UINT id, D3DXVECTOR3 position, D3DXVECTOR3 direction)
{
	/* id관련 설명은 ObjectManager헤더파일 맨 위를 참고 */
	CObject *pObject = new CObject(id);

	pObject->SetPosition(position);
	/* 앗 setdirection이 없다 */
	m_mShaders[ShaderType::IlluminatedTextured]->InsertObject(pObject);/* 해당하는 shader에 넣을것. 어느 쉐이더인지는 ResourceManager에서 알려줄거야 */

	m_mObjects[(ObjectType)(id / 10000)].push_back(pObject);
}

CObject* CObjectManager::FindObject(UINT id)
{
	for (auto obj : m_mObjects[(ObjectType)(id / 10000)])
	{
		if (id == obj->GetId())
			return obj;
	}
}

const std::vector<CObject*> CObjectManager::FindObjectInCategory(const UINT id)
{
	return m_mObjects[(ObjectType)(id / 10000)];
}

void CObjectManager::DeleteObject(UINT id)
{
	for (short i = 0; i < m_mObjects[(ObjectType)(id / 10000)].size(); ++i)
	{
		if (id == m_mObjects[(ObjectType)(id / 10000)][i]->GetId())
		{
			// 1) 쉐이더와의 연결 해제

			// 2) 오브젝트맵에서 삭제
			CObject *pObject = m_mObjects[(ObjectType)(id / 10000)][i];
			m_mObjects[(ObjectType)(id / 10000)].erase(m_mObjects[(ObjectType)(id / 10000)].begin() + i);

			// 3) 해당 오브젝트 제거
			pObject->~CObject();
		}
	}
}

void CObjectManager::DeleteObjectAll()
{
	for (short i = 0; i < m_mObjects.size(); ++i)
	{
		for (auto obj : m_mObjects[(ObjectType)i])
		{
			obj->~CObject();
		}
		m_mObjects[(ObjectType)i].clear();
	}
	m_mObjects.clear();
}