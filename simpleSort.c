#include "stdio.h"

struct Number
{
    unsigned char number;
    char shift;
};


int main(){
    printf("Please enter 3 characters\n");
    struct Number numbers[3];

    unsigned char mode;


    scanf("%c %c %c", &numbers[0].number, &numbers[1].number, &numbers[2].number);
    printf("Please enter the order you want the numbers to be sorted (0 = ascending, 1 = descending)\n");
    scanf("%hhu", &mode);

    for(unsigned char i = 0; i < 3; i++){
        if(numbers[i].number >= 97){
            numbers[i].number -= 32;
            numbers[i].shift = 32;
        }
        else{
            numbers[i].shift = 0;
        }
    }

    //simple bubble sort

    for(char i = 0; i < 3; i++){
        for(char j = 0; j < 2; j++){
            if(numbers[j].number < numbers[j+1].number){
                struct Number temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    if(!mode){
        printf("%c %c %c \n", numbers[2].number + numbers[2].shift, numbers[1].number + numbers[1].shift, numbers[0].number + numbers[0].shift);

    }
    else{
        printf("%c %c %c \n", numbers[0].number + numbers[0].shift, numbers[1].number + numbers[1].shift, numbers[2].number + numbers[2].shift);
    }

    return 0;
}