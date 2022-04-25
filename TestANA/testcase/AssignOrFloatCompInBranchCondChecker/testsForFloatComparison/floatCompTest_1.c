
void test(){
	float x=0.1;
	do{
		x++;
	}
	while(x<=1.0f); //expected warning for float loop counter
}
