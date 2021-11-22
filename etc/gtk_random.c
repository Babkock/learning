#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// variables for get_random
int number;
char tmp[15];

static void get_random(GtkWidget *w, GtkLabel *l) {
	// get random number, put it in a string
	srand(time(NULL));
	number = (rand() % 100);
	bzero(tmp, sizeof(tmp));
	sprintf(tmp, "Random number is %d", number);
	// send string to label
	gtk_label_set_text(l, tmp);
}

int main(int argc, char *argv[]) {
	GtkWidget *window, *vbox, *label, *button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// window size, I think
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	// assign label and button
	label = gtk_label_new("Random number is 0");
	button = gtk_button_new_with_label("Randomize");
	vbox = gtk_vbox_new(FALSE, 5);

	// put label and button into vbox
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
	
	// put vbox into window
	gtk_container_add(GTK_CONTAINER(window), vbox);

	// check to see if user stopped program or clicked button
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(button, "clicked", G_CALLBACK(get_random), label);

	// output window
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
