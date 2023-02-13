#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int my_size(char *str){
    int i;
    for(i = 0; str[i] != '\0'; i++){
    
    }
    return i;
}

int my_strcmp(char *str1, char *str2){
    if(my_size(str1) != my_size(str2)){
        return 0;
    }else{
        for(int i = 0; str1[i] != '\0'; i++){
            if(str1[i] != str2[i]){
                return 0;
            }
        }
    }
    return 1;
}

int is_correct(char *input){
    if(my_size(input) == 4){
        for(int i = 0; input[i] != '\0'; i++){
            if(input[i] < '0' || input[i] > '7'){
                return 0;
            }
        }
        
        for(int i = 0; i < my_size(input) -1; i++){
            for(int j = i + 1; j < my_size(input); j++){
                if(input[i] == input[j]){
                    return 0;
                }
            }
        }

    }else{
        return 0;
    }

    return 1;
}


char *my_read(int fd){
    char *str = (char*)malloc(30 * sizeof(char));
    int ind = 0;
    char c;
    while( read(fd, &c, 1) > 0){
        if(c != '\n'){
            str[ind++] = c; 
        }else{
            return str;
        }
    }

    return NULL;
}

int _index__(char *code, char n){
    for(int i = 0; code[i] != '\0'; i++){
        if(code[i] == n){
            return i;
        }
    }
    return -1;
}

char *random_(){
    
    char *code = (char*)malloc(4 * sizeof(char));
    int i = 0;
    srand(time(0));
    while(i < 4){
        char c = rand() % 8 + '0';
        if(_index__(code, c) == -1){
            code[i] = c;
            i++;
        }
    }
    
    return code;
}
int Well_placed(char* text_1, char* text_2){
    int well = 0;
    for(int i = 0; i < my_size(text_1); i++){
        if(text_1[i] == text_2[i]){
            well +=1;
        }
    }
    return well;
}
int Misplaced(char* text_1, char* text_2){
    int miss = 0;

    for(int i = 0; i < my_size(text_2); i++){
        for(int j = 0; j < my_size(text_1); j++){
            if((text_2[i] == text_1[j]) && i != j){
                miss++;
            }
        }
    }
    return miss;
}
/*-------------------------------------------------------------------------------------------------------------*/
int main(int argc,char *argv[]){
    
    int c_index = 0;
    int t_index = 0; 
    int round = 10;
    
    
    
     for(int i = 1; i < argc; i++){
        if(my_strcmp(argv[i], "-c") == 1){
            c_index = i + 1;
        }

        if(my_strcmp(argv[i], "-t") == 1){
            t_index = i + 1;
        }
    }
    
    int w, m;
    char *code;

    if(c_index > 0){
        code = argv[c_index];
    }else{
        code = random_();
    }

    if(t_index > 0){
        round = atoi(argv[t_index]);
    }

    printf("Will you find secred code?\nPlease enter a valid guess\n");
    for(int i = 0 ; i < round; i++){
        printf("---\nRound %d\n", i);
        write(1, ">" ,1);
        char *in = (char*)malloc(100);
        int correct_input;
        do{
            correct_input = 1;
            in = my_read(0);
            int f = is_correct(in);           
            if(f == 0){
                correct_input = 0;
            } 
            
            if(correct_input == 0){
                printf("Wrong input!\n");
            }
        }while(correct_input != 1);


        w = Well_placed(code, in);
        if(w == 4){
            printf("Congratz! You did it!");
            return 0;
        }else{
            m = Misplaced(code, in);
            printf("Well placed pieces: %d\n", w);
            printf("Misplaced pieces: %d\n", m);
        }
        

    }
    
}
