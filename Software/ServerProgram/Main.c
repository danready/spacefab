// GNU General Public License Agreement
// Copyright (C) 2015-2016 Daniele Berto daniele.fratello@gmail.com
//
// CollSoft is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software Foundation. 
// You must retain a copy of this licence in all copies. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
// ---------------------------------------------------------------------------------

/**
* @file MainExistence.c
* 
* @brief The MainExistence program.
*
* @author Daniele Berto
*/

#include "ApplicationSetup.h"
#include "TcpUser.h"
#include "CommunicationObject.h"
#include "OutputModule.h"
#include "Geobrick.h"
#include "Input.h"
#include <sys/types.h>
#include <stdint.h>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/prctl.h>

using namespace std;


bool reg_matches (const char *str, const char *pattern)
{
	regex_t re;
	int ret;

	if (regcomp (&re, pattern, REG_EXTENDED) != 0)
		return false;

	ret = regexec (&re, str, (size_t) 0, NULL, 0);
	regfree (&re);

	if (ret == 0)
		return true;

	return false;
}

int main (int argc, char **argv)
{
	
	Geobrick Geobrick1(GEOBRICK_IP_1, GEOBRICK_PORT, 1);
	Geobrick Geobrick2(GEOBRICK_IP_2, GEOBRICK_PORT, 2);
	
	//~ ApplicationSetup *main_application_setup;
	//~ main_application_setup = ApplicationSetup::Instance ();
	//~ main_application_setup->FetchInputMode(main_application_setup->application_setup_input_mode);
	//~ 
	//~ OutputModule *output_module;
	//~ output_module = OutputModule::Instance ();
	//~ 
	//~ TcpUser command_received_by_user;
	//~ 
	//~ CommunicationObject mioTCP;
//~ 
	//~ mioTCP.CommunicationObjectInit ();  
	//buffer array will contain the input insert via stdin.
	
	char* buffer;
	buffer = (char*) malloc (STANDARDBUFFERLIMIT);

	//The ApplicationSetup singleton contains some useful variables for the program like the path of the log files.
	ApplicationSetup *main_application_setup;
	main_application_setup = ApplicationSetup::Instance ();
	main_application_setup->FetchInputMode(main_application_setup->application_setup_input_mode);

	//The Input object fetches the Input from the stdin.
	Input* mioinput;

	//The OutputModule object sends the input to the user who has sent the command.
	OutputModule *output_module;
	output_module = OutputModule::Instance ();

	//The TcpUser object records the input obtained by the CommunicationObject mioTCP
	TcpUser command_received_by_user;

	//The CommunicationObject manages the input obtained cia TCP/IP
	CommunicationObject mioTCP;

	//CommunucationObject initialization.
	mioTCP.CommunicationObjectInit ();

	//If the user can send input to the program also via stdin
	if (main_application_setup->input_mode != ONLYTCP) {
		printf("SpaceFabServer version 0.1\nPress help for the available command list\n");
		mioinput = new Input();
	}
	
	//The program never stop: it must be killed to stop it
	while (1)
	{
		usleep(100000);
		
		//If the user can send input to the program also via stdin
		if (main_application_setup->input_mode != ONLYTCP)
		{
			fflush (stdout);
		}

		//Setting to zero buffer. The buffer array will contain the stdin input.
		bzero (buffer, STANDARDBUFFERLIMIT);

		//If the input can be sent either via stdin and via tcp/ip
		//N.B. If both of input type are present, tcp/ip input is preferred
		if (main_application_setup->input_mode == ALL)
		{

			//Get stdin input
			mioinput->GetInput (buffer);

			//If stdin input is not empty
			if (strlen (buffer) != 0)
			{
				//Enabling the output to the stdout
				output_module->OutputModuleStdoutOn();
				
				//Disbling the output to the TCP/IP
				output_module->OutputModuleSockidOff();

			}

			//Get tcp/ip input
			command_received_by_user = mioTCP.GetCommand ();

			//If tcp/ip input is not empty
			if (command_received_by_user.command_sent_by_user[0] != 0)
			{
				//Disabling the Output to the stdout
				output_module->OutputModuleStdoutOff();
				//Enabling the Output to the TCP/IP recording the user_sockid of the user who has sent the command.
				output_module->OutputModuleSockidOn(command_received_by_user.user_sockid);
				
			}
			
			//N.B. If both of input type are present, tcp/ip input is preferred
			
		}  //if (main_application_setup->input_mode == ALL)

		//If the input can be sent only via stdin
		else if (main_application_setup->input_mode ==
		ONLYUSER)
		{

			//Get stdin input
			mioinput->GetInput (buffer);

			//If stdin input is not empty
			if (strlen (buffer) != 0)
			{
				//Enabling the output to the stdout
				output_module->OutputModuleStdoutOn();
				
				//Disbling the output to the TCP/IP
				output_module->OutputModuleSockidOff();
				
			}
			
		}  //if (main_application_setup->input_mode == ONLYUSER)


		//If the input can be sent only via tcp/ip
		else if (main_application_setup->input_mode ==
		ONLYTCP)
		{

			//Get tcp/ip input
			command_received_by_user = mioTCP.GetCommand ();

			//If tcp/ip input is not empty
			if (command_received_by_user.command_sent_by_user[0] != 0)
			{
				//Disabling the Output to the stdout
				output_module->OutputModuleStdoutOff();
				
				//Enabling the Output to the TCP/IP recording the user_sockid of the user who has sent the command.
				output_module->OutputModuleSockidOn(command_received_by_user.user_sockid);			
				
			}

		}  //if (main_application_setup->input_mode == ONLYTCP)

		//If tcp/ip input is not empty
		if (strlen (buffer) != 0
		|| command_received_by_user.command_sent_by_user[0] != 0)
		{		  
			//check_process: checks if CollSoft program exists.
			if(reg_matches (command_received_by_user.command_sent_by_user, "^1:.{1,30}$")
			|| reg_matches (buffer, "^1:.{1,30}$")) 
			{
				if (buffer[0] == '1')
				{
					string message_to_send(&buffer[2]);
					Geobrick1.Send(message_to_send);
				}
				else
				{
					string message_to_send(&command_received_by_user.command_sent_by_user[2]);
					Geobrick1.Send(message_to_send);
				}
				
				output_module->Output(Geobrick1.RetrieveMessage());
				
				output_module->Output("I'm the SpaceFabServer and I have sent a command to GeoBrick\n");
			}
			
			//check_process: checks if CollSoft program exists.
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^2:.{1,30}$")
			|| reg_matches (buffer, "^2:.{1,30}$")) 
			{
				if (buffer[0] == '1')
				{
					string message_to_send(&buffer[2]);
					Geobrick2.Send(message_to_send);
				}
				else
				{
					string message_to_send(&command_received_by_user.command_sent_by_user[2]);
					Geobrick2.Send(message_to_send);
				}
				
				output_module->Output(Geobrick2.RetrieveMessage());
				
				output_module->Output("I'm the SpaceFabServer and I have sent a command to GeoBrick\n");
			}
			
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Cc][Oo][Nn][Nn][Ee][Cc][Tt]_1[ \t]*$")
			|| reg_matches (buffer, "^[Cc][Oo][Nn][Nn][Ee][Cc][Tt]_1[ \t]*$"))
			{
				output_module->Output("Connecting to GeoBrick 1\n");
				Geobrick1.Connect();
			}

			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Cc][Oo][Nn][Nn][Ee][Cc][Tt]_2[ \t]*$")
			|| reg_matches (buffer, "^[Cc][Oo][Nn][Nn][Ee][Cc][Tt]_2[ \t]*$"))
			{
				output_module->Output("Connecting to GeoBrick 2\n");
				Geobrick2.Connect();
			}
			
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Dd][Ii][Ss][Cc][Oo][Nn][Nn][Ee][Cc][Tt]_1[ \t]*$")
			|| reg_matches (buffer, "^[Dd][Ii][Ss][Cc][Oo][Nn][Nn][Ee][Cc][Tt]_1[ \t]*$"))
			{
				output_module->Output("Disconnecting to Geobrick 1\n");
				
				if (Geobrick1.Disconnect() == 0)
					output_module->Output("Disconnection to Geobrick 1 okay!\n");
				else
					output_module->Output("Disconnection problems with Geobrick 1 .\n");
			}

			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Dd][Ii][Ss][Cc][Oo][Nn][Nn][Ee][Cc][Tt]_2[ \t]*$")
			|| reg_matches (buffer, "^[Dd][Ii][Ss][Cc][Oo][Nn][Nn][Ee][Cc][Tt]_2[ \t]*$"))
			{
				output_module->Output("Disconnecting to Geobrick 2\n");
								
				if (Geobrick2.Disconnect() == 0)
					output_module->Output("Disconnection to Geobrick 2 okay!\n");
				else
					output_module->Output("Disconnection problems with Geobrick 2 .\n");
			}			
			
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Rr][Ee][Tt][Rr][Ii][Ee][Vv][Ee]_1[ \t]*$")
			|| reg_matches (buffer, "^[Rr][Ee][Tt][Rr][Ii][Ee][Vv][Ee]_1[ \t]*$"))
			{
				output_module->Output("Retrieving variables from Geobrick 1....\n");
				
				output_module->Output(Geobrick1.RetrieveCommonVariable());
			}			
			
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Rr][Ee][Tt][Rr][Ii][Ee][Vv][Ee]_2[ \t]*$")
			|| reg_matches (buffer, "^[Rr][Ee][Tt][Rr][Ii][Ee][Vv][Ee]_2[ \t]*$"))
			{
				output_module->Output("Retrieving variables from Geobrick 2....\n");
				
				output_module->Output(Geobrick2.RetrieveCommonVariable());
			}			
			
			else 
			{
				//output_module->Output("Error: unrecognized command.\n");
				
				if (command_received_by_user.command_sent_by_user[0] != 0)
				{
					string tmp(command_received_by_user.command_sent_by_user);
					output_module->Output("Error: unrecognized command '" + tmp + "'\n");
					//output_module->Output(string tmp(command_received_by_user.command_sent_by_user));
				}
				else
				{
					string tmp(buffer);
					output_module->Output("Error: unrecognized command '" + tmp + "'\n");
					//output_module->Output(string tmp(buffer));
				}
			}
			
			output_module->Output("END OF MESSAGE\n");						
		}
	}
}
