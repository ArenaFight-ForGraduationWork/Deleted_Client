#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "stdafx.h"
#include "Object.h"

/*
*		고민 : ObjectCategory
*		1) LAND와 NATURAL_FEATURE를 나눠야 하는 이유가 무엇인가
*			일단 둘 다 충돌체크O, 존재O, 움직임X
*		2) BUFF_CRYSTAL 
*			이름이 맘에 안 든다. 포괄적인 이름이 필요하다.
*			충돌체크X, 존재O인 물체
*/


class CObjectManager
{
public:
	CObjectManager* GetSingleton();
	~CObjectManager();

	/* ~데이터를 가진 오브젝트를 추가 */
	void Insert(int x, int y, int z, int dx, int dy, int dz);
	void Insert(D3DXVECTOR3 position, D3DXVECTOR3 direction);

	/* 전체 오브젝트 중에서 해당 id를 가진 오브젝트를 찾는다 */
	CObject* FindObject(int id);

	/* 오브젝트 카테고리 중 id번째 카테고리의 오브젝트들을 반환한다 */
	const std::vector<CObject*> FindObjectInCategory(int id) const;

	/* id ?의 오브젝트를 삭제 */
	void DeleteObject(int id);

	/* 현재 가지고 있는 모든 오브젝트를 삭제 */
	void DeleteObjectAll();

	/* ObjectList의 카테고리
	* LAND : 지형. 바닥, 벽
	* NATURAL_FEATURE : 나무, 돌 같은 잡동사니. 충돌체크O 존재O
	* MONSTER : 몬스터 = 보스
	* PLAYER : 나와 다른 유저들을 구분해야 할까? 고민 좀 해봐야겠음
	* BUFF_CRYSTAL : 일단 이렇게 써놨는데. 충돌체크X 존재O인 오브젝트
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