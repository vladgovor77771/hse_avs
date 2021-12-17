# Лабораторная работа 5

## Условие задачи

Вариант 19.

Задача о магазине - 2 (забывчивые покупатели). В магазине работают два отдела, каждый отдел обладает уникальным ассортиментом. В каждом отделе работает один продавец. В магазин ходят исключительно забывчивые покупатели, поэтому каждый покупатель носит с собой список товаров, которые желает купить. Покупатель приобретает товары точно в том порядке, в каком они записаны в его списке. Продавец может обслужить только одного покупателя за раз. Покупатель, вставший в очередь, засыпает пока не дойдет до продавца. Продавец засыпает, если в его отделе нет покупателей, и просыпается, если появится хотя бы один. Создать многопоточное приложение, моделирующее работу магазина.

## Модель магазина

Имеется `s = 2` пронумерованных торговца (первый, второй), каждый продает по `a` товаров.

Перед каждым торговцем имеется очередь из клиентов. Скорость обработки клиента случайна в некотором диапазоне.

Каждые `n` миллисекундсекунд (или рандомно в диапазоне) в магазин заходит клиент. У него с собой "список товаров" - множество, состоящее из чисел `k*s`, где `k` от 1 до `a`. Соответственно максимальный размер равен `a*s`.

Примем, что если клиент идет в магазин, значит 100%, что он зайдет хотя бы к одному торговцу. Значит минимальный размер "списка покупок" равен 1.

Длительность эксперимента `t` секунд.

## Мьютексы

Так как у нас очередь, нам в любом случае придется добавить какой-то thread-safety механизм. https://stackoverflow.com/questions/36762248/why-is-stdqueue-not-thread-safe

Мьютексы это очень плохо, но от них никуда не деться в такой модели.

Лочим мьютекс, когда совершаем любую операцию с очередью.

## "Спать пока не"

Можно было сделать цикл (проверка условия, сон). А можно заюзать `std::condition_variable`. В таком случае мы не дожидаемся окончания слипа и сразу начинаем делать, что нужно.

## Типы потоков

Каждый торговец - поток, обрабатывающий свою очередь. По сути, элементы очереди - это ссылки на `std::conditional_variable`, принадлежащие каждому юзеру, когда поток торговца обработал заказ (поспал случайное время), он оповещает об этом клиента.

Каждый покупатель - поток. Он решает в какую очередь встать или ждет, пока его обработают.

Поток, который создает клиентов и запускает их в магазин (main).

## Вывод программы

Клиенты-потоки пишут в лог, когда запускается эмуляция, когда встает в очередную очередь, а также когда останавливается (когда закончились продукты к покупке).

Торговцы-потоки пишут в лог, когда запускается эмуляция, после каждого обработанного клиента, а также когда завершается выполнение.

## Конфигуррование

Происходит через изменение файла `constants.h`.

Можно поменять количество торговцев, количество товаров, которые они продают, количество клиентов, а также различные слиптаймы.

## "Модель построения многопоточного приложения"

Из списка, который был в задании, модель "Клиент-Сервер" больше всего похожа на данную.

## Сборка и запуск

Быстрая команда для сборки и запуска

```bash
make && ./bin/app.out
```

## Пример вывода

Конфиг:

```cpp
static const int amount_of_sellers = 2;
static const int amount_of_clients = 5;
static const int amount_of_products = 5;
static const int sleep_from = 200;
static const int sleep_to = 400;
static const int main_sleep_seconds = 30;
```

Вывод:

```
[DEBUG] thread #139766034503488 (main): detached new seller thread #139766034499328
[DEBUG] thread #139766034499328 (seller): started emulation
[DEBUG] thread #139766034503488 (main): detached new seller thread #139765953328896
[DEBUG] thread #139766034503488 (main): created market
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765953328896 (seller): started emulation
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765944936192 (client): started emulation, need to buy 10 products
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765944936192 (client): added self to queue #1
[DEBUG] thread #139765936543488 (client): started emulation, need to buy 7 products
[DEBUG] thread #139765936543488 (client): added self to queue #1
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765936543488 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139765928150784 (client): started emulation, need to buy 5 products
[DEBUG] thread #139765928150784 (client): added self to queue #1
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765936543488 (client): added self to queue #1
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765928150784 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765936543488 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765928150784 (client): added self to queue #0
[DEBUG] thread #139765919758080 (client): started emulation, need to buy 5 products
[DEBUG] thread #139765919758080 (client): added self to queue #1
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765944936192 (client): added self to queue #0
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765919758080 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765936543488 (client): added self to queue #0
[DEBUG] thread #139765911365376 (client): started emulation, need to buy 2 products
[DEBUG] thread #139765911365376 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765928150784 (client): added self to queue #1
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765928150784 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765944936192 (client): added self to queue #1
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765919758080 (client): added self to queue #0
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765944936192 (client): added self to queue #1
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765936543488 (client): added self to queue #0
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765944936192 (client): stopped emulation
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765911365376 (client): added self to queue #1
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765928150784 (client): stopped emulation
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765911365376 (client): stopped emulation
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765919758080 (client): added self to queue #1
[DEBUG] thread #139765953328896 (seller): processed client
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139765919758080 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765936543488 (client): added self to queue #0
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139765919758080 (client): stopped emulation
[DEBUG] thread #139766034499328 (seller): processed client
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765936543488 (client): stopped emulation
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139765953328896 (seller): queue empty, waiting for clients
[DEBUG] thread #139766034499328 (seller): queue empty, waiting for clients
[DEBUG] thread #139766034503488 (main): deleting market...
[DEBUG] thread #139766034503488 (main): not all sellers stopped yet...
[DEBUG] thread #139766034503488 (main): not all sellers stopped yet...
[DEBUG] thread #139766034503488 (main): not all sellers stopped yet...
[DEBUG] thread #139765953328896 (seller): stopped emulation
[DEBUG] thread #139766034499328 (seller): stopped emulation
[DEBUG] thread #139766034503488 (main): all sellers stopped!
```
