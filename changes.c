#include<unistd.h>
#include<stdlib.h>

struct apply_changes_args
{
    double size;
    char *location;
}*create_swap;

void apply(GtkWidget* widget, gpointer data){
    // callback function to apply changes
    int fp = 0;
    struct apply_changes_args *passed = data;
    int status;
    fp = system("pkexec bash /bin/mkswap.sh");
    if (fp == -1)
        printf("errored");
    else
    {
        //
    }
}

void discard(GtkWidget* widget, gpointer data){
    // callback function to discard changes
    g_print("Changes discarded\n");
}