//reciver
#include <VirtualWire.h>

void setup()
{
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  
  vw_setup(2000);
  vw_set_rx_pin(3);
  vw_rx_start();
}

void loop()
{
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  
   if(vw_get_message(buf, &buflen))
   {
     for(int i = 0; i < buflen; i++)
     {
       if(buf[i] == '1')
       {
         digitalWrite(4,HIGH);
       }
       else if(buf[i] == '0')
       {
         digitalWrite(4,LOW);
       }
     } 
   }
}
