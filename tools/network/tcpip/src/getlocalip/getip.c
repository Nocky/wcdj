#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>	// inet_ntop
#include <netdb.h>
#include <string.h>		// bzero
#include <errno.h>


void GetSelfServerIP(char *pszIP)
{
	struct addrinfo *answer, hint, *curr;
	//char szIP[16];
	bzero(&hint, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;

	int iRet = 0;
	char szHostName[128] = {0};
	iRet = gethostname(szHostName, sizeof(szHostName));
	if (iRet != 0)
	{
		fprintf(stderr, "gethostname error! [%s]\n", strerror(errno));
		exit(1);
	}
	printf("hostname [%s]\n", szHostName);

	iRet = getaddrinfo(szHostName, NULL, &hint, &answer);
	if (iRet != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(iRet));
		exit(1);
	}

	for (curr = answer; curr != NULL; curr = curr->ai_next)
	{
		inet_ntop(AF_INET, &(((struct sockaddr_in *)(curr->ai_addr))->sin_addr), pszIP, 16);
		//printf("%s\n", pszIP);
	}

	freeaddrinfo(answer);
}

int main(int argc, char **argv)
{ 
	char szIP[16] = {0};
	GetSelfServerIP(szIP);
	printf("IP [%s]\n", szIP);

	return 0;
}


