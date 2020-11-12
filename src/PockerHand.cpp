#include "Log.h"
#include "PockerHand.h"
#include <Deck.h>
#include "..\simpleson\json.h"

PockerHand::PockerHand() {
  enabled_ = true;
}

void PockerHand::disable() {
  if (thread_->joinable()) {
    thread_->join();
  }
}

bool PockerHand::isFlash(const types::Hand& one) {
  using namespace types;
  
  for (auto i = 1; i < (sizeof(one) / sizeof(Card)); i++) {
    if (one[0].suit_ != one[i].suit_) 
      return false;
  }
  return true;
}

int32_t compare(const void* a, const void* b) { 
  return (*(int8_t*)a - *(int8_t*)b); 
}

bool PockerHand::isStraight(types::Hand one) {
  using namespace types;

  std::qsort(one, sizeof(Hand) / sizeof(Card), sizeof(Card), compare);

  for (auto i = 1; i < (sizeof(one) / sizeof(Card)); i++) {
    if (one[i-1].rank_ != static_cast<Rank>(static_cast<uint8_t>(one[i].rank_) + 1))
      return false;
  }
  return true;
}

void PockerHand::proceed(std::string message) {
  using namespace types;
  Deck new_deck;
  // Parse the input
  json::jobject result = json::jobject::parse(message);
  std::vector<std::vector<uint8_t>> cards;// = static_cast<std::vector<uint8_t>(json::jobject::parse(result));

  Hand hand;
  uint8_t ind = 0;
  for (auto ind = 0; ind < HAND_SIZE; ind++) {
    hand[ind++] = Card(cards[ind][0], cards[ind][1]);
  }

  new_deck.shuffle(); // just for be

  bool is_flash = isStraight(hand);
  bool is_straight = isStraight(hand);

  if (is_flash && is_straight) {
    lg.print("It's Flash straight");
  }

  if (is_flash) {
    lg.print("It's Straight");
  }

  if (is_straight) {
    lg.print("It's Flash");
  }
}