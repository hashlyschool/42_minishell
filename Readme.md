# Краткое описание проекта #

В данном репозитории содержится реализация простой оболочки для unix систем, которая похожа на bash курильщика

# Содержание #
* docs				- директория содержит файлы, которые описывают задание, а также ссылки на полезные материалы по теме и т.п.
* project			- директория содержит исходные коды и утилиты для сборки проекта
* .vscode			- директория содержит некоторые конфигурационные файлы для разработки в VSCode
* .gitignore		- это файл, который содержит названия неотслеживаемых файлов
* .gitsubmodules	- это файл, который содержит информацию о submodules

# Сборка и запуск программы #
```
$git clone --recurse-submodules <URL> <NAME DIR>
$cd <NAME DIR>/project && make && ./minishell
```

# Основной функционал #

> ...Пока его нет...

# External functs #

<details>
	<summary>Click to expand </summary>

| Function | Description |
| --- | --- |
| **readline** | [char *readline(const char *prompt); readline returns the text of the line read.  A blank line returns the empty string.  If EOF is encountered while reading a line, and the line is empty, NULL is returned.  If an EOF is read with a non-empty line, it is treated as a newline.](https://man7.org/linux/man-pages/man3/readline.3.html "readline возвращает текст считанной строки. Пустая строка возвращает пустое значение. Если при чтении строки встречается EOF, а строка пуста, возвращается NULL. Если EOF читается с непустой строкой, он обрабатывается как новая строка.")|
| **rl_clear_history** | [Function: void rl_clear_history (void); Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.](https://tiswww.case.edu/php/chet/readline/readline.html "Очистите список истории, удалив все записи таким же образом, как функция clear_history() из библиотеки History. Это отличается от clear_history тем, что освобождает личные данные, сохраненные Readline в списке истории.")|
| **rl_on_new_line** | [Function: int rl_on_new_line (void); Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.](https://tiswww.case.edu/php/chet/readline/readline.html#IDX357 "Сообщите функциям обновления, что мы переместились на новую (пустую) строку, как правило, после вывода новой строки.") |
| **rl_replace_line** | [Function: void rl_replace_line (const char *text, int clear_undo); Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.](https://tiswww.case.edu/php/chet/readline/readline.html#IDX357 "Замените содержимое rl_line_buffer текстом. Точка и отметка сохраняются, если это возможно. Если значение clear_undo не равно нулю, список отмены, связанный с текущей строкой, очищается.") |
| **rl_redisplay** | [Function: void rl_redisplay(void); Change what's displayed on the screen to reflect the current contents of rl_line_buffer.](https://tiswww.case.edu/php/chet/readline/readline.html#IDX357 "Измените то, что отображается на экране, чтобы отразить текущее содержимое rl_line_buffer.") |
| **add_history** | [The add_history calls go further: they add every command typed into the history buffer. With this done, we can now scroll through command history with up/down arrows, and even do history seaches with Ctrl+R.](https://tiswww.case.edu/php/chet/readline/readline.html#IDX357  "Вызов add_history добавлят каждую набранную команду в буфер истории. Теперь мы можем прокручивать историю команд с помощью стрелок вверх/вниз и даже выполнять поиск в истории с помощью Ctrl+R.") |
| **printf** | [The functions in the printf() family produce output according to a format as described to link. ](https://www.opennet.ru/man.shtml?topic=printf&category=3&russian=2 " Функции семейства printf() производят вывод в соответствии с форматом, описанным по ссылке.") |
| **malloc** | [The malloc() function allocates size bytes and returns a pointer to the allocated memory.](https://www.opennet.ru/man.shtml?topic=malloc&russian=2&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man "malloc () выделяет size байт и возвращает указатель на выделенную память. ") |
| **write** | ("") |
| **access** | [int access(const char *pathname, int mode); access() checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.](https://translate.google.com/?hl=ru&sl=en&tl=ru&text=access()%20checks%20whether%20the%20calling%20process%20can%20access%20the%20file%20pathname.%20If%20pathname%20is%20a%20symbolic%20link%2C%20it%20is%20dereferenced.&op=translate "access() проверяет, может ли вызывающий процесс получить доступ к файлу pathname. Если pathname является символической ссылкой, она разыменовывается.") |
| **open** | :smirk: |
| **read**| :smirk: |
| **fork** | :smirk: |
| **wait** | :smirk: |
| **waitpid** | :smirk: |
| **wait3** | [The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage.](https://www.opennet.ru/man.shtml?topic=wait3&russian=2&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man "Системные вызовы wait3() и wait4() похожи на waitpid(2), но дополнительно возвращают информацию об использовании ресурсов для дочернего элемента в структуре, на которую указывает rusage.") |
| **wait4** | [The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage.](https://www.opennet.ru/man.shtml?topic=wait3&russian=2&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man "Системные вызовы wait3() и wait4() похожи на waitpid, но дополнительно возвращают информацию об использовании ресурсов для дочернего элемента в структуре, на которую указывает rusage.") |
| **signal** | :smirk: |
| **sigaction** | :smirk: |
| **kill** | :smirk: |
| **exit** | :smirk: |
| **getcwd** | [char *getcwd(char *buf, size_t size); These functions return a null-terminated string containing an absolute pathname that is the current working directory of the calling process. ](https://www.opennet.ru/man.shtml?topic=getcwd&russian=2&category=&submit=%F0%CF%CB%C1%DA%C1%D4%D8+man "Эти функции возвращают строку с завершающим нулем, содержащую абсолютный путь, который является текущим рабочим каталогом вызывающего процесса.")  |
| **chdir** | :smirk: |
| **stat** | [int stat(const char *path, struct stat *buf); These functions return information about a file.](https://www.opennet.ru/man.shtml?topic=stat&category=2&russian=2 "Эти функции возвращают информацию о файле.") |
| **** | :smirk: |
| **** | :smirk: |
| **** | :smirk: |


</details>

:shell:
