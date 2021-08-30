# iPod Player
# Nibras Faruque

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// structure of song node
typedef struct _songnode{
    char title[35];
    char artist[35];
    char album[35];
    double duration;
    struct _songnode *next;
} SongNode;

// This function is used to display playlist menu
void displayPlaylistMenu(){
    printf("Playlist Menu");
    printf("\n*************");
    printf("\n1. Print playlist");
    printf("\n2. Show duration");
    printf("\n3. Search by title");
    printf("\n4. Move a song up");
    printf("\n5. Move a song down");
    printf("\n6. Remove a song");
    printf("\n7. Go to Music Library");
    printf("\n8. Quit");
}

// This function is used to display library menu
void displayLibraryMenu(){
    printf("\nLibrary Menu");
    printf("\n************");
    printf("\n1. View all songs");
    printf("\n2. Search by title");
    printf("\n3. Add a song to playlist");
    printf("\n4. Back to playlist");
}

// This function is used to display song menu
void displaySongMenu(){
    printf("\nLibrary Menu");
    printf("\n************");
    printf("\n1. Add song to the end");
    printf("\n2. Add song at the beginning");
    printf("\n3. Insert song at a specific position");
}

// This function is used to get valid option from min to max
int getValidOption(int min,int max){
    int option=0;
    int loop=1;
    // loop until valid option is entered
    while(loop){
        // prompt and get option
        printf("\nEnter your option: ");
        scanf("%d",&option);

        // if option is valid range
        if(option >= min && option <= max){
            // set loop to 0
            loop=0;
        }
        else{
            // display invalid option
            printf("Invalid option");
        }
    }
    return option;
}

// This function is used to create empty list
SongNode *createEmptyList(){
    return NULL;
}

// This function is used to create song node with particular song details
SongNode *createSongNode(char *title, char *artist, char *album, double duration){
    // create memory for song structure
    SongNode *songNode=(SongNode *)malloc(sizeof(SongNode));

    // store details of song
    strcpy(songNode->title,title);
    strcpy(songNode->artist,artist);
    strcpy(songNode->album,album);
    songNode->duration=duration;
    songNode->next=NULL;

    // return song details
    return songNode;
}


// This function is used to insert song into specific position in the list
void insertSong(SongNode **head, SongNode *newNode, int position){
    // is head is null or position is 0
    if(*head==NULL || position==0){
        // insert new node as the head
        newNode->next=*head;
        *head=newNode;
        return;
    }
    SongNode *previousSongNode=NULL;
    SongNode *currentSongNode=*head;
    int currentPosition=0;
    // loop until correct position is reached
    while(currentSongNode!=NULL && currentPosition<position){
        previousSongNode=currentSongNode;
        currentSongNode=currentSongNode->next;
        currentPosition++;
    }
    // insert a node into list
    newNode->next=previousSongNode->next;
    previousSongNode->next=newNode;
}

// This function is used to insert song in the list in an alphabetical order
void insertSongSorted(SongNode **head, SongNode *newNode){
    // if head is null or new node data is alphabetically less than first node
    if (*head == NULL || strcmp((*head)->title, newNode->title)>0){
        // insert new node as the head
		newNode->next = *head;
		*head = newNode;
		return;
	}
	SongNode *currentSongNode = *head;
	// loop until correct position is reached
	while(currentSongNode->next != NULL && strcmp(currentSongNode->next->title, newNode->title)<0){
		currentSongNode = currentSongNode->next;
	}
    // insert a node at that position
	newNode->next = currentSongNode->next;
	currentSongNode->next = newNode;
}

// This function is used to display details of song
void printSongInfo(SongNode *song){
    // display details of song
    printf("\n%-10s %s","Title:", song->title);
    printf("\n%-10s %s","Artist:", song->artist);
    printf("\n%-10s %s","Album:", song->album);
    printf("\n%-10s %.2lf\n","Duration:", song->duration);
}

// This function is used to display list of songs in the list
void printList(SongNode *head){
    // check if the list is not empty
    if(head!=NULL){
        SongNode *currentSongNode=head;
        // loop through each node in list
        while(currentSongNode!=NULL){
            // display song information
            printSongInfo(currentSongNode);
            currentSongNode=currentSongNode->next;
        }
    }
    else{
        // display error message
        printf("\nNo songs exist");
    }
}

// This function is used to display compute total duration of all songs in list
double computeDuration(SongNode *head){
    double totalDuration=0;
    SongNode *currentSongNode=head;
    // loop through each song in the list
    while(currentSongNode!=NULL){
        // add current song duration to list
        totalDuration += currentSongNode->duration;
        currentSongNode=currentSongNode->next;
    }
    return totalDuration;
}

// This function is used to search son
SongNode *searchByTitle(SongNode *head, char *search){
    // convert search to uppercase
    for(int i=0;i<strlen(search);i++){
        search[i]=toupper(search[i]);
    }
    SongNode *currentSongNode=head;
    // loop through each song in list
    while(currentSongNode!=NULL){
        // if song title matches
        if(strcmp(currentSongNode->title,search)==0){
            // return the song node
            return currentSongNode;
        }
        currentSongNode=currentSongNode->next;
    }
    return NULL;
}


// This function is used to remove the song from list
SongNode *removeSong(SongNode **head, SongNode *remNode){
    SongNode *previousSongNode=NULL;
    SongNode *currentSongNode=*head;
    // loop for each song in the list
    while(currentSongNode!=NULL){
        // if current node matches
        if(currentSongNode==remNode){
            // remove the node from list
            if(previousSongNode==NULL){
                *head=currentSongNode->next;
            }
            else{
                previousSongNode->next=currentSongNode->next;
            }
            // return the removed node
            return remNode;
        }
        previousSongNode=currentSongNode;
        currentSongNode=currentSongNode->next;
    }
    return NULL;
}

// This function is used to free the space reserved for the song node in list
int deleteSong(SongNode **head, SongNode *delNode){
    // determine the node to be removed
    SongNode *removeNode=removeSong(head,delNode);

    // if remove node is not null
    if(removeNode !=NULL){
        // free the space of remove node
        free(removeNode);
        return 0;
    }
    return -1;
}

// This function is used to determine the position of node in the list
int getNodePosition(SongNode *head, char *search){
    // convert the search to upper case
    for(int i=0;i<strlen(search);i++){
        search[i]=toupper(search[i]);
    }
    SongNode *currentSongNode=head;
    int currentPosition=-1;
    // loop through each song in the list
    while(currentSongNode!=NULL){
        // increment current position by 1
        currentPosition++;
        // if the title matches
        if(strcmp(currentSongNode->title,search)==0){
            // return current position
            return currentPosition;
        }
        currentSongNode=currentSongNode->next;
    }
    return -1;
}

// This function is used to get number of nodes in the list
int getNumberOfNodes(SongNode **head){
    int numberOfNodes=0;
    SongNode *currentSongNode=*head;
    // loop through each song in list
    while(currentSongNode!=NULL){
        // increment number of nodes by 1
        numberOfNodes++;
        currentSongNode=currentSongNode->next;
    }
    // return number of nodes
    return numberOfNodes;
}

// This function is used to add song to playlist at the specific position
void addSongToPlayList(SongNode **musicLibrary,SongNode *foundSongNode){
    // display song menu and get valid option
    displaySongMenu();
    int songMenuOption=getValidOption(1,3);

    // switch based on the songMenuOption
    switch(songMenuOption){
        case 1:
            // insert song to end of list
            insertSong(musicLibrary,foundSongNode,getNumberOfNodes(musicLibrary)+1);
            break;
        case 2:
            // insert song at beginning
            insertSong(musicLibrary,foundSongNode,0);
            break;
        case 3:{
            int musicLibPosition=-1;
            int valid=0;
            // get valid position to insert
            while(!valid){
                printf("Enter a non-integer position: ");
                scanf("%d",&musicLibPosition);
                if(musicLibPosition>=0){
                    valid=1;
                }
            }
            // insert song at that position
            insertSong(musicLibrary,foundSongNode,musicLibPosition);
        }
            break;
    }
}

// This function is used to display music library and perform operations on it
void goToMusicLibrary(SongNode **playList, SongNode **musicLibrary){
    int musicLibraryLoop=1;
    // loop until user likes to perform operation on music library
    while(musicLibraryLoop){
        // display library menu
        displayLibraryMenu();
        // get valid option from user
        int choice=getValidOption(1,4);
        char searchTitle[35];

        // if choice is 2 or 3
        if(choice==2 || choice==3){
            // read the song title
            printf("\nEnter the song title: ");
            scanf("%*c%[^\n]%*c",searchTitle);
        }
        // switch based on user choice
        switch(choice){
            case 1:
                // display the list of songs in music library
                printf("\nList of songs in music library:");
                printList(*musicLibrary);
                break;
            case 2:{
                // search song by title in library
                SongNode *foundSongNode=searchByTitle(*musicLibrary,searchTitle);
                // if found
                if(foundSongNode!=NULL){
                    // display the song
                    printf("Matched Song:");
                    printSongInfo(foundSongNode);
                }
                else{
                    // display error message
                    printf("Song Title is not found\n");
                }
            }
                break;
            case 3:{
                // search song by title in playlist
                SongNode *foundSongNode=searchByTitle(*playList,searchTitle);
                // if found
                if(foundSongNode!=NULL){
                    // display the song
                    printf("Matched Song:");
                    printSongInfo(foundSongNode);

                    // remove song from playlist
                    foundSongNode=removeSong(playList,foundSongNode);

                    // add song to play list
                    addSongToPlayList(musicLibrary,foundSongNode);
                    printf("\nSong is inserted successfully!");
                }
                else{
                    // display error message
                    printf("Song Title is not found\n");
                }
            }
                break;
            case 4:
                // set loop to false to exit the library menu
                musicLibraryLoop=0;
                break;
        }
        printf("\n");
    }
}
int main(int argc, char *argv[])
{
    // if number of arguments is not 2
    if(argc!=2){
        // display error message
        printf("Error: Usage: ./programName inputFilename");
        return -1;
    }
    // create empty list for playlist and music library
    SongNode *playList=createEmptyList();
    SongNode *musicLibrary=createEmptyList();

    // open the file in read mode
    FILE *file=fopen(argv[1],"r");
    // if file is not found
    if (file == NULL) {
        // display error message
        printf("Error: Input file does not exist.\n");
        return -1;
    }

    char title[35];
    // loop until song details is found in file
    while(fscanf(file,"%[^\n]%*c",title)==1){
        // read artist name from file
        char artist[35];
        fscanf(file,"%[^\n]%*c",artist);

        // read album name from file
        char album[35];
        fscanf(file,"%[^\n]%*c",album);

        // read duration from file
        double duration;
        fscanf(file,"%lf%*c",&duration);

        // create song node
        SongNode *newNode=createSongNode(title, artist, album,duration);

        // insert song to play list
        insertSongSorted(&playList,newNode);
    }

    int playListMenuLoop=1;

    // loop until user wishes to exist
    while(playListMenuLoop){
        // display playlist menu and get valid option
        displayPlaylistMenu();
        int  playListMenuOption=getValidOption(1,8);

        char searchTitle[35];
        // if option is 2,4,5 or 6
        if(playListMenuOption==3 || playListMenuOption == 4 || playListMenuOption ==5 || playListMenuOption==6){
            // get the song title
            printf("\nEnter the song title: ");
            scanf("%*c%[^\n]%*c",searchTitle);
        }

        // switch based on user option
        switch(playListMenuOption){
            case 1:
                // display list of songs in playlist
                printf("\nList of songs in playlist:");
                printList(playList);
                break;
            case 2:
                // compute and display total duration of songs
                printf("\nTotal Duration: %.2f\n",computeDuration(playList));
                break;
            case 3:{
                // search song by title
                SongNode *foundSongNode=searchByTitle(playList,searchTitle);
                // if found
                if(foundSongNode!=NULL){
                    // display song information
                    printf("Matched Song:");
                    printSongInfo(foundSongNode);
                }
                else{
                    // display error message
                    printf("Song Title is not found\n");
                }
            }
                break;
            case 4:{
                // search song by title
                SongNode *foundSongNode=searchByTitle(playList,searchTitle);

                // if found
                if(foundSongNode!=NULL){
                    // get the position of song in the list
                    int previousPosition=getNodePosition(playList,searchTitle);
                    // if position is greater than 0
                    if(previousPosition>0){
                        // remove song from list
                        SongNode *removedSongNode=removeSong(&playList,searchByTitle(playList,searchTitle));
                        removedSongNode->next=NULL;
                        // insert song to specific position in list
                        insertSong(&playList,removedSongNode,previousPosition-1);
                    }
                    // display success message
                    printf("Song is moved up successfully!\n");
                }
                else{
                    // display error message
                    printf("Song Title is not found\n");
                }
            }
                break;
            case 5:{
                // search song by title
                SongNode *foundSongNode=searchByTitle(playList,searchTitle);
                if(foundSongNode!=NULL){
                    // get the position of song in the list
                    int previousPosition=getNodePosition(playList,searchTitle);
                    // remove song from list
                    SongNode *removedSongNode=removeSong(&playList,searchByTitle(playList,searchTitle));
                    removedSongNode->next=NULL;
                    // insert song to specific position in list
                    insertSong(&playList,removedSongNode,previousPosition+1);
                    // display success message
                    printf("Song is moved down successfully!\n");
                }
                else{
                    // display error message
                    printf("Song Title is not found\n");
                }
            }
                break;
            case 6:{
                // remove the song from list
                SongNode *removedSongNode=removeSong(&playList,searchByTitle(playList,searchTitle));
                // if found
                if(removedSongNode!=NULL){
                    // display removed song details
                    printf("Removed Song:");
                    printSongInfo(removedSongNode);
                }
                else{
                    // display error message
                    printf("Song Title is not found\n");
                }
            }
                break;
            case 7:
                // go to music library
                goToMusicLibrary(&playList,&musicLibrary);
                break;
            case 8:
                // set loop to 0 to exit loop
                playListMenuLoop=0;
                break;
        }
        printf("\n");
    }
    // display exit message
    printf("Application is Exiting ... \n");

    return 0;
}
