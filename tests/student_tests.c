/*
    Name: Lawrence Wong
    ID: 116408194
*/

#include "unit_tests.h"
#include "hw6.h"

TestSuite(student_output, .timeout=TEST_TIMEOUT, .disabled=false); // output file
TestSuite(student_valgrind, .timeout=TEST_TIMEOUT, .disabled=false); // valgrind result

TestSuite(student_invalid_args, .timeout=TEST_TIMEOUT); // return code to OS

static char args[ARGS_TEXT_LEN];

// Testing error status codes
Test(student_invalid_args, missing_argument01, .description="no inputs") {
    char *test_name = "missing_argument01";
    prep_files("unix.txt", test_name);    
    sprintf(args, " ");
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}

Test(student_invalid_args, missing_argument02, .description="missing output file") {
    char *test_name = "missing_argument02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r end %s/%s.in.txt", TEST_INPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}

Test(student_invalid_args, missing_argument03, .description="missing output file") {
    char *test_name = "missing_argument03";
    prep_files("unix.txt", test_name);
    sprintf(args, "-s the -r end %s/%s.in.txt", TEST_INPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}

Test(student_invalid_args, missing_argument04, .description="missing -r") {
    char *test_name = "missing_argument04";
    prep_files("unix.txt", test_name);
    sprintf(args, "-s end %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}

Test(student_invalid_args, missing_argument05, .description="missing -r and -s") {
    char *test_name = "missing_argument05";
    prep_files("unix.txt", test_name);
    sprintf(args, "%s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}

Test(student_invalid_args, s_argument_missing, .description="-s argument is missing") {
    char *test_name = "s_argument_missing";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-r the -g WOLFIE -s -l 4,13 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, S_ARGUMENT_MISSING);
}

Test(student_invalid_args, r_argument_missing, .description="-r argument is missing") {
    char *test_name = "r_argument_missing";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r -l 4,13 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, R_ARGUMENT_MISSING);
}

Test(student_invalid_args, input_file_missing, .description="input file is missing") {
    char *test_name = "student_s_argument_missing";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-r the -g WOLFIE -s -l 13,4  %s/%s.out.txt", TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, INPUT_FILE_MISSING);
}

Test(student_invalid_args, output_file_unwriteable, .description="output file is unwriteable.") {
    char *test_name = "student_output_file_unwritable";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s th -r where %s/%s.in.txt /%s.out.txt", TEST_INPUT_DIR, test_name, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, OUTPUT_FILE_UNWRITABLE);
}

Test(student_invalid_args, wildcard_invalid01, .description="double star wildcard") {
    char *test_name = "wildcard_invalid01";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s *the* -r where -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, WILDCARD_INVALID);
}

Test(student_invalid_args, wildcard_invalid02, .description="no star wildcard") {
    char *test_name = "wildcard_invalid02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, WILDCARD_INVALID);
}

Test(student_invalid_args, duplicated_arguments01, .description="duplicate -s") {
    char *test_name = "duplicated_arguments01";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -s huh %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}

Test(student_invalid_args, duplicated_arguments02, .description="duplicate -s higher priority than wildcard") {
    char *test_name = "duplicated_arguments02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -s huh -r where -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}

Test(student_invalid_args, duplicated_arguments03, .description="duplicate -r") {
    char *test_name = "duplicated_arguments03";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -r huh %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}

Test(student_invalid_args, duplicated_arguments04, .description="duplicate -l") {
    char *test_name = "duplicated_arguments04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l 10,15 -l 10,15 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}

Test(student_invalid_args, duplicated_arguments05, .description="duplicate -w") {
    char *test_name = "duplicated_arguments05";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -w -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}

Test(student_invalid_args, l_argument_invalid01, .description="no l argument") {
    char *test_name = "l_argument_invalid01";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

Test(student_invalid_args, l_argument_invalid02, .description="l argument range is wrong") {
    char *test_name = "l_argument_invalid02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l 15,10 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

Test(student_invalid_args, l_argument_invalid03, .description="l argument string taken as 0") {
    char *test_name = "l_argument_invalid03";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l 10,sbu15 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

Test(student_invalid_args, l_argument_invalid04, .description="l argument is 0, 0 from string") {
    char *test_name = "l_argument_invalid04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l sbu15,sbu10 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

Test(student_invalid_args, l_argument_invalid05, .description="l argument is 0, 0") {
    char *test_name = "l_argument_invalid05";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l 0,0 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

Test(student_invalid_args, l_argument_invalid06, .description="missing second number") {
    char *test_name = "l_argument_invalid06";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r where -l 5 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

// Testing regular use
Test(student_output, student_search01, .description="Perform a simple replacement over entire file. Terms have the same length.") {
    char *test_name = "student_search01";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -r WOLFIE %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}

Test(student_output, student_search02, .description="Ignores unrecognized options and arguments") {
    char *test_name = "student_search02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s the -k -r WOLFIE -h  %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}

Test(student_output, student_search03, .description="-l 10,15 and ignores order.") {
    char *test_name = "student_search03";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-l 10,15 -s the -r WOLFIE %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}

Test(student_output, student_search04, .description="Tests for -s searching for the input text file.") {
    char *test_name = "student_search04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-l 10,15 -r the -s %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}

Test(student_output, student_wildcard_search01, .description="Prefix wildcard") {
    char *test_name = "student_wildcard_search01";
    prep_files("oneword.txt", test_name);
    sprintf(args, "-s Hom* -r \"This homework is NOT effortless.\" -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}

Test(student_output, student_wildcard_search02, .description="Postfix wildcard") {
    char *test_name = "student_wildcard_search02";
    prep_files("oneword.txt", test_name);
    sprintf(args, "-s Hom* -r \"This homework is REALLY NOT effortless.\" -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}