// libraries
#include <iostream>
#include <limits>
#include <cstdlib> 
#include <ctime> 

// constants
#define DECK_LENGTH 52
#define STARTING_DECK_SIZE 7
#define NUM_RANKS 13
#define NUM_SUITS 4
#define NO_RANK 0

// card class
class card
{
    public:
        bool compareSuitCard(card other);
        bool compareNumCard(card other);
        bool compareBoth(card other);
        void copyCard(card other);
        void printCard();
        int Suit;
        int Number;
        bool taken = false;
};

// check four of a kind
bool checkIfFour(card* deck, int cardNumber, int deckSize)
{
    int number = 0;

    for (int index = 0; index < deckSize; index++)
    {
        if (deck[index].Number == cardNumber
            && !deck[index].taken)
        {
            number++;
        }
    }

    return number == 4;
}

// mark all cards of a rank as taken
void removeAllOfType(card* deck, int numRemoval, int deckSize)
{
    for (int index = 0; index < deckSize; index++)
    {
        if (deck[index].Number == numRemoval
            && !deck[index].taken)
        {
            deck[index].taken = true;
        }
    }
}

// add card to deck
bool addCardToDeck(card* deck, card addedCard, int deckSize)
{
    bool foundCard = false;
    for (int index = 0; index < deckSize; index++)
    {
        if (deck[index].compareBoth(addedCard))
        {
            deck[index].taken = false;
            foundCard = true;
        }
    }
    if (!foundCard)
    {
        deck[deckSize].copyCard(addedCard);
        deck[deckSize].taken = false;
    }
    return foundCard;
}

// convert input string to rank number
int convertInputToCard(std::string inputStr)
{
    if (inputStr.size() == 0)
    {
        return NO_RANK;
    }
    char input = inputStr[0];
    int returnNum;

    if (input == 'A')
    {
        returnNum = 1;
    } 
    else if (input == 'J')
    {
        returnNum = 11;
    }
    else if (input == 'Q')
    {
        returnNum = 12;
    }    
    else if (input == 'K')
    {
        returnNum = 13;
    } 
    else
    {
        if (::isdigit(input))
        {
            returnNum = std::stoi( inputStr );
        }
        else
        {
            returnNum = NO_RANK;
        }
    }  

    return returnNum;
}

// check if rank is in deck
bool checkIfCardInDeck(card* deck, int deckSize, int testCard)
{
    for (int index = 0; index < deckSize; index++)
    {
        if (deck[index].Number == testCard 
            && !deck[index].taken)
        {
            return true;
        }
    }
    return false;
}

// deal cards to new deck
int fillDeck(card* deck, card* fillableDeck, int deckIndex)
{
    int deckSize = 0;
    for (int newDeckIndex = 0; newDeckIndex < STARTING_DECK_SIZE; newDeckIndex++)
    {
        fillableDeck[newDeckIndex].copyCard(deck[deckIndex+newDeckIndex]);
        deckSize++;
    }

    return deckSize;
}

// print all cards in deck
void printDeck(card* deck, int deckSize)
{
    for (int index = 0; index < deckSize; index++)
    {
        if (!deck[index].taken)
        {
            deck[index].printCard();
        }
    }
    std::cout << "\n";
}

// make ordered deck
void generateDeck(card* deck)
{
    int deckPosition = 0;
    card newCard;
    for (int suit = 0; suit < NUM_SUITS; suit++)
    {
        for (int number = 1; number <= NUM_RANKS; number++)
        {
            newCard.Suit = suit;
            newCard.Number = number;
            deck[deckPosition].copyCard(newCard);
            deckPosition++;
        }
    }
}

// shuffle deck
void shuffleDeck(card* deck)
{
    srand((unsigned)time(0)); 
    int randIndex;
    card temp;

    for (int deckIndex = 0; deckIndex < DECK_LENGTH; deckIndex++)
    {
        randIndex = (rand() % (DECK_LENGTH-1));

        temp.copyCard(deck[deckIndex]);
        deck[deckIndex].copyCard(deck[randIndex]);
        deck[randIndex].copyCard(temp);

    }
}

// print rank as text
void convertNumToCardChar(int number)
{
    if (number == 1)
    {
        std::cout << "A";
    } 
    else if (number == 11)
    {
        std::cout << "J";
    }
    else if (number == 12)
    {
       std::cout << "Q";
    }
    else if (number == 13)
    {
        std::cout << "K";
    }
    else
    {
        std::cout << number;
    }
}

// card functions
bool card::compareSuitCard(card other)
{
    return Suit == other.Suit;
}

bool card::compareNumCard(card other)
{
    return Number == other.Number;
}

bool card::compareBoth(card other)
{
    return compareNumCard(other) && compareSuitCard(other);
}

void card::copyCard(card other)
{
    Suit = other.Suit;
    Number = other.Number;
}

// print single card
void card::printCard()
{
    std::string printNum = "0";
    char printSuit = 'A';

    switch (Suit)
    {
    case 0:
        printSuit = 'S';
        break;
    case 1:
        printSuit = 'H';
        break;
    case 2:
        printSuit = 'D';
        break;
    case 3:
        printSuit = 'C';
        break;
    default:
        break;
    }

    switch (Number)
    {
    case 1:
        printNum = 'A';
        break;
    case 11:
        printNum = 'J';
        break;
    case 12:
        printNum = 'Q';
        break;
    case 13:
        printNum = 'K';
        break;
    default:
        printNum = std::to_string(Number);
        break;
    }

    std::cout << printNum << printSuit << " ";
}

int main() {
    // title
    std::cout << "Go fish Program\n------------------\n\n";
    card deck[DECK_LENGTH];
    srand((unsigned)time(0)); 

    // make and shuffle deck
    generateDeck(deck);
    shuffleDeck(deck);

    // vars
    int deckIndex = 0;
    int userDeckSize = 0;
    int computerDeckSize = 0;
    int inputNum = 0;
    std::string userInput = "";

    // sets
    int userSets = 0;
    int computerSets = 0;

    // player decks
    card userDeck[DECK_LENGTH];
    card computerDeck[DECK_LENGTH];

    // deal cards
    userDeckSize = fillDeck(deck, userDeck, deckIndex);
    deckIndex += userDeckSize;
    computerDeckSize = fillDeck(deck, computerDeck, deckIndex);
    deckIndex += computerDeckSize;

    std::cout << "Go fish Card Game\nGame Starting\n";

    // check first sets
    for (int rank = 1; rank <= NUM_RANKS; rank++)
    {
        if (checkIfFour(computerDeck, rank, computerDeckSize))
        {
            removeAllOfType(computerDeck, rank, computerDeckSize);
            computerSets++;
            std::cout << "\nComputer got a set! Computer sets: " << computerSets;
        }
        if (checkIfFour(userDeck, rank, userDeckSize))
        {
            removeAllOfType(userDeck, rank, userDeckSize);
            userSets++;
            std::cout << "\nYou got a set! Player sets: " << userSets;
        }
    }

    std::cout << "\nYour starting hand:";
    printDeck(userDeck, userDeckSize);

    bool newLineIgnore = false;

    // play loop
    while (userSets + computerSets < 13)
    {
        // user turn
        std::cout << "\nIt's your turn. Ask for a rank/number (2, 3, 4,..., J, Q, K, A):\n>";
        std::cin >> userInput;
        inputNum = convertInputToCard(userInput);
        if (!newLineIgnore)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            newLineIgnore = true;
        }

        if (checkIfCardInDeck(computerDeck, computerDeckSize, inputNum))
        {
            std::cout << "\nOpponent has " << userInput;
            std::cout << "\nCollecting all " << userInput << ", ";
            for (int index = 0; index < computerDeckSize; index++)
            {
                if (computerDeck[index].Number == inputNum
                    && !computerDeck[index].taken)
                {
                    if (!addCardToDeck(userDeck, computerDeck[index], userDeckSize))
                    {
                        userDeckSize++;
                    }
                    computerDeck[index].printCard();
                    
                    computerDeck[index].taken = true;
                }
            }
        }
        else if (deckIndex < DECK_LENGTH)
        {
            std::cout << "\nOpponent does not have "<< userInput;
            std::cout << ". You go fish. New Card: "; 
            deck[deckIndex].printCard();
            std::cout << "\n";
            userDeck[userDeckSize++].copyCard(deck[deckIndex]);
            deckIndex++;
        }
        else
        {
            std::cout << "\nNo more cards to fish!\n";
        }

        if (checkIfFour(userDeck, inputNum, userDeckSize))
        {
            removeAllOfType(userDeck, inputNum, userDeckSize);
            userSets++;
            std::cout << "\nYou got a set! Player sets: " << userSets;
        }

        std::cout << "\nYour current deck: ";
        printDeck(userDeck, userDeckSize);

        // computer turn
        std::cout << "\nOpponents Turn: ";
        inputNum = (rand() % NUM_RANKS)+1;
        std::cout << "Asked for ";
        convertNumToCardChar(inputNum);

        if (checkIfCardInDeck(userDeck, userDeckSize, inputNum))
        {
            std::cout << "\nYou have ";
            convertNumToCardChar(inputNum);
            std::cout << " Collecting all ";
            convertNumToCardChar(inputNum);
            std::cout << ", ";
            for (int index = 0; index < userDeckSize; index++)
            {
                if (userDeck[index].Number == inputNum
                    && !userDeck[index].taken)
                {
                    if (!addCardToDeck(computerDeck, userDeck[index], computerDeckSize))
                    {
                        computerDeckSize++;
                    }
                    userDeck[index].printCard();
                    userDeck[index].taken = true;
                }
            }
        }
        else if (deckIndex < DECK_LENGTH)
        {
            std::cout << "\nComputer went fish";
            computerDeck[computerDeckSize++].copyCard(deck[deckIndex]);
            deckIndex++;
        }
        else
        {
            std::cout << "\nNo more cards to fish!\n";
        }

        if (checkIfFour(computerDeck, inputNum, computerDeckSize))
        {
            removeAllOfType(computerDeck, inputNum, computerDeckSize);
            computerSets++;
            std::cout << "\nOpponent got a set! Computer sets: " << computerSets;

        }

        std::cout << "\nYour current deck: ";
        printDeck(userDeck, userDeckSize);

    }

    // results
    std::cout << "\nGame Over!\n Player sets: " << userSets <<
    "\nComputer sets: " << computerSets;
    if (computerSets > userSets)
    {
        std::cout << "\nComputer Wins!";
    }
    else if (userSets > computerSets)
    {
        std::cout << "\nPlayer Wins!";
    }
    else
    {
        std::cout << "\nIt's a tie!";
    }
    

    return 0;
}
