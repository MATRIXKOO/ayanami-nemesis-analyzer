
void test(){
	float x=0.12, y=12;

	while(x==(x*y-0.1)) //expected warning for float loop counter
		break;	
}
