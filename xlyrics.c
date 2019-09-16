/* X print lyrics by Tanner Babcock
 * October 16, 2010
 * cc prog.c -L/usr/X11/lib -lX11 */
#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#define NEXTLINE x+=11
#define PRINTLINE XDrawString(d,w,DefaultGC(d,s),10,x,line,strlen(line))

int main() {
	Display *d = XOpenDisplay(NULL);
	Window w;
	XEvent e;
	int s, x = 10;
	char *line;
	if (d == NULL) {
		printf("ERROR: Cannot open display\n");
		return 1;
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 300, 705, 1, BlackPixel(d, s), WhitePixel(d, s));
	XStoreName(d, w, "lyrics");
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapWindow(d, w);
	while (1) {
		XNextEvent(d, &e);
		if (e.type == Expose) {
			line = "I got up feeling so down";
			PRINTLINE;
			NEXTLINE;
			line = "I got off being sold out";
			PRINTLINE;
			NEXTLINE;
			line = "I\'ve kept the movie rolling";
			PRINTLINE;
			NEXTLINE;
			line = "But the story\'s getting old now";
			PRINTLINE;
			NEXTLINE;
			line = "I just looked in the mirror";
			PRINTLINE;
			NEXTLINE;
			line = "Things aren\'t looking so good";
			PRINTLINE;
			NEXTLINE;
			line = "I\'m looking California";
			PRINTLINE;
			NEXTLINE;
			line = "And feeling Minnesota";
			PRINTLINE;
			NEXTLINE;
			line = "So now you know who gets mystified";
			PRINTLINE;
			NEXTLINE;
			line = "Show me the power child";
			PRINTLINE;
			NEXTLINE;
			line = "I\'d like to say";
			PRINTLINE;
			NEXTLINE;
			line = "That I\'m down on my knees today";
			PRINTLINE;
			NEXTLINE;
			line = "It gives me the butterflies";
			PRINTLINE;
			NEXTLINE;
			line = "Gives me away";
			PRINTLINE;
			NEXTLINE;
			line = "Till I\'m up on my feet again";
			PRINTLINE;
			NEXTLINE;
			line = "I'm feeling outshined";
			PRINTLINE;
			NEXTLINE;
			line = "Someone let the dogs out";
			PRINTLINE;
			NEXTLINE;
			line = "They\'ll show you where the truth is";
			PRINTLINE;
			NEXTLINE;
			line = "The grass is always greener";
			PRINTLINE;
			NEXTLINE;
			line = "Where the dogs are shedding";
			PRINTLINE;
			NEXTLINE;
			line = "I\'m feeling that I\'m sober";
			PRINTLINE;
			NEXTLINE;
			line = "Even though I\'m drinking";
			PRINTLINE;
			NEXTLINE;
			line = "I can\'t get any lower";
			PRINTLINE;
			NEXTLINE;
			line = "Still I feel I\'m sinking";
			PRINTLINE;
			NEXTLINE;
			line = "So now you know who gets mystified";
			PRINTLINE;
			NEXTLINE;
			line = "Show me the power child";
			PRINTLINE;
			NEXTLINE;
			line = "I\'d like to say";
			PRINTLINE;
			NEXTLINE;
			line = "That I\'m down on my knees today";
			PRINTLINE;
			NEXTLINE;
			line = "It gives me the butterflies";
			PRINTLINE;
			NEXTLINE;
			line = "Gives me away";
			PRINTLINE;
			NEXTLINE;
			line = "Till I\'m up on my feet again";
			PRINTLINE;
			NEXTLINE;
			line = "I'm feeling outshined";
			PRINTLINE;
			NEXTLINE;
		}
		if (e.type == KeyPress) break;
	}
	XCloseDisplay(d);
	return 0;
}
