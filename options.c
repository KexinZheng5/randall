#include "options.h"

// process nbytes with result returned
void argProcess(int argc, char** argv, struct options *op){
  // get args
  parseArgs(argc, argv, op);

  // process input
  inputProcess(op); 
}



// parse arguments
void parseArgs(int argc, char** argv, struct options* op){
  char c;
  char *endptr;
  bool bytesSet = false; 
  // initialize to 0
  op->input = 0;
  op->output = 0;
  while ((c = getopt (argc, argv, ":i:o:")) != -1){
    switch (c)
      {
      // input
      case 'i':
        if(optarg[0] == '-') {
          fprintf(stderr,
                "Error: Option '-i' requires an operand\n");
          exit(EXIT_FAILURE);
        }
        op->input = optarg;
        break;
      // output
      case 'o':
        if(optarg[0] == '-') {
          fprintf(stderr,
                "Error: Option '-o' requires an operand\n");
          exit(EXIT_FAILURE);
        }
        op->output = optarg;
        break;
      // lack operand
      case ':':
          fprintf(stderr,
                "Error: Option '-%c' requires an operand\n", optopt);
          exit(EXIT_FAILURE);
          break;
      // not recognized
      case '?':
          fprintf(stderr,
                "Error: Unrecognized option: '-%c'\n", optopt);
          exit(EXIT_FAILURE);
          break;
      }
    }
    // find process nbytes
    for(int i = 1; i < argc; i++) {
      // skip optional arguments
      if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "-i"))
        i++; 
      // store nbytes if not found
      else if (!bytesSet)
      {
        errno = 0;
        op->nbytes = strtoll (argv[i], &endptr, 10);
        // nbytes is valid
        if (!errno && !*endptr && 0 <= op->nbytes)
          bytesSet = true; 
      }
      // extra argument
      else 
      {
        fprintf(stderr,
                "Error: Extra argument '%s'\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
    // nbytes not found or not valid
    if(bytesSet == false){
      fprintf(stderr,
                "Error: NBYTES is invalid or not given\n");
      exit(EXIT_FAILURE);
    }
}



// process input option
void inputProcess(struct options *op){
  // hardware (should be default)
  if(!(op->input) || !strcmp(op->input, "rdrand")){
    // suported
    if (rdrand_supported ()){
      hwInput(op);
    }
    // not suported but input is default (should switch to software)
    else if (!(op->input)){
     swInput(op);
     setInput("/dev/random");
    }
    // not suported and hardware is specified
    else{
      fprintf (stderr,
	       "Error: hardware random-number generation is not available");
      exit(EXIT_FAILURE);
    }   
  }
  // use mrand48_r
  else if(!strcmp(op->input, "mrand48_r")){
    mrandInput(op);
  }
  // software generated random character with given file name
  else{
    swInput(op);
    // set inputfile name
    setInput(op->input);
  }
}

void hwInput(struct options *op){
  op->initialize = hardware_rand64_init;
  op->rand64 = hardware_rand64;
  op->finalize = hardware_rand64_fini;
}

void swInput(struct options *op){
  op->initialize = software_rand64_init;
  op->rand64 = software_rand64;
  op->finalize = software_rand64_fini;
}

void mrandInput(struct options *op){
  op->initialize = mrand48_init;
  op->rand64 = mrand48_rand64;
  op->finalize = mrand48_rand64_fini;
}
