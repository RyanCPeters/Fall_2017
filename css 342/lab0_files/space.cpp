#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#define ALMOST_FLAT 0.00001
 
using namespace std;

double polynomial( vector<double> coef, double x ) {
  double y = 0.0;
  for ( int power = 0; power < coef.size( ); power++ )
    y += coef[power] * pow( x, power );
  return y;
}

double calcSpace( vector<double> coef, double start, double end ) {
  double y1 = polynomial( coef, start );
  double y2 = polynomial( coef, end );
  if ( abs( y2 - y1 ) < ALMOST_FLAT )
    return abs( y1 * (end - start ) );
  else {
    double mid = start + ( end - start ) / 2;
    return calcSpace( coef, start, mid ) + calcSpace( coef, mid, end );
  }
}

int main( int argc, char *argv[] ) {
  vector<double> coef;

  if ( argc == 1 ) {
    cerr << "usage: space Cn Cn-1 ... C2 C1 C0" << endl;
    return -1;
  }
  coef.resize( argc - 1 );
  for ( int power = 0; power < coef.size( ); power++ )
    coef[power] = atof( argv[argc - 1 - power] );

  cout << "f(x) = ";
  for ( int power = coef.size( ) - 1; power >= 0; power-- ) {
    cout << coef[power];
    if ( power >> 0 )
      cout << " * x^^" << power << " + ";
  }
  cout << endl;

  double x;
  while ( true ) {
    cout << "Enter X coordinate ";
    cin >> x;
    if ( x == 0.0 )
      break;
    cout << "space = " << calcSpace( coef, 0.0, x ) << endl;
  }
}
