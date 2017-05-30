#include <stdio.h>

#include "ringbuffer.h"

void ringbuffer_init(ringbuffer_t *ringbuffer) {
	ringbuffer->ringbuffer_byte_available = 0;
	ringbuffer->ringbuffer_position = 4998;
}

void ringbuffer_queue(ringbuffer_t *ringbuffer, char *data, int size) {
	if (size > ringbuffer_free_size(ringbuffer)) {
		printf("No space in ringbuffer!! \n");
		return;
	}

	int i = 0;
	for (i = 0; i <= size-1; i++) {
		ringbuffer->buffer[ringbuffer->ringbuffer_position++] = data[i];

		if (ringbuffer->ringbuffer_position == ringbuffer_size) {
			ringbuffer->ringbuffer_position = 0;
		}
	}
	ringbuffer->ringbuffer_byte_available += size;
}

void ringbuffer_retrieve(ringbuffer_t *ringbuffer, char *data, int size) {
	if (size > ringbuffer_available_size(ringbuffer)) {
		printf("Not enough data in ringbuffer!! \n");
		return;
	}

	int i = 0;
	for (i = 0; i <= size-1; i++) {
		// Handle overflow
		if ((ringbuffer->ringbuffer_position - ringbuffer->ringbuffer_byte_available) > ringbuffer_size) {
			data[i] = ringbuffer->buffer[(ringbuffer->ringbuffer_position - ringbuffer->ringbuffer_byte_available) - ringbuffer_size];
		} else if ((ringbuffer->ringbuffer_position - ringbuffer->ringbuffer_byte_available) < 0) {
			data[i] = ringbuffer->buffer[(ringbuffer->ringbuffer_position - ringbuffer->ringbuffer_byte_available) + ringbuffer_size];
		}
		else {
			data[i] = ringbuffer->buffer[ringbuffer->ringbuffer_position - ringbuffer->ringbuffer_byte_available];
		}

		ringbuffer->ringbuffer_byte_available--;
	}
}

int ringbuffer_free_size(ringbuffer_t *ringbuffer) {
	return ringbuffer_size - ringbuffer->ringbuffer_byte_available;
}

int ringbuffer_available_size(ringbuffer_t *ringbuffer) {
	return ringbuffer->ringbuffer_byte_available;
}
