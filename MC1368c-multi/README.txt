﻿

									Sapienti sat 

Здесь представлена библиотека для AVR микроконтроллеров, позволяющая использовать 
LCD дисплей MC1368c-multi на чипе HT1621.
Написана она в среде AVR Studio 5.0, компилируется как наитивным gcc компилятором, так и 
win-avr.

Благодарности: 
Разработчику библиотеки под Ардуино для данного дисплея, вот ссылка на проект: http://iarduino.ru/file/234.html и камраду
sas_75 c форума vrtp.ru http://vrtp.ru/index.php?showtopic=23513
В этом README и при написании библиотеки были использованы материалы, указанные выше.
Можете почитать, интересно и полезно, подробнее раскроется способ управления дисплеем.
---------------------------------------------------------------------------
Файлы проекта:
README.txt - его вы читаете сейчас
MC1368c-multi.avrsln - файл решения (солюшн) AVR Studio 5.0
AVRGCC4\MC1368c-multi.avrgccproj - файл проекта AVR Studio 5.0

Собственно сами файлы библиотеки :
MC1368c-multi.h
MC1368c-multi.с

ADC_OUTPUT-MC1368c-multi.c  - пример использования библиотеки

-----------------------------------------------------------------------------

Что может библиотека:

Выводить число размерности int максимум, этого, думаю, достаточно.
Выводит она число в любой из трех систем счисления: двоичной, десятичной и шестнадцатеричной.

Может выводить и латинские буквы, но это сомнительное преимущество, так как читать их порой 
просто невозможно. K,X,V... Некоторые буквы просто невозможно нормально вывести на 7 сегментов.

Может, независимо от выводимой на сегменты информации, включать и выключать мнемонические символы.

В библиотеке реализован алгоритм относительной адресации ячеек регистра данных,
просто первым, после команды на запись,  передается начальный адрес выводимых данных, а потом
элементарно отправляются символы побайтно. 
 
В программе текст выводим только КАПСОМ, не стал я вводить проверку на строчные и прописные.
_____________________________________________________

О дисплее:

Модуль имеет шесть выводов:

1 - Vdd - Питание модуля (2,8 - 5 В) - самый верхний, квадратный.

2 - Vlcd - Напряжение на сегментах. Резистор между этим выводом и выводом питания задает контрастность. 
Увеличение сопротивления резистора уменьшает контрастрость. 
При питании +5В у его значение составило 47кОм без засветки незадействованных сегментов.

3 - Vss - земля

4 - Data - последовательные данные

5 - WR (запись производится по переходу из лог. 0 в 1)

6 - CS (активный низкий уровень)






