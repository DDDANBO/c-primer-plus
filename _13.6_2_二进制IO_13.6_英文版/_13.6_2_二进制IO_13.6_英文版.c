
//�ٴ���Ϥ�������ļ�IO���Ѷ���ļ��Ķ���������׷�ӵ�һ���ļ���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEFILE 81
#define SIZEBUF 1024

void append(FILE * src, FILE * dest);

int main(void)
{
	char file_app[SIZEFILE];		//Ҫ׷�ӵ�Ŀ���ļ���
	char file_src[SIZEFILE];		//Դ�ļ���
	FILE * fa, *fs;					//faָ��׷�ӵ�Ŀ���ļ���fsָ��Դ�ļ�
	int count = 0;						//Դ�ļ�������

	system("color 5A");
	//��ȡ׷���ļ���
	puts("Enter name of destination file:");
	gets_s(file_app, SIZEFILE);

	//��Ҫ׷�ӵ�Ŀ���ļ�,�����������ı�����
	if (fopen_s(&fa, file_app, "a") != 0)
	{
		fprintf(stderr, "Can't open file %s!\n", file_app);
		exit(EXIT_FAILURE);
	}

	//����������Ļ�����
	if (setvbuf(fa, NULL, _IOFBF, SIZEBUF) != 0)
	{
		fputs("Can't create output buffer!\n", stderr);
		exit(EXIT_FAILURE);
	}

	//ѭ����ȡԴ�ļ���
	puts("Enter name of first file (empty to quit):");
	while (gets_s(file_src, SIZEFILE) != NULL && file_src[0] != '\0')
	{
		//����ļ����ظ�,���������������һ��Դ�ļ���
		if (strcmp(file_app, file_src) == 0)
		{
			fputs("Can't append file to itself.\n", stderr);
		}
		//��Դ�ļ���������������ı�����,�ɹ�������ʧ��������һ��Դ�ļ���
		else if (fopen_s(&fs, file_src, "r") != 0)
		{
			fprintf(stderr, "Can't open file %s!\n", file_src);
		}
		else
		{
			//�����������Ļ�����
			if (setvbuf(fs, NULL, _IOFBF, SIZEBUF) != 0)
			{
				fputs("Can't create input buffer!\n", stderr);
				continue;
			}
			append(fs, fa);									//׷������
			//����д����
			if (ferror(fa) != 0)
			{
				fprintf(stderr, "Error in writing file %s.\n", file_app);
			}
			if (ferror(fs) != 0)
			{
				fprintf(stderr, "Error in reading file %s.\n", file_src);
			}
			fclose(fs);										//�ر�Դ�ļ�(ͬʱ���ٻ�����)
			++count;										//������+1
			puts("Next name (empty to quit):");
		}
	}
	fclose(fa);												//�ر�׷���ļ�(ͬʱ���ٻ�����)
	fprintf(stdout, "Done. %d files appended.\n", count);

	system("pause");
	return 0;

}

void append(FILE * src, FILE * dest)
{
	size_t count, wc = 0;
	static char temp[SIZEBUF];								//����һ��

	while ((count = fread(temp, sizeof(char), SIZEBUF, src)) > 0)			/*�ܺã������˼���Сʱ������֪��Ϊʲôֻдһ���ַ�������
																			��TM��count=fread()>0û�����ţ���Ȼ���������ܣ�����û�����ţ��Լ����ɣ�
																			д����������ȥ�ģ����Ÿ����ˣ���Ȼ�Ǹ������*/
	{
		wc += fwrite(temp, sizeof(char), count, dest);
	}

	return;
}