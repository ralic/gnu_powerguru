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

// This is generated by autoconf
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif


#include <stdarg.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <cstdio>
#include <iostream>

#include "dejagnu.h"
#include "tcpip.h"

using namespace std;

int verbosity;
static void usage (void);
bool waitforgdb = false;
static void cntrlc_handler (int);
static void alarm_handler (int);
static bool loop = true;

int proc_tests (string procname);
int start_proc (string procname);

TestState runtest;

int
main(int argc, char *argv[])
{
    int c;
    bool dump = false;
    string filespec;
    string procname, memname;
    char buffer[300];
    int retries = 3;

    memset(buffer, 0, 300);
    
    while ((c = getopt (argc, argv, "hdvsm:")) != -1) {
        switch (c) {
          case 'h':
            usage ();
            break;
            
          case 'd':
            dump = true;
            break;
            
          case 's':
            waitforgdb = true;
            break;
                                                                                
          case 'v':
            verbosity++;
            break;
            
          case 'm':
            memname = optarg;
            cerr << "Open " << memname << endl;
            break;
            
          default:
            usage ();
            break;
        }
    }
    
    // get the file name from the command line
    if (optind < argc) {
        filespec = argv[optind];
        cout << "Will use \"" << filespec << "\" for test " << endl;
    }


    Tcpip tcpip;
    const struct hostent  *host;
//    struct protoent *proto;
    const struct servent  *service;
    const struct protoent *proto;
    const struct in_addr  *addr;

    char hostname[MAXHOSTNAMELEN];
    gethostname(hostname, MAXHOSTNAMELEN);
    
    // See if we can do host lookups
    host = tcpip.hostDataGet();
    if (host == 0)
    {
        runtest.fail ("Tcpip::hostDataGet()");
        cerr << "ERROR: no hostname! Tests can't continue" << endl;
        exit(1);
    }
    
    addr = (struct in_addr *)host->h_addr_list[0];

#if 1
//    cerr << "Name is " << host->h_name << " IP is "
//         << inet_ntoa(*(struct in_addr *)host->h_addr_list[0]) << endl;
    
    cerr << "tcpip: Name is " << tcpip.hostNameGet() << " IP is " <<
        tcpip.hostIPNameGet() << endl;  
#endif
    
    if (strcmp(host->h_name, hostname) == 0)
        runtest.pass ("Tcpip::hostDataGet()");
    else
        runtest.fail ("Tcpip::hostDataGet()");

    if (host->h_name == tcpip.hostNameGet())
        runtest.pass ("Tcpip::hostNameGet()");
    else
        runtest.fail ("Tcpip::hostNameGet()");

    if ((in_addr_t *)host->h_addr_list[0] == tcpip.hostIPGet())
        runtest.pass ("Tcpip::hostIPGet()");
    else
        runtest.fail ("Tcpip::hostIPGet()");
    
    // See if we can do service lookups
    service = tcpip.lookupService("powerguru", "tcp");
    if (strcmp(service->s_name, "powerguru") == 0 &&
        strcmp(service->s_proto, "tcp") == 0 &&
        service->s_port == htons(7654))
        runtest.pass ("Tcpip::lookupService(powerguru)");
    else
        runtest.fail ("Tcpip::lookupService(powerguru)");

//    tcpip.toggleDebug(true);
    
    // See if we can do protocol lookups
    proto = tcpip.protoDataGet();
    if (strcmp(proto->p_name, "tcp") == 0 &&
        proto->p_proto == 6)
        runtest.pass ("Tcpip::protoDataGet()");
    else
        runtest.fail ("Tcpip::protoDataGet()");

    if (tcpip.protoNameGet() == "tcp")
        runtest.pass ("Tcpip::protoNameGet()");
    else
        runtest.fail ("Tcpip::protoNameGet()");

    if (tcpip.protoNumGet() == 6)
        runtest.pass ("Tcpip::protoNumGet()");
    else
        runtest.fail ("Tcpip::protoNumGet()");
    
    tcpip.createNetServer(7654);
    //    tcpip.createNetServer("powerguru");
    
#if 1
    int pid;
    // Run the memory tests between two processes
    if (procname.size() == 0)
        pid = start_proc("./childtcpip");
    else
        pid = proc_tests (procname);
    
    // sleep so the child process has time to run, and we have time to debug it. We setup a
    // handler for ^C, so we can get out of this sleep when we're done.
    if (waitforgdb) {
        struct sigaction  act2;
        act2.sa_handler = cntrlc_handler;
        sigaction (SIGINT, &act2, NULL);
        sleep(300);
    } else {
        sleep(1);
    }
#endif
    while (retries-- > 0)
    {
        retcode_t ts = tcpip.newNetConnection(true);
        if (ts)
            break;
        else
          // Under purify, things are very slow, so wait before retries
          sleep(10);
    }
    
    struct sigaction  act;
 
    act.sa_handler = alarm_handler;
    sigaction (SIGALRM, &act, NULL);

    alarm(5);

    cout << endl
         << "Waiting 5 seconds for input from the child process..." << endl;

    
    //    int bytes = ts->readNet((char *)&buffer, 300);
    int bytes;
    
    if (bytes > 0)
    {
        cout << "Parent read  from child" << endl << buffer << endl;
    }
    //ts->writeNet("FoobyDo!");
    sleep(1);
    tcpip.closeNet();
}
// Run the tests between two processes
int
start_proc (string procname)
{
    struct stat procstats;
    char *cmd_line[5];
    pid_t childpid;
    int ret = 0;
    
    // See if the file actually exists, otherwise we can't spawn it
    if (stat(procname.c_str(), &procstats) == -1) {
        cerr << "Invalid filename \"" << procname << "\"" <<endl;
        perror(procname.c_str());
        return -1;
    }
    
    // setup a command line. By default, argv[0] is the name of the process
    memset(cmd_line, 0, sizeof(char *)*5);
    cmd_line[0] = new char(50);
    strcpy(cmd_line[0], procname.c_str());
    if (waitforgdb) {
        cmd_line[1] = new char(3);
        strcpy(cmd_line[1], "-s");
    }
 
    // fork ourselves silly
    childpid = fork();
    
    
    // childpid is a positive integer, if we are the parent, and fork() worked
    if (childpid > 0) {
        cerr << "Forked sucessfully, child process PID is " << childpid << endl;
        return childpid;
    }
    
    // childpid is -1, if the fork failed, so print out an error message
    if (childpid == -1) {
        /* fork() failed */
        perror(procname.c_str());
        return -1;
    }
    
    // If we are the child, exec the new process, then go away
    if (childpid == 0) {
        // Start the desired executable
        cout << "Starting " << procname << " with " << cmd_line[0] << endl;
        ret = execv(procname.c_str(), cmd_line);
        perror(procname.c_str());
        exit(0);
    }
    return 0;
}

// Run the memory tests between two processes
int
proc_tests (string procname)
{
    return start_proc(procname);
}
 
void
cntrlc_handler (int sig)
{
  cerr << "Got a ^C !" << endl;
}

void
alarm_handler (int sig)
{
  cerr << "Got an alarm signal !" << endl;
  cerr << "This is OK, we use it to end this test case." << endl;
  loop = false;
}

static void
usage (void)
{
    cerr << "This program tests the Global memory system." << endl;
    cerr << "Usage: tglobal [h] filename" << endl;
    cerr << "-h\tHelp" << endl;
    cerr << "-d\tDump parsed data" << endl;
    exit (-1);
}
