#ifndef Set_h
#define Set_h

namespace set {

	const int N = 9;

	typedef bool t_NumArray[N];			// true = possible || false = not possible

	typedef struct {
		t_NumArray numArray;
		int counter;					// Number of possible values stored in numArray
	} tSet;

	void emptySet ( tSet& set );				// initializes set as an empty set.
	void fullSet ( tSet& set );					// initializes set as a set containing all values in[1.. 9].
	bool isIn ( const tSet& set, int n );		// returns true if set contains n.
	void add ( tSet& set, int n );				// includes n [1..9] in set.
	void erase ( tSet& set, int n );			// deletes n [1..9] from set.
	int size ( const tSet& set );				// returns the number of elements in set.
	void display ( const tSet& set );			// displays the members of set.
	bool one ( const tSet& set, int& n );		/* returns whether set has only one element.
												   If that is the case, n is set to that element.*/
	int findOne ( const tSet& set );			// assuming set has only 1 element, returns this element

}

#endif