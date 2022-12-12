/* Xresource colors
 * May 24, 2022
 * Compile with -lX11 */
#include <X11/Xresource.h>
#include <string.h>
#include <stdio.h>

/* this program prints the 16 colors */
int main(void) {
	XrmDatabase db;
	XrmValue ret;
	Display *dpy;
	char *resource_manager;
	char *type, *val;
	char color[7];

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Could not open X display\n");
		return 1;
	}
	XrmInitialize();
	if ((resource_manager = XResourceManagerString(dpy)) == NULL) {
		return 2;
	}
	/* load the database */
	if (!(db = XrmGetStringDatabase(resource_manager))) {
		fprintf(stderr, "Could not load database\n");
		return 3;
	}
	for (int x = 0; x < 16; x++) {
		bzero(color, sizeof(color));
		sprintf(color, "color%d", x);
		
		XrmGetResource(db, color, "String", &type, &ret);
		if (ret.addr != NULL && !(strncmp("String", type, 64)))
			val = ret.addr;
		
		printf("%s = '%s'\n", color, val);
	}
	XCloseDisplay(dpy);

	return 0;
}

