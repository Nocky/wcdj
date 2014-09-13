#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>


bool GetLocalIP(char * pszIPBuf)
{
	#define MAXINTERFACES 16 

	bool result = false;

	int fd = -1;
	int intrface = 0; 
	struct ifreq buf[MAXINTERFACES]; 
	struct ifconf ifc; 

	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) 
	{ 
		ifc.ifc_len = sizeof buf; 
		ifc.ifc_buf = (caddr_t) buf; 
		if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc)) 
		{ 
			//��ȡ�ӿ���Ϣ
			intrface = ifc.ifc_len / sizeof (struct ifreq); 
			//���ݽ����Ϣѭ����ȡ�豸IP��MAC��ַ
			while (intrface-- > 0) 
			{     
				//��ȡ�豸����
				//printf ("net device %s\n", buf[intrface].ifr_name); 

				if ( strstr(buf[intrface].ifr_name,"eth") != NULL )
				{
					//��ȡ��ǰ������IP��ַ 
					if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface]))) 
					{ 
						if ( inet_ntop(AF_INET,
									&(( (struct sockaddr_in*)(& (buf[intrface].ifr_addr) ))->sin_addr),
									pszIPBuf,16) )
						{
							return true;
						}
					}
				}
			}
		}

		close (fd); 
	}

	return result;
}


int main()
{
	char pszIPBuf[20] = {0};
	GetLocalIP(pszIPBuf);
	if (pszIPBuf[0] != '\0')
		printf("local IP [%s]\n", pszIPBuf);
	else
		printf("Get local IP error!\n");

	return 0;
}

