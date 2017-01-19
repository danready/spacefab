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
#include <sys/socket.h>
#include <netinet/in.h>

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
//~ 
	//~ //At the beginning of this program it could be useful to check if an istance is already running. But it isn't actually 
	//~ //a problem: the CheckExistence program work also with two or more istance (maybe you have to check socket error...)
	//~ pid_t fork_id = fork();
	//~ 
	//~ if (fork_id > 0) {
		//~ fprintf(stderr, "Check Esistence daemon successfully start\n");
		//~ return 0;
	//~ } else if (fork_id < 0) {
		//~ fprintf(stderr, "Check Esistence daemon not started: fork failed\n");
		//~ return 1;	
	//~ }
	
	
	ApplicationSetup *main_application_setup;
	main_application_setup = ApplicationSetup::Instance ();
	main_application_setup->FetchInputMode(main_application_setup->application_setup_input_mode);
	
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
		  
			//~ //check_process: checks if CollSoft program exists.
			//~ if(reg_matches (command_received_by_user.command_sent_by_user, "^[Cc][Hh][Ee][Cc][Kk]_[Pp][Rr][Oo][Cc][Ee][Ss][Ss][ \t]*$")) 
			//~ {
			   //~ int rc1;
			   //~ rc1 = system("pidof -x CollSoft > /dev/null");
			   //~ 
			   //~ if(rc1 == 0) {
				  //~ output_module->Output("CollSoft is running");
			   //~ }
			   //~ else if(rc1 != 0) {
				   //~ 
				   //~ output_module->Output("CollSoft is not running");
			   //~ }
			   //~ else {
			       //~ output_module->Output("Check existence has not check the presence of CollSoft!!!");
			   //~ }
			   //~ 
			//~ }

			int casual_number = 0;
			srand(time(NULL));
			casual_number = rand() % 10000;
				
			output_module->Output(to_string(casual_number));

		}
	}
}
