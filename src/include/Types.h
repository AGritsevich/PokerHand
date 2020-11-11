#pragma once
#include <cstdint>

namespace types {
  constexpr auto RANK_START_LINE = __LINE__;
  enum class Rank : uint8_t {
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
  };
  constexpr auto RANK_COUNT = __LINE__ - RANK_START_LINE - 3;

  constexpr auto SUIT_START_LINE = __LINE__;
  enum class Suit : uint8_t {
    Hearts = 1,
    Diamonds,
    Clubs,
    Spades
  };
  constexpr auto SUIT_COUNT = __LINE__ - SUIT_START_LINE - 3;
  
  struct Card {
    Rank rank_;
    Suit suit_;

    Card(uint8_t rank, uint8_t suit) {
      rank_ = static_cast<Rank>(rank);
      suit_ = static_cast<Suit>(suit);
    }
  };

  static constexpr uint8_t DECK_SIZE = RANK_COUNT * SUIT_COUNT;
  static constexpr uint8_t HAND_SIZE = 5u;
  using Hand = Card[HAND_SIZE];
} // namespace types