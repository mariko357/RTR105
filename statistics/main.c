#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_SYMBOLS 127 - 32

int main(int argc, char *argv[])
{

    char *line = NULL; /* forces getline to allocate with malloc */
    size_t len = 0;    /* ignored when line = NULL */
    unsigned int count;

    printf("Please enter your string:\n");

    count = getline(&line, &len, stdin);

    unsigned char min = 255;
    for (unsigned long i = 0; i < count; i++)
    {
        if (line[i] < min && line[i] > 32)
        { // Without special symbols
            min = line[i];
        }
    }
    printf("The smallest value (according to ASCII table): %c (%d)\n", min, min);

    unsigned char max = 0;
    for (unsigned long i = 0; i < count; i++)
    {
        if (line[i] > max && line[i] > 32)
        { // Without special characters
            max = line[i];
        }
    }
    printf("The biggest value (according to ASCII table): %c (%d)\n", max, max);

    unsigned long sum = 0;
    for (unsigned long i = 0; i < count - 1; i++)
    {
        sum += line[i];
    }
    printf("The average value is: %c (%d)\n", sum / (count - 1), sum / (count - 1));

    // sorting the array
    char *copy = malloc(count);
    memcpy(copy, line, count);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1; j++)
        {
            if (copy[j] > copy[j + 1])
            {
                char tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
            }
        }
    }

    printf("Sorted string: ");
    for (unsigned int i = 0; i < count - 1; i++)
    {
        printf("%c, ", copy[i]);
    }
    printf("\n");

    printf("Sorted string (ASCII integer values): ");
    for (unsigned int i = 0; i < count; i++)
    {
        printf("%d, ", copy[i]);
    }
    printf("\n");

    printf("Median value: %c, (%d)\n", copy[count / 2], copy[count / 2]);

    int symbolCount[NUMBER_OF_SYMBOLS];
    for (int i = 0; i < NUMBER_OF_SYMBOLS; i++)
    {
        symbolCount[i] = 0;
    }
    for (int i = 0; i < NUMBER_OF_SYMBOLS; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (line[j] == i + 32)
            {
                symbolCount[i]++;
            }
        }
    }

    printf("Occurances of symbols: \n");
    for (int i = 0; i < NUMBER_OF_SYMBOLS; i++)
    {
        printf("%c: %ld \n", i + 32, symbolCount[i]);
    }

    FILE *pFile;
    pFile = fopen("statistics.dat", "w");

    // print only letters into the file:
    for (int i = 65; i < 123; i++)
    {
        if (i < 91 || i > 96)
        {
            fprintf(pFile, "\"%c\"    %ld \n", i, symbolCount[i - 32]);
        }
    }

    fclose(pFile);

    free(line); /* free memory allocated by getline */

    return 0;
}