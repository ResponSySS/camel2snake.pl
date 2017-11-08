#include <stdlib.h>
#include <stdio.h>

#include "libcsfml-sys.h"

#include "func.h"
#include "mod.h"


#define     FAT_ERR_CANT_CREATE_WINDOW              2


int main (int argc, char * argv [])
{
    puts ("WELCOME TO JUAN!\n");
    sf_render_window * window_main 
        = sfSyS_sfRenderWindowReadCmdArgs 
            ("~ Juan ~", argc, argv);
    if (! window_main)
    {   return FAT_ERR_CANT_CREATE_WINDOW;
    }
    
    char c_nextModule = 'T';
    /* 'T' for title, 'G' for game, 'R' for retry-screen */
    printf ("\nBeginning module is '%c'\n\n", c_nextModule);
    
    
    sf_event event;
    sf_input * input = sfRenderWindow_GetInput (window_main);
    
    double d_score = 0.0;
    
    /* DA GAME LOOP */
    do
    {
        //puts ("----------\n\nIN DA BEGINNING OF DA MAIN SWITCH LOOP JUAN!!!\n\n");
        // Empty sf_event buffer before next module
        while (sfRenderWindow_GetEvent (window_main, & event))     {}
        switch (c_nextModule)
        {
            case 'T':
                c_nextModule = mod_TitleT   (window_main, & event, input);
                break;
            case 'G':
                c_nextModule = mod_GameG    (window_main, & event, input, & d_score);
                break;
            case 'R':
                c_nextModule = mod_RetryR   (window_main, & event, input, d_score);
                break;
            default:
                sfRenderWindow_Close (window_main);
        }
    printf ("c_nextModule is %c\n", c_nextModule);
    } while (sfRenderWindow_IsOpened(window_main));
    
    /* Cleanup resources */
    sfRenderWindow_Destroy (window_main);
    
    
    return EXIT_SUCCESS;
}
