#include "myls.h"
#include "errhdr.h"

void dirprint(unsigned int lsflag, char *dname);

int
main(int argc, char *argv[])
{
	unsigned int lsflag = 0;
	char dirname[MAXDIRCOUNT][MAXDIRNAME] = {0};
	char path[SIZE] = {0};
	int i, j;

	if(argc < 1)
		err_quit("usage : ls [-ali] directory_name");

	i = 1;
	while(argv[i])
	{
		if(argv[i][0] == '-')
		{
			for(j=1; j<strlen(argv[i]); j++)
			{
				switch(argv[i][j])
				{
					case 'a':
						if((lsflag & 0x1) == 0)
							lsflag |= 0x1;
						break;
					case 'i':
						if((lsflag & 0x2) == 0)
							lsflag |= 0x2;
						break;
					case 'l':
						if((lsflag & 0x4) == 0)
							lsflag |= 0x4;
						break;
				}
			}
		}
		
		i++;
	}

	i = 1;
	j = 0;
	while(argv[i])
	{
		if(argv[i][0] == '-')
		{
			i++;
			continue;
		}
		else
		{
			strcpy(dirname[j], argv[i]);
			i++; j++;
		}
	}

	i = 0;
	if(strlen(dirname[i]) == 0)
		strcpy(dirname[i], ".");
	
	while(strlen(dirname[i]))
	{
		chdir(dirname[i]);
		getcwd(path, SIZE);
		printf("Current Path : %s\n", path);
		chdir(".");

		dirprint(lsflag, dirname[i]);
		i++;
	
		if(strlen(dirname[i]))
				putchar('\n');
				
		if((lsflag == 0 || (lsflag & 0x1) != 0 || (lsflag & 0x2) != 0) && (lsflag & 0x4) == 0)
			putchar('\n');
	}

	exit(0);
}


