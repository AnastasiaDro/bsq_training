/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:07:01 by cerebus           #+#    #+#             */
/*   Updated: 2020/09/28 13:07:02 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "functions.h"
#define BUFF_SIZE 1024
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #include <fcntl.h>

// //s_decis *my_square(char **arr, int lines, int columns);
 //s_decis *get_deсis(int **arr, int lines, int columns);
// //создать структуру с чарами
// s_chars	*create_s_chars(char empt, char obs, char full);
// //создать доску
// s_board	*create_s_board(s_chars *m_chars, int lines, int columns, int **my_arr);
// int read_from_file(char *file_name, char *buffer); //функция чтения из файла
// //посчитать число элементов в первой строке
// int count_columns(char *arr, int start);
// int count_args(char *arr);
// //char **create_my_2_arr(int lines, int columns, char *buffer, int start);
// int **create_my_2_arr(int lines, int columns, char *buffer, int start);
// s_decis	*create_desis(int x, int y, char steps);
// //char min(char first, char second, char third);
// int min(int first, int second, int third);
// void print_arr(int **arr, int lines, int columns);

// //заменитель единицы и нуля на символ, для результата
// char change_num_to_char(s_decis *m_dis, int i, int j, s_board *m_board);
// //распечатка результата
// void print_res_arr(s_decis *m_dis, s_board *m_board);

int main(int argc, char *argv[])
{

	//доска
	s_board *m_board;
	//символы

	s_chars *m_chars;
	//имя нужного файла
	char *file_name = 0;
	//делаем буффер
	char *buffer;
	//число строк
	int lines;
	int columns;
	//число байт
	int bytes_num;
	//число аргументов
	int args_count;

	//задаем наши чары
	m_chars = create_s_chars('.', '0', 'x');

	lines = 9;
	s_decis *decis;
   //условие обработки одного файла
   if (argc == 2)
   {
	file_name = argv[1];
	//читаем из файла нашу доску
	buffer = malloc(BUFF_SIZE);
	 bytes_num = read_from_file(file_name, buffer);
	//узнаем число аргументов
	args_count = count_args(buffer);

	
	 printf("число считанных байт %d\n", bytes_num);
	 //узнаем число колонок
	columns = count_columns(buffer, args_count);
	printf("число колонок %d\n", columns);



	//теперь нужно создать двумерный массив
	int **my_arr = create_my_2_arr(lines, columns, buffer, args_count);
	//создаем нашу доску
	m_board = create_s_board(m_chars, lines, columns, my_arr);
	
	//получаем решение
	decis = get_deсis(m_board);
	printf("x квадрата %d\n", decis->x);
    printf("y квадрата %d\n", decis->y);
    printf("число шагов %d\n", decis->steps);
	//печатаем исходный массив
	print_arr(my_arr, lines, columns);
	//печатаем результат
	print_res_arr(decis, m_board);
   }
}


//распечатка файла
void print_result(char *arr, int bytes_count)
{
	write (1, arr, bytes_count);
}


void print_arr(int **arr, int lines, int columns)
{
	int i = 0;
	int j = 0;
	char *newline = "\n";
	while (i < lines)
	{
		j=0;
		while (j<columns)
		{
			ft_putnbr(arr[i][j]);
			j++;
		}
		write(1, newline, 1);
		i++;
	}
}

//функция чтения из файла
int read_from_file(char *file_name, char *buffer)
{
	int fd;  //дескриптор
	int rd_bs_count; //число прочитанных байтов
	int bytes_count; //счётчик прочитанных байт  

	rd_bs_count = 0;
	fd = 0;
	//открываем файл на чтение
	fd = open(file_name, O_RDONLY);

	while ((bytes_count = read(fd, buffer, BUFF_SIZE))>0)
	{
	   rd_bs_count = rd_bs_count + bytes_count;
		//printf("число байт в цикле%d\n", rd_bs_count);
	}
	close(fd);
	return (rd_bs_count);
}

//считаем длину строки аргументов
int count_args(char *arr)
{
	int i;
	i = 0;
	while (arr[i]!='\n')
	{
		i++;
	}
	i++;
	return i;
}

//считаем длину строки
int count_columns(char *arr, int start)
{
	int g = 0;
	while(arr[start]!='\n')
	{
		g++;
		start++;
	}
	return(g);
}

//создаём двумерный массив и сразу делаем его интовым - из нулей и единиц
int **create_my_2_arr(int lines, int columns, char *buffer, int start)
{
	int **arr;
	int i; 
	int j;

	arr = malloc(sizeof(int *)*lines);
	i = 0;
	while (i < lines)
	{
		j = 0;
		arr[i] = malloc(sizeof(int)*(columns));
		while (buffer[start] != '\n')
		{
			if (buffer[start] == '.')
			{
				arr[i][j] = 1;
				printf("%d", arr[i][j]);
			} else {
				arr[i][j] = 0;
				printf("%d", arr[i][j]);
			}
			start++;
			j++;
		}
		printf("\n");
		start++;
		i++;
	}
	return (arr);
}


//ищем решение - индексы стартового элемента и кол-во шагов от него
//s_decis *get_deсis(int **arr, int lines, int columns, s_board *m_board)
// s_decis *get_deсis(s_board *m_board)
// {
// 	int i = 0;
// 	int j = 0;
// 	s_decis *desic;

// 	desic = create_desis(i, j, 0);
// 	 while (i < (m_board->lines))
// 	 {
// 		j = 0;
// 	 	while(j <= m_board->columns)
// 	 	{
// 	 		if (i*j == 0)
// 			 {
// 				j++;
//  				continue;	
// 			}
// 			//если индекс равен единице (т.е. "пустой")
// 			// if(m_board ->my_arr[i][j] == 1) 
// 			// {
// 			// 	//увеличиваем значение ячейки на минимальное соседнее
// 			// 	m_board ->my_arr[i][j] = min(m_board ->my_arr[i][j-1], m_board ->my_arr[i-1][j], m_board ->my_arr[i -1][j-1]) + 1;
// 			// }
// 			m_board ->my_arr[i][j] = (m_board ->my_arr[i][j] == 1) ? 
// 				(min(m_board ->my_arr[i][j-1],
// 				m_board ->my_arr[i-1][j], m_board ->my_arr[i -1][j-1]) + 1) : (m_board ->my_arr[i][j]);

// 			if(m_board ->my_arr[i][j] > (desic->steps))
// 				{
// 					desic->steps = m_board ->my_arr[i][j];
// 					desic->x = i;
// 					desic->y = j;
// 				}
// 	 		j++;
// 	 	}
// 		i++;
// 	}
// 	return (desic);
// }


//поиск минимального значения
// int min(int first, int second, int third)
// {
// 	int min = first;
// 	min = (first > second) ? second : first;
// 	min = (min > third) ? third : min;
// 	return (min);
// }

//создать структуру-решение
// s_decis	*create_desis(int x, int y, char steps)
// {
// 	s_decis *my_desis;

// 	my_desis = malloc(sizeof(s_decis));
// 	if (!my_desis)
// 	{
// 		return (0);
// 	}
// 	my_desis->x = x;
// 	my_desis->y = y;
// 	my_desis->steps = steps;
// 	return (my_desis);
// }



//создать структуру с чарами
// s_chars	*create_s_chars(char empt, char obs, char full)
// {
// 	s_chars *my_chars;

// 	my_chars = malloc(sizeof(my_chars));
// 	if (!my_chars)
// 	{
// 		return (0);
// 	}
// 	my_chars->empt = empt;
// 	my_chars->obs = obs;
// 	my_chars->full = full;
// 	return (my_chars);
// }

//создать структуру доску
s_board	*create_s_board(s_chars *m_chars, int lines, int columns, int **my_arr)
{
	s_board *m_board;

	m_board = malloc(sizeof(m_board));
	if (!m_board)
	{
		return (0);
	}
	m_board->m_chars = m_chars;
	m_board->lines = lines;
	m_board->columns = columns;
	m_board->my_arr = my_arr;
	return (m_board);
}

//заменитель единицы и нули на символ
char change_num_to_char(s_decis *m_dis, int i, int j, s_board *m_board)
{
	int start_x;
	int start_y;
	char res_char;
	
	start_x = m_dis->x - (m_dis->steps - 1);
	start_y = m_dis->y - (m_dis->steps - 1);
	//если i между старт_x и x
	if ((i>=start_x) && (i<=m_dis->x) && (j >= start_y) && (j <= m_dis->y)) 
	{
		res_char = m_board ->m_chars ->full;
	} else {
		//если в этом индексе равно 0,то возвращаем чар 0, иначе возвращаем чар пустота '.';
		res_char = (m_board->my_arr)[i][j] == 0 ? (m_board->m_chars->obs) : (m_board->m_chars->empt);
	}
	return (res_char);
}

void print_res_arr(s_decis *m_dis, s_board *m_board)
{
	int i = 0;
	int j = 0;
	char *newline = "\n";
	char p_char = 'u'; 
	while (i < m_board->lines)
	{
		j=0;
		while (j<m_board->columns)
		{
			p_char = change_num_to_char(m_dis, i, j, m_board);
			write(1, &p_char, 1);
			j++;
		}
		write(1, newline, 1);
		i++;
	}
}
