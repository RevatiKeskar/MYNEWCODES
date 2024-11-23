#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h> #include
<sys/stat.h>
#include <unistd.h>
int main() {
char s1[300], s2[300]; // Buffers to store input and output strings
int num, fd1, fd2, byt; // Variables for file descriptors and byte count
// Create two named pipes (FIFOs) with read/write permissions mknod("pipe1", S_IFIFO |
0666, 0);
mknod("pipe2", S_IFIFO | 0666, 0);
// Wait for the other process to connect to the second end of the FIFO pipe
printf("fifo 1st side connected, waiting for other process to connect to the 2nd end of fifo
pipe...\n");
// Open pipe1 for writing and pipe2 for reading fd1 = open("pipe1", O_WRONLY);
fd2 = open("pipe2", O_RDONLY);
// Inform that connection is established and prompt for user input printf("established
connection--type some stuff\n");
gets(s1); // Get user input and store it in s1 (Note: 'gets' is unsafe, consider using 'fgets'
instead)
// Write the input data to pipe1
if ((num = write(fd1, s1, strlen(s1))) == -1)
perror("write"); // Print error message if write fails else {
// Print the number of bytes written to pipe1 printf("wrote %d bytes to file1\n", num);
// Read data from pipe2 into s2 and store the number of bytes read byt = read(fd2, s2, 300);
s2[byt] = '\0'; // Null-terminate the received string
// Print the received message from pipe2 printf(" %s\n", s2);
}
return 0; // Exit the program
}
Program 2:
#include <stdio.h>
#include <stdlib.h> #include <errno.h> #include <string.h> #include <fcntl.h> #include
<sys/types.h> #include <sys/stat.h> #include <unistd.h>
int main() {
char s[300], send[300]; // Buffers to store received data and the message to be sent int num,
fd1, fd2, sig, k = 0, i; // Variables for file descriptors and counts
int wordcnt = 1, charcnt = 0, linecnt = 0, vowelCnt = 0; // Counters for words, characters,
lines, and vowels
// Create two named pipes (FIFOs) with read/write permissions mknod("pipe1", S_IFIFO |
0666, 0);
mknod("pipe2", S_IFIFO | 0666, 0);
// Wait for the other process to connect to the first end of the FIFO pipe
printf("fifo 2nd side connected, waiting for other process to connect to the 1st end of fifo
pipe...\n");
// Open pipe1 for reading and pipe2 for writing fd1 = open("pipe1", O_RDONLY);
fd2 = open("pipe2", O_WRONLY); printf("established connection\n");
// Read data from pipe1 into the buffer 's' if ((num = read(fd1, s, 300)) == -1)
perror("read"); // Print error message if reading fails else {
s[num] = '\0'; // Null-terminate the received string printf("read %d bytes: \"%s\"\n", num, s);
// Initialize counters for word, vowel, character, and line counts wordcnt = 1;
vowelCnt = 0;
// Loop through the received string to calculate counts for (i = 0; i < num; i++) {
// Count vowels (both uppercase and lowercase)
if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') { vowelCnt++;
}
// Count words based on spaces or periods followed by non-space characters if ((s[i] == ' '
&& s[i+1] != ' ') || (s[i] == '.' && s[i+1] != '\0')) {
wordcnt++;
}
// Count lines based on periods or the end of the input if (s[i] == '.' || (s[i] != '.' && s[i+1] ==
'\0')) {
linecnt++;
}
// Count non-space, non-period characters else if (s[i] != '.' && s[i] != ' ') {
charcnt++;
}
}
// Create a message summarizing the counts
sprintf(send, "For the given sentence:\nWord count: %d\nVowel count: %d\nCharacter count:
%d\nLine count: %d\n",
wordcnt, vowelCnt, charcnt, linecnt);
// Write the summarized message to pipe2 if ((sig = write(fd2, send, strlen(send))) != -1)
printf("\nWritten successfully to file 2"); else
printf("\nError in writing to file 2");
}
return 0; // Exit the program
}
