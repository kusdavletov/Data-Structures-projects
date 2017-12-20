// CSE221 Assignment 2

# ifndef polynomial_h
# define polynomial_h

# include <typeinfo>
# include <iostream>
# include <cmath>

using namespace std;

// if (-EPS < x < EPS), we consider that (x == 0) is true
const double EPS = 1e-6;

// guaranties:
// 0) works for real-number types
// 1) everything inside [size, capacity) is 0
// 2) capacity doubles when reserved
template < class T >
class Polynomial
{
private:
    // _capacity is an actual array size
    // _size is a used size
    // *buffer is an array
    int _capacity, _size;
    T* buffer;
public:
    // just for convenience
    typedef T* Iterator;
    // empty constructor
    Polynomial () {
        _capacity = 0;
        _size = 0;
        buffer = 0;
    }
    // constructor with given size
    Polynomial (int size) {
        _capacity = size;
        _size = size;
        buffer = new T[_size];

        for (int i = 0; i < _size; ++i)
            buffer[i] = 0;
    }
    // constructor with given size and initial value
    Polynomial (int, const T& value) {
        _size = size;
        _capacity = size;
        buffer = new T [_size];

        for (int i = 0; i < _size; i++)
            buffer[i] = value;
    }
    // copy constructor
    Polynomial (const Polynomial < T >& source) {
        _size = source._size;
        _capacity = source._size;
        buffer = new T[_size];

        for (int i = 0; i < _size; ++i)
            buffer[i] = source.buffer[i];
    }
    // destructor
    ~Polynomial() {
        delete[] buffer;
    }
    // reservation of array capacity
    void reserve (int capacity) {
        // if array capacity is already bigger, end the function
        if (capacity <= _capacity) return;

        // otherwise double the capacity until it's sufficient
        int temp = max (1, _capacity);
        while (temp <= capacity)
            temp += temp;
        capacity = temp;

        // create a new array
        Iterator new_buffer = new T[capacity];

        // copy it
        for (int i = 0; i < _size; ++i)
            new_buffer[i] = buffer[i];

        // fill 0 to remaining spots
        for (int i = _size; i < capacity; ++i)
            new_buffer[i] = 0;

        // delete an old array
        delete[] buffer;

        // change old array to new one, increase the capacity
        buffer = new_buffer;
        _capacity = capacity;
    }
    // actual array resizing
    void resize (int value) {
        // first reserve
        reserve (value);
        // if array size was decreased, set the cut part to zero
        for (int i = value; i < _size; ++i)
            buffer[i] = 0;
        _size = value;
    }
    // almost same as copy constructor
    Polynomial<T>& operator = (const Polynomial<T>& source) {
        delete[] buffer;

        _size = source._size;
        _capacity = source._size;
        buffer = new T [_size];

        for (int i = 0; i < _size; i++)
            buffer[i] = source.buffer[i];

        return *this;
    }
    // array access operator
    T& operator [] (int index) {
        // if the element requested doesn't exist, reserve it
        if (index >= _size) reserve (index + 1);
        return buffer[index];
    }
    // get the capacity
    int capacity () const {
        return _capacity;
    }
    // get the size
    int size () const {
        return _size;
    }
    // check if empty
    bool empty () const {
        return (_size == 0);
    }
    // pointer to the beginning
    Iterator begin () {
        return buffer;
    }
    // pointer to the end
    Iterator end () {
        return buffer + _size;
    }
    // first element
    T& front () {
        return buffer[0];
    }
    // last element
    T& back () {
        return buffer[_size - 1];
    }
    // add an element to the end
    void push_back (const T& value) {
        reserve (_size + 1);
        buffer[_size++] = value;
    }
    // erase the last element
    void pop_back () {
        buffer[--_size] = 0;
    }
	// Sum of *this and source polynomials
	Polynomial operator + (const Polynomial& source);
	// Subtract of source polynomials from *this
	Polynomial operator - (const Polynomial& source);
	// Product of *this and source polynomials
	Polynomial operator * (const Polynomial& source);
	// Evaluate polynomial *this at x and return the result
	T Eval (T x);
	// Print polynomial
	void Print ();
	// Create a new term. If the term exists, overwrite its coefficient.
	void CreateTerm (const T coef, const int exp);
	// erase first zero-coefficient elements
	void normalize ();
};

//
// Implementation
//

template < typename T >
void Polynomial < T > :: Print ()
{
    if (_size == 0)
    {
        cout << "0\n";
        return;
    }
    for (int i = _size - 1; i >= 0; --i)
    if (buffer[i] > EPS || buffer[i] < -EPS)
    {
        if (buffer[i] > 0 && i < _size - 1) cout << '+';
        // uncomment  next line, if 1-valued coefficient shouldn't be printed
        //if (buffer[i] > 1 + EPS || buffer[i] < 1 - EPS)
        cout << buffer[i];
        if (i > 0) cout << 'x';
        // change 0 to 1 in the next line, if "x^1" should be printed as "x"
        if (i > 0) cout << '^' << i;
    }
    cout << "\n";
}

// Sum of *this and source polynomials
template < typename T >
Polynomial < T >
Polynomial < T > :: operator + (const Polynomial& source)
{
    Polynomial temp (max (_size, source._size));

    for (int i = source._size - 1; i >= 0; --i)
        temp[i] = buffer[i] + source.buffer[i];

    temp.normalize ();

    return temp;
}

// Difference of *this and source polynomials
template < typename T >
Polynomial < T >
Polynomial < T > :: operator - (const Polynomial& source)
{
    Polynomial temp (max (_size, source._size));

    for (int i = source._size - 1; i >= 0; --i)
        temp[i] = buffer[i] - source.buffer[i];

    temp.normalize ();

    return temp;
}

// Multiplication of *this and source polynomials
template < typename T >
Polynomial < T >
Polynomial < T > :: operator * (const Polynomial& source)
{
    Polynomial temp (_size + source._size);

    for (int i = _size - 1; i >= 0; --i)
        for (int j = source._size - 1; j >= 0; --j)
            temp[i + j] += buffer[i] * source.buffer[j];

    temp.normalize ();

    return temp;
}

// Polynomial evaluation
template < typename T >
T Polynomial < T > :: Eval (T x)
{
    double res = 0;
    for (int i = 0; i < _size; ++i)
        res += pow (double (x), double (i)) * buffer[i];
    return T (res);
}

// New term creation
template < typename T >
void Polynomial < T > :: CreateTerm (const T coef, const int exp)
{
    if (exp >= _size) resize (exp + 1);
    buffer[exp] = coef;
    normalize ();
}

// Erasing leading zero-valued coefficients
template < typename T >
void Polynomial < T > :: normalize ()
{
    while (back () < EPS && back () > -EPS) pop_back ();
}
#endif
