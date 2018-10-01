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
	if (damege >= this->currentHealth)
	{
		this->currentHealth = 0;
	}
	else
	{
		this->currentHealth -= damege;
	}
	return damege;
}

bool Body::IsDead(void)
{
	if (this->currentHealth <= 0) return true;
	return false;
}


unsigned int Body::GetCurrentHealth(void)
{
	return this->currentHealth;
}

std::string & Body::WhoAmI(void)
{
	return this->name;
}

void Body::WhoAmI(const char * name)
{
	this->name.assign(name);
}

unsigned int Body::GetLevel(void)
{
	return this->level;
}

void Body::SetLevel(unsigned int level)
{
	this->level = level;
}

unsigned int Body::GetMaxHealth(void)
{
	return this->maxHealth;
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
	cout << plr->WhoAmI() << "\tLV:" << plr->GetLevel() << endl;
	cout << " HP:\t" << this->plr->GetCurrentHealth() << " / "
		<< this->plr->GetMaxHealth() << endl;
	this->PrintLine();
	cout << mst->WhoAmI() << "\tLV:" << mst->GetLevel() << endl;
	cout << " HP:\t" << this->mst->GetCurrentHealth() << " / "
		<< this->mst->GetMaxHealth() << endl;
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
	this->SetAtkModifier(1.0);
	this->SetLevel(1);
}

void Player::SetMaxHealth(void)
{
	//����ֵ = k * level + 128
	const double k = 1.0;
	this->maxHealth = static_cast<unsigned int>(k * this->level + 128);
}


unsigned int Player::ResetCurrentHealth(void)
{
	this->currentHealth = this->maxHealth;
	return this->currentHealth;
}

unsigned int Player::GetAtk(double k)
{
	//����������4
	return static_cast<unsigned int>(
		(k * this->level + 4)*(this->atkModifier)
		);
}

void Player::SetAtkModifier(double atkModifier)
{
	//������С�ڵ���0
	if (atkModifier <= 0) return;
	this->atkModifier = atkModifier;
}

double Player::GetAtkModifier(void)
{
	return this->atkModifier;
}



unsigned int Monster::GetAtk(double k)
{
	//Ĭ��4
	return 4;
}

void Monster::SetMaxHealth(void)
{
	//����ֵ = k * level + 128
	const double k = 1.0;
	this->maxHealth = static_cast<unsigned int>(k * this->level + 128);
}

void Monster::SetMaxHealth(unsigned int maxHealth)
{
	this->maxHealth = maxHealth;
}

unsigned int Monster::ResetCurrentHealth(void)
{
	this->currentHealth = maxHealth;
	return this->currentHealth;
}
