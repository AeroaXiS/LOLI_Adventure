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
		//�س���\r\n������
		_getch();
		return;
	}
	else if (keyboardPressed == 0x00 || keyboardPressed == 0xE0)
	{
		//��չ�ַ�Ҫ��취����������Ĳ���
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
	//���ȼ���ǲ��ǿ��Կ�ս
	if (!this->IsAllReady())
	{
		//���淵��ս��ʧ��
		std::cout << "[����] ��ͼ�����ݲ���ʱ����Battlefield::Start()"
			<< std::endl;
		this->WaitKeyboard();
		return false;
	}

	//ս��ѭ����ֻҪû����ͼ���
	while (!this->IsFinshed())
	{
		this->ShowState();
		std::cout << "���»س�����һ�غ�..." << std::endl;
		this->WaitKeyboard();
		this->Fuck();
	}

	//ս��������˭���ˣ���ν���
	if (this->player->IsDead())
	{
		//�������
		this->ShowState();
		std::cout << "ʧ���ˣ�" << std::endl;
		this->WaitKeyboard();
		return false;
	}
	else if (this->monster->IsDead())
	{
		//���Ӯ��
		this->ShowState();
		std::cout << "ʤ���ˣ�" << std::endl;
		this->WaitKeyboard();
		return true;
	}
	else
	{
		//��Ȼ������ս��ѭ������û����������Ų����ܵ����
		std::cout << "[����] ս��������������¼�" << std::endl;
		this->WaitKeyboard();
		return false;
	}
	return false;
}
