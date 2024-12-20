# MP3 Tag Reader
This project implements an MP3 Tag Reader and Editor in C. It allows you to view and edit metadata (tags) of MP3 files, such as the song title, artist name, album name, year, comments, and more.

# Features
View MP3 File Contents: Use the -v option to display the tags of the MP3 file (ID3v2.3 format only).
Edit MP3 File Tags: Use the -e option followed by additional options to edit specific tags:
-t: Edit song title
-a: Edit artist name
-A: Edit album name
-y: Edit year
-m: Edit the content
-c: Edit comments

# Usage
To view please pass like: ./a.out -v mp3filename
To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename
To get help please pass like: ./a.out --help

Feel free to replace ./a.out with your actual executable name if needed, and update any other details as required!
