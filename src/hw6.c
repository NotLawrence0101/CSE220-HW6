#include "hw6.h"

int main(int argc, char *argv[]) {
    // Accounts for MISSING_ARGUMENT
    if(argc < 7)
        return MISSING_ARGUMENT;

    // Initialize counts for duplicates and arguments
    int s_count=0, r_count=0, l_count=0, w_count=0;
    char *s_arg=NULL, *r_arg=NULL, *l_arg=NULL;
    int opt;
    opterr = 0;

    // Loop with getopt
    while((opt = getopt(argc, argv, "s:r:l:w")) != -1){
        switch(opt){
            case 's':
                if(s_count>0) 
                    return DUPLICATE_ARGUMENT;
                s_arg = optarg; 
                s_count++; 
                break;
            case 'r':
                if(r_count>0) 
                    return DUPLICATE_ARGUMENT;
                r_arg = optarg; 
                r_count++; 
                break;
            case 'l':
                if(l_count>0) 
                    return DUPLICATE_ARGUMENT;
                l_arg = optarg; 
                l_count++; 
                break;
            case 'w':
                if(w_count>0) 
                    return DUPLICATE_ARGUMENT;
                w_count++; 
                break;
            case '?': 
                break;
        }
    }

    // Accounts for file input and output errors
    char *input = argv[argc-2];
    char *output = argv[argc-1];

    FILE *fp = fopen(input, "r");
    if(!fp)
        return INPUT_FILE_MISSING;
    fclose(fp);

    fp = fopen(output, "w");
    if(!fp) 
        return OUTPUT_FILE_UNWRITABLE;
    fclose(fp);

    // Accounts for S_ARGUMENT_MISSING
    if(s_count == 0 || s_arg == NULL || s_arg[0] == '-')
        return S_ARGUMENT_MISSING;
    // Accounts for R_ARGUMENT_MISSING
    if(r_count == 0 || r_arg == NULL || r_arg[0] == '-')
        return R_ARGUMENT_MISSING;

    // Accounts for L_ARGUMENT_INVALID
    if(l_count > 0){
        if(!l_arg || l_arg[0] == '-') 
            return L_ARGUMENT_INVALID;
        if(strchr(l_arg, ',') == NULL) 
            return L_ARGUMENT_INVALID;

        int start, end; 
        char extra;
        if(sscanf(l_arg, "%d,%d%c", &start, &end, &extra) != 2)
            return L_ARGUMENT_INVALID;

        if(start < 1 || end < 1 || start > end)
            return L_ARGUMENT_INVALID;
    }

    // Accounts for WILDCARD_INVALID
    if(w_count > 0){
        int len = strlen(s_arg);
        int star_count = 0;
        for(int i = 0; i < len; i++){
            if(s_arg[i] == '*'){
                star_count++;
                if(i != 0 && i != len - 1)
                    return WILDCARD_INVALID;
            }
        }
        if(star_count == 0)
            return WILDCARD_INVALID;
        if(star_count > 1)
            return WILDCARD_INVALID;
    }
    return 0;
}