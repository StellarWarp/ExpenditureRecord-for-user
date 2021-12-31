#pragma once
#include<stdio.h>
#include"Struct.h"
#include"LinkedList.h"
#include<string.h>


void print_Date(struct Date date)
{
	printf("%4d.%2d.%2d", date.y, date.m, date.d);
}
void print_Record(struct Record record, int printform[])
{
	float amount = (float)record.amount / 100;
	char type[15];
	if (record.type == 食品) strcpy_s(type, 15, "食品");
	if (record.type == 日用品) strcpy_s(type, 15, "日用品");
	if (record.type == 服装)strcpy_s(type, 15, "服装");
	if (record.type == 电器)strcpy_s(type, 15, "电器");
	if (record.type == 水电煤气)strcpy_s(type, 15, "水电煤气");
	if (record.type == 房贷)strcpy_s(type, 15, "房贷");
	if (record.type == 学费)strcpy_s(type, 15, "学费");
	if (record.type == 交通费)strcpy_s(type, 15, "交通费");
	print_Date(record.date);
	printf(" %10s %7.2f %15s %10s %10s %10s", 
		record.name,amount,type,record.method,record.site,record.detail);
}