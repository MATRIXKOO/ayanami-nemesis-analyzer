
void test(){
	int x=1, y=2, z=3;

	if(x==2, (y && x), z, z=3) //expected warning for assign in controlling stmt
		return;
}
