#include <stdlib.h>
#include <stdio.h>

#include "libcsfml-sys.h"

#include "func.h"
#include "mod.h"


#define     FAT_ERR_CANT_CREATE_WINDOW              2


int main (int argc, char * argv [])
{
    puts ("WELCOME TO JUAN!\n");
    sfRenderWindow * windowMain 
        = sfSyS_sfRenderWindowReadCmdArgs 
            ("~ Juan ~", argc, argv);
    if (! windowMain)
    {   return FAT_ERR_CANT_CREATE_WINDOW;
    }
    
    char c_nextModule = 'T';
    /* 'T' for title, 'G' for game, 'R' for retry-screen */
    printf ("\nBeginning module is '%c'\n\n", c_nextModule);
    
    
    sfEvent event;
    sfInput * input = sfRenderWindow_GetInput (windowMain);
    
    double d_score = 0.0;
    
    /* DA GAME LOOP */
    do
    {
        //puts ("----------\n\nIN DA BEGINNING OF DA MAIN SWITCH LOOP JUAN!!!\n\n");
        // Empty sfEvent buffer before next module
        while (sfRenderWindow_GetEvent (windowMain, & event))     {}
        switch (c_nextModule)
        {
            case 'T':
                c_nextModule = mod_TitleT   (windowMain, & event, input);
                break;
            case 'G':
                c_nextModule = mod_GameG    (windowMain, & event, input, & d_score);
                break;
            case 'R':
                c_nextModule = mod_RetryR   (windowMain, & event, input, d_score);
                break;
            default:
                sfRenderWindow_Close (windowMain);
        }
    printf ("c_nextModule is %c\n", c_nextModule);
    } while (sfRenderWindow_IsOpened(windowMain));
    
    /* Cleanup resources */
    sfRenderWindow_Destroy (windowMain);
    
    
    return EXIT_SUCCESS;
}
