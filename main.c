// CRC implementation in C
// complete implementation pending

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inp_head_index;

void printArr(int *arr, int size){
    for(int i = 0; i< size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int firstOne(int* xorArr, int keySize){
    for(int i = 0; i < keySize; i++){
        if(xorArr[i] == 1)
            return i;
        else continue;
    }
    return -1;
}

void shift(int* xorArr, int keySize){
    for(int i = 0; i< keySize-1; i++)
            xorArr[i] = xorArr[i+1];
}

void XOR(char* func, int* key, int* input, int* xorArr, int keySize, int frameSize){
    while (inp_head_index<frameSize+1){
        // xor operation
        for(int i = 0; i < keySize; i++){
            xorArr[i] = xorArr[i] ^ key[i];
        }
        // finding first one
        int firstOneIndex;
        firstOneIndex = firstOne(xorArr, keySize);
        if (firstOneIndex == -1){
            if (stricmp(func, "decode") == 0){
                printf("\nNo zeros found\n");
                inp_head_index++;
            }
            else if(stricmp(func, "encode") == 0)
                xorArr[0] = input[inp_head_index++];
        }
        // left shift
        for(int i = 0; i < firstOneIndex; i++){
            shift(xorArr, keySize);
            // appending input bit to the temp array
            xorArr[keySize-1] = input[inp_head_index++];
        }
    }
}

int* crc(int* key, int* input, int* xorArr, int keySize, int frameSize){
    inp_head_index = keySize;
    XOR("encode", key, input, xorArr, keySize, frameSize);

    printf("The remainder that needs to be appended: ");
    printArr(xorArr, keySize-1);

    // appending the xorArr to the input
    int j = 0;
    for(int i = frameSize - keySize + 1; i <= frameSize; i++, j++){
        input[i] = xorArr[j];
    }
    printf("Frame that will get transferred: ");
    printArr(input, frameSize);
    return input;
}

void checkIntegrity(int *dataArr, int *crckey, int frameSize, int keySize){
    inp_head_index = keySize;
    int tempArr[keySize];
    printf("\nFrame recieved: ");
    printArr(dataArr, frameSize);
    for(int i = 0; i < keySize; i++){
        tempArr[i] = dataArr[i];
    }
    XOR("decode", crckey, dataArr, tempArr, keySize, frameSize);

    for(int i = 0; i < keySize; i++){
        if(tempArr[i] == 0)
            continue;
        else{
            printf("Rejected\n");
            return;
        }
    }
    printf("Data Integrity check successful\n");
}

int main() {
    // taking the input code by https://github.com/apoorvapendse
    int inputSize;
    int crcSize;
    int frameSize;
//    printf("Enter the size of the inputSize\n");
//    scanf("%d",&inputSize);
//
//    //creating input array
//
//    printf("Enter the size of the CRC key\n");
//    scanf("%d",&crcSize);
//
//    frameSize = crcSize + inputSize;
//    int* crckey = (int*)malloc(sizeof(int) * crcSize);
//    int *inputArr = (int*)malloc(sizeof(int) * (inputSize+crcSize-1));
//    int* xorArray = (int*)malloc(sizeof(int)*crcSize);

    // test case
int inputArr[11] = {1,0,0,0,0,1,1,0,0,0,0};
int crckey[5] = {1, 1, 0, 0, 1};
int xorArray[5] = {1,0,0,0,0};
crcSize = 5;
frameSize = 11;
    int sampledataarr[11] = {1 ,1, 0, 0, 0, 1, 1, 1, 1, 0, 1};



//    //taking input array;
//    for(int i = 0 ; i < inputSize;i++){
//        printf("Enter the value of element at index %d for input array\n",i);
//        scanf("%d",&inputArr[i]);
//    }
//    //inputting crckey
//    printf("\n");
//    for(int i = 0 ; i < crcSize;i++){
//        printf("Enter the value of element at index %d for crc key\n",i);
//        scanf("%d",&crckey[i]);
//
//    }
//
//    //appending zeros to the input array
//    printf("frameSize:%d\n",frameSize);
//    for(int i = inputSize ; i < frameSize-1; i++){
//        printf("i value is:%d\n",i);
//        inputArr[i] = 0 ;//appending n-1 zeros;
//    }
//    //copying contents of first n bits into xorArray, where n is the crckey size
//    for(int i = 0 ; i < crcSize;i++){
//        xorArray[i] = inputArr[i];
//    }


    int* dataArr = crc(crckey, inputArr, xorArray, crcSize, frameSize);

    checkIntegrity(dataArr, crckey, frameSize, crcSize);

    return 0;
}
