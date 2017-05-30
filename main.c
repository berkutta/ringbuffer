#include <stdio.h>

#include "ringbuffer.h"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("./ringbuffer file1 file2 \n");
		return;
	}

	ringbuffer_t myringbuffer;

	ringbuffer_init(&myringbuffer);


	int c;
	FILE *file, *output;
	char mydata[1];

	file = fopen(argv[1], "rb");
	output = fopen(argv[2], "wb+");

	if (file) {
		char result;
		do {
			result = fread(mydata, 1, 1, file);
			ringbuffer_queue(&myringbuffer, &mydata, 1);

			if (ringbuffer_available_size(&myringbuffer) >= 200) {
				char buffer[200];
				ringbuffer_retrieve(&myringbuffer, &buffer, 200);
				fwrite(&buffer, 1, 200, output);
			}

		} while (result != 0);
		fclose(file);
		fclose(output);
	}

	printf("Finish! \n");

	getchar();
}
