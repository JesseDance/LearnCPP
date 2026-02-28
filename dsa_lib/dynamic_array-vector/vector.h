#include <iostream>
#include <memory>		//std::allocator
#include <new>			//Placement New
#include <stdexcept>
#include <utility>		//std::move

template <typename T>
class Vector {
private:
	T* data;		//pointer to first element
	size_t m_size;	//elements currently constructed
	size_t m_capacity; //total slots allocated in raw memory

	//buffer grows
	void reallocate(size_t new_capacity) {
		//allocate new block of memory
		//cast to T* since ::operator returns void*
		//quantity * sizeof(T) gives total bytes needed
		T* new_block = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

		//move elements to new block
		//move up to m_size (not m_capacity)
		for(size_t i = 0; i < m_size; i++) {
			//PLACEMENT NEW + STD::MOVE
			//construct a T at address &new_block[i] using the data moved from data[i]
			new (&new_block[i]) T(std::move(data[i]));
		}

		for(size_t i = 0; i < m_size; ++i) {
			data[i].~T();
		}

		//free the old raw memory
		//use ::operator delete since ::operator new used
		::operator delete(data);

		//update pointers
		data = new_block;
		m_capacity = new_capacity;

	}

public:
	Vector() : data(nullptr), m_size(0), m_capacity(0) {}

	//copy constructor
	Vector(const Vector& other) 
		: m_size(other.m_size), m_capacity(other.m_capacity)
	{
		//allocate raw memory
		data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));

		//copy constructed elements from other into new memory
		for(size_t i = 0; i < m_size; ++i) {
			//other.data[i] as blueprint
			new (&data[i]) T(other.data[i]);
		}
	}

	//copy assignment (copy and swap)
	Vector& operator=(const Vector& other) {
		//check for self assignment v=v
		if (this == &other) return *this;

		//create copy (allocate new memory, copy data)
		Vector temp(other);

		//swap pointers with temp
		//steal temp new memory, temp gets old memory
		std::swap(data, temp.data);
		std::swap(m_size, temp.m_size);
		std::swap(m_capacity, temp.m_capacity);

		return *this;

		//end of scope: 'this' destroyed
		//old memory is freed here
	}

	//move constructor
	//noexcept allows stl containers to trust the class
	Vector(Vector&& other) noexcept
		: data(other.data), m_size(other.m_size), m_capacity(other.m_capacity)
	{
		//already got initializer list data

		//leave 'other' vector in a valid empty state
		//if this step is missing, other's destructor will free the memory that was taken
		other.data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	//move assignment
	Vector& operator=(Vector&& other) noexcept {
		//check for self reference to move
		if (this == &other) return *this;

		//clean up current memory (since memory being replaced)
		for(size_t i = 0; i < m_size; ++i) data[i].~T();
		::operator delete(data);

		//steal resources
		data = other.data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		//nullify other's data
		other.data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		return *this;
	}

	~Vector() {
		//destroy all live objects
		for(size_t i = 0; i < m_size; ++i) {
			data[i].~T();
		}

		//free raw memory
		::operator delete(data);
	}

	//operator [] unsafe but fast
	T& operator[](size_t index) {return data[index];}
	const T& operator[](size_t index) const {return data[index];}

	//at() with safe bounds checking
	T& at(size_t index) {
		if(index >= m_size) throw std::out_of_range("Vector index out of bounds");
		return data[index];
	}

	//iterators (enables for (auto& x : vector))
	T* begin() {return data;}
	T* end() {return data + m_size;}

	//const iterators for read only vectors
	const T* begin() const {return data;}
	const T* end() const {return data + m_size;}

	void push_back(const T& value) {
		//if full, grow
		//standard growth is double capacity
		if(m_size >= m_capacity) {
			size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
			reallocate(new_cap);
		}

		//placement new
		//cosntruct new element at specific address data+m_size
		new (&data[m_size]) T(value);

		m_size++;
	}

	//push back with move semantics (rvalue)
	void push_back(T&& value) {
		if(m_size >= m_capacity) {
			size_t new_cap = (m_capacity == 0) ? 1 : m_capacity * 2;
			reallocate(new_cap);
		}

		new(&data[m_size]) T(std::move(value));
		m_size++;
	}

};