#include <stdio.h>
#include <stdbool.h>
#define STR_LENGTH 32

void hash(char *password) {
    int i = 0;
    do {
        password[i] += i + 1;
        i++;
    } while(password[i] != '\0');
}

bool strCompare(char *a, char *b) {
    for(int i = 0; i < STR_LENGTH; i++) {
        if(a[i] != b[i]) return false;
        if(a[i] == '\0') return true;
    }
    return false;
}

bool login() {
    char name[STR_LENGTH];
    char password[STR_LENGTH];
    printf("\nName: ");
    fflush(stdin);
    scanf("%s", name);
    printf("Password: ");
    fflush(stdin);
    scanf("%s", password);
    hash(password);
    FILE *file = fopen("database.txt", "r");
    if(!file) return false;
    char currentName[STR_LENGTH];
    char currentPassword[STR_LENGTH];
    while(fscanf(file, "%s %s", currentName, currentPassword) != EOF)
        if(strCompare(name, currentName)) {
            fclose(file);
            return strCompare(password, currentPassword);
        }
    fclose(file);
    return false;
}

bool signup() {
    char name[STR_LENGTH];
    char password[STR_LENGTH];
    char passwordConf[STR_LENGTH];

    FILE *file = fopen("database.txt", "a+");
    if(!file) return false;
    
    printf("Tell us your Name: ");
    fflush(stdin);
    scanf("%s", name);

    char currentName[STR_LENGTH];
    while(fscanf(file, "%s", currentName) != EOF)
        if(strCompare(name, currentName)) {
            printf("There's already an user with that name.\n");
            return false;
        }

    do{        
        printf("Choose your Password: ");
        fflush(stdin);
        scanf("%s", password);
        printf("Confirm your password: ");
        fflush(stdin);
        scanf("%s", passwordConf);
        if(!strCompare(password, passwordConf)) printf("Passwords don't match.\n");
    } while(!strCompare(password, passwordConf));
            
    fputs(name, file);
    fputs(" ", file);
    hash(password);
    fputs(password, file);
    fputs("\n", file);
    fclose(file);
    return true;
}

int main() {
    unsigned int options;
    do {
        printf("\nHello!\nPlease, choose an option:\n1] Log-in\n2] Sign-up\n\n");
        fflush(stdin);
        scanf("%u", &options);
        options--;
    } while(options > 1);
    switch(options) {
        case 0:
            if(login()) printf("\nLogged-in!\n");
            else printf("\nLog-in failed\n");
            break;
        case 1:
            if(signup()) printf("\nRegistred!\n");
            else printf("\nRegistration failed!\n");
            break;
    }
}