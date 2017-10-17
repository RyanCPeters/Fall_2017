#include <iostream>
#define SIZE 8
using namespace std;

void init( bool t[SIZE][SIZE] ) {
  for ( int i = 0; i < SIZE; i++ )
    for ( int j = 0; j < SIZE; j++ )
      t[i][j] = false;
}

void print( bool t[SIZE][SIZE] ) {
  for ( int row = 0; row < SIZE; row++ ) {
    for (int col = 0; col < SIZE; col++ )
      cout << ( ( t[row][col] ) ? "X" : "." );
    cout << endl;
  }
}

bool safeLocation( bool t[SIZE][SIZE], int row, int col ) {
  for ( int prevCol = 0; prevCol < col; prevCol++ ) {
    if ( t[row][prevCol] )           
      return false;  // another queen stays in the same row
    int upperLeftDiagonal = row - ( col - prevCol );
    int lowerLeftDiagonal = row + ( col - prevCol );
    if ( upperLeftDiagonal >= 0 && t[upperLeftDiagonal][prevCol] )
      return false;  // another queen stays in a upper left diagonal line
    if ( lowerLeftDiagonal < SIZE && t[lowerLeftDiagonal][prevCol] )
      return false;  // another queen stays in a lower left diagonal line
  }
  return true;
}

bool addQueen( bool t[SIZE][SIZE], int col ) {
  if ( col >= SIZE )
    return true;                        // all cols have been examined
  for ( int row = 0; row < SIZE; row++ ) {
    if ( safeLocation( t, row, col ) ) {// this row may be a candidate
      t[row][col] = true;               // place a new queen;
      if ( addQueen( t, col + 1 ) )
	return true;                    // all the following cols were filled
      else
	t[row][col] = false;            // A wrong position. Try the next row
    }
  }
  return false;                         // all rows examined, but no candidates
}

int main( ) {
  bool table[SIZE][SIZE];   // there are no matrix templates in STL

  init( table );
  if ( addQueen( table, 0 ) )
    print( table );
  else
    cout << "no solution" << endl;
}
