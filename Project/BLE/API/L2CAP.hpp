#pragma once

#include "HCI.hpp"

class L2CAP
{
	/**
	  * @brief Send an L2CAP connection parameter update request from the slave to the master.
	An @ref aci_l2cap_connection_update_resp_event event will be raised when the master will respond to the 
	request (accepts or rejects).
	  * @param Connection_Handle Connection handle for which the command is given.
	  * Values:
	  - 0x0000 ... 0x0EFF
	  * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
	than or equal to Conn_Interval_Max.
	Time = N * 1.25 msec.
	  * Values:
	  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
	  * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
	greater than or equal to Conn_Interval_Min.
	Time = N * 1.25 msec.
	  * Values:
	  - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
	  * @param Slave_latency Slave latency for the connection in number of connection events.
	  * Values:
	  - 0x0000 ... 0x01F3
	  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
	  * @retval Value indicating success or error code.
	*/
	HCI::Status aci_l2cap_connection_parameter_update_req(ushort Connection_Handle, ushort Conn_Interval_Min, ushort Conn_Interval_Max, ushort Slave_latency, ushort Timeout_Multiplier);

	/**
	  * @brief Accept or reject a connection update. This command should be sent in response
	  to a @ref aci_l2cap_connection_update_req_event event from the controller. The accept parameter has to be
	  set if the connection parameters given in the event are acceptable.
	    * @param Connection_Handle Connection handle for which the command is given.
	    * Values:
	    - 0x0000 ... 0x0EFF
	    * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
	    than or equal to Conn_Interval_Max.
	    Time = N * 1.25 msec.
	      * Values:
	      - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
	      * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
	      greater than or equal to Conn_Interval_Min.
	      Time = N * 1.25 msec.
	        * Values:
	        - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
	        * @param Slave_latency Slave latency for the connection in number of connection events.
	        * Values:
	        - 0x0000 ... 0x01F3
	        * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
	        * @param Minimum_CE_Length Information parameter about the minimum length of connection
	        needed for this LE connection.
	        Time = N * 0.625 msec.
	          * Values:
	          - 0x0000 (0.000 ms)  ... 0xFFFF (40959.375 ms) 
	          * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
	          for this LE connection.
	          Time = N * 0.625 msec.
	            * Values:
	            - 0x0000 (0.000 ms)  ... 0xFFFF (40959.375 ms) 
	            * @param Identifier Identifier received in ACI_L2CAP_Connection_Update_Req event.
	            * @param Accept Specify if connection update parameters are acceptable or not.
	            * Values:
	            - 0x00: Reject
	            - 0x01: Accept
	            * @retval Value indicating success or error code.
	            */
	HCI::Status aci_l2cap_connection_parameter_update_resp(ushort Connection_Handle, ushort Conn_Interval_Min, ushort Conn_Interval_Max, ushort Slave_latency, ushort Timeout_Multiplier, ushort Minimum_CE_Length, ushort Maximum_CE_Length, byte Identifier, byte Accept);
};