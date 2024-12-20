#ifndef MP3_EDIT_H
#define MP3_EDIT_H

#include "common.h"
#include "mp3view.h"   //for check header details and get size little endian

/*Read and validate edit arguments */
Status read_and_validate_edit_arguments(MP3file *mp3, char *argv[]);

/*Edit mp3 file*/
Status edit_mp3_file(MP3file *mp3);

/*Open mp3 and duplicate file*/
Status open_files(MP3file *mp3);

/*check and copy header*/
Status check_and_copy_header(MP3file *mp3);

/*Get size in little endian*/    //mp3view.h

/*Compare tag and copy other data*/
Status copy_and_compare_tag(MP3file *mp3);

/*Modify text*/
// Status modify_text(MP3file *mp3, char *tag);
Status modify_text(FILE *fptr_dup, char *tag, char *text, short flags);

/*Put size in big endian*/
Status put_size_big_endian(FILE *fptr, int size);

/*Copy remaining data*/
Status copy_remaining_data(FILE *fptr_dest, FILE *fptr_src);

/*Copy dup to mp3*/
Status copy_dup_to_mp3(FILE *fptr_dest, FILE *fptr_src);
#endif