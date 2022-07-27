#include<unistd.h>
#include<stdlib.h>

struct apply_changes_args
{
    double size;
    char *location;
}*create_swap;

void apply(GtkWidget* widget, gpointer scale){
    // callback function to apply changes
    int fp = 0;
    create_swap->size = gtk_range_get_value((GtkRange *)scale);
    if(fork() == 0)
    {
        char numstring[3];
        snprintf(numstring, 5, "%d", (int)create_swap->size);
        fp = execlp("bash","bash","/bin/mkswap.sh",
        numstring,create_swap->location,NULL);
        if (fp == -1){
            printf("errored %s",strerror(errno));
        }
        else{
            printf("Changes applied successfully");
        }
    }
        

}

void discard(GtkWidget* widget, gpointer data){
    // callback function to discard changes
    g_print("Changes discarded\n");
}