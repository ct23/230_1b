/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady
 *
 * Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  4/19/2013    Modernized call to fprintf for errors.
 *   Modified:  5/25/2015    Updated to use printError function.
 *
 *   Modified: 4/17/2016    Implemented printLabels function
 *   Modified: 4/18/2016    Implemented findLabel
 *   Modified: 4/24/2016    Created and implemented verifyLabelExists function
 *                          Implemented addLabel, tableInit
 *
 * WARNING: These functions are incomplete!!!!!
*/

#include "assembler.h"

// internal global variables (global to this file only)
static const char * ERROR0 = "Error: no label table exists.\n";
static const char * ERROR1 = "Error: a duplicate label was found.\n";
static const char * ERROR2 = "Error: cannot allocate space in memory.\n";

// internal function (visible to this file only)
static int verifyTableExists(LabelTable * table);

void tableInit (LabelTable * table)
  /* Postcondition: table is initialized to indicate that there
   *       are no label entries in it.
   */
{
    /* verify that current table exists */
    if ( ! verifyTableExists (table) )
        return;           /* fatal error: table doesn't exist */

    table->capacity = 0;
    table-> nbrLabels = 0;
    table->entries = 0;
    //if (table-> entries != NULL) {
    //    printf("ERROR: Existing table entries found for new table");
    //}
    
}

void printLabels (LabelTable * table)
  /* Postcondition: all the labels in the table, with their
   *      associated addresses, have been printed to the standard
   *      output.
   */
{
    int i;
    
    /* If the table is null, print that */
    if ( table == NULL )
        (void) printf ("Label Table is a NULL pointer.\n");
    else
    {
        /* Prints the number of labels */
        (void) printf ("There are %d labels in the table:\n",
                                table->nbrLabels);

        /* Iterate through table and entries. If an entry has
            a label, label and address are printed */
        for (i = 0; i < table->nbrLabels; i++) {
            if (table->entries[i].label != NULL) {
                printf("Label: %s, address: %d\n", table->entries[i].label,
                        table->entries[i].address);
            }
        }
    }
}

int findLabel (LabelTable * table, char * label)
  /* Returns the address associated with the label; -1 if label is
   *      not in the table or table doesn't exist
   */
{
    int i;
    
    // Iterate through the table
    // Return address of current label IF equal to label in question
    for (i = 0; i < table->capacity; i++) {
        if ((table->entries[i].label) == label) {
            return table->entries[i].address;
        }
    }
    // If label cannot be found, function fails
    return -1;
}

int addLabel (LabelTable * table, char * label, int PC)
  /* Postcondition: if label was already in table, the table is 
   *      unchanged; otherwise a new entry has been added to the 
   *      table with the specified label name and instruction address
   *      (memory location) and the table has been resized if necessary.
   * Returns 1 if no fatal errors occurred; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
    char * labelDuplicate;

    /* verify that current table exists */
    if ( ! verifyTableExists (table) )
        return 0;           /* fatal error: table doesn't exist */

    /* Was the label already in the table? */
    if (verifyLabelExists(table, label))
    {
        /* This is an error (ERROR1), but not a fatal one.
         * Report error; don't add the label to the table again.
         */
        printf("\n%s", ERROR1);
        return 0;
    }

    /* Create a dynamically allocated version of label that will persist. */
    /*   NOTE: on some machines you may need to make this _strdup !  */
    if ((labelDuplicate = strdup (label)) == NULL)
    {
        printError ("%s", ERROR2);
        return 0;           /* fatal error: couldn't allocate memory */
    }

    /* Resize the table if necessary. */
    if ( table->nbrLabels >= table->capacity )
    {
        if (! tableResize(table, (table->nbrLabels + 1))) {
            printf("ERROR: Table resizing encountered an error!");
        }
        /* Tip:  Choose a new size that will work even if current
         *       capacity is 0.
         */
    }

    // Create a label entry with given parameters
    LabelEntry newEntry;
    newEntry.label = label;
    newEntry.address = PC;
    /* Add the entry to the table */
    table->entries[table->nbrLabels] = newEntry;
    // Increment nbrLabels
    table->nbrLabels ++;

    return 1;               /* everything worked great! */
}

int tableResize (LabelTable * table, int newSize)
  /* Postcondition: table now has the capacity to hold newSize
   *      label entries.  If the new size is smaller than the
   *      old size, the table is truncated after the first
   *      newSize entries.
   * Returns 1 if everything went OK; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char *       ptr;               /* points to any byte in memory */
        LabelEntry * newEntryList;
        int          smaller;

        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
            return 0;           /* fatal error: table doesn't exist */

        /* create a new internal table of the specified size */
        if ((newEntryList = malloc (newSize * sizeof(LabelEntry))) == NULL)
        {
            printError ("%s", ERROR2);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        if ( table->entries )           /* if there were entries */
        {
            /* move contents of internal table to new internal table */
            smaller = table->nbrLabels < newSize ? table->nbrLabels : newSize;
            (void) memcpy (newEntryList, table->entries,
                           smaller * sizeof(LabelEntry));

            /* free the space taken up by the old internal table */
            free (table->entries);
            table->nbrLabels = smaller;
        }

        table->entries = newEntryList;
        table->capacity = newSize;
        return 1;
}

static int verifyTableExists(LabelTable * table)
 /* Returns true (1) if table exists; prints an error and returns
  * false (0) otherwise.
  */
{
        /* verify that current table exists */
        if ( ! table )
        {
            printError ("%s", ERROR0);
            return 0;
        }

        return 1;
}
/*
 * Returns true (1) if label exists in table.
 * Returns false (0) otherwise.
 */
int verifyLabelExists(LabelTable * table, char * label) {
    
    int i;
    
    // Iterate through the table
    // Return 1 IF equal to label in question
    for (i = 0; i < table->capacity; i++) {
        if ((table->entries[i].label) == label) {
            return 1;
        }
    }
    // If label cannot be found, function fails
    return 0;
}
