#include "Prototipos.h"

int main()
{
    FILE * flujo,*Voltaje,*FECHA_HORA;
    long int cant_elementos;

    flujo=fopen("HKTMST.bin","rb");

    if(!flujo)
    {
        printf("error al abrir el archivo flujo");
        return 500;
    }

    fseek(flujo,0,SEEK_END);
    cant_elementos=ftell(flujo);
    rewind(flujo);

    if(cant_elementos%4000!=0)
    {
        printf("error en tamaño del archivo");
        fclose(flujo);
        return 100;
    }

    Voltaje=fopen("Voltaje.txt","wt");

    if(!Voltaje)
    {
        printf("error al abrir archivo Voltaje");
        fclose(flujo);
        return 300;
    }

    FECHA_HORA=fopen("FECHA_HORA.txt","wt");

    if(!FECHA_HORA)
    {
        printf("error al abrir archivo FECHA_HORA");
        fclose(flujo);
        return 350;
    }

    if(comprobar_endianidad()==1)
    {
        printf("La plataforma es little endian.");
    }
    else printf("La plataforma es big endian.");

    Escribir_volt(flujo,Voltaje,cant_elementos);
    Escribir_fecha(flujo,FECHA_HORA,cant_elementos);

    fclose(FECHA_HORA);
    fclose(Voltaje);
    cambiar_puntoXcoma();
    fclose(flujo);


    return 0;
}

