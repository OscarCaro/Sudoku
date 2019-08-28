#ifndef PlayerList_h
#define PlayerList_h

#include "Player.h"

namespace playerList {

	const std::string fileName = "playerlist.txt";
	const int INIT_SIZE = 5;

	typedef player::tPlayerPtr* tArrayPtr;		// Pointer to an array of pointers

	typedef struct {
		tArrayPtr players;		// Pointer to an array of pointers
		int count;
		int size;
	}tPlayerList;

	void create ( tPlayerList& list );			// Initializes list as an empty list.
	bool load ( tPlayerList& list );			// Loads into list the content of playerslist.txt
													// True if: file could be open
	void display ( const tPlayerList& list );
	bool save ( const tPlayerList& list );		// Stores in playerslist.txt the content of list
	void playerScore ( tPlayerList& list, int score );
		/* Asks for a player ID and her position in list is updated.The update can modify the score
		   ( if the player was on the list ) or add the player to the list ( with the score ) if
			the list is not full. */
	void addPlayer ( tPlayerList& list, int pos, std::string id, int score );
		// Add a new player (if there's room for one more) at position 'pos', shifting the rest to the right
	bool find ( const tPlayerList& list, std::string id, int& pos );
		/* Locates the player with the identifier id in the list; returns true and the position (pos) where
			the player is, or false and the position where the player should be if not on the list.*/
	int bSearch ( const  tPlayerList& list, std::string id, int beg, int end );
	tPlayerList rankSort ( const tPlayerList& list );
		/* Returns a copy of the list sorted by score (descending, and if score matches another,
		by ID in descending order). Algorithm: Selection Sort*/
	void matchedScores ( tPlayerList& sort );
		// If an score matches another, sort them by ID in descending order	
	void sortById ( tPlayerList& sort, int beg, int end );
		// Sort by Id (descending order) the segment beg-end of the list
	void reverseOrder ( tPlayerList& list, int beg, int end );
		// Re-sort the list in opposite order 
	void resize ( tPlayerList& list );	// Makes the list twice as big
	void freeArray ( tPlayerList& list );	// Release the list.players dynamic array of pointers
	void freePlayers ( tPlayerList& list );	// Release each dynamic tPlayer pointed in the array

}

#endif