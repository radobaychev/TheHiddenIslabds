#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <string>

class Game
{
private:
	const static int DELAY = 5;
	bool liftedCurse;
	bool killedDragon;
	bool acceptedHelp;
	bool choseForest;
	bool tookShield;
	bool beenToVillage;

	void ArrivalToTheIsles();
	void TheGoldenForest();
	void TheCursedVillage();
	void BattleWithTheDragon();
	void TheTower();
	void Epilogue();

	void WaitEnter();
public:
	Game();
	void StartGame();
};


#endif
