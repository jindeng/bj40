#define _CRT_SECURE_NO_WARNINGS
#include "RespondCodec.h"

#include <iostream>

using namespace std;


//���캯��
RespondCodec::RespondCodec():Codec()
{
	//�����ڴ�
	m_msg = new  RespondMsg;
	if (NULL == m_msg)
	{
		cout << "new RespondMsg failed.." << endl;

		return;
	}
}

RespondCodec::RespondCodec(RespondMsg * msg):Codec()
{
	//�����ڴ�
	m_msg = new RespondMsg;
	if (NULL == m_msg)
	{
		cout << "new RespondMsg failed.." << endl;

		return;
	}

	//��ֵ
	m_msg->rv = msg->rv;
	strcpy(m_msg->clientId, msg->clientId);
	strcpy(m_msg->serverId, msg->serverId);
	strcpy((char *)m_msg->r2, (char *)msg->r2);

	m_msg->seckeyid = msg->seckeyid;
}


//��������
RespondCodec::~RespondCodec()
{
	delete m_msg;
}


int RespondCodec::msgEncode(char ** outData, int & len)
{
	int ret = 0;

	//1. ����rv
	ret = writeHeadNode(m_msg->rv);
	if (0 != ret)
	{
		cout << "writeHeadNode rv failed..." << endl;
		return ret;
	}

	//2. ����clientId
	ret = writeNextNode(m_msg->clientId, strlen(m_msg->clientId));
	if (0 != ret)
	{
		cout << "writeHeadNode clientId failed..." << endl;
		return ret;
	}

	//3. ����serverId
	ret = writeNextNode(m_msg->serverId, strlen(m_msg->serverId));
	if (0 != ret)
	{
		cout << "writeHeadNode serverId failed..." << endl;
		return ret;
	}

	//4. ����r2
	ret = writeNextNode((char*)m_msg->r2, strlen((char *)m_msg->r2));
	if (0 != ret)
	{
		cout << "writeHeadNode r2 failed..." << endl;
		return ret;
	}

	//5. ����seckeyid
	ret = writeNextNode(m_msg->seckeyid);
	if (0 != ret)
	{
		cout << "writeHeadNode seckeyId failed..." << endl;
		return ret;
	}

	//6. �����ṹ��
	ret = packSequence(outData, len);
	if (0 != ret)
	{
		cout << "packSequence failed..." << endl;
		return ret;
	}

	//7. ���� 

	//8. �ͷ�����ռ�
	freeSequence();

	return 0;
}

//��Ӧ���Ľ��뺯��
void * RespondCodec::msgDecode(char * inData, int inLen)
{
	int ret = 0;

	//����
	memset(m_msg, 0, sizeof(RespondMsg));

	//1. �����ṹ��
	ret = unpackSequence(inData, inLen);
	if (0 != ret)
	{
		cout << "packSequence failed..." << endl;
		return NULL;
	}

	//2. ����rv
	ret = readHeadNode(m_msg->rv);
	if (0 != ret)
	{
		cout << "readHeadNode failed..." << endl;
		return NULL;
	}

	//3. ����clientId
	ret =  readNextNode(m_msg->clientId);
	if (0 != ret)
	{
		cout << "readHeadNode failed..." << endl;
		return NULL;
	}

	//4. ����serverId
	ret = readNextNode(m_msg->serverId);
	if (0 != ret)
	{
		cout << "readHeadNode failed..." << endl;
		return NULL;
	}

	//5. ����r2
	ret = readNextNode((char *)m_msg->r2);
	if (0 != ret)
	{
		cout << "readHeadNode failed..." << endl;
		return NULL;
	}

	//6. ����seckeyid
	ret = readNextNode(m_msg->seckeyid);
	if (0 != ret)
	{
		cout << "readHeadNode failed..." << endl;
		return NULL;
	}

	//7. �ͷ�����ռ�
	freeSequence();

	return m_msg;
}

int RespondCodec::msgMemFree(void ** point)
{
	return 0;
}
