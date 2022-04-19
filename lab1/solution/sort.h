#include "vector.h"

template <typename U> 
TVector<U> CountingSort(const TVector<U> &unsortedVector, unsigned int max) {
	TVector<unsigned int> count{max + 1};
	for (unsigned int i = 0; i <= max; i++) {
		count[i] = 0;
	}
	for (unsigned int i = 0; i < unsortedVector.Size(); ++i) {
		++count[unsortedVector[i].key];
	}
	for (unsigned int i = 1; i <= max; i++) {
		count[i] += count[i-1];
	}
	TVector<U> result{unsortedVector.Size()};
	for (int i = unsortedVector.Size() - 1; i >= 0; i--) {
		result[--count[unsortedVector[i].key]] = unsortedVector[i];
	}

	return result;
}