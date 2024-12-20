// #include "common.h"
#include "mp3view.h"
#include "mp3edit.h"

int main(int argc, char *argv[])
{
    MP3file mp3 = {NULL};
    mp3.tag_count=0;
    
    mp3.tags[0] = "TIT2";
    mp3.tags[1] = "TPE1"; 
    mp3.tags[2] = "TALB";
    mp3.tags[3] = "TYER";
    mp3.tags[4] = "TCON"; 
    mp3.tags[5] = "COMM";
    
    if(argc==2)
    {
        if (check_operation_type(argv)==m_help)
        {
            printf("----------------------------HELP MENU----------------------------\n");
            printf("1. -v -> to view mp3 file contents\n2. -e -> to edit mp3 file contents\n");
            printf("\t2.1. -t -> to edit song title\n");
            printf("\t2.2. -a -> to edit artist name title\n");
            printf("\t2.3. -A -> to edit album name title\n");
            printf("\t2.4. -y -> to edit year\n");
            printf("\t2.5. -m -> to edit content\n");
            printf("\t2.6. -c -> to edit comment\n");
            printf("-----------------------------------------------------------------\n");
        }
        else
        {
            printf("ERROR: INVALID ARGUMENTS\nUSAGE:\nTo view please pass like: ./a.out -v mp3filename\n");
            printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
            printf("To get help please pass like: ./a.out --help\n");
            return 0;
        }
    }
    else if(argc==3)
    {
        if(check_operation_type(argv) == m_view)
        {
            printf("------------------------------------SELECTED VIEW DETAILS------------------------------------\n");
            if (read_and_validate_mp3_file_view(&mp3, argv) == m_success)
            {
                if (show_mp3_file(&mp3)==m_success)
                {
                    printf("-------------------------------DETAILS DISPLAYED SUCCESSFULLY--------------------------------\n");
                }
                else 
                {
                    printf("ERROR: in showing\n");
                    return 0;
                }
            }
            else 
            {
                // printf("ERROR: in reading and validating mp3 view\n");
                return 0;
            }
        }
        else
        {
            printf("ERROR: Unsupported operation\n");
            return 0;
        }
    }
    else if(argc==5)
    {
        if(check_operation_type(argv)==m_edit)
        {
            printf("------------------------------------SELECTED EDIT DETAILS------------------------------------\n");
            if(read_and_validate_edit_arguments(&mp3, argv)==m_success)
            {
                if(edit_mp3_file(&mp3)==m_success)
                {
                    printf("---------------------------------DETAILS EDITED SUCCESSFULLY---------------------------------\n\n");
                }
                else
                {
                    printf("ERROR: in editing\n");
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            printf("ERROR: Unsupported operation\n");
            return 0;
        }
    }
    else
    {
        printf("ERROR: INVALID ARGUMENTS\nUSAGE:\nTo view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("To get help please pass like: ./a.out --help\n");
    }

    /*Closing files*/
    if(mp3.fptr_mp3_flie) fclose(mp3.fptr_mp3_flie);
    if(mp3.fptr_dup_file) fclose(mp3.fptr_dup_file);

    /*Free dynamic allocated memory*/
    if(mp3.mp3_fname) free(mp3.mp3_fname);
    if(mp3.dup_fname) free(mp3.dup_fname);
    if(mp3.text) free(mp3.text);
    if(mp3.TIT2_title_name) free(mp3.TIT2_title_name);
    if(mp3.TPE1_artist_name) free(mp3.TPE1_artist_name);
    if(mp3.TALB_album_name) free(mp3.TALB_album_name);
    if(mp3.TYER_year) free(mp3.TYER_year);
    if(mp3.TCON_content_type) free(mp3.TCON_content_type);
    if(mp3.COMM_composer) free(mp3.COMM_composer);
    
    return 0;
}

Operation_type check_operation_type(char *argv[])
{
    if(!strcmp(argv[1], "-v"))
        return m_view;
    else if (!strcmp(argv[1], "-e"))
        return m_edit;
    else if (!strcmp(argv[1], "--help"))
        return m_help;
    else 
        return m_unsupported;
    return 0;
}

Status read_and_validate_mp3_file_view(MP3file *mp3, char *argv[])
{
    /* ./a.out -v mp3file
           0    1    2     */
    if(strstr(argv[2], ".mp3"))
    {
        mp3->mp3_fname = (char*)malloc(strlen(argv[2])*sizeof(char));
        strcpy(mp3->mp3_fname, argv[2]);
    }   
    else
    {
        printf("ERROR: Given file is not a mp3 file\n");
        return m_failure;
    } 

    return m_success;
}

Status read_and_validate_edit_arguments(MP3file *mp3, char *argv[])
{
    /* ./a.out -e opration changing_text mp3file
           0    1     2           3         4     */
    if(strstr(argv[4], ".mp3"))
    {
        mp3->mp3_fname = (char*)malloc(strlen(argv[2])*sizeof(char));
        strcpy(mp3->mp3_fname, argv[4]);
    }
    else
    {
        printf("ERROR: Given file is not a mp3 file\n");
        return m_failure;
    }

    /*edit operation type*/
    if(!strcmp(argv[2], "-t"))
    {
        printf("--------------------------CHANGE TITLE--------------------------\n");
        printf("\tTITLE : %s\n", argv[3]);
        mp3->tag_count = 0;
    }
    else if(!strcmp(argv[2], "-a"))
    {
        printf("--------------------------CHANGE ARTIST NAME--------------------------\n");
        printf("\tARTIST NAME : %s\n", argv[3]);
        mp3->tag_count = 1;
    } 
    else if(!strcmp(argv[2], "-A"))
    {
        printf("--------------------------CHANGE ALBUM NAME--------------------------\n");
        printf("\tALBUM NAME : %s\n", argv[3]);
        mp3->tag_count = 2;
    } 
    else if(!strcmp(argv[2], "-y"))
    {
        printf("--------------------------CHANGE YEAR--------------------------\n");
        printf("\tYEAR : %s\n", argv[3]);
        mp3->tag_count = 3;
    } 
    else if(!strcmp(argv[2], "-m"))
    {
        printf("--------------------------CHANGE CONTENT--------------------------\n");
        printf("\tCONTENT : %s\n", argv[3]);
        mp3->tag_count = 4;
    } 
    else if(!strcmp(argv[2], "-c"))
    {
        printf("--------------------------CHANGE COMMENT--------------------------\n");
        printf("\tCOMMENT : %s\n", argv[3]);
        mp3->tag_count = 5;
    } 
    else
    {
        printf("ERROR: INVALID EDIT OPTION\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        return m_failure;
    }

    mp3->text = (char*)malloc(strlen(argv[3]));
    strcpy(mp3->text, argv[3]);

    mp3->dup_fname = (char*)malloc(strlen(mp3->mp3_fname)+4);
    strcpy(mp3->dup_fname, "dup");
    strcat(mp3->dup_fname, mp3->mp3_fname);

    return m_success;
}