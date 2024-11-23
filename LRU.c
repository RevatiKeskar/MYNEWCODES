          #include <stdio.h>
          #include <stdlib.h>

          // Function to check if a page is already present in frames
          int checkHit(int page, int frames[], int frame_count) {
              for (int i = 0; i < frame_count; i++) {
                  if (frames[i] == page) {
                      return 1; // Page found in frames
                  }
              }
              return 0; // Page not found
          }

          // Function to print the current state of frames
          void printFrame(int page, int frames[], int frame_count) {
              printf("PAGE\t");
              for (int i = 0; i < frame_count; i++) {
                  printf("F%d\t", i + 1);
              }
              printf("\n");

              printf("%d\t", page);
              for (int i = 0; i < frame_count; i++) {
                  if (frames[i] == -1) {
                      printf("-\t"); // Print '-' for empty frames
                  } else {
                      printf("%d\t", frames[i]);
                  }
              }
              printf("\n");
          }

          // Function to implement the LRU page replacement algorithm
          void LRU(int page[], int frames[], int page_count, int frame_count) {
              int faults = 0, hits = 0, filled = 0;

              // Initialize frames to -1
              for (int i = 0; i < frame_count; i++) {
                  frames[i] = -1;
              }

              for (int i = 0; i < page_count; i++) {
                  // Check if the page is already in the frames
                  if (checkHit(page[i], frames, frame_count)) {
                      hits++; // Page hit
                  } else {
                      if (filled < frame_count) {
                          // There is still space in the frames
                          frames[filled++] = page[i];
                      } else {
                          // Find the least recently used page
                          int max_dist = -1, index = -1;
                          for (int j = 0; j < frame_count; j++) {
                              int dist = 0;
                              for (int k = i - 1; k >= 0; k--) {
                                  dist++;
                                  if (frames[j] == page[k]) {
                                      break;
                                  }
                              }
                              if (dist > max_dist) {
                                  max_dist = dist;
                                  index = j;
                              }
                          }
                          frames[index] = page[i]; // Replace the least recently used page
                      }
                      faults++; // Page fault
                  }
                  printFrame(page[i], frames, frame_count);
              }

              // Print the total number of hits and faults
              printf("Total hits: %d\n", hits);
              printf("Total faults: %d\n", faults);
          }

          int main() {
              int page_count, frame_count;

              printf("Enter the number of pages: ");
              scanf("%d", &page_count);

              printf("Enter the number of frames: ");
              scanf("%d", &frame_count);

              int page[page_count];
              int frames[frame_count];

              printf("Enter the page sequence: ");
              for (int i = 0; i < page_count; i++) {
                  scanf("%d", &page[i]);
              }

              LRU(page, frames, page_count, frame_count);

              return 0;
          }
