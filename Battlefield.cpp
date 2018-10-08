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

bool Battlefield::Start_IsWin(void)
{
	if (this->pPlayer->IsDead())
	{
		//�������
		this->AddMessage("ʧ���ˣ�");
		return false;
	}
	else if (this->pMonster->IsDead())
	{
		//���Ӯ��
		this->AddMessage("ʤ���ˣ�");
		return true;
	}
	else
	{
		//�ܹ��������ﲢ��û�������ǲ����ܵ�
		std::cout << "[����] ս��������������¼�" << std::endl;
		WaitAnyKey();
		return false;
	}
	return false;
}

void Battlefield::Start_ShowResult(void)
{
	system("cls");
	this->ShowState();
	this->ShowMessage();
	WaitAnyKey();
}

void Battlefield::Start_ShowMonsterText(void)
{
	ss.clear();
	ss.str("");
	ss << "������" << this->pMonster->GetLevel() << "����" << this->pMonster->WhoAmI();
	this->AddMessage();
}

void Battlefield::Start_Award(void)
{
	//�Ӿ���
	pPlayer->AwardExp(pMonster->GetExpDrop());
	ss.clear();
	ss.str("");
	ss << "����� " << pMonster->GetExpDrop() << " �㾭��";
	this->AddMessage();
	//����
	if (this->pPlayer->CheckLevelUp() != 0)
	{
		ss.clear();
		ss.str("");
		ss << "������ " << this->pPlayer->GetLevel() << " ����";
		this->AddMessage();
	}
}

int Battlefield::AddAction(Body * pbySender, Body * pbyVictim, ActionType at, unsigned int data1, unsigned int data2)
{
	Action tmpA;
	tmpA.pbySender = pbySender;
	tmpA.pbyVictim = pbyVictim;
	tmpA.at = at;
	tmpA.unData1 = data1;
	tmpA.unData2 = data2;
	this->vActionQueue.push_back(tmpA);
	return 0;
}

int Battlefield::FlushActionQueue(void)
{
	std::vector<Action> emptyVec;
	this->vActionQueue.swap(emptyVec);
	return 0;
}

int Battlefield::RunAcionQueue(void)
{
	for (auto &a : this->vActionQueue)
	{
		//���
		ss.clear();
		ss.str("");
		switch (a.at)
		{
		case AT_NORMAL:
			unsigned int damage;
			damage = a.pbySender->BattleCommonHit(a.pbyVictim);
			ss << a.pbySender->WhoAmI() << " �� "
				<< a.pbyVictim->WhoAmI() << " ��� "
				<< damage << " �˺�";
			this->AddMessage(ss.str().c_str());
			break;
		default:
			ss << a.pbySender->WhoAmI() << " ��֪����";
			this->AddMessage(ss.str().c_str());
			break;
		}
	}
	return 0;
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

bool Battlefield::Start_IsFinshed(void)
{
	if (this->pPlayer->IsDead() || this->pMonster->IsDead())
	{
		return true;
	}
	return false;
}

bool Battlefield::Start_Interaction(void)
{
	system("cls");
	this->ShowState();
	this->ShowMessage();
	this->PrintLine();
	std::cout << "A-����" << std::endl;
	//�Ѿ���ȡ�ж�����
	bool actionTaken = false;
	while (!actionTaken)
	{
		switch (_getch())
		{
		case'a':
		case'A':
			this->AddMessage("������");
			this->AddAction(this->pPlayer, this->pMonster,
							AT_NORMAL, 0, 0);
			actionTaken = true;
			break;
		default:
			break;
		}
	}
	return true;
}

void Battlefield::PrintLine(void)
{
	using namespace std;
	cout <<
		"================================================================"
		<< endl;
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

bool Battlefield::ShowMessage(void)
{
	int delta;
	//�����Ϣ��������8��
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

//����ʾ������ʾ�б�����64��
bool Battlefield::AddMessage(const char * str)
{
	if (this->vMessage.size() >= 64)
	{
		this->vMessage.erase(this->vMessage.begin());
	}
	this->vMessage.emplace_back(str);
	return true;
}

//��ss�����ݷŽ���ʾ�б���ݲ���
bool Battlefield::AddMessage(void)
{
	this->AddMessage(this->ss.str().c_str());
	return true;
}

bool Battlefield::FlushMessage(void)
{
	std::vector<std::string> emptyVec;
	this->vMessage.swap(emptyVec);
	return true;
}

bool Battlefield::Start(void)
{
	//���ȼ���ǲ��ǿ��Կ�ս �����Ծͷ���ս��ʧ��
	if (!this->Start_IsReady()) return false;

	//�����������
	this->Start_ShowMonsterText();

	//ս��ѭ��
	while (!this->Start_IsFinshed())
	{
		UniformRandomSrand();
		this->Start_Interaction();
		//todo:	��������������
		//��������ʱ��
		this->AddAction(this->pMonster, this->pPlayer, AT_NORMAL, 0, 0);
		this->RunAcionQueue();
		this->FlushActionQueue();
	}

	//Ӯ����ʤ������
	if (this->Start_IsWin()) this->Start_Award();

	//��ӡ������
	this->Start_ShowResult();

	return true;
}