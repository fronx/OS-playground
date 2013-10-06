#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main () {
	char addr_buffer[INET_ADDRSTRLEN];
	for ( struct hostent *host_entry = gethostent();
              host_entry != NULL;
              host_entry = gethostent()
            ) {
		printf("%s\n", host_entry->h_name);
                for ( char **addr = host_entry->h_addr_list;
                      *addr != NULL;
                      addr++
		) {
			printf("    %s\n", inet_ntop(AF_INET, *addr, addr_buffer, INET_ADDRSTRLEN));
		}
                      
	}
	endhostent();
	return 0;
}
