float f(){
	float x = 1.3f;
	return x;
}

void test(){
	float x=0.1f;
	do{
		x++;
	}
	while(x <= f()); //expected warning for float loop counter
}
