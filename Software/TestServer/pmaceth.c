/***************************************************************************
 *   Copyright (C) 2006 by root   *
 *   root@esrhb04.external.hp.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct tagEthernetCmd
{
  u_int8_t   RequestType;
  u_int8_t   Request;
  u_int16_t  wValue;
  u_int16_t  wIndex;
  u_int16_t  wLength;
  u_int8_t   bData[1492];
} ETHERNETCMD,*PETHERNETCMD;

#define ETHERNETCMDSIZE 8

#define VR_PMAC_GETRESPONSE 0xBF
#define VR_UPLOAD        0xC0
#define VR_DOWNLOAD      0x40

int main(int argc, char *argv[])
{
  int result,sock,length;
  struct sockaddr_in client;
  ETHERNETCMD EthCmd;
  char cCommand[256],cResponse[2048];

  printf("PMAC Ethernet communication test\n");

  sock = socket (PF_INET,SOCK_STREAM, 0);
//client.sin_addr.s_addr = inet_addr("192.6.94.5");
  client.sin_addr.s_addr = inet_addr("127.0.0.1");
  client.sin_family = PF_INET;
  client.sin_port = htons(1025);
  //client.sin_port = htons(1112);
  length = sizeof(client);
  
  result = connect (sock,(__CONST_SOCKADDR_ARG)&client, (socklen_t)length);
  if(result ==0)
    printf("connect successful\n");
  else
    printf("connect failed with result = %d\n",result);

  EthCmd.RequestType = VR_DOWNLOAD;
  EthCmd.Request     = VR_PMAC_GETRESPONSE;
  EthCmd.wValue      = 0;
  EthCmd.wIndex      = 0;
  //strcpy(cCommand,"RHX$0");
  //strcpy(cCommand,"RHX$0");
  strcpy(cCommand,"VERSION");
  EthCmd.wLength     = htons((u_int16_t)strlen((const char*)cCommand));
  strncpy((char*)&EthCmd.bData[0],cCommand,strlen(cCommand));

  printf("Attempting Get Response\n");
  send(sock,(char*)&EthCmd,ETHERNETCMDSIZE + strlen(cCommand),0);
  recv(sock,cResponse,1400,0);
  printf(" %s:%s \n",cCommand,cResponse);

  printf("Done \n");
  shutdown (sock,SHUT_RDWR);


  return EXIT_SUCCESS;
}
