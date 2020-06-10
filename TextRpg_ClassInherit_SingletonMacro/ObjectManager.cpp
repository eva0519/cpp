#include "ObjectManager.h"

DEFINITION_SINGLE(CObjectManager);

CObjectManager::CObjectManager()
{

}

CObjectManager::~CObjectManager()
{

}

bool CObjectManager::Init()
{
	return true;
}

CObj* CObjectManager::CreateObject(OBJECT_TYPE eType)
{
	return nullptr;
}
