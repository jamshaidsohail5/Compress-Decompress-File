//Libraries to be used.

#include<iostream>//Used for basic input/output.
#include<cmath>//Used for ciling function.
#include<fstream>//Used for file Handling.
#include<string>//Used for string copy function.
#include<math.h>//Used for calculating log function.
#include<Windows.h>//Used for adding colours in the program.

//Functions to be used.
//Function prototypes.


void copy_file_characters (char arr[]);//This function copy the charcters contained in the file into a character array.
void displaying_array(char arr[]);//This function displays the array on the screen.
void copy_into_other_array(char arr[]);//This function copy one array into other array.
void deleting_repitition(char arr[]);//This function deletes the repetition in the array.
int  calculating_unique_letters(char arr[]);//This function calculates the number of unique letters in the array.
double calculating_no_of_bits(double lenght);//This function calculates the number of bits in the array. 
void displaying_binary(char arr[],int lenght,int bits_calculated);//This function displays the binary on the screen .
void converting_to_binary(int bit_calculated,int index);//This functions converts the number into binary according to the bits calculated. 


using namespace std;




int main()//This is the main.
{

	char arr[1000000];
	copy_file_characters(arr);//In this function i will copy the characters that are contained in file.
	copy_into_other_array(arr);//In this function i will copy "arr" into a temporary array.
	deleting_repitition(arr);//In this function the characters which are repeated will be deleted.
	system("pause");
	return 0;

}
void copy_file_characters (char arr[])
{
	ifstream fin;
	fin.open("jamshaid.txt");//opens the file for getting input.
	char ch='\0';
	int i=0;
	fin.getline(arr,1000000);
	fin.close();
}
void displaying_array(char arr[])
{
	for(int i=0;arr[i]!='\0';i++)
	{
		cout<<arr[i]<<"|";
	}

}
void copy_into_other_array(char arr[])
{
	char temparr[100]={'\0'};
	strcpy(temparr,arr);//using the string copy function.
}
void deleting_repitition(char arr[])
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


	int no_of_unique_letters=calculating_unique_letters(arr);//calculating number of unique letters in the file
	double bits=calculating_no_of_bits(no_of_unique_letters);//calculating number of bits that will be assigned per unique letter.


	//used for adding colours.
	HANDLE hconsole=0;
	hconsole=GetStdHandle(STD_OUTPUT_HANDLE);


	//From here on all the manipulation performed in the program will be displayed on the screen.



	SetConsoleTextAttribute(hconsole,11);
	cout<<"I hope you will find my code user friendly "<<endl<<endl;
	SetConsoleTextAttribute(hconsole,10);//sets the colour of text.
	cout<<"The array containing unique letters are "<<endl<<endl;
	displaying_array(arr);
	cout<<endl<<endl;
	SetConsoleTextAttribute(hconsole,06);
	cout<<"There are "<<no_of_unique_letters<<" unique letters in the file ."<<endl<<endl;
	SetConsoleTextAttribute(hconsole,13);
	cout<<"The bits per unique letter is "<<bits<<" bits ."<<endl<<endl;
	SetConsoleTextAttribute(hconsole,12);
	cout<<"The bits assigned per unique letters are "<<endl<<endl;
	displaying_binary(arr,no_of_unique_letters,bits);
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
void displaying_binary(char arr[],int lenght,int bits_calculated)
{
	char temparr[1000]={'\0'};
	ifstream fin;
	fin.open("jamshaid.txt");
	while(!fin.eof())
	{
		fin.getline(temparr,1000,'\n');
			for(int j=0;temparr[j]!='\0';j++)

		{
		for(int i=0;arr[i]!='\0';i++)

			{
				if(arr[i]==temparr[j])
				{
					converting_to_binary(bits_calculated,i);
				}
			}
		}
	}
}
void converting_to_binary(int bit_calculated,int index)
{   int  count=0;
//This for loop works according to the bits calculated for example if the bits calculated are 4 then it will display the binary of number in 4bits.
for(int i=bit_calculated-1;i>=0;i--)
{
	//This counter is used to determine when the bits of first unique letter is displayed.

	count++;

	//This statement right shift the decimal number and then takes its modulus by 2 and displays the remainder on the screen.

	cout<<((index>>i)%2);


	//This if statement separates the bits assigned to the first unique letter from the bits assigned to the second unique letter.

	if(count==bit_calculated)
	{
		cout<<" ";
	}
}
}





