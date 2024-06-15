#include "player.h"

Player::Player() {
	this->trump = -1;
}

Player::Player(int trump)
{
	this->trump = trump;
}

bool Player::canBeat(Card* attacker, Card* defender)
{
	if (attacker->suit == defender->suit)
	{
		if (defender->rank > attacker->rank)
		{
			return true;
		}
	}
	else if (defender->isTrump(trump))
	{
		return true;
	}

	return false;
}

bool Player::canBeat(Card* card)
{
	for (Card player_card : cards)
	{
		if (canBeat(card, &player_card))
		{
			return true;
		}
	}

	return false;
}

bool Player::canToss(std::vector<Card> card_stack)
{
	for (Card card : card_stack)
	{
		for (Card player_card : cards)
		{
			if (card.rank == player_card.rank)
			{
				return true;
			}
		}
	}

	return false;
}

bool Player::canToss(std::vector<Card> card_stack, Card* card)
{
	for (Card stack_card : card_stack)
	{
		if (stack_card.rank == card->rank)
		{
			return true;
		}
	}

	return false;
}

bool Player::action(std::vector<Card>* card_stack, int permissions)
{
	bool can_attack = permissions & Permissions::attack;
	bool can_defence = permissions & Permissions::defence;
	bool can_toss = permissions & Permissions::toss;
	bool can_take = permissions & Permissions::take;
	bool can_discard = permissions & Permissions::discard;


	while (true)
	{
		if (can_attack)
		{
			std::wcout << L"Введіть номер карти, щоб атакувати\t";
		}
		if (can_defence)
		{
			std::wcout << L"Введіть номер карти, щоб відбитися\t";
		}
		if (can_toss)
		{
			std::wcout << L"Введіть номер карти, щоб підкинути\t";
		}
		if (can_take)
		{
			std::wcout << L"[в] - взяти карти";
		}
		if (can_discard)
		{
			std::wcout << L"[д] - відбій";
		}

		std::wcout << std::endl;

		std::wstring input = getValue(L"  Виберіть дію");
		int card_index = -1;

		if (!wstringToInt(input, card_index))
		{
			switch (input.c_str()[0])
			{
			case L'в':
			case L'В':
			case L'd':
			case L'D':
				if (!can_take)
				{
					std::wcout << textColor(L"Ви не можете виконати зараз цю дію", Colors::bright_magenta) << std::endl;
					continue;
				}

				takeCards(card_stack);
				return false;
			case L'д':
			case L'Д':
			case L'l':
			case L'L':
				if (!can_discard)
				{
					std::wcout << textColor(L"Ви не можете виконати зараз цю дію", Colors::bright_magenta) << std::endl;
					continue;
				}

				discard(card_stack);
				return true;
			default:
				std::wcout << textColor(L"Не вірна команда", Colors::bright_magenta) << std::endl;
				continue;
			}

			std::wcout << std::endl;
		}

		card_index--;

		if (cards.size() <= card_index || card_index < 0)
		{
			std::wcout << textColor(L"Не вірний номер карти", Colors::bright_magenta) << std::endl;
			continue;
		}

		if (!can_attack && !can_defence && !can_toss && card_index != -1)
		{
			std::wcout << textColor(L"Ви не можете виконати зараз цю дію", Colors::bright_magenta) << std::endl;
			continue;
		}

		if (!card_stack->empty() && !canBeat(&card_stack->back(), &cards[card_index]) && can_defence)
		{
			std::wcout << textColor(L"Ви не можете відбитися цією картою", Colors::bright_magenta) << std::endl;
			continue;
		}

		if (!card_stack->empty() && !canToss(*card_stack, &cards[card_index]) && can_toss)
		{
			std::wcout << textColor(L"Ви не можете підкинути цю карту", Colors::bright_magenta) << std::endl;
			continue;
		}

		attack(card_stack, card_index);

		break;
	}

	return false;
}

void Player::takeCards(std::vector<Card>* cards_stack)
{
	cards.insert(cards.end(), cards_stack->begin(), cards_stack->end());
	cards_stack->erase(cards_stack->begin(), cards_stack->end());
}

void Player::takeCards(CardDeck* card_deck)
{
	int deficit = 6 - cards.size();

	if (deficit <= 0)
	{
		return;
	}

	for (int i = 0; i < deficit; i++)
	{
		Card card = card_deck->pop();

		if (card.suit == -1)
		{
			return;
		}

		cards.push_back(card);
	}
}

void Player::attack(std::vector<Card>* card_stack, int card_index)
{
	card_stack->push_back(cards[card_index]);
	cards.erase(cards.begin() + card_index);
	std::wcout << cards.size();
}

void Player::discard(std::vector<Card>* card_stack)
{
	card_stack->erase(card_stack->begin(), card_stack->end());
}

bool Player::hasCards()
{
	return cards.size() != 0;
}

