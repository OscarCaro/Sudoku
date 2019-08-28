#ifndef Cell_h
#define Cell_h

#include "Set.h"

namespace cell {

	typedef enum { empty, fixed, filled }tState;
	typedef struct {
		tState state;
		int num;
		set::tSet possible;
	}tCell;

	void initCell ( tCell& cell );		// initialize Cell state = empty, Possible = [1...9]
	void fillCell ( tCell& cell, char c, bool isFixed = false );		// Fills state and value of cell
		// Mode 1: fillCell(cell, ' ')			->  Empty cell
		// Mode 2: fillCell(cell, 'c')			->  Not fixed, filled with c ['1' ... '9']   (fixed = false autom.)
		// Mode 3: fillCell(cell, 'c', true)	->  Fixed, filled with c ['1' ... '9']
	void bgColor ( int color );		// Set the background color (0 = black, 1 = blue, 4 = red)
	void drawCell ( const tCell& cell );	//Draws the cell
		// Fixed cell   -> Blue background
		// Filled cell  -> Red background
		// Other		-> Black background (default)
	bool isSimple ( const tCell& cell, int& number );
	// Cell with only one possible value	-> bool = true || number = the value
	// Otherwise							-> bool = false

}

#endif 
