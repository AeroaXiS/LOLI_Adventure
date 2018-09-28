#include "pch.h"
#include "Body.h"

Battlefield * Battlefield::pBattlefield = nullptr;

Body::Body()
{
}


Body::~Body()
{
}

unsigned int Body::Battle_Hit(Body * enemy)
{
	//�˺���ʱ��ȷ����!
	return enemy->Battle_Suffer(4);
}

unsigned int Body::Battle_Suffer(unsigned int damege)
{
	if (damege >= this->health)
	{
		this->health = 0;
	}
	else
	{
		this->health -= damege;
	}
	return damege;
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

std::string & Body::WhoAmI(void)
{
	return this->name;
}

void Body::WhoAmI(const char * name)
{
	this->name.assign(name);
}

bool Battlefield::Start_IsReady(void)
{
	//����
	if (this->player != nullptr &&
		this->monster != nullptr)
	{
		return true;
	}
	//����
	std::cout << "[����] ��ͼ�����ݲ���ʱ����Battlefield::Start()"
		<< std::endl;
	WaitAnyKey();
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

bool Battlefield::AttackRound(void)
{
	//����ת�����ַ�����
	std::stringstream ss;
	//�����ɵ��˺�
	unsigned int player_hit = this->player->Battle_Hit(this->monster);
	//ת��
	ss << player->WhoAmI() << "\t��\t" << monster->WhoAmI()
		<< "\t���\t" << player_hit << "\t�˺���";
	//ע��
	this->AddMessage(ss.str().c_str());
	//���
	ss.clear();
	ss.str("");
	//����һ��
	unsigned int monster_hit = this->monster->Battle_Hit(this->player);
	ss << monster->WhoAmI() << "\t��\t" << player->WhoAmI()
		<< "\t���\t" << monster_hit << "\t�˺���";
	this->AddMessage(ss.str().c_str());
	return true;
}

bool Battlefield::Start_Interaction(void)
{
	bool quit = false;
	unsigned int battle_round = 1, prev_battle_round = 1;;
	std::stringstream ss;
	while (!quit)
	{
		//�������ǵڼ��غϷŽ���ʾ
		if (battle_round == prev_battle_round)
		{
			//����Ҫ����ʾ
		}
		else
		{
			ss.clear();
			ss.str("");
			ss << "��\t" << battle_round << "\t�غ�";
			this->AddMessage(ss.str().c_str());
			prev_battle_round = battle_round;
		}
		//���
		system("cls");
		//��ӡ״̬
		this->ShowState();
		//��ӡ��ʾ
		this->ShowMessages();
		this->PrintLine();
		//��ӡ������������
		this->Start_Interaction_ListCommand();
		//����
		switch (_getch())
		{
			//����
		case 'A':
		case 'a':
			this->AddMessage("���ѡ�񹥻���");
			this->AttackRound();
			//�غ�����һ
			battle_round++;
			break;
		default:
			break;
		}
		//�����ж�
		if (this->IsFinshed()) quit = true;
	}
	return false;
}

void Battlefield::Start_Interaction_ListCommand(void)
{
	std::cout << "A-����" << std::endl;
}

bool Battlefield::ShowState(void)
{
	using namespace std;
	this->PrintLine();
	cout << player->WhoAmI() << endl
		<< " HP:\t" << this->player->Health() << endl;
	this->PrintLine();
	cout << monster->WhoAmI() << endl
		<< " HP:\t" << this->monster->Health() << endl;
	this->PrintLine();
	return true;
}

bool Battlefield::ShowMessages(void)
{
	int delta;
	//�����Ϣ��������4��
	if (this->vMessage.size() <= 8)
	{
		delta = this->vMessage.size();
	}
	else
	{
		delta = 9;
	}
	for (auto iter = this->vMessage.end() - delta;
		 iter != vMessage.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
	return true;
}

bool Battlefield::AddMessage(const char * str)
{
	if (this->vMessage.size() >= 64)
	{
		this->vMessage.erase(this->vMessage.begin());
	}
	this->vMessage.emplace_back(str);
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

void Battlefield::PrintLine(void)
{
	using namespace std;
	cout << "=================================" << endl;
}

bool Battlefield::Start(void)
{
	//���ȼ���ǲ��ǿ��Կ�ս
	if (!this->Start_IsReady())
	{
		//�����Ծͷ���ս��ʧ��
		return false;
	}

	//ս��ѭ��
	while (this->Start_Interaction())
	{

	}

	//Ӯ����
	bool isWin = false;
	//ս��������˭���ˣ���ν���
	if (this->player->IsDead())
	{
		//�������
		this->AddMessage("ʧ���ˣ�");
		isWin = false;
	}
	else if (this->monster->IsDead())
	{
		//���Ӯ��
		this->AddMessage("ʤ���ˣ�");
		isWin = true;
	}
	else
	{
		//��Ȼ������ս��ѭ������û����������Ų����ܵ����
		std::cout << "[����] ս��������������¼�" << std::endl;
		WaitAnyKey();
		isWin = false;
	}
	//�����֪�����
	system("cls");
	this->ShowState();
	this->ShowMessages();
	WaitAnyKey();
	return isWin;
}