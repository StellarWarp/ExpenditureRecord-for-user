#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Struct.h"
#include"LinkedList.h"

void wirtefile_Record(struct RecordList recordlist)
{
	struct Record* record = recordlist.C_Record;
	FILE* outfile = NULL;
	if (fopen_s(&outfile, "Data/fee.dat", "wb"))
	{
		printf("Fail to open fee.bdat\n");
		exit(-1);
	}
	while (record)
	{
		fwrite(record, sizeof(struct Record), 1, outfile);
	}
}
void readfile_Record_all(struct RecordList* recordlist)
{
	struct Record record;
	FILE* infile = NULL;
	if (fopen_s(&infile, "Data/fee.dat", "rb"))
	{
		printf("Fail to open fee.bdat\n");
		exit(-1);
	}
	fread(&record, sizeof(struct Record), 1, infile);
	while (!feof(infile))
	{
		in_Record(recordlist, recordlist->E_Record, record);
		fread(&record, sizeof(struct Record), 1, infile);
	}
}
struct Member* search_member(struct MemberList memberlist, systemID id)
{
	struct Member* member = memberlist.C_Member;
	while (member)
	{
		if (member->systemid == id)
		{
			return member;
		}
		member = member->next;
	}

}
void import_to_member(struct RecordList* source, struct MemberList memberlist)
{
	struct Record* record = source->C_Record;
	int num = 0;
	while (record)
	{
		struct Member* member = search_member(memberlist, record->membersystemid);
		member->record = *source;
		while (record&&member->systemid == record->membersystemid )
		{
			record = record->next;
			num++;
		}
		//分段
		if (record)
		{
			record->prev->next = NULL;
			member->record.E_Record = record->prev;
			member->record.len += num;
			source->len -= num;
			num = 0;
			source->C_Record = record;
			record->prev = NULL;
		}
	}
}

void readfile_Member(struct MemberList* memberlist)
{
	struct Member member;
	FILE* infile = NULL;
	if (fopen_s(&infile, "Data/member.bin", "rb"))
	{
		printf("Fail to open member.bin\n");
		exit(-1);
	}
	fread(&member, sizeof(struct Member), 1, infile);
	while (!feof(infile))
	{
		member.record = initial_RecordList();
		in_Member(memberlist, memberlist->E_Member, member);
		fread(&member, sizeof(struct Member), 1, infile);
	}
}