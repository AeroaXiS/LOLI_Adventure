#include "pch.h"

Body::Body()
{
	this->strName = "未命名Body对象";
	this->unLevel = 1;
	this->dAtkBonus = 1.0;
	this->dDefBonus = 1.0;
	this->unMaxHealth = this->unLevel;
}

Body::~Body()
{
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

unsigned int Body::DecreaseHealth(unsigned int unDamage)
{
	if (unDamage >= this->unCurrentHealth)
	{
		this->unCurrentHealth = 0;
		return 0;
	}
	else
	{
		this->unCurrentHealth -= unDamage;
		return this->unCurrentHealth;
	}
}

unsigned int Body::IncreaseHealth(unsigned int unHeal)
{
	this->unCurrentHealth += unHeal;
	if (this->unCurrentHealth > this->unMaxHealth)
	{
		this->unCurrentHealth = this->unMaxHealth;
		return this->unCurrentHealth;
	}
	return this->unCurrentHealth;;
}

unsigned int Body::GetAtk(void)
{
	return static_cast<unsigned int>(this->unBasicAtk*this->dAtkBonus);
}

unsigned int Body::GetDef(void)
{
	return static_cast<unsigned int>(this->unBasicDef*this->dDefBonus);
}

void Body::SetAtkBonus(double dAtkBonus)
{
	if (dAtkBonus == 0.0) dAtkBonus = 1.0;
	this->dAtkBonus = dAtkBonus;
}

void Body::SetDefBonus(double dDefBonus)
{
	if (dDefBonus == 0.0) dDefBonus = 1.0;
	this->dDefBonus = dDefBonus;
}

Player::Player()
{
	this->SetMaxHealth();
	this->ResetCurrentHealth();
	this->UpdateBasicAtk();
	this->UpdateBasicDef();
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

unsigned int Player::UpdateBasicAtk(void)
{
	this->unBasicAtk =
		4 + this->unLevel * 4;
	return this->unBasicAtk;
}

unsigned int Player::UpdateBasicDef(void)
{
	this->unBasicDef =
		1 + this->unBasicDef * 3;
	return this->unBasicDef;
}

unsigned long Player::GetExpNeed(void)
{
	//到下一等级所需经验值计算公式 16x^2 + 128
	unsigned int x = this->unLevel - 1;
	return (x * x * 256 + 128);
}

unsigned long Player::GetExpOwn(void)
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

unsigned int Monster::UpdateBasicAtk(void)
{
	this->unBasicAtk =
		5 + this->unLevel * 4;
	return this->unBasicAtk;
}

unsigned int Monster::UpdateBasicDef(void)
{
	this->unBasicDef =
		6 + this->unLevel * 4;
	return this->unBasicDef;
}

Monster::Monster()
{
	this->SetMaxHealth(64);
	this->ResetCurrentHealth();
	this->UpdateBasicAtk();
	this->UpdateBasicDef();
	this->SetExpDrop(1024);
}

Monster::Monster(Monster & right)
{
	this->SetLevel(right.GetLevel());
	this->UpdateBasicAtk();
	this->UpdateBasicDef();
	this->SetAtkBonus(1.0);
	this->SetDefBonus(1.0);
	this->SetMaxHealth(64);
	this->ResetCurrentHealth();
	this->SetExpDrop(right.GetExpDrop());
	this->SetName(right.GetName().c_str());
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