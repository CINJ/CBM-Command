/***************************************************************
Copyright (c) 2010, Payton Byrd
All rights reserved.

Redistribution and use in source and binary forms, with or
without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the following
  disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the following
  disclaimer in the documentation and/or other materials
  provided with the distribution.

* Neither the name of Payton Byrd nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior written
  permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#include "cbm.h"


#include "CBM-REL.h"

unsigned char getRecordSize(
	const unsigned char command_lfn,
	const unsigned char logical_file_number,
	const unsigned char unit_number,
	const unsigned char secondary,
	const char* file_name)
{
	const static unsigned char s=128;
	unsigned char result=0;
	unsigned char r=0;
	static unsigned char relFileName[21];
	static unsigned char commandBuffer[12]; // = { 'p', 2, 1, itoc(0), itoc(128), '\0' };
	static unsigned char errorBuffer[256];

	sprintf(relFileName, ":%s,l", file_name);

	result = cbm_open(
		logical_file_number, unit_number, 
		secondary, relFileName);

	if(result == 0)
	{
		for(r=1; r<254; ++r)
		{
			commandBuffer[0] = 'p';
			commandBuffer[1] = secondary;
			commandBuffer[2] = 1;
			commandBuffer[3] = 0;
			commandBuffer[4] = r;
			commandBuffer[5] = '\0';

			cbm_write(command_lfn, commandBuffer, 5);

			cbm_read(command_lfn, errorBuffer, sizeof errorBuffer);

			if(errorBuffer[0] != '0')
			{
				--r;
				break;
			}
		}

		if(r == 255) r = 254;

		cbm_close(logical_file_number);
	}
	else
	{
		return -1;
	}

	return r;
}
//
//struct rel_file* openRelativeFile(
//	const unsigned char logical_file_number,
//	const unsigned char unit_number,
//	const unsigned char secondary,
//	const unsigned char record_size,
//	const char* file_name,
//	bool count_records)
//{
//	static unsigned char file[21], command[] = "p    ";
//	char result = 0;
//	unsigned int count = 0;
//	struct rel_file file_struct;
//
//	
//	//printf("\r\n--------------------\r\nOpening relative file %s", file_name);
//	//sprintf(file, "%s,l,", file_name);
//
//	file[strlen(file) + 1] = '\0';
//	file[strlen(file)] = record_size;
//
//	//cbm_open(127u, unit_number, 15u, "");
//	result = cbm_open(logical_file_number, unit_number, secondary, file);
//	//cbm_read(127u, errorBuffer, sizeof errorBuffer);
//	//printf("errorChannel: %s", errorBuffer);
//	//cbm_close(127u);
//
//	if(result != 5)
//	{
//		strcpy(file_struct.file_name, file_name);
//		file_struct.record_size = record_size;
//		if(count_records)
//		{
//			cbm_open(127u, unit_number, 15u, "");
//			command[1] = secondary;
//			command[4] = 1u;
//			for(count = 0; count < 65535; ++count)
//			{
//				command[2] = count % 256u;
//				command[3] = count / 256u;
//				result = cbm_write(127u, command, 5u);
//				if(result == -1) break;
//			}
//			cbm_close(127u);
//		}
//
//		file_struct.record_count = count;
//	}
//
//	return &file_struct;
//}
//
//char __fastcall getRecord(
//	const unsigned char logical_file_number,
//	const unsigned char unit_number,
//	const unsigned char secondary,
//	struct rel_file_rec* record,
//	const unsigned char rel_size)
//{
//	char result = 0;
//	static unsigned char errorBuffer[41], file[21], command[] = "p    ";
//	static unsigned char temp[3];
//	//printf("\r\n-----------------------\r\nLFN: %u  UN: %u  Sec: %u", logical_file_number, unit_number, secondary);
//	cbm_open(127u, unit_number, 15u, "");
//	command[1] = 96 + logical_file_number;
//	command[2] = record->record_number % 256;
//	command[3] = record->record_number / 256;
//	command[4] = rel_size;
//	result = cbm_write(127u, command, 5u);
//	result = cbm_write(127u, command, 5u);
//	if(result > -1)
//	{
//		cbm_read(logical_file_number, record->record_data, rel_size);
//		cbm_read(127u, errorBuffer, sizeof errorBuffer);
//		temp[0] = errorBuffer[0];
//		temp[1] = errorBuffer[1];
//		temp[2] = '\0';
//		result=atoi(temp);
//	}
//	cbm_close(127u);
//
//	return result;
//}
//
//char __fastcall saveRecord(
//	const unsigned char logical_file_number,
//	const unsigned char unit_number,
//	const unsigned char secondary,
//	struct rel_file_rec* record,
//	const unsigned char rel_size)
//{
//	char result = 0;
//	static unsigned char errorBuffer[256], file[21], command[] = "p    ";
//
//	cbm_open(127u, unit_number, 15u, "");
//	command[1] = 96 + logical_file_number;
//	command[2] = record->record_number % 256u;
//	command[3] = record->record_number / 256u;
//	command[4] = rel_size;
//	result = cbm_write(127u, command, 5u);
//	cbm_read(127u, errorBuffer, sizeof errorBuffer);
//	printf("\r\n================\r\nWrite Step 1 - result: %u errorBuffer: %s\r\n", result, errorBuffer);
//	if(result > -1)
//	{
//		result = cbm_write(logical_file_number, record->record_data, rel_size);
//		cbm_read(127u, errorBuffer, sizeof errorBuffer);
//		printf("\r\n================\r\nWrite Step 2 - result: %u errorBuffer: %s\r\n", result, errorBuffer);
//	}
//	result = cbm_write(127u, command, 5u);
//	cbm_read(127u, errorBuffer, sizeof errorBuffer);
//	printf("\r\n================\r\nWrite Step 3 - result: %u errorBuffer: %s\r\n", result, errorBuffer);
//	cbm_close(127u);
//
//	return result;
//}
//
//char initializeRelativeFile(
//	const unsigned char unit_number,
//	const unsigned char record_size,
//	const unsigned int record_count,
//	const char* file_name)
//{
//	static char result = 0;
//	static unsigned int count = 0u;
//	static struct rel_file* file;
//	static struct rel_file_rec rec;
//	
//	file = openRelativeFile(
//		126u, unit_number, 2u,
//		record_size, file_name, false);
//
//	if(file != NULL)
//	{
//		rec.file = file;
//	
//		for(count = 0; count < record_size; ++count)
//		{
//			rec.record_data[count] = count % 256;
//		}
//
//		for(count = 0; count < record_count; ++count)
//		{
//			rec.record_number = count;
//			result = saveRecord(126, unit_number, 2, &rec, record_size);
//
//			if(result == -1)
//			{
//				break;
//			}
//		}
//
//		cbm_close(126);
//		return result;
//	}
//
//	return -1;
//}
