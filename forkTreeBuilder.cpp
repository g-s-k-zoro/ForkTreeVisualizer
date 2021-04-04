// #include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<bits/stdc++.h>

using namespace std;

#define main_parent 9
const string FILENAME = "graph.txt";

void generateTreeImage(map<long, vector<long> >nodeMapping) {

	fstream dotFile;
	dotFile.open("dotfile.gv", ios::trunc | ios::out);

	int count = 0;

	dotFile<<"digraph processTree {\n";
	for(auto ppid = nodeMapping.begin(); ppid != nodeMapping.end(); ppid++) {
		if( ppid->first == main_parent ){
			dotFile<<"MAIN_PROCESS->"<<ppid->second[0]<<";\n";
			count++;
		}
		else {
			for(auto pid = ppid->second.begin(); pid != ppid->second.end(); pid++) {
				dotFile<<ppid->first<<"->"<<*pid<<";\n";
				count++;
			}
		}
	}
	dotFile<<"Processes_Spawned_"<<count<<" [shape=polygon, sides=4, peripheries=2, color = red];\n";
	dotFile<<"MAIN_PROCESS [shape=polygon,sides=6,peripheries=2,color=lightgreen,style=filled]\n}";

	dotFile.close();

	//Generrating the PNG file
	string command = "dot -Tpng dotfile.gv -o ForkTree.png";
	system(command.c_str());
}

void generateTree() {

	fstream file;
	map<long, vector<long> > nodeMapping;
	file.open(FILENAME);
	string input;
	long parent, child;
	int index;
	
	while(!file.eof()) {
		
		getline(file, input);
		
		if(file.eof())
			break;
		
		index = input.find(":");
		stringstream P(input.substr(0, index));
		stringstream C(input.substr(index+1, input.size()-index-1) );
		P>>parent; C>>child;
		nodeMapping[ parent ].push_back( child );
	}

	file.close();

	generateTreeImage(nodeMapping);
}


int main(int argc, char const *argv[])
{	
	string FILENAME = "graph.txt";
	fstream file;
	file.open(FILENAME, ios::trunc | ios::out | ios::in);

	//Custom Code Begins
	fork();
	fork() && fork() || fork();
	fork();

	//Custom Code Ends
	file<<(long)getppid()<<":"<<(long)getpid()<<endl;

	sleep(2);

	if((long)getppid() != main_parent)
		exit(0);

	cout<<"Only Main Process : "<<(long)getppid()<<endl;
	file.close();

	generateTree();
	return 0;
}