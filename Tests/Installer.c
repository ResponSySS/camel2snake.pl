#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <unistd.h>


int main (int argc, char * * argv)
{
    const char * ccp_installerTitle = "\n\nINSTALLER\n";
    int i_binReturnCode = 0;
    
    i_binReturnCode = system ("./Play");
    puts   (ccp_installerTitle);
    printf ("Juan binary returned code %d\n", i_binReturnCode);
    
    if (i_binReturnCode == EXIT_SUCCESS)
    {   puts   ("No need to install anything, it already works!");
        printf ("If you want to play, execute %s rather than %s.\n", "./Play", argv [0]);
        goto Label_Exit;
    }
    else
    {   puts ("Provided program don't work yet, we need to install it properly on your system.");
        puts ("Let's go.");
    }

    // Possible options
    const char * ccp_optClean        = "--clean";
    const char * ccp_optCleanUseless = "--clean-useless";
    const char * ccp_optDepsOnly     = "--only-deps";
    const char * ccp_optHelp         = "--help";
    const char * ccp_optHelpAdv      = "-H";
    const char * ccp_optUninstall    = "--uninstall";
    
    
    const char * ccp_workingDir = ".src/";
    char c_helpAdvanced = 0;
    
    
    if (argc == 1)
    {   fputs ("If you seek help, type:", stdout);
        printf ("    %s %s\n\n", argv [0], ccp_optHelp);
    }
    else if (strncmp ("--help", argv [1], strlen (argv [1])) == 0)
    {   goto Label_ShowUsage;
    }
    else if (strncmp ("-H", argv [1], strlen (argv [1])) == 0)
    {   c_helpAdvanced = 1;
        goto Label_ShowUsage;
    }
    
    // Installing needed packages
    if (system ("which apt-get") == 0)
    {   puts ("Using apt-get to install missing packages.");
        puts ("sudo apt-get install -y gcc make scons");
        puts ("I need your password for that.");
        system ("sudo apt-get install -y gcc make scons");
    }
    else if (system ("which yum") == 0)
    {   puts ("Using yum to install missing packages.");
        puts ("sudo yum install -y gcc make scons");
        puts ("I need your password for that.");
        system ("sudo yum install -y gcc make scons");
    }
    else
        puts ("Using yum to install missing packages.");
    
    if  (argc == 2)
    {    if (strncmp (ccp_optDepsOnly, argv [1], strlen (argv [1])) == 0)
            goto Label_Exit;
    }
    
    
    // Changing dir
    if (chdir (ccp_workingDir) == 0)
    {   printf ("In %s directory.\n", ccp_workingDir);
    }
    else
    {   printf ("Can't find the %s directory.\n", ccp_workingDir);
    }
    
    
    // Basic installation
    if (argc == 1)
    {   puts       ("scons install -Q");
        if (system ("scons install -Q") == 0)
                puts ("Successfully installed.\nTo play, execute Play.");
        goto Label_Exit;
    }
    
    
    // Reading command-line arguments
    int i; 
    for (i = 1; i < argc; i++)
    {   if (strncmp (ccp_optUninstall,          argv [i], strlen (argv [i])) == 0)
        {   puts   ("scons install --clean");
            system ("scons install --clean");
        }
        else if (strncmp (ccp_optClean,         argv [i], strlen (argv [i])) == 0)
        {   puts   ("scons --clean");
            system ("scons --clean");
        }
        else if (strncmp (ccp_optCleanUseless,  argv [i], strlen (argv [i])) == 0)
        {   puts   ("scons Juan *.o *.os --clean");
            system ("scons Juan *.o *.os --clean");
        }
	else if (strncmp (ccp_optHelp,          argv [1], strlen (argv [1])) == 0)
    	{   goto Label_ShowUsage;
    	}
    	else if (strncmp (ccp_optHelpAdv,       argv [1], strlen (argv [1])) == 0)
    	{   c_helpAdvanced = 1;
            goto Label_ShowUsage;
    	}
        else
        {   puts   ("Error:");
            printf ("%20s:  Wrong argument.\n\n", argv [i]);
            goto Label_ShowUsage;
        }
    }
    
    goto Label_Exit;
    
    Label_ShowUsage:
    puts   ("Usage:");
    printf ("%20s:  Uninstall Juan from the current folder.\n", ccp_optUninstall );
    printf ("%20s:  Show this very help.\n",                    ccp_optHelp );
    printf ("%20s:  Show advanced help.\n",                     ccp_optHelpAdv );
    if (c_helpAdvanced)
    {   puts   ("Advanced usage:");
        printf ("    %s interacts with the SConstruct file located in the .src/ directory.\n", argv [0]);
        printf ("%20s:  Remove everything created by scons from the .src/ directory.\n",         ccp_optClean );
        printf ("%20s:  Remove useless files and extra executable from the .src/ directory.\n",  ccp_optCleanUseless );
    }
    puts ("\nExamples:");
    printf ("%20s %s\n",       argv [0],  ccp_optUninstall);
    printf ("%20s %s\n",       argv [0],  ccp_optHelp);
    
    
    Label_Exit:
    puts ("See you!");
    return 0;
}
