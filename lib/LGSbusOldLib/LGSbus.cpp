

#include "LGSbus.h"

LGSbus::LGSbus()
{

}

LGSbus::~LGSbus()
{
  
}

void LGSbus::begin(int id, HardwareSerial *serial, int baud, int timeout)
{ 
  serial->begin(abs(baud));
  serial->setTimeout(abs(timeout));
  SR = serial;
  ID = constrain(id, 0, 255);
}

int LGSbus::send(int id, int type, int addr, int data, int timeout, int cnt_max)
{
  // 1. prepare
  addr = constrain(addr, 0, 255);
  timeout = abs(timeout);
  cnt_max = abs(cnt_max);
  int cnt = 0;
    
  while(cnt < cnt_max)  // times exceeded
  { 
    cnt++;
    
    // 2. send
    SR->write('#');
    SR->println(id);
    SR->println(type);
    SR->println(addr);
    SR->println(data);
    SR->println(id + type + addr + data);  
  
    // 3. return
    unsigned long startTime = millis();
    while(millis()-startTime < timeout) // timeout
    {
      if (SR->find('&'))
      {
        int id_ret    = SR->parseInt();
        int type_ret  = SR->parseInt();
        int addr_ret  = SR->parseInt();
        int data_ret  = SR->parseInt();
        int sum_ret   = SR->parseInt();
        int sum_cal   = id_ret + type_ret + addr_ret + data_ret; 

        if (id==id_ret && type_ret==RETURN_TYPE && addr==addr_ret && sum_cal==sum_ret)
        {
          addr_ret = constrain(addr_ret, 0, DATA_BUF_SIZE-1);
          DATA_BUF[addr_ret] = data_ret;
          return 1;
        }
        else  // packet incorrect 
        {
          break;
        }
      }
    }
  }
  return 0;
}

int LGSbus::readData(int addr)
{
  addr = constrain(addr, 0, DATA_BUF_SIZE-1); 
  return DATA_BUF[addr];
}

void LGSbus::writeData(int addr, int data)
{
  addr = constrain(addr, 0, DATA_BUF_SIZE-1); 
  DATA_BUF[addr] = data;
}

int LGSbus::readLastAddress()
{
  return LAST_ADDR ;
}

int LGSbus::write(int id, int addr, int data, int timeout, int cnt_max)
{
  return send(id, WRITE_TYPE, addr, data, timeout, cnt_max);
}

int LGSbus::read(int id, int addr, int timeout, int cnt_max)
{
  return send(id, READ_TYPE, addr, 0, timeout, cnt_max);
}

int LGSbus::poll()
{
  if (SR->available())
  {
    if (SR->find('#'))
    {
      int id      = SR->parseInt();
      int type    = SR->parseInt();
      int addr    = SR->parseInt();
      int data    = SR->parseInt();
      int sum     = SR->parseInt();
      int sum_cal = id + type + addr + data; 
      
      if (id==ID && sum_cal==sum)
      {
        addr = constrain(addr, 0, DATA_BUF_SIZE-1);
        LAST_ADDR = addr;
        if (type == WRITE_TYPE) DATA_BUF[addr] = data;

        delay(5);
        SR->write('&');
        SR->println(id);
        SR->println(RETURN_TYPE);
        SR->println(addr);
        SR->println(DATA_BUF[addr]);
        SR->println(id + RETURN_TYPE + addr + DATA_BUF[addr]);  
        return 1;
      }
    }
  }
  return 0; // not responde or packet incorrect
}

void LGSbus::customReturn(int addr, int data)
{
  SR->write('&');
  SR->println(ID);
  SR->println(RETURN_TYPE);
  SR->println(addr);
  SR->println(data);
  SR->println(ID + RETURN_TYPE + addr + data);  
}