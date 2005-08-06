/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf,v 1.9 2005/01/07 09:37:18 dts12 Exp $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "powerguru.h"

int unimplemented;
/** Initializes the powerguru module */
void
init_powerguru(void)
{
    static oid      powerGuruDataLog_oid[] = { 1, 3, 6, 1, 4, 1, 8072, 1 };
    static oid      powerGuruUnitAddress_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 3 };
    static oid      powerGuruChargeAmps_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 4 };
    static oid      powerGuruPVAmps_oid[] = { 1, 3, 6, 1, 4, 1, 8072, 5 };
    static oid      powerGuruPVVolts_oid[] = { 1, 3, 6, 1, 4, 1, 8072, 6 };
    static oid      powerGuruDailyKW_oid[] = { 1, 3, 6, 1, 4, 1, 8072, 7 };
    static oid      powerGuruAuxMode_oid[] = { 1, 3, 6, 1, 4, 1, 8072, 8 };
    static oid      powerGuruErrorMode_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 9 };
    static oid      powerGuruChargerMode_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 10 };
    static oid      powerGuruBatteryVolts_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 11 };
    static oid      powerGuruLoadAmps_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 12 };
    static oid      powerGuruACBuyAmps_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 13 };
    static oid      powerGuruACInputVolts_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 14 };
    static oid      powerGuruACOutputVolts_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 15 };
    static oid      powerGuruACSellAmps_oid[] =
        { 1, 3, 6, 1, 4, 1, 8072, 16 };

    DEBUGMSGTL(("powerguru", "Initializing\n"));

    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruDataLog", handle_powerGuruDataLog,
                             powerGuruDataLog_oid,
                             OID_LENGTH(powerGuruDataLog_oid),
                             HANDLER_CAN_RWRITE));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruUnitAddress",
                             handle_powerGuruUnitAddress,
                             powerGuruUnitAddress_oid,
                             OID_LENGTH(powerGuruUnitAddress_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruChargeAmps",
                             handle_powerGuruChargeAmps,
                             powerGuruChargeAmps_oid,
                             OID_LENGTH(powerGuruChargeAmps_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruPVAmps", handle_powerGuruPVAmps,
                             powerGuruPVAmps_oid,
                             OID_LENGTH(powerGuruPVAmps_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruPVVolts", handle_powerGuruPVVolts,
                             powerGuruPVVolts_oid,
                             OID_LENGTH(powerGuruPVVolts_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruDailyKW", handle_powerGuruDailyKW,
                             powerGuruDailyKW_oid,
                             OID_LENGTH(powerGuruDailyKW_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruAuxMode", handle_powerGuruAuxMode,
                             powerGuruAuxMode_oid,
                             OID_LENGTH(powerGuruAuxMode_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruErrorMode",
                             handle_powerGuruErrorMode,
                             powerGuruErrorMode_oid,
                             OID_LENGTH(powerGuruErrorMode_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruChargerMode",
                             handle_powerGuruChargerMode,
                             powerGuruChargerMode_oid,
                             OID_LENGTH(powerGuruChargerMode_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruBatteryVolts",
                             handle_powerGuruBatteryVolts,
                             powerGuruBatteryVolts_oid,
                             OID_LENGTH(powerGuruBatteryVolts_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruLoadAmps", handle_powerGuruLoadAmps,
                             powerGuruLoadAmps_oid,
                             OID_LENGTH(powerGuruLoadAmps_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruACBuyAmps",
                             handle_powerGuruACBuyAmps,
                             powerGuruACBuyAmps_oid,
                             OID_LENGTH(powerGuruACBuyAmps_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruACInputVolts",
                             handle_powerGuruACInputVolts,
                             powerGuruACInputVolts_oid,
                             OID_LENGTH(powerGuruACInputVolts_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruACOutputVolts",
                             handle_powerGuruACOutputVolts,
                             powerGuruACOutputVolts_oid,
                             OID_LENGTH(powerGuruACOutputVolts_oid),
                             HANDLER_CAN_RONLY));
    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("powerGuruACSellAmps",
                             handle_powerGuruACSellAmps,
                             powerGuruACSellAmps_oid,
                             OID_LENGTH(powerGuruACSellAmps_oid),
                             HANDLER_CAN_RONLY));
}

int
handle_powerGuruDataLog(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *reqinfo,
                        netsnmp_request_info *requests)
{
    int             ret;
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */4 );
        break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
    case MODE_SET_RESERVE1:
        /*
         * or you could use netsnmp_check_vb_type_and_size instead 
         */
        ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
        if (ret != SNMP_ERR_NOERROR) {
            netsnmp_set_request_error(reqinfo, requests, ret);
        }
        break;

    case MODE_SET_RESERVE2:
        /*
         * XXX malloc "undo" storage buffer 
         */
        if ( unimplemented /* XXX if malloc, or whatever, failed: */ ) {
            netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_ERR_RESOURCEUNAVAILABLE);
        }
        break;

    case MODE_SET_FREE:
        /*
         * XXX: free resources allocated in RESERVE1 and/or
         * RESERVE2.  Something failed somewhere, and the states
         * below won't be called. 
         */
        break;

    case MODE_SET_ACTION:
        /*
         * XXX: perform the value change here 
         */
        if ( unimplemented /* XXX: error? */ ) {
            netsnmp_set_request_error(reqinfo, requests, /* some error */
                                      unimplemented);
        }
        break;

    case MODE_SET_COMMIT:
        /*
         * XXX: delete temporary storage 
         */
        if ( unimplemented /* XXX: error? */ ) {
            /*
             * try _really_really_ hard to never get to this point 
             */
            netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_ERR_COMMITFAILED);
        }
        break;

    case MODE_SET_UNDO:
        /*
         * XXX: UNDO and return to previous value for the object 
         */
        if ( unimplemented /* XXX: error? */ ) {
            /*
             * try _really_really_ hard to never get to this point 
             */
            netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_ERR_UNDOFAILED);
        }
        break;

    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_powerGuruDataLog\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruUnitAddress(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *reqinfo,
                            netsnmp_request_info *requests)
{
  printf("HEY Now !!!!!\n");
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so 
     * we don't need to loop over a list of requests; we'll only get one. 
     */
  int foo = 666;
  
    switch (reqinfo->mode) {
    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &foo,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 4);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruUnitAddress\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruChargeAmps(netsnmp_mib_handler *handler,
                           netsnmp_handler_registration *reginfo,
                           netsnmp_agent_request_info *reqinfo,
                           netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */1 );
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruChargeAmps\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruPVAmps(netsnmp_mib_handler *handler,
                       netsnmp_handler_registration *reginfo,
                       netsnmp_agent_request_info *reqinfo,
                       netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_powerGuruPVAmps\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruPVVolts(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *reqinfo,
                        netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_powerGuruPVVolts\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruDailyKW(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *reqinfo,
                        netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_powerGuruDailyKW\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruAuxMode(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *reqinfo,
                        netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_powerGuruAuxMode\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruErrorMode(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info *reqinfo,
                          netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruErrorMode\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruChargerMode(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *reqinfo,
                            netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruChargerMode\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruBatteryVolts(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *reqinfo,
                             netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruBatteryVolts\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruLoadAmps(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *reqinfo,
                         netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruLoadAmps\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruACBuyAmps(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info *reqinfo,
                          netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruACBuyAmps\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruACInputVolts(netsnmp_mib_handler *handler,
                             netsnmp_handler_registration *reginfo,
                             netsnmp_agent_request_info *reqinfo,
                             netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruACInputVolts\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruACOutputVolts(netsnmp_mib_handler *handler,
                              netsnmp_handler_registration *reginfo,
                              netsnmp_agent_request_info *reqinfo,
                              netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruACOutputVolts\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int
handle_powerGuruACSellAmps(netsnmp_mib_handler *handler,
                           netsnmp_handler_registration *reginfo,
                           netsnmp_agent_request_info *reqinfo,
                           netsnmp_request_info *requests)
{
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 (u_char *)
                                 /* XXX: a pointer to the scalar's data */
                                 &unimplemented,
                                 /*
                                  * XXX: the length of the data in bytes 
                                  */ 1);
        break;


    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_powerGuruACSellAmps\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}