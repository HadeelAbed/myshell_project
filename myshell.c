#include "myshell.h"  // Include the shell header file

/* Colors for printing text in different colors */
#define ANSI_COLOR_BRIGHT_RED "\033[1m\033[31m"    // BIRGHT red color
#define ANSI_COLOR_BIRGHT_BLUE "\033[1m\033[34m"   // BIRGHT blue color
#define ANSI_COLOR_CYAN_BOLD  "\033[1m\033[36m"    // Bold cyan color
#define ANSI_COLOR_YELLOW_BOLD   "\033[1m\033[33m" // Bold yellow color
#define ANSI_COLOR_RESET  "\033[0m"                 // Reset to default color
//***********
void Command_shell_interactive(void)
{
    char *line;
    char cwd[1024];  

    while (1)
    {
    
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            
            char prompt[1100];
             snprintf(prompt, sizeof(prompt), "%s> ", cwd);
            line = readline(prompt);
        }
        else
        {
            
            line = readline("myshell> ");
        }

        if (!line)  // Ctrl+D pressed (EOF)
        {
            printf("\nExit shell.\n");
            break;
        }

        if (*line)  // If input is not empty
        {
            add_history(line);  // Save to history for arrow keys navigation
            Execute(line);      // Call your command executor
        }

        free(line);
    }
}

//***********
int main (int argc, char *argv[])
{
    char buf[MAX_BUFFER], pwd[MAX_ARGS];    // Buffers for commands and current path
    char shell_path[MAX_ARGS] = "shell=";   // Environment variable for shell path
    char readme_path[MAX_ARGS] = "readme_path="; // Environment variable for readme path
    char newpath[MAX_ARGS * 1000];           // String to modify PATH variable
    int len;                                // Variable to store length or index

    strcpy(newpath, getenv("PATH"));  // Copy current PATH environment variable
    strcat(newpath, ":");              // Add ':' to separate paths

    // If the program is NOT started as "./myshell" or "myshell"
    if (strcmp(argv[0], "./myshell") && strcmp(argv[0], "myshell"))
    {
        len = strlen(argv[0]);          // Get length of program name
        while (len && argv[0][len] != '/')  // Find last '/' in argv[0]
            len--;
        argv[0][len] = '\0';            // Remove filename, keep directory path only
        strcpy(pwd, argv[0]);           // Save directory path to pwd
        get_fullpath(pwd, argv[0]);     // Get full path (external function)
        printf("%s\n", pwd);            // Print the full path
    }
    else
        strcpy(pwd, getenv("PWD"));     // Else, get current working directory

    strcat(newpath, pwd);               // Add current directory to PATH string
    setenv("PATH", newpath, 1);        // Update PATH environment variable

    strcat(shell_path, pwd);            // Append current directory to "shell="
    strcat(shell_path, "/myshell");     // Add the shell executable name
    putenv(shell_path);                 // Add shell path to environment variables

    strcat(readme_path, pwd);           // Append current directory to "readme_path="
    strcat(readme_path, "/readme");     // Add readme file path
    putenv(readme_path);                // Add readme path to environment variables

    if (argc > 1)  // If user typed arguments after shell executable
    {
        strcpy(buf, "myshell ");        // Start building the command string
        int i;
        for (i = 1; i < argc; i++)      // Add all arguments to command string
        {
            strcat(buf, argv[i]);
            strcat(buf, "  ");
        }
        Execute(buf);                   // Execute the command (external function)
    }
    else  // If no arguments, run the interactive shell
    {
        Command_clear();                // Clear the screen (external function)
  
        // Print welcome message in cyan color
        fprintf(stderr, ANSI_COLOR_CYAN_BOLD "Welcome to Hadeel, Ruba & Doha's  simple shell!\n" ANSI_COLOR_RESET);

        // Tell user to type "help" for manual in blue color
        printf("Type ");
        printf(ANSI_COLOR_BIRGHT_BLUE "help" ANSI_COLOR_RESET);
        printf(" to view manual\n");

        // Tell user to type "exit" to quit in red color
        printf("Type ");
        printf(ANSI_COLOR_BRIGHT_RED "exit" ANSI_COLOR_RESET);
        printf(" to terminate.\n");
        // 
       printf(ANSI_COLOR_YELLOW_BOLD "Tip: You can use arrow keys to navigate command history.\n" ANSI_COLOR_RESET);

        printf(" ");
        

        //Command_shell(stdin, NULL, NULL);  // Start command shell loop (external function)
              Command_shell_interactive(); // Start shell loop

    }
    return 0;  // Exit program
}

