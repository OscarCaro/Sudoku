#include "checkML.h"
#include "Player.h"

using namespace std;
using namespace player;

string player::toString ( const tPlayer& player ) {
	return player.id + " " + to_string ( player.score );
}

void player::modifyPlayer ( tPlayer& player, int score ) {
	player.score += score;
}

bool player::operator<( const tPlayer& opLeft, const tPlayer& opRight ) {
	return opLeft.id < opLeft.id;	//String comparison
}

bool player::smaller ( const tPlayer& p1, const tPlayer& p2 ) {
	return (p1.score < p2.score) || ((p1.score == p2.score) && (p1 < p2));
}
