

void test() {
	int x=1, y=2, z=3, w=4;

	while(x=1, y=(w-z), y, z=5) //expected warning for assign in controlling stmt
		break;
}
