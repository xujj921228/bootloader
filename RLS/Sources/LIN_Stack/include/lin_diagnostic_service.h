#include "lin.h"




extern void lin_diagservice_session_state(void);
extern void lin_diagservice_session_control(void);


extern void lin_diagservice_read_data_by_identifier(void);
extern void lin_diagservice_write_data_by_identifier(void);

extern void lin_diagservice_service_securityaccess(void);
extern void lin_diagservice_request_download(void);
extern void lin_diagservice_transfer_data(void);
void lin_diagservice_service_trigger_check(void);
extern void lin_diagservice_exit_transfer(void);


extern l_u8 diagnostic_Session,diagnostic_Session_flg;
extern l_u16 diagnostic_Session_timer;




