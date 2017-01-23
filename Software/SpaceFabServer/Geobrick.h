// GNU General Public License Agreement
// Copyright (C) 2015-2016 Daniele Berto daniele.fratello@gmail.com
//
// SpaceFabServer is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software Foundation. 
// You must retain a copy of this licence in all copies. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
// ---------------------------------------------------------------------------------

#ifndef __GEOBRICKH
#define __GEOBRICKH
/**
* @file Geobrick.h
* @author Daniele Berto
*/

#include "DefineGeneral.h"
#include <stdio.h>
#include <string>

using namespace std;

typedef struct tagEthernetCmd
{
  u_int8_t   RequestType;
  u_int8_t   Request;
  u_int16_t  wValue;
  u_int16_t  wIndex;
  u_int16_t  wLength;
  u_int8_t   bData[GEOBRICKSOCKETLIMIT];
} ETHERNETCMD,*PETHERNETCMD;

class Geobrick
{
private:

	int geobrick_number;

	int geobrick_sock_id;

	int status;

	std::string ip;

	int port;

    ETHERNETCMD EthCmd;
    
    string response;

public:

    Geobrick(std::string ip, int port, int geobrick_number);
  /**
   * @brief The ApplicationSetup constructor sets imset variable to zero.
   */
    int Connect();
    
    int Disconnect();
    
    int Send(std::string ip);
    
    string RetrieveCommonVariable();
    
    string RetrieveMessage();
};
#endif
