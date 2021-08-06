# ScorebasedLRU

Implementation of LRU with a scoring system to improve hit rate

In LRU, you will find a normal LRU implemented using a doubly Linked List and a map.

In LRU + LFU, the same implementation has been modified to keep track of the frequency of a particular page hit.

In LRU-recency, the basic idea of our algorithm is to rank pages based on their recency, frequency and reference rate.

In LRU-SW, a sliding window methord has been used which will limit the number of cache requests.

In LRU-GEO we are decreasing the relavance of past requests by and also keeping track of the total score for each object
