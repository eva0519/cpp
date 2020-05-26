#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	return true;
}

void CBullet::Update()
{
	// 매번 총알을 오른쪽으로 한칸 이동시킨다.
	m_tPos.x++;
}
