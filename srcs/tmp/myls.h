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
	char path[SIZE];		// 전체 경로
	char abspath[SIZE];		// 절대 경로
	char property[2];		// 속성
	char permission[10];	// 권한
	unsigned int nlink;		// 링크수
	char uname[SIZE];		// 사용자명
	char gname[SIZE];		// 그룹명
	unsigned int filesize;	// 파일 크기
	char filetime[SIZE];	// 파일 접근 시간
	char linkname[SIZE];	// 링크가 가리키는 파일 이름
};

#endif	//__MYLS_H__
