#include "stdafx.h"
#include "ObjectManager.h"

#include "Object.h"
#include "Shader.h"





CObjectManager::CObjectManager(ID3D11Device *pd3dDevice)
{
	for (BYTE i = (BYTE)ObjectType::START; i < (BYTE)ObjectType::END; ++i)
	{
		m_mObjects[(ObjectType)i] = std::vector<CObject*>();
	}

	pResourceManager = CResourceManager::GetSingleton(pd3dDevice);
}

CObjectManager::~CObjectManager()
{
}

CObjectManager* CObjectManager::GetSingleton(ID3D11Device *pd3dDevice)
{
	static CObjectManager instance(pd3dDevice);
	return &instance;
}

void CObjectManager::Insert(UINT id, int x, int y, int z, int dx, int dy, int dz)
{
	/* id���� ������ ObjectManager������� �� ���� ���� */
	CObject *pObject = new CObject(id);
	pObject->SetMesh(pResourceManager->GetMesh(CResourceManager::ResourceType::Cube));
	pObject->SetMaterial(pResourceManager->GetMaterial(CResourceManager::ResourceType::Cube));
	pObject->SetTexture(pResourceManager->GetTexture(CResourceManager::ResourceType::Cube));
	pObject->SetPosition(x, y, z);
	/* �� setdirection�� ���� */
	m_mObjects[(ObjectType)(id / 10000)].push_back(pObject);

	CShader *pShader = pResourceManager->GetShaderByResourceType(CResourceManager::ResourceType::Cube);
	pShader->InsertObject(pObject);
}
void CObjectManager::Insert(UINT id, D3DXVECTOR3 position, D3DXVECTOR3 direction)
{
	/* id���� ������ ObjectManager������� �� ���� ���� */
	CObject *pObject = new CObject(id);
	pObject->SetMesh(pResourceManager->GetMesh(CResourceManager::ResourceType::Cube));
	pObject->SetMaterial(pResourceManager->GetMaterial(CResourceManager::ResourceType::Cube));
	pObject->SetTexture(pResourceManager->GetTexture(CResourceManager::ResourceType::Cube));
	pObject->SetPosition(position);
	/* �� setdirection�� ���� */
	m_mObjects[(ObjectType)(id / 10000)].push_back(pObject);

	CShader *pShader = pResourceManager->GetShaderByResourceType(CResourceManager::ResourceType::Cube);
	pShader->InsertObject(pObject);
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
			CShader *pShader;
			for (BYTE i = (BYTE)CResourceManager::ShaderType::START; i < (BYTE)CResourceManager::ShaderType::END; ++i)
			{
				pShader = pResourceManager->GetShaderByShaderType((CResourceManager::ShaderType)i);
				pShader->ReleaseObject(id);
				/* 
					�� �κ� ���̴� ��ü�� ���ϱ� �̰� ��� �� �ٲ�߰ڴ�
					bool�� ��ȯ�ϰ� �ؼ� Ȯ���ұ�
				*/
			}

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
	// 1) ��� ���̴��� ������Ʈ���� ���� ����
	CShader *pShader;
	for (BYTE i = (BYTE)CResourceManager::ShaderType::START; i < (BYTE)CResourceManager::ShaderType::END; ++i)
	{
		pShader = pResourceManager->GetShaderByShaderType((CResourceManager::ShaderType)i);
		pShader->ReleaseAllObjects();
	}

	// 2) �ش� ������Ʈ ���� �� ����
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