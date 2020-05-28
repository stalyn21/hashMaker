// Prof. Oscar chang
// April 21, 2020
// Modified by: Stalyn Chancay, Bryan Chamorro, and Jaime Astudillo
 
//Global---------------------------
char hex_number[]= "0123456789abcdef",plaintext[1000], out_text[1000], new_hash[20], hash_aux[20];
int hash_frame[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4}, hash_out[20];
int nib_0, nib_1,text_pointer,hash_pointer,temp,plaintext_lenght,zero_count,sum; 
//-----------------------------------
#include <iostream>
#include <cstring>
#include <ctime>       /* time_t, time, ctime */
#include <unistd.h> // gets(), sleep()
#include <vector>
#define randomize() srand48(getpid())

using namespace std;
using std::string;

#include "hash_lib.hpp"
//------------------------------------------
void write_hash_found_1(void) 
{
    int i,j,k,count=0, hash=1;

    for(i=0;i<20;i++)
    {
        plaintext[plaintext_lenght-22+i] = hex_number[hash_out[i]]; // to save the hash finded
        plaintext[15+i] = '0';
    }
    plaintext[6]=hex_number[count];
    plaintext[plaintext_lenght-25] = hex_number[hash];
    save_block_0();
    
    count++, hash++;
    
    for(i=0;i<20;i++)
    {
        plaintext[15+i] = hex_number[hash_out[i]];
        plaintext[plaintext_lenght-22+i] = '0';
    }
    plaintext[6]=hex_number[count];
    plaintext[plaintext_lenght-25] = hex_number[hash];
    save_block_1();
}

//-------------------------------------------
int zero_counter(void)
{
   int i=0;
   zero_count=0;
       
    if((hash_out[0]==0)&&(hash_out[1]==0)&&(hash_out[2]==0)&&(hash_out[3]==0)&&(hash_out[4]==0)) zero_count++;     
   
    if(zero_count>=1) return 1;   //    Grado de dificultad del proof of work    
             
    return 0;
}
//-------------------------------------------
void hash_loop(void)
{
    long int counter=0, proof=0;
   
    do
    {
        //system("cls");
        counter++;
        //cout<< "CONTADOR "<<counter<< endl<< endl;
        hash_maker();        
        nonce_filler();        
        if (zero_counter()==1) {
          cout<<"noce: "<<pnonce;
          cout<<"hash: ";
          for(int j=0;j<20;j++)cout << hex_number[hash_out[j]]; //  imprime hash en HEX    
          cout<<endl;
          proof++;
        }
        if(proof==3) break;
    }while(1);
}

//-------------------------------------------
int main(void)
{
    int i;
    long double t0, t1;
    load_block_0();   //read block
    std::cout << "------------------------------------------------------------------------ " << std::endl;
    std::cout << "---------------------- Brute force algorithm --------------------------- " << std::endl;
    std::cout << "------------------------------------------------------------------------ " << std::endl;
    cout<<"HASH FRAME "<<endl;
    for(i=0;i<20;i++)cout << hash_frame[i]<<" ";  //  to print the hash in digital
    std::cout<< std::endl << "------------------------------------------------------------------------ " << std::endl;
    //cout << "-------------\n";
    //cout <<plaintext << endl;   cout << "-------------\n"; 
    randomize();   
    plaintext_lenght = strlen(plaintext);
    text_pointer=0;
    //tiempo
    t0=clock();
    hash_loop();
    t1=clock();
    long double time = (t1-t0)/CLOCKS_PER_SEC;
    cout << "Run time: "<< time << " seconds " <<endl;
}

/* g++ compiler or gcc compler 
#ifndef __TURBOC__
#define randomize() srand48(getpid())
#define random(x) (lrand48() % x)
#endif
*/
