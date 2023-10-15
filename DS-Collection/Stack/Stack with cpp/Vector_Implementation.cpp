#include <iostream>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <algorithm>
using namespace std;

template <class T>
class Vec{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	
	Vec() { create(); }
	explicit Vec(size_type n, const T& data) { create(n, data); }
	Vec(const Vec& v) { create(v.begin(), v.end()); }
	~Vec() { uncreate(); }
	
	Vec& operator=(const Vec& rhs){
		if( &rhs != this){
			uncreate();
			create(rhs.begin(), rhs.end());
		}
		
		return *this;
	}
	
	void push(const T& data){
		if( avail == limit ) grow();
		unchecked_append(data);
	}
	
	void pop(){
		if( empty() ) return;
		iterator temp = avail--;
		alloc.destroy(temp);
	}
	
	bool empty() const { return data == limit == avail; }
	size_type size() const { return avail-data; }
	
	iterator begin() { return data; }
	const_iterator begin() const { return data; }
	iterator end() { return avail; }
	const_iterator end() const { return avail; }
	
private:
	iterator data;
	iterator avail;
	iterator limit;
	
	allocator<T> alloc;
	
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	
	void uncreate();
	
	void grow();
	void unchecked_append(const T&);
};

int main(int argc, char *argv[]) {
	
}

