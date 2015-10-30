#include <stdio.h>
#include <sys/sysinfo.h>
// http://man7.org/linux/man-pages/man2/getpagesize.2.html
#include <unistd.h>

                                                            
int main(void)
{
	struct sysinfo sys;
	printf("Hello User world:\n");
	printf("Uptime: %ld\n", sys.uptime);
	printf("Total RAM: %lu MB\n", sys.totalram / 1024 / 1024);
	printf("Free RAM: %lu MB\n", sys.freeram / 1024 / 1024);
	printf("Process Count: %hu\n", sys.procs);
	printf("Page size: %ldB\n", getpagesize());

	return 0;
}