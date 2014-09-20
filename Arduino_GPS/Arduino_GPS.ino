#include <SoftwareSerial.h>
#include "a3gs.h"

//pin

//twitter command
const char *token = "2575172004-zGDI1dcWnMKq7BFrOUTtkA47d1PiVxQwb9yBMnU"; //toritori:1424505170-9hWXoVYrz9wDI1XKbnXOuO3by9AClM1rCxV5OkT
char *message = "Ardino Tweet Test Start";

//gps command
char lat[15],lng[15];     //lat=latitude,lng=longitude

void setup(){
  Serial.begin(9600);
  Serial.println("Start");
  if(a3gs.start() == 0 && a3gs.begin() == 0){
    Serial.println("Succeed");
    //gps check
    if(a3gs.getLocation(a3gsMPBASED,lat,lng) == 0) Serial.println("Gps:OK");
    else Serial.println("Gps:NG");
    //tweet check
    if(a3gs.tweet(token,message) == 0) Serial.println("Tweet:OK");
    else Serial.println("Tweet:NG");   
  }else Serial.println("Faild");
}

void loop(){
  Serial.println("Test Start");
  GpsGet();
  TwitterGet();
  delay(10000);
  Serial.println("http://www.n-survey.com/online/gmap2.htm");
}

void GpsGet(){ 
  Serial.println("gps...");
  if(a3gs.getLocation(a3gsMPBASED,lat,lng) == 0){
    Serial.print("OK");
    Serial.print(lat);
    Serial.print(",");
    Serial.println(lng);
  }else Serial.println("No,error");
}

void TwitterGet(){
  Serial.println("tweet");
  const char *mapping = "Plese the followring URL, enter the latitude and longitude .->http://www.n-survey.com/online/gmap2.htm";
  //Plese the followring URL, enter the latitude and longitude .So check the position from the map.->http://www.n-survey.com/online/gmap2.htm
  sprintf(message,"latitude : %d , longitude : %d ",lat,lng);
  if(a3gs.tweet(token,message) == 0){
    if(a3gs.tweet(token,mapping) == 0) Serial.println("Message:OK");
    else Serial.println("Message:NG");
  }
}
