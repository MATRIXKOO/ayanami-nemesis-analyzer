
void test(){
	float x = 0.1;

	if(x<3, x=(2>3)) //expected warning for assign in controlling stmt
		return;
}
