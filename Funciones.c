#include "Prototipos.h"

int comprobar_endianidad(void)
{
    unsigned int x=1;
    char *c=(char*)&x;
    return (int)*c;
}

int Escribir_volt(FILE *flujo,FILE *Voltaje, long int cant_elementos)
{
    long int cant_actual;
    int16_t raw;
    float procesado_raw;

    fseek(flujo,1604,SEEK_SET);
    fseek(flujo,750,SEEK_CUR);

    while(!feof(flujo))
    {

        cant_actual=ftell(flujo);
        if(fread(&raw,2,1,flujo)==1)
        {
            raw=
                ((raw & 0x00FF) << 8)|
                ((raw & 0xFF00) >> 8); // Pasaje de big a little

            procesado_raw=(float)(raw*0.01873128+(-38.682956));
            fprintf(Voltaje,"%f\n",procesado_raw);

            if((cant_elementos-cant_actual)<=1646)//4000-1604-750 es la cantidad min de bytes que deben quedar por leer en el archivo
                break;
            else
            {
                fseek(flujo,3998,SEEK_CUR);
            }
        }
        else
        {
            printf("error al escribir elemento");
            return 120;
        }
    }
    return 0;
}

int Escribir_fecha(FILE *flujo,FILE *FECHA_HORA,long int cant_elementos)
{
    time_t segundos;
    long int cant_actual;
    fseek(flujo,8,SEEK_SET);
    fseek(flujo,92,SEEK_CUR);

    while(!feof(flujo))
    {
        cant_actual=ftell(flujo);
        if(fread(&segundos,4,1,flujo)==1)
        {
            segundos=
                ((segundos & 0x000000FF) << 24)|
                ((segundos & 0x0000FF00) << 8)|
                ((segundos & 0x00FF0000) >> 8)|
                ((segundos & 0xFF000000) >> 24);
            struct tm*fecha_hora_struct=gmtime(&segundos);

            fprintf(FECHA_HORA,"%04d-%02d-%02d %02d:%02d:%02d\n",
                    fecha_hora_struct->tm_year + 1910,  // Año (se suma 1910)
                    fecha_hora_struct->tm_mon + 1,      // Mes (se suma 1)
                    fecha_hora_struct->tm_mday + 6,         // Día
                    fecha_hora_struct->tm_hour,         // Hora
                    fecha_hora_struct->tm_min,          // Minutos
                    fecha_hora_struct->tm_sec);         // Segundos

            if((cant_elementos-cant_actual)<=3900)//4000-92-8 es la cantidad min de bytes que deben quedar por leer en el archivo
                break;
            else
            {
                fseek(flujo,3996,SEEK_CUR);
            }
        }
        else
        {
            printf("error al escribir elemento");
            return 120;
        }
    }
    return 0;
}

int cambiar_puntoXcoma()
{
    FILE *Voltaje;
    int caracter;

    Voltaje=fopen("Voltaje.txt","r+");
    if(!Voltaje)
    {
        printf("error al abrir el archivo Voltaje");
        return 550;
    }


    while((caracter=fgetc(Voltaje))!=EOF)//reemplaza los puntos en el archivo por una coma para que lo leea bien en excel
    {
        if(caracter=='.')
        {
            fseek(Voltaje,-1,SEEK_CUR);
            fputc(',',Voltaje);
            fflush(Voltaje);
        }
    }
    return 0;
}
