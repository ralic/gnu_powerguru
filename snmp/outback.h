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

/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.9 2005/01/07 09:37:18 dts12 Exp $
 */
#ifndef OUTBACK_H
#define OUTBACK_H

/* function declarations */
void            init_outback(void);
Netsnmp_Node_Handler handle_outbackMXAddress;
Netsnmp_Node_Handler handle_outbackMXChargeAmps;
Netsnmp_Node_Handler handle_outbackMXPVVolts;
Netsnmp_Node_Handler handle_outbackMXDailyKW;
Netsnmp_Node_Handler handle_outbackMXAuxMode;
Netsnmp_Node_Handler handle_outbackMXErrorMode;
Netsnmp_Node_Handler handle_outbackMXChargerMode;
Netsnmp_Node_Handler handle_outbackMXBatteryVolts;
Netsnmp_Node_Handler handle_outbackFXAddress;
Netsnmp_Node_Handler handle_outbackFXLoadAmps;
Netsnmp_Node_Handler handle_outbackFXChargeAmps;
Netsnmp_Node_Handler handle_outbackFXBuyAmps;
Netsnmp_Node_Handler handle_outbackFXInputVolts;
Netsnmp_Node_Handler handle_outbackFXOutputVolts;
Netsnmp_Node_Handler handle_outbackFXSellAmps;
Netsnmp_Node_Handler handle_outbackFXOpMode;
Netsnmp_Node_Handler handle_outbackFXErrorMode;
Netsnmp_Node_Handler handle_outbackFXACMode;
Netsnmp_Node_Handler handle_outbackFXBatteryVolts;
Netsnmp_Node_Handler handle_outbackFXMiscByte;
Netsnmp_Node_Handler handle_outbackFXWarningMode;
Netsnmp_Node_Handler handle_outbackFXCommand;

#endif                          /* OUTBACK_H */

// local Variables:
// mode: C++
// indent-tabs-mode: nil
// End:
