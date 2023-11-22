/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:39 by graux             #+#    #+#             */
/*   Updated: 2023/11/22 21:33:54 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int i) : fd(i)
{
}

char	*Client::getReadBuff(void)
{
	return (read_buff);
}

char	*Client::getSendBuff(void)
{
	return (read_buff);
}
