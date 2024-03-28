/*
 * Theatre.cpp
 *
 *  Created on: Mar 28, 2024
 *      Author: keith
 */

#include "Theatre.h"
extern void print (std::string s);

Theatre::Theatre(int capacity):capacity(capacity),cur_num_people(0){}

bool Theatre::enter(int numpeople){
	//can I go in?
	std::lock_guard<std::mutex> lck(m);
	if(cur_num_people+numpeople>capacity){
		print("Oh No! theatre full");
		return false;
	}
	//yes
	cur_num_people+=numpeople;
	return true;
}

