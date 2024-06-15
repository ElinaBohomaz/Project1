#include "bot.h"

Bot::Bot()
{
	
}

Bot::Bot(int trump)
{
	this->trump = trump;
}

int Bot::getMinCardIndex(const std::vector<Card>& cards, int trump, bool onlyTrump) {
    int minIndex = -1;

    for (int i = 0; i < cards.size(); i++)
    {
        if (onlyTrump && cards[i].suit != trump) 
        {
            continue;
        }

        if (minIndex == -1 || cards[i].rank < cards[minIndex].rank)
        {
            minIndex = i;
        }
    }
    return minIndex;
}


bool Bot::action(std::vector<Card>* card_stack, int permissions)
{
    bool can_attack = permissions & Permissions::attack;
    bool can_defence = permissions & Permissions::defence;
    bool can_toss = permissions & Permissions::toss;
    bool can_take = permissions & Permissions::take;
    bool can_discard = permissions & Permissions::discard;

    if (can_defence && !card_stack->empty())
    {
        for (int i = 0; i < cards.size(); i++)
        {
            if (canBeat(&card_stack->back(), &cards[i]))
            {
                attack(card_stack, i);
                return false;
            }
        }

        takeCards(card_stack);
        return false;
    }

    if (can_attack)
    {
        int minCardIndex = getMinCardIndex(cards, trump, false);

        if (minCardIndex != -1)
        {
            attack(card_stack, minCardIndex);
            return false;
        }
    }

    if (can_toss && !card_stack->empty())
    {
        for (int i = 0; i < cards.size(); i++)
        {
            if (canToss(*card_stack, &cards[i]))
            {
                attack(card_stack, i);
                return false;
            }
        }
    }

    if (can_discard)
    {
        discard(card_stack);
        return true;
    }

    if (can_take)
    {
        takeCards(card_stack);
        return false;
    }

    return false;
}
