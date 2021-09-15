#include<iostream>
#include<bits/stdc++.h>
#include<string>

using namespace std;

struct inode
{
  char name[8];
  int sizes;
  int BlockPointers[8];
  int used = 0;
};

struct Super_Block
{
  char Is_empty[128];
  struct inode Index[16];
};

struct Data_block
{
 char block[1024];
};


class Filesystem
{
   struct Super_Block super;
   struct Data_block Data[127];
   public:

   void Initialize()
   {
      for(int i=0; i<128;i++)
      {
         super.Is_empty[i]='0';
      }
   }



   void create(char name[], int sizes)
   {


      for(int i=0; i<16;i++)               // Any file with this name already exist or not
      {
        if((strcmp(name,super.Index[i].name) == 0)&&(super.Index[i].used==1))
        {
           cout<<"\n------------------------------------\n";
           cout<<name<<" file already exist, can't create another file with same name\n";
           cout<<"------------------------------------\n";
           return;
        }
      }


      int file_space = -1;
      for(int i=0;i<16;i++)                              // File system is full or not
      {
          if(super.Index[i].used==0)
          {
             file_space = i;
             break;
          }
      }


      if(file_space==-1)
      {
        cout<<"\n------------------------------------\n";
        cout<<"File system is already full, so can't create "<<name<<" file\n";
        cout<<"------------------------------------\n";
        return;
      }



      int Block_required = 0;
      for(int i=1 ;i <128 ;i++)                   // Number of required empty blocks exist or not
      {
        if(super.Is_empty[i]=='0')
        Block_required++;

       }

       if(Block_required<sizes)
       {
         cout<<"\n------------------------------------\n";
         cout<<"Number of blocks required for "<<name<<" file is higher than the number of empty blocks, so cant create this file\n";
         cout<<"------------------------------------\n";
         return;
       }

       strcpy(super.Index[file_space].name, name);         // create the file with this name;
       super.Index[file_space].sizes = sizes ;
       Block_required=0;
       int i=1;
       while(Block_required!=sizes)
       {
         if(super.Is_empty[i]=='0')
         {
             super.Is_empty[i]='1';
             super.Index[file_space].BlockPointers[Block_required]=i;
             Block_required++;
         }
          i++;
       }

        super.Index[file_space].used=1;
        cout<<"\n------------------------------------\n";
        cout<<name<<" file created succesfully \n";
        cout<<"------------------------------------\n";

   };




   void Delete(char name[])                            //Delete the file
   {
        for(int i=0; i<16;i++)               // Any file with this name already exist or not
      {
        if((strcmp(name,super.Index[i].name) == 0)&&(super.Index[i].used==1))
        {
           super.Index[i].used=0;
           for(int j=0; j<super.Index[i].sizes;j++)
           {
              super.Is_empty[super.Index[i].BlockPointers[j]]='0';
           }
           cout<<"\n------------------------------------\n";
           cout<<name<<" file deleted successfully\n";
           cout<<"------------------------------------\n";
           return;
        }
      }

      cout<<"\n------------------------------------\n";
      cout<<name<<" file doesn't exist, so unable to delete\n";
      cout<<"------------------------------------\n";
   }





   void read(char name[] , int blockNum, char buf[])                    // Read the particular block
   {

        for(int i=0; i<16;i++)
      {
        if((strcmp(name,super.Index[i].name) == 0)&&(super.Index[i].used))
        {
        
           if(blockNum>=super.Index[i].sizes) {
           cout<<"\n------------------------------------\n";
           cout<<"Block is inaccessible, number of blocks allocated is less than block number\n";
           cout<<"------------------------------------\n";
           }
           else
           {
           cout<<"\n------------------------------------\n";
           cout<<"Data read from "<<name<<" file at blockumber "<<blockNum<<" is = "<<Data[super.Index[i].BlockPointers[blockNum]].block<<endl;
           cout<<"------------------------------------\n";
           strcpy(buf, Data[super.Index[i].BlockPointers[blockNum]].block);}
           return;
        }
      }
      cout<<"\n------------------------------------\n";
      cout<<name<<" file doesn't exist, so unable to read\n";
      cout<<"------------------------------------\n";

   }


   void write(char name[], int blockNum, char buf[])
    {

          for(int i=0; i<16;i++)
      {
        if((strcmp(name,super.Index[i].name) == 0)&&(super.Index[i].used))
        {
            if(blockNum>=super.Index[i].sizes) {
              cout<<"\n------------------------------------\n";
              cout<<"Block is inaccessible, number of blocks allocated is less than block number\n";
              cout<<"------------------------------------\n";
            }
           else{
              strcpy(Data[super.Index[i].BlockPointers[blockNum]].block,buf);
              cout<<"\n------------------------------------\n";
              cout<<"Write is successfull\n";
              cout<<"------------------------------------\n";
            }
           return;
        }
      }

      cout<<"\n------------------------------------\n";
      cout<<name<<" file doesn't exist, so unable to write\n";
      cout<<"------------------------------------\n";

    }


    void Is()
    {
        cout<<"\n------------------------------------\n";
         for(int i=0;i<16;i++)
         {
            if(super.Index[i].used==1)
            {
              cout<<"File name = "<<super.Index[i].name<<"  size = "<<super.Index[i].sizes<<endl; 
            }
         }
        cout<<"------------------------------------\n";
    }


};



int main()
{
  Filesystem root;
  root.Initialize();

  int n=1;


  while(n)
  {
    cout<<"\n------------------------------------\n";
    cout<<"Press 1 for Creating a file \n";
    cout<<"Press 2 for Deleting a file \n";
    cout<<"Press 3 for reading  a file \n";
    cout<<"Press 4 for writing  a file \n";
    cout<<"Press 5 for printing all file \n";
    cout<<"Press 0 for exit \n";
    cout<<"------------------------------------\n";
    cout<<"Enter the number = ";
    cin>>n;

    if(n==1)
    {
      cout<<"Enter the name of file = ";
      char str[8];
      //cin>>str;
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      cout<<"Enter the size of file = ";
      int sizes;
      cin>>sizes;
      if(sizes>8)
      cout<<"It is not allowed to create a file of size more than 8 block\n";
      else
      root.create(str, sizes);
    }

    else if(n==2)
    {
      cout<<"Enter the name of file = ";
      char str[8];
      //cin>>str;
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      root.Delete(str);
    }

    else if(n==3)
    {
      cout<<"Enter the file name = ";
      char str[8];
      //cin>>str;
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      cout<<"Enter the block number = ";
      int block;
      cin>>block;
      char buf[1024];
      root.read(str, block , buf);
    }

    else if(n==4)
    {
      cout<<"Enter the file name = ";
      char str[8];
      //cin>>str;
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      cout<<"Enter the block number = ";
      int block;
      cin>>block;
      char buf[1024];
      cout<<"Enter what do you want to write in the file = ";
      cin.ignore(256, '\n');
      cin.getline(buf, 1024);
      root.write(str, block , buf);

    }

    else if(n==5)
    {
      root.Is();
    }

    cout<<endl;
  }

  return 0;
}
