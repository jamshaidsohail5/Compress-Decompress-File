//Libraries to be used.

#include<iostream>//Used for basic input/output.
#include<cmath>//Used for ceiling function.
#include<fstream>//Used for file Handling.
#include<string>//Used for string copy function.
#include<math.h>//Used for calculating log function.
#include<Windows.h>//Used for adding colours in the program.

//Functions to be used.
//Function prototypes.


void copy_file_characters (char arr[], char*argv[]);//This function copy the charcters contained in the file into a character array.
void deleting_repitition(char arr[],int total_no_of_characters_in_file,char *argv[]);//This function deletes the repetition in the array.
int  calculating_unique_letters(char arr[]);//This function calculates the number of unique letters in the array.
double calculating_no_of_bits(double lenght);//This function calculates the number of bits in the array. 
void displaying_binary(int no_of_letters_in_original_file,char arr[],int lenght,int bits_calculated,int size_of_dynamic_array,char *argv[]);//This function displays the binary on the screen .
int  calculating_size_of_dynamic_array_named_stream(int bits,int total_no_of_characters_in_file);
void  packbits(char str[],int lenght_of_dynamic_array);
void creating_hidden_info_cmp_file(int bits,int no_of_letters_in_original_file,char array_containing_unique_letters[]);




using namespace std;



//This is the main for decomression.
/*int main(int argc,char *argv[])
{

}*/




//This is the main for compression.
int main(int argc,char *argv[])//This is the main.Inside the main brackets i have written the command line arguments.
{
	if(argc!=2)
	{
		cout << "Usage: " << argv[0] << " input_file_name.txt" << endl;
		system("pause");
		return 0;
	}
	char arr[100000];
	copy_file_characters(arr,argv);//In this function i will copy the characters that are contained in file.


	char temparr[100000]={'\0'};
	strcpy(temparr,arr);//using the string copy function.
	int lenght=0;
	lenght=strlen(arr);

	
	deleting_repitition(arr,lenght,argv);//In this function the characters which are repeated will be deleted.
	system("pause");
	return 0;

}
void copy_file_characters (char arr[], char*argv[])

{
	ifstream fin;
	fin.open(argv[1]);//opens the file for getting input
	{
		fin.getline(arr,100000,'\n');
	}
	fin.close();
}
void deleting_repitition(char arr[],int total_no_of_characters_in_file,char *argv[])
{
	//deletes the repeated letters.

	int k=0;
	for(int i=0;arr[i]!='\0';i++)
	{
		for(int j=i+1;arr[j]!='\0';j++)
		{
			if(arr[i]==arr[j])
			{
				for(int k=j;arr[k]!='\0';k++)
					arr[k]=arr[k+1];
				j--;
			}
		}
	}
	int no_of_unique_letters=calculating_unique_letters(arr);
	double bits=calculating_no_of_bits(no_of_unique_letters);
	int size=calculating_size_of_dynamic_array_named_stream(bits,total_no_of_characters_in_file);
	displaying_binary(total_no_of_characters_in_file,arr,no_of_unique_letters,bits,size,argv);
	cout<<endl<<endl;
}
int calculating_unique_letters(char arr[])
{
	int count=0;
	for(int i=0;arr[i]!='\0';i++)
	{
		{
			count++;
		}
	}
	return count;
}
double calculating_no_of_bits(double lenght)
{
	double logsaved=0;
	double ceiling=0;
	logsaved=log10(lenght)/log10(2);//This expression is equal to log2.
	ceiling=ceil(logsaved);//This function rounds the floating point number to the number to the nearest decimal number which is greater than the floating number.
	return ceiling;
}
void displaying_binary(int no_of_letters_in_original_file,char arr[],int lenght,int bits_calculated,int size_of_dynamic_array,char *argv[])
{
	creating_hidden_info_cmp_file(bits_calculated,no_of_letters_in_original_file,arr);
	char *stream_array_pointer=NULL;
	stream_array_pointer=new char[size_of_dynamic_array];

	char temp='\0';
	char temparr[1000]={'\0'};
	ifstream fin;
	fin.open(argv[1]);
	int a = 0;
	while(!fin.eof())
	{
		fin.getline(temparr,1000,'\n');
		for(int j=0;temparr[j]!='\0';j++)
		{
			for(int i=0;arr[i]!='\0';i++)
			{
				if(arr[i]==temparr[j])
				{
					for(int k=bits_calculated-1;k>=0;k--)
					{
						temp=((i>>k)%2);
						if(temp==1)
						{

							stream_array_pointer[a++]='1';

						}
						else 
						{
							stream_array_pointer[a++]='0';

						}
					}
				}
			}
		}
	}

	stream_array_pointer[a]  = '\0';
	for(int i=0;stream_array_pointer[i]!='\0';i++)
		cout<<stream_array_pointer[i];
	packbits(stream_array_pointer,size_of_dynamic_array);	

}
void packbits(char str[],int lenght_of_dynamic_array)

{

	
	int size_of_compressed_stream_array=ceil(lenght_of_dynamic_array/8);
	unsigned char *compressed_stream_array_pointer=NULL;
	compressed_stream_array_pointer=new unsigned char[size_of_compressed_stream_array];
	for(int i=0;i<size_of_compressed_stream_array;i++)
		compressed_stream_array_pointer[i]=0x00;
	unsigned char mask = 0x80;
	int temp = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{   
		if (str[i] == '1')
		{
			compressed_stream_array_pointer[temp] = compressed_stream_array_pointer[temp] | mask;
		}	
		if (mask==0)
		{
			mask=0x80;
			temp++;
		}
		mask = mask >> 1;
	}
	compressed_stream_array_pointer[temp+1]='\0';

	for(int i=0;compressed_stream_array_pointer[i]!='\0';i++)
	{
		cout<<compressed_stream_array_pointer[i];
	}

	ofstream fout("filecompress.cmp",ios::out | ios::binary);
	for(int i=0;compressed_stream_array_pointer[i]!='\0';i++)
	{
		cout<<compressed_stream_array_pointer[i];
	}
	//fout.open("filecompress.cmp",ios::binary);
	//fout.write((char*) compressed_stream_array_pointer,size_of_compressed_stream_array);
	//fout.close();

}
int  calculating_size_of_dynamic_array_named_stream(int bits,int total_no_of_characters_in_file)
{
	int temp=0;
	temp=bits*total_no_of_characters_in_file;
	return temp;
}
void creating_hidden_info_cmp_file(int bits,int no_of_letters_in_original_file,char array_containing_unique_letters[])
{
	ofstream fout;
	fout.open("info.cmp");
	SetFileAttributes("info.cmp",FILE_ATTRIBUTE_HIDDEN);
	fout<<bits<<" ";
	fout<<no_of_letters_in_original_file<<endl;
	for(int i=0;array_containing_unique_letters[i]!='\0';i++)
	{
		fout<<array_containing_unique_letters[i]<<" | ";
	}
}






