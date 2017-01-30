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

/**
* @file Geobrick.cpp
* @author Daniele Berto
*/
#include "ApplicationSetup.h"
#include "Geobrick.h"
#include "OutputModule.h"
#include "DefineGeneral.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

Geobrick::Geobrick (std::string ip, int port, int geobrick_number)
{
	Geobrick::ip = ip;
	Geobrick::port = port;

	Geobrick::geobrick_number = geobrick_number;

	geobrick_sock_id = -1;
	status = -1;

	EthCmd.RequestType = VR_DOWNLOAD;
	EthCmd.Request     = VR_PMAC_GETRESPONSE;
	EthCmd.wValue      = 0;
	EthCmd.wIndex      = 0;

	int i = 0;

	for ( i = 0; i < GEOBRICKSOCKETLIMIT; i++)
		EthCmd.bData[i] = 0;

	response = " ";
}

int Geobrick::Connect ()
{
	
	if (status == 0)	
	shutdown (geobrick_sock_id,SHUT_RDWR);

	//The OutputModule object sends the input to the user who has sent the command.
	OutputModule *output_module;
	output_module = OutputModule::Instance ();	  
	  
	int result,sock,length;
	//struct sockaddr_in client;
	struct sockaddr_in client;

	//printf("PMAC Ethernet communication test\n");

	sock = socket (PF_INET,SOCK_STREAM, 0);
	client.sin_addr.s_addr = inet_addr(ip.c_str());
	client.sin_family = PF_INET;
	client.sin_port = htons(port);
	length = sizeof(client);

	output_module->Output("Connection attempt..."); 

	//~ fcntl(sock, F_SETFL, O_NONBLOCK); //This is an aspect of socket programming that I have never considered before now.
									//~ //Moreover, fcntl manipulates the file descriptor, it is not a function strictly
									//~ //binded to the network programming

	result = connect (sock,(__CONST_SOCKADDR_ARG)&client, (socklen_t)length);

	//if 

	//perror("");

	if(result == 0)
	{
	output_module->Output("Connection okay to GeoBrick " + to_string(geobrick_number) + " !\n");  
	geobrick_sock_id = sock; 
	status = 0;
	}
	else
	{
	output_module->Output("Connection failed to GeoBrick " + to_string(geobrick_number) + " !\n");	  
	geobrick_sock_id = -1;
	status = -1;
	}

	return result;

}

int Geobrick::Disconnect()
{
	int result = shutdown (geobrick_sock_id,SHUT_RDWR);
	status = -1;
	return result;
}

int Geobrick::Send(std::string message)
{
	
	//The OutputModule object sends the input to the user who has sent the command.
	OutputModule *output_module;
	output_module = OutputModule::Instance ();	

	int length_to_send;	

	char cResponse[STANDARDBUFFERLIMIT]; //It's too much hard coded...

	bzero(cResponse, STANDARDBUFFERLIMIT);

	int i = 0;

	for ( i = 0; i < GEOBRICKSOCKETLIMIT; i++)
		EthCmd.bData[i] = 0;  

	length_to_send = message.size();

	if (length_to_send > STANDARDBUFFERLIMIT)
	length_to_send = STANDARDBUFFERLIMIT;
	else if (length_to_send < 0)
	length_to_send = 0;

	EthCmd.wLength = htons((u_int16_t)length_to_send);
	strncpy((char*)&EthCmd.bData[0],message.c_str(),length_to_send);

	//printf("Attempting Get Response\n");
	send(geobrick_sock_id,(char*)&EthCmd,ETHERNETCMDSIZE + length_to_send, MSG_NOSIGNAL);
	//send(geobrick_sock_id,"pippo",ETHERNETCMDSIZE + length_to_send, MSG_NOSIGNAL);
	recv(geobrick_sock_id,cResponse,STANDARDBUFFERLIMIT,MSG_NOSIGNAL); //It's too much hard coded...

	string str_tmp(cResponse);

	response = str_tmp;

	return 0;
	//printf(" %s:%s \n",cCommand,cResponse);

	//printf("Done \n");	

	//send(sock,&EthCmd,ETHERNETCMDSIZE + strlen(cCommand),MSG_NOSIGNAL);
	//recv(sock,cResponse,1400,0);

}

string Geobrick::RetrieveMessage()
{
	if (status == -1)
	 //response = "Error: server disconnected\n";
	 response = "Server Offline\n";	
	return response;	
}

string Geobrick::RetrieveCommonVariable()
{
	string results = "";
	
	//The OutputModule object sends the input to the user who has sent the command.
	OutputModule *output_module;
	output_module = OutputModule::Instance ();
	
	Geobrick::Send("&2q70");
	results += "q70 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q77");
	results += "q77 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q78");
	results += "q78 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q79");
	results += "q79 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q87");
	results += "q87 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q88");
	results += "q88 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q89");
	results += "q89 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2q94");
	results += "q94 = " + Geobrick::RetrieveMessage() + '\n';	
	
	Geobrick::Send("&2q95");
	results += "q95 = " + Geobrick::RetrieveMessage() + '\n';	
	
	Geobrick::Send("&2q96");
	results += "q96 = " + Geobrick::RetrieveMessage() + '\n';
	
	Geobrick::Send("&2p91");
	results += "p91 = " + Geobrick::RetrieveMessage() + '\n';	
	
	Geobrick::Send("&2p80");
	results += "p80 = " + Geobrick::RetrieveMessage() + '\n';
	
	return results;								
}
