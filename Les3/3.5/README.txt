Задание 3.5 (1 балл). Изменить программу из п. 3.4 так, чтобы она игнорировала сигнал SIGINT и SIGQUIT, если в это время идет работа с файлом.
Программа считывает сигналы и передает их в листенер в случае если файл закрыт, тогда при вызове сигналов 2 и 3, будет выведенно сообщение, если же файл открыт, то сигналы проигнорируются.
