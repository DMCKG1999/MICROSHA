#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>

using std::string;
using std::list;
using std::vector;
using std::cin;
using std::cout;
using std::getline;
using std::size_t;

// Name = print current directory name
void pcdn (bool pr);
list<vector<string>*> *str_part (string str);

int main (int argc, char **argv, char **envp) {

    uid_t uid = getuid ();

    // Write invitation to input
    pcdn(uid == 0);

    // Read commands from imput
    string str;
    getline(cin, str);

    // Cut the string
    list<vector<string>*> * commands;
    commands = str_part (str);

    printf ("\n");
    return 0;
}

// Name = print current directory name
void pcdn (bool pr) {
    cout << get_current_dir_name () << ((pr)? '!' : '>');
}


list<vector<string>*> *str_part (string str) {
    //printf ("Open\n");
    list<vector<string>*> * l = new list<vector<string>*>;

    //int i = 0;
    bool not_exit = true;
    while (not_exit) {
        //printf ("%d ", i++);
        size_t num = str.find("|");
        if (num == string::npos) not_exit = false;

        l->push_back(new vector<string>);
        string sstr = "";
        while (str.length() > 0) {
             num = str.find(" ");
             if (num == string::npos && str.length() > 0) {
                 sstr = str;
                 str.clear();
             } else {
                 sstr = str.substr(0, num - 1);
                 str.erase(0, num);
             }
             l->back()->push_back(sstr);             
        }        
    }
    return l;
}
