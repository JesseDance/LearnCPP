#include <cstddef> 		// size_t
#include <utility>		//std::move, std::swap
#include <stdexcept>	//std::out_of_range
#include <initializer_list>	//{1,2,3} initialization

template <typename T>
class Vector {
private:
	//data members
	T* data;		//pointer to start of heap memory
	size_t size;	//number of elements currently stored
	size_t capacity;//total slots available in current allocated memory

	//helper to manage growth
	void reallocate(size_t new_capacity);

public:
	//constructors
	Vector();								//default
	Vector(size_t init_capacity);			//pre-allocate space
	Vector(std::initializer_list<T> init);	//v={1,2,3};

	//rule of five
	~Vector();								//destructor
	Vector(const Vector& other);			//copy constr
	Vector& operator=(const Vector& other);	//copy assignmnt
	Vector(Vector&& other) noexcept;		//Move constr
	Vector& operator=(Vector&& other) noexcept; //Move assingm

	//element access
	T& operator[](size_t index);			//fast unsafe access
	const T& operator[](size_t index) const; //read only access
	T& at(size_t index);					//slow safe access

	//modifiers
	void push_back(const T& value);			//add copy
	void push_back(T&& value);				//add via move
	void pop_back();						//remove last element

	//metadata
	size_t length() const {return size;}
	size_t cap() const {return capacity;}
	bool isEmpty() const {return size == 0;}


};