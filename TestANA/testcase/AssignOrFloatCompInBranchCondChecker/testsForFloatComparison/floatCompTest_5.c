

void test(){
	float x;

	for (x = 0.1f; x < 4; x += 0.1f) //no warning expected
		break;
}
