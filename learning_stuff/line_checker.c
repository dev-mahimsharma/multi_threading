#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME 100
#define TOTAL_JOBS 10

typedef struct {
    char file_name[FILE_NAME];
    int id;
} job_t;

CRITICAL_SECTION line_count_secure;

int total_line_count = 0;

DWORD WINAPI worker(LPVOID args) {
    job_t job = *(job_t *)args;

    printf("working on job id %d with file %s.\n", job.id, job.file_name);

    FILE *open_file = fopen(job.file_name, "r");

    if (open_file == NULL) {
        fprintf(stderr, "failed to open file: %s\n", job.file_name);
        return 1;
    }

    int ch;
    int local_lines = 0;
    int has_any_char = 0;
    int last_char_was_newline = 1;

    while ((ch = fgetc(open_file)) != EOF) {
        has_any_char = 1;

        if (ch == '\n') {
            local_lines++;
            last_char_was_newline = 1;
        } else {
            last_char_was_newline = 0;
        }
    }

    if (has_any_char && !last_char_was_newline) {
        local_lines++;
    }

    fclose(open_file);

    EnterCriticalSection(&line_count_secure);
    total_line_count += local_lines;
    LeaveCriticalSection(&line_count_secure);

    printf("total lines in file %s with id %d is %d.\n",
           job.file_name,
           job.id,
           local_lines);

    return 0;
}

int main(void) {
    InitializeCriticalSection(&line_count_secure);

    job_t jobs_array[TOTAL_JOBS];
    HANDLE threads[TOTAL_JOBS];

    int job_count = 0;

    while (job_count < TOTAL_JOBS) {
        char file_name[FILE_NAME];

        printf("enter file name... (type exit to quit)\n");

        if (fgets(file_name, sizeof(file_name), stdin) == NULL) {
            fprintf(stderr, "something went wrong.\n");
            break;
        }

        file_name[strcspn(file_name, "\n")] = '\0';

        if (strcmp(file_name, "exit") == 0) {
            break;
        }

        strncpy(jobs_array[job_count].file_name, file_name, FILE_NAME - 1);
        jobs_array[job_count].file_name[FILE_NAME - 1] = '\0';
        jobs_array[job_count].id = job_count + 1;

        threads[job_count] = CreateThread(
            NULL,
            0,
            worker,
            &jobs_array[job_count],
            0,
            NULL
        );

        if (threads[job_count] == NULL) {
            fprintf(stderr, "failed to create worker thread. Error: %lu\n", GetLastError());
            DeleteCriticalSection(&line_count_secure);
            return 1;
        }

        printf("created thread for job %d.\n", job_count + 1);

        job_count++;
    }

    if (job_count > 0) {
        WaitForMultipleObjects(job_count, threads, TRUE, INFINITE);
    }

    for (int i = 0; i < job_count; i++) {
        CloseHandle(threads[i]);
    }

    printf("total lines in all files = %d\n", total_line_count);

    DeleteCriticalSection(&line_count_secure);

    return 0;
}