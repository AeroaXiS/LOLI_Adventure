#include "pch.h"
#include "Body.h"


Body::Body()
{
}


Body::~Body()
{
}

unsigned int Body::BattleCommonHit(Body * enemy)
{
	//默认防御力2
	return enemy->BattleSuffer(RangeUniformRandom(this->GetAtk(1), 0.2));
}

unsigned int Body::BattleSuffer(unsigned int damege)
{
	if (damege >= this->unCurrentHealth)
	{
		this->unCurrentHealth = 0;
	}
	else
	{
		this->unCurrentHealth -= damege;
	}
	return damege;
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

std::string & Body::WhoAmI(void)
{
	return this->strName;
}

void Body::WhoAmI(const char * name)
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
	this->SetLevel(1);
	this->ulExp = 0;
}

void Player::SetMaxHealth(void)
{
	//生命值 = k * level + 128
	const double k = 1.0;
	this->unMaxHealth = static_cast<unsigned int>(k * this->unLevel + 128);
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

unsigned int Player::LevelUp(void)
{
	this->unLevel++;
	return this->unLevel;
}

bool Player::IsAbleToLevelUp(void)
{
	if (ulExp >= this->ExpNeed())
	{
		return true;
	}
	return false;
}

unsigned long Player::ExpNeed(void)
{
	//到下一等级所需经验值计算公式 16x^2 + 128
	unsigned int x = this->unLevel - 1;
	return (x * x * 256 + 128);
}

unsigned long Player::ExpHave(void)
{
	return this->ulExp;
}

unsigned long Player::AwardExp(unsigned long quantity)
{
	this->ulExp += quantity;
	return this->ulExp;
}


unsigned int Monster::GetAtk(double k)
{
	//默认4
	return 4;
}

void Monster::SetMaxHealth(void)
{
	//生命值 = k * level + 128
	const double k = 1.0;
	this->unMaxHealth = static_cast<unsigned int>(k * this->unLevel + 128);
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
