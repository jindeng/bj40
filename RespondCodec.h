#pragma once
#include "Codec.h"


//��ԿӦ����
struct  RespondMsg
{
	int					rv;				// ����ֵ
	char				clientId[12];	// �ͻ��˱��
	char				serverId[12];	// ���������
	unsigned char		r2[64];			// �������������
	int					seckeyid;		// �Գ���Կ���    keysn
};

class RespondCodec : public Codec
{
public:
	RespondCodec();
	RespondCodec(RespondMsg *msg);
	~RespondCodec();


public: 
	// ��д���ຯ��
	//���뺯��
	int msgEncode(char** outData, int &len);

	//���뺯��
	void* msgDecode(char *inData, int inLen);

	//�ڴ��ͷ�
	int msgMemFree(void **point);

private:
	RespondMsg *m_msg = NULL;

};

