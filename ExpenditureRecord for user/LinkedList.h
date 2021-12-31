#pragma once
#include<stdio.h>
#include<malloc.h>
#include"Struct.h"
//结构体初始化
struct RecordList initial_RecordList()
{
	struct RecordList recordlist;
	recordlist.C_Record = NULL;
	recordlist.E_Record = NULL;
	recordlist.len = 0;
	return recordlist;
}
struct MemberList initial_MemberList()
{
	struct MemberList memberlist;
	memberlist.C_Member = NULL;
	memberlist.E_Member = NULL;
	memberlist.len = 0;
	return memberlist;
}

//使用前要初始化
void in_Record(struct RecordList* recordlist, struct Record* p_record, struct Record record)
{
	struct Record* newnode = (struct Record*)malloc(sizeof(struct Record));
	*newnode = record;

	if (recordlist->C_Record)
	{
		//链表插入
		newnode->next = p_record->next;
		if (p_record->next)
			p_record->next->prev = newnode;
		else
			recordlist->E_Record = newnode;
		p_record->next = newnode;
		newnode->prev = p_record;
		recordlist->len++;
	}
	else
	{
		//创建第一节点
		newnode->next = NULL;
		newnode->prev = NULL;
		recordlist->C_Record = recordlist->E_Record = newnode;
		recordlist->len = 1;
	}
}
void dele_Record(struct RecordList* recordlist, struct Record* record)
{
	if (record == recordlist->C_Record)
	{
		recordlist->C_Record = record->next;
	}
	if (record == recordlist->E_Record)
	{
		recordlist->E_Record = record->prev;
	}
	record->prev = record->next;
	record->next = record->prev;
	recordlist->len--;
	free(record);
}

void modify_Record(struct Record* precord, struct Record record)
{
	*precord = record;
}

//void swap_Record(struct Record** h, struct Record** a, struct Record** b)
//{
//	if ((*b)->next) (*b)->next->prev = (*a);
//	struct Record** temp = (*a)->next->prev;
//	(*b)->prev->next = (*a);
//	*temp = (*b);
//	if (a == *h) *h = (*b);
//	else (*a)->prev->next = (*b);
//	swap((*a)->next, (*b)->next);
//	swap((*a)->prev, (*b)->prev);
//	swap((*a), (*b));
//}
//使用前要初始化
struct displayArray_Record
{
	struct Record** Array;
	//struct Record* (*test)[10];
	int num;
	int len;
	struct Record** currentpos;
};
struct displayArray_Record initial_display()
{
	struct displayArray_Record array;
	array.Array = NULL;
	array.num = 0;
	array.currentpos = NULL;
	array.len = 0;
	return array;
}
void in_displayArray(struct displayArray_Record* displayArray, struct Record* record)
{
	int lenth = displayArray->len;
	int input_lenth = displayArray->num;
	struct Record** currentpos = displayArray->currentpos;
	if (lenth)
	{
		*currentpos = record;
		input_lenth++;
		currentpos++;
		if (input_lenth == lenth)
		{
			displayArray->Array = realloc(displayArray->Array, (lenth *= 2) * sizeof(struct Record*));
			//displayArray->test = (struct Record* (*)[10])displayArray->Array;//测试
			currentpos = displayArray->Array + input_lenth;
		}
		displayArray->len = lenth;
		displayArray->num = input_lenth;
		displayArray->currentpos = currentpos;
	}
	else
	{
		displayArray->len = 4;
		displayArray->currentpos = displayArray->Array = (struct Record**)calloc(4, sizeof(struct Record*));
		//displayArray->test = (struct Record* (*)[10])displayArray->Array;//测试
		*displayArray->currentpos = record;
		displayArray->currentpos++;
		displayArray->num = 1;
	}
}

void in_Member(struct MemberList* recordlist, struct Member* p_record, struct Member record)
{
	struct Member* newnode = (struct Member*)malloc(sizeof(struct Member));
	*newnode = record;

	if (recordlist->C_Member)
	{
		//链表插入
		newnode->next = p_record->next;
		if (p_record->next)
			p_record->next->prev = newnode;
		else
			recordlist->E_Member = newnode;
		p_record->next = newnode;
		newnode->prev = p_record;
		recordlist->len++;
	}
	else
	{
		//创建第一节点
		newnode->next = NULL;
		newnode->prev = NULL;
		recordlist->C_Member = recordlist->E_Member = newnode;
		recordlist->len = 1;
	}
}
void dele_Member(struct MemberList* recordlist, struct Member* record)
{
	if (record == recordlist->C_Member)
	{
		recordlist->C_Member = record->next;
	}
	if (record == recordlist->E_Member)
	{
		recordlist->E_Member = record->prev;
	}
	record->prev = record->next;
	record->next = record->prev;
	recordlist->len--;
	free(record);
}

void modify_Member(struct Member* precord, struct Member record)
{
	*precord = record;
}

//void swap_Member(struct Member** h, struct Member** a, struct Member** b)
//{
//	if ((*b)->next) (*b)->next->prev = (*a);
//	struct Member** temp = (*a)->next->prev;
//	(*b)->prev->next = (*a);
//	*temp = (*b);
//	if (a == *h) *h = (*b);
//	else (*a)->prev->next = (*b);
//	swap((*a)->next, (*b)->next);
//	swap((*a)->prev, (*b)->prev);
//	swap((*a), (*b));
//}
//使用前要初始化
struct displayArray_Member
{
	struct Member** Array;
	int num;
	int len;
	struct Member** currentpos;
};
void in_displayArray_m(struct displayArray_Member* displayArray, struct Member* record)
{
	int lenth = displayArray->len;
	int input_lenth = displayArray->num;
	struct Member** currentpos = displayArray->currentpos;
	if (lenth)
	{
		*currentpos = record;
		input_lenth++;
		currentpos++;
		if (input_lenth == lenth)
		{
			displayArray->Array = realloc(displayArray->Array, (lenth *= 2) * sizeof(struct Member*));
			currentpos = displayArray->Array + input_lenth;
		}
		displayArray->len = lenth;
		displayArray->num = input_lenth;
		displayArray->currentpos = currentpos;
	}
	else
	{
		displayArray->len = 4;
		displayArray->currentpos = displayArray->Array = (struct Member**)calloc(4, sizeof(struct Member*));
		*displayArray->currentpos = record;
		displayArray->currentpos++;
		displayArray->num = 1;
	}
}