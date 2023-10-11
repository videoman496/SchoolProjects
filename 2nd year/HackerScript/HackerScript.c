#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINESIZE 100
#define MAX_ITEMS 50

struct foodItem {
    char name[LINESIZE];
    float price;
};

char hackerScript(char c) {
    c = tolower(c);
    switch (c) {
        case '0': return 'o';
        case '1': return 'i';
        case '2': return 'z';
        case '3': return 'e';
        case '4': return 'a';
        case '5': return 's';
        case '6': return 'b';
        case '7': return 't';
        case '8': return 'b';
        case '9': return 'q';
        default: return c;
    }
}

int naiveSearch(const char *str, const char *sub) {
    int len_str = strlen(str);
    int len_sub = strlen(sub);

    for (int i = 0; i <= len_str - len_sub; i++) {
        int matched = 1;
        for (int j = 0; j < len_sub; j++) {
            if (hackerScript(str[i + j]) != hackerScript(sub[j])) {
                matched = 0;
                break;
            }
        }
        if (matched) {
           
            return 1;
        }
    }
    
    return 0;
}

int readFoodItem(struct foodItem* item) {
    if (!fgets(item->name, LINESIZE, stdin)) return -1; 
    if (item->name[0] == '\n') return -1;
    item->name[strcspn(item->name, "\n")] = 0;

    if (scanf("%f", &item->price) != 1) return -1;
    getchar(); // Удалить оставшийся символ новой строки из ввода

    return 1;
}

int main() {
    char searchStr[LINESIZE];
    printf("Zadaj hladanu surovinu:\n");
    fgets(searchStr, LINESIZE, stdin);
    searchStr[strcspn(searchStr, "\n")] = 0;
   

    struct foodItem items[MAX_ITEMS];
    int totalItems = 0;

    printf("Zadaj jedalny listok:\n");
    
    

    
    while (totalItems < MAX_ITEMS && readFoodItem(&items[totalItems]) == 1) {
        if (naiveSearch(items[totalItems].name, searchStr)) {
            printf("%s\n%.2f\n", items[totalItems].name, items[totalItems].price);  // Отладочное сообщение
        }
        totalItems++;
    }
    printf("Nacitanych %d poloziek.\n", totalItems);
    return 0;
}
