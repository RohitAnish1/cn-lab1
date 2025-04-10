#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

#define TOTAL_PACKETS 5
#define TIMEOUT 3

int simulate_acknowledgment(){
    return rand()%10<7;
}

int main(){
    srand(time(0));
    int packet = 1;
    int ack_recieved;
    while(packet <= TOTAL_PACKETS){
        printf("Sender:Sending packet%d\n",packet);
        ack_recieved = simulate_acknowledgment();
        if(ack_recieved){
            printf("ACK for packet%d recieved\n",packet);
            packet++;
        }
        else{
            printf("ACK for packet%d lost!\n",packet);
            sleep(TIMEOUT);
        }
    }
    printf("All packets sent successfully!\n");
    return 0;
}