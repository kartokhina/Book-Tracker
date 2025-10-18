// Некорректная записаь в файл (saveBookToFile)(исправленно)
// Проблема с дробными числами и нельзя поставить пробел в названии или автора (исправленно)
// Дописать статистику
// Понять как просходит выгрузка из файла


#include <stdio.h>
#include <string.h>

// Структура для одной книги
struct Book{
    char name[50];
    char author[100];
    int year;  
    float grade;
};

const int MAX_BOOKS = 1000;
struct Book books[MAX_BOOKS];
int books_count;

// Выгрузка из файла
int unload_from_file(const char *filename){

    FILE *file = fopen(filename, "r");
    char *s;
    if (file == NULL) {
        printf("Файл не существует, будет создан новый.\n");
        return 1;
    }

    books_count = 0;
    
    char line[256];
    while (books_count < MAX_BOOKS && fgets(line, sizeof(line), file)) {
        // Пропускаем пустые строки
        if (strlen(line) <= 1) continue;
        
        // Парсим строку: название автор год оценка
        if (sscanf(line, "%99[^\t] %49[^\t] %d %f", 
                  books[books_count].name,
                  books[books_count].author,
                  &books[books_count].year,
                  &books[books_count].grade) == 4) {
            books_count++;
        }
    }
    fclose(file);
    return 0;
}
//Показкать меню
void show_menu(){
    printf("=== Трекер книг ===\n");
    printf("1. Добавить книгу\n");
    printf("2. Показать все книги\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");

}
//Сохранить книгу в файл
void save_book_to_file(const char *filename, struct Book b){
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Ошибка при сохранении файла!\n");
        return;
    }
    fprintf(file,  "%s\t%s\t%d\t%.1f\n", b.name, b.author, b.year, b.grade);
    fclose(file);
}
//Добавдение книги
void add_book(){
    struct Book new_book;
    
    getchar(); // Очистка буфера от предыдущего ввода

    printf("Введите название книги: ");
    fgets(new_book.name, 100, stdin);
    
    new_book.name[strcspn(new_book.name, "\n")] = 0;
    
    printf("Введите автора: ");
    fgets(new_book.author, 50, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0;
    
    printf("Год прочтения: ");
    scanf("%d", &new_book.year);


    printf("Ваша оценка (0-10): ");
    scanf("%f", &new_book.grade);

    books[books_count++] = new_book;
    save_book_to_file("books.txt", new_book);

    printf("Книга добавлена!\n \n");
   
    
    return;
}
//Показать все книги
void show_all_books(){
    if (books_count == 0){
        printf("Нет сохраненных книг. \n\n");
        return;
    }

    printf("\n=== Все книги ===\n");
    for (int i = 0; i < books_count; i++){
        printf("%d. \"%s\" - %s (%d) - Оценка: %.1f\n", 
               i+1, books[i].name, books[i].author, 
               books[i].year, books[i].grade);
    }
    printf("\n");

}
//Показать статистику
void show_statistics(){
   double sr = 0;
   double mx;
   int ind_mx;
   for (int i = 0; i < books_count; i++){
        if (books[i].grade > mx){
            mx = books[i].grade;
            ind_mx = i;
        }
        sr += books[i].grade;
   }
    sr = sr / books_count;
    printf("\n=== Статистика ===\n");
    printf("o Количество прочитанных книг: %d\n", books_count);
    printf("o Средняя оценка: %.1f\n", sr);
    printf("o Самая высоко оценённая книга: \"%s\" %s с баллом %.1f\n\n", books[ind_mx].name, books[ind_mx].author, books[ind_mx].grade);

}

int main(int argc, char const *argv[])
{

    unload_from_file("books.txt");
    int input;

    do
    {
        show_menu();
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            add_book();
            break;
        case 2:
            show_all_books();
            break;
        case 3:
            show_statistics();
            break;
        case 4:
            //Выход
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный ввод\n");
            break;
        }
    } while (input != 4);
    
   
    return 0;
}
