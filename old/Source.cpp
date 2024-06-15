#include"cards.h"
#include"cards2.h"
#include"cards3.h"
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>

#include <Windows.h>

int f0(const std::string s);
int f1(const std::vector<std::string>& vec);
bool f2();
void f3();

template<class T> class cards
{
protected:
    int pMin;
    int bMin;
    std::string cos;
    std::vector<std::string>::iterator iter1;
    std::vector<std::string>::iterator iter2;
    std::vector<T> colod;
    std::vector<T> player;
    std::vector<T> bot;
    std::vector<T> cos_player;
    std::vector<T> cos_bot;
public:
    cards();
    void cards_of_player();
    void cards_of_bot();
    void get_cos();
    friend void func(cards<std::string>& object);
    bool min();
    bool Str(std::string& str, std::string& str1);
    void remove_cards(std::vector<std::string> vec, std::vector<std::string>& vec1); //видаляє карту
    void remove_elem(std::vector<std::string>& vec, std::string x);                  //видаляє карту
    friend int f0(const std::string s);
};
template<class T>cards<T>::cards()
{
    for (int i = 0; i < (sizeof(ns) / sizeof(std::string)); i++)
    {
        for (int j = 0; j < (sizeof(ns2) / sizeof(std::string)); j++)
        {
            colod.push_back(ns[i].name + ns2[j].suit);
        }
    }
    srand(unsigned(time(NULL)));
    std::random_shuffle(colod.begin(), colod.end());
}

template<class T>void cards<T>::cards_of_player()
{
    std::cout << "ваші карти:" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        player.push_back(colod[i]);
        std::string str = colod[i];
        std::cout << player[i] << std::endl;
    }
    std::cout << std::endl;
    remove_cards(player, colod);
}
template<class T>void cards<T>::cards_of_bot()
{
    std::cout << std::endl << "бот отримав карти" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        bot.push_back(colod[i]);
        std::string str = colod[i];
        std::cout << bot[i] << std::endl;
    }
    std::cout << std::endl;
    remove_cards(bot, colod);
}
template<class T>void cards<T>::get_cos()
{
    cos = colod[0];
    remove_elem(colod, cos);
    std::cout << "козир - " << cos << std::endl;
    colod.push_back(cos);
}
template<class T>void cards<T>::remove_cards(std::vector<std::string> vec, std::vector<std::string>& vec1)
    {
           for (int i = 0; i < vec1.size(); i++)
           {
               for (int j = 0; j < vec.size(); j++)
                {
                    if (vec1[i] == vec[j])
                    {
                        remove_elem(vec1,vec[j]);
                    }
                }
           }
    }
    template<class T>void cards<T>::remove_elem(std::vector<std::string>& vec, std::string x)
    {
        if (vec.size() != 0)
        {
            iter2 = std::remove(vec.begin(), vec.end(), x);
            vec.erase(iter2, vec.end());
        }
    }
    template<class T>bool cards<T>::min()
    {
        int pMin = f1(cos_player);
        int bMin = f1(cos_bot);
        if (pMin < bMin) return 1;
        else return 0;
    }
    template<class T>bool cards<T>::Str(std::string& str, std::string& str1)
    {
        if (str[2] == str1[2] || (str[3] == str1[3] && str[2] == ' ') || str[2] == str1[3] || str[3] == str1[2]) return 1;
        return 0;
    }
    void func(cards<std::string>& object)
    {
        std::string str, str1;
        if (object.cos[1] == ' ')
        {
            str1 = object.cos.substr(2, object.cos.end() - object.cos.begin());
        }
        else str1 = object.cos.substr(3, object.cos.end() - object.cos.begin());
        for (object.iter1 = object.player.begin(); object.iter1 < object.player.end(); object.iter1++)
        {
            str = *object.iter1;
            if (str[1] == ' ')
            {
                str = str.substr(2, str.end() - str.begin());
            }
            else str = str.substr(3, str.end() - str.begin());
            if (str == str1) object.cos_player.push_back(*object.iter1);
        }
        std::cout << std::endl;
        for (object.iter2 = object.bot.begin(); object.iter2 < object.bot.end(); object.iter2++)
        {
            str = *object.iter2;
            str = str.substr(2, str.end() - str.begin());
            if (str == str1) object.cos_bot.push_back(*object.iter2);
        }
        std::cout << std::endl;
    }
    template<class X> class game :public cards<std::string>
    {
    protected:
        std::vector<std::string> MinValue;
        std::string CDS;
        int CardOfBotMin;
        std::vector<std::string> LeftCards;
        int NumberOfCard;
        std::string CardOfBot;
        bool bl2;
        bool bl3;
    public:
        game() {};
        void SelectPlayerOrBot(int bl);
        void AddCards();
        void AI_NOOB();
        void AI_Normal();
        void AI_Hard();
        void game_bot(std::string CRD, int ValueCRD, bool b);
        void game_player(bool b);
        bool player_select(std::string CRD, int ValueCRD);
        void VecOfMinCards(std::string s, int v);
        std::string MinCard(int val, std::string str);
        void CardsPrint();
    };

    template<class X>void game<X>::SelectPlayerOrBot(int bl)
    {
        if (bl == 1)
        {
            game_player(1);
        }
        else if (bl == 0)
        {
            AI_NOOB();
        }
        if (player.size() == 0)
            std::cout << "Ви виграли!" << std::endl;
        if (bot.size() == 0)
            std::cout << "Бот виграв!" << std::endl;
        if (player.size() == 0 && bot.size() == 0)
            std::cout << "Нічия!" << std::endl;
        system("pause");
        f3();
    }
    template<class X>void game<X>::AddCards()
    {
        if (colod.size() != 0)
        {
            if (player.size() < 6)
            {
                while (player.size() != 6)
                {
                    player.push_back(colod[0]);
                    remove_elem(colod, colod[0]);
                }
            }
        }
        if (colod.size() != 0)
        {
            if (bot.size() < 6)
            {
                while (bot.size() != 6)
                {
                    bot.push_back(colod[0]);
                    remove_elem(colod, colod[0]);
                }
            }
        }
    }
    template<class X>void game<X>::AI_NOOB()
    {
        if (bot.size() == 0)
            SelectPlayerOrBot(3);
        while (LeftCards.size() != NULL)
        {
            LeftCards.pop_back();
        }
        for (int i = 0; i < (sizeof(ns2) / sizeof(std::string)); i++)
        {
            if (ns2[i].suit != cos.substr(1, cos.end() - cos.begin()) || ns2[i].suit != cos.substr(2, cos.end() - cos.begin()))
                VecOfMinCards(ns2[i].suit, 5);
        }
        CardOfBotMin = f1(MinValue);
        for (int i = 0; i < (sizeof(ns2) / sizeof(std::string)); i++)
        {
            for (int j = 0; j < MinValue.size(); j++)
                if (MinValue[j] == MinCard(CardOfBotMin, ' ' + ns2[i].suit))
                    CardOfBot = MinValue[j];
        }
        while (MinValue.size() != NULL)
        {
            MinValue.pop_back();
        }

        std::cout << "бот походив картою - " << CardOfBot << std::endl;
        std::cout << "****************************************************************************" << std::endl;
        std::cout << "****************************************************************************" << std::endl;
        bl3 = player_select(CardOfBot, CardOfBotMin);
        if (bl3 == 0)
            AI_NOOB();
        if (bl3 == 1)
            game_player(1);
    }
    template<class X>bool game<X>::player_select(std::string CRD, int ValueCRD)
    {
        std::cout << "є чим відбитись? Y/y - так ";
        if (f2() == 1)
        {
            std::cout << "Виберіть карту: ";
            std::cin >> NumberOfCard;
            if (f0(player[NumberOfCard - 1]) > ValueCRD && (Str(player[NumberOfCard - 1], CRD) == 1) || Str(player[NumberOfCard - 1], cos) == 1)
            {
                std::cout << std::endl << player[NumberOfCard - 1] << " може бити цю карту " << CRD << std::endl;
                remove_elem(bot, CRD);
                remove_elem(player, player[NumberOfCard - 1]);
                AddCards();

                CardsPrint();
                return 1;
            }
            else
            {
                std::cout << std::endl << player[NumberOfCard - 1] << " Не може бити цю карту " << CRD << std::endl;
                std::cout << "Вибрати іншу карту? Y/y - Так ";
                if (f2() == 1)
                    player_select(CRD, ValueCRD);
            }
        }
        else
        {
            player.push_back(CRD);
            remove_elem(bot, CRD);
            AddCards();
            while (LeftCards.size() != NULL)
                LeftCards.pop_back();
            CardsPrint();
            return 0;
        }

    }
    template<class X>void game<X>::game_player(bool b)
    {

        if (player.size() == 0)
            SelectPlayerOrBot(3);
        std::cout << "Виберіть карту: ";
        std::cin >> NumberOfCard;
        std::cout << "****************************************************************************" << std::endl;
        std::cout << "****************************************************************************" << std::endl;
        std::cout << "ви походили картою - " << player[NumberOfCard - 1] << std::endl;

        if (b == 1)
            game_bot(player[NumberOfCard - 1], f0(player[NumberOfCard - 1]), 1);
        else
        {
            bl2 = 0;
            for (int i = 0; i < LeftCards.size(); i++)
            {
                if (f0(player[NumberOfCard - 1]) == f0(LeftCards[i]))
                {
                    game_bot(player[NumberOfCard - 1], f0(player[NumberOfCard - 1]), 1);
                    bl2 = 1;
                }

            }
            if (bl2 == 0)
            {
                std::cout << std::endl << "цією картою неможна ходити оберіть іншу  " << std::endl;
                std::cout << "вибрати іншу карту y/n" << std::endl;
                if (f2() == 1)
                    game_player(0);
                else
                {
                    while (LeftCards.size() != NULL)
                        LeftCards.pop_back();
                    AddCards();
                    std::cout << "****************************************************************************" << std::endl;
                    std::cout << "****************************************************************************" << std::endl;
                    CardsPrint();
                    AI_NOOB();
                }
            }
        }
    }

    template<class X>void game<X>::game_bot(std::string CRD, int ValueCRD, bool b)
    {
        VecOfMinCards(CRD, ValueCRD);
        if (MinValue.size() == 0)
            CardOfBotMin = 15;
        else
            CardOfBotMin = f1(MinValue);
        if (b == 1)
        {
            CDS = CRD;
            LeftCards.push_back(CDS);
        }
        while (MinValue.size() != NULL)
        {
            MinValue.pop_back();
        }
        if ((CardOfBotMin == 15 || !CardOfBotMin))
        {

            if (Str(cos, CRD) == 1)
            {
                std::cout << "бот підняв" << std::endl;
                for (int i = 0; i < LeftCards.size(); i++)
                    bot.push_back(LeftCards[i]);
                while (LeftCards.size() != NULL)
                    LeftCards.pop_back();
                remove_elem(player, CDS);
                AddCards();
                CardsPrint();
                game_player(1);
            }
            else if (Str(cos, CRD) == 0) 
            {
                game_bot(cos, 5, 0);
            }

        }
        else
        {
            std::cout << "бот походив картою - " << MinCard(CardOfBotMin, CRD) << std::endl;
                LeftCards.push_back(MinCard(CardOfBotMin, CRD));
                remove_elem(bot, MinCard(CardOfBotMin, CRD));
                remove_elem(player, CDS);                                                //"спитати " в ігрока про вибері карти. в випадку співпадіння цієї карти  с LeftCards дозволити та продовжити.
                CardsPrint();
            std::cout << "****************************************************************************" << std::endl;
            std::cout << "****************************************************************************" << std::endl;
            if (player.size() == 0 || bot.size() == 0)
                SelectPlayerOrBot(3);
            std::cout << "Підкинути карту y/n?" << std::endl;
            if (f2() == 1)
                game_player(0);
            else
            {
                AddCards();
                while (LeftCards.size() != NULL)
                {
                    LeftCards.pop_back();
                }
                CardsPrint();
                AI_NOOB();
            }
        }
    }
    template<class X>std::string game<X>::MinCard(int val, std::string str)
    {
        if (str.substr(0, 2) == "10")
            str = str.substr(2, str.end() - str.begin());
        else
            str = str.substr(1, str.end() - str.begin());
        for (int i = 0; i < (sizeof(ns) / sizeof(std::string)); i++)
        {
            if (ns3[i].value == val)
            {
                str = ns[i].name + str;
                return str;
            }
        }
    }
    template<class X>void game<X>::VecOfMinCards(std::string s, int v)
    {
        std::string str;
        for (int i = 0; i < bot.size(); i++)
        {

            str = bot[i];
            if (Str(str, s) == 1)
            {
                if (f0(bot[i]) > v)
                {
                    MinValue.push_back(bot[i]);
                }
            }
        }
    }
    template<class X>void game<X>::CardsPrint()
    {
        std::cout << std::endl << "ваші карти:" << std::endl;
        for (int i = 0; i < player.size(); i++)
            std::cout << player[i] << ' ';
        std::cout << std::endl;
        std::cout << std::endl << "козирь - " << cos << std::endl;
        std::cout << std::endl << "Карти цього ходу:" << std::endl;
        for (int i = 0; i < LeftCards.size(); i++)
            std::cout << LeftCards[i] << ' ';
        std::cout << std::endl;
    }
    int f0(const std::string s)
    {
        for (int i = 0; i < sizeof(ns) / sizeof(std::string); i++)
        {
            if (s.substr(0, 1) == ns[i].name || s.substr(0, 2) == ns[i].name)
            {
                return ns3[i].value;
            }
        }
    }
    int f1(const std::vector<std::string>& vec)
    {
        int temp = 15;
        int p;
        for (int i = 0; i < vec.size(); i++)
        {
            p = f0(vec[i]);
            if (temp > p)
            {
                temp = p;
            }
        }
        return temp;
    }

    bool f2()
    {
        char ch;
        std::cin >> ch;
        if (ch == 'y' || ch == 'Y')
            return 1;
        else
            return 0;
    }
    bool start(char ch1);
    void f3()
    {
        char ch = 0;
        bool a;
        do
        {
            std::cout << "Почати нову гру? y/n" << std::endl;
            a = start(ch);
        } while (a == 1);
        exit(1);
    }

    int main()
    {
        setlocale(LC_ALL, "ukr");
        f3();
        return 0;
    }
    bool start(char ch1)
    {
        game<std::string> g;
        std::cin >> ch1;
        switch (ch1)
        {
        case 'Y': case 'y':
            g.cards_of_player();
            g.cards_of_bot();
            g.get_cos();
            func(g);
            g.SelectPlayerOrBot(g.min());
            return 1;
        case 'N': case 'n':
            return 0;
        default:
            std::cout << "Некоректна буква" << '\n';
            return 1;
        }
    }
