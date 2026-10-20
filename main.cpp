#include <iostream>
#include <array>
#include <ctime> // для time()
#include <cstdlib> // для rand() и srand()

enum CardSuit
{
    SUIT_TREFY,
    SUIT_BUBNY,
    SUIT_CHERVY,
    SUIT_PIKI,
    MAX_SUITS,
};

enum CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_VALET,
    RANK_DAMA,
    RANK_KOROL,
    RANK_TUZ,
    MAX_RANKS,
};

struct Card
{
    CardSuit suit;
    CardRank rank;
};

void printCard(const Card &card)
{
    switch(card.rank)
    {

    case RANK_2: std::cout << "2"; break;
    case RANK_3: std::cout << "3"; break;
    case RANK_4: std::cout << "4"; break;
    case RANK_5: std::cout << "5"; break;
    case RANK_6: std::cout << "6"; break;
    case RANK_7: std::cout << "7"; break;
    case RANK_8: std::cout << "8"; break;
    case RANK_9: std::cout << "9"; break;
    case RANK_10: std::cout << "10"; break;
    case RANK_VALET: std::cout << "V"; break;
    case RANK_DAMA: std::cout << "D"; break;
    case RANK_KOROL: std::cout << "K"; break;
    case RANK_TUZ: std::cout << "T"; break;
        break;
    }

    switch(card.suit)
    {

    case SUIT_TREFY: std::cout << "TR"; break;
    case SUIT_BUBNY: std::cout << "B"; break;
    case SUIT_CHERVY: std::cout << "CH"; break;
    case SUIT_PIKI: std::cout << "P"; break;
        break;
    }
}

void printDeck(const std::array<Card, 52> &deck)
{
    for (const auto &card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }

    std::cout << "\n";
}

void swapCard(Card &a, Card &b)
{
    // временная переменная для значения a
    Card temp = a;

    // меняем a и b местами
    a = b;

    b = temp;
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52> &deck)
{
    for (int i = 0; i < 52; ++i)
    {
        int swapIndex = getRandomNumber(1, 51);
        swapCard(deck[i], deck[swapIndex]);
    }
}

int getCardValue(Card card)
{
    switch(card.rank)
    {

    case RANK_2: return 2;
    case RANK_3: return 3;
    case RANK_4: return 4;
    case RANK_5: return 5;
    case RANK_6: return 6;
    case RANK_7: return 7;
    case RANK_8: return 8;
    case RANK_9: return 9;
    case RANK_10: return 10;
    case RANK_VALET: return 10;
    case RANK_DAMA: return 10;
    case RANK_KOROL: return 10;
    case RANK_TUZ: return 11;
        break;
    }
}

char getPlayerChoice()
{
    std::cout << "(h) to hit, or (s) to stand: ";
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'h' && choice != 's');

    return choice;
}

bool playBlackjack(std::array<Card, 52> &deck)
{
    // Настраиваем стартовый режим игры
    const Card *cardPtr = &deck[0];

    int dealerScore = 0;
    int playerScore = 0;

    dealerScore = getCardValue(*cardPtr++);
    std::cout << "The dealer is showing: " << dealerScore << std::endl;

    playerScore = getCardValue(*cardPtr++);
    playerScore = getCardValue(*cardPtr++);

    while(1)
    {
        std::cout << "Your score: " << playerScore << std::endl;

        if (playerScore > 21)
            return false;

        char choice = getPlayerChoice();
        if (choice == 's')
            break;
        playerScore += getCardValue(*cardPtr++);
    }

    while(dealerScore < 17)
    {
        dealerScore +=getCardValue(*cardPtr++);
        std::cout << "The dealer now has: " << dealerScore << '\n';
    }

    if (dealerScore > 21)
        return true;

    return (playerScore > dealerScore);

}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::array<Card, 52> deck;

    int card = 0;
    for (int suit = 0; suit < MAX_SUITS; ++suit)
        for (int rank = 0; rank < MAX_RANKS; ++rank)
        {
            deck[card].suit = static_cast<CardSuit>(suit);
            deck[card].rank = static_cast<CardRank>(rank);
            ++card;
        }

    printDeck(deck);

    shuffleDeck(deck);

    printDeck(deck);

    if (playBlackjack(deck))
        std::cout << "You win!\n";
    else
        std::cout << "You lose!\n";

    return 0;
}