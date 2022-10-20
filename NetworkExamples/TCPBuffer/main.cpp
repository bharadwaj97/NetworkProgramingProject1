#include<vector>
#include <iostream>
#include"Buffer.h"


int main(int argc, char** argv) {

	Buffer buffer(12);

	buffer.WriteInt32LE(50);

	buffer.WriteInt32LE(4, 500);

	int myReadValue50 = buffer.ReadUInt32LE();

	int myReadValue500 = buffer.ReadUInt32LE(4);

	printf("%d Buffer should be 50\n", myReadValue50);

	printf("%d Buffer should be 500\n", myReadValue500);


	int breakpoint = 1;

	return 0;



}
