#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_QUESTIONS 10
#define OPTIONS 4
#define FILE_NAME "highscore.txt"


/* Question Structure */
struct Question
{
    char question[200];

    char options[OPTIONS][100];

    int correctAnswer;
};


/* Function declarations */
void displayRules();
void startQuiz();
void displayHighScore();
void saveHighScore(int score);
void shuffleQuestions();
void menu();


/* Question Bank */
struct Question questions[TOTAL_QUESTIONS] =
{
    {
        "Which language is known as the mother of C++?",
        {
            "A. Java",
            "B. C",
            "C. Python",
            "D. Pascal"
        },
        2
    },

    {
        "Which symbol is used to end a statement in C?",
        {
            "A. :",
            "B. .",
            "C. ;",
            "D. ,"
        },
        3
    },

    {
        "Which function is used to print output in C?",
        {
            "A. scanf()",
            "B. printf()",
            "C. print()",
            "D. output()"
        },
        2
    },

    {
        "Which data type is used to store an integer?",
        {
            "A. float",
            "B. char",
            "C. int",
            "D. double"
        },
        3
    },

    {
        "Which operator is used to get the address of a variable?",
        {
            "A. *",
            "B. &",
            "C. %",
            "D. #"
        },
        2
    },

    {
        "Which function is used for dynamic memory allocation?",
        {
            "A. malloc()",
            "B. printf()",
            "C. strlen()",
            "D. scanf()"
        },
        1
    },

    {
        "Which keyword is used to define a structure?",
        {
            "A. class",
            "B. structure",
            "C. struct",
            "D. record"
        },
        3
    },

    {
        "Which loop executes at least once?",
        {
            "A. for",
            "B. while",
            "C. do-while",
            "D. nested for"
        },
        3
    },

    {
        "Which header file is required for printf()?",
        {
            "A. stdlib.h",
            "B. string.h",
            "C. math.h",
            "D. stdio.h"
        },
        4
    },

    {
        "What is the correct extension for a C source file?",
        {
            "A. .cpp",
            "B. .java",
            "C. .c",
            "D. .py"
        },
        3
    }
};


/* Main Function */
int main()
{
    menu();

    return 0;
}


/* Menu */
void menu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          C QUIZ APPLICATION\n");
        printf("========================================\n");

        printf("1. Start Quiz\n");
        printf("2. Quiz Rules\n");
        printf("3. View High Score\n");
        printf("4. Exit\n");

        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                startQuiz();
                break;

            case 2:
                displayRules();
                break;

            case 3:
                displayHighScore();
                break;

            case 4:
                printf("\nThank you for playing!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 4);
}


/* Display Rules */
void displayRules()
{
    printf("\n========== QUIZ RULES ==========\n");

    printf("1. There are %d questions.\n",
           TOTAL_QUESTIONS);

    printf("2. Each question has 4 options.\n");

    printf("3. Select the correct option number.\n");

    printf("4. Each correct answer gives 1 mark.\n");

    printf("5. There is no negative marking.\n");

    printf("6. Your final score will be displayed.\n");

    printf("7. Highest score will be saved.\n");

    printf("================================\n");
}


/* Shuffle Questions */
void shuffleQuestions()
{
    int i;
    int randomIndex;

    struct Question temp;

    for(i = TOTAL_QUESTIONS - 1; i > 0; i--)
    {
        randomIndex = rand() % (i + 1);

        temp = questions[i];

        questions[i] = questions[randomIndex];

        questions[randomIndex] = temp;
    }
}


/* Start Quiz */
void startQuiz()
{
    int i;
    int answer;

    int score = 0;

    float percentage;

    char playerName[50];

    printf("\n========== START QUIZ ==========\n");

    printf("Enter your name: ");

    scanf(" %[^\n]", playerName);

    srand(time(NULL));

    shuffleQuestions();

    printf("\nHello %s!\n", playerName);

    printf("Let's start the quiz.\n");

    printf("\nPress Enter to continue...");

    getchar();
    getchar();


    for(i = 0; i < TOTAL_QUESTIONS; i++)
    {
        printf("\n----------------------------------------\n");

        printf("Question %d of %d\n",
               i + 1,
               TOTAL_QUESTIONS);

        printf("----------------------------------------\n");

        printf("%s\n",
               questions[i].question);

        printf("\n");

        printf("%s\n",
               questions[i].options[0]);

        printf("%s\n",
               questions[i].options[1]);

        printf("%s\n",
               questions[i].options[2]);

        printf("%s\n",
               questions[i].options[3]);

        printf("\nEnter your answer (1-4): ");

        scanf("%d", &answer);


        if(answer == questions[i].correctAnswer)
        {
            printf("\nCorrect Answer! +1\n");

            score++;
        }
        else
        {
            printf("\nWrong Answer!\n");

            printf("Correct answer: %d\n",
                   questions[i].correctAnswer);
        }
    }


    percentage =
        ((float)score / TOTAL_QUESTIONS) * 100;


    printf("\n========================================\n");
    printf("              QUIZ RESULT\n");
    printf("========================================\n");

    printf("Player Name : %s\n",
           playerName);

    printf("Total Questions : %d\n",
           TOTAL_QUESTIONS);

    printf("Correct Answers : %d\n",
           score);

    printf("Wrong Answers   : %d\n",
           TOTAL_QUESTIONS - score);

    printf("Score           : %d/%d\n",
           score,
           TOTAL_QUESTIONS);

    printf("Percentage      : %.2f%%\n",
           percentage);

    printf("========================================\n");


    if(score >= 8)
    {
        printf("Excellent Performance!\n");
    }
    else if(score >= 5)
    {
        printf("Good Performance!\n");
    }
    else
    {
        printf("Keep Practicing!\n");
    }


    saveHighScore(score);
}


/* Save High Score */
void saveHighScore(int score)
{
    FILE *fp;

    int oldScore = 0;

    fp = fopen(FILE_NAME, "r");

    if(fp != NULL)
    {
        fscanf(fp, "%d", &oldScore);

        fclose(fp);
    }


    if(score > oldScore)
    {
        fp = fopen(FILE_NAME, "w");

        if(fp == NULL)
        {
            printf("\nUnable to save high score.\n");
            return;
        }

        fprintf(fp, "%d", score);

        fclose(fp);

        printf("\nCongratulations! New High Score: %d\n",
               score);
    }
}


/* Display High Score */
void displayHighScore()
{
    FILE *fp;

    int highScore;

    fp = fopen(FILE_NAME, "r");

    if(fp == NULL)
    {
        printf("\nNo high score available yet.\n");
        return;
    }

    fscanf(fp, "%d", &highScore);

    fclose(fp);

    printf("\n========== HIGH SCORE ==========\n");

    printf("Highest Score: %d/%d\n",
           highScore,
           TOTAL_QUESTIONS);

    printf("================================\n");
}
