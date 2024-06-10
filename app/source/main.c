#include <common.h>

PSP_HEAP_SIZE_MAX();
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);
PSP_MODULE_INFO("themadump", PSP_MODULE_USER, VER_MAJOR, VER_MINOR);

static KernelFunctions _ktbl;
KernelFunctions *k_tbl = &_ktbl;

void kmain(void)
{
	int k1 = pspSdkSetK1(0);
	pspXploitScanKernelFunctions(k_tbl);
	pspXploitRepairKernel();
	kthread();
	pspSdkSetK1(k1);
}

int main(void)
{
	pspDebugScreenInit();
	pspDebugScreenClear();
	SceCtrlData pad;

	BackColor(BLACK);
	TextColor(WHITE);
	printf("themadump v%i.%i - github.com/catmagicspell/themadump\n\n", VER_MAJOR, VER_MINOR);

	int ret;
	ret = pspXploitInitKernelExploit();

	if (ret == 0)
	{
		ret = pspXploitDoKernelExploit();
		if (ret == 0)
		{
			pspXploitExecuteKernel(kmain);
			sceDisplayWaitVblank();
		}
		else
		{
			TextColor(RED);
			printf("Error: pspXploitDoKernelExploit = 0x%08x\n", ret);
		}
	}
	else
	{
		TextColor(RED);
		printf("Error: pspXploitInitKernelExploit = 0x%08x\n", ret);
	}

	while (1)
	{
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons)
			break;
	}

	sceKernelExitGame();
	return 0;
}