all: ex1 ex2 ex3 ex4 ex5
ex1 : in-h.dot
	sed 's/, color="red"//' in-h.dot > ex1.dot
	dot ex1.dot -Tpng > ex1.png
ex2: in-h.dot
	sed 's/\\n.*\"/\"/' in-h.dot > ex2.dot
	dot ex2.dot -Tpng > ex2.png
ex3 : in-cpp.dot
	sed 's/, color="red"//' in-cpp.dot > ex3.dot
	dot ex3.dot -Tpng > ex3.png
ex4: in-h.dot
	dot in-h.dot -Tpng > ex4.png
ex5: in-cpp.dot
	dot in-cpp.dot -Tpng > ex5.png
