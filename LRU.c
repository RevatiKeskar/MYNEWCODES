#include <stdio.h>

// Function to check if a page is present in the frame
int checkHit(int page, int pageframe[], int filled) {
  for (int i = 0; i < filled; i++) {
    if (pageframe[i] == page) {
      return 1; // Page found
    }
  }
  return 0; // Page not found
}

// Function to print the page frame status
void printFrame(int pageframe[], int size, int page) {
  printf("%d : ", page);
  for (int i = 0; i < size; i++) {
    printf("      %d    ", pageframe[i]);
  }
}

// Main function
int main() {
  int pages[] = {3, 0, 1, 1, 0, 2, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  int n = sizeof(pages) / sizeof(pages[0]); // Number of pages
  int pageframe[3];                         // Page frame size of 3
  int filled = 0;                           // Tracks filled slots in page frame
  int pagefault = 0;                        // Count of page faults

  printf("Page  Pageframe1 Pageframe2 Pageframe3 \n");

  for (int i = 0; i < n; i++) {
    int page = pages[i];

    // Check if the page is already in the frame
    if (checkHit(page, pageframe, filled)) {
      printFrame(pageframe, filled, page); // No page fault
    }
    // If the page is not in the frame and there is space
    else if (filled < 3) {
      pagefault++;
      pageframe[filled] = page;
      filled++;
      printFrame(pageframe, filled, page); // Add page to frame
    }
    // If the frame is full, replace the least recently used page
    else {
      int maxi = 0, index;
      int distance[3] = {0};

      // Calculate the distance since each page in the frame was last used
      for (int j = 0; j < filled; j++) {
        for (int k = i - 1; k >= 0; k--) {
          distance[j]++;
          if (pageframe[j] == pages[k]) {
            break;
          }
        }
        // Find the page with the maximum distance (least recently used)
        if (maxi < distance[j]) {
          maxi = distance[j];
          index = j;
        }
      }

      pagefault++;
      pageframe[index] = page; // Replace LRU page
      printFrame(pageframe, filled, page);
    }
    printf("\n");
  }

  // Calculate and display hit and page fault ratios
  int hits = n - pagefault;
  printf("\nHits ratio : %.2f", (float)hits / n);
  printf("\nPage fault ratio : %.2f", (float)pagefault / n);

  return 0;
}
