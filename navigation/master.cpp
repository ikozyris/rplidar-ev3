#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdbool>
#include <cstdint>

#include "lidar-utils.cpp"
#include <gtk/gtk.h>

#define PI	3.141592653589793	  // I only remeber 15 decimal points :)
#define p 	0.0174532925199432958 // π / 180

uint8_t image_data[700 * 700 * 3 + 5];
bool scan = false;

int create_image2()
{
    sl_lidar_response_measurement_node_hq_t nodes[8192];
    // fetch result and print it out...
    size_t count = _countof(nodes);    
    op_result = drv->grabScanDataHq(nodes, count);    
    drv->ascendScanData(nodes, count);

    memset(image_data, 255, 700 * 700 * 3);
    int AB, OA;
    float OB;
    float a; // in radians

    for (size_t i = count; i != 0; --i) {
    	if (nodes[i].quality == 0 || (nodes[i].dist_mm_q2) > 7000)
			continue;
        OB = (nodes[i].dist_mm_q2 / 4.0f) / 5.0f;
        //printf("++++++a=%lf OB=%lf\n", a, OB);
        a = ((nodes[i].angle_z_q14 * 90.f) / 16384.f) * p; //find a in radians
        //printf("a in rad=%f\n",aa);
        AB = sin(a) * OB;
        OA = cos(a) * OB;
        // printf("OA=%d AB=%d\n", OA, AB);
        image_data[((AB + 350) * 700 + OA + 350) * 3]     = 0; // R
        image_data[((AB + 350) * 700 + OA + 350) * 3 + 1] = 0; // G
        image_data[((AB + 350) * 700 + OA + 350) * 3 + 2] = 0; // B
    }

    return 0;
}

inline void start_scan() { drv->startScanExpress(0, SL_LIDAR_CONF_SCAN_COMMAND_BOOST); scan = true; }
inline void stop_scan()  { scan = false; drv->stop();}
inline void disconnect() { scan = false; _disconnect(); }

static gboolean on_timeout(gpointer user_data)
{
    if (scan) {
        create_image2();
        GtkImage *image = GTK_IMAGE(user_data);
        GdkPixbuf *pixbuf;
        pixbuf = gdk_pixbuf_new_from_data(image_data, GDK_COLORSPACE_RGB, false, 8, 700, 700, 700 * 3,
                                           (GdkPixbufDestroyNotify)g_free, (gpointer)g_free);
        gtk_image_set_from_pixbuf(image, pixbuf);
    }
	return G_SOURCE_CONTINUE; // G_SOURCE_REMOVE when you want to stop
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *window, *grid, *button;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// Here we construct the container that is going pack our buttons
	grid = gtk_grid_new();

	// Pack the container in the window
	gtk_container_add(GTK_CONTAINER(window), grid);

	button = gtk_button_new_with_label("Connect");
	g_signal_connect(button, "clicked", G_CALLBACK(connect), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

	button = gtk_button_new_with_label("Start Scanning");
	g_signal_connect(button, "clicked", G_CALLBACK(start_scan), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

	button = gtk_button_new_with_label("Stop Scanning");
	g_signal_connect(button, "clicked", G_CALLBACK(stop_scan), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);

	button = gtk_button_new_with_label("Disconnect");
	g_signal_connect(button, "clicked", G_CALLBACK(disconnect), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 3, 0, 1, 1);

	GtkWidget *image;
    GdkPixbuf *pixbuf;
    pixbuf = gdk_pixbuf_new_from_data(image_data, GDK_COLORSPACE_RGB, false, 8, 700, 700, 700 * 3, 
                                      (GdkPixbufDestroyNotify)g_free, (gpointer)g_free);
    image = gtk_image_new_from_pixbuf(pixbuf);

	gtk_grid_attach(GTK_GRID(grid), image, 0, 1, 4, 1);


  	// create a new window, and set its title
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_timeout_add(333 /* milliseconds */, on_timeout, image);
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
