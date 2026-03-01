#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int lru(int pages[], int n, int frames) {
    int frame[frames], recent[frames];
    int faults = 0, count = 0;

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                recent[j] = ++count;
                break;
            }
        }

        if(!found) {
            int min = INT_MAX, pos = 0;

            for(int j = 0; j < frames; j++) {
                if(frame[j] == -1) {
                    pos = j;
                    break;
                }
                if(recent[j] < min) {
                    min = recent[j];
                    pos = j;
                }
            }

            frame[pos] = pages[i];
            recent[pos] = ++count;
            faults++;
        }
    }

    return faults;
}

int optimal(int pages[], int n, int frames) {
    int frame[frames];
    int faults = 0;

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            int pos = -1, farthest = i;

            for(int j = 0; j < frames; j++) {
                int k;
                for(k = i + 1; k < n; k++) {
                    if(frame[j] == pages[k])
                        break;
                }

                if(k == n) {
                    pos = j;
                    break;
                }

                if(k > farthest) {
                    farthest = k;
                    pos = j;
                }
            }

            if(pos == -1)
                pos = 0;

            frame[pos] = pages[i];
            faults++;
        }
    }

    return faults;
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Usage: %s <length> <frames>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int frames = atoi(argv[2]);

    if(frames < 1 || frames > 7) {
        printf("Frames must be between 1 and 7\n");
        return 1;
    }

    int pages[n];

    srand(time(0));

    printf("Reference String: ");
    for(int i = 0; i < n; i++) {
        pages[i] = rand() % 10;
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("LRU Page Faults: %d\n", lru(pages, n, frames));
    printf("Optimal Page Faults: %d\n", optimal(pages, n, frames));

    return 0;
}

// gcc LRU_opt.c -o lru
//THIS IS HOW I COMPILE IT IN VS CODE
//./lru 20 3
//AND THE ABOVE ONE IS HOW I RAN IT IN VS CODE
