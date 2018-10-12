#include "pch.h"

Body::Body()
{
}

Body::~Body()
{
}

unsigned int Body::BattleCommonHit(Body * enemy)
{
	return enemy->BattleSuffer(RangeUniformRandom(this->GetAtk(1), 0.2));
}

unsigned int Body::BattleSuffer(unsigned int damage)
{
	//防御力的25%为减伤
	unsigned int damageRedution =
		static_cast<unsigned int>(this->GetDef(1.0)*0.25);
	//如果减伤大于等于伤害，伤害为1
	if (damageRedution >= damage)
	{
		damage = 1;
	}
	else
	{
		damage -= damageRedution;
	}
	if (damage >= this->unCurrentHealth)
	{
		this->unCurrentHealth = 0;
	}
	else
	{
		this->unCurrentHealth -= damage;
	}
	return damage;
}

bool Body::IsDead(void)
{
	if (this->unCurrentHealth <= 0) return true;
	return false;
}

unsigned int Body::GetCurrentHealth(void)
{
	return this->unCurrentHealth;
}

std::string & Body::GetName(void)
{
	return this->strName;
}

void Body::SetName(const char * name)
{
	this->strName.assign(name);
}

unsigned int Body::GetLevel(void)
{
	return this->unLevel;
}

void Body::SetLevel(unsigned int level)
{
	this->unLevel = level;
}

unsigned int Body::GetMaxHealth(void)
{
	return this->unMaxHealth;
}

Player::Player()
{
	this->SetAtkModifier(1.0);
	this->SetDefModifier(1.0);
	this->SetLevel(1);
	this->SetMaxHealth();
	this->ulExp = 0;
}

void Player::SetMaxHealth(void)
{
	//生命值 = k * level * level + 128
	const double k = 2.0;
	this->unMaxHealth =
		static_cast<unsigned int>(k * this->unLevel * this->unLevel + 128);
}

unsigned int Player::ResetCurrentHealth(void)
{
	this->unCurrentHealth = this->unMaxHealth;
	return this->unCurrentHealth;
}

unsigned int Player::GetAtk(double k)
{
	//基础攻击力4
	return static_cast<unsigned int>(
		(k * this->unLevel + 4)*(this->dAtkModifier)
		);
}

void Player::SetAtkModifier(double atkModifier)
{
	//不可以小于等于0
	if (atkModifier <= 0) return;
	this->dAtkModifier = atkModifier;
}

double Player::GetAtkModifier(void)
{
	return this->dAtkModifier;
}

unsigned int Player::GetDef(double k)
{
	//基础防御力4
	return static_cast<unsigned int>(
		(k*this->unLevel + 4)*(this->dDefModifier)
		);
}

void Player::SetDefModifier(double defModifier)
{
	this->dDefModifier = defModifier;
}

double Player::GetDefModifier(void)
{
	return this->dDefModifier;
}

unsigned int Player::LevelUp(void)
{
	this->unLevel++;
	return this->unLevel;
}

bool Player::IsAbleToLevelUp(void)
{
	if (ulExp >= this->GetExpNeed())
	{
		return true;
	}
	return false;
}

unsigned long Player::GetExpNeed(void)
{
	//到下一等级所需经验值计算公式 16x^2 + 128
	unsigned int x = this->unLevel - 1;
	return (x * x * 256 + 128);
}

unsigned long Player::GetExpHave(void)
{
	return this->ulExp;
}

unsigned long Player::AwardExp(unsigned long quantity)
{
	this->ulExp += quantity;
	return this->ulExp;
}

unsigned int Player::CheckLevelUp(void)
{
	if (!this->IsAbleToLevelUp())
	{
		//不可以升级
		return 0;
	}
	else
	{
		//循环检测可以升级多少次
		while (this->IsAbleToLevelUp())
		{
			this->LevelUp();
		}
		//升级完成
		return this->unLevel;
	}
	//错误?
	return 0;
}

Monster::Monster()
{
	this->SetLevel(1);
	this->SetMaxHealth(64);
	this->SetExpDrop(1024);
}

Monster::Monster(Monster & right)
{
	this->SetLevel(right.GetLevel());
	this->SetExpDrop(right.GetExpDrop());
	this->SetName(right.GetName().c_str());
}

unsigned int Monster::GetAtk(double k)
{
	return static_cast<unsigned int>(
		(k * this->unLevel + 4)
		);
}

unsigned int Monster::GetDef(double k)
{
	return static_cast<unsigned int>(
		(k*this->unLevel + 4)
		);
}

void Monster::SetMaxHealth(void)
{
	//生命值 = k * level + 128
	const double k = 1.0;
	this->unMaxHealth =
		static_cast<unsigned int>(k * this->unLevel * this->unLevel + 128);
}

void Monster::SetMaxHealth(unsigned int maxHealth)
{
	this->unMaxHealth = maxHealth;
}

unsigned int Monster::ResetCurrentHealth(void)
{
	this->unCurrentHealth = unMaxHealth;
	return this->unCurrentHealth;
}

unsigned long Monster::GetExpDrop(void)
{
	return this->ulExpDrop;
}

void Monster::SetExpDrop(unsigned long expDrop)
{
	this->ulExpDrop = expDrop;
}