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

int main ()
{

	//At the beginning of this program it could be useful to check if an istance is already running. But it isn't actually 
	//a problem: the CheckExistence program work also with two or more istance (maybe you have to check socket error...)
	pid_t fork_id = fork();
	
	if (fork_id > 0) {
		fprintf(stderr, "Check Esistence daemon successfully start\n");
		return 0;
	} else if (fork_id < 0) {
		fprintf(stderr, "Check Esistence daemon not started: fork failed\n");
		return 1;	
	}
	
	OutputModule *output_module;
	output_module = OutputModule::Instance ();
	
	TcpUser command_received_by_user;
	CommunicationObject mioTCP;
	mioTCP.CommunicationObjectInit ();  
	
	
	//The program never stop: it must be killed to stop it
	while (1)
	{
		
		//Sleep to make the fetching input cycle slower in order to preserve CPU resources.
		usleep(100000);

		//Get tcp/ip input
		command_received_by_user = mioTCP.GetCommand ();

		//If tcp/ip input is not empty
		if (command_received_by_user.command_sent_by_user[0] != 0)
		{
			output_module->OutputModuleStdoutOff();
			output_module->OutputModuleSockidOn(command_received_by_user.user_sockid);
		}

		//If tcp/ip input is not empty
		if (command_received_by_user.command_sent_by_user[0] != 0)
		{		
			//ON: checks if CollSoft program exists, if not creates an instance of it.
			if(reg_matches (command_received_by_user.command_sent_by_user, "^[Oo][Nn][ \t]*$")) 
			{
				
			   int rc1;
			   rc1 = system("pidof -x SpaceFabServer > /dev/null");
			   
			   if(rc1 == 0) {
				  output_module->Output("SpaceFabServer is already running:\n");
			   }
			   else if(rc1 != 0) {
				   
					pid_t childPID = fork();
					
					//if I'm the child
					if (childPID == 0) {
						
						//If check_existence died, CollSoft died
						int r = prctl(PR_SET_PDEATHSIG, SIGTERM);
						if (r == -1) { perror(0); exit(1); }
						
						setsid();
						execl(SPACEFAB_PATH, "SpaceFabServer", NULL); //Qui c'e' un problema di hard coding!!!!
					}
					
					usleep(100000);
					
					rc1 = system("pidof -x SpaceFabServer > /dev/null");
					
					if (rc1 == 0)
					{
					output_module->Output("New SpaceFabServer process created successfully");
					}
					
				}
			}
			//OFF: checks if CollSoft program exists, if yes kills it.
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Oo][Ff][Ff][ \t]*$")) 
			{
				char line[STANDARDBUFFERLIMIT];
				bzero(line, STANDARDBUFFERLIMIT);
				FILE *cmd = popen("pidof SpaceFabServer", "r");

				fgets(line, STANDARDBUFFERLIMIT, cmd);
				pid_t pid = strtoul(line, NULL, 10);

				pclose(cmd);
				
				if (pid != 0) {
					kill(pid, SIGKILL);
					output_module->Output("Killing SpaceFabServer process (pid is " + to_string(pid) + ")...");
					int status;
					waitpid(pid, &status, 0);
					output_module->Output("...SpaceFabServer processed killed.");
				}
				else
				{
					output_module->Output("SpaceFabServer process is not running:\nI can't kill it");
				}
				
			}
			
			//CHECK: checks if CollSoft program exists.
			else if(reg_matches (command_received_by_user.command_sent_by_user, "^[Cc][Hh][Ee][Cc][Kk][ \t]*$")) 
			{
			   int rc1;
			   rc1 = system("pidof -x SpaceFabServer > /dev/null");
			   
			   if(rc1 == 0) {
				  output_module->Output("SpaceFabServer is running");
			   }
			   else if(rc1 != 0) {
				   
				   output_module->Output("SpaceFabServer is not running");
			   }
			   else {
			       output_module->Output("Check existence has not check the presence of SpaceFabServer!!!");
			   }
			   
			}				
			
			else 
			{
				output_module->Output("Error: unrecognized command.");
			}
			
			output_module->Output("END OF MESSAGE\n");						
		}
	}
}
