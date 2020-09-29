/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_decis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerebus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:42:14 by cerebus           #+#    #+#             */
/*   Updated: 2020/09/29 12:42:20 by cerebus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

s_decis *get_deсis(s_board *m_board)
{
	int i = 0;
	int j = 0;
	s_decis *desic;

	desic = create_desis(i, j, 0);
	 while (i < (m_board->lines))
	 {
		j = 0;
	 	while(j <= m_board->columns)
	 	{
	 		if (i*j == 0)
			 {
				j++;
 				continue;	
			}
			//если индекс равен единице (т.е. "пустой")
			// if(m_board ->my_arr[i][j] == 1) 
			// {
			// 	//увеличиваем значение ячейки на минимальное соседнее
			// 	m_board ->my_arr[i][j] = min(m_board ->my_arr[i][j-1], m_board ->my_arr[i-1][j], m_board ->my_arr[i -1][j-1]) + 1;
			// }
			m_board ->my_arr[i][j] = (m_board ->my_arr[i][j] == 1) ? 
				(min(m_board ->my_arr[i][j-1],
				m_board ->my_arr[i-1][j], m_board ->my_arr[i -1][j-1]) + 1) : (m_board ->my_arr[i][j]);

			if(m_board ->my_arr[i][j] > (desic->steps))
				{
					desic->steps = m_board ->my_arr[i][j];
					desic->x = i;
					desic->y = j;
				}
	 		j++;
	 	}
		i++;
	}
	return (desic);
}
