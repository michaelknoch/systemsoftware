#include <stdio.h>
#include <sys/sysinfo.h>
// http://man7.org/linux/man-pages/man2/getpagesize.2.html
#include <unistd.h>
#include <sys/utsname.h>
                                                 
int main(void)
{
	struct sysinfo sys;
	struct utsname uts;
	
	if (sysinfo(&sys) != 0) {
		fprintf( stderr, "Hoppla!" );
		return 1;
	}

	if (uname(&uts) != 0) {
		fprintf( stderr, "Hoppla!" );
		return 1;
	}

	//http://stackoverflow.com/questions/504810/how-do-i-find-the-current-machines-full-hostname-in-c-hostname-and-domain-infos
	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);

	printf("Hello User world:\n");

	printf("Kernel: %s %s %s\n", uts.sysname, uts.release, uts.version);
	printf("Hostname: %s\n", hostname);
	printf("Machine: %s\n", uts.machine);7

	printf("Uptime: %ld\n", sys.uptime);
	printf("Total RAM: %lu MB\n", sys.totalram / 1024 / 1024);
	printf("Free RAM: %lu MB\n", sys.freeram / 1024 / 1024);
	printf("Process Count: %hu\n", sys.procs);
	printf("Page size: %ldB\n", getpagesize());

	return 0;
}
