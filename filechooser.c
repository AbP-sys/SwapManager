struct cb_data
{
    GtkWidget* window;
    GtkEntryBuffer *loc_buffer;
    struct apply_changes_args *apply;
}*cb_data;

static void set_location(GtkWidget* button, gpointer args)
{
    GtkWidget *dialog;
    struct cb_data *passed = args;
    dialog = gtk_file_chooser_dialog_new("Chosse a file", GTK_WINDOW(passed->window), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,"Open",GTK_RESPONSE_OK, NULL);
    gtk_widget_show_all(dialog);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),"/");
    //gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        char *new_loc = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_entry_buffer_set_text(passed->loc_buffer,new_loc,sizeof(new_loc));
        passed->apply->location = new_loc;
    }
    else
        g_print("You pressed Cancel\n");
    gtk_widget_destroy(dialog);  
}
