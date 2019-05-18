//snippetysnip_begin:overloads
void f(unsigned int);
void f(int);
void f(char);
//snippetysnip_end
void f(unsigned int){}
void f(int){}
void f(char){}

int main() {
//snippetysnip_begin:call
char x = 1;
char y = 2;
f(x + y);
//snippetysnip_end
}
