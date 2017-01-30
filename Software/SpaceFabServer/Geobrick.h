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
* @details This object manages the interaction between the SpaceFabServer
* and the two GeoBricks. I have to underline that the interaction operates
* with a TCP/IP communication. The protocol is described in the document
* Software Doku Spacefab_1_96.pdf .
* 
* N.B. In this project it is used the word "GeoBrick" both to indicate
* the elettronic module of the SpaceFab and the software object GeoBrick
* who manages the interaction with it. 
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

	//The program have to manage two GeoBrick. The geobrick_number
	//variable records the number of the GeoBrick managed by the current
	//object.
	int geobrick_number;

	//This variable records the sock_id used to communicate with the GeoBrick.
	int geobrick_sock_id;

	//This variable records the status of the connection with the GeoBrick.
	int status;

	//This variable records the ip of the physical GeoBrick that communicates
	//with the current GeoBrick object.
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
