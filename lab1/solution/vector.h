#include <iostream>

template <typename T> 
class TVector {
public:
	using TValueType = T;
	using TIterator = TValueType *;
	TVector();
	TVector(unsigned int size);
	unsigned int Size() const;
	bool Empty() const;
	TIterator Begin() const;
	TIterator End() const;

	template <typename U> 
    friend void VecSwap(TVector<U>& first, TVector<U>& second);

	TVector& operator=(TVector other);
	~TVector();
	TValueType& operator[](int index) const;
	void PushBack(TValueType& value);

	template <typename U> 
    friend TVector<U> CountingSort(const TVector<U>& unsortedVector, unsigned int max);

private:
	int storageSize;
	int capacity;
	TValueType *storage;
};

template <typename T> 
TVector<T>::TVector() {
	storageSize = capacity = 0;
	storage = nullptr;
}

template <typename T> 
TVector<T>::TVector(unsigned int size) : TVector() {
    if (size < 0) {
        throw "Incorrect size";
    }

	if (size == 0) {
		return;
    }

	storageSize = capacity = size;
	storage = new typename TVector<T>::TValueType[size];
}

template <typename T> 
unsigned int TVector<T>::Size() const {
	return capacity;
}

template <typename T> 
bool TVector<T>::Empty() const {
	return Size() == 0;
}

template <typename T> typename 
TVector<T>::TIterator TVector<T>::Begin() const {
	return storage;
}

template <typename T> typename 
TVector<T>::TIterator TVector<T>::End() const {
	if (storage) 
		return storage + capacity;
	
	return nullptr;
}

template <typename U> 
void VecSwap(TVector<U>& first, TVector<U>& second) {
	using std::swap;

	swap(first.capacity, second.capacity);
	swap(first.storageSize, second.storageSize);
	swap(first.storage, second.storage);
}

template <typename T> 
TVector<T>& TVector<T>::operator=(TVector<T> other) {
	VecSwap(*this, other);
	return *this;
}

template <typename T> 
TVector<T>::~TVector() {
	storageSize = 0;
    capacity = 0;
	delete[] storage;
	storage = nullptr;
}

template <typename T> typename 
TVector<T>::TValueType &TVector<T>::operator[](int index) const {
	if (index < 0 || index > capacity) {
        throw "Incorrect index";
	}

	return storage[index];
}

template <typename T> 
void TVector<T>::PushBack(TValueType &value) {
	if (capacity < storageSize) {
		storage[capacity] = value;
		++capacity;
		return;
	}

	unsigned int next_size = 1;
	if (storage) {
		next_size = storageSize * 2;
	}

	TVector<T> next{next_size};
	next.capacity = capacity;

	if (storage) {
		std::copy(storage, storage + storageSize, next.storage);
	}
	next.PushBack(value);
	VecSwap(*this, next);
}

template <typename T> 
std::ostream& operator<<(std::ostream& output, TVector<T>& elem) {
    for (unsigned int i = 0; i < elem.Size(); ++i) {
        output << elem[i] << '\n';
    }
    return output;
}
