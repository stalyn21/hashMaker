#define random(x) (lrand48() % x)
 char line_hash[40], merkle[40], timestamp[8], nBits[1], nonce[26], nonce_val[20],pnonce[1];
 unsigned char nibble[2];

 typedef struct Transaction
 {
    char ID_user[3]; // Identificacion usuario
    char value_user[4]; //valor asignado
 }Trans_user;
Transaction Users[10];
 
 
//-------------------------------------------------------------------------------------------------------
//---------------------------           Disk access          ---------------------------------------------
//-------------------------------------------------------------------------------------------------------
void load_block_0(void)
{
    int aux;
    char strconfig[100];
    
    FILE *in_file;
    aux=0;
    
    if ((in_file = fopen ("blockchain_0.txt", "rt")) == NULL)
        printf("archivo blockchain_0 no existe \n");
    else
    {
        strcpy(plaintext,"");
        fseek(in_file, 0, SEEK_SET);
        while (fscanf(in_file, "%s \n",strconfig) !=EOF)       
        { 
            strcat(plaintext,strconfig); 
        } 
    }
    fclose (in_file);       
}

//-------------------------------------------------�
void save_block_0(void)
{
    int i;
	FILE *out_file;
    char m[1];
    
	if ((out_file = fopen ("blockchain_0.txt", "w")) == NULL)
		printf("No pudo crear archivo HASH_0.txt \n");
	else
    {
        for(i=0;i<plaintext_lenght+1;i++)
        {
            m[0] = plaintext[i];
            if(m[0] == '|') fprintf(out_file,"%c \n",m[0]);
            else fprintf(out_file,"%c",m[0]); 
       }
    }
    fclose(out_file);
}

//-------------------------------------------------�
void save_block_1(void)
{
    int i;
	FILE *out_file;
    char m[1];
    int nonce_count=0;
    int star_flag=0;
    
	if ((out_file= fopen ("blockchain_1.txt", "w")) == NULL)
		printf("No pudo crear archivo HASH_1.txt \n");
	else
    {
        for(i=0;i<plaintext_lenght+1;i++)
        {
            m[0] = plaintext[i];
            if(m[0] == '|') fprintf(out_file,"%c \n",m[0]);
            else fprintf(out_file,"%c",m[0]); 
       }
    }
    fclose(out_file);
}

//-------------------------------------------------
//          HASH_MAKER
//-------------------------------------------------
void hash_maker(void)
{ 
    int i,j;
    hash_pointer=0;
    j=0;  
    
    for(i=0;i<20;i++)
    {
       hash_out[i] = hash_frame[i]; 
    }
    
    do
    {  
        text_pointer=0;
        do 
        {
            for(hash_pointer=j;hash_pointer<20;hash_pointer=hash_pointer+2)
            {
                nibble[0]=plaintext[text_pointer];   //    captura character completo
                nib_0=nibble[0];              //   lo convierte en entero para operar e imprimir 
                nib_0=nib_0>>4;               //  deja solo 4 bits mas sinificativos
                //cout <<"  " <<nibble[0]  ;                     //   lo imprime                      
                nibble[0]=nib_0;              //   lo convierte a caracter    
                //------------------------------------------     
                nibble[1]=plaintext[text_pointer];   //   catura character completo
                nib_1=nibble[1];                     //   lo convierte en entero para imprimir 
                nib_1=nib_1 & 15;                    //   solo 4 bits menos significativos
             
                //cout << " = " <<nib_0<<"  "<<nib_1 <<endl ;               //   lo imprime 
                nibble[1]=nib_1;  
                hash_out[hash_pointer]= hash_out[hash_pointer]^nibble[0];  
                hash_out[hash_pointer+1]= hash_out[hash_pointer+1]^nibble[1];  
                text_pointer++; 
            }
        }   while(text_pointer<plaintext_lenght-22); // para no incluir el hash que se genera
        j++;
    }while(j<19);
    
    //cout<<plaintext;  // se imprime el mensaje 
    //cout<<endl; 
}
//-------------------------------------------------
void nonce_filler(void)
{
    char temp[1];
    int i=0;
    int j,k,m;
    
    for(i=0;i<plaintext_lenght-1;i++)
    {
       if( plaintext[i] == '*')break;  // * es el marcador del nonce
    }
    i++;
    k = random(20);                  //  20 posiciones posibles  dentro de nonce
    temp[0] = random(95)+32;         //  se escoge un caracter ASCII aleatorio entre 32 "space"  y 126 "~"
    plaintext[i+k] = temp[0] ;       //  se guarda como char imprimible en el nonce
    pnonce[0] = temp[0];
}
//--------------------------------------------------------------------------
//    3.58   10 exp 39      number of possible combination for the nonce
//