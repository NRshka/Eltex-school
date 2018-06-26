int count_func = 1;
char head[1][4] = { "add" };
int count_operands[1] = { 2 };
char** names = (char**)head;

extern float add(float oper1, float oper2){
	return oper1 + oper2;
}
