#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include <glob.h>

/*
using std::string;
using std::list;
using std::vector;
using std::cin;
using std::cout;
using std::getline;
using std::size_t;
*/
using namespace std;

class sm_str {
private:
	vector<string> split (string str, const char* d) {
		vector<string> ans; 
    	for (int i = 0; i < (int)str.length(); i++) {
			//for (int j = 0; j < ans.size(); j++)
			//	cout << i << " " << ans[j] << endl;
			for (int j = 0; d[j] != '\0'; j++) {        
	    		if (str[i] == d[j]) {
	     		    if (i != 0) {
						ans.push_back(str.substr(0, i));
					}
		    	
					str.erase(0, i+1);
					i = -1;
				    break;
	  		    }
			}
    	}
    	if ((int)str.length() != 0) ans.push_back(str);
    	return ans;
	}

	/*list<vector<string>> *str_part (string str) {
    	//printf ("Open\n");
	    list<vector<string>> * l = new list<vector<string>>;

	    int i = 0;
	    bool not_exit = true;
	    //printf ("S_open\n");
	    while (not_exit) {
	        printf ("%d %d\n", i++, not_exit);
	        size_t num = str.find("|");
	        if (num == string::npos) not_exit = false;
	
	        l->push_back(vector<string>());
	        string sstr = "";
	        while (str.length() > 0) {
	            num = str.find(" ");
	            if()	    
	
	            if (num == string::npos && str.length() > 0) {
	                sstr = str;
	                str.clear();
	            } else {
	                sstr = str.substr(0, num);
	                str.erase(0, num + 1);
	            }
		    std::cout << "sstr=" << sstr << "num=" << num << std::endl;
	            l->back().push_back(sstr);
	  //      printf ("%d %d\n", i++, not_exit);             
	        }        
	    //    printf ("%d %d\n", i++, not_exit);
	    }
	      //  printf ("%d %d\n", i++, not_exit);
	    return l;
	}*/

	void pcdn (bool pr) {
    	cout << get_current_dir_name () << ((pr)? '!' : '>');
	}

public:
	vector<string> commands;

	sm_str () {
		pcdn(getuid() == 0);
		string str;		
		getline(cin, str);
		commands = split(str, "|");	
	}

	bool run (){
		for (auto &com : commands) {
			vector<string> com_pat = split (com, " \t");

			glob_t globbuf;	
					
			for (globbuf.gl_offs = 0; globbuf.gl_offs < com_pat.size(); globbuf.gl_offs++){
				if (com_pat[globbuf.gl_offs].find("*") != string::npos) {
					break;				
				}			
			}	
			glob("", GLOB_DOOFFS, NULL, &globbuf);
			for (int i = 0; i < com_pat.size(); i++){
				size_t found = com_pat[i].find("*"); 
				if (found == string::npos) {
					globbuf.gl_pathv[i] = strdup(com_pat[i].c_str());
				} else {
					glob(com_pat[i].c_str(), GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);	
				} 
			}
			execvp(com_pat[0].c_str(), &globbuf.gl_pathv[0]);

			for (int i = 0; i < globbuf.gl_offs; i++){
				free (globbuf.gl_pathv[i]);			
			}
			globfree(&globbuf);
		}
		return true;
	}

};


int main (int argc, char **argv, char **envp) {

    sm_str SSTR = sm_str();

	SSTR.run();
	/*for (vector<string>::iterator it = commands.begin(); it != commands.end(); it++) {
		cout << 1111 << *it << 1111 << endl;
	}*/
    printf ("\n");
    return 0;
}


