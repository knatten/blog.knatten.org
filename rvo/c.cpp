#include "c.h"
extern int copies;
extern int ctors;

C::C() {
	++ctors;
}

C::C(const C&) {
	++copies;
}
