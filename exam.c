Assignment name  : ft_strrev
Expected files   : ft_strrev.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that reverses (in-place) a string.

It must return its parameter.

Your function must be declared as follows:

char    *ft_strrev(char *str);

/////////////////////
Mon premier code :

char *ft_strrev(char *str)
{
	int i;
	int len;
    char    c;
	
    i = 0;
    len = 0;
	while (str[len])
		len++;
    while (str[i] && i < (length - 1) / 2)
	{
		c = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = c;
	}
	return (str);
}

int main{void}
{
    char    str[11] = "Allouetteuh";

    printf("%s\n", ft_strrev(str));
    return (0);
}

///////////////
Ensuite j ai testé ma fonction avec :
cc -Wall -Werror -Wextra ft_strrev.c && ./a.out

J ai alors eu l erreur c  n est pas initialisé
Et apres l avoir initialisé j ai eu un segfault avec l erreur "transmutation" denied si ma mémoire est bonne a la ligne : str[i] = str[len - 1 - i];

/////////////////////
Mon code final :

char *ft_strrev(char *str)
{
	int i;
	int len;
    char    c;
    char    k;
	
    i = 0;
    len = 0;
    c = '0'; // Il voulait pas prendre c = '\0'; ni NULL, J AI PAS COMPRIS
	k = '0'; // je comprends toujours pas mdr
    while (str[len])
		len++;
    while (str[i] && i < length - 1 / 2)
	{
		c = str[i];
        k = str[len - 1 - i];
		str[i] = k; 
		str[len - 1 - i] = c;
	}
	return (str);
}

// int main{void}
// {
//     char    str[11] = "Allouetteuh";

//     printf("%s\n", ft_strrev(str));
//     return (0);
// }

/////////////////////
Et la ca a marché pas de probleme de compilation, j ai essayé avec une len paire puis impaire et c est passé le grademe

Le programme d apres dont mes souvenirs sur les details peuvent m echapper, en tout cas ce qui est sure ce sont les erreurs que j ai rencontre et dont j ai mentionné sur discord et ci dessous

/////////////////////
Assignment name  : expand_str
Expected files   : expand_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./expand_str "See? It's easy to print the same thing" | cat -e
See?   It s   easy   to   print   the   same   thing$
$> ./expand_str " this        time it      will     be    more complex  " | cat -e
this   time   it   will   be   more   complex$
$> ./expand_str "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
$
$> ./expand_str "" | cat -e
$
$>

/////////////////////
Ma premiere version de code, bon je previens y a beaucoup plus simple que mon code xd je sais pas pourquoi j avais besoin d une string xd :

#include <unistd.h>

int ft_length(char *argv)
{
    int i;
    int len;

    while (argv[i])
    {
        while (argv[i] && (argv[i] == ' ' || (argv[i] >= 9 && argv[i] <= 13)))
            i++;
        while (argv[i] && (argv[i] != ' ' || (argv[i] < 9 && argv[i] > 13)))
        {
            i++;
            len++;
        }
        if (argv[i])
            len = len + 3;
    }
    return (len);
}

int main(int argc, char **argv)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;

    len = ft_length(&*argv[1]);

    char    s[len];

    s[0] = '0'; // pour les memes raisons que plus haut
    while (argv[1][i] && argc == 2)
    {
        while (argv[1][i] && (argv[1][i] == ' ' || (argv[1][i] >= 9 && argv[1][i] <= 13)))
            i++;
        if (argv[1][i] && j != 0)
        {
            j = j + 3;
            write(1, "   ", 3);
        }
        while (argv[1][i] && (argv[1][i] != ' ' || (argv[1][i] < 9 && argv[1][i] > 13)))
        {
            s[j] = argv[1][i];
            write (1, &s[j], 1);
            i++;
            j++;
        }
    }
    write(1, '\n', 1);
    return (0);
}
/////////////////////
(Il y a cette ligne que je ne sais plus si ca s écrit comme ca xd : len = ft_length(&*argv[1]); ou comme ca len = ft_length(argv[1]);
Enfin bref plus tard avec lldb la string s envoyait correctement a ft_length)

Ensuite du coup je compile et j essaye ma commande avec un exemple comme ca:
cc -Wall -Werror -Wextra expand_str.c && ./a.out "fhsduqog     dshquoiuytyfgsq      sqdouihsuiqftcggcxs     "

J ai eu une erreur de compilation qui disait que cette condition etait toujours vraie dans ft_length :
(argv[i] && (argv[i] != ' ' || (argv[i] < 9 && argv[i] > 13)))

Alors du coup je me dis ca doit etre moi avec les && ou les || ou avec = 9 ou = ' '
Je verifie 5 fois mes && et || et apres essaye toutes les combinaisons :
(argv[i] && (argv[i] != ' ' || (argv[i] < '\t' && argv[i] > '\r')))
Meme erreur
(argv[i] && (argv[i] != 32 || (argv[i] < 9 && argv[i] > 13)))
Ici j ai eu l erreur que on ne peut pas comparer un char * avec un int
Je perds patience et j essaie
(argv[i] && (argv[i] != ' ' || argv[i] != '\t' || argv[i] != '\n' || argv[i] != '\v' || argv[i] != '\f' || argv[i] != '\r'))
erreur condition toujours vraie
(argv[i] && (argv[i] != 32 || argv[i] != 9 || argv[i] != 10 || argv[i] != 11 || argv[i] != 12 || argv[i] != 13))
erreur que on ne peut pas comparer un char * avec un int

Je ne savais plus trop quoi faire alors avec ce dernier message d erreur pour rigoler j ai rajouté un int devant les argvs comme ceci :
(argv[i] && ((int)argv[i] != 32 || (int)argv[i] != 9 || (int)argv[i] != 10 || (int)argv[i] != 11 || (int)argv[i] != 12 || (int)argv[i] != 13))
Et.. c est bon plus de probleme de compilation.. j ai meme essayé du coup avec :
(argv[i] && ((int)argv[i] != 32 || ((int)argv[i] < 9 && (int)argv[i] > 13)))
Plus de probleme de compilation, je n ai pas les mots je ne comprends pas

Mais bon je décide tout de meme de continuer et je tombe sur un segfault #karma
Avec lldb comme ceci :
cc -g3 -Wall -Werror -Wextra expand_str.c && lldb ./a.out "fhsduqog     dshquoiuytyfgsq      sqdouihsuiqftcggcxs     "

Je remarque que cette boucle là ne s arrete pas
while (argv[i] && ((int)argv[i] != 32 || ((int)argv[i] < 9 && (int)argv[i] > 13)))
    {
        i++;
        len++;
    }
Je me dis y a moyen que j envoie mal la chaine
du coup avec un petit c = argv[i] comme ceci :
while (argv[i] && ((int)argv[i] != 32 || ((int)argv[i] < 9 && (int)argv[i] > 13)))
    {
        c = argv[i];
        i++;
        len++;
    }
et un petit lldb
cc -g3 -Wall -Werror -Wextra expand_str.c && lldb ./a.out "fhsduqog     dshquoiuytyfgsq      sqdouihsuiqftcggcxs     "
Je remarque que les caracteres affichés de c dans lldb sont corrects et que juste.. la boucle ne se stoppe pas d où le segfault
Bon, (argv) ne fonctionne pas,
donc j essaye avec argv[i] != '\0' => erreur de compilation je sais plus le message
j essaye argv[i] != 0 => erreur de ne peut pas comparer un char * avec un int donc...
(int)argv[i] != 0 ??? => OUI C ETAIT CA APPAREMENT

Je perds toute raison et decide de ne pas m attarder dessus parce que le temps avance du coup un petit :
cc -Wall -Werror -Wextra expand_str.c && ./a.out "fhsduqog     dshquoiuytyfgsq      sqdouihsuiqftcggcxs     "
Erreur de compilation dans main : (argv[1][i] == ' ' || (argv[1][i] >= 9 && argv[1][i] <= 13)) est toujours vraie
..
Bon on remplace tout hein ce qui donne :

#include <unistd.h>

int ft_length(char *argv)
{
    int i;
    int len;

    while (argv[i])
    {
        while ((int)argv[i] && ((int)argv[i] == 32 || ((int)argv[i] >= 9 && (int)argv[i] <= 13)))
            i++;
        while ((int)argv[i] && ((int)argv[i] != 32 || ((int)argv[i] < 9 && (int)argv[i] > 13)))
        {
            i++;
            len++;
        }
        if (argv[i])
            len = len + 3;
    }
    return (len);
}

int main(int argc, char **argv)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;

    len = ft_length(&*argv[1]);

    char    s[len];

    s[0] = '0';
    while ((int)argv[1][i] != 0 && argc == 2)
    {
        while ((int)argv[1][i] && ((int)argv[1][i] == 32 || ((int)argv[1][i] >= 9 && (int)argv[1][i] <= 13)))
            i++;
        if ((int)argv[1][i] && j != 0)
        {
            j = j + 3;
            write(1, "   ", 3);
        }
        while ((int)argv[1][i] && ((int)argv[1][i] != 32 || ((int)argv[1][i] < 9 && (int)argv[1][i] > 13)))
        {
            s[j] = argv[1][i];
            write (1, &s[j], 1);
            i++;
            j++;
        }
    }
    write(1, '\n', 1);
    return (0);
}

... je compile en y croyant pas trop :
cc -Wall -Werror -Wextra expand_str.c && ./a.out "fhsduqog     dshquoiuytyfgsq      sqdouihsuiqftcggcxs     "
dans le terminal :
   fhsduqog   dshquoiuytyfgsq   sqdouihsuiqftcggcxs

Si vraiment quelqu un sait ce qui c est passé.. expliquez moi car je deviennnnnne fooouuuuu

Alors petit disclaimer je n ai rien testé de ce que j ai ecrit au dessus MAIS je peux vous assurer que j en suis venue à ce resultat là, il restait 3 minutes
J ai essayé de faire en sorte que ca ne fasse plus les 3 espaces au debut j avais reussi mais pas fait les autres tests du sujet et push + grademe 1 min avant la fin
J ai bien evidemment fail
Merci a ceux qui ont la patience de lire ce roman d un examen qui pourtant parraissait si simple et pourtant a détruit toutes les croyances d une jeune etudiante