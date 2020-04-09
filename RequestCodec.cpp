#define _CRT_SECURE_NO_WARNINGS
#include "RequestCodec.h"

//�޲ι��캯��
RequestCodec::RequestCodec()
{
	m_msg = new RequestMsg;
}

//�������Ĺ��캯��
RequestCodec::RequestCodec(RequestMsg * msg)
{
	//����ռ�
	m_msg = new RequestMsg;

	//��ֵ
	//��������
	m_msg->cmdType = msg->cmdType;
	//�ͻ��˱��
	strcpy(m_msg->clientId, msg->clientId);
	//����˱��
	strcpy(m_msg->serverId, msg->serverId);
	//��֤��
	strcpy(m_msg->authCode, msg->authCode);
	//�����
	memcpy(m_msg->r1, msg->r1, sizeof(msg->r1));
}

//��������
RequestCodec::~RequestCodec()
{
	delete m_msg;
}

int RequestCodec::msgEncode(char ** outData, int & len)
{
	//1. ����cmdType
	writeHeadNode(m_msg->cmdType);

	//2. ����clientId
	writeNextNode(m_msg->clientId, strlen(m_msg->clientId));

	//3. ����authCode
	writeNextNode(m_msg->authCode, strlen(m_msg->authCode));

	//4. ����serverId
	writeNextNode(m_msg->serverId, strlen(m_msg->serverId));

	//5. ����r1
	writeNextNode(m_msg->r1, sizeof(m_msg->r1));

	//6. �����ṹ��
	packSequence(outData, len);	//1. free

	//7. �ͷ�����
	freeSequence();

	return 0;
}


void * RequestCodec::msgDecode(char * inData, int inLen)
{
	//����
	memset(m_msg, 0, sizeof(struct RequestMsg));

	//1. �����ṹ��  �õ�һ������
	unpackSequence(inData, inLen);

	//2. ����cmdType
	readHeadNode(m_msg->cmdType);

	//3. ����clientId
	readNextNode(m_msg->clientId);

	//4. ����authCode
	readNextNode(m_msg->authCode);

	//5. ����serverId
	readNextNode(m_msg->serverId);

	//6. ����r1
	readNextNode(m_msg->r1);

	//7. �ͷ�����
	freeSequence();

	return m_msg;
}

int RequestCodec::msgMemFree(void ** point)
{

	return 0;
}
