/*
 * config.h
 *
 *  Created on: 26.07.2017
 *      Author: de1m
 */

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#endif /* MAIN_CONFIG_H_ */

#include <string.h>
#include <stdlib.h>
#include "esp_system.h"

struct wCLIENTCFG {
	char ssid[32];
	char password[64];
	char ip[15];
	char netmask[15];
	char gw[15];
	char dns1[15];
	char dns2[15];
};

struct icinInfo {
	char *identity;
	int hostack; 	//host acknowlege
	int hostdown; 	//host down
	int hostflap;	//host flapping
	int hostindt; 	//host in downtime
	int hostpend; 	//host in pending
	int hostunre; 	//host unreachable
	int hostup; 	//host up;
	int hostall;	//number of hosts

	int servack; 	//service acknowlege
	int servcrit; 	//service critical
	int servflap;	//service flapping
	int servindt;	//service in downtime
	int servok;		//service ok
	int servpend;	//service pending
	int servunkn;	//service unknown
	int servunre;	//service unreachable
	int servwarn;	//service warning
	int servall;	//number of all services
};
