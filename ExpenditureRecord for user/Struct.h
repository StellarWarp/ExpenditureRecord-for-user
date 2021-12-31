#pragma once
#include"Date.h"

typedef unsigned long systemID;

enum ConsumeType
{
	食品, 日用品, 服装, 电器, 水电煤气, 房贷, 学费, 交通费
};
struct Record
{
	systemID systemid;
	systemID membersystemid;
	struct Date date;
	char name[15];
	int amount;//x100
	enum ConsumeType type;
	char method[20];
	char site[30];
	char detail[50];
	struct Record* next;
	struct Record* prev;
};

//使用前要初始化
struct RecordList
{
	struct Record* C_Record;
	struct Record* E_Record;
	unsigned int len;
};
struct Member
{
	systemID systemid;
	char name[20];
	int MemberSpending;
	struct RecordList record;
	struct Member* next;
	struct Member* prev;
};
struct MemberList
{
	struct Member* C_Member;
	struct Member* E_Member;
	unsigned int len;
};
struct Family
{
	systemID systemid;
	char FamilyName[20];
	struct MemberList menber;
};

