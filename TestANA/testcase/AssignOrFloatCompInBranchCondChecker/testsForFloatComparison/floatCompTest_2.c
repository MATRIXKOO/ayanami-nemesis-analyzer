
void test(){
	float x=1, y=2, z=3;
	do{
		x++;
	}
	while(x<=(z=y)); //expected warning for float loop counter
}
