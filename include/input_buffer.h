#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#define INPUT_BUFFER_SIZE 256

// Push a character into the input buffer
void input_put(char c);

// Get one character, non-blocking
int getc_nonblock(void);

// Read an entire line (blocking)
int readline(char *out, int max);

#endif
