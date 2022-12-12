void dummy(void) {
}

void main(void) {
	char *video_memory = (char *)0xb80a0;
	char *str = "Welcome to the kernel!";
	int x;
	
	/* prints the string in video memory, in alternating
	 * colors, directly below "Landed in 32-bit Protected Mode" */
	for (x = 0; x < 22; x++) {
		(*video_memory++) = str[x];
		if (x % 2 == 0)
			(*video_memory++) = 0x0a;
		else if (x % 3 == 0)
			(*video_memory++) = 0x0d;
		else
			(*video_memory++) = 0x0c;
	}
}

