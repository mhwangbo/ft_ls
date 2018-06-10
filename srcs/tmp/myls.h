#ifndef __MYLS_H__

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "errhdr.h"

#define	MAXDIRCOUNT	256
#define	MAXDIRNAME	256
#define	SIZE		256

struct directory
{
	char path[SIZE];		// ��ü ���
	char abspath[SIZE];		// ���� ���
	char property[2];		// �Ӽ�
	char permission[10];	// ����
	unsigned int nlink;		// ��ũ��
	char uname[SIZE];		// ����ڸ�
	char gname[SIZE];		// �׷��
	unsigned int filesize;	// ���� ũ��
	char filetime[SIZE];	// ���� ���� �ð�
	char linkname[SIZE];	// ��ũ�� ����Ű�� ���� �̸�
};

#endif	//__MYLS_H__
