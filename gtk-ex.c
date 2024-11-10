// gtk example
// compile with:
// gcc -o gtk-ex gtk-ex.c `pkg-config --cflags --libs gtk+-3.0`

#include <gtk/gtk.h>

void on_new_item_activate(GtkWidget *widget, gpointer data) {
    g_print("New File activated\n");
}

void on_open_item_activate(GtkWidget *widget, gpointer data) {
    g_print("Open File activated\n");
}

void on_quit_item_activate(GtkWidget *widget, gpointer data) {
    gtk_main_quit(); // Quit the application
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Application with Menubar");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container to hold the menubar and content
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a menubar
    GtkWidget *menubar = gtk_menu_bar_new();

    // Create "File" menu and items
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);

    GtkWidget *new_item = gtk_menu_item_new_with_label("New");
    g_signal_connect(new_item, "activate", G_CALLBACK(on_new_item_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);

    GtkWidget *open_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open_item, "activate", G_CALLBACK(on_open_item_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);

    GtkWidget *quit_item = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(quit_item, "activate", G_CALLBACK(on_quit_item_activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);

    // Add "File" menu to the menubar
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);

    // Create "Edit" menu and items
    GtkWidget *edit_menu = gtk_menu_new();
    GtkWidget *edit_item = gtk_menu_item_new_with_label("Edit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_item), edit_menu);

    GtkWidget *cut_item = gtk_menu_item_new_with_label("Cut");
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), cut_item);

    GtkWidget *copy_item = gtk_menu_item_new_with_label("Copy");
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), copy_item);

    GtkWidget *paste_item = gtk_menu_item_new_with_label("Paste");
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), paste_item);

    // Add "Edit" menu to the menubar
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_item);

    // Add menubar to the vertical box container
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the main GTK loop
    gtk_main();

    return 0;
}

