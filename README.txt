Name: Lawrence Wong
Student ID: 116408194

To run each tests each time run "make clean", "make all", and then "make test".

The student_tests.c file is located in the folder tests with the unit_tests.c and I modified the makefile to compile the and run the tests.

The student_tests.c file accounts for the following:

• The arguments having MISSING_ARGUMENT
• The arguments having INPUT_FILE_MISSING
• The arguments having OUTPUT_FILE_UNWRITABLE
• The arguments having S_ARGUMENT_MISSING
• The arguments having R_ARGUMENT_MISSING
• The arguments having L_ARGUMENT_INVALID
• The l argument that doesn't have a second number returns L_ARGUMENT_INVALID
• The arguments having WILDCARD_INVALID
• The wildcard input having two stars returns WILDCARD_INVALID
• The wildcard input having no stars returns WILDCARD_INVALID
• The arguments having DUPLICATE_ARGUMENT
• The arguments having regular R and S arguments and valid input/output files.
• The input having regular l arguments.
• The input having regular w arguments.