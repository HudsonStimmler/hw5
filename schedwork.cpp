#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add your implementation of schedule() and other helper functions here
bool scheduleDay(
    size_t daypos,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& schedule,
    vector<size_t>& sCount,
    vector<Worker_T> currentDay,
    size_t workerIndex,
    size_t workersScheduled
);


bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) 
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    size_t k = avail[0].size(); 
    sched.resize(avail.size());
    vector<size_t> sCount(k, 0); 
    vector<Worker_T> currentDay;
    return scheduleDay(0, avail, dailyNeed, maxShifts, sched, sCount, currentDay, 0, 0);
}


bool scheduleDay(size_t daypos, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& sCount, vector<Worker_T> currentDay, size_t workerIndex, size_t workersScheduled) 
{
    if(daypos == avail.size()){
        return true; 
    }
    if(workersScheduled == dailyNeed){
        sched[daypos] = currentDay;
        vector<Worker_T> a;
        return scheduleDay(daypos + 1, avail, dailyNeed, maxShifts, sched, sCount, a, 0, 0);
    }
    for(size_t i = workerIndex; i < avail[daypos].size(); i++) {
        if((avail[daypos][i] == true) && (sCount[i] < maxShifts)){
            currentDay.push_back(i);
            sCount[i] += 1;
            if(scheduleDay(daypos, avail, dailyNeed, maxShifts, sched, sCount, currentDay, i + 1, workersScheduled + 1) == true){
                return true;
            }
            sCount[i] -= 1;
            currentDay.pop_back();
        }
    }
    return false; 
}