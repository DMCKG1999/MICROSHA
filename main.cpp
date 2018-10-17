#include <stdio.h>
#include <unistd.h>

// Name = print current directory name
void pcdn (bool pr);

int main (int argc, char **argv, char **envp) {

    pcdn(true);


    printf ("\n");
    return 0;
}

// Name = print current directory name
void pcdn (bool pr) {
    printf ("%s%c ", get_current_dir_name (), (pr)? '!' : '>');
}
