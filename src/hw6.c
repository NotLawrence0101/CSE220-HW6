/*
Name: Lawrence Wong
SBU ID: 116408194
*/

#include "hw6.h"

int main(int argc, char *argv[]) {

    // Accounts for MISSING_ARGUMENT
    if(argc<7)
        return MISSING_ARGUMENT;
    // Accounts for DUPLICATED_ARGUMENTS
    int s_count = 0, r_count = 0, l_count = 0, w_count = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-s") == 0) 
            s_count++;
        else if(strcmp(argv[i], "-r") == 0) 
            r_count++;
        else if(strcmp(argv[i], "-l") == 0) 
            l_count++;
        else if(strcmp(argv[i], "-w") == 0) 
            w_count++;
    }
    if (s_count > 1 || r_count > 1 || l_count > 1 || w_count > 1)
        return DUPLICATE_ARGUMENT;
    // Accounts for INPUT_FILE_MISSING
    char *input = argv[argc - 2];
    FILE *fp = fopen(input, "r");
    if (fp == NULL)
        return INPUT_FILE_MISSING;
    fclose(fp);
    // Accounts for OUTPUT_FILE_UNWRITABLE
    char *output = argv[argc - 1];
    fp = fopen(output, "w");    
    if (fp == NULL)
        return OUTPUT_FILE_UNWRITABLE;
    fclose(fp);
    // Accounts for S_ARGUMENT_MISSING
    if(s_count==0)
        return S_ARGUMENT_MISSING;
    // Accounts for R_ARGUMENT_MISSING
    if(r_count==0)
        return R_ARGUMENT_MISSING;
    // Accounts for missing S, R, and L_ARGUMENT_INVALID
    if(strcmp(argv[i], "-s") == 0){
        if(i + 1 >= argc || argv[i+1][0] == '-')
            return S_ARGUMENT_MISSING;
    }
    else if(strcmp(argv[i], "-r") == 0){
        if(i + 1 >= argc || argv[i+1][0] == '-')
            return R_ARGUMENT_MISSING;
    }
    else if(strcmp(argv[i], "-l") == 0){
        if (i + 1 >= argc || argv[i+1][0] == '-')
            return L_ARGUMENT_INVALID;

        int start, end;
        char extra;
        if(sscanf(argv[i+1], "%d,%d%c", &start, &end, &extra) != 2)
            return L_ARGUMENT_INVALID;

        if(start < 1 || end < 1 || start > end)
            return L_ARGUMENT_INVALID;
    }
    // Accounts for WILDCARD_INVALID
    return 0;
}
