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
       
    if(hash_out[0]==0) zero_count++;  
   
     for(i=1;i<20;i++)
     {
      if((hash_out[i-1]==0)&&(hash_out[i]==0 )) zero_count++;
      else break;      
     }
    cout << "-zeros_counter-----"<<zero_count <<endl;      
   
    if(zero_count>=2)    //    Grado de dificultad del proof of work
            {
             write_hash_found_1();   
             cout << "-Proof of work found ! -----" <<endl;      
             sleep (5);  
             return 1;
            }
    return 0;
}
//-------------------------------------------
void hash_loop(void)
{
    long int counter=0;
   
    do
    {
        system("cls");
        counter++;
        cout<< "CONTADOR "<<counter<< endl<< endl;
        hash_maker();        
        nonce_filler();        
        if (zero_counter()==1) break;
    }while(1);
    sleep(1);
}

//-------------------------------------------
int main(void)
{
    int i;
    load_block_0();   //read block
    
    cout<<"HASH FRAME "<<endl;
    for(i=0;i<20;i++)cout << hash_frame[i]<<" ";  //  to print the hash in digital
    cout << endl;
    cout << "-------------\n";
    cout <<plaintext << endl;   cout << "-------------\n"; 
  
    randomize();   
    plaintext_lenght = strlen(plaintext);
    text_pointer=0;
    hash_loop();
}

/* g++ compiler or gcc compler 
#ifndef __TURBOC__
#define randomize() srand48(getpid())
#define random(x) (lrand48() % x)
#endif
*/
