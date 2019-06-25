#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

static pthread_mutex_t semmphore1;
static pthread_mutex_t semmphore2;
static pthread_cond_t e1 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t e2[10] = {PTHREAD_COND_INITIALIZER};
int groupOrder;
int totalWaitGroup = 0;
int totalWaitLocked = 0;
int go2;
int proGroup = 0;
int posUse[10] = { 0 };

struct user {
	int userNumber;
	int user;
	int position;
	int WaitTime;
	int sleepTime;
};

void *requestUse(void *theUser) {

	user* tUser = (user*)theUser;
	Sleep(tUser->WaitTime);
	pthread_mutex_lock(&semmphore1);

	cout << "User " << tUser->userNumber << " from Group " << tUser->user << " arrives to the DBMS" << endl;
	if (tUser->user != groupOrder) {
		totalWaitGroup++;
		cout << "User " << tUser->userNumber << " is waiting due to its group" << endl;
		pthread_cond_wait(&e1, &semmphore1);
	}
	if (posUse[tUser->position - 1] != 0) {
		totalWaitLocked++;
		cout << "User " << tUser->userNumber << " is waiting: position " << tUser->position << " of the databse is being used by user " << posUse[tUser->position - 1] << endl;
		pthread_cond_wait(&e2[tUser->position-1], &semmphore1);
	}

	cout << "User " << tUser->userNumber << " is accessing the position " << tUser->position << " of the database for " << tUser->sleepTime << " second(s)" << endl;
	posUse[tUser->position - 1] = tUser->userNumber;
	if(proGroup <= 0 )
		pthread_cond_signal(&e1);
	pthread_mutex_unlock(&semmphore1);


	Sleep(tUser->sleepTime);


	pthread_mutex_lock(&semmphore2);

	cout << "User " << tUser->userNumber << " finished its execution" << endl;
	posUse[tUser->position - 1] = 0;
	pthread_cond_signal(&e2[tUser->position - 1]);

		--proGroup;
	if (proGroup == 0) {

		cout << endl << "All users from Group " << groupOrder << " finished their execution" << endl;
		cout << "The userrs from Group " << go2 << " start their execution" << endl;

		groupOrder = go2;
		pthread_cond_signal(&e1);
		cout << endl;
	}

	pthread_mutex_unlock(&semmphore2);

	return NULL;
}


class mdms {
private:
	static int posUse[10];
	int userNum = 0;
	int sleepThisMuch = 0;

	int totalUsersGS = 0;
	int totalug1 = 0;
	int totalug2 = 0;


	queue<user> groups;


public:
	mdms() {
		string temp;
		int i = 0;
		user tempUser;
		getline(cin, temp);
		groupOrder = stoi(temp);

		if (groupOrder == 1)
			go2 = 2;
		else
			go2 = 1;

		while (getline(cin, temp)) {
			stringstream ss1(temp);
			i = 0;
			string new1;
			while (getline(ss1, new1, ' ')) {
				if (i == 0) {
					tempUser.userNumber = ++userNum;
					tempUser.user = stoi(new1);

					if (tempUser.user == 1)
						++totalug1;
					else
						++totalug2;
					if (tempUser.user == groupOrder)
						++proGroup;
				}
				else if (i == 1) {
					tempUser.position = stoi(new1);
				}
				else if (i == 2) {
					tempUser.WaitTime = stoi(new1);
				}
				else if (i == 3) {
					tempUser.sleepTime = stoi(new1);
				}
				++i;
			}
			groups.push(tempUser);
			totalUsersGS++;
		}
	}
	void database(){
		int last = 0;
		pthread_t tid[totalUsersGS];
		for (int k = 0; k < totalUsersGS; k++) {
			groups.front().WaitTime += last;
			pthread_create(&tid[k], NULL, &requestUse, &groups.front());
			last = groups.front().WaitTime;
			groups.pop();
		} 
		for (int k = 0; k < totalUsersGS; k++) {
			pthread_join(tid[k], NULL);
		}
		cout <<endl<< "Total Requests:" << endl << "         Group 1: " << totalug1 << endl << "         Group 2: " << totalug2 << endl;
		cout <<endl<< "Requests that waited:" << endl << "         Due to its  group: " << totalWaitGroup << endl<< "         Due to a locked position: " <<totalWaitLocked<< endl;
	} 
};

int main(int argc, char** argv) {
	pthread_mutex_init(&semmphore1, NULL);
	mdms start;
	start.database();
	return 0;
}