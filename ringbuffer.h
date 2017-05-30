#pragma once

#define ringbuffer_size 5000

typedef struct ringbuffer_datatype {
	char buffer[ringbuffer_size];
	int ringbuffer_byte_available;
	int ringbuffer_position;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t *ringbuffer);

void ringbuffer_queue(ringbuffer_t *ringbuffer, char *data, int size);

void ringbuffer_retrieve(ringbuffer_t *ringbuffer, char *data, int size);

int ringbuffer_free_size(ringbuffer_t *ringbuffer);

int ringbuffer_available_size(ringbuffer_t *ringbuffer);
