#define MEASUREMENTS_PERIOD 10 //period in seconds
Ticker measurements_timer;

void timers_init()
{
  // Set up the ticker to call the serialCom_request function every MEASUREMENTS_PERIOD seconds (1000 ms)
  measurements_timer.attach(MEASUREMENTS_PERIOD, serialCom_request);
}