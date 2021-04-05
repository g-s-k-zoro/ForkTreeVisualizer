# ForkTreeVisualizer
Educational tool to visualize how fork() works. For a given code snippet with fork(), A compact Representation of
the Process tree is generated.

Steps to Use - 

Clone and -
1. Install Graphviz on your OS - 
	a. Linux  : sudo apt-get install -y graphviz  
	b. Windows : https://gitlab.com/graphviz/graphviz/-/package_files/8184046/download  
				 Add to PATH for all/current user(s)  
	c. MacOS   : sudo port install graphviz OR brew install graphviz  

2. Whatever snippet of code that involves spawning child processes using force, copy it and paste in
   the Custom Code Section in forkVisualizer.cpp - 

//-----------------Custom Code Begins-------------------------------------------
  
  
  
  
  
//-----------------Custom Code Ends---------------------------------------------

3. Run forkVisualizer.cpp : - g++ forkVisualizer.cpp and the fork() Tree will be saved as ForkTree.png in the same directory.

*Note : The tree generated is dependent on the order in which the processes are executed. Structure of trees for different orders is 
uniform, but the process order may vary.