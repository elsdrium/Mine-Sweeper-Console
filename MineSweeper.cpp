#include "MineSweeper.hpp"

using namespace MineSweeperGame;

MineSweeper::MineSweeper() : col(0), row(0), bcount(0), ucount(0)
{
}

MineSweeper::MineSweeper( MineSweeper &ms )
{
	this->col    = ms.col;
	this->row    = ms.row;
	this->bcount = ms.bcount;
	this->ucount = ms.ucount;
	this->matrix = ms.matrix;
}

inline void MineSweeper::PutBomb( size_t bcount )
{
	// put bomb randomly
	srand( time(0) );
	for( int i=0, x, y; i!=bcount; ++i ) {
		x = rand() % col;
		y = rand() % row;

		if( matrix[x][y] != Bomb ) {
			matrix[x][y]  = Bomb;
		}
		else {   // it guarantees 'bcount' bombs would be set up
			--i;
			continue;
		}
	}
}

inline void MineSweeper::InitMatrix( size_t col, size_t row )
{
	vector< vector<MType> >( col, vector<MType>( row, NoBomb ) ).swap( matrix );
}

inline void MineSweeper::Reset()
{
	for( int i=0; i!=col; ++i )
		for( int j=0; j!=row; ++j )
			matrix[i][j] = NoBomb;
	ucount = col * row;
}

inline void MineSweeper::Open( int x, int y )
{
	MType &here( matrix[x][y] );

	if( x >= col || y >= row )
		throw RangeError();
	if( here != Bomb && here != NoBomb )
		return;
	if( here == Bomb )
		throw YouLose();

	// count bombs around, and let ucount -1
	here = BombCountAround( x, y );
	--ucount;

	// if no bomb around, then spread here
	if( !here )
		Spread( x, y );
}

inline void MineSweeper::Spread( int x, int y )
{
	for( int i=-1; i<=1; ++i ) { // from -1 to 1
		for( int j=-1; j<=1; ++j ) { // from -1 to 1
			if( x+i >= col || y+j >= row )
				continue;
			Open( x+i, y+j );
		}
	}
}

inline MineSweeper::MType MineSweeper::BombCountAround( int x, int y )
{
	MType count = 0;
	for( int i=-1; i<=1; ++i ) { // from -1 to 1
		for( int j=-1; j<=1; ++j ) { // from -1 to 1
			if( x+i >= col || y+j >= row )
				continue;
			if( matrix[ x+i ][ y+j ] == Bomb )
				++count;
		}
	}
	return count;
}

inline void MineSweeper::CheckWin()
{
	if( ucount == bcount )
		throw YouWin();
}

inline void MineSweeper::Draw() const
{
	cout << "  ";
	for( int i=0; i!=col; ++i )
		cout << setw(2) << i+1;  // adapt index to start from 1 for user
	cout << endl;

	// row first
	for( int j=0; j!=row; ++j ) {
		cout << setw(2) << j+1 ;

		for( int i=0; i!=col; ++i ) {
			switch( matrix[i][j] ) {
				case Bomb:
				case NoBomb:
					cout << "█"; break;
				case B0:  cout << "　"; break;
				case B1:  cout << "１"; break;
				case B2:  cout << "２"; break;
				case B3:  cout << "３"; break;
				case B4:  cout << "４"; break;
				case B5:  cout << "５"; break;
				case B6:  cout << "６"; break;
				case B7:  cout << "７"; break;
				case B8:  cout << "８"; break;
				default:  cout << "??";
			}
		}
		cout << setw(2) << j+1 << endl;
	}

	cout << "  ";
	for( int i=0; i!=col; ++i )
		cout << setw(2) << i+1;
	cout << endl;
}

// No fool-proofing
inline void MineSweeper::NewGame()
{
	int x, y;

	Reset();
	PutBomb( bcount );

	while(true) {
		Draw();
		cout << "Please input the coord. -->" ;
		cin >> x >> y;

		try {
			Open( x-1, y-1 ); // from (1,1) to (col,row)
			CheckWin();
		}
		catch( RangeError ) {
			cout << "Input Error!" << endl;
		}
		catch( YouLose ) {
			cout << "You Lose!\a" << endl;
			system("pause");
			throw GameFinish();
		}
		catch( YouWin ) {
			Draw();
			cout << "You Win!\a" << endl;
			system("pause");
			throw GameFinish();
		}
	}
}

// No fool-proofing
inline void MineSweeper::InputArgs()
{
	cout << "Please input the col. of the game." << endl;
	cin >> col;
	cout << "Please input the row. of the game." << endl;
	cin >> row;
	cout << "Please input the bombs count of the game." << endl;
	cin >> bcount;
	if( !bcount || !col || !row || cout.fail() ) {
		cerr << "Input error!" << endl;
		throw cout.fail();
	}

	if( double( bcount ) / double( col*row ) > MaxBombRate )
		bcount = double( col*row ) * MaxBombRate;

	cout << "OK." << endl;
}

void MineSweeper::Play()
{
	cout << "Welcome to the Mine Sweeper game which designed by Chen." << endl;
	cout << "The rules of this game just likes the Mine Sweeper in Windows." << endl;
	cout << "So, here is nothing expression about this game." << endl;
	cout << "Good luck!  Have fun.  :) \n" << endl;

	if( !col || !row || !bcount ) {
		InputArgs();
		InitMatrix( col, row );
	}

	char input(0);
	while(true) {
		cout << "== Please select a option. ==" << endl
		     << "  1  Start a new game."        << endl
			 << "  2  Setup."                   << endl
			 << "  3  Exit."                    << endl
			 << "=============================" << endl;

		cin >> input;
		if( input == '1' ) {
			try {
				NewGame();
			}
			catch( GameFinish ) {
				continue;
			}
			catch( ... ) {
				cerr << "Catch a unidentified exception!  The game will be aborted." << endl;
//				system("pause");
				exit( EXIT_FAILURE );
			}
		}
		else if( input == '2' ) {
			InputArgs();
			InitMatrix( col, row );
		}
		else if( input == '3' )
			break;
		else
			continue;
	}
}
