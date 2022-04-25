
void testFor(){
	int x=1, y=1, z=1;

	for(x=1; x<15, y<12, z=3; x++) //expected warning for assign in controlling stmt
		return;
}

