
void test(){
	int x = 1;

	while(x,(x=1)) //no warning expected
		break;
}

