/*
 * Theatre.h
 *
 *  Created on: Mar 28, 2024
 *      Author: keith
 */

#ifndef THEATRE_H_
#define THEATRE_H_
#include <mutex>

class Theatre {
public:
	Theatre(int capacity);

	bool enter(int numpeople=1);
	int get_cur_num_people(){return cur_num_people;}
private:
	//how many people will fit in total
	int capacity;

	//how many people are in it now
	int cur_num_people;
	std::mutex m;
};

#endif /* THEATRE_H_ */
