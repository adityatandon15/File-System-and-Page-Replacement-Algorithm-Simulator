# File-System-and-Page-Replacement-Algorithm-Simulator
File System and Page Replacement Algorithm Simulator.    
We have used Ubuntu terminal to compile and run the code  

First--->  
-------------Simulating FIFO, LRU and LFU page replacement algorithm.---------------------  
  
The first line of the file contains two integers in this order: the number of pages  
in the reference string, and the number of page frames.  
 --> The rest of the file contains page reference string as a sequence of integers that  
are the page numbers (in virtual address space) accessed by the process in  
sequence.The simulator will simulate the behavior of the following page-replacement algorithms  
on the reference string, and report the number of page faults generated for each  
algorithm:  
FIFO  
LFU  
LRU  
The simulator should take the following command-line arguments (in this sequence):  
the name of the data file, a sequence of strings (maximum three) from the following  
sets: FF, LF, LR. The simulator simulates only the algorithms specified in the command  
line. If no algorithm is specified, all three are simulated.  
  
  
To run the code-------------------------  
Compile : g++ pageReplacement.cpp  
RUN: ./a.out input LR FF LF  
(INPUT IS A TEXT FILE,  WHICH CONTAIN NUMBER OF PAGES AND FRAMES IN FIRST LINE, AFTER THAT LINE WE HAVE STRING)  
  
  
  
Second--->  
---------------------File System in C++----------------------------------  
  
Designing a File System which makes the following  
assumptions:  
1. The File system resides on a disk that is 128 KB in size.  
2. There is only one root directory. No subdirectories are allowed.  
3. The File system supports at most 16 files.  
4. The maximum size of a file is 8 blocks where each block is 1KB in size.  
5. Each File has a unique name.  
  
                  The layout of 128 KB disk is as follows:  
  
The first 1KB block is called the super block. It stores the free block list and index  
nodes (inode) for each file.  
The remaining 127 1KB blocks store data blocks of the files on your file system.  
The exact structure of the super block is as follows:  
The first 128 bytes stores the free block list. Each entry in this list indicates  
whether the corresponding block is free or in use (if the i-th byte is 0, it indicates  
that the block is free, else it is in use). Initially all blocks except the super block  
are free.  
Immediately following the free block list are the 16 index nodes, one for each file  
that is allowed in the file system. Initially, all inodes are free. Each inode stores  
the following information:  
  
char name[8];  //file name  
int size; //file size (in number of blocks)  
int blockpointer[8]; //direct block pointers.  
int used;           //0-> inode is free, 1-> in use.  
  
Note that each inode is 56 bytes in size; Since you have 16 of these, the total size of occupied  
by the inodes is 896 bytes. The free/used block information (mentioned above) is 128 byes. So  
the total space used in the super block is 1024 bytes.  
  
Implemented the following operations for your file system.  
1. create(char name[8], int size): create a new file with this name and with these many  
blocks. (You can assume that the file size is specified at file creation time and the file  
does not grow or shrink from this point on)  
2. delete(char name[8]): delete the file with this name  
3. read(char name[8], int blockNum, char buf[1024]): read the specified block from this  
file into the specified buffer; blockNum can range from 0 to 7.  
4. write(char name[8], int blockNum, char buf[1024]): write the data in the buffer to the  
specified block in this file.  
5. ls(void): list the names of all files in the file system and their sizes.  
  
TO run the code.................  
compile : g++ fileSystem.cpp  
Run : ./a.out   

