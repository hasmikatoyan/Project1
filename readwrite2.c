#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define SIZE 256

#define SHM_P1 "/p1_to_p2"
#define SHM_P2 "/p2_to_p1"

#define SEM_P1_WRITE "/sem_p1_write"
#define SEM_P1_READ  "/sem_p1_read"
#define SEM_P2_WRITE "/sem_p2_write"
#define SEM_P2_READ  "/sem_p2_read"

int main() {
    printf("Process 2 started.\n");

    int shm_recv = shm_open(SHM_P1, O_CREAT | O_RDWR, 0666);
    int shm_send = shm_open(SHM_P2, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_send, SIZE);
    ftruncate(shm_recv, SIZE);

    char *recv_buf = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_recv, 0);
    char *send_buf = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_send, 0);

    sem_t *sw = sem_open(SEM_P2_WRITE, O_CREAT, 0666, 1);
    sem_t *sr = sem_open(SEM_P2_READ,  O_CREAT, 0666, 0);

    sem_t *rw = sem_open(SEM_P1_WRITE, O_CREAT, 0666, 0);
    sem_t *rr = sem_open(SEM_P1_READ,  O_CREAT, 0666, 1);

    while (1) {
        char msg[SIZE];

        // RECEIVE from process1
        sem_wait(rr);
        printf("Process 1: %s\n", recv_buf);
        sem_post(rw);

        // SEND to process1
        printf("Enter message: ");
        fgets(msg, SIZE, stdin);

        sem_wait(sw);
        strcpy(send_buf, msg);
        sem_post(sr);
    }

    return 0;
}
