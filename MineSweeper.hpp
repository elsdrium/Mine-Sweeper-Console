#ifndef _MINESWEEPER_HPP_

#define _MINESWEEPER_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace MineSweeperGame {

const double MaxBombRate = 0.8;

class MineSweeper {
private:
	typedef int MType;

	// column, row, bombs count, unopened lattices count
	size_t col, row, bcount, ucount;

	// •Œ vector< vector<T> > ®”™Ì•‹§G∫˚∞}¶C, •H´KØ‡∞ ∫A®M©w§j§p
	vector< vector<MType> > matrix;

	inline void  PutBomb( size_t bcount );
	inline void  InitMatrix( size_t col, size_t row );
	inline void  Reset();
	inline void  Open( int x, int y );    // open a lattice
	inline void  Spread( int x, int y );  // spread lattices around the (x,y).
	inline MType BombCountAround( int x, int y );
	inline void  CheckWin();
	inline void  Draw() const;
	inline void  NewGame();
	inline void  InputArgs();   // set the col. row. and the bombs count of the game.

public:
	MineSweeper();
	MineSweeper( MineSweeper& _M );
	void Play();

private:
	enum {
		NoBomb = -1,  // unopened, no bomb
		Bomb   = -2,  // unopened, bomb

		// opened, and there are N bombs around the lattice.
		B0     =  0,
		B1     =  1,
		B2     =  2,
		B3     =  3,
		B4     =  4,
		B5     =  5,
		B6     =  6,
		B7     =  7,
		B8     =  8,
		// B9 is a impossible state.
	};

};

struct RangeError { };
struct YouLose    { };
struct YouWin     { };
struct GameFinish { };


} // namespace MineSweeperGame
#endif // _MINESWEEPER_HPP_
