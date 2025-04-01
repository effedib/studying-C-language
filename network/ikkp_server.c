#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int listener_d = 0;

void handle_shutdown(int sig)
{
    if (listener_d)
        close(listener_d);
    fprintf(stderr, "Bye!\n");
    exit(0);
}

int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int read_data(int socket, char *buf, int len)
{
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    while ((c > 0) && (s[c - 1] != '\n'))
    {
        s += c;
        slen -= c;
        c = recv(socket, s, slen, 0);
    }

    if (c < 0)
        return c;
    else if (c == 0)
        buf[0] = '\0';
    else
        buf[c - 1] = '\0';

    return len - slen;
}

int open_listener_socket()
{
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Can't open a socket");

    return s;
}

void bind_to_port(int socket, int port)
{
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)))
        error("Can't set the reuse option to the socket!");

    if (bind(socket, (struct sockaddr *)&name, sizeof(name)) == -1)
        error("Can't bind the port");
}

int say(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "%s: %s", "Error talking to the client", strerror(errno));

    return result;
}

int run_server(int depth, int port)
{
    listener_d = open_listener_socket();
    bind_to_port(listener_d, port);

    if (listen(listener_d, depth) == -1)
        error("Can't listen");

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);

    puts("Waiting for connection");

    char buffer[255];

    while (1)
    {
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1)
            error("Can't open secondary socket");
        int s1 = say(connect_d, "Knock! Knock!\n");
        if (s1 < 0)
        {
            close(connect_d);
            continue;
        }
        int r1 = read_data(connect_d, buffer, sizeof(buffer));
        if (strcasecmp(buffer, "who's there?\r") != 0)
        {
            puts("Wrong answer!!");
            close(connect_d);
            continue;
        }
        int s2 = say(connect_d, "Oscar\n");
        if (s2 < 0)
        {
            close(connect_d);
            continue;
        }
        int r2 = read_data(connect_d, buffer, sizeof(buffer));
        if (strcasecmp(buffer, "oscar who?\r") != 0)
        {
            puts("Wrong answer!!");
            close(connect_d);
            continue;
        }
        int s3 = say(connect_d, "Oscar silly question, you get a silly answer\n");

        close(connect_d);
    }

    return 0;
}

int main()
{
    if (catch_signal(SIGINT, handle_shutdown) == -1)
        error("Can't set up the error handler\n");
    run_server(10, 30000);

    return 0;
}