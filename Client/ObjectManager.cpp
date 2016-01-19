#include "stdafx.h"
#include "ObjectManager.h"





CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

CObjectManager* CObjectManager::GetSingleton()
{
	static CObjectManager *pInstance = new CObjectManager();
	return pInstance;
}