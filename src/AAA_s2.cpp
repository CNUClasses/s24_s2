#include <mutex>
#include <thread>
#include <iostream>
#include <atomic>
#include <vector>
#include "Theatre.h"

using namespace std;

int numtickets=500;
Theatre t1(numtickets/2);
Theatre t2(numtickets/2);

mutex m;
mutex mcout;

void print (string s){
	lock_guard<mutex> lck1(mcout);
	cout<<s<<endl;
}
void agent(int i){

	//I sell tickets
	int numsold=0;
	print("Agent "+ to_string(i)+" starting...");

	while(true){
		{
			lock_guard<mutex> lck1(m);
			if (numtickets==0)
				break;
			numtickets--;
		}

		//enter a theatre
		if(!t1.enter())
			t2.enter();

		numsold++;
		print("Agent "+ to_string(i)+" sold 1");
	}

	print("Agent "+to_string(i)+" LEAVING!, sold="+to_string(numsold));
}

int main() {
	std::vector<std::thread> vecThreads;

	//how many cores (2 virtual cores per physical core)
	int numbThreads = std::thread::hardware_concurrency();

	//lets start up 1 per core
	for (int i=0;i<numbThreads/2;i++){
		vecThreads.push_back(std::thread(agent,i));
	}

	{lock_guard<mutex> lck1(m);
	print("Starting to sell tickets! numtickets="+to_string(numtickets));
	}

	//wait for em to finish
	for(auto& t : vecThreads){
		t.join();
	}

	cout<<"Finished! numtickets="<<numtickets<<endl;
	cout<<" num in theatre1="<<t1.get_cur_num_people()<<endl;
	cout<<" num in theatre2="<<t2.get_cur_num_people()<<endl;
	return 0;
}
