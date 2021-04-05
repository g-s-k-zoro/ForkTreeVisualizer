#include "forktreebuilder.h"

int main(int argc, char const *argv[])
{	
	fstream file;
	file.open(FILENAME, ios::trunc | ios::out);

//-----------------Custom Code Begins-------------------------------------------
	
    if (fork() && (!fork())) {
        if (fork() || fork()) {
            fork();
        }
    }




//-----------------Custom Code Ends---------------------------------------------
	file<<(long)getppid()<<":"<<(long)getpid()<<endl;

	sleep(2);

	if((long)getppid() != main_parent)
		exit(0);

	ConstructTree(file);
	return 0;
}