#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_SHIELD
#define INCLUDE_GPS_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#include <OneSheeld.h>

HttpRequest latitudeRequest("https://rd-year-project-509e1.firebaseio.com/cabs/vehicles/0/lat.json");
HttpRequest longitudeRequest("https://rd-year-project-509e1.firebaseio.com/cabs/vehicles/0/long.json");



void setup() {
  // put your setup code here, to run once:
  Terminal.println("Seting up");
  OneSheeld.begin();
  latitudeRequest.setOnSuccess(&onSuccess);
  latitudeRequest.getResponse().setOnError(&onResponseError);
  
  
  //Internet.setOnError(&onInternetError); 
  
}
 
void loop()
{
  // put your main code here, to run repeatedly:
  
  Terminal.println(dtostrf(GPS.getLatitude(), 11, 6, "xxxx.xxxxxx"));
  Terminal.println(dtostrf(GPS.getLongitude(), 11, 6, "xxxx.xxxxxx"));
  latitudeRequest.addRawData(dtostrf(GPS.getLatitude(), 11, 6, "        "));
  longitudeRequest.addRawData(dtostrf(GPS.getLongitude(), 11, 6, "        "));
  Internet.performPut(latitudeRequest);
  Internet.performPut(longitudeRequest);
  OneSheeld.delay(3000);
  
}
void onSuccess(HttpResponse & response)
{
  Terminal.println("Succeeded");
}

/* Error handling functions. */
void onResponseError(int errorNumber)
{
  /* Print out error Number.*/
  Terminal.print("Response error:");
  switch(errorNumber)
  {
    case INDEX_OUT_OF_BOUNDS: Terminal.println("INDEX_OUT_OF_BOUNDS");break;
    case RESPONSE_CAN_NOT_BE_FOUND: Terminal.println("RESPONSE_CAN_NOT_BE_FOUND");break;
    case HEADER_CAN_NOT_BE_FOUND: Terminal.println("HEADER_CAN_NOT_BE_FOUND");break;
    case NO_ENOUGH_BYTES: Terminal.println("NO_ENOUGH_BYTES");break;
    case REQUEST_HAS_NO_RESPONSE: Terminal.println("REQUEST_HAS_NO_RESPONSE");break;
    case SIZE_OF_REQUEST_CAN_NOT_BE_ZERO: Terminal.println("SIZE_OF_REQUEST_CAN_NOT_BE_ZERO");break;
    case UNSUPPORTED_HTTP_ENTITY: Terminal.println("UNSUPPORTED_HTTP_ENTITY");break;
    case JSON_KEYCHAIN_IS_WRONG: Terminal.println("JSON_KEYCHAIN_IS_WRONG");break;
  }
} 
