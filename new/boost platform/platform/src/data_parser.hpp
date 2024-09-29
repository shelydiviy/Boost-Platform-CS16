#pragma once
#include <archtypes.h>

typedef unsigned char byte;

class CDataParser
{
public:
	CDataParser(unsigned char* pBuff, int bufflen);
	CDataParser(int bufflen);
	~CDataParser(void);

	//Get Data
	byte GetByte();
	short GetShort();
	int GetInt();
	uint64 GetUInt64();
	long GetLong();
	float GetFloat();
	long long GetLongLong();
	char* GetString();

	//Set Data
	void SetByte(byte val);
	void SetShort(short val);
	void SetInt(int val);
	void SetUInt64(uint64 val);
	void SetLong(long val);
	void SetFloat(float val);
	void SetLongLong(long long val);
	void SetString(char* pVal);
	void SetData(unsigned char* pVal, int valsize);

	int GetOffset();
	void SetOffset(int val);
	int MoveOffset(int changeoffs);
	void ClearAllBuf();

	//Full data
	unsigned char* GetFullData();
	int GetFullSize();

	//Current data
	unsigned char* GetCurrentData();
	int GetCurrentSize();

private:
	int offset;
	int buffsize;
	unsigned char* pBuffLink;
	bool isAllocated;
};
