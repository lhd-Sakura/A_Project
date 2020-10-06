#ifndef __USER_PROTCOL_H_
#define __USER_PROTCOL_H_
/**

1.6节的代码

**/
#include "user_system.h"
//枚举类型代表到底是什么数据
enum _ptl_type
{
	VAL_START = 0,
	VAL_POSE,
	VAL_IMU_RAW,
	VAL_VEL,
	VAL_PID,
	VAL_IMU,
	VAL_END
};
//起始码
#define _SERIAL_SYN_CODE_START 0XFA
//因为串口是一个字节一个字节发送的，此关键字代表一字节对齐，否则可能发送到容量不同的设备会有不一样
#pragma pack(1)
//整个结构体就是我们要发送的数据协议
typedef struct _serial_data
{
	uint8_t syn;//同部位
	uint8_t type;//数据类型位，指明数据类型
	//数据，联合体发送不同类型的数据，共用的空间
	union{
		struct{
			float liner[3],angular[3];
		}vel;
		struct{
			bool rot_ok,acc_ok,mag_ok;
			double rot[3],acc[3],msg[3];
		}imu;
		float pid[3];
	}dat;
	//数据结束位
	uint8_t syn_CR;
	uint8_t syn_LF;
}serialData;
#pragma pack()
#endif 
