/****************************************************************************************
# *  Name: Yash Sharma
# *  Cruz ID: yhsharma
# *  Assignment Name: pa6
# *****************************************************************************************/

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include "List.h"

typedef long base;
typedef int power;

// Class Constructors & Destructors ---------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:·
// signum=0, digits=().

BigInteger::BigInteger() {
    signum = 0;
    digits = ();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.

BigInteger::BigInteger(std::string s) {
    signum = 0;
    digits = ();
    if (s != NULL) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    if (s == NULL) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N);


// Access functions --------------------------------------------------------
// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,·
// negative or 0, respectively.
int BigInteger::sign() const;

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const;


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of·
// this BigInteger positive <--> negative.·
void BigInteger::negate();

// BigInteger Arithmetic operations ---------------------------------------       -

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger::add(const BigInteger& N) const;

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger::sub(const BigInteger& N) const;

// mult()
// Returns a BigInteger representing the product of this and N.·
BigInteger::mult(const BigInteger& N) const;


// Other Functions --------------------------------------------------------       -

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string·
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string();


// Overriden Operators ----------------------------------------------------       -
···
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.·
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::equals(B);
}

// operator<()
// Returns true if and only if A is less than B.·
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A < B) {
        return true;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B.·
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A <= B) {
        return true;
    }
}

// operator>()
// Returns true if and only if A is greater than B.·
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A > B) {
        return true;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.·
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A >= B) {
        return true;
    }
}

// operator+()
// Returns the sum A+B.·
BigInteger& BigInteger::operator+( const BigInteger& A, const BigInteger& B ) {
    return (add(&A) + add(&B));
}
// operator+=()
// Overwrites A with the sum A+B.·
BigInteger& BigInteger::operator+=( BigInteger& A, const BigInteger& B );

// operator-()
// Returns the difference A-B.·
BigInteger& BigInteger::operator-( const BigInteger& A, const BigInteger& B );
    return (sub(&A) + sub(&B));
// operator-=()
// Overwrites A with the difference A-B.·
BigInteger& BigInteger::operator-=( BigInteger& A, const BigInteger& B );

// operator*()
// Returns the product A*B.·
BigInteger& BigInteger::operator*( const BigInteger& A, const BigInteger& B );
    return (mult(&A) + mult(&B));
// operator*=()
// Overwrites A with the product A*B.·
BigInteger& BigInteger::operator*=( BigInteger& A, const BigInteger& B );

