<!--
{
	"author": "lxf",
	"title": "C语言文件操作函数",
	"date": "2019-04-11 02:45:27",
	"category": "C语言程序设计"
}
-->

C语言文件操作函数
------------------------------------------------------------
``` 
int main()
{
	FILE *fpr, *fpw;
	char ch;
	char buffer[255];
	memset(buffer, 0, 255);
	fopen_s(&fpw, "file.txt", "w");
	fpr = fopen("CFileOperate.cpp", "r");
	
	do
	{
		int iret = feof(fpr);
		printf("---%u  ----\n", iret);
		if (iret == 1) break;
		ch = fgetc(fpr);
		printf("%c", ch);
		fputc(ch, fpw);
	} while (1/*ch != EOF*/);

	while (fgets(buffer, 255, fpr))
	{
		puts(buffer);
		fputs(buffer, fpw);
	}

	while (fscanf(fpr, "%s", buffer) != EOF)
	{
		puts(buffer);
		memset(buffer, 0, 255);
	}
	fprintf(fpw, "%s", "hello");

	gets_s(buffer, 255);
	puts(buffer);
	fwrite(buffer, 1, strlen(buffer), fpw);
	/*fread(buffer, 1, 254, fpr);
	puts(buffer);

	while (1)
	{
		int iret = getw(fpr);
		if (iret == EOF) break;
		printf("%u ", iret);
	}
	putw(65536, fpw);

	while (1)
	{
		int iret = feof(fpr);
		if (iret == EOF) break;
		printf("%u ", iret);
	}

	int iseek = fseek(fpr, 1, 1);
	printf("%u ", iseek);

	fclose(fpr);
	fclose(fpw);
	return 0;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/C语言程序设计/README.md)  |
[返回首页](./../../../../README.md)