// ООП Курсовой.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


class Card 
{
public:
    string suit;
    string value;

    Card(const string& s, const string& v) : suit(s), value(v) {}
};


class Deck 
{
private:
    vector<Card> cards;

public:
    Deck() 
    {
        
        string suits[] = { "\u2665", "\u2666", "\u2663", "\u2660" };
        string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

        for (const string& suit : suits) 
        {
            for (const string& value : values) 
            {
                cards.push_back(Card(suit, value));
            }
        }
    }

    
    void shuffle() 
    {
        srand(time(0));
        for (int i = 0; i < cards.size(); i++) 
        {
            int j = rand() % cards.size();
            swap(cards[i], cards[j]);
        }
    }


    Card dealCard() 
    {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

   
    bool isEmpty() const 
    {
        return cards.empty();
    }
};


class Hand 
{
private:
    vector<Card> cards;

public:
    void addCard(const Card& card) 
    {
        cards.push_back(card);
    }

    int getScore() const
    {
        int score = 0;
        int numAces = 0;

        for (const Card& card : cards) 
        {
            if (card.value == "Ace") 
            {
                score += 11;
                numAces++;
            }
            else if (card.value == "Jack" || card.value == "Queen" || card.value == "King") 
            {
                score += 10;
            }
            else
            {
                score += stoi(card.value);
            }
        }

        while (score > 21 && numAces > 0)
        {
            score -= 10;
            numAces--;
        }

        return score;
    }

    void display() const 
    {
        for (const Card& card : cards) 
        {
            cout << card.value  << card.suit << endl;
        }
    }
};

int main() 
{
    Deck deck;
    deck.shuffle();

    Hand playerHand;
    Hand dealerHand;

   
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());

    cout << "Player's cards:" << endl;
    playerHand.display();

    cout << "\nDealer's cards:" << endl;
    dealerHand.display();

    
    while (true) 
    {
        int playerScore = playerHand.getScore();
        if (playerScore == 21) 
        {
            cout << "Congratulations! You win!" << endl;
            break;
        }
        else if (playerScore > 21)
        {
            cout << " You lose." << endl;
            break;
        }

        cout << "\nDo you want to hit? (y/n): ";
        string choice;
        cin >> choice;

        if (choice == "y")
        {
            playerHand.addCard(deck.dealCard());
            cout << "\nYour cards:" << endl;
            playerHand.display();
        }
        else
        {
            break;
        }
    }


    while (true)
    {
        int dealerScore = dealerHand.getScore();
        if (dealerScore == 21) 
        {
            cout << "Dealer wins!" << endl;
            break;
        }
        else if (dealerScore > 21)
        {
            cout << "Dealer lost!" << endl;
            break;
        }

        if (dealerScore < 17) 
        {
            dealerHand.addCard(deck.dealCard());
            cout << " Dealer's cards: " << endl;
            dealerHand.display();
        }
        else 
        {
            break;
        }
    }
    
   
    int playerScore = playerHand.getScore();
    int dealerScore = dealerHand.getScore();

    cout << "\nYour score: " << playerScore << endl;
    cout << "Dealer's score: " << dealerScore << endl;

    if (playerScore <= 21 && dealerScore <= 21) {
        if (playerScore > dealerScore) {
            cout << "You win!" << endl;
        }
        else if (playerScore < dealerScore) {
            cout << "Dealer wins!" << endl;
        }
        else {
            cout << "It's a tie!" << endl;
        }
    }
    else if (playerScore <= 21 && dealerScore > 21) {
        cout << "You win!" << endl;
    }
    else if (playerScore > 21 && dealerScore <= 21) {
        cout << "Dealer wins!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }
    return 0;
}
