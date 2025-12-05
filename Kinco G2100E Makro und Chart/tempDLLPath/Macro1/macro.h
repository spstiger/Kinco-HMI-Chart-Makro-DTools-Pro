#ifndef MACRO_H
#define  MACRO_H

#include <string.h> 
#include <math.h> 

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;

//函数错误码
enum CmdRet
{
CMD_WIDGET_ILLEGAL = -3,	//元件不存在
CMD_WINDOW_ILLEGAL = -2,	//窗口不存在
CMD_ILLEGAL = -1,			//命令不支持
CMD_OK = 0,					//成功
CMD_NG = 1,					//一般错误
CMD_WINDOW_OPENED = 2,	//窗口已打开
CMD_WINDOW_CLOSED = 3,	//窗口已关闭
CMD_USERNAME_ILLEGAL = 4,	//用户名不存在
CMD_PSWD_ERROR = 5,		//密码错误
CMD_USERNAME_EXISTED,	//用户名已存在
CMD_NO_PERMISSION,		//没有权限
//......
};

typedef enum _PlcComState
{
PLC_COM_OK = 0,
PLC_COM_OVERTIME = 0x2,  //通讯超时
PLC_COM_ERROR,  //通讯失败

PLC_COM_ILLEGAL = 0xf,  //只在通讯时使用，通讯之外的其它错误，宏里面不使用
//PLC_COM_DONE = BitMsk(4), //写成功，宏里面不使用，成功全部返回0
//上面是comserver返回的状态，下面是comclient的自定义状态，宏里面不使用
PLC_COM_NOT_START = 0x20,  //变量没有通讯过，宏里面不使用
PLC_COM_DISCONNECT,  //与服务端连接中断或未连接成功
PLC_COM_PARAM_ERR, //参数错误
}PlcComState;

typedef enum Encode //编码类型
{
    ENCODE_GB2312 = 0,
    ENCODE_UNICODE,
    ENCODE_UTF8,
    ENCODE_ASCII,
}Encode;

typedef struct _OperSetting OperSetting;

typedef PlcComState (*ReadVarFunc)(OperSetting *oper
									, U32 varId		//变量唯一ID
									, void *readBuf
									, int dstEncode);
typedef PlcComState (*WriteVarFunc)(OperSetting *oper
									, U32 varId
									, const void * writeBuf
									, int srcEncode);

typedef PlcComState (*ReadArrayVarFunc)(U32 varId		//变量唯一ID
									, U32 index
									, void *readBuf
									, OperSetting *oper);
typedef PlcComState (*WriteArrayVarFunc)(U32 varId
									, U32 index
									, const void * writeBuf
									, OperSetting *oper);

typedef PlcComState (*ReadBlockFunc)(U32 DevNameID	//设备名
									, U32 RegID		//寄存器ID
									, U32 Address
									, U8 Type
									, void *ReadBuf
									, U16 BufLen
									, void * RecvLen
									, OperSetting *oper);
typedef PlcComState (*WriteBlockFunc)(U32 DevNameID
									, U32 RegID
									, U32 Address
									, U8 Type
									, U16 BufLen
									, void *WriteBuf
									, OperSetting *oper);


typedef PlcComState (*DirectReadVarFunc)(OperSetting *oper
									, U32 varId		//变量唯一ID
									, void *readBuf
									, int dstEncode);
									
typedef PlcComState (*DirectWriteVarFunc)(OperSetting *oper
									, U32 varId
									, const void * writeBuf
									, int srcEncode);
									

struct _OperSetting
{
	U32 _flag;
	U32 _macroId;
	ReadVarFunc _readVar;
	WriteVarFunc _writeVar;
	ReadArrayVarFunc _readArrayVar;
	WriteArrayVarFunc _writeArrayVar;
	ReadBlockFunc _readBlock;
	WriteBlockFunc _writeBlock;
	
	DirectReadVarFunc _directReadVar;
	DirectWriteVarFunc _directWriteVar;
};



#ifdef WIN32
#ifdef __cplusplus
extern "C"
{
#endif
__declspec( dllexport ) int MainMacro(OperSetting *oper);
#ifdef __cplusplus
}
#endif
#else
#ifdef __cplusplus
extern "C"
{
#endif
int MainMacro(OperSetting *oper);
#ifdef __cplusplus
}
#endif
#endif



#define ReadVar(...)  xReadVar(oper, __VA_ARGS__)
static PlcComState xReadVar(OperSetting *oper
						, U32 varId
						, void *readBuf
						, int dstEncode = -1
						)
{
	return oper->_readVar(oper
						, varId
						, readBuf
						, dstEncode
						);
}

#define WriteVar(...)  xWriteVar(oper, __VA_ARGS__)
static PlcComState xWriteVar(OperSetting *oper
						, U32 varId
						, const void * writeBuf
						, int srcEncode = -2 
						)
{
	return oper->_writeVar(oper
						, varId
						, writeBuf
						, srcEncode
						);
}

#define ReadArrayVar(varId, index, readBuf)  xReadArrayVar(oper, varId, index, readBuf)
static PlcComState xReadArrayVar(OperSetting *oper
						, U32 varId
						, U32 index
						, void *readBuf
						)
{
	return oper->_readArrayVar(varId
						, index
						, readBuf
						, oper
						);
}

#define WriteArrayVar(varId, index, readBuf)  xWriteArrayVar(oper, varId, index, readBuf)
static PlcComState xWriteArrayVar(OperSetting *oper
						, U32 varId
						, U32 index
						, const void * writeBuf
						)
{
	return oper->_writeArrayVar(varId
						, index
						, writeBuf
						, oper
						);
}

#define ReadBlock(DevNameID, RegID, Address, Type, ReadBuf, BufLen, RecvLen)  xReadBlock(oper, DevNameID, RegID, Address, Type, ReadBuf, BufLen, RecvLen)
static PlcComState xReadBlock(OperSetting *oper
						, U32 DevNameID
						, U32 RegID
						, U32 Address
						, U8 Type
						, void *ReadBuf
						, U16 BufLen
						, void * RecvLen
						)
{
	return oper->_readBlock(DevNameID
						, RegID
						, Address
						, Type
						, ReadBuf
						, BufLen
						, RecvLen
						, oper
						);
}

#define WriteBlock(DevNameID, RegID, Address, Type, BufLen, WriteBuf)  xWriteBlockFunc(oper, DevNameID, RegID, Address, Type, BufLen, WriteBuf)
static PlcComState xWriteBlockFunc(OperSetting *oper
						, U32 DevNameID
						, U32 RegID
						, U32 Address
						, U8 Type
						, U16 BufLen
						, void *WriteBuf
						)
{
	return oper->_writeBlock(DevNameID
						, RegID
						, Address
						, Type
						, BufLen
						, WriteBuf
						, oper
						);
}


#define DirectReadVar(...)  xDirectReadVar(oper, __VA_ARGS__)
static PlcComState xDirectReadVar(OperSetting *oper
						, U32 varId
						, void *readBuf
						, int dstEncode = -1
						)
{
	return oper->_directReadVar(oper
						, varId
						, readBuf
						, dstEncode
						);
}

#define DirectWriteVar(...)  xDirectWriteVar(oper, __VA_ARGS__)
static PlcComState xDirectWriteVar(OperSetting *oper
						, U32 varId
						, const void * writeBuf
						, int srcEncode = -2 
						)
{
	return oper->_directWriteVar(oper
						, varId
						, writeBuf
						, srcEncode
						);
}


#define Main() MainMacro(OperSetting *oper)

#endif

