// 
//   Copyright (C) 2005 Free Software Foundation, Inc.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#include <net-snmp/net-snmp-config.h>
#ifdef HAVE_CONFIG_H
# undef PACKAGE_VERSION
# undef PACKAGE_TARNAME
# undef PACKAGE_STRING
# undef PACKAGE_NAME
# undef PACKAGE_BUGREPORT
// This is generated by autoconf.
# include "config.h"
#endif

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/time.h>
#include <iostream>

#if 0
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/scalar.h>
#endif

#include "err.h"
#include "snmp.h"
#include "proc.h"

#if 0
#include "ifTable.h"
#include "ifTable_data_access.h"
#include "ifTable_data_set.h"
#else
extern "C" {
# include "powerguru.h"
}
#endif

#define RETSIGTYPE void

using namespace std;

SnmpClient::SnmpClient()
{
}

SnmpClient::~SnmpClient()
{
}

retcode_t
SnmpClient::open(std::string init, std::string mibname)
{
  // PowerGuru
  init_snmp(init.c_str());

  snmp_sess_init( &_session );
  _session.version = SNMP_VERSION_1;
  _session.community = (u_char *)"public";
  _session.community_len = strlen((const char *)_session.community);
  //  _session.peername = _hostname.c_str();
  _handle = snmp_open(&_session);

  add_mibdir(".");
  // "XANTREX-MIB.txt"
  _mibtree = read_mib(mibname.c_str());

  _pdu = snmp_pdu_create(SNMP_MSG_GET);

  return SUCCESS;
}

retcode_t
SnmpClient::close(void)
{
  snmp_close(_handle);
  cerr << __PRETTY_FUNCTION__ << "ERROR: unimplemented!" << endl;
  return ERROR;
}

struct snmp_pdu *
SnmpClient::read(std::string mibnode)
{
  struct variable_list *vars;
  oid id_oid[MAX_OID_LEN];
  //  oid serial_oid[MAX_OID_LEN];
  //  size_t serial_len = MAX_OID_LEN;
  size_t id_len = MAX_OID_LEN;
  int status;                             

  // read_objid("XANTREX-MIB::xantrex.0", id_oid, &id_len);
  read_objid(mibnode.c_str(), id_oid, &id_len);
  snmp_add_null_var(_pdu, id_oid, id_len);

  status = snmp_synch_response(_handle, _pdu, &_response);
  
  for(vars = _response->variables; vars; vars = vars->next_variable) {
    print_value(vars->name, vars->name_length, vars);
  }
  
  snmp_free_pdu(_response);

  return _response;             // FIXME: this may be incorrect
}


static int keep_running;

RETSIGTYPE
stop_server(int a) {
    keep_running = 0;
}

SnmpDaemon::SnmpDaemon()
{
}

SnmpDaemon::~SnmpDaemon()
{
}


retcode_t
SnmpDaemon::master(bool background) {
  // print log errors to syslog or stderr
  snmp_enable_stderrlog();
  snmp_debug_init();  

  snmp_set_do_debugging(1);
  
  // run in the background
  Proc daemon;
  if (background) {
    daemon.Start("pgd");
    exit(1);
  }

  // initialize tcpip, if necessary
  SOCK_STARTUP;

  // initialize MIB agent
  init_agent("pgd");
  //init_mib_modules();
  
  // mib generated code
  init_powerguru();

#if 0
  // initialize vacm/usm access control
  init_vacm_vars();
  init_usmUser();
#endif
  
  init_snmp("pgd");

  snmp_store("pgd");
  
  // open the port to listen on (defaults to udp:161)
  init_master_agent();

  // In case we receive a request to stop (kill -TERM or kill -INT)
  keep_running = 1;
  signal(SIGTERM, stop_server);
  signal(SIGINT, stop_server);

  snmp_log(LOG_INFO,"powerguru is up and running.\n");

  // main loop
  while(keep_running) {
    // if you use select(), see snmp_select_info() in snmp_api(3)
    //     --- OR ---
    if (agent_check_and_process(1) > 0) { // 0 == don't block
      printf("GOT SNMP Message!\n");
    }
  }

  if (background) {
    //daemon.Stop("pgd");
  }
  
  snmp_shutdown("powerguru");
  SOCK_CLEANUP;

  return SUCCESS;
}

#if 0
retcode_t
SnmpDaemon::process(void)
{
  int             numfds, count;

  fd_set          readfds, writefds, exceptfds;
  struct timeval  timeout, *tvp = &timeout;
  int             block = 1;
  

  snmp_select_info(&numfds, &readfds, tvp, &block);
  netsnmp_external_event_info(&numfds, &readfds, &writefds, &exceptfds);
  netsnmp_dispatch_external_events(&count, &readfds,
                                   &writefds, &exceptfds);
  /* If there are still events leftover, process them */
  if (count > 0) {
    snmp_read(&readfds);
  }

  return SUCCESS;
}
#endif

#endif
