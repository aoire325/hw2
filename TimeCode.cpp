#include "TimeCode.h"
#include <string>
#include <stdexcept>

using namespace std;


TimeCode::TimeCode(unsigned int hr, unsigned int min, unsigned long long int sec){
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc){
    t = tc.t;
}

void TimeCode::SetHours(unsigned int hours){
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hours, min, sec);
}

void TimeCode::SetMinutes(unsigned int minutes){
    if (minutes >= 60){
        throw invalid_argument("Minutes must be between 0 and 59.");
    }

    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hr, minutes, sec);
}


void TimeCode::SetSeconds(unsigned int seconds){
    if (seconds >= 60){
        throw invalid_argument("Seconds must be between 0 and 59.");
    }

    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hr, min, seconds);
}

void TimeCode::reset(){
    t = 0;
}

unsigned int TimeCode::GetHours() const{
    return t / 3600;
}

unsigned int TimeCode::GetMinutes() const{
    return (t / 60) % 60;
}

unsigned int TimeCode::GetSecond() const{
    return t % 60;
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
	// Convert total seconds back into hours, minutes, and seconds.
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = t % 60;
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
	unsigned long long int totalSeconds = static_cast<unsigned long long>(hr) * 3600 + static_cast<unsigned long long>(min) * 60 + sec;
    return totalSeconds;
}

string TimeCode::ToString()const{
    return to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSecond());
}

TimeCode TimeCode::operator+(const TimeCode& other) const{
    TimeCode result;

    result.t = t + other.t;

    return result;
}

TimeCode TimeCode::operator-(const TimeCode& other) const{
    if (other.t > t){
        throw invalid_argument("Cannot subtract a larger TimeCode.");
    }

    TimeCode result;

    result.t = t - other.t;

    return result;
}

TimeCode TimeCode::operator*(double a) const {
    if (a < 0){
        throw invalid_argument("Negative arguments not allowed: " + to_string(a));
    }

    TimeCode result;

    result.t = static_cast<unsigned long long>(t * a);

    return result;
}

TimeCode TimeCode::operator/(double a) const {
    if (a <= 0){
        throw invalid_argument("Cannot divide TimeCode by zero or a negative number.");
    }

    TimeCode result;

    result.t = static_cast<unsigned long long>(t / a);

    return result;
}

bool TimeCode::operator==(const TimeCode& other) const {
    return t == other.t;
}

bool TimeCode::operator!=(const TimeCode& other) const {
    return t != other.t;
}

bool TimeCode::operator<(const TimeCode& other) const {
    return t < other.t;
}

bool TimeCode::operator<=(const TimeCode& other) const {
    return t <= other.t;
}

bool TimeCode::operator>(const TimeCode& other) const {
    return t > other.t;
}

bool TimeCode::operator>=(const TimeCode& other) const {
    return t >= other.t;
}
