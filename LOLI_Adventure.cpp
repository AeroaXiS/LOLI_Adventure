// LOLI_Adventure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

int main()
{
	Battlefield * bf = Battlefield::CreateBattlefield();
	Player plr;
	plr.SetName("LOLI");
	plr.SetLevel(5);
	plr.SetMaxHealth();
	plr.ResetCurrentHealth();
	plr.SetAtkBonus(1.0);
	plr.UpdateBasicAtk();
	plr.UpdateBasicDef();
	Monster mst1;
	mst1.SetExpDrop(8192);
	mst1.SetLevel(1);
	mst1.SetMaxHealth(128);
	mst1.ResetCurrentHealth();
	mst1.SetName("大哥");
	mst1.UpdateBasicAtk();
	mst1.UpdateBasicDef();
	Monster mst2(mst1);
	mst2.SetName("大哥的跟班");
	mst2.SetMaxHealth(256);
	mst2.ResetCurrentHealth();
	bf->JoinMonster(&mst1);
	bf->JoinMonster(&mst2);
	bf->JoinPlayer(&plr);
	bf->Start();
	return 0;
}