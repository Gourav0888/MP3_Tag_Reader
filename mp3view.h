#ifndef MP3_VIEW_H
#define MP3_VIEW_H

#include "common.h"

/*Check Operation type*/
Operation_type check_operation_type(char *argv[]);
 
/*Read and validate mp3 file*/
Status read_and_validate_mp3_file_view(MP3file *mp3, char *argv[]);

/*Show mp3 file*/
Status show_mp3_file(MP3file *mp3);

/*Open mp3 file*/
Status open_mp3_file_view(MP3file *mp3);

/*Check header details*/
Status check_header_details(MP3file *mp3);

/*Get content from mp3 file*/
Status collect_mp3_content(MP3file *mp3);

/*Check  tag*/
int check_tag(char *str_tag, char **tags);

/*Get size in little endian format*/
int get_size_little_endian(FILE *fptr, int data_type_size);

/*Read content*/
Status get_and_read_content(char *data_buffer, FILE *fptr, int size);

/*Print mp3 content*/
Status print_mp3_content(MP3file *mp3);

#endif