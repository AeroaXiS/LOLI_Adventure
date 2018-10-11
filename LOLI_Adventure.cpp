// LOLI_Adventure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

int main()
{
	Battlefield * bf = Battlefield::CreateBattlefield();
	Player plr;
	plr.SetName("LOLI");
	Monster mst1, mst2;
	mst1.SetName("叔叔甲");
	mst2.SetName("叔叔乙");
	plr.SetLevel(5);
	plr.SetMaxHealth();
	bf->JoinMonster(&mst1)->ResetCurrentHealth();
	bf->JoinMonster(&mst2)->ResetCurrentHealth();
	bf->JoinPlayer(&plr)->ResetCurrentHealth();
	bf->Start();
	return 0;
}