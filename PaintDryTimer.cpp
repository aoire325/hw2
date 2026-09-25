#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "TimeCode.h"

using namespace std;


struct DryingSnapShot {
    string name;
    time_t startTime;
    TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
    long long int totalTime =
        dss.timeToDry->GetHours() * 3600 +
        dss.timeToDry->GetMinutes() * 60 +
        dss.timeToDry->GetSeconds();

    long long int elapsedTime = time(0) - dss.startTime;

    return totalTime - elapsedTime;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
    return dss.name + ": " +
           to_string(get_time_remaining(dss)) +
           " seconds remaining";
}


double get_sphere_sa(double rad){
    return 4 * M_PI * rad * rad;
}


TimeCode *compute_time_code(double surfaceArea){
    unsigned long long seconds =
        static_cast<unsigned long long>(surfaceArea);

    TimeCode *tc = new TimeCode(0, 0, seconds);

    return tc;
}


void tests(){
    // get_time_remaining
    DryingSnapShot dss;
    dss.startTime = time(0);

    TimeCode tc = TimeCode(0, 0, 7);
    dss.timeToDry = &tc;

    long long int ans = get_time_remaining(dss);

    assert(ans == 7);

    // add more tests here


    // get_sphere_sa
    double sa = get_sphere_sa(2.0);

    assert(50.2654 < sa && sa < 50.2655);

    // add more tests here


    // compute_time_code
    TimeCode *tc2 = compute_time_code(1.0);

    assert(tc2->GetTimeCodeAsSeconds() == 1);

    assert(tc2->GetHours() == 0);
    assert(tc2->GetMinutes() == 0);
    assert(tc2->GetSeconds() == 1);

    delete tc2;


    // add more tests here


    cout << "ALL TESTS PASSED!" << endl;
}


int main(){
    tests();
}