#include <stdio.h>
#include <Windows.h>

DWORD WINAPI worker(LPVOID args){

    int id =*(int *)args;

    printf("sub thread created %d.\n",id);

    return 0;
};


int main(void){

    int args =1;

    HANDLE all_threads =CreateThread(NULL ,0 ,worker ,&args ,0,NULL);

    if (all_threads ==NULL)
    {
        fprintf(stderr ,"failed to create thread.\n");
    }
    

    printf("main thread created.\n");


    WaitForSingleObject(all_threads, INFINITE);
    CloseHandle(all_threads);


    return 0;
}