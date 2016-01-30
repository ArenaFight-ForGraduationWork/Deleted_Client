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
	/* id���� ������ ObjectManager������� �� ���� ���� */
	CObject *pObject = new CObject(id);
	pObject->SetPosition(x, y, z);

	/* �� setdirection�� ���� */
	m_mShaders[ShaderType::IlluminatedTextured]->InsertObject(pObject);/* �ش��ϴ� shader�� ������. ��� ���̴������� ResourceManager���� �˷��ٰž� */

	m_mObjects[(ObjectType)(id / 10000)].push_back(pObject);
}
void CObjectManager::Insert(UINT id, D3DXVECTOR3 position, D3DXVECTOR3 direction)
{
	/* id���� ������ ObjectManager������� �� ���� ���� */
	CObject *pObject = new CObject(id);

	pObject->SetPosition(position);
	/* �� setdirection�� ���� */
	m_mShaders[ShaderType::IlluminatedTextured]->InsertObject(pObject);/* �ش��ϴ� shader�� ������. ��� ���̴������� ResourceManager���� �˷��ٰž� */

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
			// 1) ���̴����� ���� ����

			// 2) ������Ʈ�ʿ��� ����
			CObject *pObject = m_mObjects[(ObjectType)(id / 10000)][i];
			m_mObjects[(ObjectType)(id / 10000)].erase(m_mObjects[(ObjectType)(id / 10000)].begin() + i);

			// 3) �ش� ������Ʈ ����
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