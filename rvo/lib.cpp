#include "lib.h"

C getTemporaryC() {
	return C();
}

C getLocalC() {
	C c;
	return c;
}

vector<C> getVectorOfC() {
	vector<C> v;
	v.push_back(C()); 
	return v;
}
