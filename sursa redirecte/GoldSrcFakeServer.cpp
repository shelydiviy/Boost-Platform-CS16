#include "stdafx.h"
#include "tools.h"
#include "Csocket.h"
#include "DataParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int source = 2;


int numred = 0;
int hideconsole = 0;

int SV_MAXQuery = 100000;


using namespace std;

int defineport = 1;

string path1 = "goldsrc/maplist.txt";
ifstream fin1(path1);

string path2 = "goldsrc/hostname.txt";
ifstream fin2(path2);

string path3 = "sourcesrc/tagname_csgo.txt";
ifstream fin3(path3);

string path7 = "sourcesrc/cl_redirect.txt";
ifstream fin7(path7);

string path4 = "goldsrc/cl_svc.txt";
ifstream fin4(path4);

string path5 = "goldsrc/cl_redirect.txt";
ifstream fin5(path5);

string path6 = "goldsrc/cl_kick.txt";
ifstream fin6(path6);

string source_bots = "goldsrc/bots.txt";
ifstream fin8(source_bots);
int floodpause = 0;


struct serverinfo_t
{
	int  serverport;
	char pServAddr[1024];

	byte protocol;
	char pHostName[1024];
	char pMapName[1024];
	char pGameDir[1024];
	char pGameName[1024];
	short appid;

	byte curpl;
	byte maxplayers;
	byte bots;
	byte type;
	byte os;
	byte password;


	byte ismod;
	char pLinkMod[1024];
	char pDownloadLink[1024];
	long modversion;
	long modsize;
	byte typemod;
	byte isuseowndll;

	byte secure;

	char pVersion[1024];
	short gameport;
	long long steamid;
	short sourcetvport;
	char pSourceTVName[1024];
	char tags[1024];
	long long gameid;
};

int IfFileDir() {

	server_print("GoldSrcFakeServer 1.03 started...\n\n");

	if (fin1.fail()) {
		LogPrintf(true, "File '%s' missing\n", path1);
		return 1;
	}
	if (fin2.fail()) {
		LogPrintf(true, "File '%s' missing\n", path2);
		return 1;
	}
	if (source == 1) {
		if (fin3.fail()) {
			LogPrintf(true, "File '%s' missing\n", path3);
			return 1;
		}
	}
	if (fin4.fail()) {
		LogPrintf(true, "File '%s' missing\n", path4);
		return 1;
	}
	if (fin6.fail()) {
		LogPrintf(true, "File '%s' missing\n", path6);
		return 1;
	}
	if (fin7.fail()) {
		LogPrintf(true, "File '%s' missing\n", path7);
		return 1;
	}
	if (fin8.fail()) {
		LogPrintf(true, "File '%s' missing\n", source_bots);
		return 1;
	}
}
int SendCvarList2(Csocket* pSocket)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);
	pQuery->SetByte(0xFE);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x03);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x12);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x7A);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x38);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x37);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x56);
	pQuery->SetByte(0x54);
	pQuery->SetByte(0x43);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x56);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x37);
	pQuery->SetByte(0x52);
	pQuery->SetByte(0x43);
	pQuery->SetByte(0x33);
	pQuery->SetByte(0x00);
	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}
int SendCvarList(Csocket* pSocket)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFE);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x03);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x02);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x45);
	pQuery->SetByte(0x58);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x37);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x38);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x33);
	pQuery->SetByte(0x37);
	pQuery->SetByte(0x34);
	pQuery->SetByte(0x36);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x71);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x33);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x37);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6A);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x71);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x71);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x71);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x39);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x33);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x34);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x34);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x7A);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x71);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x36);
	pQuery->SetByte(0x36);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x2E);
	pQuery->SetByte(0x36);
	pQuery->SetByte(0x36);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x38);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x38);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x35);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x77);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x75);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x68);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x31);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x66);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x34);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x79);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x38);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x67);
	pQuery->SetByte(0x62);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x6B);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x78);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x70);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x33);
	pQuery->SetByte(0x32);
	pQuery->SetByte(0x30);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x76);
	pQuery->SetByte(0x5F);
	pQuery->SetByte(0x6D);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x61);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x65);
	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}
void SendDataPack(Csocket* pSocket, CDataParser* pEncodeQuery, int sequence, int sequence_ack)
{
	COM_Munge2(pEncodeQuery->GetFullData(), pEncodeQuery->GetOffset(), sequence & 0xFF);


	CDataParser* pQueryPack = new CDataParser(8192);


	pQueryPack->ClearAllBuf();
	pQueryPack->SetOffset(0);


	pQueryPack->SetLong(sequence);
	pQueryPack->SetLong(sequence_ack);
	pQueryPack->SetData(pEncodeQuery->GetFullData(), pEncodeQuery->GetOffset());

	pSocket->Send(pQueryPack->GetFullData(), pQueryPack->GetOffset());

	delete pQueryPack;
}

int RecvDataPack(Csocket* pSocket, CDataParser* pRevData)
{
	unsigned int recv_sequence;
	unsigned int sequence_ack;


	pRevData->ClearAllBuf();
	pRevData->SetOffset(0);


	int recvbytes = pSocket->Recv(pRevData->GetFullData(), pRevData->GetFullSize());

	if (recvbytes >= 8)
	{

		recv_sequence = pRevData->GetLong();
		sequence_ack = pRevData->GetLong();


		COM_UnMunge2(pRevData->GetCurrentData(), pRevData->GetCurrentSize(), recv_sequence & 0xFF);

		pRevData->SetOffset(0);
	}

	return recvbytes;
}
int SendCSGO_RED(Csocket* pSocket)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xff);
	pQuery->SetByte(0xff);
	pQuery->SetByte(0xff);
	pQuery->SetByte(0xff);
	pQuery->SetByte(0x39);
	pQuery->SetByte(0x43);
	pQuery->SetByte(0x6F);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x6E);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x52);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x69);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x63);
	pQuery->SetByte(0x74);
	pQuery->SetByte(0x41);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x72);
	pQuery->SetByte(0x65);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x73);
	pQuery->SetByte(0x3A);
	std::ifstream file(path7);
	std::string str;
	while (std::getline(file, str)) {
		char* c = strcpy(new char[str.length() + 1], str.c_str());
		pQuery->SetString(c);
	}

	pQuery->SetByte(0x00);

	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}

int SendInfoAboutServer2(Csocket* pSocket, serverinfo_t* pServerInfo)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x6D);
	pQuery->SetString("62.121.116.122:27023");


	pQuery->SetString(pServerInfo->pHostName);
	pQuery->SetString(pServerInfo->pMapName);
	pQuery->SetString(pServerInfo->pGameDir);
	pQuery->SetString(pServerInfo->pGameName);



	pQuery->SetByte(pServerInfo->curpl);
	pQuery->SetByte(pServerInfo->maxplayers);

	pQuery->SetByte(0x2F);
	pQuery->SetByte(0x64);
	pQuery->SetByte(0x6C);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x01);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x01);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);

	pQuery->SetByte(0x00);

	pQuery->SetByte(0x01);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x00);
	pQuery->SetByte(0x19);


	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}

int SendInfoAboutServer(Csocket* pSocket, serverinfo_t* pServerInfo)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	if (source == 2) {
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0x49);

		pQuery->SetByte(0x11);
		pQuery->SetString(pServerInfo->pHostName);
		pQuery->SetString(pServerInfo->pMapName);
		pQuery->SetString(pServerInfo->pGameDir);
		pQuery->SetString(pServerInfo->pGameName);

		pQuery->SetShort(pServerInfo->appid);
		pQuery->SetByte(pServerInfo->curpl);
		pQuery->SetByte(pServerInfo->maxplayers);
		pQuery->SetByte(pServerInfo->bots);

		pQuery->SetByte(pServerInfo->type);
		pQuery->SetByte(pServerInfo->os);
		pQuery->SetByte(pServerInfo->password);
		pQuery->SetByte(pServerInfo->secure);

		pQuery->SetString(pServerInfo->pVersion);

	}
	if (source == 1) {
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0x49);

		pQuery->SetByte(0x11);
		pQuery->SetString(pServerInfo->pHostName);
		pQuery->SetString(pServerInfo->pMapName);
		pQuery->SetString(pServerInfo->pGameDir);
		pQuery->SetString(pServerInfo->pGameName);

		pQuery->SetShort(pServerInfo->appid);
		pQuery->SetByte(pServerInfo->curpl);
		pQuery->SetByte(pServerInfo->maxplayers);
		pQuery->SetByte(pServerInfo->bots);

		pQuery->SetByte(pServerInfo->type);
		pQuery->SetByte(pServerInfo->os);
		pQuery->SetByte(pServerInfo->password);
		pQuery->SetByte(pServerInfo->secure);

		pQuery->SetString(pServerInfo->pVersion);

		pQuery->SetByte(0xF1);
		pQuery->SetByte(0x87);
		pQuery->SetByte(0x69);
		pQuery->SetByte(0x1F);
		pQuery->SetByte(0x6D);
		pQuery->SetByte(0x27);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x30);
		pQuery->SetByte(0x01);
		pQuery->SetByte(0x8C);
		pQuery->SetString("iDE.MORTIMATI.RO");
		std::ifstream tagnamelist;
		std::string lines2[9999];
		int index2 = 0;

		tagnamelist.open(path3, std::ifstream::in);
		while (tagnamelist.good() && index2 < 9999) {
			tagnamelist >> lines2[index2];
			index2++;
		}
		tagnamelist.close();
		srand(time(0));
		int randomIndex2 = rand() % index2;
		string f_tagname = lines2[randomIndex2];
		char* v_tagname = &f_tagname[0];

		pQuery->SetString(v_tagname);
		pQuery->SetByte(0xDA);
		pQuery->SetByte(0x02);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
	}
	if (source == 0) {

		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0xFF);
		pQuery->SetByte(0x49);

		pQuery->SetByte(0x00);
		pQuery->SetString(pServerInfo->pHostName);
		pQuery->SetString(pServerInfo->pMapName);
		pQuery->SetString(pServerInfo->pGameDir);
		pQuery->SetString(pServerInfo->pGameName);

		pQuery->SetShort(pServerInfo->appid);
		pQuery->SetByte(pServerInfo->curpl);
		pQuery->SetByte(pServerInfo->maxplayers);
		pQuery->SetByte(pServerInfo->bots);

		pQuery->SetByte(pServerInfo->type);
		pQuery->SetByte(pServerInfo->os);
		pQuery->SetByte(pServerInfo->password);
		pQuery->SetByte(pServerInfo->secure);

		pQuery->SetString(pServerInfo->pVersion);

		pQuery->SetByte(0x80);
		pQuery->SetByte(0x87);
		pQuery->SetByte(0x69);

		pQuery->SetByte(0xD2);
		pQuery->SetByte(0x04);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x0A);
		pQuery->SetByte(0x0A);
		pQuery->SetByte(0x40);
		pQuery->SetByte(0x01);
		pQuery->SetByte(0x0A);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);
		pQuery->SetByte(0x00);

	}
	if (hideconsole == 0) {
		server_print_red("Updated settings: %s\n", pQuery->GetFullData());
	}
	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;


	return 1;
}


int SendChallengeForSteam(Csocket* pSocket)
{

	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x41);
	pQuery->SetString("00000000 466639471 3 90127494217252875m 1");
	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}

int SendChallengeForValve(Csocket* pSocket)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x41);
	pQuery->SetString("00000000 2031975158 2");
	pQuery->SetByte(0x0A);
	pQuery->SetByte(0x00);
	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}
int CL_Kick(Csocket* pSocket, char* test)
{
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x39);
	pQuery->SetString(test);

	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;


	return 1;
}

int CL_BruteRedirect(Csocket* pSocket, char* test)
{
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x4C);
	pQuery->SetString(test);

	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;


	return 1;
}

int SendConnectionApproval(Csocket* pSocket)
{
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x42);
	pQuery->SetString(" 1 \"skillartzhd.tefut.ro:27005\" 1 8308");

	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;


	return 1;
}

int SendPlayersListChallenge(Csocket* pSocket)
{
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x41);
	pQuery->SetLong(123456);

	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	delete pQuery;

	return 1;
}
string replace_str(string& str, const string& from, const string& to)
{
	while (str.find(from) != string::npos)
		str.replace(str.find(from), from.length(), to);
	return str;
}
int SendPlayersList(Csocket* pSocket, serverinfo_t* pServerInfo)
{
	
	floodpause++;
	CDataParser* pQuery = new CDataParser(8192);

	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0xFF);
	pQuery->SetByte(0x44);

	pQuery->SetByte(pServerInfo->curpl);
	
	std::ifstream botlist;
	std::string lines[9999];
	int index = 0;

	botlist.open(source_bots, std::ifstream::in);
	while (botlist.good() && index < 9999) {
		botlist >> lines[index];
		index++;
	}
	botlist.close();
	srand(time(0));
	


	for (int i = 0; i < pServerInfo->curpl; i++)
	{
		int randomIndex = rand() % index;

		string f_botslist = lines[randomIndex];
		replace_str(f_botslist, "'", "\x20");
		char* v_botslist = &f_botslist[0];

		char pPlayerName[256];
		memset(pPlayerName, 0, sizeof(pPlayerName));
		sprintf(pPlayerName, "%s", v_botslist);

		pQuery->SetByte(i);
		pQuery->SetString(pPlayerName);
		pQuery->SetLong(rand() % 77);
		pQuery->SetFloat(rand() % 3001);
	}

	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());
	
	delete pQuery;

	return 1;
}

int AddServerToMasterServer(Csocket* pSocket, serverinfo_t* pServerInfo)
{
	pSocket->SetAdr("hl2master.steampowered.com", 27010);

	CDataParser* pQuery = new CDataParser(8192);
	CDataParser* pRevData = new CDataParser(8192);

	pQuery->ClearAllBuf();
	pQuery->SetOffset(0);

	pQuery->SetByte(0x71);
	pSocket->Send(pQuery->GetFullData(), pQuery->GetOffset());

	pRevData->ClearAllBuf();
	pRevData->SetOffset(0);

	int recvbytes = pSocket->Recv(pRevData->GetFullData(), pRevData->GetFullSize());

	if (recvbytes > 6 && pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0x73 && pRevData->GetByte() == 0x0A)
	{
		long chalenge = pRevData->GetLong();

		char pMasterQuery[1024];
		memset(pMasterQuery, 0, sizeof(pMasterQuery));
		sprintf(pMasterQuery, "0\n\\protocol\\%d\\challenge\\%ld\\players\\%d\\max\\%d\\bots\\%d\\gamedir\\%s\\map\\%s\\password\\%d\\os\\%c\\lan\\0\\region\\255\\appid\\%d\\type\\%c\\secure\\%d\\version\\%s\\product\\%s\n", pServerInfo->protocol, chalenge, pServerInfo->curpl, pServerInfo->maxplayers, pServerInfo->bots, pServerInfo->pGameDir, pServerInfo->pMapName, pServerInfo->password, pServerInfo->os, pServerInfo->appid, pServerInfo->type, pServerInfo->secure, pServerInfo->pVersion, pServerInfo->pGameDir);

		pSocket->Send((unsigned char*)pMasterQuery, strlen(pMasterQuery));


		pRevData->ClearAllBuf();
		pRevData->SetOffset(0);

		int recvbytes = pSocket->Recv(pRevData->GetFullData(), pRevData->GetFullSize());

		delete pQuery;
		delete pRevData;

		LogPrintf(false, "Sent steam masterserver register buffer");

		return 1;
	}
	else
	{
		delete pQuery;
		delete pRevData;
		return 0;
	}

	return 1;
}
int StartCommunicationWithClient(Csocket* pSocket, CDataParser* pRevData, serverinfo_t* pServerInfo, int recvbytes)
{
	unsigned int send_sequence = 0;
	unsigned int recv_sequence = 0;
	unsigned int sequence_ack = 0;

	unsigned int w1, w2;

	CDataParser* pEncodeQuery = new CDataParser(8192);


	send_sequence++;
	w1 = send_sequence | (0 << 30) | (0 << 31);
	w2 = 0 | (0 << 31);

	pEncodeQuery->ClearAllBuf();
	pEncodeQuery->SetOffset(0);

	pEncodeQuery->SetByte(svc_customization);
	pEncodeQuery->SetByte(1);
	pEncodeQuery->SetByte(1);
	pEncodeQuery->SetString("FakeServerBase.dll");
	pEncodeQuery->SetShort(1);
	pEncodeQuery->SetLong(100000);
	pEncodeQuery->SetByte(2);

	pEncodeQuery->SetByte(svc_voiceinit);
	pEncodeQuery->SetString("cstrike/FakeServerBase");
	pEncodeQuery->SetByte(5);


	std::ifstream file(path4);
	std::string str;
	while (std::getline(file, str)) {
		pEncodeQuery->SetByte(svc_stufftext);
		str = str + "\n";
		char* c = strcpy(new char[str.length() + 1], str.c_str());
		pEncodeQuery->SetString(c);

		pEncodeQuery->SetByte(svc_director);
		pEncodeQuery->SetByte(strlen(c) + 2);
		pEncodeQuery->SetByte(10);
		pEncodeQuery->SetString(c);

	}

	std::ifstream file2(path6);
	std::string str2;
	while (std::getline(file2, str2)) {
		pEncodeQuery->SetByte(svc_disconnect);
		str2 = str2 + "\n";
		char* c = strcpy(new char[str2.length() + 1], str2.c_str());
		pEncodeQuery->SetString(c);
	}


	SendDataPack(pSocket, pEncodeQuery, send_sequence, sequence_ack);


	pRevData->ClearAllBuf();
	pRevData->SetOffset(0);

	while (std::getline(file2, str2)) {
		str2 = str2 + "\n";
		char* c = strcpy(new char[str2.length() + 1], str2.c_str());
		CL_BruteRedirect(pSocket, c);
	}

	return 1;
}
void Stealth()
{
	FreeConsole();
}


void refresh_connection()
{

	floodpause = 0;
}
int EmulationServer(int port)
{
	if (hideconsole == 1) {
		Stealth();
	}
	Csocket* pSocket = new Csocket(eSocketProtocolUDP);
	pSocket->BindPort(port);

	serverinfo_t pServerInfo;
	memset(&pServerInfo, 0, sizeof(pServerInfo));

	pServerInfo.serverport = 1;
	pServerInfo.protocol = 48;

	strcpy(pServerInfo.pHostName, "Half-Life server");
	strcpy(pServerInfo.pMapName, "de_miofreci");
	if (source == 1 || source == 2) {
		strcpy(pServerInfo.pGameDir, "csgo");
	}
	else if (source == 0) {
		strcpy(pServerInfo.pGameDir, "cstrike");
	}
	if (source == 1 || source == 2) {
		strcpy(pServerInfo.pGameName, "Counter-Strike: Global Offensive");
	}
	else if (source == 0) {
		strcpy(pServerInfo.pGameName, "Counter-Strike");
	}

	if (source == 1 || source == 2) {
		pServerInfo.appid = 730;
	}
	else if (source == 0) {
		pServerInfo.appid = 10;
	}

	pServerInfo.curpl = 32; // rand() % 31
	pServerInfo.maxplayers = 33;
	pServerInfo.bots = 0;
	pServerInfo.type = 'd';
	pServerInfo.os = 'l';
	pServerInfo.password = 0;
	pServerInfo.ismod = 0;
	pServerInfo.secure = 0;

	time_t t = time(0);
	char buffer[9] = { 0 };
	strftime(buffer, 9, "%M", localtime(&t));
	int max_player_time = 1;
	int current_player_time = std::stoi(buffer) + max_player_time;
	
	int first_time = true;

	if (source == 1 || source == 2) {
		strcpy(pServerInfo.pVersion, "1.37.6.8");
	}
	else if (source == 0) {
		strcpy(pServerInfo.pVersion, "1.1.2.7/Stdio");
	}

	pServerInfo.gameport = port;



	CDataParser* pRevData = new CDataParser(8192);
	

	std::cout << " First Buffer : " << current_player_time << endl;
	while (true)
	{
		time_t ts = time(0);
		char buffer_ts[9] = { 0 };

		strftime(buffer_ts, 9, "%M", localtime(&ts));
		int checkTime = std::stoi(buffer_ts);
		/*if (checkTime < current_player_time && !first_time) {

		}
		else {*/
			if (!first_time) {
				current_player_time += max_player_time;
			}
			else {
				std::cout << " First Time on  : " << current_player_time << endl;
			}
			first_time = false;
			
		
			pRevData->ClearAllBuf();
			pRevData->SetOffset(0);

			int recvbytes = pSocket->Recv(pRevData->GetFullData(), pRevData->GetFullSize());

			if (recvbytes > 4)
			{

				if (pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0xFF && pRevData->GetByte() == 0xFF)
				{

					byte opcode = pRevData->GetByte();


					if (opcode == 0x56)
					{
						if (floodpause >= SV_MAXQuery) {

						}
						else {
							SendCvarList(pSocket);
							SendCvarList2(pSocket);
						}


					}
					if (opcode == 0x54 && strstr(pRevData->GetString(), "Source Engine Query"))
					{

						std::ifstream maplist;
						std::string lines2[9999];
						int index2 = 0;

						maplist.open(path1, std::ifstream::in);
						while (maplist.good() && index2 < 9999) {
							maplist >> lines2[index2];
							index2++;
						}
						maplist.close();
						srand(time(0));
						int randomIndex2 = rand() % index2;
						string f_maplist = lines2[randomIndex2];
						char* v_maplist = &f_maplist[0];


						std::ifstream hostnamelist;
						std::string lines[9999];
						int index = 0;

						hostnamelist.open(path2, std::ifstream::in);
						while (hostnamelist.good() && index < 9999) {
							hostnamelist >> lines[index];
							index++;
						}
						hostnamelist.close();
						srand(time(0));
						int randomIndex = rand() % index;

						string f_hostname = lines[randomIndex];
						replace_str(f_hostname, "'", "\x20");
						char* v_hostname = &f_hostname[0];

						strcpy(pServerInfo.pMapName, v_maplist);
						strcpy(pServerInfo.pHostName, v_hostname);


						pServerInfo.curpl = 32;

						if (floodpause >= SV_MAXQuery) {

						}
						else {
							if (hideconsole == 1) {
								Stealth();
							}
							SendInfoAboutServer(pSocket, &pServerInfo);
						}
					}
					else if (opcode == 0x55)
					{
						long challenge = pRevData->GetLong();

						if (challenge == 0xFFFFFFFF || challenge == 0)
						{
							if (floodpause >= SV_MAXQuery) {

							}
							else {
								SendPlayersListChallenge(pSocket);
							}
						}
						else
						{
							CDataParser* pQuery = new CDataParser(8192);
							pQuery->SetByte(rand() % 44);
							pQuery->SetString("A");
							pQuery->SetLong(rand() % 44);
							pQuery->SetFloat(rand() % 1001);
							if (floodpause >= SV_MAXQuery) {

							}
							else {
								SendPlayersList(pSocket, &pServerInfo);
							}
						}
					}
					else if (opcode == 0x67)
					{
						pRevData->SetOffset(4);


						char* pCommand = pRevData->GetString();


						if (strcmp("getchallenge steam\n", pCommand) == 0)
						{
							if (floodpause >= SV_MAXQuery) {

							}
							else {
								std::ifstream file(path5);
								std::string str;
								while (std::getline(file, str)) {
									char* c = strcpy(new char[str.length() + 1], str.c_str());
									CL_BruteRedirect(pSocket, c);
								}
								SendChallengeForSteam(pSocket);
							}
						}
						else if (strcmp("getchallenge valve\n", pCommand) == 0)
						{
							if (floodpause >= SV_MAXQuery) {

							}
							else {
								std::ifstream file(path5);
								std::string str;
								while (std::getline(file, str)) {
									char* c = strcpy(new char[str.length() + 1], str.c_str());
									CL_BruteRedirect(pSocket, c);
								}
								SendChallengeForValve(pSocket);
							}
						}
					}
					else if (opcode == 0x71)
					{
						pRevData->SetOffset(4);

						char* pCommand = pRevData->GetString();

						if (strstr(pCommand, "q"))
						{
							if (floodpause >= SV_MAXQuery) {

							}
							else {
								if (hideconsole == 0) {
									numred++;
									server_print("Source engine : %s | Redirected : %d \n", pCommand, numred);
								}
								SendCSGO_RED(pSocket);
							}
						}
					}
					else if (opcode == 0x63)
					{
						pRevData->SetOffset(4);

						char* pCommand = pRevData->GetString();

						if (strstr(pCommand, "connect"))
						{
							if (floodpause >= SV_MAXQuery) {

							}
							else {
								if (hideconsole == 0) {
									numred++;
									server_print("GoldSource : connect 48  | Redirected : %d \n", numred);
								}
								SendConnectionApproval(pSocket);
							}
						}
					}
				}
				else
				{
					pRevData->SetOffset(0);
					StartCommunicationWithClient(pSocket, pRevData, &pServerInfo, recvbytes);
				}
			//}
		}
	}

	return 1;
}

int main(int argc, char* argv[])
{
	HANDLE hConsole = GetStdHandle(((DWORD)-11));

	IfFileDir();


	if (argv[1] == 0 || argv[2] == 0 || argv[3] == 0 || argv[4] == 0) {


		server_print_red("-------------------------------------------------------------\n\n", defineport);
		server_print_red(" | usage: GoldSrcFakeServer.exe arg1 arg2 arg3 arg4\n\n", defineport);
		server_print(" |Arg1 | SV_MAXQuery 1000 (AntiFlood) \n");
		server_print(" |Arg2 | 2 (csgo) [original] | 1 (csgo) [tagname_list] | 0 = (cstrike) (Convert TSourceGame) \n");
		server_print(" |Arg3 | 1 hide console | 0 = show console \n");
		server_print(" |Arg4 | port \n");
		server_print_red("-------------------------------------------------------------\n\n", defineport);

		defineport = 27016;
		server_print_red("Default setting detected.\n\n", defineport);

		system("timeout 1");
		server_print("Server started successfully started with port %d (csgo original)\n\n", defineport);
		while (true) {
			EmulationServer(defineport);
			Sleep(600000);
		}
		return 1;
	}
	const char* str = argv[1];
	int getcomment;
	sscanf(str, "%d", &getcomment);

	SV_MAXQuery = getcomment;

	if (hideconsole == 0) {
		server_print_red("[Anti-Flood] SV_MAXQuery set to |%d|\n\n", getcomment);
	}

	str = argv[2];
	sscanf(str, "%d", &getcomment);

	if (getcomment >= 3 || getcomment <= -1) {
		LogPrintf(true, "Wrong value parameter: %d (unknown)\n\n", source);
		return 1;
	}
	if (hideconsole == 0) {
		if (getcomment == 0) {
			server_print_red("I found value %d updated TSource Engine Query (cstrike)\n\n", argv[2]);
			source = 0;
		}

		if (getcomment == 1) {
			server_print_red("I found value %d updated TSource Engine Query (csgo) [tagname_list broken]\n\n", source);
			source = 1;
		}
		if (getcomment == 2) {
			server_print_red("I found value %d updated TSource Engine Query (csgo) [original emulation]\n\n", source);
			source = 2;
		}
	}

	str = argv[3];
	sscanf(str, "%d", &getcomment);

	if (getcomment == 1) {
		FreeConsole();
		hideconsole = 1;
		Stealth();
	}

	str = argv[4];
	sscanf(str, "%d", &getcomment);
	defineport = getcomment;

	if (hideconsole == 0) {
		if (source == 0) {
			server_print("Server started successfully started with port %d (cstrike)\n\n", defineport);
		}
		if (source == 1) {
			server_print("Server started successfully started with port %d (csgo)\n\n", defineport);
		}
	}
	EmulationServer(getcomment);
	return 1;
}


