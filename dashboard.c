#include <gtk/gtk.h>
#include"getinfo.c"
#include"changes.c"
#include"filechooser.c"
#include<math.h>
#define WINDOW_SIZE 200
 
void welcome(GtkWidget*, gpointer);
void destroy(GtkWidget*, gpointer);
void set_location(GtkWidget*,gpointer);

GtkWidget* create_label(char* mnemonic,int col,int row,int scolm,int srow,GtkWidget* grid,int align)
{
    GtkWidget *label = gtk_label_new_with_mnemonic (mnemonic);
    gtk_grid_attach (GTK_GRID (grid), label, col, row, scolm, srow);
    gtk_label_set_xalign ((GtkLabel *)label,align);
    return label;
}
 
int main(int argc, char* argv[]){
    GtkWidget* window;
    GtkWidget *grid;
    GtkWidget* button;
    GtkWidget* button1;
    GtkWidget* button2;
    GtkWidget *scale;
    GtkEntryBuffer *loc_buffer;
    GtkStyleContext *context;                                                                       
    GtkCssProvider *provider;

    struct memory current_swap;
    get_current_swap(&current_swap);

    struct memory system_memory;
    get_system_memory(&system_memory);
 
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), WINDOW_SIZE);
    
    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);
    //gtk_grid_set_row_homogeneous(GTK_GRID(grid),TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
 
    scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 4); 
    gtk_widget_set_size_request(scale,300,40);
    gtk_range_set_value((GtkRange*) scale,current_swap.value);                     
    gtk_grid_attach (GTK_GRID (grid), scale, 0, 0, 4, 1);

    provider = gtk_css_provider_new();                                                              
    gtk_css_provider_load_from_path(provider, "/etc/SwapManager/mystyles.css", NULL);                                 
    context = gtk_widget_get_style_context(GTK_WIDGET(window));                                     
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    context = gtk_widget_get_style_context(GTK_WIDGET(scale));                                      
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    create_label("Recommended: ",1,1,1,1,grid,1);
    
    char recom_size[5]; 
    sprintf(recom_size,"%.2f",ceil(sqrt(system_memory.value)));
    recom_size[4] = system_memory.suffix;
    create_label(recom_size,2,1,1,1,grid,1);

    create_label("location: ",0,2,1,1,grid,1); 
    
    loc_buffer = gtk_entry_buffer_new ("/swapfile",9);
    button2 = gtk_entry_new_with_buffer(loc_buffer);
    gtk_grid_attach (GTK_GRID (grid), button2, 1, 2, 2, 1);
   
    GtkWidget* open = gtk_button_new_from_icon_name ("document-open",GTK_ICON_SIZE_BUTTON);
    cb_data = g_new0(struct cb_data, 1);    //store arguments in a struct for passing into the callback function
    create_swap = g_new0(struct apply_changes_args, 1);
    cb_data->window = window;
    cb_data->loc_buffer = loc_buffer;
    cb_data->apply = create_swap;
    g_signal_connect(G_OBJECT(open), "clicked", G_CALLBACK(set_location),cb_data);
    gtk_grid_attach (GTK_GRID (grid), open, 3, 2, 1, 1);  

    button1 = gtk_button_new_with_label("Discard changes");
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(welcome), "button");
    gtk_grid_attach (GTK_GRID (grid), button1, 2, 3, 1, 1);  

    button = gtk_button_new_with_label("Apply changes");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(apply), scale);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 3, 1, 1); 
 
    gtk_widget_show_all(window);
    gtk_main();
 
    return 0;
}

void welcome(GtkWidget* widget, gpointer data){
    // printf equivalent in GTK+
    g_print("Changes applied successfully\n");
    //g_print("%s Clicked %d times\n", (char*)data, ++COUNT);
}
 
void destroy(GtkWidget* widget, gpointer data){
    gtk_main_quit();
}