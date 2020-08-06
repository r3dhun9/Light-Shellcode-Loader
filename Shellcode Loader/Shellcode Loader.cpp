#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("Usage: \"Shellcode Loader.exe\" <filename>");
		return -1;
	}

	FILE* fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		printf("Open file failed.");
		return -2;
	}
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	printf("Size: %ld\n", size);

	LPVOID mem = VirtualAlloc(NULL, size+1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	fread(mem, size + 1, 1, fp);
	fclose(fp);

	printf("Shellcode address: %p\n", mem);
	printf("Starting execute your shellcode, press any key to continue ...");
	getchar();
	((void(*)())mem)();

	VirtualFree(mem, 0, MEM_RELEASE);
	return 0;
}