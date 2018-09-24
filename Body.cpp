#include "pch.h"
#include "Body.h"

Battlefield * Battlefield::pBattlefield = nullptr;

Body::Body()
{
}


Body::~Body()
{
}

void Body::Battle_Hit(Body * enemy)
{
	enemy->Battle_Suffer(4);
}

void Body::Battle_Suffer(unsigned int damege)
{
	if (damege >= this->health)
	{
		this->health = 0;
	}
	else
	{
		this->health -= damege;
	}
}

bool Body::IsDead(void)
{
	if (this->health <= 0) return true;
	return false;
}

unsigned int Body::Health(void)
{
	return this->health;
}

unsigned int Body::Health(unsigned int health)
{
	this->health = health;
	return this->health;
}

bool Battlefield::IsAllReady(void)
{
	if (this->player != nullptr &&
		this->monster != nullptr)
	{
		return true;
	}
	return false;
}

Battlefield * Battlefield::CreateBattlefield(void)
{
	if (Battlefield::pBattlefield != nullptr)
	{
		return Battlefield::pBattlefield;
	}
	pBattlefield = new Battlefield;
	return pBattlefield;
}

bool Battlefield::WhoseBattlefield(Player * player, Monster * monster)
{
	this->player = player;
	this->monster = monster;
	return true;
}

bool Battlefield::Fuck(void)
{
	this->player->Battle_Hit(this->monster);
	this->monster->Battle_Hit(this->player);
	return true;
}

void Battlefield::WaitKeyboard(void)
{
	///std::getline(std::cin, keyboardCache);
	keyboardPressed = _getch();
	if (keyboardPressed == '\r')
	{
		//回车有\r\n两部分
		_getch();
		return;
	}
	else if (keyboardPressed == 0x00 || keyboardPressed == 0xE0)
	{
		//拓展字符要想办法抛弃掉后面的部分
		_getch();
		return;
	}
	else
	{
		return;
	}
}


bool Battlefield::ShowState(void)
{
	using namespace std;
	cout << "=========================" << endl;
	cout << "LOLI" << endl
		<< " HP:\t" << this->player->Health() << endl;
	cout << "=========================" << endl;
	cout << "Monster" << endl
		<< " HP:\t" << this->monster->Health() << endl;
	cout << "=========================" << endl;
	return true;
}

bool Battlefield::IsFinshed(void)
{
	if (this->player->IsDead() || this->monster->IsDead())
	{
		return true;
	}
	return false;
}

bool Battlefield::Start(void)
{
	//首先检测是不是可以开战
	if (!this->IsAllReady())
	{
		//警告返回战斗失败
		std::cout << "[错误] 试图在数据不足时进行Battlefield::Start()"
			<< std::endl;
		this->WaitKeyboard();
		return false;
	}

	//战斗循环，只要没人输就继续
	while (!this->IsFinshed())
	{
		this->ShowState();
		std::cout << "按下回车键下一回合..." << std::endl;
		this->WaitKeyboard();
		this->Fuck();
	}

	//战斗结束，谁死了，如何结算
	if (this->player->IsDead())
	{
		//玩家输了
		this->ShowState();
		std::cout << "失败了！" << std::endl;
		this->WaitKeyboard();
		return false;
	}
	else if (this->monster->IsDead())
	{
		//玩家赢了
		this->ShowState();
		std::cout << "胜利了！" << std::endl;
		this->WaitKeyboard();
		return true;
	}
	else
	{
		//既然跳出了战斗循环但是没有人死，大概不可能的情况
		std::cout << "[错误] 战场结算出现灵异事件" << std::endl;
		this->WaitKeyboard();
		return false;
	}
	return false;
}
