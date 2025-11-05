#include "Combinations.h"

Combination::Combination(Key k1, func c) {
	key1 = k1;
	callback = c;
}

Combination::Combination(Key k1, Key k2, func c) {
	key1 = k1;
	key2 = k2;
	callback = c;
}

Combination::Combination(Key k1, Key k2, Key k3, func c) {
	key1 = k1;
	key2 = k2;
	key3 = k3;
	callback = c;
}