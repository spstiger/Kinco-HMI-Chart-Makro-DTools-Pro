#ifndef MACRO_H
#define  MACRO_H

#include <string.h> 
#include <math.h> 

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;

//����������
enum CmdRet
{
CMD_WIDGET_ILLEGAL = -3,	//Ԫ��������
CMD_WINDOW_ILLEGAL = -2,	//���ڲ�����
CMD_ILLEGAL = -1,			//���֧��
CMD_OK = 0,					//�ɹ�
CMD_NG = 1,					//һ�����
CMD_WINDOW_OPENED = 2,	//�����Ѵ�
CMD_WINDOW_CLOSED = 3,	//�����ѹر�
CMD_USERNAME_ILLEGAL = 4,	//�û���������
CMD_PSWD_ERROR = 5,		//�������
CMD_USERNAME_EXISTED,	//�û����Ѵ���
CMD_NO_PERMISSION,		//û��Ȩ��
//......
};

typedef enum _PlcComState
{
PLC_COM_OK = 0,
PLC_COM_OVERTIME = 0x2,  //ͨѶ��ʱ
PLC_COM_ERROR,  //ͨѶʧ��

PLC_COM_ILLEGAL = 0xf,  //ֻ��ͨѶʱʹ�ã�ͨѶ֮����������󣬺����治ʹ��
//PLC_COM_DONE = BitMsk(4), //д�ɹ��������治ʹ�ã��ɹ�ȫ������0
//������comserver���ص�״̬��������comclient���Զ���״̬�������治ʹ��
PLC_COM_NOT_START = 0x20,  //����û��ͨѶ���������治ʹ��
PLC_COM_DISCONNECT,  //�����������жϻ�δ���ӳɹ�
PLC_COM_PARAM_ERR, //��������
}PlcComState;

typedef struct _OperSetting OperSetting;

typedef PlcComState (*ReadVarFunc)(U32 varId		//����ΨһID
									, void *readBuf
									, OperSetting *oper);
typedef PlcComState (*WriteVarFunc)(U32 varId
									, const void * writeBuf
									, OperSetting *oper);

typedef PlcComState (*ReadArrayVarFunc)(U32 varId		//����ΨһID
									, U32 index
									, void *readBuf
									, OperSetting *oper);
typedef PlcComState (*WriteArrayVarFunc)(U32 varId
									, U32 index
									, const void * writeBuf
									, OperSetting *oper);

typedef PlcComState (*ReadBlockFunc)(U32 DevNameID	//�豸��
									, U32 RegID		//�Ĵ���ID
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



#define ReadVar(varId, readBuf)  xReadVar(oper, varId, readBuf)
static PlcComState xReadVar(OperSetting *oper
						, U32 varId
						, void *readBuf
						)
{
	return oper->_readVar(varId
						, readBuf
						, oper
						);
}

#define WriteVar(varId, readBuf)  xWriteVar(oper, varId, readBuf)
static PlcComState xWriteVar(OperSetting *oper
						, U32 varId
						, const void * writeBuf
						)
{
	return oper->_writeVar(varId
						, writeBuf
						, oper
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

#define Main() MainMacro(OperSetting *oper)

#endif

