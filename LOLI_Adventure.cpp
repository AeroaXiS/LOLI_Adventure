// LOLI_Adventure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

int main()
{
	Battlefield * bf = Battlefield::CreateBattlefield();
	Player * loli = new Player;
	Monster * uncle = new Monster;

	loli->SetMaxHealth();
	loli->ResetCurrentHealth();
	loli->WhoAmI("LOLI"); 
	loli->SetAtkModifier(1);
	loli->SetLevel(1);

	uncle->WhoAmI("怪蜀黍");
	uncle->SetMaxHealth(128);
	uncle->SetExpDrop(512);
	uncle->SetLevel(1);

	loli->ResetCurrentHealth();
	uncle->ResetCurrentHealth();

	for (int i = 0; i != 16; i++)
	{
		bf->WhoseBattlefield(loli, uncle);
		bf->Start();
		loli->ResetCurrentHealth();
		uncle->ResetCurrentHealth();
	}
	return 0;
}