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


// Add prototypes for any helper functions here
bool assign(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& nShift, size_t nDay);
bool valWorker(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& nShift, size_t nDay);

// Add your implementation of schedule() and other helper functions here

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
    
    // Add your code below

  //backtracking recursive algorithm that makes a n row by k column matrix of booleans
  //d workers needed
  //k possible workers
  //n day period
  //m max max shifts a woker can work over the n day period

  size_t d = dailyNeed;
  size_t m = maxShifts;
  size_t n = avail.size();//row
  size_t k = avail[0].size();//column

  sched.clear();
  sched.resize(n);

  vector<int> nShift(k, 0);

  return assign(avail, dailyNeed, maxShifts, sched, nShift, 0);


}

bool assign(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& nShift, size_t nDay){
  size_t n = avail.size();

  //base case
  //all days filled
  if(nDay == n){
    return true;
  }

  //move to next day if curr day is not available
  if(sched[nDay].size() == dailyNeed){
    return assign(avail, dailyNeed, maxShifts, sched, nShift, nDay+1);
  }

  return valWorker(avail, dailyNeed, maxShifts, sched, nShift, nDay);
  //new recur func

}


bool valWorker(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& nShift, size_t nDay){
  size_t k = avail[nDay].size();

  for(size_t i=0; i<k; i++){
    if(!avail[nDay][i]){
      continue;
    }
    if(nShift[i]<maxShifts){
      if(find(sched[nDay].begin(), sched[nDay].end(), i) != sched[nDay].end()){
        continue;
      }
      sched[nDay].push_back(i);
      nShift[i]++;

      //fill next worker or day
      if(assign(avail, dailyNeed, maxShifts, sched, nShift, nDay)==true){
        return true;
      }
      //btrack 
      sched[nDay].pop_back();
      nShift[i]--;
    }
  }
  return false;
}
