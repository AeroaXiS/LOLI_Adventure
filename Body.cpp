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
	//伤害暂时是确定的!
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
	//正常
	if (this->player != nullptr &&
		this->monster != nullptr)
	{
		return true;
	}
	//警告
	std::cout << "[错误] 试图在数据不足时进行Battlefield::Start()"
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
	//用于转换的字符串流
	std::stringstream ss;
	//获得造成的伤害
	unsigned int player_hit = this->player->Battle_Hit(this->monster);
	//转化
	ss << player->WhoAmI() << "\t对\t" << monster->WhoAmI()
		<< "\t造成\t" << player_hit << "\t伤害！";
	//注入
	this->AddMessage(ss.str().c_str());
	//清空
	ss.clear();
	ss.str("");
	//再来一遍
	unsigned int monster_hit = this->monster->Battle_Hit(this->player);
	ss << monster->WhoAmI() << "\t对\t" << player->WhoAmI()
		<< "\t造成\t" << monster_hit << "\t伤害！";
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
		//将现在是第几回合放进提示
		if (battle_round == prev_battle_round)
		{
			//不需要放提示
		}
		else
		{
			ss.clear();
			ss.str("");
			ss << "第\t" << battle_round << "\t回合";
			this->AddMessage(ss.str().c_str());
			prev_battle_round = battle_round;
		}
		//清空
		system("cls");
		//打印状态
		this->ShowState();
		//打印提示
		this->ShowMessages();
		this->PrintLine();
		//打印可以做的事情
		this->Start_Interaction_ListCommand();
		//命令
		switch (_getch())
		{
			//攻击
		case 'A':
		case 'a':
			this->AddMessage("玩家选择攻击！");
			this->AttackRound();
			//回合数加一
			battle_round++;
			break;
		default:
			break;
		}
		//死亡判定
		if (this->IsFinshed()) quit = true;
	}
	return false;
}

void Battlefield::Start_Interaction_ListCommand(void)
{
	std::cout << "A-攻击" << std::endl;
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
	//如果消息数量不足4条
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
	//首先检测是不是可以开战
	if (!this->Start_IsReady())
	{
		//不可以就返回战斗失败
		return false;
	}

	//战斗循环
	while (this->Start_Interaction())
	{

	}

	//赢了吗
	bool isWin = false;
	//战斗结束，谁死了，如何结算
	if (this->player->IsDead())
	{
		//玩家输了
		this->AddMessage("失败了！");
		isWin = false;
	}
	else if (this->monster->IsDead())
	{
		//玩家赢了
		this->AddMessage("胜利了！");
		isWin = true;
	}
	else
	{
		//既然跳出了战斗循环但是没有人死，大概不可能的情况
		std::cout << "[错误] 战场结算出现灵异事件" << std::endl;
		WaitAnyKey();
		isWin = false;
	}
	//让玩家知道结果
	system("cls");
	this->ShowState();
	this->ShowMessages();
	WaitAnyKey();
	return isWin;
}