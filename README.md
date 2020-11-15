C++ Test
● The following questions are to be implemented using C++03, 11 or 14, using no libraries other
than the standard (Boost not permitted).
1. Consider a standard deck of 52 distinct cards used in poker. Assuming that the only
things you need to know from each card are:
i) rank - (A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K)
ii) suit - (Hearts, Diamonds, Clubs, Spades)
a) Design two data structures/types to represent a card and a deck. Make your priority that
it should be easy to create algorithms and data structures around these two types,
without compromising (too much) memory or processing time.
b) Implement a method ‘shuffle’ to randomize all the cards in a deck.
c) Implement a method ‘isFlush’ that checks if all cards passed as parameter have the
same suit.
d) Implement a method ‘isStraight’ that checks if all 5 cards passed as a parameter have
consecutive ranks. Example:
i) A, 5, 2, 3, 4 is a straight
ii) A, 5, 3, 4, 6 is NOT a straight
iii) 6, 7, 10, 9, 8 is a straight
iv) 10, K, A, J, Q is a straight
2. Create an application that listens on a UNIX domain socket for events in the form of
strings in the standard JSON format. Each event should be processed by one of N
threads. Each thread should perform an operation with the event that might take up to
several seconds to be executed and then log its results into one common text file.