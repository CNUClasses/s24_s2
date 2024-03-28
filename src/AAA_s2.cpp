#include <mutex>
#include <thread>
#include <iostream>
#include <atomic>
#include <vector>
using namespace std;

atomic<int> numtickets(50);
mutex m;

void agent(int i){
	//I sell tickets

	while(numtickets>0){
		{
			lock_guard<mutex> lck(m);
			if(numtickets!=0)
				numtickets--;
		}

		cout<<"Agent "<<i<<" sold a ticket, numtickets="<<numtickets<<endl;
	}
	lock_guard<mutex> lck(m);
	cout<<"Agent "<<i<<" LEAVING!, numtickets="<<numtickets<<endl;
}

int main() {
	std::vector<std::thread> vecThreads;

	//how many cores (2 virtual cores per physical core)
	int numbThreads = std::thread::hardware_concurrency();

	//lets start up 1 per core
	for (int i=0;i<numbThreads/2;i++){
		vecThreads.push_back(std::thread(agent,i));
	}
	{
		lock_guard<mutex> lck(m);
		cout<<"Starting to sell tickets! numtickets="<<numtickets<<endl;
	}

	//wait for em to finish
	for(auto& t : vecThreads){
		t.join();
	}

	cout<<"Finished! numtickets="<<numtickets<<endl;
	return 0;
}
