void
dirprint(unsigned int lsflag, char *dname)
{
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		file_stat;
	struct passwd	*userinfo;
	struct group	*grpinfo;
	struct tm		*time;

	struct directory *dir;

	char buff[80];
	char colstart[8];
	char colend[] = "[0m";
	int n=0, m=0, i=0;

	if((dp = opendir(dname)) == NULL)
		err_sys("can't open %s", dname);

	while(dirp = readdir(dp))
	{
		dir = (struct directory *)malloc(sizeof(struct directory));		
		memset(dir, 0, sizeof(dir));
		memset(buff, 0, sizeof(buff));
		memset(colstart, 0, sizeof(colstart));

		if(dirp->d_ino == 0)
			continue;

		if((lsflag & 0x01) == 0)
		{
			if(strncmp(dirp->d_name, ".", 1) == 0)
				continue;
		}

		sprintf(dir->path, "%s/%s", dname, dirp->d_name);

		if(lstat(dir->path, &file_stat) < 0)
			err_sys("can't read file stat");


		switch(file_stat.st_mode & S_IFMT)
		{
			case S_IFREG :
				dir->property[0] = '-';
				break;
			case S_IFDIR :
				dir->property[0] = 'd';
				strcpy(colstart, "[0;34m");	// ÆÄ¶õ»ö
				break;
			case S_IFIFO :
				dir->property[0] = 'p';
				break;
			case S_IFLNK :
				dir->property[0] = 'l';
				strcpy(colstart, "[0;36m");	// ¿¬³ì»ö
				readlink(dir->path, dir->linkname, SIZE);
				break;
			case S_IFBLK :
				dir->property[0] = 'b';
				strcpy(colstart, "[1;33m");	// ³ë¶õ»ö
				break;
			case S_IFCHR :
				dir->property[0] = 'c';
				strcpy(colstart, "[1;33m");	// ³ë¶õ»ö
				break;
		}
		dir->property[1] = '\0';

		for(n=0, m=0; n<3; n++, m+=3)
		{
			if(file_stat.st_mode & (S_IREAD >> (n*3)))
				dir->permission[m] = 'r';
			else
				dir->permission[m] = '-';
			
			if(file_stat.st_mode & (S_IWRITE >> (n*3)))
				dir->permission[m+1] = 'w';
			else
				dir->permission[m+1] = '-';
			
			if(file_stat.st_mode & (S_IEXEC >> (n*3)))
			{
				dir->permission[m+2] = 'x';
				
				if((file_stat.st_mode & S_IFMT) == S_IFREG)
					strcpy(colstart, "[0;32m");	// ³ì»ö
			}
			else
				dir->permission[m+2] = '-';
		}
		dir->permission[9] = '\0';
		if((lsflag & 0x02) != 0)
		{
			printf("%7ld ", dirp->d_ino);
		}
		if((lsflag & 0x04) == 0 || (lsflag == 0))
		{
			printf("%s%-25s%s", colstart, dirp->d_name, colend);
			
			i++;
			if(i == 4)
			{
				printf("\n");
				i = 0;
			}
		}
		else
		{
			dir->nlink = file_stat.st_nlink;
			
			userinfo = getpwuid(file_stat.st_uid);
			strcpy(dir->uname, userinfo->pw_name);

			grpinfo = getgrgid(file_stat.st_gid);
			strcpy(dir->gname, grpinfo->gr_name);

			dir->filesize = file_stat.st_size;

			time = localtime(&file_stat.st_mtime);
			strftime(buff, 80, "%b %e", time);
			strncpy(dir->filetime, buff, 80);
			strftime(buff, 80, "  %G", time);
			if(strcmp(buff, "  2006") < 0)
			{
				strcat(dir->filetime, buff);
				dir->filetime[sizeof(dir->filetime)-1] = '\0';
			}
			else
			{
				strftime(buff, 80, " %R", time);
				strcat(dir->filetime, buff);
				dir->filetime[sizeof(dir->filetime)-1] = '\0';
			}

			printf("%s%s %4d %-8s %-8s %8d  %s ", dir->property, dir->permission, dir->nlink,\
			dir->uname, dir->gname, dir->filesize, dir->filetime);
			printf("%s%s%s", colstart, dirp->d_name, colend);
			if(strlen(dir->linkname))
				printf(" -> %s\n", dir->linkname);
			else
				printf("\n");
		}
	}
	closedir(dp);
}
