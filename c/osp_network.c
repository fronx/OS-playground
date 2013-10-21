#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/queue.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct frx_hostent_addr {
	TAILQ_ENTRY(frx_hostent_addr) addr_entry;
	char addr[0];
};

struct frx_hostent {
	char *h_name;
	TAILQ_HEAD(frx_hostent_addrs, frx_hostent_addr) addrs;
};

int
frx_hostent_init(struct frx_hostent *self)
{
	char addr_buffer[INET_ADDRSTRLEN];
	struct frx_hostent_addr *addr_elem;

	TAILQ_INIT(&self->addrs);

	for (
		struct hostent *host_entry = gethostent();
		host_entry != NULL;
		host_entry = gethostent()
	) {
		self->h_name = strdup(host_entry->h_name);

		for (
			char **addr = host_entry->h_addr_list;
			*addr != NULL;
			addr++
		) {
			if (!inet_ntop(AF_INET, *addr, addr_buffer, INET_ADDRSTRLEN)) {
				perror("inet_ntop() failed");
				return -1;
				/* something terrible is afoot! */
			}

			addr_elem = calloc(1, sizeof(*addr_elem) + strlen(addr_buffer));
			if (!addr_elem) {
				fprintf(stderr, "calloc() failed, out of memory?\n");
				return -1;
			}

			strcat(addr_elem->addr, addr_buffer);
			TAILQ_INSERT_HEAD(&self->addrs, addr_elem, addr_entry);
		}
	}

	endhostent();
	return 0;
}

void
frx_hostent_fini(struct frx_hostent *self)
{
	struct frx_hostent_addr *addr;

	if(self->h_name)
		free(self->h_name);

	while ((addr = TAILQ_FIRST(&self->addrs))) {
		TAILQ_REMOVE(&self->addrs, addr, addr_entry);
		free(addr);
	}
}

void
frx_hostent_print(struct frx_hostent *self)
{
	struct frx_hostent_addr *addr;
	printf("%s\n", self->h_name);

	TAILQ_FOREACH(addr, &self->addrs, addr_entry)
		printf("    %s\n", addr->addr);
}

int main () {
	struct frx_hostent yes;
	frx_hostent_init(&yes);
	frx_hostent_print(&yes);
	frx_hostent_fini(&yes);
	return 0;
}