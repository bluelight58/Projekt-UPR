#include "elo.h"

void match(FILE *matches, Player *allPlayers)
{
    char buff_matches[SIZE];

    char *token;

    int count = 0;

    fscanf(matches, "%s", buff_matches);

    token = buff_matches;

    while (strcmp(token, "match") == 0)
    {   
        for (int i = 0; i < 2; i++)
        {
            fscanf(matches, "%s", buff_matches);

            token = buff_matches;

            token = strtok(token, ",");
            allPlayers[count].ID = atoi(token);

            token = strtok(NULL, ",");
            allPlayers[count + 1].ID = atoi(token);

            token = strtok(NULL, ",");
            allPlayers[count + 2].ID = atoi(token);

            fscanf(matches, "%s", buff_matches);

            int help = count;

            for (int j = 0; j < 3; j++)
            {
                if (j == 0)
                {
                    token = strtok(buff_matches, ";");
                }
                else
                {
                    token = strtok(NULL, ";");
                }
                
                allPlayers[help].K = atoi(token);

                token = strtok(NULL, ";");
                allPlayers[help].A = atoi(token);

                token = strtok(NULL, ",");
                allPlayers[help].D = atoi(token);

                allPlayers[help].KDratio = KDratio(allPlayers[help].K, allPlayers[help].D);
                allPlayers[help].KADratio = KADratio(allPlayers[help].K, allPlayers[help].A, allPlayers[help].D);

                help++;
            }

            count += 3;
        }

        fscanf(matches, "%s", buff_matches);

        token = buff_matches;

        for (int i = 0; i < count; i++)
        {
            double eloEnemyRED = (allPlayers[0].eloRating + allPlayers[1].eloRating + allPlayers[2].eloRating) / 3;
            double eloEnemyBLUE = (allPlayers[3].eloRating + allPlayers[4].eloRating + allPlayers[5].eloRating) / 3;

            if (i < 3 && strcmp(token, "red") == 0)
            {
                allPlayers[i].winCount++;
                allPlayers[i].matchCount++;
                allPlayers[i].eloRating = eloRating(allPlayers[i].eloRating, eloEnemyBLUE, 1);
                allPlayers[i].division = division(allPlayers[i].eloRating);
            }
            else if (i < 3 && strcmp(token, "blue") == 0)
            {
                allPlayers[i].loseCount++;
                allPlayers[i].matchCount++;
                allPlayers[i].eloRating = eloRating(allPlayers[i].eloRating, eloEnemyBLUE, 0);
                allPlayers[i].division = division(allPlayers[i].eloRating);
            }

            if (i > 2 && strcmp(token, "blue") == 0)
            {
                allPlayers[i].winCount++;
                allPlayers[i].matchCount++;
                allPlayers[i].eloRating = eloRating(allPlayers[i].eloRating, eloEnemyRED, 1);
                allPlayers[i].division = division(allPlayers[i].eloRating);
            }
            else if (i > 2 && strcmp(token, "red") == 0)
            {
                allPlayers[i].loseCount++;
                allPlayers[i].matchCount++;
                allPlayers[i].eloRating = eloRating(allPlayers[i].eloRating, eloEnemyRED, 0);
                allPlayers[i].division = division(allPlayers[i].eloRating);
            }
        }
    }
}

void player(FILE *players, Player *allPlayers)
{
    char buff_players[SIZE];

    char *token;
    char *piece;

    fscanf(players, "%s", buff_players);

    int countPlayers = 1;

    for (int i = 0; i < 100; i++)
    {
        if (buff_players[i] == ';')
        {
            countPlayers++;
        }
    }

    piece = strtok(buff_players, ",");

    for (int i = 0; i < countPlayers; i++)
    {
        if (i != 0)
        {
            piece = strtok(NULL, ",");
        }
        
        token = piece;
        piece = strtok(NULL, ";");

        for (int j = 0; j < 100; j++)
        {
            if (allPlayers[j].ID == atoi(token))
            {
                allPlayers[j].nickname = piece;
            }
        }
    }
}

void createHTMLtable(FILE *html, Player *allPlayers)
{
    fprintf(html, "<html>\n");
    fprintf(html, "  <head>\n");
    fprintf(html, "    <style type=\"text/css\">\n");
    fprintf(html, "      .tg {border-collapse:collapse;border-color:#9ABAD9;border-spacing:0;}\n");
    fprintf(html, "      .tg td{background-color:#EBF5FF;border-color:#9ABAD9;border-style:solid;border-width:1px;color:#444;\n");
    fprintf(html, "        font-family:Arial, sans-serif;font-size:14px;overflow:hidden;padding:10px 5px;word-break:normal;}\n");
    fprintf(html, "      .tg th{background-color:#409cff;border-color:#9ABAD9;border-style:solid;border-width:1px;color:#fff;\n");
    fprintf(html, "        font-family:Arial, sans-serif;font-size:14px;font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}\n");
    fprintf(html, "      .tg .tg-6578{border-color:#9abad9;text-align:center;vertical-align:top}\n");
    fprintf(html, "    </style>\n");
    fprintf(html, "  </head>\n");
    fprintf(html, "    <h1>League of Legends ELO rating</h1>\n");
    fprintf(html, "    <table class=\"tg\">\n");
    fprintf(html, "      <thead>\n");
    fprintf(html, "        <tr>\n");
    fprintf(html, "          <th class=\"tg-6578\">ID</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">Nickname</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">K</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">A</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">D</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">K/D ratio</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">KA/D ratio</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">Win count</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">Lose count</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">Match count</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">ELO rating</th>\n");
    fprintf(html, "          <th class=\"tg-6578\">Division</th>\n");
    fprintf(html, "        </tr>\n");
    fprintf(html, "      </thead>\n");
    fprintf(html, "      <tbody>\n");

    for (int i = 0; i < 100; i++)
    {
        if (allPlayers[i].nickname != "NoName")
        {
            fprintf(html, "        <tr>\n");
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].ID);
            fprintf(html, "          <td class=\"tg-6578\">%s</td>\n", allPlayers[i].nickname);
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].K);
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].A);
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].D);
            fprintf(html, "          <td class=\"tg-6578\">%.2f</td>\n", allPlayers[i].KDratio);
            fprintf(html, "          <td class=\"tg-6578\">%.2f</td>\n", allPlayers[i].KADratio);
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].winCount);
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].loseCount);
            fprintf(html, "          <td class=\"tg-6578\">%d</td>\n", allPlayers[i].matchCount);
            fprintf(html, "          <td class=\"tg-6578\">%.2f</td>\n", allPlayers[i].eloRating);
            fprintf(html, "          <td class=\"tg-6578\">%s</td>\n", allPlayers[i].division);
            fprintf(html, "        </tr>\n");
        }
    }

    fprintf(html, "      </tbody>\n");
    fprintf(html, "    </table>\n");
    fprintf(html, "</html>");
}