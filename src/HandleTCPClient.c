#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <iostream>
#include <assert.h>
#include "CalcServer.h"
#include "CalcFramer.hpp"
#include "CalcParser.hpp"

using namespace std;

void HandleTCPClient(int clntSocket)
{
	// PUT YOUR CODE HERE

    close(clntSocket);    /* Close client socket */
}
