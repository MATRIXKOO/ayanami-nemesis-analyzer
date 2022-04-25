
void test(){
	float x = 0.1f;
	float y = 3.4f;
	if(x <= y)
		return; //expected warning for float comparison
}
