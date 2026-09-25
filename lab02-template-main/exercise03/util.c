// ensf 461 lab 02 - exercise 03
// oscar (30242380), somrit (30230926)
#include "util.h"

int* read_next_line(FILE* fin) {
    // TODO: This function reads the next line from the input file
    // The line is a comma-separated list of integers
    // Return the list of integers as an array where the first element
    // is the number of integers in the rest of the array
    // Return NULL if there are no more lines to read

    char* buf = NULL;
    size_t cap = 0;
    ssize_t len;

    // skip blank lines so a trailing newline does not produce an empty record
    do {
        len = getline(&buf, &cap, fin);
        if ( len == -1 ) {
            free(buf);
            return NULL;
        }
        while ( len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r') ) {
            buf[--len] = '\0';
        }
    } while ( len == 0 );

    int count = 1;
    for ( ssize_t i = 0; i < len; i++ ) {
        if ( buf[i] == ',' ) {
            count++;
        }
    }

    int* values = (int*)malloc((count + 1) * sizeof(int));
    if ( values == NULL ) {
        fprintf(stderr, "Error: unable to allocate memory!\n\n");
        free(buf);
        exit(-3);
    }

    values[0] = count;
    char* p = buf;
    for ( int i = 1; i <= count; i++ ) {
        values[i] = (int)strtol(p, &p, 10);
        if ( *p == ',' ) {
            p++;
        }
    }

    free(buf);
    return values;
}


float compute_average(int* line) {
    // TODO: Compute the average of the integers in the vector
    // Recall that the first element of the vector is the number of integers

    int n = line[0];
    if ( n <= 0 ) {
        return 0.0f;
    }

    float sum = 0.0f;
    for ( int i = 1; i <= n; i++ ) {
        sum += line[i];
    }
    return sum / n;
}


float compute_stdev(int* line) {
    // TODO: Compute the standard deviation of the integers in the vector
    // Recall that the first element of the vector is the number of integers

    int n = line[0];
    if ( n <= 0 ) {
        return 0.0f;
    }

    // population standard deviation, matching reference_output.csv
    float avg = compute_average(line);
    float sq_sum = 0.0f;
    for ( int i = 1; i <= n; i++ ) {
        float diff = line[i] - avg;
        sq_sum += diff * diff;
    }
    return sqrtf(sq_sum / n);
}
