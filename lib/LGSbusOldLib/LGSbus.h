
 /*
 *  LGSbus.h
 *  Old version LGSbus library, Because it can only be sent to one address at a time.
 * 
 *  Author: M.Teerachot
 *  Tested with STM32G431CBU6
 */

#ifndef LGSBUS_H
#define LGSBUS_H

#include <Arduino.h>
#include <Stream.h>
#include <HardwareSerial.h>

class LGSbus
{
  #define DATA_BUF_SIZE   30  
  #define READ_TYPE        0
  #define WRITE_TYPE       1
  #define RETURN_TYPE      2
      
private:
    uint16_t ID;
    int DATA_BUF[DATA_BUF_SIZE];
    int LAST_ADDR;
    
public:
    LGSbus(); 
    ~LGSbus();
    const uint8_t ID_MASTER = -1; 
    void begin(int id, HardwareSerial *serial, int baud, int timeout=50);
    int send(int id, int type, int addr, int data, int timeout, int cnt_max);
    int readData(int addr);
    void writeData(int addr, int data);
    
    /* master */
    int write(int id, int addr, int data, int timeout=500, int cnt_max=1);
    int read(int id, int addr, int timeout=500, int cnt_max=1);
    
    /* slave */
    int poll();
    int readLastAddress();
    void customReturn(int addr, int data);
    
  protected:
    Stream *SR;

};

#endif // LGSBUS_H