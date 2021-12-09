/* X keypress by Tanner Babcock
 * October 16, 2010
 * cc prog.c -L/usr/X11/lib -lX11 */
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	Display *d = XOpenDisplay(NULL);
	Window w;
	XEvent e;
	int s;
	char *a, *b = "";
	if (d == NULL) {
		printf("ERROR: Cannot open display\n");
		return 1;
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 260, 50, 1, BlackPixel(d, s), WhitePixel(d, s));
	XStoreName(d, w, "keys");
	XSelectInput(d, w, ExposureMask | KeyPressMask | ButtonPressMask);
	XMapWindow(d, w);
	a = "Press an arrow key, or space bar to exit.";
	while (1)  {
		XNextEvent(d, &e);
		if (e.type == Expose) XDrawString(d, w, DefaultGC(d, s), 10, 20, a, strlen(a));
		if (e.type == KeyPress) {
			XClearWindow(d, w);
			XDrawString(d, w, DefaultGC(d, s), 10, 20, a, strlen(a));
			if (XLookupKeysym(&e.xkey, 0) == XK_Up) b = "You pressed up.";
			if (XLookupKeysym(&e.xkey, 0) == XK_Down) b = "You pressed down.";
			if (XLookupKeysym(&e.xkey, 0) == XK_Right) b = "You pressed right.";
			if (XLookupKeysym(&e.xkey, 0) == XK_Left) b = "You pressed left.";
			XDrawString(d, w, DefaultGC(d, s), 10, 40, b, strlen(b));
			if (XLookupKeysym(&e.xkey, 0) == XK_space) break;
		}
	}
	XCloseDisplay(d);
	return 0;
}
