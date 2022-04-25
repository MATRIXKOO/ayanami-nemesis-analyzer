
void test(){
	float x=12, y=0.12;

	while(x>(x*y-0.1)) //no warning expected
		break;	
}

