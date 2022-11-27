

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool scheduleHelper (const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int days,
    int workers,
    std::vector<int> daysWorked
);

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    int days=avail.size();
    int workers=avail[0].size();
    std::vector<int> daysWorked;
    for (int i=0; i<workers;i++){
        daysWorked.push_back(0);
    }
    return scheduleHelper(avail, dailyNeed,maxShifts,sched,days,workers,daysWorked);
}

bool scheduleHelper (const AvailabilityMatrix& avail,
    const size_t d,
    const size_t m,
    DailySchedule& sched,
    int days,
    int workers,
    std::vector<int> daysWorked
) {
    if ((int)sched.size()==days){
        if(sched[days-1].size()==d){
            return true;
        }
    }
    if (sched.size()==0){
        std::vector<Worker_T> temp;
        sched.push_back(temp);
    }
    int day=sched.size();

    if ((int)sched[day-1].size()==(int)d){
        std::vector<Worker_T> temp;
        sched.push_back(temp);
    }
    day=sched.size();

    for (int i=0; i<workers; i++){

        //if worker is in the current day
        if (!(std::find(sched[day-1].begin(), sched[day-1].end(), i) != sched[day-1].end())){
            if (avail[day-1][i]){
                sched[day-1].push_back(i);
                if (daysWorked[i]<(int)m){
                    daysWorked[i]++;
                    if (scheduleHelper(avail,d,m,sched,days,workers,daysWorked)){
                        return true;
                    }
                    daysWorked[i]--;
                }
                sched[day-1].pop_back();
            }
        }
    }
    if (sched[day-1].size()==0){
        sched.pop_back();
    }
    return false;
}

