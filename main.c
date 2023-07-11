// CRC implementation in C
// currently prints the bits that needed to be appended after the data
// complete implementation pending

#include <stdio.h>

int input[11] = {1,1,0,0,0,1,1,0,0,0,0};
int inp_len = 11;
int key[5] = {1, 1, 0, 0, 1};

// initially temp has same content as input
int temp[5] = {1,1,0,0,0};

const int key_len = 5;
int inp_head_index = key_len;

void printArr(int *arr, int size){
    for(int i = 0; i< size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void shift(){
    do{
        for(int i = 0; i< key_len-1; i++){
            temp[i] = temp[i+1];
        }
        temp[key_len-1] = input[inp_head_index];
        inp_head_index++;
    }while(temp[0] == 0);
}

void XOR(){
//    int temp_g = temp;

    for(int i = 0; i < key_len; i++){
        temp[i] = temp[i] ^ key[i];
    }
    shift();
}

void crc(){
    while(inp_head_index != inp_len+1){
        XOR();
    }
    printf("The remainder that needs to be appended: ");
    printArr(temp, key_len-1);
}

int main() {
    crc();
    return 0;
}
