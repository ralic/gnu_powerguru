// 
// Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011
//      Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

// This is generated by autoconf
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

// system header files
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include <string>
#include <fstream>
#include <ostream>
#include <iostream>

// project header files
#include "err.h"
#include "log.h"
#include "serial.h"

using namespace std;

extern LogFile dbglogfile;
LogFile seriallogfile; // ("tserial.log")

// Set the names of the baud rates so we can dump them in a human
// readable fashion.
const char *serial_speeds[] = {
    "B0",
    "B50",
    "B75",
    "B110",
    "B134",
    "B150",
    "B200",
    "B300",
    "B600",
    "B1200",
    "B1800",
    "B2400",
    "B4800",
    "B9600",
    "B19200",
    "B38400",
    "B57600",
    "B115200",
    "B230400"
};


// Translate baud rates from integers to damn B_codes.
struct damnbaud {
    int rate;
    int code;
};
struct damnbaud baudtab[] = {
    {50, B50},
    {75, B75},
    {110, B110},
    {134, B134},
    {150, B150},
    {200, B200},
    {300, B300},
    {600, B600},
    {1200, B1200},
    {1800, B1800},
    {2400, B2400},
    {4800, B4800},
    {9600, B9600},
    {19200, B19200},
    {38400, B38400},
#ifdef B57600
    {57600, B57600},
#endif
#ifdef B115200
    {115200, B115200},
#endif
    {-1, -1},
};

int
rate_to_code(int rate) {
    int i;

    for (i = 0; baudtab[i].rate != -1; i++)
        if (rate == baudtab[i].rate)
            return baudtab[i].code;

    return -1;
}

Serial::Serial(void)
{
    // DEBUGLOG_REPORT_FUNCTION;

    // FIXME: for some reason, on Solaris 2.5.1, the static constructor
    // doesn't work, and we have to reopen it to get things to really work.
    seriallogfile.Open ("tserial.log");

}

Serial::~Serial(void)
{
    // DEBUGLOG_REPORT_FUNCTION;
    //Close();
}

// Open the serial port. This function must initialize the serial port so that
// it can be read/write in raw mode.
retcode_t
Serial::Open(string name)
{
    return Open(name.c_str());
}


retcode_t
Serial::Open(const char *filespec)
{
    DEBUGLOG_REPORT_FUNCTION;
  
    dbglogfile << "Opening host device " << filespec << endl;

    // We don't want to timestamp
    seriallogfile.SetStamp(false);

    seriallogfile << "<?xml version='1.0'?>" << endl;
    seriallogfile << "<device>\"" << filespec << "\"</device>" << endl;
  
    //  serialin.open(name, ios::in|ios::out);

    if (filespec != 0) {
        if ((_uartfd = open(filespec, O_RDWR | O_NONBLOCK)) < 0) { //  | O_NONBLOCK
            if (_uartfd < 0) {
                errcond << "couldn't open " << filespec << endl;
                throw errcond;
            }
        }
    }

    uartfile = fdopen(_uartfd, "w+");

    // store the tty configuration so we can reset it when we're done
    tcgetattr(_uartfd, &origtty);

    // for now, this is also the current settings
    tcgetattr(_uartfd, &currenttty);
  
    DumpTtyState();
  
    // set to raw mode, so all I/O is unbuffered
    //SetRaw();

#if 0
    // set the timeout value for communications
    if (SetTimeout (20, errcond) == ERROR) {
        dbglogfile << "ERROR: Couldn't set the timeout value";
        return ERROR;
    }
    DumpTtyState();
#endif

    return SUCCESS;
}

// Close the serial port
retcode_t
Serial::Close(void)
{
    DEBUGLOG_REPORT_FUNCTION;
  
    dbglogfile << endl << "Closing host device" << endl;
    seriallogfile << endl << "Closing host device" << endl;

    tcsetattr(_uartfd, TCSANOW, &origtty);

    ::close (_uartfd);

    _uartfd = -1;
    uartfile = 0;
  
    return ERROR;
}

retcode_t
Serial::Flush  (void)
{
    tcflush(_uartfd, TCIOFLUSH);

    return SUCCESS;               // FIXME: this should be a real check
}

int
Serial::Read(char *buf, int nbytes)
{
    //DEBUGLOG_REPORT_FUNCTION;

    int ret, sret, i;
    fd_set fdset;
    int retries = 2;
    string data;
    struct timeval timeout;

    ret = -1;
    char *tmpbuf = new char[nbytes+1];
    if (_uartfd > 0) {

        // Wait till we know there's data
        while (retries-- > 0) {
            timeout.tv_sec = 2;
            timeout.tv_usec = 20;  // 1500
      
            FD_ZERO(&fdset);
            FD_SET(_uartfd, &fdset);
      
            sret = select(_uartfd+1, &fdset, NULL, NULL, &timeout);
            dbglogfile << "select returned " << sret
                       << " for file descriptor  " << _uartfd << endl;
#if 1
            if (sret == 0) {
                memset(buf, 0, nbytes);
                //seriallogfile << "<device><select>Timeout</select></device>" << endl;
                return sret;
            }
            if ((sret < 0) && (errno == EAGAIN)) {
                memset(buf, 0, nbytes);
                return sret;
            }
#endif
      
            memset(tmpbuf, 0, nbytes+1);
            memset(buf, 0, nbytes);
            ret = ::read (_uartfd, tmpbuf, nbytes);
            dbglogfile << "read returned " << ret << " for file descriptor  " << _uartfd << endl;
            if (ret == 0) {
                continue;
            }
      
            if (ret > 0) {
                dbglogfile << "Read " << ret << " bytes" << endl;
                //if ((line.find('\n', 0) == string::npos) && (ret > 0)) 
                // Filter out the control characters that appear on the
                // end of the line
                for (i=0; i<ret; i++) {
                    if (isascii(tmpbuf[i])) {
                        if ((tmpbuf[i] == 10) || (tmpbuf[i] == 13)) {
                            continue;
                        }
                        data += tmpbuf[i];
                    }
                } // end of for loop
                // dbglogfile << "Reading more data, data left before is \"" << tmpbuf << "\"" << endl;
            }
      
            //if (ret < 0)
            {
                //data = line.substr(0, line.find('\n', 0));
                if (data.size() > 0) {
                    seriallogfile << "<read time=" << timestamp()
                                  << " bytes=" << (int)data.size()
                                  << ">" << data << "</read>" << endl;
          
                    memcpy(buf, data.c_str(), data.size());
                    return data.size();
                }
            }
        }
    
        memcpy(buf, data.c_str(), data.size());
        return ret;
    }
  
  
#if 0                
                  
        
    //if ((ret == 1) && (ret == 0xa)) {
    if (ret == 1) {
        dbglogfile << "Read CR " << endl;
        //ret = ::read (_uartfd, buf, 36);
    }
        
    if (ret > 0) {
        dbglogfile << "Read " << ret << " bytes" << endl;
        for (i=0; i< nbytes; i++){
#if 0
            if (buf[i] == 0xa) {
                buf[i] = ' ';
                continue;
            }
#endif
            if ((buf[i] > ' ') && (buf[i] < 'z')) {
                dbglogfile << "Copying character: " << i << endl;
                *bufptr++ = buf[i];
            } else {
                buf[i] = ' ';
            }
        }
        *bufptr = 0;
        seriallogfile << "<read  time=" << timestamp()
                      << " bytes=" << ret
                      << ">" << buf << "</read>" << endl;
    }
}

if ((sret == 0) && (ret <= 0)) {
    dbglogfile << "WARNING: Too many retries." << endl;
}

//    seriallogfile.Write((const char *)buf, ret);

//seriallogfile << "<read>" << buf << "</read>" << endl;
} else {
      return ERROR;
  }
#endif

return ret;
}

int
Serial::Write(const char *buf, int nbytes) const
{
    //DEBUGLOG_REPORT_FUNCTION;
    int ret;
  
    // Sometimes Iostreams are so weird... To make read/write
    // stream, we need to make the output stream use the input streams
    // buffer.
    //  ostream outserial (serialin.rdbuf());
  
    if (_uartfd > 0) {
        ret = ::write (_uartfd, buf, nbytes);
        tcdrain(_uartfd);
        //    seriallogfile.write((const char *)buf, ret);
        //   seriallogfile << buf;
        seriallogfile << "<write time=" << timestamp()
                      << " bytes=" << ret
                      << ">" << buf << "</write>" << endl;
        return nbytes;
    } else {
        return -1;
    }
}

retcode_t
Serial::SetBaud (int baudcode)
{
    DEBUGLOG_REPORT_FUNCTION;
  
    speed_t ibaud;
    speed_t obaud;
    termios ctty;

    tcgetattr(_uartfd, &ctty);
#if 0
    currenttty.c_cflag &= ~(CBAUD|CIBAUD);
    currenttty.c_cflag |= baudcode;  
#else
    cfsetispeed(&ctty, baudcode);
    cfsetospeed(&ctty, baudcode);
#endif
    int ret = tcsetattr(_uartfd, TCSANOW, &ctty);
    if (ret == 0) {
        dbglogfile << __PRETTY_FUNCTION__ << " worked" << endl;
        return SUCCESS;
    }
  
    seriallogfile << "<device><baud>\"" << serial_speeds[baudcode] << "\"</baud></device>" << endl;

    // See if it worked
    //int ret = tcsetattr(_uartfd, TCSADRAIN, &currenttty);
    ibaud = cfgetispeed(&currenttty);
    obaud = cfgetospeed(&currenttty);
    dbglogfile << "Input baud is now set to " << serial_speeds[ibaud] << endl;
    dbglogfile << "Output baud is now set to " << serial_speeds[obaud] << endl;

    dbglogfile << __PRETTY_FUNCTION__ << " failed" << endl;
    return ERROR;
}

#if 0
retcode_t
Serial::send_break (struct errcond *err) const
{
    DEBUGLOG_REPORT_FUNCTION;
    
    tcsendbreak (Device::fd, 0);

    return SUCCESS;
}
#endif

retcode_t
Serial::SetBlocking(bool mode)
{
    tcgetattr(_uartfd, &currenttty);
  
    //seriallogfile << "<device><blocking>True</device>" << endl;

    currenttty.c_cc[VMIN] = 0;
    currenttty.c_cc[VTIME] = 10;
  
    tcsetattr(_uartfd, TCSANOW, &currenttty);

    return SUCCESS;               // FIXME: this should be a real check
}

//  modem control lines
// TIOCM_LE, TIOCM_DTR, TIOCM_RTS, TIOCM_ST, TIOCM_SR, TIOCM_CTS,
// TIOCM_CAR, TIOCM_RNG, TIOCM_DSR, TIOCM_CD, TIOCM_RI,
// TIOCM_OUT1,IOCM_OUT2, TIOCM_LOOP
retcode_t
Serial::SetDTR (void)
{
    return SetDTR(true);
}

retcode_t
Serial::SetDTR (bool value)
{
    int arg = 0;

    ioctl(_uartfd, TIOCMGET, (unsigned long) &arg);

    cerr << "ARG is " << arg << endl;
  
    // Turn off everything but DTR
    if (value) {  
        seriallogfile << "<device><DTR>True</DTR></device>" << endl;
        arg = TIOCM_DTR;
    } else { 
        seriallogfile << "<device><DTR>False</DTR></device>" << endl;
        arg = 0;
    }
    // arg |= TIOCM_DTR | ~TIOCM_RTS;

    ioctl(_uartfd, TIOCMSET, (unsigned long) &arg);

    return SUCCESS;               // FIXME: this should be a real check
}

retcode_t
Serial::SetRaw (void)
{
    DEBUGLOG_REPORT_FUNCTION;
  
    // speed 38400 baud; line = 0;
    // min = 1; time = 0;
    // ignbrk -brkint -icrnl -imaxbel
    // -opost
    // -isig -icanon -iexten -echo
  
    tcgetattr(_uartfd, &currenttty);

#if 1
    cfmakeraw(&currenttty);
#else
    //currenttty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
    currenttty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP);
    currenttty.c_oflag &= ~OPOST;
    currenttty.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
    currenttty.c_cflag &= ~(CSIZE|PARENB);
    currenttty.c_cflag |= CS8;
    currenttty.c_cc[VMIN] = 0;
    currenttty.c_cc[VTIME] = 10;
#endif
  
    tcsetattr(_uartfd, TCSANOW, &currenttty);

    return SUCCESS;               // FIXME: this should be a real check
}

void
Serial::DumpTtyState (void)
{
    DEBUGLOG_REPORT_FUNCTION;
    int ibaud, obaud;

    ibaud = cfgetispeed(&currenttty);
    dbglogfile << "Input baud rate is " << serial_speeds[ibaud] << endl;

    obaud = cfgetospeed(&currenttty);
    dbglogfile << "Output baud rate is " << serial_speeds[obaud] << endl;
  
}

termios *
Serial::SetTtyState (termios *tty)
{
    DEBUGLOG_REPORT_FUNCTION;

    tcsetattr(_uartfd, TCSANOW, tty);
    return &currenttty;
}

termios *
Serial::GetTtyState(void)
{
    DEBUGLOG_REPORT_FUNCTION;

    tcgetattr(_uartfd, &currenttty);
    return &currenttty;
}

// These methods do byte oriented I/O on the serial port
int
Serial::Getc   (void)
{ 
    // DEBUGLOG_REPORT_FUNCTION;
    if (uartfile != NULL)
        return getc(uartfile);
    else
        return -1;
}

int
Serial::UnGetc (int ch)
{  
    // DEBUGLOG_REPORT_FUNCTION;
    if (uartfile != NULL)
        return ungetc(ch, uartfile);
    else
        return -1;
}

int
Serial::Putc (int x)
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (uartfile != NULL) {
        return putc(x, uartfile);
    } else {
        return -1;
    }
}

// This grabs the endl operator. If we see this, then we are done
// formatting the string. We currently don't do anything with this.
ostream&
Serial::operator << (ostream & (&)(ostream &)) {
    ostream outserial (serialin.rdbuf());
    outserial.write("\n", 1);
    return cout;                  // FIXME: this is probably bogus
}

Serial& 
Serial::operator << (char const *x)
{
    DEBUGLOG_REPORT_FUNCTION;

    ostream outserial (serialin.rdbuf());
    outserial.write(x, strlen(x));

    seriallogfile << x;

    return *this;
}

Serial& 
Serial::operator << (string &x)
{
    DEBUGLOG_REPORT_FUNCTION;

    ostream outserial (serialin.rdbuf());

    //outserial.write(x, x.length());

    seriallogfile << x;
  
    return *this;
}

ostream& 
operator << (ostream &os, Serial& e)
{
    DEBUGLOG_REPORT_FUNCTION;

    string msg;

#if 0
    if (e.GetCode() > EMEDIUMTYPE) {
        msg = "WARNING: ";
    } else {
        msg = "ERROR: ";
    }
  
    if (e.GetFunc().size() > 0)
        msg += e.GetFunc();

    if (e.GetLine() > 0)
        msg += e.GetFunc();
  
    if (e.GetMsg().size() > 0)
        msg += e.GetMsg();

    if (errno) {
        msg += " (";
        msg += strerror(errno);
        msg += ") ";
    }
#endif
  
    return os << msg;
}

// local Variables:
// mode: C++
// indent-tabs-mode: nil
// End:
