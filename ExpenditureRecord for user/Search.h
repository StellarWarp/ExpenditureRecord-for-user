#pragma once
#include"LinkedList.h"
#include<string.h>
#define mode_date 1
#define mode_name 2
#define mode_amount 4
#define mode_type 8
#define mode_method 16
#define mode_site 32

struct Searchinfo
{
	unsigned int searchmode;
	struct Date date_low;
	struct Date date_top;
	char name[15];
	int amount_low;//x100
	int amount_top;
	enum ConsumeType type;
	char method[20];
	char site[30];
	char detail[50];
};
struct Searchinfo info_init()
{
	struct Searchinfo info;
	info.searchmode = 0;
	info.date_low.td = 0;
	info.date_top.td = 0;
	info.amount_low = 0;
	info.amount_top = 0;
	return info;
}
void __search_Record__(struct displayArray_Record* result, struct RecordList record, struct Searchinfo info)
{
	struct Record* pos = record.C_Record;
	while (pos)
	{
		//date search
		if (info.searchmode & mode_date)
		{
			if (info.date_low.td == 0)//无下限
			{
				if (!(datecmp(pos->date, info.date_top) <= 0))
				{
					pos = pos->next;
					break;
				}
			}
			else if (info.date_top.td == 0)//无上限
			{
				if (!(datecmp(pos->date, info.date_low) >= 0))
				{
					pos = pos->next;
					break;
				}
			}
			else if (!(datecmp(pos->date, info.date_low) >= 0 && datecmp(pos->date, info.date_top) <= 0))
			{
				pos = pos->next;
				break;
			}
		}
		//amount search
		if (info.searchmode & mode_amount)
		{
			if (info.amount_low == 0)//无下限
			{
				if (!(pos->amount <= info.amount_top))
				{
					pos = pos->next;
					break;
				}
			}
			else if (info.amount_top == 0)//无上限
			{
				if (!(pos->amount >= info.amount_low))
				{
					pos = pos->next;
					break;
				}
			}
			else if (!(pos->amount >= info.amount_low && pos->amount <= info.amount_top))
			{
				pos = pos->next;
				break;
			}
		}
		//type search
		if (info.searchmode & mode_type)
		{
			if (info.type != pos->type)
			{
				pos = pos->next;
				break;
			}
		}
		//method search
		if (info.searchmode & mode_method)
		{
			if (strcmp(info.method, pos->method) != 0)
			{
				pos = pos->next;
				break;
			}
		}
		//site search
		if (info.searchmode & mode_site)
		{
			if (strcmp(info.site, pos->site) != 0)
			{
				pos = pos->next;
				break;
			}
		}
		in_displayArray(result, pos);
		pos = pos->next;
	}
}
void search_Record(struct displayArray_Record* result, struct MemberList memberlist, struct Searchinfo info)
{
	if (info.searchmode & mode_name)
	{
		struct RecordList record;
		struct Member* member = memberlist.C_Member;
		while (member)
		{
			if (member->name == info.name)
			{
				record = member->record;
				break;
			}
			member = member->next;
		}
		__search_Record__(result, record, info);
	}
	else
	{
		struct Member* member = memberlist.C_Member;
		while (member)
		{
			__search_Record__(result, member->record, info);
			member = member->next;
		}
	}
	

}