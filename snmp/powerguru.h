// 
// Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
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

/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.9 2005/01/07 09:37:18 dts12 Exp $
 */
#ifndef POWERGURU_H
#define POWERGURU_H

/*
 * function declarations 
 */
void            init_powerguru(void);
Netsnmp_Node_Handler handle_powerGuruDataLog;
Netsnmp_Node_Handler handle_powerGuruUnitAddress;
Netsnmp_Node_Handler handle_powerGuruChargeAmps;
Netsnmp_Node_Handler handle_powerGuruPVAmps;
Netsnmp_Node_Handler handle_powerGuruPVVolts;
Netsnmp_Node_Handler handle_powerGuruDailyKW;
Netsnmp_Node_Handler handle_powerGuruAuxMode;
Netsnmp_Node_Handler handle_powerGuruErrorMode;
Netsnmp_Node_Handler handle_powerGuruChargerMode;
Netsnmp_Node_Handler handle_powerGuruBatteryVolts;
Netsnmp_Node_Handler handle_powerGuruLoadAmps;
Netsnmp_Node_Handler handle_powerGuruACBuyAmps;
Netsnmp_Node_Handler handle_powerGuruACInputVolts;
Netsnmp_Node_Handler handle_powerGuruACOutputVolts;
Netsnmp_Node_Handler handle_powerGuruACSellAmps;

#endif                          /* POWERGURU_H */
