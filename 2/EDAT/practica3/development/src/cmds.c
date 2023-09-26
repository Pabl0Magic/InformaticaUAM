/*
    Project: EDAT Lab 3 test program
    File:    cmds.c
    Author:  Simone Santini
    Rev.     1.0
    Date:    10/11/2019 
    
    This file contains the main command execution function as well as the
    function that does a controlled reading of the commands from the screen.
    
    
    See cmds.h for details and a list of commands.
*/


#include "cmds.h"
#include "import.h"
#include "table.h"
#include "type.h"
#include "index.h"
#include <ctype.h>
#include <string.h>


/* 
    This structure maintain the global status of the system. It contains
    the following fields:  
    
    text_in:  flag that determines whether we have valid text file data in 
              main memory
    text_data: data for the text file, as returned by the function f_read
    text_file: name of the text file
    
    table_in:   flag that determines whether there is a table in memory
    table:      table structure, as in table.c 
    tablefile:  name of the table 
    orig_key:  structure in which the original parameters of the keyboard
               are stored. The function c_get_cmd uses modified keyboard
               parameter, and the keyboard must be restored before exiting 
               the program. The original status is stored here.
    index_in:  flag that determines whether there is a index in memory
    index:     index structure, as in index.c 
    indexfile:  name of the index 
    key_changed: flag that determines whether we are already in the key_changed
                mode. Used to avoid doing the change twice.
*/

struct _cmdstatus {
    int text_in;
    filedata *txtdata;
    char *txtfile;
    
    int table_in;
    void *table;
    char *tablefile;

    int index_in;
    void *index;
    char *indexfile;
    struct termios orig_key;
    int    key_changed;
};



/*
    This is the type of the functions that execute one of the commands. they 
    receive the command line (complete: including the command), and the 
    status. Execute the command and returnn:
    
    0:  executed correctly
    1:  the command in the command line is not the one in the function
    2:  some parameter was incorrect (message written on the screen).
    
    The status structure is updated, if necessary.
*/

typedef int (*cmd_f)(cmdstatus *, char *);

/*
    Commands available
*/
#define read     "read"
#define tmake    "tmake"
#define tclose   "tclose"
#define topen    "topen"
#define check    "check"
#define tshow    "tshow" 
#define verify   "verify"
#define mkindex  "mkindex"
#define iinsert  "iinsert"
#define isave    "isave"
#define ifind    "ifind"
#define ishow    "ishow"
#define tindex   "tindex"
#define retrieve "retrieve"
#define help     "help"

/*
    Structure that contains the information to execute a command. It contains
    the name of the command and a pointer to the function that executes it.
*/

typedef struct {
    char *name;
    cmd_f exe;
} cmd_data;



/************************************************************************
 *
 *             A U X I L I A R Y    F U N C T I O N S 
 * 
 ************************************************************************/

/*
  Auxiliary function: _free_text(cmdstatus *cs)

  If the text file has been allocated in the given status, releases it and 
  marks the status as having no text file.

  Returns:
  Nothing
*/
void _free_text(cmdstatus *cs) {
  if (cs->text_in) {
    f_free(cs->txtdata);
    free(cs->txtfile);
    cs->text_in = 0;
  }
  return;
}


/*
  Auxiliary function: _free_table(cmdstatus *cs)

  If the table has been allocated in the given status, releases it and 
  marks the status as having no table.

  Returns:
  Nothing
*/
void _free_table(cmdstatus *cs) {
  if (cs->table_in) {
    table_close(cs->table);
    free(cs->tablefile);
    cs->table_in = 0;
  }
  return;
}


/*
  Auxiliary function: _free_index(cmdstatus *cs)

  If an index has been allocated in the given status, releases it and 
  marks the status as having no index.

  Returns:
  Nothing
*/
void _free_index(cmdstatus *cs) {
  if (cs->index_in) {
    index_save(cs->index);
    index_close(cs->index);
    free(cs->indexfile);
    cs->index_in = 0;
  }
  return;
}



/*
  Auxiliary function: char *_get_par(char *line, char *cmd, char *err_msg)
  
  Receives the input line and the command. Checks that the input line
  begins with the given command, otherwise prints an error
  message. After that, isolates and returns the parameter that follows
  the command, with the leading and trailing spaces removed. If the
  parameter is not present, print the contents of err?msg.

  Returns: 
  The parameter that follows the command, isolated in the same line
  that is passed as a paramter. Returns NULL if there is no paramenter
  after the command.
*/
char *_get_par(char *line, char *cmd, char *err_msg) {
  if (strncmp(line, cmd, strlen(cmd))) {
    printf("Command mismatch. called %s on %s\n", cmd, line);
    return NULL;
  }
  char *p = line + strlen(cmd);
  while(*p && isspace(*p))
    p++;
  if (!(*p)) {
    printf ("%s\n", err_msg);
    return NULL;
  }
  char *c = p + strlen(p) - 1;
  while (*c && isspace(*c) && c >=p)
    c--;
  if (c < p) {
    printf ("%s\n", err_msg);
    return NULL;
  }
  *(c+1) = 0;
  return p;
}  


/*
  Auxiliary function: char **_get_two_par(char *line, char *cmd, char *err_msg)
  
  Receives the input line and the command. Checks that the input line
  begins with the given command, otherwise prints an error
  message. After that, isolates and returns the two parameters that
  follow the command, with the leading and trailing spaces removed. If
  the parameter is not present, print the contents of err_msg.

  Returns:   
  An array of two strings, with the parameter that follows the
  command, isolated in the same line that is passed as a
  paramter. Note that the individual pointers should bot be released,
  but the char ** pointer should, indeed, be released. Returns NULL if
  there is no paramenter after the command.
  */
char **_get_two_par(char *line, char *cmd, char *err_msg) {
  if (strncmp(line, cmd, strlen(cmd))) {
    printf("Command mismatch. called %s on %s\n", cmd, line);
    return 0;
  }
  char **w = (char **) malloc(2*sizeof(char *));
  char *p = line + strlen(cmd);
  while(*p && isspace(*p))
    p++;
  if (!(*p)) {
    printf ("(1) %s\n", err_msg);
    return NULL;
  }
  w[0] = p;
  while (*p && !isspace(*p))
    p++;
  if (!(*p)) {
    printf ("(2) %s\n", err_msg);
    return NULL;
  }
  *p = 0;
  p++;
  while(*p && isspace(*p))
    p++;
  if (!(*p)) {
    printf ("(3) %s\n", err_msg);
    return NULL;
  }
  w[1] = p;
  while (*p && !isspace(*p))
    p++;
  if (*p) {
    *p = 0;
  }
  return w;
}  


/*
  Auxiliary function: int _tuple_check(void **txtval, table_t *tb, int ncols, type_t *types)

  Receives the contents of a record of the table and a record of the
  file and checks whether they are the same.

  Parameters:
  txtval:    ncols pointers to the data of a record taken from the text file
  tb:        the table, with the correct record already read in memory
  ncol:      number of columns in the table and the file
  types:     array of ncol elements with the types of the columns

  Returns:
  1:  the records are the same
  0:  the records differ

  In addition, the function prints the contents of the records. 
*/
int _tuple_check(void **txtval, table_t *tb, int ncols, type_t *types) {
  for (int i=0; i<ncols; i++) {
    print_value(stdout, types[i], txtval[i]);
    printf("\t");
  }
  printf("   text file\n");
  for (int i=0; i<ncols; i++) {
    print_value(stdout, types[i], table_get_col(tb, i));
    printf("\t");
  }
  printf("   table\n");
  for (int i=0; i<ncols; i++) {
    if (value_cmp(types[i], txtval[i], table_get_col(tb, i))) {
      printf("Record mismatch!\n");
      return 0;
    }
  }      
  return 1;
}

/*
  Auxiliary function: int _tuple_show(table_t *tb)

  Receives a table with a record already in memory, and prints the record
  on the screen.

  Parameters:
  tb:        the table, with the correct record already read in memory

  Returns:
  Nothing

*/
void _tuple_show(table_t *tb) {
    type_t *types = table_types(tb);
    for (int i=0; i<table_ncols(tb); i++) {
        print_value(stdout, types[i], table_get_col(tb, i));
        printf("\t");
    }
    printf ("\n");
}

/*
  Auxiliary function: char *_add_ext(char *name, char*ext)

  Adds the extension ext (given without the dot) to the given name. If
  the given name already has an extension, the old one will be removed
  and the new one placed in its stead.
*/
char *_add_ext(char *name, char*ext) {
  char *nn = (char *) malloc(strlen(name) + strlen(ext) + 4);
  strcpy(nn, name);
  char *c = strrchr(nn, '.');
  if (c) {
    *c = 0;
  }
  sprintf(nn, "%s.%s", nn, ext);
  return nn;
}

/*
  Auxiliary function: int _check(cmdstatus *cs);

  Checks that the contents of the text file in the cmdstatus and those
  of the table are the same.

  Returns:
  1: the contents are the sae
  0: there is a mismatch. In this case, a messae is printed.

  The function does not check that text and table are defined. The caller
  must make sure of it.
*/
int _check(cmdstatus *cs) {
  if (f_columns(cs->txtdata) != table_ncols(cs->table)) {
    printf("Column mismatch> %d columns in text, %d in table\n", f_columns(cs->txtdata), table_ncols(cs->table));
    return 0;
  }
  type_t *tp = table_types(cs->table);
  type_t *tp1 = f_types(cs->txtdata);
  for (int i=0; i<f_columns(cs->txtdata); i++) {
    if (tp[i] != tp1[i]) {
      printf("Type mismatch on column %d\n", i);
      return 0;
    }    
  }      
  long pt = table_first_pos(cs->table);
  for (int i=0; i<f_records(cs->txtdata); i++) {
    pt = table_read_record(cs->table, pt);
    if (pt<0) {
      printf("Mismatch on record number: text has more than the table\n");
      return 0;
    }    
    if (!_tuple_check(f_vals(cs->txtdata, i), cs->table, table_ncols(cs->table), table_types(cs->table))) 
      return 0;
  }
  pt = table_read_record(cs->table, pt);
  if (pt>0) {
    printf("Mismatch on record number: table has more than the text\n");
    return 0;
  }    
  return 1;
}



/**********************************************************************

              FUNCTIONS THAT IMPLEMENT COMMANDS

 **********************************************************************
*/

/*
  Function:  int _cmd_read(cmdstatus *cs, char*line)
  
  Executes the read command: reads a text file specified in the command 
  line) in the command status and updates the command structure 
  accordingly.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)

  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_read(cmdstatus *cs, char*line) {  
  char *p = _get_par(line, read, "Usage: read <file>");
  if (!p) return 0;

  _free_text(cs);
  FILE *fp = fopen(p, "r");
  if (!fp) {
    printf("file %s does not exist\n", p);
    return 0;
  }
  fclose(fp);
  cs->txtfile = strdup(p);
  cs->text_in = 1;
  cs->txtdata = f_read(cs->txtfile);
  printf("Text data in\n");
  return 1;
}

/*
  Function:  int _cmd_tmake(cmdstatus *cs, char*line)
  
  Executes the tmake command: stores the contents of the text file
  currently in memory on the table specified in the command line. If
  there is no text file in memory, no table is created.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_tmake(cmdstatus *cs, char*line) {
  char *p = _get_par(line, tmake, "Usage: tmake <file>");
  if (!p) return 0;

  _free_table(cs);
  if (!cs->text_in) {
    printf("No text file was loaded: use read <file> to load a file before creating the table.\n");
    return 0;
  }
  if (!table_create(p, f_columns(cs->txtdata), f_types(cs->txtdata)) || !(cs->table = table_open(p))) {
    printf("Error creating table %s\n", p);
    return 0;
  }
  cs->table_in = 1;
  cs->tablefile = strdup(p);
  for (int i=0; i<f_records(cs->txtdata); i++) 
    table_insert_record(cs->table, f_vals(cs->txtdata, i));
  return 1;
}

/*
  Function:  int _cmd_topen(cmdstatus *cs, char*line)
  
  Executes the topen command: opens a table and keeps it in memory as
  the current table.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_topen(cmdstatus *cs, char*line) {
  char *p = _get_par(line, topen, "Usage: topen <file>");
  if (!p) return 0;

  _free_table(cs);
  if (!(cs->table = table_open(p))) {
    printf("Error opening table %s\n", p);
    return 0;
  }
  cs->table_in = 1;
  cs->tablefile = strdup(p);
  return 1;
}

/*
  Function:  int _cmd_tclose(cmdstatus *cs, char*line)
  
  Executes the tclose command: closes the currently opened table.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_tclose(cmdstatus *cs, char*line) {
  char mycmd[] = tclose;
  if (strncmp(line, mycmd, strlen(mycmd))) {
    printf("Command mismatch. called %s on %s\n", mycmd, line);
    return 0;
  }
  if (!cs->table_in) {
    printf("No table currently open in memory.\n");
    return 0;
  }
  table_close(cs->table);
  free(cs->tablefile);
  cs->table_in = 0;
  return 1;
}


/*
  Function:  int _cmd_check(cmdstatus *cs, char*line)
  
  Executes the check command: checks whether the text in memory and the contents
  of the table have the same content.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_check(cmdstatus *cs, char*line) {
  char mycmd[] = check;
  if (strncmp(line, mycmd, strlen(mycmd))) {
    printf("Command mismatch. called %s on %s\n", mycmd, line);
    return 0;
  }
  if (!cs->table_in || !cs->text_in) {
    printf("You need to have a text and a table in memory in order to check.\n");
    return 0;
  }
  return _check(cs);
}

/*
  Function:  int _cmd_tshow(cmdstatus *cs, char*line)
  
  Executes the tshow command: Shows the nth record of a table

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_tshow(cmdstatus *cs, char*line) {
  char *p = _get_par(line, tshow, "Usage: tshow <n>");
  if (!p) return 0;

  int n = atoi(p);
  if (!cs->table_in) {
    printf("No table in memory\n");
    return 0;
  }  
  long pt = table_first_pos(cs->table);
  for (int i=0; i<n; i++) {
    pt = table_read_record(cs->table, pt);
    if (pt < 0) {
      printf("Record %d does not exist; table has %d\n", n, i);
      return 0;
    }
  }
  _tuple_show(cs->table);
  return 1;
}

/*
  Function:  int _cmd_verify(cmdstatus *cs, char*line)
  
  Executes the verify command: loads a text file, creates a table for it, then
  verifies the equality of the two

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_verify(cmdstatus *cs, char*line) {
  char *p = _get_par(line, verify, "Usage: verify <file>");
  if (!p) return 0;

  _free_text(cs);
  _free_table(cs);
  FILE *fp = fopen(p, "r");
  if (!fp) {
    printf("file %s does not exist\n", p);
    return 0;
  }
  fclose(fp);
  cs->txtfile = strdup(p);
  cs->text_in = 1;
  cs->txtdata = f_read(cs->txtfile);

  p = cs->tablefile = _add_ext(cs->txtfile, "dat");
  if (!table_create(p, f_columns(cs->txtdata), f_types(cs->txtdata)) || !(cs->table = table_open(p))) {
    printf("Error creating table %s\n", p);
    return 0;
  }
  cs->table_in = 1;
  for (int i=0; i<f_records(cs->txtdata); i++) 
    table_insert_record(cs->table, f_vals(cs->txtdata, i));
  table_close(cs->table);

  cs->table=table_open(p);
  return _check(cs);
}


/*
  Function:  int _cmd_mkindex(cmdstatus *cs, char*line)
  
  Executes the mkindex command: creates an empty index in memory and 
  on the given file. The index is created and then opened in memory.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_mkindex(cmdstatus *cs, char*line) {
  char *p = _get_par(line, mkindex, "Usage: mkindex <file>");
  if (!p) return 0;

  _free_index(cs);
  if (!index_create(p, INT)) {
    printf("Error creating the file\n");
    return 0;
  }
  if (!(cs->index = index_open(p))) {
    printf("Error opening the index\n");
    return 0;
  }
  cs->indexfile = strdup(p);
  cs->index_in = 1;
  return 1;
}

/*
  Function:  int _cmd_iinsert(cmdstatus *cs, char*line)
  
  Executes the iinsert command: inserts a (key, position) pair into an
  index.  

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_iinsert(cmdstatus *cs, char*line) {
  if (!cs->index_in) {
    printf("No index defined\n");
    return 0;
  }

  char **p = _get_two_par(line, iinsert, "Usage: insert <key> <position>");
  if (!p) return 0;

  int key = atoi(p[0]);
  long pos = atol(p[1]);
  free(p);
  int n = index_put(cs->index, key, pos);
  if (n>0) {
    printf("%d entries in the index\n", n);
    return 1;
  }
  else {
    printf("Error in insertion\n");
    return 0;
  }
}

/*
  Function:  int _cmd_ifind(cmdstatus *cs, char*line)
  
  Executes the ifind command: searches the index for a key and prints
  all the positions associated to it.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_ifind(cmdstatus *cs, char*line) {
  char *p = _get_par(line, ifind, "Usage: ifind <key>");
  if (!p) return 0;

  if (!cs->index_in) {
    printf("No index defined\n");
    return 0;
  }

  int key = atoi(p);
  int npos = 0;

  long *poss = index_get(cs->index, key, &npos);
  if (!poss) {
    printf("Key %d not in the index\n", key);
    return 1;
  }
  else {
    printf("%d --> ", key);
    for (int k=0; k<npos; k++) 
      printf("%ld\t", poss[k]);
    printf("\n");
  }
  return 1;
}


/*
  Function:  int _cmd_ishow(cmdstatus *cs, char*line)
  
  Executes the ishow command: shows the contents of an index in the
  order in which they are stored (if the index is correct, the primary
  keys should come out ordered).

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_ishow(cmdstatus *cs, char*line) {
  char mycmd[] = ishow;
  if (strncmp(line, mycmd, strlen(mycmd))) {
    printf("Command mismatch. called %s on %s\n", mycmd, line);
    return 0;
  }

  if (!cs->index_in) {
    printf("No index defined\n");
    return 0;
  }

  int npos = 0;
  int key = 0;
  long *poss;

  for (int n=0; poss= index_get_order(cs->index, n, &key, &npos); n++) {
    printf("%d --> ", key);
    for (int k=0; k<npos; k++) 
      printf("%ld\t", poss[k]);
    printf("\n");
  }
  return 1;
}




/*
  Function:  int _cmd_tindex(cmdstatus *cs, char*line)
  
  Executes the tindex command: Creates an index in the file <file> for
    the column <col> of the table currently in memory, and stores all
    the record in the index

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_tindex(cmdstatus *cs, char*line) {
  if (!cs->table_in) {
    printf("No table defined\n");
    return 0;
  }

  char **p = _get_two_par(line, tindex, "Usage: ifind <key>");
  if (!p) return 0;
  char *file = p[0];
  int col = atoi(p[1]);
  free(p);
  if (col < 0 || col >= table_ncols(cs->table)) {
    printf ("Table does not have a column number %d\n", col);
    return 0;
  }
  type_t *t = table_types(cs->table);
  if (t[col] != INT) {
    printf("Only INT columns can be indexed in this version\n");
    return 0;
  }
  _free_index(cs);
  index_create(file, t[col]);
  cs->index = index_open(file);

  long pt = table_first_pos(cs->table);
  long pt1;
  while((pt1 = table_read_record(cs->table, pt))>=0) {
    int key = *((int *) table_get_col(cs->table, col));
    index_put(cs->index, key, pt);
    pt = pt1;
  }
  index_save(cs->index);
  cs->indexfile = strdup(file);
  cs->index_in = 1;
  return 1;
}


/*
  Function:  int _cmd_retrieve(cmdstatus *cs, char*line)
  
  Executes the retrieve command: searches the index for a key and prints
  all the positions associated to it.

  Parameters:
  cs:   the current status of the program (see the cmdstatus structure
        definition)
  line: the complete line given as a command (that is, including the 
        command itself)
  
  returns 1 on success, 0 on failure (prints a message if necessary)
*/
int _cmd_retrieve(cmdstatus *cs, char*line) {
  char *p = _get_par(line, retrieve, "Usage: retrieve <key>");
  if (!p) return 0;

  if (!cs->index_in || !cs->table_in) {
    printf("You need both a table and its index loaded\n");
    return 0;
  }
  int key = atoi(p);
  int npos = 0;
  long *poss = index_get(cs->index, key, &npos);
  if (!poss) {
    printf("Key not in the table\n");
    return 1;
  }
  for (int k=0; k<npos; k++) {
    table_read_record(cs->table, poss[k]);
    _tuple_show(cs->table);
  }
  return 1;
}




/*
  Function:  int _cmd_help(cmdstatus *cs, char*line)
  
  Executes the help command: prints a help message on the screen
  taking it from the file t_help.txt.

  Parameters:
    Ignored
    
  Returns:
  1: help printed
  0: help file not found
*/
int _cmd_help(cmdstatus *cs, char *line) {
    FILE *hf = fopen("t_help.txt", "r");
    if (!hf) {
        printf("Help file not found. Sorry.\n");
        return 0;
    }
    char buf[1000];
    while(fgets(buf, 1000, hf)) 
        printf("%s", buf);
    printf("\n");
    fclose(hf);
    return 1;
}



/************************************************************************
 *
 *  P U B L I C    F U N C T I O N S 
 * 
 * 
 ************************************************************************/


/*
    Function: c_create()

    Creates an empty command status function and returns it. 
*/
cmdstatus *c_create() {
    cmdstatus *cs = (cmdstatus *) malloc(sizeof(cmdstatus));
    cs->text_in = 0;
    cs->txtdata = NULL;
    cs->txtfile = NULL;
    cs->table_in = 0;
    cs->table = NULL;
    cs->tablefile = NULL;
    
    cs->index_in = 0;
    cs->index = NULL;
    cs->indexfile = NULL;

    tcgetattr(fileno(stdin), &(cs->orig_key));
    cs->key_changed = 0;
    
    return cs;
}


/*
  Function: void c_close(cmdstatus *cs);

  Closes a status: closes the table, saves the index and closes it,
  frees the text space and frees the command structure.

  NOTE: This function must be called for the index to be saved on disk.
*/
void c_close(cmdstatus *cs) {
  _free_text(cs);
  _free_index(cs);
  _free_table(cs);
  free(cs);
  return;
}



/*
    Function: c_key_init(cmdstatus *cs)
    
    Initializes the keyboard to work in the non-standard mode that we 
    need to control command input with the function cmd_get: this function
    should be called once before calling c_cmd_get for the first time. At the 
    end of the program, the main program should call c_key_restore to 
    restore the keyboard in its default state.
*/
void c_key_init(cmdstatus *cs) {
    if (!cs) return;
    if (cs->key_changed) return;

	struct termios new; /*a termios structure contains a set of attributes about 
					    how the terminal scans and outputs data*/
		
	new = cs->orig_key;	    
						        
	new.c_lflag &= ~ICANON;    
						       
						  
	new.c_lflag &= ~ECHO; 
						  
	new.c_cc[VMIN] = 1;   
					      
	new.c_cc[VTIME] = 0;  
	new.c_lflag &= ~ISIG; 
						  
	tcsetattr(fileno(stdin), TCSANOW, &new);  
    cs->key_changed = 1;
    return;
}

/*
    Function: c_key_restore(cmdstatus *cmd);
    
    Restores the keyboard to work in the standard mode. This function
    should be called once before exiting the program. 
*/
void c_key_restore(cmdstatus *cs) {
    if (!cs) return;
    if (!cs->key_changed) return;
	tcsetattr(fileno(stdin), TCSANOW, &(cs->orig_key));  
    return;
}

/*
    Function:  char *c_cmd_get(int maxlen);
    
    Reads a line from the keyboard, limiting the inmput to maxlen 
    characters. Only maxlen characters will be displayed on the screen
    (if you type more, the last character will be overwritten).
    Only the ascii characters, the backspace and the Enter key are 
    recognized.
    
    Returns: the string entered or NULL if there is any problem.
*/
char *c_cmd_get(int max_len) {
    char *res = (char *) malloc((max_len+1)*sizeof(char));
    int cur = 0;
    char prompt[] = "$ ";
    int begin = strlen(prompt) + 1;
    
    printf("%s", prompt);
    while(1) {
        printf("%c[%dG", 27, begin+cur);
        char ch = fgetc(stdin);
        if (ch == '\n') {
            res[cur] = 0;
            return res;
        }
        else if (ch == 127) {
            if (cur > 0) {
                cur--;
                printf("%c[%dG ", 27, begin+cur);
                res[cur] = 0;
            }
        }
        else if (ch >= 32) {
            res[cur] = ch;
            printf("%c[%dG", 27, begin+cur);
            printf("%c", ch);
            fflush(stdout);
            if (cur < max_len) cur++;
        }
    }
}


/*
    List of commands and associated Functions
*/

cmd_data cmds[] = {
    {read, _cmd_read},
    {tmake, _cmd_tmake},
    {topen, _cmd_topen},
    {tclose, _cmd_tclose},
    {check, _cmd_check},
    {tshow, _cmd_tshow},
    {verify, _cmd_verify},
    {mkindex, _cmd_mkindex},
    {iinsert, _cmd_iinsert},
    {ifind, _cmd_ifind},
    {ishow, _cmd_ishow},
    {tindex, _cmd_tindex},
    {retrieve, _cmd_retrieve},
    {help, _cmd_help},
    {NULL, NULL}
};



/*
    Function: int c_execute(cmdstatus *cs, char *cmd)
    
    Executes the command "cmd", given as it is read from the command 
    line. Searches the command in the command list and executes the 
    associated function. Prints an error message if the command does not 
    exist in the list.
    
    Returns 1 if the command has been executed, 0 if it was unknown or
    there was en error.
*/
int c_execute(cmdstatus *cs, char *cmd) {
     for (cmd_data *p=cmds; p->name; p++) {
         if (!strncmp(p->name, cmd, strlen(p->name))) {
             return (p->exe)(cs, cmd);
         }
     }
     printf("Unknown command\n");
     return 0;
}


/*
  Function: void c_print_status(cmdstatus *cs);

  Prints on the screen the current status of the command program.
*/
void c_print_status(cmdstatus *cs) {
  if (cs->text_in)
    printf("Text: %s, ", cs->txtfile);
  else
    printf("Text: none, ");
  if (cs->table_in)
    printf("table: %s, ", cs->tablefile);
  else
    printf("table: none, ");
  if (cs->index_in)
    printf("index: %s, ", cs->indexfile);
  else
    printf("index: none, ");
  printf("\n");
  return;
}
