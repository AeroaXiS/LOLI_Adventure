#include "pch.h"
#include "Body.h"

Battlefield * Battlefield::pBattlefield = nullptr;

Body::Body()
{
}


Body::~Body()
{
}

unsigned int Body::BattleCommonHit(Body * enemy)
{
	//Ĭ�Ϸ�����2
	return enemy->BattleSuffer(RangeUniformRandom(this->GetAtk(1), 0.2));
}

unsigned int Body::BattleSuffer(unsigned int damege)
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
	if (this->plr != nullptr &&
		this->mst != nullptr)
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

bool Battlefield::WhoseBattlefield(Player * plr, Monster * mst)
{
	this->plr = plr;
	this->mst = mst;
	return true;
}

bool Battlefield::AttackRound(void)
{
	//����ת�����ַ�����
	std::stringstream ss;
	//�����ɵ��˺�
	unsigned int plr_hit = this->plr->BattleCommonHit(this->mst);
	//ת��
	ss << plr->WhoAmI() << "\t��\t" << mst->WhoAmI()
		<< "\t���\t" << plr_hit << "\t�˺���";
	//ע��
	this->AddMessage(ss.str().c_str());
	//���
	ss.clear();
	ss.str("");
	//����һ��
	unsigned int mst_hit = this->mst->BattleCommonHit(this->plr);
	ss << mst->WhoAmI() << "\t��\t" << plr->WhoAmI()
		<< "\t���\t" << mst_hit << "\t�˺���";
	this->AddMessage(ss.str().c_str());
	return true;
}

bool Battlefield::Start_Interaction(void)
{
	system("cls");
	this->ShowState();
	this->ShowMessages();
	this->PrintLine();
	std::cout << "A-����" << std::endl;
	switch (_getch())
	{
	case'a':
	case'A':
		this->AddMessage("������");
		this->AttackRound();
		if (this->IsFinshed()) return false; //����֮��ս����������ѭ��
		else return true;
		break;
	default:
		return true;
		break;
	}
}

bool Battlefield::ShowState(void)
{
	using namespace std;
	this->PrintLine();
	cout << plr->WhoAmI() << endl
		<< " HP:\t" << this->plr->Health() << endl;
	this->PrintLine();
	cout << mst->WhoAmI() << endl
		<< " HP:\t" << this->mst->Health() << endl;
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
	if (this->plr->IsDead() || this->mst->IsDead())
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
		UniformRandomSrand();
	}

	//Ӯ����
	bool isWin = false;
	//ս��������˭���ˣ���ν���
	if (this->plr->IsDead())
	{
		//�������
		this->AddMessage("ʧ���ˣ�");
		isWin = false;
	}
	else if (this->mst->IsDead())
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

Player::Player()
{
	atkModifier = 1.0;
}

unsigned int Player::GetAtk(double k)
{
	//����������4
	//Ĭ�ϵȼ�5
	return static_cast<unsigned int>(k * 5 + 4);
}

unsigned int Monster::GetAtk(double k)
{
	//Ĭ��4
	return 4;
}
