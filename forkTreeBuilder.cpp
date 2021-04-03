// #include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<bits/stdc++.h>

using namespace std;

#define main_parent 9
const string FILENAME = "graph.txt";
void generateTreeImage(map<long, vector<long> >nodeMappings) {

}

void generateTree() {

	fstream file;
	map<long, vector<long> > nodeMapping;
	file.open(FILENAME);
	string input;
	long parent, child;
	int index;
	
	while(file) {
		
		getline(file, input);
		index = input.find(":");
		stringstream P(input.substr(0, index));
		stringstream C(input.substr(index+1, input.size()-index-1) );
		
		P>>parent; C>>child;
		nodeMapping[ parent ].push_back( child );
		cout<<"Child : "<<child<<endl;
	}

	file.close();

	for(auto ppid = nodeMapping.begin(); ppid != nodeMapping.end(); ppid++) {

		cout<<ppid->first<<" : ";
		for(auto  pid = ppid->second.begin(); pid != ppid->second.end(); pid++) {
			cout<<*pid<<", ";
		}
		cout<<endl;
	}
}


int main(int argc, char const *argv[])
{	
	string FILENAME = "graph.txt";
	fstream file;
	file.open(FILENAME, ios::trunc | ios::out | ios::in);

	fork();
	fork() && fork() || fork();
	fork();

	sleep(2);
	file<<(long)getppid()<<":"<<(long)getpid()<<endl;
	cout<<"1"<<endl;
	sleep(2);

	if((long)getppid() != main_parent)
		exit(0);

	cout<<"Only Main Process : "<<(long)getppid()<<endl;
	file.close();

	generateTree();
	return 0;
}