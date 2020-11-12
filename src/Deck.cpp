#include <stdlib.h>
#include <time.h>

#include "Deck.h"

Deck::Deck()
  : deck_(types::DECK_SIZE){
}

std::deque<types::Card> Deck::get_new() {
  using namespace types;
  std::deque<types::Card> new_deck;
  for (uint8_t suit = static_cast<uint8_t>(Suit::Hearts); suit < SUIT_COUNT; suit++) {
    for (uint8_t rank = static_cast<uint8_t>(Rank::Ace); rank < RANK_COUNT; rank++) {
      new_deck.emplace_back(Card{ rank, suit });
    }
  }
  return new_deck; 
};

void Deck::clear() {
  // deck_.
};

void Deck::shuffle() {
  using namespace types;

  auto ordered_deck = get_new();
  srand(static_cast<uint32_t>(time(NULL) ));

  uint8_t filled = 0;

  for (uint8_t suit = static_cast<uint8_t>(Suit::Hearts); suit < SUIT_COUNT; suit++) {
    for (uint8_t rank = static_cast<uint8_t>(Rank::Ace); rank < RANK_COUNT; rank++) {
      uint8_t index = 0;
      index = rand() % (DECK_SIZE + 1 - filled++);
      deck_.emplace_back(std::move(ordered_deck[index]));
    }
  }
}