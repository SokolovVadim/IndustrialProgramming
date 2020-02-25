#pragma once
#define CASE(NUM, SIZEARG, COMMAND)                            \
       case SIZEARG:                                           \
       {                                                       \
		    COMMAND;                                           \
	   }


#define PRINT(FILENAME, PARAM, TEXT)                           \
        fprintf(FILENAME, #PARAM #TEXT);

#define PRINTP(FILENAME, PARAM, TEXT)                          \
        fprintf(FILENAME, #PARAM, (TEXT));

#define PRINTF(FILENAME, PARAM, TEXT_1, TEXT_2)                \
		fprintf(FILENAME, #PARAM, (TEXT_1), (TEXT_2));


#define SCAN(BUFF, PARAM, BUFFER)                              \
		sscanf_s(BUFF, #PARAM, BUFFER, SIZEBUFF);

#define IND(BUFF, BUFFER)                                      \
		int differ = IncreasePtr(BUFF, BUFFER); return differ;


#define REGSUB(BUFFER)                                         \
        (BUFFER[0] - 'a')

#define SIGNSUB(BUFFER)                                        \
		(BUFFER[0] - 'A' + BUFFER[1] - 'A')

#define GETSEC(BUFF, BUFFER)                                   \
		int differ = IncreasePtr(BUFF, BUFFER);                \
        fprintf(Log, "\n\nGETSEC: SIGN = %d\n", SIGNSUB(BUFFER)); \
		buff += differ;                                        \
		SCAN(BUFF, %s, BUFFER);                                \
        EMIT1(atoi(BUFFER), binbuff, newcounter, char);        \
        *newcounter = 3;                                       \
		differ += IncreasePtr(BUFF, BUFFER);                   \
		PRINTP(Fout, \t%s\n, BUFFER);                          \
		PRINTP(Text, %d\n, atoi(BUFFER));                      \
		return differ;


#define GETSEC1(BUFF, BUFFER)                                  \
        SCAN(BUFF, %s, BUFFER);       \
        PRINTP(Fout, \t%s, BUFFER);        \
		int differ = IncreasePtr(BUFF, BUFFER);                \
		buff += differ;                                        \
        char buffer1[SIZEBUFF];  \
        SCAN(BUFF, %s, buffer1);  \
        PUTVALUE2(buffer1);                                     \
        *newcounter += 2;                                       \
		differ += IncreasePtr(BUFF, buffer1);                   \
		PRINTP(Fout, \t%s\n, buffer1);                          \
		return differ;





#define DO(COMMAND)                           \
        do                                    \
		{                                     \
		     COMMAND                          \
		}while(0)




//int buffer[]={ 128, 12, 64, 342, 231 };
//char arr[5];
//memcpy_s(arr, sizeof(arr), buffer, sizeof(int));
//for (int i(0); i < 1; ++i)\
		// printf("%d\t", arr[i]);



 //int *buffer = (int*)calloc(5, sizeof(int));
	// buffer[0] = 123;
	// buffer[1] = 125;
	// char* arr;
	// arr = (char*)calloc(5, sizeof(char));
	// char* arrr;
	// arrr = (char*)calloc(5, sizeof(char));
	// memcpy_s(arr, sizeof(arr), buffer, sizeof(int));
	// strcat_s(arrr, sizeof(arr), arr);
	// buffer[0] = 98;
	// memcpy_s(arr, sizeof(arr), buffer, sizeof(int));
	// strcat_s(arrr, sizeof(arr), arr);
	// for (int i(0); i < 2; ++i)\
	// 		 printf("%d\t", arrr[i]);





// err = memcpy_s(a1, sizeof(a1), a2, 10 * sizeof (int) );

 #define EMIT(BUFF, BINBUFF, COUNTER, TYPE)                                 \
         do                                                                 \
         {                                                                  \
              TYPE value;                                                   \
              if(sizeof(TYPE) == sizeof(int))                               \
			  {                                                             \
                   value = atoi(BUFF);           /*!!!!int!!!!!*/           \
                   fprintf(Log, "EMIT INT { TYPE: %d }\n", sizeof(TYPE));   \
			  }                                                             \
              else                                                          \
              {                                                             \
                   value = atof(BUFF);           /*!!!!double!!!!!*/        \
                   fprintf(Log, "EMITDOUBLE { TYPE: %d }\n", sizeof(TYPE)); \
		      }                                                             \
		      memcpy_s(BINBUFF, sizeof(TYPE), &value, sizeof(TYPE));        \
              *COUNTER = sizeof(TYPE);                                      \
                                                                            \
         } while (0);



 #define EMIT1(VALUE, BINBUFF, COUNTER, TYPE)                               \
         do                                                                 \
         {                                                                  \
              int value = VALUE;                                            \
              fprintf(Log, "EMIT 1 { value = %d TYPE: %d }\n", value, sizeof(TYPE));\
		      memcpy_s(binbuff, sizeof(TYPE), &value, sizeof(TYPE));        \
              *newcounter = sizeof(TYPE);                                   \
              binbuff += sizeof(TYPE);                                      \
         } while (0);


// bool flag_value(true);
// *flag_value = false;



// false for double
#define SEARCH(VALUE)                                                       \
do                                                                          \
{                                                                           \
    int sizes(strlen(VALUE));                                               \
    *flag_value = true;                                                     \
	for (int increas(0); increas < sizes; increas++)                        \
	{                                                                       \
		if ((VALUE[increas] == '.') || (VALUE[increas] == 'e'))             \
		{                                                                   \
			*flag_value = false;                                            \
			break;                                                          \
		}                                                                   \
	}                                                                       \
    fprintf(Log, "SEARCH: VALUE : %s flag = %d\n", VALUE, *flag_value);     \
} while (0);




#define PUTVALUE(BUFFER)                                                    \
do                                                                          \
{                                                                           \
	SEARCH(BUFFER);                                                         \
	if (*flag_value)                                                        \
	{                                                                       \
		EMIT(BUFFER, binbuff, newcounter, int)                              \
	}                                                                       \
	else                                                                    \
	{                                                                       \
		EMIT(BUFFER, binbuff, newcounter, double)                           \
	}                                                                       \
}while(0);

#define PUTVALUE1(BUFFER)                                                   \
do                                                                          \
{                                                                           \
	SEARCH(BUFFER);                                                         \
	if (*flag_value)                                                        \
	{                                                                       \
        PRINTF(Text, %d \t%d\n, cmd_pushi, atoi(buffer));                        \
        EMIT1(cmd_pushi, binbuff, newcounter, char);                        \
		EMIT(BUFFER, binbuff, newcounter, int);                             \
		/*PRINTP(Text, %d\n, atoi(BUFFER));*/                                   \
	}                                                                       \
	else                                                                    \
	{                                                                       \
        PRINTF(Text, %d \t%lf\n, cmd_pushd, atof(buffer));                        \
        EMIT1(cmd_pushd, binbuff, newcounter, char);                        \
		EMIT(BUFFER, binbuff, newcounter, double)                           \
		/*PRINTP(Text, %d\n, atof(BUFFER));*/                                   \
	}                                                                       \
}while(0);


#define PUTVALUE2(BUFFER)                                                   \
do                                                                          \
{                                                                           \
	SEARCH(BUFFER);                                                         \
	if (*flag_value)                                                        \
	{                                                                       \
        PRINTF(Text, %d \t%d\t, cmd_pushri, buffer[0] - 'a');                        \
        EMIT1(cmd_pushri, binbuff, newcounter, char);                       \
        EMIT1(REGSUB(buffer), binbuff, newcounter, char);                   \
		EMIT(BUFFER, binbuff, newcounter, int);                             \
		PRINTP(Text, %d\n, atoi(BUFFER));                                   \
	}                                                                       \
	else                                                                    \
	{                                                                       \
        PRINTF(Text, %d \t%d\t, cmd_pushrd, buffer[0] - 'a');               \
        EMIT1(cmd_pushrd, binbuff, newcounter, char);                       \
        EMIT1(REGSUB(buffer), binbuff, newcounter, char);                   \
		EMIT(BUFFER, binbuff, newcounter, double)                           \
		PRINTP(Text, %lf\n, atof(BUFFER));                                  \
	}                                                                       \
}while(0);