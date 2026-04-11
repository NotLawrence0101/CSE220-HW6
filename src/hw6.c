/*
    Name: Lawrence Wong
    ID: 116408194
*/

#include "hw6.h"
#define MAX_LINE_LEN 1024

void wildcard_replace_line(FILE *out, char *line, char *s_arg, char *r_arg){
    int len = strlen(line);
    int i = 0;

    int is_prefix = (s_arg[strlen(s_arg)-1] == '*');
    int is_suffix = (s_arg[0] == '*');

    char pattern[256];
    if(is_prefix){
        strncpy(pattern, s_arg, strlen(s_arg)-1);
        pattern[strlen(s_arg)-1] = '\0';
    }
    else{
        strcpy(pattern, s_arg + 1);
    }

    while(i < len){
        // Non-word char → copy directly
        if(!isalnum(line[i])){
            fputc(line[i], out);
            i++;
            continue;
        }

        // Extract word
        int start = i;
        while(i < len && isalnum(line[i])) 
            i++;
        int word_len = i - start;

        char word[256];
        strncpy(word, line + start, word_len);
        word[word_len] = '\0';

        int match = 0;
        if(is_prefix){
            int plen = strlen(pattern);
            if (word_len >= plen && strncmp(word, pattern, plen) == 0)
                match = 1;
        }
        if(is_suffix){
            int plen = strlen(pattern);
            if(word_len >= plen && strcmp(word + word_len - plen, pattern) == 0)
                match = 1;
        }

        if(match)
            fputs(r_arg, out);
        else
            fwrite(word, 1, word_len, out);
    }
}

int main(int argc, char *argv[]) {
    // Accounts for MISSING_ARGUMENT
    if(argc < 7)
        return MISSING_ARGUMENT;

    // Initialize counts for duplicates and arguments
    int s_count=0, r_count=0, l_count=0, w_count=0;
    char *s_arg=NULL, *r_arg=NULL, *l_arg=NULL;
    int opt;
    opterr = 0;

    // Loop with getopt for DUPLICATE_ARGUMENT
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
    int start_line = 1, end_line = 1e9;
    if (l_count > 0) {
    char extra;
        if (!strchr(l_arg, ','))
            return L_ARGUMENT_INVALID;
        if (sscanf(l_arg, "%d,%d%c", &start_line, &end_line, &extra) != 2)
            return L_ARGUMENT_INVALID;
        if (start_line < 1 || end_line < 1 || start_line > end_line)
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

    // Read and write
    FILE *in = fopen(input, "r");
    if(!in) 
        return INPUT_FILE_MISSING;

    FILE *out = fopen(output, "w");
    if(!out){
        fclose(in);
        return OUTPUT_FILE_UNWRITABLE;
    }

    char buffer[MAX_LINE_LEN];
    int current_line=1;

    while(fgets(buffer, sizeof(buffer), in)){
        if(current_line < start_line || current_line > end_line){
            fputs(buffer, out);
        } else{
            if(w_count > 0){ // Wild card
                wildcard_replace_line(out, buffer, s_arg, r_arg);
            } else{
                char *curr = buffer, *match;
                while((match = strstr(curr, s_arg)) != NULL){
                    fwrite(curr, 1, match-curr, out);
                    fputs(r_arg, out);
                    curr = match + strlen(s_arg);
                }
                fputs(curr, out);
            }
        }
        current_line++;
    }

    fclose(in);
    fclose(out);
    return 0;
}