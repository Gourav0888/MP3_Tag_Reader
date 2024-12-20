#include "mp3view.h"
// char *tags[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "TCOM"};

Status show_mp3_file(MP3file *mp3)
{
    if(open_mp3_file_view(mp3)==m_failure)
        return m_failure;
     
    if(check_header_details(mp3)==m_failure)
        return m_failure;
 
    if(collect_mp3_content(mp3)==m_failure)
        return m_failure;

    if(print_mp3_content(mp3)==m_failure)
        return m_failure;

    return m_success;
}

Status open_mp3_file_view(MP3file *mp3)
{
    mp3->fptr_mp3_flie = fopen( mp3->mp3_fname,"r");

    if(mp3->fptr_mp3_flie==NULL)
    {
        printf("ERROR: Unable to open %s\n", mp3->mp3_fname);    
        return m_failure;
    }

    // printf("Opened successfully\n");
    return m_success;
}

Status check_header_details(MP3file *mp3)
{
    char id[4];
    fread(id, sizeof(char), 3, mp3->fptr_mp3_flie);
    id[3] = '\0';

    if(strcmp(id, "ID3"))
    {
        return m_failure;
    }

    short version;
    version = get_size_little_endian(mp3->fptr_mp3_flie, sizeof(short));  
    if(version!=768)
    {
        return m_failure;
    }

    fseek(mp3->fptr_mp3_flie, 1, SEEK_CUR);  //skip one byte for flag
    int fsize ;
    fread(&fsize, sizeof(int), 1, mp3->fptr_mp3_flie);
    mp3->mp3_fsize = fsize;
    return m_success;
}

Status collect_mp3_content(MP3file *mp3)
{
    while(mp3->tag_count!=MAX_TAG_COUNT)
    {
        char tag[5];
        int  size, tag_no;
        fread(tag, sizeof(char), 4, mp3->fptr_mp3_flie);
        tag[4] = '\0';
        size = get_size_little_endian(mp3->fptr_mp3_flie, sizeof(int)); 
        fseek(mp3->fptr_mp3_flie, 2, SEEK_CUR);  //skip 2 bytes for flags
        
        tag_no = check_tag(tag, mp3->tags);
        if(tag_no!=-1)
            mp3->tag_count++;  //if tag is available inc count
        else 
            fseek(mp3->fptr_mp3_flie, size ,SEEK_CUR);
        // printf("count = %d\n", mp3->tag_count);
        // printf("tag = %s\n", tag);
        // sleep(1);
        switch (tag_no)
        {
        case 0:
            {
                mp3->TIT2_title_name = (char*)malloc(size * sizeof(char));
                if(get_and_read_content(mp3->TIT2_title_name, mp3->fptr_mp3_flie, size)==m_failure)
                    return m_failure;
            }
            break;
        case 1:
            {
                mp3->TPE1_artist_name = (char*)malloc(size * sizeof(char));
                if(get_and_read_content(mp3->TPE1_artist_name, mp3->fptr_mp3_flie, size)==m_failure)
                    return m_failure;
            }
            break;
        case 2:
            {
                mp3->TALB_album_name = (char*)malloc(size * sizeof(char));
                if(get_and_read_content(mp3->TALB_album_name, mp3->fptr_mp3_flie, size)==m_failure)
                    return m_failure;
            }
            break;
        case 3:
            {
                mp3->TYER_year = (char*)malloc(size * sizeof(char));
                if(get_and_read_content(mp3->TYER_year, mp3->fptr_mp3_flie, size)==m_failure)
                    return m_failure;
            }
            break;
        case 4:
            {
                mp3->TCON_content_type = (char*)malloc(size * sizeof(char));
                if(get_and_read_content(mp3->TCON_content_type, mp3->fptr_mp3_flie, size)==m_failure)
                    return m_failure;
            }
            break;
        case 5:
            {
                mp3->COMM_composer = (char*)malloc(size * sizeof(char));
                if(get_and_read_content(mp3->COMM_composer, mp3->fptr_mp3_flie, size)==m_failure)
                    return m_failure;
            }
            break;
        default:
            break;
        }
        
    }
    return m_success;
}

int check_tag(char *str_tag, char **tags)
{
    for(int i=0; i<6; i++)
    {
        if(!strcmp(str_tag, tags[i]))
        {
            return i;
        }
    }
    return -1;
}

int get_size_little_endian(FILE *fptr, int data_type_size)
{
    int size = 0, i;
    char *ptr = (char*)&size;
    for(i=data_type_size-1; i>=0; i--)
    {
        fread(ptr+i, sizeof(char), 1, fptr);
    }
    return size;
}

Status get_and_read_content(char *data_buffer, FILE *fptr, int size)
{
    int  i, idx=0;
    for(i=0; i<size; i++)
    {
        char ch;
        fread(&ch, 1, 1, fptr);
        if(ch=='\0') continue;
        data_buffer[idx++] = ch;
    }
    data_buffer[idx] = '\0';
}

Status print_mp3_content(MP3file *mp3)
{
    char *lines = "-----------------------------------------------------------------------------"; 
    printf("\n%s\n%51s\n%s\n", lines, "MP3 TAG READER AND EDITER FOR ID3v2",lines);
    printf("\t\t%-10s : \t%s\n", "TITLE", mp3->TIT2_title_name);
    printf("\t\t%-10s : \t%s\n", "ARTIST", mp3->TPE1_artist_name);
    printf("\t\t%-10s : \t%s\n", "ALBUM", mp3->TALB_album_name);
    printf("\t\t%-10s : \t%s\n", "YEAR", mp3->TYER_year);
    printf("\t\t%-10s : \t%s\n", "MUSIC", mp3->TCON_content_type);
    printf("\t\t%-10s : \t%s\n", "COMMENT", mp3->COMM_composer);
    printf("%s\n\n", lines);
    return m_success;
}