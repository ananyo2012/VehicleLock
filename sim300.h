#ifndef SIM300_H_
#define SIM300_H_

//Error List
#define SIM300_OK					 1
#define SIM300_INVALID_RESPONSE		-1
#define SIM300_FAIL					-2
#define SIM300_TIMEOUT				-3

//Status
#define SIM300_NW_REGISTERED_HOME	1
#define SIM300_NW_SEARCHING			2
#define SIM300_NW_REGISTED_ROAMING	5
#define SIM300_NW_ERROR				99
#define SIM300_SIM_NOT_READY		100
#define SIM300_MSG_EMPTY			101

#define SIM300_SIM_PRESENT			1
#define SIM300_SIM_NOT_PRESENT		0

//Low Level Functions
int8_t SIM300Cmd(const char *cmd);

//Public Interface
int8_t	SIM300Init();
int8_t	SIM300CheckResponse(const char *response,const char *check,uint8_t len);
int8_t	SIM300WaitForResponse(uint16_t timeout);
int8_t	SIM300GetNetStat();
int8_t	SIM300IsSIMInserted();
uint8_t SIM300GetProviderName(char *);
int8_t	SIM300GetIMEI(char *);
int8_t	SIM300GetManufacturer(char *);
int8_t	SIM300GetModel(char *);
int8_t	SIM300DeleteMsg(uint8_t i);
int8_t	SIM300WaitForMsg(uint8_t *);
int8_t	SIM300ReadMsg(uint8_t i, char *);
int8_t	SIM300SendMsg(const char *, const char *,uint8_t *);



#endif /* SIM300_H_ */