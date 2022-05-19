/* XCB events
 * May 19, 2022
 * Compile with -lxcb */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xcb/xcb.h>

void print_modifiers(uint32_t mask) {
	const char **mod, *mods[] = {
		"Shift", "Lock", "Ctrl", "Alt",
		"Mod2", "Mod3", "Mod4", "Mod5",
		"Button1", "Button2", "Button3", "Button4", "Button5"
	};
	printf("Modifier mask: ");
	for (mod = mods; mask; mask >>= 1, mod++) {
		if (mask & 1)
			printf(*mod);
	}
	putchar('\n');
}

int main(void) {
	xcb_connection_t *c;
	xcb_screen_t *screen;
	xcb_window_t win;
	xcb_generic_event_t *e;
	uint32_t mask = 0;
	uint32_t values[2];

	/* connect to X server */
	c = xcb_connect(NULL, NULL);

	/* get the first screen */
	screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;

	/* ask for window's id */
	win = xcb_generate_id(c);

	/* create the window */
	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = screen->white_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS |
		XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
		XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
		XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;
	xcb_create_window(c,			// connection
		0,							// depth
		win,						// window id
		screen->root,				// parent window
		0, 0,						// x, y
		200, 200,					// width, height
		10,							// border width
		XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
		screen->root_visual,		// visual
		mask, values				// masks
	);

	/* map the window */
	xcb_map_window(c, win);

	xcb_flush(c);

	bool skip = false;
	while ((e = xcb_wait_for_event(c))) {
		if (!skip)
			skip = true;
		else {
			skip = false;
			continue;
		}
		switch (e->response_type & ~0x80) {
			case XCB_EXPOSE: {
				xcb_expose_event_t *ev = (xcb_expose_event_t *)e;
				printf("Window %ld exposed. Region to be redrawn at location (%d,%d)\n", ev->window, ev->x, ev->y);
				printf("with dimensions %d x %d\n", ev->width, ev->height);
				break;
			}
			case XCB_BUTTON_PRESS: {
				xcb_button_press_event_t *ev = (xcb_button_press_event_t *)e;
				print_modifiers(ev->state);

				switch (ev->detail) {
					case 4:
						printf("Wheel button up in window %ld, at coords (%d,%d)\n", ev->event, ev->event_x, ev->event_y);
						break;
					case 5:
						printf("Wheel button down in window %ld, at coords (%d,%d)\n", ev->event, ev->event_x, ev->event_y);
						break;
					default:
						printf("Button %d pressed in window %ld, at coords (%d,%d)\n", ev->detail, ev->event, ev->event_x, ev->event_y);
						break;
				}
				break;
			}
			case XCB_BUTTON_RELEASE: {
				xcb_button_release_event_t *ev = (xcb_button_release_event_t *)e;
				print_modifiers(ev->state);

				printf("Button %d released in window %ld, at coords (%d,%d)\n", ev->detail, ev->event, ev->event_x, ev->event_y);
				break;
			}
			case XCB_MOTION_NOTIFY: {
				xcb_motion_notify_event_t *ev = (xcb_motion_notify_event_t *)e;

				printf("Mouse moved in window %ld, at coords (%d,%d)\n", ev->event, ev->event_x, ev->event_y);
				break;
			}
			case XCB_ENTER_NOTIFY: {
				xcb_enter_notify_event_t *ev = (xcb_enter_notify_event_t *)e;
				printf("Mouse entered window %ld, at coords (%d,%d)\n", ev->event, ev->event_x, ev->event_y);
				break;
			}
			case XCB_LEAVE_NOTIFY: {
				xcb_leave_notify_event_t *ev = (xcb_leave_notify_event_t *)e;
				printf("Mouse left window %ld, at coords (%d,%d)\n", ev->event, ev->event_x, ev->event_y);
				break;
			}
			case XCB_KEY_PRESS: {
				xcb_key_press_event_t *ev = (xcb_key_press_event_t *)e;
				print_modifiers(ev->state);
				printf("Key pressed in window %ld\n", ev->event);
				break;
			}
			case XCB_KEY_RELEASE: {
				xcb_key_release_event_t *ev = (xcb_key_release_event_t *)e;
				print_modifiers(ev->state);
				printf("Key released in window %ld\n", ev->event);
				break;
			}
			default:
				printf("Unknown event: %d\n", e->response_type);
				break;
		}

		/* free the generic event */
		free(e);
	}
	return 0;
}

