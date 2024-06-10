#include <common.h>

int (*_sceIoAssign)(const char *, const char *, const char *, int, void *, long) = NULL;
int (*_sceIoUnassign)(const char *) = NULL;
int (*_sceIoOpen)(const char *, int, SceMode) = NULL;
int (*_sceIoClose)(SceUID) = NULL;
int (*_sceIoRead)(SceUID, void *, SceSize) = NULL;
int (*_sceIoWrite)(SceUID, const void *, SceSize) = NULL;
int (*_sceIoMkdir)(const char *, SceMode) = NULL;
int (*_sceKernelDelayThread)(int) = NULL;

void tthread(void)
{
	printf("Assigning flash1...");
	_sceIoUnassign("flash1:");
	SceUID f1 = _sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", 0, NULL, 0);
	if (f1 < 0)
	{
		TextColor(RED);
		printf(" failed! (0x%08x)\n\n", f1);
		TextColor(WHITE);
		printf("Please try running the program again. Exiting...");
		printf("Press any button to exit.");
		return;
	}
	else
	{
		TextColor(GREEN);
		printf(" success!\n");
	}

	TextColor(WHITE);
	printf("Reading custom_theme.dat...");

	SceUID ret = _sceIoOpen("flash1:/vsh/theme/custom_theme.dat", PSP_O_RDONLY, 0777);
	if (ret < 0)
	{
		TextColor(RED);
		printf(" failed! (0x%08x)\n\n", ret);
		TextColor(WHITE);
		printf("Maybe a custom theme wasn't set?\n");
		printf("Press any button to exit.");
		return;
	}
	else
	{
		TextColor(GREEN);
		printf(" success!\n");
	}

	TextColor(WHITE);
	printf("Dumping custom_theme.dat...");

	int read;
	u8 buf[512];

	_sceKernelDelayThread(500000);
	SceUID theme = _sceIoOpen("ms0:/PSP/THEME/custom_theme.ptf", PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777);
	if (theme < 0)
	{
		_sceIoMkdir("ms0:/PSP/THEME", 0777);
		theme = _sceIoOpen("ms0:/PSP/THEME/custom_theme.ptf", PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777);
	}

	while ((read = _sceIoRead(ret, buf, 512)) > 0)
		_sceIoWrite(theme, buf, read);

	_sceIoClose(ret);
	_sceIoClose(theme);
	_sceIoUnassign("flash1:");
	_sceKernelDelayThread(3000000);

	TextColor(GREEN);
	printf(" success!\n\n");
	TextColor(WHITE);
	printf("Saved as ms0:/PSP/THEME/custom_theme.ptf\n");
	printf("Press any button to exit.");
}

void kthread(void)
{
	_sceIoAssign = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0xB2A628C1);
	_sceIoUnassign = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0x6D08A871);
	_sceIoOpen = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0x109F50BC);
	_sceIoClose = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0x810C4BC3);
	_sceIoRead = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0x6A638D83);
	_sceIoWrite = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0x42EC03AC);
	_sceIoMkdir = pspXploitFindFunction("sceIOFileManager", "IoFileMgrForKernel", 0x06A70004);
	_sceKernelDelayThread = pspXploitFindFunction("sceThreadManager", "ThreadManForUser", 0xCEADEB47);

	SceUID kthreadID = k_tbl->KernelCreateThread("themadump_kthread", (void *)KERNELIFY(&tthread), 1, 0x20000, PSP_THREAD_ATTR_VFPU, NULL);
	if (kthreadID >= 0)
	{
		k_tbl->KernelStartThread(kthreadID, 0, NULL);
		k_tbl->waitThreadEnd(kthreadID, NULL);
	}
}