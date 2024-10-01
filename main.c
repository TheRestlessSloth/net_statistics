#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TOMILLISECS(x) x*1000
#define TOUSECS(x) TOMILLISECS(x)*1000

typedef struct ICMP{
    int size;
    int addr;
    int mes_type;
    int ttl;
    double latency;
    time_t datetime;
}icmp_t;

/***
 * @brief Функция вывода параметров пакета
 * @param[in] пакет
 ***/
void print_packet(icmp_t pack){
    printf("%d bytes from %d:\tmes_type=%d\tttl=%d\ttime=%3.1f\tus\tdatetime=%s", pack.size, pack.addr, pack.mes_type, pack.ttl, pack.latency,ctime(&(pack.datetime)));
}

/***
 * @brief Функция вывода статистики
 * Функция выполняет базовый расчёт и вывод статистики, касаемо пришедших пакетов
 * (когда пришло, сколько правильно пришло, сколько нет, в процентном соотношении, средняя задержка)
 * @param[in] массив пришедших пакетов
 ***/
 void print_packet_stats(icmp_t packets[10]){
    int success = 0, miss = 0, sum_latency = 0;
    for(int i = 0; i<10; i++){
        success += packets[i].mes_type;
        miss += !packets[i].mes_type;
        sum_latency += packets[i].latency;
    }
    printf("PACKETS STATISTICS on %ssuccessful:\t\t%d\tpacks\nmiss:\t\t\t%d\tpacks\npacket_throughput:\t%0.1f\t'/. \navg_latency:\t\t%0.1f\tus\n",ctime(&(packets[0].datetime)), success, miss, success/10.0*100, sum_latency/10.0);
}

int main(){
    srand(time(NULL));   //СИД
    icmp_t icmp[10];
    
    //Временная метка (дата)
    time_t current_time = time(NULL);
    
    //Тики таймера
    clock_t past_clk = 0;
    clock_t current_clk = clock();
    
    for(int i=0; i<10; i++){
        past_clk = current_clk;
        current_clk = clock();
        //Определение структур (@todo сделать тоже самое для модемов)
        icmp[i] = (icmp_t){
            .size=64, //размер пакета
            .addr=199, //адрес
            .mes_type=rand()%2, //пришло-не пришло
            .ttl=i, //time-to-live
            .latency=TOUSECS((double)(current_clk-past_clk)/CLOCKS_PER_SEC),//задержка
            .datetime=current_time //временной штамп(дата)
        };
        print_packet(icmp[i]);
    }
    print_packet_stats(icmp);
    system("pause");
    return 0;
}
