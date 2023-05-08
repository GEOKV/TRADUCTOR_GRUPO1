#include<iostream>

using namespace std;

const char *Traductor ="Traductor.dat";
	struct Palabra{
		char pal_ing[20];
		char pal_esp[20];
		char pal_info[300];
	}; 
	
void Ingresar_Palabras();
void Mostrar_Palabras();
void Actualizar_Palabras();
void Eliminar();
void traductor(string& frase, string buscar,string rempl);
void Traducir();
int main(){
	int opcion;
	do{
		system("cls");
		cout<<"INGRESE UNA OPCION"<<endl;
		cout<<" "<<endl;
		cout<<"1. INGRESAR PALABRAS "<<endl;
		cout<<"2. MOSTRAR PALABRAS "<<endl;
		cout<<"3. MODIFICAR PALABRAS"<<endl;
		cout<<"4. ELIMINAR PALABRAS"<<endl;
		cout<<"5. TRADUCIR"<<endl;
		cout<<"6. SALIR"<<endl;
		cout<<"QUE OPCION DESEAS REALIZAR: ";
		cin>>opcion;
		
		switch (opcion){
			case 1:
				Ingresar_Palabras();
				system("pause");
				break;
			case 2:
				Mostrar_Palabras();
				system("pause");
				break;
			case 3:
				Actualizar_Palabras();
				system("pause");
				break;
			case 4:
				Eliminar();
				system("pause");
				break;
			case 5:
				Traducir();
				system("pause");
				break;	
			case 6:
				system("cls");
				return 0;
			
		default:
		break;			
		}
	}while(opcion<=6 || opcion>=6);
return 0;
}	

void Ingresar_Palabras(){
	system("cls");
	
	FILE* archivo = fopen(Traductor, "a+b");
	char continuar;
	Palabra palabra;
	string pal_ing, pal_esp, pal_info;
	system("cls");
	do{
		fflush(stdin);
			
		cout<<"Ingrese palabra : ";
		cin.getline	(palabra.pal_ing,20);
         
		cout<<"Ingrese Traduccion: ";
		cin.getline	(palabra.pal_esp,20);
    	
		cout<<"Ingrese Funcionalidad: ";
		cin.getline	(palabra.pal_info,300);
				
		fwrite( &palabra, sizeof(Palabra), 1, archivo );
		
		cout<<"Desea agregar otra palabra S/N: ";
		cin>>continuar;
		}
		while((continuar=='s') || (continuar=='S'));
		
		
		fclose(archivo);
				
}
void Mostrar_Palabras(){
	system("cls");
	FILE* archivo = fopen(Traductor, "rb");
	if (!archivo){
		archivo=fopen(Traductor,"w+b");
	}
	Palabra palabra;
	int id=1;
	fread(&palabra,sizeof(Palabra),1, archivo);
	cout<<"------------------------------------DICCIONARIO-------------------------------"<<endl;
	
	do{
		cout<<"----------------PALABRA----------------"<<endl;
		cout<<"No: "<<id<<endl;
		cout<<"Palabra: "<<palabra.pal_ing<<endl;
		cout<<"Traduccion: "<<palabra.pal_esp<<endl;
		cout<<"Funcionalidad: "<<palabra.pal_info<<endl;
		
		
	fread(&palabra,sizeof(Palabra),1, archivo);
	id+=1;
	}while (feof(archivo)==0);
	fclose(archivo);
}
void Actualizar_Palabras(){
	system("cls");
	FILE* archivo = fopen(Traductor, "r+b");
		
	Palabra palabra;
	int id;
		
	cout<<"INGRESE EL No. DE LA PALABRA QUE DESEA MODIFICAR: ";
	cin>>id;
	id=id-1;
	cin.ignore();	
	fseek(archivo,id * sizeof(Palabra),SEEK_SET);
	
 		cout<<"Ingrese palabra : ";
		cin.getline(palabra.pal_ing,20);
        
        
		cout<<"Ingrese Traduccion: ";
		cin.getline(palabra.pal_esp,20);
    	

		cout<<"Ingrese Funcionalidad: ";
		cin.getline(palabra.pal_info,300);
				
		fwrite( &palabra, sizeof(Palabra), 1, archivo );
	
	fclose(archivo);
	Mostrar_Palabras();	
}
void Eliminar(){
	system ("cls");
	const char *Traductor_archivo_temp = "archivo_temp.dat";
	
	FILE* archivo_temp = fopen(Traductor_archivo_temp, "w+b");
	FILE* archivo = fopen(Traductor,"rb");
	
	Palabra palabra;
	int id=1, id_n=1;
	
	cout<<"INGRESE EL No. DE LA PALABRA QUE DESEA ELIMINAR: ";
	cin>>id;
	while(fread(&palabra,sizeof(Palabra),1,archivo)){
		if (id_n !=id){
			fwrite(&palabra,sizeof(Palabra),1,archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);
	archivo_temp = fopen(Traductor_archivo_temp,"rb");
	archivo = fopen(Traductor,"wb");
	while(fread(&palabra,sizeof(Palabra),1,archivo_temp)){
		fwrite(&palabra,sizeof(Palabra),1,archivo);
	}
	fclose(archivo);
	fclose(archivo_temp);
	Mostrar_Palabras();
}
void traductor(string& frase, string buscar,string rempl){
	int pos= frase.find(buscar);
	while (pos != -1){
		frase.replace(pos,buscar.size(),rempl);
		pos = frase.find(buscar, pos + rempl.size());
	}
}
void Traducir(){
	system("cls");
	
	FILE* archivo = fopen(Traductor, "rb");
	string frase;
	Palabra palabra;
	cout<<"_________________________________________________________________"<<endl;
	cout<<"           Ingrese codigo que desea traducir        "<<endl;
	cout<<"_________________________________________________________________"<<endl;
	cout<<"  Para traducir el codigo debe colocar '#' al final del codigo"<<endl;
	getline(cin,frase,'#');	
	fread(&palabra,sizeof(Palabra),1,archivo);	
	do{
		
		traductor(frase, palabra.pal_ing, palabra.pal_esp);
		fread ( &palabra, sizeof(Palabra), 1, archivo );
	} while (feof( archivo ) == 0);
	cout<<"\n\n        CODIGO TRADUCIDO        "<<endl;
	cout<<"------------------------------------"<<endl;
	
	cout<<frase<<endl;
	fclose(archivo);
	
}






