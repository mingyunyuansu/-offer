#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Replace all spaces with "%20"

char src[] = "We are not happy.";

void brute_force (char *s) {
    int i, l;
    i = l = strlen(src);
    //printf ("%d\n", s[l]);
    while (i >= 0) {
        if (s[i] == ' ') {
            // Moving
            int j  = l;
            while (j != i) {
                s[j + 2] = s[j];
                j --;
            }
            s[j++] = '%';
            s[j++] = '2';
            s[j] = '0';
            // Length changed
            l += 2;
        }
        i--;
    }
}

void advanced (char *s) {
    // Count spaces, and move in once
    int count = 0;
    int i, l;
    i = l = strlen (s);
    for (int j = 0; j < l; j++) {
        if (s[j] == ' ') count ++;
    }
    //Treat the position l as a pointer
    //If a ' ', generate "%20", otherwise copy and go on
    l = l + count * 2;
    while (i >= 0 && l >= 0) {
        if (s[i] == ' ') {
            s[l--] = '0';
            s[l--] = '2';
            s[l--] = '%';
            i--;
        }
        else {
            s[l--] = s[i--];
        }
    }
}

int main () {
    char *s = (char *)malloc(50 * sizeof(char));
    strcpy (s, src);
    printf ("%d\n", strlen(s));
    printf ("%s\n", s);
    //brute_force (s);
    advanced(s);
    printf ("%d\n", strlen(s));
    printf ("%s\n", s);
    free(s);
    return 0;
}