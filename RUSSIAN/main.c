//// Basic source code MemStickTest by Adrahil
//// http://forums.ps2dev.org/viewtopic.php?p=69085#69085
//// Modification and Russification: ErikPshat

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "../res/mdumper_prx.h"

PSP_MODULE_INFO("MemStickTest", 0, 1, 0);

PSP_MAIN_THREAD_ATTR(0);

#define printf pspDebugScreenPrintf
#define color pspDebugScreenSetTextColor
#define exit sceKernelExitGame

#define blue 0xff0000
#define erikpshat 0x6600cc
#define green 0x00ff00
#define red 0x0000ff
#define purple 0xff00ff
#define orange 0x0099ff


void ErrorExit(int milisecs, char *fmt, ...)
{ 
		va_list list;
		char msg[256];

		va_start(list, fmt);
		vsprintf(msg, fmt, list);
		va_end(list);

		printf(msg);

		sceKernelDelayThread(milisecs*1000);
		sceKernelExitGame();
}

int pspMsReadAttrB(int attr, void *addr); 

u8		buffer[1024*1024];
u8		msid[16];
int main()
{ 
		int i; 
		u32 sysinfo_addr = 0;
		u32 modname_addr = 0;
		wbmspro_attribute_t *ptr_attr = 0;
		wbmspro_device_info_entry_item_t *ptr_entry = 0;
		wbmspro_sys_info_t* s_info = 0;
		unsigned char msid[1] = "";
		pspSdkLoadStartModule("mdumper.prx", PSP_MEMORY_PARTITION_KERNEL);

		pspDebugScreenInit();		
		color(purple);
		printf("MemStickTest by Adrahil  ");
		color(erikpshat);
		printf("-= MOD RUS by ErikPshat =-\n\n");
		
		color(green);
		printf("Эта программа создаст в корне карты памяти файл ");
		color(erikpshat);
		printf("msid.bin\n");
		color(green);
		printf("И ещё все 3 секции по 512 байт атрибутов в файл ");
		color(erikpshat);
		printf("attr.bin\n\n");

		color(orange);
		printf("Результат сектора 0 = %08X\n", pspMsReadAttrB(0, buffer));
		printf("Результат сектора 1 = %08X\n", pspMsReadAttrB(1, buffer + 512));
		printf("Результат сектора 2 = %08X\n\n", pspMsReadAttrB(2, buffer + 1024));
		
		color(red);
		printf("Чтение даных из атрибутов и ");
		int fd = sceIoOpen("ms0:/attr.bin", PSP_O_WRONLY | PSP_O_CREAT, 0777);
		sceIoWrite(fd, buffer, 3*512);
		sceIoClose(fd);
		printf("запись в файлы ");
		color(erikpshat);
		printf("attr.bin");
		color(red);
		printf(", ");
		color(erikpshat);
		printf("msid.bin");
		color(red);
		printf(" - OK!\n\n");
		
		color(orange);
		ptr_attr = (wbmspro_attribute_t*) buffer;
		printf("Сигнатура: %04X (должно быть 0xA5C3)\n", WSBH(ptr_attr->signature));
		printf("Версия:    %04X\n\n", WSBH(ptr_attr->version));
		
		printf("Количество записей: %02X\n", ptr_attr->device_information_entry_count);
		for (i = 0; i < ptr_attr->device_information_entry_count; i++){
				ptr_entry = (wbmspro_device_info_entry_item_t*) (buffer+ 0x10 + 0xC*i);
				printf("Запись: %d  ID: %01X  ", i, ptr_entry->info_id);
				printf("Позиция: 0x%03X  Размер: 0x%01X\n", (unsigned int)WSBW(ptr_entry->address), (unsigned int)WSBW(ptr_entry->size));

				switch (ptr_entry->info_id){
						case 0x10: sysinfo_addr = (int)buffer + WSBW(ptr_entry->address); break;
						case 0x15: modname_addr = (int)buffer + WSBW(ptr_entry->address); break;
						default: break;
				}
		}
		s_info = (wbmspro_sys_info_t*) sysinfo_addr;
		color(blue);
		printf("\n\n");
		color(purple);
		printf("Серийный номер: %08X\n", (unsigned int)s_info->serial_number);
		printf("Номер MSPro ID: ");
		color(red);
		printf("0x");
		int f = sceIoOpen("ms0:/msid.bin", PSP_O_WRONLY | PSP_O_CREAT, 0777);
		for(i = 0; i< 0x10; i++){
				printf("%02X", s_info->mspro_id[i]);
				msid[0] = buffer[i+0x1E0];
				sceIoWrite(f, msid, sizeof(msid));
				}
		sceIoClose(f);
		color(purple);
		printf("\nСтандарт карты: %s\n\n", (char*)modname_addr);
		
		color(green);
		printf("Нажмите  для выхода\n");
		while (1)
		{
		SceCtrlData pad;
		sceCtrlReadBufferPositive(&pad, 1);

		if (pad.Buttons & PSP_CTRL_CROSS)
			{
			sceKernelExitGame();
			break;
			}		
		sceKernelDelayThread(10000);
		}
		return 0; 
}