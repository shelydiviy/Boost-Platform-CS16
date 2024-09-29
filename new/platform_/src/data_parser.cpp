#include "data_parser.hpp"
#include <cstring>

CDataParser::~CDataParser(void)
{
	if (isAllocated)
	{
		delete[] pBuffLink;
	}
}

CDataParser::CDataParser(int bufflen)
{
	pBuffLink = new byte[bufflen];
	std::memset(pBuffLink, 0, bufflen);

	offset = 0;
	buffsize = bufflen;
	isAllocated = true;
}

CDataParser::CDataParser(unsigned char* pBuff, int bufflen)
{
	pBuffLink = pBuff;
	offset = 0;
	buffsize = bufflen;
	isAllocated = false;
}

byte CDataParser::GetByte()
{
	byte val = pBuffLink[offset];
	offset++;
	return val;
}

short CDataParser::GetShort()
{
	short val = (short)((short*)(pBuffLink + offset))[0];
	offset += sizeof(short);

	return val;
}

int CDataParser::GetInt()
{
	int val = (int)((int*)(pBuffLink + offset))[0];
	offset += sizeof(int);

	return val;
}

long CDataParser::GetLong()
{
	long val = (long)((long*)(pBuffLink + offset))[0];
	offset += sizeof(long);

	return val;
}

float CDataParser::GetFloat()
{
	float val = (float)((float*)(pBuffLink + offset))[0];
	offset += sizeof(float);

	return val;
}

long long CDataParser::GetLongLong()
{
	long long val = (long long)((long long*)(pBuffLink + offset))[0];
	offset += sizeof(long long);

	return val;
}

char* CDataParser::GetString()
{
	int oldoffset = offset;

	char* pVal = (char*)pBuffLink + offset;

	offset += (strlen(pVal) + 1);
	return pVal;
}

unsigned char* CDataParser::GetFullData()
{
	return pBuffLink;
}

int CDataParser::GetFullSize()
{
	return buffsize;
}

unsigned char* CDataParser::GetCurrentData()
{
	return pBuffLink + offset;
}

int CDataParser::GetCurrentSize()
{
	return buffsize - offset;
}


int CDataParser::GetOffset()
{
	return offset;
}

void CDataParser::SetByte(byte val)
{
	pBuffLink[offset] = val;
	offset++;
}

void CDataParser::SetOffset(int val)
{
	offset = val;
}

int CDataParser::MoveOffset(int changeoffs)
{
	offset += changeoffs;

	return 1;
}

void CDataParser::ClearAllBuf()
{
	std::memset(pBuffLink, 0, buffsize);
}

//Set data
void CDataParser::SetShort(short val)
{
	*reinterpret_cast<short*>(pBuffLink + offset) = val;
	offset += sizeof(short);
}

void CDataParser::SetInt(int val)
{
	*reinterpret_cast<int*>(pBuffLink + offset) = val;
	offset += sizeof(int);
}

void CDataParser::SetLong(long val)
{
	*reinterpret_cast<long*>(pBuffLink + offset) = val;
	offset += sizeof(long);
}

void CDataParser::SetFloat(float val)
{
	*reinterpret_cast<float*>(pBuffLink + offset) = val;
	offset += sizeof(float);
}

void CDataParser::SetLongLong(long long val)
{
	*reinterpret_cast<long long*>(pBuffLink + offset) = val;
	offset += sizeof(long long);
}

void CDataParser::SetString(char* pVal)
{
	strcpy(reinterpret_cast<char*>(pBuffLink + offset), pVal);
	offset += (strlen(pVal) + 1);
}

void CDataParser::SetData(unsigned char* pVal, int valsize)
{
	memcpy(pBuffLink + offset, pVal, valsize);
	offset += valsize;
}