/* X hello world by Tanner Babcock
 * October 16, 2010
 * cc prog.c -L/usr/X11/lib -lX11 */
#include <X11/Xlib.h>
#include <stdio.h>
 
int main(void) {
	Display *d = XOpenDisplay(NULL);
	Window w;
	XEvent e;
	int s;
	if (d == NULL) {
		fprintf(stderr, "ERROR: Cannot open display\n");
		return 1;
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 150, 30, 1, BlackPixel(d, s), WhitePixel(d, s));
	XStoreName(d, w, "hello");
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapWindow(d, w);
	while (1) {
		XNextEvent(d, &e);
		if (e.type == Expose) XDrawString(d, w, DefaultGC(d, s), 10, 20, "hello world", 11);
		if (e.type == KeyPress) break;
	}
	XCloseDisplay(d);
	return 0;
}
