/*Design a class TIME which stores hour, minute and second. The class should have the methods to support the following:
• User may give the time value in 24-hour format.
• User may give the time value in AM/PM format
• Display the time in 24-hour format.
  
• Display the time in AM/PM format.
• User may like to add minute with a time value.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Time{
  int hour;
  int minute;
  int seconds;
  public:
  void set_time_in_24(int hour,int minute,int seconds){
    this->hour = hour;
    this->minute = minute;
    this->seconds = seconds;
  }
  void set_time_in_ampm(int hr,int minute,int seconds,string s){
    if(s=="AM")
      if(hr==12)
        hour = hr - 12;
      else
        hour = hr;
    else
      if(hr==12)
        hour = hr;
      else
        hour = hr + 12;
    this->minute = minute;
    this->seconds = seconds;
  }
  void show_in_24(){
    cout<<"Time is: "<<hour<<":"<<minute<<":"<<seconds<<endl;
  }
  void show_in_ampm(){
    int hr = hour;
    if(hour>12)
      hr = hour%12;
    else if(hour==0)
      hr = 12;
    string s = hour>=12 ? "PM" : "AM";
    cout<<"Time is: "<<hr<<":"<<minute<<":"<<seconds<<" "<<s<<endl;
  }
  void add_minutes(int minutes){
    int hr = minutes/60;
    minutes = minutes%60;
    hour = (hour+hr)%24;
    
    if(minute+minutes>=60){
      hour = (hour+1)%24;
      minute = (minute+minutes)%60;
    }else
      minute += minutes;
  }
};

int main()
{
 Time t;
 t.set_time_in_24(0,55,22);
 t.show_in_24();
 t.show_in_ampm(); 
 t.add_minutes(200);
 t.show_in_24();
 t.show_in_ampm(); 
 t.set_time_in_ampm(12,32,11,"PM");
 t.show_in_24();
 t.show_in_ampm(); 
 t.add_minutes(130);
 t.show_in_24();
 t.show_in_ampm(); 
 return 0;
}

