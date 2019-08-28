#ifndef Player_h
#define Player_h

#include <string>

namespace player {

	typedef struct {
		std::string id;
		int score;
	}tPlayer;

	typedef tPlayer* tPlayerPtr;

	std::string toString ( const tPlayer& player );		//Format: identifier score
	void modifyPlayer ( tPlayer& player, int score );	//Add score to player's score
	bool operator<( const tPlayer& opLeft, const tPlayer& opRight );
	// Overload of operator < to compare identifiers. (true -> left goes first alphabetically)
	bool smaller ( const tPlayer& p1, const tPlayer& p2 );
	// True if:		p1's points < p2's points
	//				p1's points = p2's points  and  p1's id < p2's id

}

#endif
