#include "PlayerStrategy.h"


int HumanPlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "HumanPlayerStrategy: Please choose a strategy from the following \n"
		"1 for issueOrder(), 2 for toAttack(), 3 for toDefend(). " << endl;
	int input;
	cin >> input;
	if (input == 1) {
		issueOrder(order);
		return armies - 1;
	}
	else if (input == 2) {
		toAttack();
		return armies - 2;
	}
	else if (input == 3) {
		toDenfend();
		return armies;
	}
	else {
		cout << "Please input an correct integer from 1 to 3...\n" << endl;
	}
}

void HumanPlayerStrategy::issueOrder(string order)
{
	cout << "HumanPlayerStrategy: issueOrder() -> " << order << endl;
}

void HumanPlayerStrategy::toAttack()
{
	cout << "HumanPlayerStrategy: toAttack() " << endl;
}

void HumanPlayerStrategy::toDenfend()
{
	cout << "HumanPlayerStrategy: toAttack() " << endl;
}



int AggressivePlayerStrategy::changeStrategy(string order, int armies)
{
	cout << "AggressivePlayerStrategy: makeDecision() " << endl;
	
	issueOrder(order);
	
	toAttack();

	toDenfend();
	return armies - 5;
}

void AggressivePlayerStrategy::issueOrder(string order)
{
	cout << "AggressivePlayerStrategy: issueOrder() -> " << order << " -> reinforces its strongest country. " << endl;
}

void AggressivePlayerStrategy::toAttack()
{
	cout << "AggressivePlayerStrategy: toAttack() " << endl;
}

void AggressivePlayerStrategy::toDenfend()
{
	cout << "AggressivePlayerStrategy: toDenfend() -> maximize aggregation of forces in the country" << endl;
}

int BenevolentPlayerStrategy::changeStrategy(string order, int numArmy)
{
	cout << "BenevolentPlayerStrategy: makeDecision() " << endl;
	//focus on protecting its weak country
	issueOrder(order);
	//never attacks, toDefend
	toDenfend();
	return numArmy - 1;
}

void BenevolentPlayerStrategy::issueOrder(string order)
{
	cout << "BenevolentPlayerStrategy: issueOrder() -> " << order << " -> reinforces its weakest country. " << endl;
}

void BenevolentPlayerStrategy::toAttack()
{
	cout << "BenevolentPlayerStrategy : never attacks" << endl;
}

void BenevolentPlayerStrategy::toDenfend()
{
	cout << "BenevolentPlayerStrategy: toDenfend() -> move armies to weaker countries. " << endl;
}


#pragma region Neutral Player Strategy


int NeutralPlayerStrategey::changeStrategy(string, int)
{
	return 0;
}

void NeutralPlayerStrategey::issueOrder(string)
{
}

void NeutralPlayerStrategey::toAttack()
{
}

void NeutralPlayerStrategey::toDenfend()
{
}

#pragma endregion

#pragma region Cheater Player Strategy

int CheaterPlayerStrategey::changeStrategy(string, int)
{
	return 0;
}

void CheaterPlayerStrategey::issueOrder(string)
{
}

void CheaterPlayerStrategey::toAttack()
{
}

void CheaterPlayerStrategey::toDenfend()
{
}

#pragma endregion
