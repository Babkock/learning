/* Xft/freetype example
 * May 24, 2022
 * Compile with -lX11 -lXft -lfreetype -I/usr/include/freetype2 */
#include <X11/Xft/Xft.h>
#include <stdio.h>

int main(void) {
	Display *dpy;
	int scr;
	Visual *visual;
	Colormap cmap;
	Window win;
	XftFont *font;
	const char *fontname = "Fura Code Nerd Font:size=14:antialias=true";
	const FcChar8 *msg = "Hello world\0";
	XftDraw *draw;
	XftColor color, color2, color3;

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Could not open X display\n");
		return 1;
	}
	scr = DefaultScreen(dpy);
	visual = DefaultVisual(dpy, scr);
	cmap = DefaultColormap(dpy, scr);

	win = XCreateSimpleWindow(dpy, RootWindow(dpy, scr), 100, 100, 200, 100, 1, WhitePixel(dpy, scr), BlackPixel(dpy, scr));
	XSelectInput(dpy, win, ExposureMask | KeyPressMask);
	XMapWindow(dpy, win);

	if (!(font = XftFontOpenName(dpy, scr, fontname))) {
		fprintf(stderr, "Could not load font %s\n", fontname);
		return 2;
	}
	if (!XftColorAllocName(dpy, visual, cmap, "#0000ee", &color)) {
		fprintf(stderr, "Could not allocate color\n");
		return 2;
	}
	if (!XftColorAllocName(dpy, visual, cmap, "#ee0000", &color2)) {
		fprintf(stderr, "Could not allocate color\n");
		return 2;
	}
	if (!XftColorAllocName(dpy, visual, cmap, "#00ee00", &color3)) {
		fprintf(stderr, "Could not allocate color\n");
		return 2;
	}
	draw = XftDrawCreate(dpy, win, visual, cmap);

	while (1) {
		XEvent ev;
		XNextEvent(dpy, &ev);
		if (ev.type == Expose) {
			XftDrawStringUtf8(draw, &color, font, 20, 20, msg, 11);
			XftDrawStringUtf8(draw, &color2, font, 20, 41, msg, 11);
			XftDrawStringUtf8(draw, &color3, font, 20, 62, msg, 11);
		}
		else if (ev.type == KeyPress)
			break;
	}
	
	XftColorFree(dpy, visual, cmap, &color);
	XftDrawDestroy(draw);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
	return 0;
}

