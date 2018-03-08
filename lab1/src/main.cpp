//////////////////////////
//     Coleman Lyski    //
//    August 29, 2017   //
//   Assignment: Lab 1  //
//    Data Structures   //
//////////////////////////

#include <iostream>
#include <math.h>
#include <cstdio>
using namespace std;

void inputFractions(int & n1, int & d1, int & n2, int & d2, int & n3, int & d3, int & n4, int & d4) {
	// Fraction 1
	cout << "Enter the first fraction numerator: ";
	cin >> n1;
	if(n1 < 0) {
		do {
			cout << "The numerator may not be negative." << endl;
			cout << "Enter the first fraction numerator: ";
			cin >> n1;
		} while(n1 < 0);
	};
	cout << "Enter the first fraction denominator: ";
	cin >> d1;
	if(d1 <= 0) {
		do {
			cout << "The denominator may not be negative or zero." << endl;
			cout << "Enter the first fraction denominator: ";
			cin >> d1;
		} while(d1 <= 0);
	};

	// Fraction 2
	cout << "Enter the second fraction numerator: ";
	cin >> n2;
	if(n2 < 0) {
		do {
			cout << "The numerator may not be negative." << endl;
			cout << "Enter the second fraction numerator: ";
			cin >> n2;
		} while(n2 < 0);
	};
	cout << "Enter the second fraction denominator: ";
	cin >> d2;
	if(d2 <= 0) {
		do {
			cout << "The denominator may not be negative or zero." << endl;
			cout << "Enter the second fraction denominator: ";
			cin >> d2;
		} while(d2 <= 0);
	};

	// Fraction 3
	cout << "Enter the third fraction numerator: ";
	cin >> n3;
	if(n3 < 0) {
		do {
			cout << "The numerator may not be negative." << endl;
			cout << "Enter the third fraction numerator: ";
			cin >> n3;
		} while(n3 < 0);
	};
	cout << "Enter the third fraction denominator: ";
	cin >> d3;
	if(d3 <= 0) {
		do {
			cout << "The denominator may not be negative or zero." << endl;
			cout << "Enter the third fraction denominator: ";
			cin >> d3;
		} while(d3 <= 0);
	};

	// Fraction 4
	cout << "Enter the fourth fraction numerator: ";
	cin >> n4;
	if(n4 < 0) {
		do {
			cout << "The numerator may not be negative." << endl;
			cout << "Enter the fourth fraction numerator: ";
			cin >> n4;
		} while(n4 < 0);
	};
	cout << "Enter the fourth fraction denominator: ";
	cin >> d4;
	if(d4 <= 0) {
		do {
			cout << "The denominator may not be negative or zero." << endl;
			cout << "Enter the fourth fraction denominator: ";
			cin >> d4;
		} while(d4 <= 0);
	};
}

void reduce1(int & num, int & den) {
	int a,b,i = 0;

	// set num and den variables
	a = den;
	b = num;

	for (i = 50; i > 1; i--)
	{
		if ((a % i == 0) && (b % i == 0))	// If both num and den are divisible by same number, then divide
		{
			a /= i;
			b /= i;
		}
	}

	// pass new num and den back
	den = a;
	num = b;

}

void reduce2(int & num, int & den, int & whole) {
	int a,b = 0;
	int w = 0;

	// set num and den
	a = den;
	b = num;

	if( b - a >= 0 ) {
		do {
			b = b - a;
			w++;
		} while( b - a >= 0 );	// while the num > den, subtract and add +1 to whole number
	}

	reduce1(b, a);

	// pass back num, den, and whole
	den = a;
	num = b;
	whole = w;

}

int* addFractions(int num1, int den1, int num2, int den2) {
	// function returns a pointer to an array
	int a,b,c,d = 0;
	int x,y = 0;
	int static sol[2];

	a = num1;
	b = den1;
	c = num2;
	d = den2;

	// numerators multiplied by opposite den
	a = a*d;
	c = c*b;

	// numerators added and common den found
	x = a + c;
	y = b * d;

	// set values of the array
	sol[0] = x;
	sol[1] = y;

	// returns a pointer
	return sol;
}

bool isGreater(int num1, int den1, int num2, int den2) {
	double a, b, c, d, f1, f2;
	a = num1;
	b = den1;
	c = num2;
	d = den2;

	// fractions turned to doubles
	f1 = a / b;
	f2 = c / d;

	// doubles compared
	if( f1 > f2 ) {
		return true;
	} else {
		return false;
	}
}

void fracPower(int & num, int & den, int power) {
	int a, b, p;
	a = num;
	b = den;
	p = power;

	// pow function used
	a = pow(a, p);
	b = pow(b, p);

	reduce1(a, b);

	// return values
	num = a;
	den = b;
}

int main() {
	int n1, d1, n2, d2, n3, d3, n4, d4 = 0;

    ///////////////////////////////////////////////
	// Get fractions
	inputFractions(n1, d1, n2, d2, n3, d3, n4, d4);
	cout << endl << "Reduce 1 Function:" << endl;

	// Fraction 1 first reduce
	cout << n1 << "/" << d1 << " is reduced to ";
	reduce1(n1, d1);
	if( n1 == 0 ) {
		cout << "0" << endl;
	} else if( n1 == d1 ) {
		cout << "1" << endl;
	} else if( d1 == 1 ) {
		cout << n1 << endl;
	} else {
		cout << n1 << "/" << d1 << endl;
	}

	// Fraction 2 first reduce
	cout << n2 << "/" << d2 << " is reduced to ";
	reduce1(n2, d2);
	if( n2 == 0 ) {
		cout << "0" << endl;
	} else if( n2 == d2 ) {
		cout << "1" << endl;
	} else if( d2 == 1 ) {
		cout << n2 << endl;
	} else {
		cout << n2 << "/" << d2 << endl;
	}

	// Fraction 3 first reduce
	cout << n3 << "/" << d3 << " is reduced to ";
	reduce1(n3, d3);
	if( n3 == 0 ) {
		cout << "0" << endl;
	} else if( n3 == d3 ) {
		cout << "1" << endl;
	} else if( d3 == 1 ) {
		cout << n3 << endl;
	} else {
		cout << n3 << "/" << d3 << endl;
	}

	// Fraction 4 first reduce
	cout << n4 << "/" << d4 << " is reduced to ";
	reduce1(n4, d4);
	if( n4 == 0 ) {
		cout << "0" << endl;
	} else if( n4 == d4 ) {
		cout << "1" << endl;
	} else if( d4 == 1 ) {
		cout << n4 << endl;
	} else {
		cout << n4 << "/" << d4 << endl;
	}

	cout << endl;


	///////////////////////////////////////////
	// Get fractions
	inputFractions(n1, d1, n2, d2, n3, d3, n4, d4);
	int whole = 0;

	cout << endl << "Reduce 2 Function:" << endl;

	// Fraction 1 second reduce
	cout << n1 << "/" << d1 << " is reduced to ";
	reduce2(n1, d1, whole);
	if( n1 == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << n1 << "/" << d1 << endl;
	}

	// Fraction 2 second reduce
	cout << n2 << "/" << d2 << " is reduced to ";
	reduce2(n2, d2, whole);
	if( n2 == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << n2 << "/" << d2 << endl;
	}

	// Fraction 3 second reduce
	cout << n3 << "/" << d3 << " is reduced to ";
	reduce2(n3, d3, whole);
	if( n3 == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << n3 << "/" << d3 << endl;
	}

	// Fraction 4 second reduce
	cout << n4 << "/" << d4 << " is reduced to ";
	reduce2(n4, d4, whole);
	if( n4 == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << n4 << "/" << d4 << endl;
	}

	cout << endl;


	///////////////////////////////////////////
	// Get fractions
	cout << "Add fractions... " << endl;
	inputFractions(n1, d1, n2, d2, n3, d3, n4, d4);
	int n5, d5, n6, d6, n7, d7, n8, d8 = 0;
	int f5an, f5ad, f5bn, f5bd, f6an, f6ad, f6bn, f6bd, f7an, f7ad, f7bn, f7bd, f8an, f8ad, f8bn, f8bd = 0;
	int *added;

	// Frac1 + Frac2
	cout << endl << "The sum of " << n1 << "/" << d1 << " and " << n2 << "/" << d2 << " is ";
	added = addFractions(n1, d1, n2, d2);
	f5an = added[0];
	f5bn = added[0];
	n5 = added[0];
	f5ad = added[1];
	f5bd = added[1];
	d5 = added[1];
	cout << n5 << "/" << d5 << endl;

	cout << n5 << "/" << d5 << " reduced by reduce1 is ";
	reduce1(f5an, f5ad);
	if( f5an == 0 ) {
		cout << "0" << endl;
	} else if( f5an == f5ad ) {
		cout << "1" << endl;
	} else if( f5ad == 1 ) {
		cout << f5an << endl;
	} else {
		cout << f5an << "/" << f5ad << endl;
	}

	cout << n5 << "/" << d5 << " reduced by reduce2 is ";
	reduce2(f5bn, f5bd, whole);
	if( f5bn == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << f5bn << "/" << f5bd << endl;
	}

	cout << endl;

	// Frac1 + Frac3
	cout << "The sum of " << n1 << "/" << d1 << " and " << n3 << "/" << d3 << " is ";
	added = addFractions(n1, d1, n3, d3);
	f6an = added[0];
	f6bn = added[0];
	n6 = added[0];
	f6ad = added[1];
	f6bd = added[1];
	d6 = added[1];
	cout << n6 << "/" << d6 << endl;

	cout << n6 << "/" << d6 << " reduced by reduce1 is ";
	reduce1(f6an, f6ad);
	if( f6an == 0 ) {
		cout << "0" << endl;
	} else if( f6an == f6ad ) {
		cout << "1" << endl;
	} else if( f6ad == 1 ) {
		cout << f6an << endl;
	} else {
		cout << f6an << "/" << f6ad << endl;
	}

	cout << n6 << "/" << d6 << " reduced by reduce2 is ";
	reduce2(f6bn, f6bd, whole);
	if( f6bn == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << f6bn << "/" << f6bd << endl;
	}

	cout << endl;


	// Frac2 + Frac3
	cout << "The sum of " << n2 << "/" << d2 << " and " << n3 << "/" << d3 << " is ";
	added = addFractions(n2, d2, n3, d3);
	f7an = added[0];
	f7bn = added[0];
	n7 = added[0];
	f7ad = added[1];
	f7bd = added[1];
	d7 = added[1];
	cout << n7 << "/" << d7 << endl;

	cout << n7 << "/" << d7 << " reduced by reduce1 is ";
	reduce1(f7an, f7ad);
	if( f7an == 0 ) {
		cout << "0" << endl;
	} else if( f7an == f7ad ) {
		cout << "1" << endl;
	} else if( f7ad == 1 ) {
		cout << f7an << endl;
	} else {
		cout << f7an << "/" << f7ad << endl;
	}

	cout << n7 << "/" << d7 << " reduced by reduce2 is ";
	reduce2(f7bn, f7bd, whole);
	if( f7bn == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << f7bn << "/" << f7bd << endl;
	}

	cout << endl;


	// Frac2 + Frac4
	cout << "The sum of " << n2 << "/" << d2 << " and " << n4 << "/" << d4 << " is ";
	added = addFractions(n2, d2, n4, d4);
	f8an = added[0];
	f8bn = added[0];
	n8 = added[0];
	f8ad = added[1];
	f8bd = added[1];
	d8 = added[1];
	cout << n8 << "/" << d8 << endl;

	cout << n8 << "/" << d8 << " reduced by reduce1 is ";
	reduce1(f8an, f8ad);
	if( f8an == 0 ) {
		cout << "0" << endl;
	} else if( f8an == f8ad ) {
		cout << "1" << endl;
	} else if( f8ad == 1 ) {
		cout << f8an << endl;
	} else {
		cout << f8an << "/" << f8ad << endl;
	}

	cout << n8 << "/" << d8 << " reduced by reduce2 is ";
	reduce2(f8bn, f8bd, whole);
	if( f8bn == 0 ) {
		cout << whole << endl;
	} else {
		cout << whole << " and " << f8bn << "/" << f8bd << endl;
	}

	cout << endl;


	///////////////////////////////////////////
	// Get fractions
	cout << "Is greater... " << endl;
	inputFractions(n1, d1, n2, d2, n3, d3, n4, d4);
	bool yeet;

	// Frac1 and Frac2
	cout << endl << "The fraction " << n1 << "/" << d1 << " is ";
	yeet = isGreater(n1, d1, n2, d2);
	if( yeet == true ) {
		cout << "greater than " << n2 << "/" << d2 << endl;
	} else {
		cout << "not greater than " << n2 << "/" << d2 << endl;

	}

	// Frac2 and Frac3
	cout << "The fraction " << n2 << "/" << d2 << " is ";
	yeet = isGreater(n2, d2, n3, d3);
	if( yeet == true ) {
		cout << "greater than " << n3 << "/" << d3 << endl;
	} else {
		cout << "not greater than " << n3 << "/" << d3 << endl;

	}

	// Frac2 and Frac4
	cout << "The fraction " << n2 << "/" << d2 << " is ";
	yeet = isGreater(n2, d2, n4, d4);
	if( yeet == true ) {
		cout << "greater than " << n4 << "/" << d4 << endl;
	} else {
		cout << "not greater than " << n4 << "/" << d4 << endl;

	}

	// Frac3 and Frac4
	cout << "The fraction " << n3 << "/" << d3 << " is ";
	yeet = isGreater(n3, d3, n4, d4);
	if( yeet == true ) {
		cout << "greater than " << n4 << "/" << d4 << endl;
	} else {
		cout << "not greater than " << n4 << "/" << d4 << endl;

	}

	cout << endl;


	///////////////////////////////////////////
	// Get fractions
	cout << "Frac power... " << endl;
	inputFractions(n1, d1, n2, d2, n3, d3, n4, d4);
	int n, m, k, l;
	cout << "Enter fraction 1 power: ";
	cin >> n;
	cout << "Enter fraction 2 power: ";
	cin >> m;
	cout << "Enter fraction 3 power: ";
	cin >> k;
	cout << "Enter fraction 4 power: ";
	cin >> l;
	cout << endl;

	// Frac 1
	cout << "The fraction " << n1 << "/" << d1 << " raised to power " << n << " is ";
	fracPower(n1, d1, n);
	if( n1 == 0 ) {
		cout << "0" << endl;
	} else if( n1 == d1 ) {
		cout << "1" << endl;
	} else if( d1 == 1 ) {
		cout << n1 << endl;
	} else {
		cout << n1 << "/" << d1 << endl;
	}

	// Frac 2
	cout << "The fraction " << n2 << "/" << d2 << " raised to power " << m << " is ";
	fracPower(n2, d2, m);
	if( n2 == 0 ) {
		cout << "0" << endl;
	} else if( n2 == d2 ) {
		cout << "1" << endl;
	} else if( d2 == 1 ) {
		cout << n2 << endl;
	} else {
		cout << n2 << "/" << d2 << endl;
	}

	// Frac 3
	cout << "The fraction " << n3 << "/" << d3 << " raised to power " << k << " is ";
	fracPower(n3, d3, k);
	if( n3 == 0 ) {
		cout << "0" << endl;
	} else if( n3 == d3 ) {
		cout << "1" << endl;
	} else if( d3 == 1 ) {
		cout << n3 << endl;
	} else {
		cout << n3 << "/" << d3 << endl;
	}

	// Frac 4
	cout << "The fraction " << n4 << "/" << d4 << " raised to power " << l << " is ";
	fracPower(n4, d4, l);
	if( n4 == 0 ) {
		cout << "0" << endl;
	} else if( n4 == d4 ) {
		cout << "1" << endl;
	} else if( d4 == 1 ) {
		cout << n4 << endl;
	} else {
		cout << n4 << "/" << d4 << endl;
	}

	std::getchar();
	return(0);
}
