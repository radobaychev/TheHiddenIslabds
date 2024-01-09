#include "Game.h"
#include <chrono>
#include <thread>

struct s_cout {
	std::string data;
	long int delay = 10;
};

std::ostream& operator<<(std::ostream& out, const s_cout& s) {
	for (const auto& c : s.data) {
		out << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(s.delay));
	}
	return out;
}

Game::Game() {
	liftedCurse = false;
	killedDragon = false;
	acceptedHelp = false;
	choseForest = false;
	tookShield = false;
	beenToVillage = false;
}

void Game::WaitEnter() {
	std::cout << s_cout{ "Press ENTER to begin...\n" };
	while (std::cin.get() != '\n');
}

void Game::StartGame() {
	std::cout << s_cout{ "Welcome to The Hidden Isles!\n"}
	<< s_cout{ "You are an ordinary merchant whose ship is lost in a storm. After some time you wash up on the shores of the Hidden Isles, a mysterious set of islands filled with magic, adventures and dangers.\n" };

	WaitEnter();

	ArrivalToTheIsles();
}

void Game::ArrivalToTheIsles() {
	std::cout << s_cout{ "ARRIVAL TO THE HIDDEN ISLES" } << std::endl
		<< s_cout{ "Upon waking up on the beach you see that there are no other survivors around you.\n" }
		<< s_cout{ "There is a nearby FOREST. There is also what appears to be a VILLAGE nearby.\n" }
		<< s_cout{ "Where do you want to go?\n" };

	std::string choice;

	bool validChoice = false;

	while (!validChoice) {
		std::getline(std::cin, choice);

		if (choice == "FOREST" || choice == "forest" || choice == "Forest") {
			validChoice = true;
			choseForest = true;
		}
		else if (choice == "VILLAGE" || choice == "village" || choice == "Village") {
			validChoice = true;
			choseForest = false;
		}
		else {
			std::cout << "Invalid choice.\n";
		}
	}

	if (choseForest) {
		std::cout << s_cout{ "You decide to explore the FOREST.\n\n",  };
		TheGoldenForest();
	}
	else {
		std::cout << s_cout{ "You decide to explore the VILLAGE.\n\n",  };
		beenToVillage = true;
		TheCursedVillage();
	}
}

void Game::TheGoldenForest() {
	std::cout << s_cout{ "THE GOLDEN FOREST",  } << std::endl
		<< s_cout{ "While walking through the forest you encounter a group of elves.\n",  }
		<< s_cout{ "They offer to help you escape the isles but only after they deal with the evil dragon hiding in their forest.\n",  }
		<< s_cout{ "Do you ACCEPT or REFUSE their offer?\n",  };

	std::string choice;

	bool validChoice = false;

	while (!validChoice) {
		std::getline(std::cin, choice);

		if (choice == "ACCEPT" || choice == "accept" || choice == "Accept") {
			validChoice = true;
			acceptedHelp = true;
		}
		else if (choice == "REFUSE" || choice == "refuse" || choice == "Refuse") {
			validChoice = true;
			acceptedHelp = false;
		}
		else {
			std::cout << "Invalid choice.\n";
		}
	}

	if (acceptedHelp) {
		std::cout << s_cout{ "You accepted the elves' help.\n",  }
			<< s_cout{ "They will wait for you in the forest until you are prepared to fight the dragon.\n",  };
	}
	else {
		std::cout << s_cout{ "You refused the elves' help\n",  }
		<< s_cout{ "The elves go to fight the dragon alone.\n",  };
	}

	std::cout << s_cout{ "You can tell the only way you will be able to leave the island is if you fight the dragon.\n", };

	if (beenToVillage) {
		std::cout << s_cout{ "You decide to go fight the dragon.\n\n",  };
		BattleWithTheDragon();
	}
	else {
		std::cout << s_cout{ "You can go FIGHT the dragon now or go back and explore the VILLAGE.\n",  }
		<< s_cout{ "What do you want to do?\n",  };
		validChoice = false;
		bool fightDragon = false;

		while (!validChoice) {
			std::getline(std::cin, choice);

			if (choice == "FIGHT" || choice == "Fight" || choice == "fight") {
				validChoice = true;
				fightDragon = true;
			}
			else if (choice == "VILLAGE" || choice == "Village" || choice == "village") {
				validChoice = true;
			}
			else {
				std::cout << "Invalid choice\n";
			}
		}

		if (fightDragon) {
			std::cout << s_cout{ "You have decided to FIGHT the dragon.\n\n",  };
			BattleWithTheDragon();
		}
		else {
			std::cout << s_cout{ "You have decided to go back to explore the VILLAGE.\n\n",  };
			TheCursedVillage();
		}
	}
}

void Game::TheCursedVillage() {

	std::cout << s_cout{ "THE CURSED VILLAGE",  } << std::endl;

	std::cout << s_cout{ "The village appears empty as you arrive, but upon further inspection you see a lone villager sitting in front of a house.\n",  }
		<< s_cout{ "He tells you that all the other villagers have barricaded themselves in their homes so as to protect themselves from the curse that is afflicting the village.\n",  }
	<< s_cout{ "He also tells you that according to an old legend the source of the curse is in the tower next to the village.\n",  };

	std::cout << s_cout{ "You can go try to LIFT the curse",  };
	if (choseForest) {
		std::cout << s_cout{ " or go FIGHT the dragon.\n",  };
	}
	else {
		std::cout << s_cout{ " or go explore the FOREST.\n",  };
	}
	std::cout << s_cout{ "What do you want to do?\n",  };

	bool validChoice = false;
	bool liftCurse = false;

	std::string choice;

	while (!validChoice) {
		std::getline(std::cin, choice);

		if ((choice == "FOREST" || choice == "forest" || choice == "Forest") && !choseForest) {
			validChoice = true;
		}
		else if ((choice == "FIGHT" || choice == "Fight" || choice == "fight") && choseForest) {
			validChoice = true;
		}
		else if (choice == "LIFT" || choice == "Lift" || choice == "lift") {
			validChoice = true;
			liftCurse = true;
		}
		else {
			std::cout << "Invalid choice.\n";
		}
	}

	if (liftCurse) {
		std::cout << s_cout{ "You have chosen to try to LIFT the curse.\n\n",  };
		TheTower();
	}
	else {
		if (choseForest) {
			std::cout << s_cout{ "You have chosen to FIGHT the dragon.\n\n",  };
			BattleWithTheDragon();
		}
		else {
			std::cout << s_cout{ "You have chosen to go to the FOREST.\n\n",  };
			TheGoldenForest();
		}
	}
}

void Game::TheTower() {
	std::cout << s_cout{ "THE TOWER\n",  };

	std::cout << s_cout{ "You enter the tower. Suprisingly it is empty. You easily reach the top of the tower.\n",  }
		<< s_cout{ "There there is only a round table with a dark shield on top of it.\n",  }
		<< s_cout{ "You can tell that the shield is the source of the curse.",  }
	<< s_cout{ "You can DESTROY the shield, you can TAKE it with you or you can just LEAVE the tower and go ",  };

	if (choseForest) {
		std::cout << s_cout{ "fight the dragon.\n",  };
	}
	else {
		std::cout << s_cout{ "explore the forest.\n",  };
	}

	std::string choice;
	bool validChoice = false;


	while (!validChoice) {
		std::getline(std::cin, choice);
		
		if ((choice == "LEAVE" || choice == "leave" || choice == "Leave")) {
			validChoice = true;
		}
		else if ((choice == "DESTROY" || choice == "Destroy" || choice == "destroy")) {
			validChoice = true;
			liftedCurse = true;
		}
		else if (choice == "TAKE" || choice == "Take" || choice == "take") {
			validChoice = true;
			tookShield = true;
		}
		else {
			std::cout << "Invalid choice.\n";
		}
	}

	if (tookShield) {
		std::cout << s_cout{ "You decided to take the shield. It might come in handy.\n" };
	}
	else if (liftedCurse) {
		std::cout << s_cout{ "You decided to destroy the shield. The curse has been lifted. The villagers will be thankful.\n"};
	}
	else {
		std::cout << s_cout{ "You decided to leave the tower.\n" };
	}

	if (choseForest) {
		std::cout << s_cout{ "It is time to fight the dragon.\n\n" };
		BattleWithTheDragon();
	}
	else {
		std::cout << s_cout{ "The only place left to explore is the forest.\n\n" };
		TheGoldenForest();
	}
}

void Game::BattleWithTheDragon() {
	std::cout << s_cout{ "BATTLE WITH THE DRAGON\n" };

	std::cout << s_cout{"The dragon is ready for battle.\n"};

	if (!acceptedHelp) {
		std::cout << s_cout{ "The elves are nowhere to be seen.\n" };
	}

	std::cout << s_cout{ "The dragon becomes enraged at the sight of you and prepares to breathe fire.\n" };

	if (acceptedHelp) {
		killedDragon = true;
		std::cout << s_cout{ "All of the elves cast a shielding spell on you. \nThe flames are reflected back to the dragon.\n" };
	}
	else if (tookShield) {
		killedDragon = true;
		liftedCurse = true;
		std::cout << s_cout{ "You lift up the cursed shield to protect yourself from the flames. The shield is destroyed but the flames are reflected back to the dragon\n" };
	}
	else {
		std::cout << s_cout{ "The dragon's fire incenerates you.\n" };
	}

	if (killedDragon) {
		std::cout << s_cout{ "The dragon is dead!\n\n" };

		Epilogue();
	}
	else {
		std::cout << s_cout{ "You were defeated by the dragon. The hidden isles will surely be destroyed by him.\n" };
		std::cout << s_cout{ "GAME OVER\n\n" };
	}
}

void Game::Epilogue() {
	std::cout << s_cout{ "EPILOGUE\n" };

	if (acceptedHelp) {
		std::cout << s_cout{ "After killing the dragon you easily returned home with the help of the elves.\n" };

		if (tookShield && !liftedCurse) {
			std::cout << s_cout{ "You thought that after coming home you would be able to live a peaceful life, however the curse from the village transfered to your home because you took the shield.\n" }
			<< s_cout{ "GAME OVER!\n" };
			return;
		}
		else if (!liftedCurse && beenToVillage) {
			std::cout << s_cout{ "No word has come from the village, the curse has probably destroyed it.\n" };
		}
		else if (liftedCurse){
			std::cout << s_cout{ "Shortly after returning home you recieved a letter from the villager you met. The villagers have been living peacefully since the lifting of the curse.\n" };
		}

		std::cout << s_cout{ "Thank you for playing The Hidden Isles!\n" };
		return;
	}
	else {
		if (tookShield && !liftedCurse) {
			std::cout << s_cout{ "After killing the dragon you tried to make your way home, however you fell victim to the curse.\n" }
				<< s_cout{"GAME OVER\n" };
		}
		else {
			std::cout << s_cout{ "After a long journey you managed to make you way home only to find it destroyed.\n" }
			<< s_cout{ "You moved to the neighbouring town where you lived peacefully.\n" };

			std::cout << s_cout{ "Thank you for playing The Hidden Isles.\n" };
			
			return;
		}
	}
}