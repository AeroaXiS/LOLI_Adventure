#include "Battlefield.h"
#include "pch.h"

Battlefield * Battlefield::pBattlefield = nullptr;


bool Battlefield::Start_IsReady(void)
{
	//����
	if (this->pPlayer != nullptr &&
		this->pMonster != nullptr)
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
	this->pPlayer = plr;
	this->pMonster = mst;
	return true;
}

bool Battlefield::AttackRound(void)
{
	//����ת�����ַ�����
	std::stringstream ss;
	//�����ɵ��˺�
	unsigned int plr_hit = this->pPlayer->BattleCommonHit(this->pMonster);
	//ת��
	ss << pPlayer->WhoAmI() << "\t��\t" << pMonster->WhoAmI()
		<< "\t���\t" << plr_hit << "\t�˺���";
	//ע��
	this->AddMessage(ss.str().c_str());
	//���
	ss.clear();
	ss.str("");
	//����һ��
	unsigned int mst_hit = this->pMonster->BattleCommonHit(this->pPlayer);
	ss << pMonster->WhoAmI() << "\t��\t" << pPlayer->WhoAmI()
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
	cout << pPlayer->WhoAmI() << "\tLV:" << pPlayer->GetLevel()
		<< " Exp:" << pPlayer->ExpHave() << " / " << pPlayer->ExpNeed() << endl;
	cout << " HP:\t" << this->pPlayer->GetCurrentHealth() << " / "
		<< this->pPlayer->GetMaxHealth() << endl;
	this->PrintLine();
	cout << pMonster->WhoAmI() << "\tLV:" << pMonster->GetLevel() << endl;
	cout << " HP:\t" << this->pMonster->GetCurrentHealth() << " / "
		<< this->pMonster->GetMaxHealth() << endl;
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
	if (this->pPlayer->IsDead() || this->pMonster->IsDead())
	{
		return true;
	}
	return false;
}

void Battlefield::PrintLine(void)
{
	using namespace std;
	cout <<
		"================================================================"
		<< endl;
}

bool Battlefield::Start(void)
{
	std::stringstream ss;

	//���ȼ���ǲ��ǿ��Կ�ս
	if (!this->Start_IsReady())
	{
		//�����Ծͷ���ս��ʧ��
		return false;
	}

	//�����������
	ss << "������" << this->pMonster->GetLevel() << "����" << this->pMonster->WhoAmI();
	this->AddMessage(ss.str().c_str());

	//ս��ѭ��
	while (this->Start_Interaction())
	{
		UniformRandomSrand();
	}

	//Ӯ����
	bool isWin = false;
	if (this->pPlayer->IsDead())
	{
		//�������
		this->AddMessage("ʧ���ˣ�");
		isWin = false;
	}
	else if (this->pMonster->IsDead())
	{
		//���Ӯ��
		this->AddMessage("ʤ���ˣ�");
		//�Ӿ���
		pPlayer->AwardExp(pMonster->GetExpDrop());
		ss.clear();
		ss.str("");
		ss << "����� " << pMonster->GetExpDrop() << " �㾭��";
		this->AddMessage(ss.str().c_str());
		isWin = true;
	}
	else
	{
		//��Ȼ������ս��ѭ������û����������Ų����ܵ����
		std::cout << "[����] ս��������������¼�" << std::endl;
		WaitAnyKey();
		isWin = false;
	}

	//ѭ���������
	while (pPlayer->IsAbleToLevelUp())
	{
		ss.clear();
		ss.str("");
		ss << "�ȼ������� " << pPlayer->LevelUp() << " ����";
		this->AddMessage(ss.str().c_str());
	}

	//�����֪�����
	system("cls");
	this->ShowState();
	this->ShowMessages();
	WaitAnyKey();
	return isWin;
}
