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
    CalcFramer myframer;
    CalcParser myparser;
    size_t rb_size = 500;
    char rece_buffer[rb_size];
    ssize_t rece_bytes = recv(clntSocket, rece_buffer, rb_size, 0);
    if(rece_bytes < 0){
        DieWithError("receive failed");
    }
    int accum = 0;
    //size_t sb_size;
    //char send_buffer[sb_size];
    while(rece_bytes > 0){
        myframer.append(rece_buffer);
        while(myframer.hasMessage()){
            CalcInstruction ret = myparser.parse(myframer.topMessage());
            myframer.popMessage();
            if(ret.end){
                //strcpy(send_buffer, to_string(accum).c_str());
                string send_buffer = to_string(accum)+"\r\n";
                accum = 0;
                ssize_t sent_bytes = send(clntSocket, send_buffer.c_str(), send_buffer.length(), 0);
                if(sent_bytes < 0){
                    DieWithError("send() failed");
                } else if(sent_bytes < send_buffer.length()){
                    DieWithError("send unexpected number of bytes");
                }
            } else {
                switch (ret.op){
                    case 0:
                        accum=ret.num;
                        break;
                    case 1:
                        accum+=ret.num;
                        break;
                    case 2:
                        accum-=ret.num;
                        break;
                }
            }
        }
        rece_bytes = recv(clntSocket, rece_buffer, rb_size, 0);
        if(rece_bytes < 0){
            DieWithError("recv() failed");
        }
    }
    
    close(clntSocket);    /* Close client socket */
}
