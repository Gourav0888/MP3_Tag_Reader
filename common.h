#ifndef COMMON_H
#define COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

// #define MAX_DATA_SIZE 100
#define MAX_TAG_COUNT 6

typedef struct MP3file
{
    char *mp3_fname;  //mp3 file name
    FILE *fptr_mp3_flie; //mp3 file pointer
    char *dup_fname; //duplicate file name
    FILE *fptr_dup_file; //duplicate file pointer
    int mp3_fsize;
    char *tags[10];
    int tag_count;    //tag count for counting in view mode 
                      //tag count for changing text tag no. in edit mode 

    char *text; //changing text
    char *TIT2_title_name;
    char *TPE1_artist_name;
    char *TALB_album_name;
    char *TYER_year;
    char *TCON_content_type;
    char *COMM_composer;

}MP3file;

typedef enum 
{
    m_view,
    m_edit,
    m_help,
    m_unsupported
}Operation_type;

typedef enum 
{
    m_success,
    m_failure
} Status;

typedef  enum
{
    t_tittle,
    a_artist,
    A_album,
    y_year,
    m_content,
    c_comment
}Edit_operation_type;

#endif