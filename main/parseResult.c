/*
 * parseResult.c
 *
 *  Created on: 26.07.2017
 *      Author: de1m
 */

#include "config.h"

char* readValue(char *buf, char *searchstr, int numValue)
{
    int searchStrLen = strlen(searchstr);
    int startStr, endStr;
	int idx = 0;
    char *identity = strstr(buf, searchstr);
    char *tempbuf;

    int index = (int)(identity - buf);
    int endSearchString = index + searchStrLen;

    while(*identity++ != ','){
        idx++;
    }

    if(numValue == 1){
      startStr = endSearchString + 2;
      endStr = endSearchString + idx - searchStrLen - 3;
    } else {
      startStr = endSearchString + 2;
      endStr = endSearchString + idx - searchStrLen - 2;
    }

    int bufsize = endStr - startStr;
    if(bufsize == 0){
    	bufsize = 1;
    }

    int count = startStr;
    int returnCount = 0;

    if ((tempbuf = malloc(sizeof(char) * bufsize)) == NULL){
    	return (NULL);
    }

    for(count = startStr; count <= endStr; count++){
        tempbuf[returnCount] = buf[count];
        returnCount++;
    }

	return tempbuf;
}

struct icinInfo parseInput (char *buf, int buflen){

	struct icinInfo ic2;


	ic2.hostack 	= atoi(readValue(buf, "num_hosts_acknowledged", 1));
	ic2.hostflap	= atoi(readValue(buf, "num_hosts_flapping",1));
	ic2.hostdown 	= atoi(readValue(buf, "num_hosts_flapping",1));
	ic2.hostindt	= atoi(readValue(buf, "num_hosts_in_downtime",1));
	ic2.hostpend	= atoi(readValue(buf, "num_hosts_pending",1));
	ic2.hostunre	= atoi(readValue(buf, "num_hosts_unreachable",1));
	ic2.hostup		= atoi(readValue(buf, "num_hosts_up",1));
	ic2.hostall 	= ic2.hostack + ic2.hostflap + ic2.hostdown + ic2.hostindt + ic2.hostpend + ic2.hostunre + ic2.hostup;

	ic2.servack 	= atoi(readValue(buf, "num_services_acknowledged",1));
	ic2.servcrit	= atoi(readValue(buf, "num_services_critical",1));
	ic2.servflap	= atoi(readValue(buf, "num_services_flapping",1));
	ic2.servindt	= atoi(readValue(buf, "num_services_in_downtime",1));
	ic2.servok		= atoi(readValue(buf, "num_services_ok",1));
	ic2.servpend	= atoi(readValue(buf, "num_services_pending",1));
	ic2.servunkn	= atoi(readValue(buf, "num_services_unknown",1));
	ic2.servunre	= atoi(readValue(buf, "num_services_unreachable",1));
	ic2.servwarn	= atoi(readValue(buf, "num_services_warning",1));
	ic2.servall		= ic2.servack + ic2.servcrit + ic2.servflap + ic2.servindt + ic2.servok + ic2.servpend + ic2.servunkn + ic2.servunre + ic2.servwarn;

//	printf("\n########## IC2 Services all ##########\n%d\n", ic2.servall);
//	printf("\n########## IC2 Hosts all ##########\n%d\n", ic2.hostall);

	return ic2;
}


