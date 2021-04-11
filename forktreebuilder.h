// Compact Fork Tree Builder as an Educational Tool : Ghanashyam Katti
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

#define main_parent 9
const string FILENAME = "graph.txt";

void generateTreeImage(map<long, vector<long>> nodeMapping, map<long, int> labels)
{

    fstream dotFile;
    dotFile.open("dotfile.gv", ios::trunc | ios::out);

    int count = 0, seq = 0;

    dotFile << "digraph processTree {\n";

    for (auto ppid = nodeMapping.begin(); ppid != nodeMapping.end(); ppid++)
    {
        if (ppid->first == main_parent)
        {
            dotFile << "SYSTEM->" << ppid->second[0] << ";\n";
            count++;
        }
        else
        {
            for (auto pid = ppid->second.begin(); pid != ppid->second.end(); pid++)
            {
                dotFile << ppid->first << "->" << *pid << ";\n";
                count++;
            }
        }
    }

    for (auto lab = labels.begin(); lab != labels.end(); lab++)
    {
        lab->second = seq++;

        if (lab->second)
            dotFile << lab->first << "[label=" << lab->second << "];\n";
        else
        {
            dotFile << lab->first << "[label=" << lab->second
                    << ", shape=polygon, sides=5, peripheries=1, color = blue];\n";
        }
    }

    dotFile << "Processes_Spawned_" << count - 1 << " [shape=polygon, sides=4, peripheries=2, color = red];\n";
    dotFile << "SYSTEM [shape=polygon,sides=6,peripheries=2,color=lightgreen,style=filled]\n}";

    dotFile.close();

    // Generating the PNG file
    string command = "dot -Tpng dotfile.gv -o ForkTree.png";
    system(command.c_str());
}

void generateTree()
{

    fstream file;
    map<long, vector<long>> nodeMapping;
    map<long, int> labels;
    file.open(FILENAME);
    string input;
    long parent, child;
    int index, seq = 0;

    while (!file.eof())
    {

        getline(file, input);

        if (file.eof())
            break;

        index = input.find(":");
        stringstream P(input.substr(0, index));
        stringstream C(input.substr(index + 1, input.size() - index - 1));
        P >> parent;
        C >> child;
        nodeMapping[parent].push_back(child);
        labels[child] = seq++;
    }

    file.close();

    generateTreeImage(nodeMapping, labels);
}

void ConstructTree(fstream &file)
{

    cout << "Only Main Process : " << (long)getppid() << endl;
    file.close();

    string line;
    int number_of_lines = 0;

    file.open(FILENAME, ios::in);

    while (getline(file, line))
    {
        ++number_of_lines;
        if (number_of_lines > 1)
            break;
    }
    file.close();

    if (number_of_lines < 2)
    {
        cout << "No Fork Executed !" << endl;
        return;
    }

    generateTree();
}