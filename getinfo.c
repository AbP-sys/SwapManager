#include<ctype.h>
struct memory
{
    double value;
    char suffix;
};
char get_suffix(char *path)
{
    //suffix
    return path[strlen(path)-2]; 
}

double get_prefix(char *path)
{
    char num[8];
    int i = 0;
    while(isdigit(path[i]))
    {
        num[i] = path[i];
        i++;
    }
    return atoi(num);  
}

void get_current_swap(struct memory *current)
{
    /* Handle error */
    FILE *fp;
    int status;
    char path[PATH_MAX];
    fp = popen("swapon | tail -n +2 | awk '{print $3}'","r");
    if (fp == NULL);
    else
    {
        fgets(path,PATH_MAX,fp);
        current->suffix = get_suffix(path);
        current->value = get_prefix(path);
        status = pclose(fp);
    }
    
}

void get_system_memory(struct memory *current)
{
    /* Handle error */
    FILE *fp;
    int status;
    char path[PATH_MAX];
    fp = popen("free -m | awk 'NR==2{print}' | awk '{print $2}'","r");
    if (fp == NULL);
    else
    {
        fgets(path,PATH_MAX,fp);
        current->suffix = 'G';
        current->value = (double) get_prefix(path)/1024.0;
        status = pclose(fp);
    }
    
}
