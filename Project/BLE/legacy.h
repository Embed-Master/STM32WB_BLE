#pragma once

/******************************************************************************
 * Transport Layer (TL)
 ******************************************************************************/
#define TL_EVT_HDR_SIZE					3

#define TL_BLEEVT_CC_OPCODE				0x0E
#define TL_BLEEVT_CS_OPCODE				0x0F
#define TL_BLEEVT_VS_OPCODE				0xFF

#define EVT_VENDOR						0xFF
#define EVT_DISCONN_COMPLETE			0x05
#define EVT_LE_META_EVENT				0x3E
#define EVT_LE_CONN_UPDATE_COMPLETE		0x03
#define EVT_LE_CONN_COMPLETE			0x01
#define EVT_LE_PHY_UPDATE_COMPLETE		0x0C
#define EVT_HCI_COMMAND_COMPLETE_EVENT	0x0E

/******************************************************************************
 * Services
 ******************************************************************************/
#define SVCCTL_EGID_EVT_MASK   0xFF00
#define SVCCTL_GATT_EVT_TYPE   0x0C00

/* BLE core event codes */
#define EVT_BLUE_GATT_ATTRIBUTE_MODIFIED          (0x0C01)
#define EVT_BLUE_GATT_PROCEDURE_TIMEOUT           (0x0C02)
#define EVT_BLUE_ATT_EXCHANGE_MTU_RESP            (0x0C03)
#define EVT_BLUE_ATT_FIND_INFORMATION_RESP        (0x0C04)
#define EVT_BLUE_ATT_FIND_BY_TYPE_VAL_RESP        (0x0C05)
#define EVT_BLUE_ATT_READ_BY_TYPE_RESP            (0x0C06)
#define EVT_BLUE_ATT_READ_RESP                    (0x0C07)
#define EVT_BLUE_ATT_READ_BLOB_RESP               (0x0C08)
#define EVT_BLUE_ATT_READ_MULTIPLE_RESP           (0x0C09)
#define EVT_BLUE_ATT_READ_BY_GROUP_TYPE_RESP      (0x0C0A)
#define EVT_BLUE_ATT_PREPARE_WRITE_RESP           (0x0C0C)
#define EVT_BLUE_ATT_EXEC_WRITE_RESP              (0x0C0D)
#define EVT_BLUE_GATT_INDICATION                  (0x0C0E)
#define EVT_BLUE_GATT_NOTIFICATION                (0x0C0F)
#define EVT_BLUE_GATT_PROCEDURE_COMPLETE          (0x0C10)
#define EVT_BLUE_GATT_ERROR_RESP                  (0x0C11)
#define EVT_BLUE_GATT_DISC_READ_CHAR_BY_UUID_RESP (0x0C12)
#define EVT_BLUE_GATT_WRITE_PERMIT_REQ            (0x0C13)//Write
#define EVT_BLUE_GATT_READ_PERMIT_REQ             (0x0C14)//Read
#define EVT_BLUE_GATT_READ_MULTI_PERMIT_REQ       (0x0C15)
#define EVT_BLUE_GATT_TX_POOL_AVAILABLE           (0x0C16)
#define EVT_BLUE_GATT_SERVER_CONFIRMATION_EVENT   (0x0C17)
#define EVT_BLUE_GATT_PREPARE_WRITE_PERMIT_REQ    (0x0C18)
#define EVT_BLUE_GAP_LIMITED_DISCOVERABLE         (0x0400)
#define EVT_BLUE_GAP_PAIRING_CMPLT                (0x0401)
#define EVT_BLUE_GAP_PASS_KEY_REQUEST             (0x0402)
#define EVT_BLUE_GAP_AUTHORIZATION_REQUEST        (0x0403)
#define EVT_BLUE_GAP_SLAVE_SECURITY_INITIATED     (0X0404)
#define EVT_BLUE_GAP_BOND_LOST                    (0X0405)
#define EVT_BLUE_GAP_DEVICE_FOUND                 (0x0406)
#define EVT_BLUE_GAP_PROCEDURE_COMPLETE           (0x0407)
#define EVT_BLUE_GAP_ADDR_NOT_RESOLVED            (0x0408)
#define EVT_BLUE_GAP_NUMERIC_COMPARISON_VALUE     (0x0409)
#define EVT_BLUE_GAP_KEYPRESS_NOTIFICATION        (0x040A)
#define EVT_BLUE_L2CAP_CONNECTION_UPDATE_REQ      (0x0802)
#define EVT_BLUE_L2CAP_CONNECTION_UPDATE_RESP     (0x0800)

// AD types for adv. data and scan response data
#define AD_TYPE_FLAGS                              0x01
#define AD_TYPE_16_BIT_SERV_UUID                   0x02
#define AD_TYPE_16_BIT_SERV_UUID_CMPLT_LIST        0x03
#define AD_TYPE_32_BIT_SERV_UUID                   0x04
#define AD_TYPE_32_BIT_SERV_UUID_CMPLT_LIST        0x05
#define AD_TYPE_128_BIT_SERV_UUID                  0x06
#define AD_TYPE_128_BIT_SERV_UUID_CMPLT_LIST       0x07
#define AD_TYPE_SHORTENED_LOCAL_NAME               0x08
#define AD_TYPE_COMPLETE_LOCAL_NAME                0x09
#define AD_TYPE_TX_POWER_LEVEL                     0x0A
#define AD_TYPE_CLASS_OF_DEVICE                    0x0D
#define AD_TYPE_SEC_MGR_TK_VALUE                   0x10
#define AD_TYPE_SEC_MGR_OOB_FLAGS                  0x11
#define AD_TYPE_SLAVE_CONN_INTERVAL                0x12
#define AD_TYPE_SERV_SOLICIT_16_BIT_UUID_LIST      0x14
#define AD_TYPE_SERV_SOLICIT_128_BIT_UUID_LIST     0x15
#define AD_TYPE_SERVICE_DATA                       0x16
#define AD_TYPE_APPEARANCE                         0x19
#define AD_TYPE_ADVERTISING_INTERVAL               0x1A
#define AD_TYPE_LE_ROLE                            0x1C
#define AD_TYPE_SERV_SOLICIT_32_BIT_UUID_LIST      0x1F
#define AD_TYPE_URI                                0x24
#define AD_TYPE_MANUFACTURER_SPECIFIC_DATA         0xFF

/* Advertising policy for filtering (white list related)
 * See hci_le_set_advertising_parameters
 */
#define NO_WHITE_LIST_USE			0x00
#define WHITE_LIST_FOR_ONLY_SCAN	0x01
#define WHITE_LIST_FOR_ONLY_CONN	0x02
#define WHITE_LIST_FOR_ALL			0x03