#include "elo.c"
#include "files.c"

int main(int argc, char *argv[])
{
    FILE *matches = fopen(argv[1], "r"); //matches.txt
    FILE *players = fopen(argv[2], "r"); //players.txt
    FILE *html = fopen(argv[3], "w"); //output.html
    
    if (matches == NULL || players == NULL)
    {
        printf("File %s or %s not found!", argv[1], argv[2]);
        
        return 1;
    }
    else if (html != NULL)
    {
        printf("The %s file was created.\n", argv[3]);
    }

    Player *allPlayers = (Player*)malloc(sizeof(Player) * 100);

    for (int i = 0; i < 100; i++)
    {
        allPlayers[i].ID = -1;
        allPlayers[i].nickname = "NoName";
        allPlayers[i].winCount = 0;
        allPlayers[i].loseCount = 0;
        allPlayers[i].matchCount = 0;
        allPlayers[i].eloRating = 1000;
    }

    match(matches, allPlayers);
    fclose(matches);

    player(players, allPlayers);
    fclose(players);

    createHTMLtable(html, allPlayers);
    fclose(html);

    free(allPlayers);

    return 0;
}