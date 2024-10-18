#define SERIAL_TRANSMIT_INT_PIN 2


void interrupts_init()
{
  attachInterrupt(digitalPinToInterrupt(SERIAL_TRANSMIT_INT_PIN), initiate_Tx , CHANGE);
}

void initiate_Tx()
{
  start_Tx = true;
}
