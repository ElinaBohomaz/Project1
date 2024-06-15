#include <iostream>
#include <string>
#include <stack>

#include "io.h"
#include "fcntl.h"

#include "card.h"
#include "cards.h"
#include "card_deck.h"
#include "player.h"
#include "permissions.h"
#include "bot.h"
#include "utilities.h"

class Game
{
private:
	CardDeck* card_deck = new CardDeck();
	std::vector<Card> card_stack;
	Player* players[2];

	int player_turn = 0;
	int attacker = 0;

	bool running = true;

	void start()
	{
		card_deck->clear();

		card_deck->init();
		card_deck->shuffle();

		players[0] = new Bot(card_deck->getTrump().suit);
		players[1] = new Player(card_deck->getTrump().suit);

		int lowest_rank = Ranks::ace;

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Card card = card_deck->pop();

				if (card.rank < lowest_rank && card_deck->isTrump(card))
				{
					lowest_rank = card.rank;
					player_turn = j;
					attacker = j;
				}

				if (card.suit != -1)
				{
					players[j]->add(card);
				}
			}
		}
	}

	void show()
	{
		std::wcout << L"Карти бота: " << players[0]->toString() << std::endl << std::endl << std::endl;

		std::wcout << L"Козир: " << card_deck->getTrump().toString() << L"\t";
		std::wcout << L"Карт в колоді: " << card_deck->getCount() << std::endl << std::endl;

		std::wcout << L"Бій:" << std::endl;

		for (int i = 0; i < card_stack.size(); i++)
		{
			std::wcout << "  " << card_stack[i].toString() << " -> ";

			if (card_stack.size() <= ++i)
			{
				std::wcout << L"?";
			}
			else
			{
				std::wcout << card_stack[i].toString();
			}

			std::wcout << std::endl;
		}

		std::wcout << std::endl << std::endl << std::endl;

		std::wcout << L"Хід: " << (player_turn ? L"Ваш" : L"бота") << std::endl;

		std::wcout << L"Ваші карти: " << players[1]->toString() << std::endl << std::endl << std::endl;
	}

	void game()
	{
		while (true)
		{
			clear();
			show();

			int permissions = 0;

			if (card_stack.empty())
			{
				permissions |= Permissions::attack;
			}

			if (card_stack.size() % 2 != 0)
			{
				if (players[player_turn]->canBeat(&card_stack.back()))
				{
					permissions |= Permissions::defence;
				}

				permissions |= Permissions::take;
			}

			if (players[player_turn]->canToss(card_stack) && player_turn == attacker)
			{
				permissions |= Permissions::toss;
			}

			if (card_stack.size() != 0 && card_stack.size() %2 == 0 || card_stack.size() == 12)
			{
				permissions |= Permissions::discard;
			}

			bool swap_players = players[player_turn]->action(&card_stack, permissions);

			player_turn = (int)!player_turn;

			if (swap_players)
			{
				attacker = (int)!attacker;
			}

			if (card_stack.empty())
			{
				players[player_turn]->takeCards(card_deck);
				players[!player_turn]->takeCards(card_deck);
			}

			if (players[0]->getCount() == 0 && players[1]->getCount() == 0 && card_stack.empty())
			{
				std::wcout << std::endl << textColor(L"Нічия!", Colors::yellow) << std::endl << std::endl;
				pause();
				break;
			}

			if (players[0]->getCount() == 0 && card_stack.empty())
			{
				std::wcout << std::endl << textColor(L"Ви програли!", Colors::red) << std::endl << std::endl;
				pause();
				break;				
			}

			if (players[1]->getCount() == 0 && card_stack.empty())
			{
				std::wcout << std::endl << textColor(L"Ви перемогли!", Colors::green) << std::endl << std::endl;
				pause();
				break;
			}
		}
	}

public:
	void run()
	{
		while (running)
		{
			start();
			game();
		}
	}
};

int main() {
	// Для коректного відображення символів UTF-8
	if (_setmode(_fileno(stdout), _O_U16TEXT) == -1 ||
		_setmode(_fileno(stdin), _O_U16TEXT) == -1)
	{
		std::cout << "Unable to set unicode input/output" << std::endl;
		return -1;
	}

	Game* game = new Game();
	game->run();
}

/*
* 
* Player* player = new Player(Suits::spades);

	player->add(std::vector<Card> {
		// Card{ Ranks::seven, Suits::spades },
		Card{ Ranks::seven, Suits::clubs },
		Card{ Ranks::ten, Suits::clubs }
	});

	std::wcout << player->canBeat(new Card{ Ranks::ace, Suits::spades }) << std::endl;
	std::wcout << player->canBeat(new Card{ Ranks::eight, Suits::spades }) << std::endl;
	std::wcout << player->canBeat(new Card{ Ranks::eight, Suits::clubs }) << std::endl;\

	int flags = Yep::defence | Yep::take | Yep::toss;

	if (flags & Yep::none)
	{
		std::wcout << L"None! " << flags << std::endl;
	}
	if (flags & Yep::attack)
	{
		std::wcout << L"Attack! " << flags << std::endl;
	}
	if (flags & Yep::defence)
	{
		std::wcout << L"Defence! " << flags << std::endl;
	}
	if (flags & Yep::take)
	{
		std::wcout << L"Take! " << flags << std::endl;
	}
	if (flags & Yep::toss)
	{
		std::wcout << L"Toss! " << flags << std::endl;
	}
	*/
